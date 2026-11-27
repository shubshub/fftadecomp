#!/usr/bin/env python3
"""Behavioural case for func_0809D128: a fourteenth movement uses a NULL slot.

    python3 docs/bugs/0809D128/repro.py [path/to/baserom.bin]

Runs the ORIGINAL function bytes from your ROM and the -DBUGFIX build of
src/**/0809D128.c under a Thumb emulator, from the same memory states, and
asserts what each does when all thirteen movement slots are in use: the ROM
stores into BIOS space through the NULL slot and starts the movement through
the word it reads back from 0x00000004, while the BUGFIX build returns and
leaves memory untouched.  With a free slot both fill it identically.  Exits 0
when every assertion holds.

Dependencies
  * Python 3.8+ and unicorn (`pip install unicorn`; tested with 2.1.4).
  * The repository toolchain, as tools/match.py runs it: cpp,
    $HOME/agbcc/gcc/agbcc (override with AGBCC) and arm-none-eabi-as
    (override with CPP / AS).
  * Your ROM: argv[1], default <repo root>/baserom.bin.  No ROM bytes ship
    with this file.  FFTA_ROOT overrides the repository root.

The BIOS page 0x00000000-0x00003FFF is modelled as the hardware has it for
code running from ROM: every read returns one open-bus word (the last BIOS
opcode fetched; the case uses 0xE3A02004) and writes are dropped.  Any access
outside the mapped GBA memory stops the run and is reported.

Stubs (each entry is replaced by `bx lr` plus a Python behaviour):
  * func_08022840 (heap allocator): bump blocks, pre-filled with 0xEE.
  * g_callbacks_0836D4B8[0] (IWRAM 0x03005E78): zero-fills (dst, size).
  * g_callbacks_0836D4B8[1] = data_0836D4BC[0] (IWRAM 0x03005EE8): copies
    (dst, src, size).  Both drop stores into the BIOS page, as the bus does.
  * func_0809A53C returns 1; func_0809836C and func_0809A570 do nothing;
    func_0809B014 returns 0; func_08148A98 returns the count;
    func_08099644 returns 0 (only reached on paths this case does not take).
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
from unicorn import UC_HOOK_MEM_READ, UC_HOOK_MEM_WRITE, UC_HOOK_MEM_UNMAPPED

ADDRESS, EXTENT = 0x0809D128, 464
BIOS, BIOS_SIZE, OPEN_BUS = 0x00000000, 0x4000, 0xE3A02004
FILL, COPY = 0x03005E78, 0x03005EE8          # g_callbacks_0836D4B8[0], [1]
ALLOC = 0x08022840
MANAGER = EWRAM + 0x10000                    # MovementSlots: flags at +4, 13 slots of 0xB4 from +8
SLOT, SLOTS, SLOT_SIZE = 8, 13, 0xB4
OBJECT, DATA, OWNER = EWRAM + 0x18000, EWRAM + 0x18100, EWRAM + 0x18300
ROUTE = EWRAM + 0x18400                      # the caller's route: count x {s8 x, s8 z, u8 height, u8}
HEAP = EWRAM + 0x20000
COUNT = 5
# agbcc's call thunks, bx rN at 0x08142244 + 4N, for the two callback calls
THUNKS = {f"_call_via_r{n}": 0x08142244 + 4 * n for n in range(8)}
_config_symbols = data_symbols


def data_symbols():
    """The harness's symbol table plus the call thunks, whose names carry no address."""
    return {**_config_symbols(), **THUNKS}


STUBS = {"func_0809A53C": lambda m: m.set_reg(0, 1), "func_0809836C": lambda m: None,
         "func_0809A570": lambda m: None, "func_0809B014": lambda m: m.set_reg(0, 0),
         "func_08148A98": lambda m: m.set_reg(0, m.reg(1)), "func_08099644": lambda m: m.set_reg(0, 0)}


def in_bios(address):
    return BIOS <= address < BIOS + BIOS_SIZE


def prepare(m):
    m.heap, m.bios, m.dropped, m.unmapped = HEAP, [], [], []
    m.uc.mem_write(HEAP, b"\xEE" * 0x4000)
    m.uc.mem_map(BIOS, BIOS_SIZE)
    image = struct.pack("<I", OPEN_BUS) * (BIOS_SIZE // 4)
    m.uc.mem_write(BIOS, image)
    m.dirty = False

    def read(uc, access, address, size, value, _):
        m.bios.append(("read", address, size))

    def write(uc, access, address, size, value, _):
        m.bios.append(("write", address, size))
        m.dirty = True

    def restore(uc, address, size, _):
        if m.dirty:                          # the write has happened by now: undo it
            uc.mem_write(BIOS, image)
            m.dirty = False

    def unmapped(uc, access, address, size, value, _):
        m.unmapped.append((hex(uc.reg_read(UC_ARM_REG_PC)), hex(address)))
        return False

    m.uc.hook_add(UC_HOOK_MEM_READ, read, begin=BIOS, end=BIOS + BIOS_SIZE - 1)
    m.uc.hook_add(UC_HOOK_MEM_WRITE, write, begin=BIOS, end=BIOS + BIOS_SIZE - 1)
    m.uc.hook_add(UC_HOOK_CODE, restore, begin=1, end=0)
    m.uc.hook_add(UC_HOOK_MEM_UNMAPPED, unmapped)

    def alloc(m):
        size = m.reg(0)
        block = m.heap
        m.heap = (block + size + 3) & ~3
        m.set_reg(0, block)

    def store(m, dst, data):
        for k, byte in enumerate(data):
            if in_bios(dst + k):
                m.dropped.append(dst + k)
            else:
                m.uc.mem_write(dst + k, bytes([byte]))

    m.stub(ALLOC, alloc)
    m.stub(FILL, lambda m: store(m, m.reg(0), bytes(m.reg(1))))
    m.stub(COPY, lambda m: store(m, m.reg(0), bytes(m.uc.mem_read(m.reg(1), m.reg(2)))))
    # the object being moved: movement_type 0 (not 2), so no path search
    m.w32(OBJECT, DATA)
    m.w8(OBJECT + 0x1F, 3)                   # direction
    m.w32(OBJECT + 0x80, OWNER)
    for k in range(COUNT):
        m.uc.mem_write(ROUTE + 4 * k, bytes([k, 2 * k, 1, 0]))


def machines(rom, fixed_obj):
    original = Machine(rom)
    prepare(original)
    for name, behaviour in STUBS.items():
        original.stub(address_of(name, {}), behaviour)
    fixed = Machine(rom)
    prepare(fixed)
    used = {name for _, _, name, _ in fixed_obj[1]}
    entry = install_fixed(fixed, fixed_obj, {**STUBS, "func_08022840": ALLOC,
                                             **{n: a for n, a in THUNKS.items() if n in used}})
    return (original, ADDRESS), (fixed, entry)


def fill(m, free):
    """Slots in use except those in `free`; each used slot keeps its own state."""
    m.uc.mem_write(MANAGER, bytes(8 + SLOTS * SLOT_SIZE))
    for k in range(SLOTS):
        if k not in free:
            m.w32(MANAGER + SLOT + SLOT_SIZE * k, 0x02030000 + 0x100 * k)      # another object
            m.w32(MANAGER + SLOT + SLOT_SIZE * k + 4, 0x02031000 + 0x100 * k)  # its movement


def start(m, entry):
    m.bios, m.dropped, m.unmapped = [], [], []
    try:
        m.call(entry, MANAGER, OBJECT, ROUTE, COUNT)
        returned = True
    except UcError:
        returned = False
    return returned


def snapshot(m):
    return bytes(m.uc.mem_read(MANAGER, 8 + SLOTS * SLOT_SIZE)), bytes(m.uc.mem_read(HEAP, 0x400))


def main():
    rom = load_rom()
    source, fixed_obj = build_pair(rom, ADDRESS, EXTENT)
    print(f"source {source.relative_to(ROOT)}: default build == ROM bytes "
          f"[{ADDRESS:08X}, {ADDRESS + EXTENT:08X})")
    c = Checks()

    print("\n1. Trigger: all thirteen slots are in use and a fourteenth movement starts.")
    (original, rom_entry), (fixed, fixed_entry) = machines(rom, fixed_obj)
    for m in (original, fixed):
        fill(m, ())
    before = snapshot(original)
    returned = start(original, rom_entry)
    print(f"   ROM BIOS accesses: {original.bios[:6]}{' ...' if len(original.bios) > 6 else ''}")
    c.check("ROM    stores slot->object to 0x00000000 (0x0809D158)", ("write", 0, 4) in original.bios, True)
    c.check("ROM    reads slot->movement from 0x00000004", ("read", 4, 4) in original.bios, True)
    c.check("ROM    stores the route copy and the status clear into BIOS space",
            (min(original.dropped), max(original.dropped)) if original.dropped else None, (0x08, 0x6C + 0x48 - 1))
    c.check("ROM    manager flags bit 0 set", original.u8(MANAGER + 4) & 1, 1)
    print(f"   ROM run stopped at {original.unmapped[:1]}: the movement state pointer is the word read")
    print(f"   from 0x00000004 ({OPEN_BUS:#010x}), and start_movement stores through it.")
    c.check("ROM    reaches its own return", returned, False)
    c.check("ROM    first access outside GBA memory is inside the open-bus 'state'",
            bool(original.unmapped) and OPEN_BUS <= int(original.unmapped[0][1], 16) < OPEN_BUS + 0xE4, True)
    returned = start(fixed, fixed_entry)
    c.check("BUGFIX reaches its own return", returned, True)
    c.check("BUGFIX BIOS accesses", fixed.bios, [])
    c.check("BUGFIX accesses outside GBA memory", fixed.unmapped, [])
    c.check("BUGFIX manager and heap unchanged", snapshot(fixed) == before, True)

    for free in ((12,), (3, 7)):
        first = free[0]
        print(f"\n{2 if free == (12,) else 3}. Non-trigger: slot(s) {', '.join(map(str, free))} free: "
              f"both use slot {first}.")
        (original, rom_entry), (fixed, fixed_entry) = machines(rom, fixed_obj)
        for m in (original, fixed):
            fill(m, free)
        c.check("ROM    returns", start(original, rom_entry), True)
        c.check("BUGFIX returns", start(fixed, fixed_entry), True)
        for m, label in ((original, "ROM   "), (fixed, "BUGFIX")):
            slot = MANAGER + SLOT + SLOT_SIZE * first
            c.check(f"{label} slot {first}: object, active, count, BIOS accesses",
                    (hex(m.u32(slot)), m.u16(slot + 0x6C), m.u8(slot + 0x68), m.bios),
                    (hex(OBJECT), 1, COUNT, []))
        c.check("manager, slots and the new movement state identical in both",
                snapshot(original) == snapshot(fixed), True)
    c.finish()


if __name__ == "__main__":
    main()
