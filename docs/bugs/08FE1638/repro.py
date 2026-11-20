#!/usr/bin/env python3
"""Behavioural case for func_08FE1638 (GDB's shifted_reg_val in the
development-cartridge debug monitor): a rotate by a nonzero amount returns
the operand unrotated.

    python3 docs/bugs/08FE1638/repro.py [path/to/baserom.bin]

Runs the ORIGINAL function bytes from your ROM and the -DBUGFIX build of
src/**/08FE1638.c under a Thumb emulator from the same saved-register states,
compares both with what an ARM core computes for the same shifter operand
(unicorn's ARM core running one instruction), and runs the ROM's ARM next-PC
decoder func_08FE1B04 with each build to show the misplaced step.  Exits 0
when every assertion holds.

Dependencies
  * Python 3.8+ and unicorn (`pip install unicorn`; tested with 2.1.4).
  * The repository toolchain, as tools/match.py runs it: cpp,
    $HOME/agbcc/gcc/agbcc (override with AGBCC) and arm-none-eabi-as
    (override with CPP / AS).
  * Your ROM: argv[1], default <repo root>/baserom.bin.  No ROM bytes ship
    with this file.  FFTA_ROOT overrides the repository root.

Memory: the monitor image (ROM 0x08FE0000-0x08FE3FFF) is also mapped at its
run address, ROM address + 0x01002000, because its jump tables hold run
addresses and its saved-register block (0x09FE2100) lies inside it.  The ROM
functions run from there.  No callee is stubbed: func_08FE1638 is a leaf, and
func_08FE1B04 runs with the ROM's func_08FE1810 (condition test).
"""
# ---------------------------------------------------------------------------
# Harness: ROM loading, the agbcc build of the source, a minimal ELF linker
# and a Thumb machine (unicorn).  Identical in every docs/bugs/*/repro.py.
# ---------------------------------------------------------------------------
import json, os, re, shutil, struct, subprocess, sys, tempfile
from pathlib import Path

try:
    from unicorn import Uc, UcError, UC_ARCH_ARM, UC_MODE_THUMB, UC_HOOK_CODE
    from unicorn.arm_const import (UC_ARM_REG_R0, UC_ARM_REG_R1, UC_ARM_REG_R2,
                                   UC_ARM_REG_R3, UC_ARM_REG_SP, UC_ARM_REG_LR,
                                   UC_ARM_REG_PC)
except ImportError:
    sys.exit("repro.py needs unicorn: pip install unicorn (tested with 2.1.4)")

ROOT = Path(os.environ.get("FFTA_ROOT", Path(__file__).resolve().parents[3]))
ROM_BASE, ROM_SIZE = 0x08000000, 0x01000000
EWRAM, IWRAM = 0x02000000, 0x03000000
SCRATCH = 0x0A000000          # BUGFIX code and its callee stubs (not GBA memory)
RETURN = SCRATCH + 0xF000     # return address that ends a call
STACK_TOP = IWRAM + 0x7F00    # the GBA user stack top
REGS = (UC_ARM_REG_R0, UC_ARM_REG_R1, UC_ARM_REG_R2, UC_ARM_REG_R3)


def load_rom():
    path = Path(sys.argv[1]) if len(sys.argv) > 1 else ROOT / "baserom.bin"
    data = path.read_bytes()
    if len(data) != ROM_SIZE or data[0xAC:0xB0] != b"AFXE":
        sys.exit(f"{path}: not the FFTA (AFXE) ROM")
    return data


def find_source(address):
    hits = sorted((ROOT / "src").rglob(f"{address:08X}.c"))
    if len(hits) != 1:
        sys.exit(f"expected one src/**/{address:08X}.c under {ROOT}, found {len(hits)}")
    return hits[0]


def compile_source(source, defines=()):
    """cpp -> agbcc -> as, as tools/match.py runs them; returns the .o bytes."""
    agbcc = os.path.expandvars(os.environ.get("AGBCC", "$HOME/agbcc/gcc/agbcc"))
    cpp = os.environ.get("CPP", "cpp")
    gas = os.environ.get("AS", "arm-none-eabi-as")
    for tool in (agbcc, cpp, gas):
        if shutil.which(tool) is None:
            sys.exit(f"toolchain: {tool} not found (set AGBCC / CPP / AS)")
    with tempfile.TemporaryDirectory() as tmp:
        i, s, o = (os.path.join(tmp, "f." + x) for x in "iso")
        run = lambda *cmd: subprocess.run(cmd, check=True, cwd=ROOT, env=dict(os.environ, TMPDIR=tmp))
        run(cpp, "-nostdinc", "-undef", "-I", str(ROOT / "include"),
            *("-D" + d for d in defines), str(source), "-o", i)
        run(agbcc, "-mthumb-interwork", "-O2", i, "-o", s)
        run(gas, "-mthumb-interwork", s, "-o", o)
        return Path(o).read_bytes()


def parse_elf(data):
    """.text, its relocations and the defined function symbols of an ELF32 .o."""
    shoff, = struct.unpack_from("<I", data, 0x20)
    shnum, shstrndx = struct.unpack_from("<HH", data, 0x30)
    sections = [struct.unpack_from("<10I", data, shoff + 40 * k) for k in range(shnum)]
    def string(table, offset):
        start = sections[table][4] + offset
        return data[start:data.index(b"\0", start)].decode()
    names = [string(shstrndx, sec[0]) for sec in sections]
    text_index = names.index(".text")
    text = data[sections[text_index][4]:][:sections[text_index][5]]
    symbols = []
    for sec in sections:
        if sec[1] == 2:                                   # SHT_SYMTAB
            for k in range(sec[5] // 16):
                name, value, size, info, _, shndx = struct.unpack_from("<IIIBBH", data, sec[4] + 16 * k)
                symbols.append((string(sec[6], name), value, size, info & 15, shndx))
    relocs = []
    for sec in sections:
        if sec[1] == 9 and sec[7] == text_index:          # SHT_REL for .text
            for k in range(sec[5] // 8):
                offset, info = struct.unpack_from("<II", data, sec[4] + 8 * k)
                name, _, _, kind, shndx = symbols[info >> 8]
                relocs.append((offset, info & 0xFF, name, kind == 3 and shndx == text_index))
    functions = {name: (value & ~1, size) for name, value, size, kind, shndx in symbols
                 if kind == 2 and shndx == text_index}
    return text, relocs, functions


def data_symbols():
    path = ROOT / "config" / "data_symbols.json"
    return {k: int(v, 0) for k, v in json.loads(path.read_text()).items()} if path.exists() else {}


def address_of(name, table):
    if name in table:
        return table[name]
    match = re.search(r"_([0-9A-Fa-f]{8})$", name)
    if not match:
        sys.exit(f"cannot place symbol {name}")
    return int(match.group(1), 16)


def link(obj, base, resolve):
    """Places .text at base and applies R_ARM_ABS32 / R_ARM_THM_CALL."""
    text, relocs, functions = obj
    code = bytearray(text)
    for offset, kind, name, local in relocs:
        target = base if local else resolve(name)
        if kind == 2:                                      # R_ARM_ABS32
            addend, = struct.unpack_from("<I", code, offset)
            if name.startswith("func_") and not local:
                target |= 1
            struct.pack_into("<I", code, offset, (target + addend) & 0xFFFFFFFF)
        elif kind == 10:                                   # R_ARM_THM_CALL
            high, low = struct.unpack_from("<HH", code, offset)
            addend = ((high & 0x7FF) << 12) | ((low & 0x7FF) << 1)
            addend -= (addend & 0x400000) << 1
            value = (target & ~1) + addend - (base + offset)
            if not -0x400000 <= value < 0x400000:
                sys.exit(f"BL to {name} out of range")
            struct.pack_into("<HH", code, offset, 0xF000 | ((value >> 12) & 0x7FF),
                             0xF800 | ((value >> 1) & 0x7FF))
        else:
            sys.exit(f"unsupported relocation type {kind} against {name}")
    return bytes(code), functions


class Machine:
    """A Thumb CPU with the ROM, EWRAM, IWRAM and a scratch page mapped."""

    def __init__(self, rom):
        self.uc = Uc(UC_ARCH_ARM, UC_MODE_THUMB)
        for base, size in ((EWRAM, 0x40000), (IWRAM, 0x8000), (ROM_BASE, ROM_SIZE), (SCRATCH, 0x10000)):
            self.uc.mem_map(base, size)
        self.uc.mem_write(ROM_BASE, rom)
        self.uc.mem_write(RETURN, b"\x70\x47")            # never executed: the run stops here
        self.stubs = {}
        self.next_stub = SCRATCH + 0xE000
        self.uc.hook_add(UC_HOOK_CODE, self._stub_hook, begin=SCRATCH + 0xE000, end=SCRATCH + 0xEFFF)

    def _stub_hook(self, uc, address, size, _):
        if address in self.stubs:
            self.stubs[address](self)

    def stub(self, address, behaviour):
        """Replaces the callee at address with `bx lr` after running behaviour(machine)."""
        self.uc.mem_write(address & ~1, b"\x70\x47")
        self.stubs[address & ~1] = behaviour
        self.uc.hook_add(UC_HOOK_CODE, self._stub_hook, begin=address & ~1, end=address & ~1)

    def scratch_stub(self, behaviour):
        address = self.next_stub
        self.next_stub += 4
        self.uc.mem_write(address, b"\x70\x47")
        self.stubs[address] = behaviour
        return address

    def veneer(self, target):
        address = self.next_stub = (self.next_stub + 3) & ~3
        self.next_stub += 16
        self.uc.mem_write(address, struct.pack("<6HI", 0xB401, 0x4802, 0x4684, 0xBC01,
                                               0x4760, 0x46C0, target | 1))
        return address

    def load(self, address, code):
        self.uc.mem_write(address, code)

    def reg(self, index):
        return self.uc.reg_read(REGS[index])

    def set_reg(self, index, value):
        self.uc.reg_write(REGS[index], value & 0xFFFFFFFF)

    def stack_arg(self, n):
        """The n-th stacked argument (0 = the fifth) at a callee's entry."""
        return self.u32(self.uc.reg_read(UC_ARM_REG_SP) + 4 * n)

    def call(self, address, *args):
        sp = STACK_TOP - 0x40
        for k, value in enumerate(args[4:]):
            self.w32(sp + 4 * k, value)
        for k, value in enumerate(args[:4]):
            self.set_reg(k, value)
        self.uc.reg_write(UC_ARM_REG_SP, sp)
        self.uc.reg_write(UC_ARM_REG_LR, RETURN | 1)
        self.uc.emu_start(address | 1, RETURN, count=2_000_000)
        if self.uc.reg_read(UC_ARM_REG_PC) & ~1 != RETURN:
            sys.exit(f"call to {address:08X} did not return")
        return self.reg(0)

    def u8(self, a):  return self.uc.mem_read(a, 1)[0]
    def u16(self, a): return struct.unpack("<H", self.uc.mem_read(a, 2))[0]
    def s16(self, a): return struct.unpack("<h", self.uc.mem_read(a, 2))[0]
    def u32(self, a): return struct.unpack("<I", self.uc.mem_read(a, 4))[0]
    def s32(self, a): return struct.unpack("<i", self.uc.mem_read(a, 4))[0]
    def w8(self, a, v):  self.uc.mem_write(a, struct.pack("<B", v & 0xFF))
    def w16(self, a, v): self.uc.mem_write(a, struct.pack("<H", v & 0xFFFF))
    def w32(self, a, v): self.uc.mem_write(a, struct.pack("<I", v & 0xFFFFFFFF))


def build_pair(rom, address, extent):
    """Compiles the source twice.  The default build, linked at the function's
    own address, must equal the ROM bytes: that checks the ROM, the toolchain
    and this linker at once.  Returns the source path and the -DBUGFIX object."""
    source = find_source(address)
    table = data_symbols()
    default, functions = link(parse_elf(compile_source(source)), address,
                              lambda n: address_of(n, table))
    start, size = functions.get(f"func_{address:08X}", (0, 0))
    if size != extent or default[start:start + size] != rom[address - ROM_BASE:][:extent]:
        sys.exit(f"default build of {source} does not reproduce the ROM bytes")
    return source, parse_elf(compile_source(source, ["BUGFIX"]))


def install_fixed(machine, obj, bindings):
    """Links the -DBUGFIX object into the scratch page; returns its entry.

    The scratch page is out of BL range of the ROM, so each call goes to a
    slot there: bindings[name] is either a Python stub (the same behaviour
    the ROM callee is given) or a ROM address, reached through a veneer that
    keeps r0-r3 and lr (ldr r0, =target; mov ip, r0; bx ip)."""
    table = data_symbols()
    slots = {}
    for name, binding in bindings.items():
        if callable(binding):
            slots[name] = machine.scratch_stub(binding)
        else:
            slots[name] = machine.veneer(binding)
    def resolve(name):
        if name in slots:
            return slots[name]
        if name.startswith("func_"):
            sys.exit(f"the BUGFIX build calls {name}, which this case does not bind")
        return address_of(name, table)
    code, functions = link(obj, SCRATCH, resolve)
    machine.load(SCRATCH, code)
    (start, _), = functions.values()
    return SCRATCH + start


class Checks:
    def __init__(self):
        self.failed = 0

    def check(self, label, got, want):
        ok = got == want
        self.failed += not ok
        print(f"  [{'ok' if ok else 'FAIL'}] {label}: {got!r}" + ("" if ok else f" (expected {want!r})"))

    def finish(self):
        print("\nall assertions hold" if not self.failed else f"\n{self.failed} assertion(s) failed")
        sys.exit(1 if self.failed else 0)
# ----------------------------------------------------------------------------
from unicorn import UC_MODE_ARM
from unicorn.arm_const import (UC_ARM_REG_R4, UC_ARM_REG_R5, UC_ARM_REG_R6, UC_ARM_REG_R7,
                               UC_ARM_REG_R8, UC_ARM_REG_R9, UC_ARM_REG_R10, UC_ARM_REG_R11,
                               UC_ARM_REG_R12, UC_ARM_REG_CPSR)

ADDRESS, EXTENT = 0x08FE1638, 306
IMAGE, IMAGE_SIZE = 0x08FE0000, 0x4000   # the debug monitor's memory image in the ROM
LINK = 0x01002000                        # it runs at its ROM address + LINK
REGS_AT = 0x09FE2100                     # saved r0-r15, then CPSR (index 16)
CPSR_AT = REGS_AT + 4 * 16
ARM_STEP = 0x08FE1B04                    # func_08FE1B04(pc, &is_arm): next PC of an ARM instruction
INSN_AT = EWRAM + 0x100                  # where the stepped instruction sits
FLAG_C = 0x20000000
SYS_ARM = 0x1F                           # CPSR: System mode, ARM state
ALL_REGS = REGS + (UC_ARM_REG_R4, UC_ARM_REG_R5, UC_ARM_REG_R6, UC_ARM_REG_R7, UC_ARM_REG_R8,
                   UC_ARM_REG_R9, UC_ARM_REG_R10, UC_ARM_REG_R11, UC_ARM_REG_R12,
                   UC_ARM_REG_SP, UC_ARM_REG_LR)


def veneer_at(m, address, target):
    """The harness veneer (ldr r0, =target; mov ip, r0; bx ip), written over a ROM function."""
    m.uc.mem_write(address, struct.pack("<6HI", 0xB401, 0x4802, 0x4684, 0xBC01,
                                        0x4760, 0x46C0, target | 1))


def machine(rom, fixed_obj=None):
    """The ROM, plus the monitor image mapped at its run address: its jump
    tables (func_08FE1810 at 0x09FE3840, func_08FE1B04 at 0x09FE3E40) hold run
    addresses, and its saved-register block lies inside the image."""
    m = Machine(rom)
    m.uc.mem_map(IMAGE + LINK, IMAGE_SIZE)
    m.uc.mem_write(IMAGE + LINK, rom[IMAGE - ROM_BASE:][:IMAGE_SIZE])
    entry = ADDRESS + LINK
    if fixed_obj is not None:
        entry = install_fixed(m, fixed_obj, {})
        # The ARM decoder's BLs (0x08FE1D00, 0x08FE1E20) reach the run copy
        # of func_08FE1638: send them to the BUGFIX build.
        veneer_at(m, ADDRESS + LINK, entry)
    return m, entry


def stop_cpu(m, regs, cpsr):
    """Fills the monitor's saved-register block for a CPU stopped in System mode."""
    for k in range(26):
        m.w32(REGS_AT + 4 * k, 0)
    for k, value in regs.items():
        m.w32(REGS_AT + 4 * k, value)
    m.w32(CPSR_AT, cpsr)


def cpu(inst, regs, cpsr):
    """What an ARM core computes: runs one ARM instruction (unicorn's ARM core)
    with the registers set and returns (r2 after, pc after)."""
    uc = Uc(UC_ARCH_ARM, UC_MODE_ARM)
    uc.mem_map(EWRAM, 0x40000)
    uc.mem_write(INSN_AT, struct.pack("<I", inst))
    for k, reg in enumerate(ALL_REGS):
        uc.reg_write(reg, regs.get(k, 0))
    uc.reg_write(UC_ARM_REG_CPSR, cpsr)
    uc.emu_start(INSN_AT, INSN_AT + 4, count=1)
    return uc.reg_read(REGS[2]), uc.reg_read(UC_ARM_REG_PC)


def operand(inst):
    """The same shifter operand as `mov r2, ...`, so the core's value can be read."""
    return (inst & 0xFFF) | 0xE1A02000


def main():
    rom = load_rom()
    source, fixed_obj = build_pair(rom, ADDRESS, EXTENT)
    print(f"source {source.relative_to(ROOT)}: default build == ROM bytes "
          f"[{ADDRESS:08X}, {ADDRESS + EXTENT:08X})")
    original, fixed = machine(rom), machine(rom, fixed_obj)
    c = Checks()

    def both(inst, regs, cpsr=SYS_ARM):
        out = []
        for m, entry in (original, fixed):
            stop_cpu(m, regs, cpsr)
            out.append(m.call(entry, inst, INSN_AT))
        return out

    x = 0x12345678
    print("\n1. Trigger: an immediate rotate, `mov pc, r0, ror #8` (0xE1A0F460),")
    print("   r0 = 0x12345678.  ROM: the operand comes back unrotated.")
    inst = 0xE1A0F460
    rom_value, fixed_value = both(inst, {0: x})
    core = cpu(operand(inst), {0: x}, SYS_ARM)[0]
    c.check("ROM    operand", hex(rom_value), hex(x))
    c.check("BUGFIX operand", hex(fixed_value), hex(0x78123456))
    c.check("ARM core (mov r2, r0, ror #8)", hex(core), hex(fixed_value))

    print("\n2. Trigger: a register rotate, `mov pc, r0, ror r1` (0xE1A0F170), r1 = 4.")
    inst = 0xE1A0F170
    rom_value, fixed_value = both(inst, {0: x, 1: 4})
    core = cpu(operand(inst), {0: x, 1: 4}, SYS_ARM)[0]
    c.check("ROM    operand", hex(rom_value), hex(x))
    c.check("BUGFIX operand", hex(fixed_value), hex(0x81234567))
    c.check("ARM core", hex(core), hex(fixed_value))

    print("\n3. Non-trigger: RRX (`ror #0`, 0xE1A0F060), carry from the saved CPSR.")
    inst = 0xE1A0F060
    for carry in (0, FLAG_C):
        values = both(inst, {0: x}, SYS_ARM | carry)
        core = cpu(operand(inst), {0: x}, SYS_ARM | carry)[0]
        c.check(f"C={int(bool(carry))}: ROM, BUGFIX, ARM core",
                [hex(v) for v in values + [core]], [hex((x >> 1) | (0x80000000 if carry else 0))] * 3)

    print("\n4. Non-trigger: the other shift types agree with the core.")
    for name, inst, regs in (("lsl #4", 0xE1A0F200, {0: x}), ("lsr #12", 0xE1A0F620, {0: x}),
                             ("asr #8", 0xE1A0F440, {0: 0x87654321}),
                             ("lsl r1 (r1 = 40)", 0xE1A0F110, {0: x, 1: 40})):
        values = both(inst, regs)
        core = cpu(operand(inst), regs, SYS_ARM)[0]
        c.check(f"{name:17} ROM, BUGFIX, ARM core", [hex(v) for v in values + [core]], [hex(core)] * 3)

    print("\n5. Inherited from GDB, not this bug: both builds, like GDB's")
    print("   shifted_reg_val, take a shift field of 0 literally and treat a")
    print("   register rotate by a multiple of 32 as RRX.  The core differs.")
    for name, inst, regs, gdb in (("lsr #0 (= lsr #32)", 0xE1A0F020, {0: x}, x),
                                  ("asr #0 (= asr #32)", 0xE1A0F040, {0: 0x87654321}, 0x87654321),
                                  ("ror r1, r1 = 32", 0xE1A0F170, {0: x, 1: 32}, x >> 1)):
        values = both(inst, regs)
        core = cpu(operand(inst), regs, SYS_ARM)[0]
        c.check(f"{name:19} ROM, BUGFIX", [hex(v) for v in values], [hex(gdb)] * 2)
        print(f"      ARM core: {core:#x}")

    print("\n6. Impact: the ROM's ARM decoder func_08FE1B04 predicts the next PC of")
    print("   `mov pc, r0, ror #8` with r0 = 0x00020002.  The core goes to 0x02000200.")
    inst, regs = 0xE1A0F460, {0: 0x00020002, 15: INSN_AT}
    core_pc = cpu(inst, regs, SYS_ARM)[1]
    predicted = []
    for m, _ in (original, fixed):
        stop_cpu(m, regs, SYS_ARM)
        m.w32(INSN_AT, inst)
        out = STACK_TOP - 0x80
        predicted.append(m.call(ARM_STEP + LINK, INSN_AT, out))
    c.check("ARM core next PC", hex(core_pc), hex(0x02000200))
    c.check("ROM    decoder prediction (where the step breakpoint goes)", hex(predicted[0]), hex(0x00020002))
    c.check("BUGFIX decoder prediction", hex(predicted[1]), hex(core_pc))
    c.finish()


if __name__ == "__main__":
    main()
