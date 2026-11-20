#!/usr/bin/env python3
"""Behavioural case for func_08FE18F0 (the Thumb single step of the
development-cartridge debug monitor): MOV PC, PC is predicted to go to its
own address, so the step never gets past it.

    python3 docs/bugs/08FE18F0/repro.py [path/to/baserom.bin]

Runs the ORIGINAL function bytes from your ROM and the -DBUGFIX build of
src/**/08FE18F0.c under a Thumb emulator from the same saved-register
states, compares both with what a Thumb core does (unicorn running the
instruction), then runs the ROM's single step func_08FE1EC8 with each build
and lets the CPU resume until it reaches the planted breakpoint.  Exits 0
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
functions run from there.  No callee is stubbed: func_08FE18F0 calls the
ROM's func_08FE1810 (condition test), and func_08FE1EC8 the ROM's
func_08FE176C (plants the breakpoint).
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
from unicorn.arm_const import (UC_ARM_REG_R4, UC_ARM_REG_R5, UC_ARM_REG_R6, UC_ARM_REG_R7,
                               UC_ARM_REG_R8, UC_ARM_REG_R9, UC_ARM_REG_R10, UC_ARM_REG_R11,
                               UC_ARM_REG_R12, UC_ARM_REG_CPSR)

ADDRESS, EXTENT = 0x08FE18F0, 530
IMAGE, IMAGE_SIZE = 0x08FE0000, 0x4000   # the debug monitor's memory image in the ROM
LINK = 0x01002000                        # it runs at its ROM address + LINK
REGS_AT = 0x09FE2100                     # saved r0-r15, CPSR (16), banked SP/LR/SPSR (17-25)
CPSR_AT = REGS_AT + 4 * 16
SAVED_INSN, STEP_AT = 0x09FE20E8, 0x09FE20EC   # what func_08FE176C saves and where it planted
STEP = 0x08FE1EC8                        # func_08FE1EC8: the single step (decode + plant)
CONDITION = 0x08FE1810                   # func_08FE1810(cond): the condition test
BREAKPOINT = 0xEFFF                      # the monitor's Thumb breakpoint (func_08FE176C)
INSN_AT = EWRAM + 0x100                  # where the stepped instruction sits
NOP = 0x46C0
SYS_THUMB, IRQ_THUMB = 0x3F, 0x32        # CPSR values: mode | T
ALL_REGS = REGS + (UC_ARM_REG_R4, UC_ARM_REG_R5, UC_ARM_REG_R6, UC_ARM_REG_R7, UC_ARM_REG_R8,
                   UC_ARM_REG_R9, UC_ARM_REG_R10, UC_ARM_REG_R11, UC_ARM_REG_R12,
                   UC_ARM_REG_SP, UC_ARM_REG_LR)


def veneer_at(m, address, target):
    """The harness veneer (ldr r0, =target; mov ip, r0; bx ip), written over a ROM function."""
    m.uc.mem_write(address, struct.pack("<6HI", 0xB401, 0x4802, 0x4684, 0xBC01,
                                        0x4760, 0x46C0, target | 1))


def machine(rom, fixed_obj=None):
    """The ROM, plus the monitor image mapped at its run address: its jump
    tables hold run addresses and its saved-register block lies inside it."""
    m = Machine(rom)
    m.uc.mem_map(IMAGE + LINK, IMAGE_SIZE)
    m.uc.mem_write(IMAGE + LINK, rom[IMAGE - ROM_BASE:][:IMAGE_SIZE])
    entry = ADDRESS + LINK
    if fixed_obj is not None:
        entry = install_fixed(m, fixed_obj, {"func_08FE1810": CONDITION + LINK})
        # func_08FE1EC8's BL (0x08FE1EE0) reaches the run copy of
        # func_08FE18F0: send it to the BUGFIX build.
        veneer_at(m, ADDRESS + LINK, entry)
    return m, entry


def stop_cpu(m, code, regs, cpsr):
    """Places the Thumb code at INSN_AT and fills the saved-register block as
    the monitor leaves it for a CPU stopped there."""
    for k, half in enumerate(code):
        m.w16(INSN_AT + 2 * k, half)
    for k in range(26):
        m.w32(REGS_AT + 4 * k, 0)
    for k, value in regs.items():
        m.w32(REGS_AT + 4 * k, value)
    m.w32(REGS_AT + 4 * 15, INSN_AT)
    m.w32(CPSR_AT, cpsr)


def core_next(code, regs):
    """What a Thumb core does: runs the first instruction (unicorn) and returns
    the next PC and whether the core is now in ARM state."""
    uc = Uc(UC_ARCH_ARM, UC_MODE_THUMB)
    uc.mem_map(EWRAM, 0x40000)
    uc.mem_write(INSN_AT, b"".join(struct.pack("<H", h) for h in code))
    for k, reg in enumerate(ALL_REGS):
        uc.reg_write(reg, regs.get(k, 0))
    uc.emu_start(INSN_AT | 1, 0, count=1)
    return uc.reg_read(UC_ARM_REG_PC), not uc.reg_read(UC_ARM_REG_CPSR) & 0x20


def resume(m, limit=8):
    """Lets the stopped CPU run from INSN_AT until it reaches a halfword the
    monitor planted (its breakpoint traps there).  Returns (stop address,
    instructions executed before it)."""
    executed, stop = [], []
    def hook(uc, address, size, _):
        if m.u16(address) == BREAKPOINT:
            stop.append(address)
            uc.emu_stop()
        else:
            executed.append(address)
    handle = m.uc.hook_add(UC_HOOK_CODE, hook, begin=EWRAM, end=EWRAM + 0x3FFFF)
    m.uc.emu_start(INSN_AT | 1, 0, count=limit)
    m.uc.hook_del(handle)
    if not stop:
        sys.exit("the resumed CPU never reached the planted breakpoint")
    return stop[0], len(executed)


def main():
    rom = load_rom()
    source, fixed_obj = build_pair(rom, ADDRESS, EXTENT)
    print(f"source {source.relative_to(ROOT)}: default build == ROM bytes "
          f"[{ADDRESS:08X}, {ADDRESS + EXTENT:08X})")
    original, fixed = machine(rom), machine(rom, fixed_obj)
    c = Checks()
    out = STACK_TOP - 0x80

    def both(code, regs, cpsr=SYS_THUMB):
        results = []
        for m, entry in (original, fixed):
            stop_cpu(m, code, regs, cpsr)
            m.w32(out, 0xFFFFFFFF)
            results.append((m.call(entry, INSN_AT, out), m.u32(out)))
        return results

    print(f"\n1. Trigger: `mov pc, pc` (0x46FF) at {INSN_AT:#x}.  The core reads PC")
    print("   as the address + 4.")
    (rom_pc, _), (fixed_pc, _) = both([0x46FF, NOP, NOP, NOP], {})
    core_pc, _ = core_next([0x46FF, NOP], {15: INSN_AT})
    c.check("Thumb core next PC", hex(core_pc), hex(INSN_AT + 4))
    c.check("ROM    prediction (the MOV itself)", hex(rom_pc), hex(INSN_AT))
    c.check("BUGFIX prediction", hex(fixed_pc), hex(core_pc))

    print("\n2. Impact: the ROM's single step func_08FE1EC8 plants its breakpoint,")
    print("   then the CPU resumes until it reaches it.")
    for name, (m, _), planted, saved, executed in (("ROM   ", original, INSN_AT, 0x46FF, 0),
                                                   ("BUGFIX", fixed, INSN_AT + 4, NOP, 1)):
        stop_cpu(m, [0x46FF, NOP, NOP, NOP], {}, SYS_THUMB)
        m.call(STEP + LINK)
        c.check(f"{name} breakpoint address (0x09FE20EC)", hex(m.u32(STEP_AT)), hex(planted))
        c.check(f"{name} halfword saved from under it (0x09FE20E8)", hex(m.u32(SAVED_INSN)), hex(saved))
        c.check(f"{name} halfword at the MOV now", hex(m.u16(INSN_AT)),
                hex(BREAKPOINT if planted == INSN_AT else 0x46FF))
        stop, count = resume(m)
        c.check(f"{name} resumed CPU stops at, instructions executed first",
                (hex(stop), count), (hex(planted), executed))
    print("   ROM: the breakpoint replaces the MOV, so the CPU traps before")
    print("   executing it and the step ends where it began.  BUGFIX: the MOV")
    print("   runs and the step stops after it.")

    print("\n3. Non-trigger: `mov pc, r3` (0x469F), r3 = 0x02000201.")
    (a, _), (b, _) = both([0x469F, NOP], {3: 0x02000201})
    core_pc, _ = core_next([0x469F, NOP], {3: 0x02000201, 15: INSN_AT})
    c.check("ROM, BUGFIX (bit 0 kept; func_08FE176C clears it)", (hex(a), hex(b)), (hex(0x02000201),) * 2)
    c.check("Thumb core next PC", hex(core_pc), hex(0x02000200))

    print("\n4. Non-trigger: `mov pc, lr` (0x46F7) in IRQ mode: LR from the IRQ bank (18).")
    (a, _), (b, _) = both([0x46F7, NOP], {14: 0x08000111, 18: 0x02000301}, IRQ_THUMB)
    c.check("ROM, BUGFIX", (hex(a), hex(b)), (hex(0x02000301),) * 2)

    print("\n5. Non-trigger: `bx pc` (0x4778), the BX path's own + 4.")
    results = both([0x4778, NOP, NOP, NOP], {})
    core_pc, core_arm = core_next([0x4778, NOP], {15: INSN_AT})
    c.check("ROM    (next PC, ARM flag)", (hex(results[0][0]), results[0][1]), (hex(INSN_AT + 4), 1))
    c.check("BUGFIX (next PC, ARM flag)", (hex(results[1][0]), results[1][1]), (hex(INSN_AT + 4), 1))
    c.check("Thumb core (next PC, ARM state)", (hex(core_pc), core_arm), (hex(INSN_AT + 4), True))

    print("\n6. Non-trigger: `b` forward (0xE002) and `pop {r0, pc}` (0xBD01).")
    (a, _), (b, _) = both([0xE002, NOP], {})
    c.check("b:   ROM, BUGFIX", (hex(a), hex(b)), (hex(INSN_AT + 8),) * 2)
    stack = IWRAM + 0x7E00
    for m, _ in (original, fixed):
        m.w32(stack, 0x11111111)
        m.w32(stack + 4, 0x02000401)
    (a, _), (b, _) = both([0xBD01, NOP], {13: stack})
    c.check("pop: ROM, BUGFIX", (hex(a), hex(b)), (hex(0x02000401),) * 2)
    c.finish()


if __name__ == "__main__":
    main()
