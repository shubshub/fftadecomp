#!/usr/bin/env python3
"""Behavioural case for func_0804E358: an empty list underflows the saved row.

    python3 docs/bugs/0804E358/repro.py [path/to/baserom.bin]

Runs the ORIGINAL function bytes from your ROM and the -DBUGFIX build of
src/**/0804E358.c under a Thumb emulator, from the same memory states, and
asserts the buggy and the corrected results.  It then runs the two ROM
consumers of the saved row with each result to show where the bad value goes.
Exits 0 when every assertion holds.

Dependencies
  * Python 3.8+ and unicorn (`pip install unicorn`; tested with 2.1.4).
  * The repository toolchain, as tools/match.py runs it: cpp,
    $HOME/agbcc/gcc/agbcc (override with AGBCC) and arm-none-eabi-as
    (override with CPP / AS).
  * Your ROM: argv[1], default <repo root>/baserom.bin.  No ROM bytes ship
    with this file.  FFTA_ROOT overrides the repository root.

Stubs (each callee entry is replaced by `bx lr` plus a Python behaviour):
  * func_08050E74 / func_08050E84 return the entry count of list 4 / list 5
    (in the game they count g_state_02002B08 and the 20 halfwords at
    0x02001F3C).
  * func_0814186C (BIOS CpuSet, svc 0x0B) only records its arguments; it is
    reached from func_0801799C in the impact part.
Everything else runs from the ROM: func_08017AF4, func_0801799C, the
__modsi3 at func_08142950 and func_08017FB0.
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

ADDRESS, EXTENT = 0x0804E358, 98
MENU_POINTER = 0x0201F548          # data_0201F548
MENU = EWRAM + 0x10000             # the menu data it points at
RECORDS = MENU + 0x53C             # SavedSelection selections[group]: {u16 top, u16 selected}
COUNT_4, COUNT_5 = 0x08050E74, 0x08050E84


def clamp(machine, entry, group, top, selected, count):
    """Runs one clamp; returns the saved (top, selected) afterwards."""
    machine.w32(MENU_POINTER, MENU)
    record = RECORDS + 4 * group
    machine.w16(record, top)
    machine.w16(record + 2, selected)
    machine.count = count
    machine.call(entry, group)
    return machine.u16(record), machine.u16(record + 2)


def machines(rom, fixed_obj):
    def count(m):
        m.set_reg(0, m.count)
    original = Machine(rom)
    original.stub(COUNT_4, count)
    original.stub(COUNT_5, count)
    fixed = Machine(rom)
    entry = install_fixed(fixed, fixed_obj, {"func_08050E74": count, "func_08050E84": count})
    return (original, ADDRESS), (fixed, entry)


# The consumers.  func_0804F948 restores a list's saved row when the list is
# shown: it passes the selected halfword's low byte to func_08017AF4 read as
# s8 (ldrsb at 0x0804FA46, bl at 0x0804FA4C) and to func_08017FB0 read as u8
# (ldrb at 0x0804FA9C, bl at 0x0804FAA0).  The top row goes to the menu's
# +0x1A (strh at 0x0804FA1A).
HIGHLIGHT, CURSOR_ROW = 0x08017AF4, 0x08017FB0
WINDOW = EWRAM + 0x20000           # the menu record func_0801799C reads
TILES = EWRAM + 0x21000            # its tile ring
MAP = EWRAM + 0x23000              # the map rows it copies into
LIST = EWRAM + 0x24000             # the list record func_08017FB0 writes
ROWS, WIDTH, MAP_STRIDE = 6, 12, 32


def consume(rom, low_byte):
    """Shows a list with saved row low_byte; returns the CpuSet destinations
    func_0801799C uses and the cursor fields func_08017FB0 stores."""
    m = Machine(rom)
    copies = []
    m.stub(0x0814186C, lambda m: copies.append((m.reg(0), m.reg(1), m.reg(2))))
    m.w32(WINDOW + 0x08, MAP)       # destination
    m.w32(WINDOW + 0x0C, TILES)     # tiles
    m.w16(WINDOW + 0x10, 0)         # flags: bit 0 clear, so the highlight is drawn
    m.w8(WINDOW + 0x15, WIDTH)      # row width in tiles
    m.w8(WINDOW + 0x17, ROWS)       # rows in the tile ring
    m.w16(WINDOW + 0x1A, 0)         # top row, restored from the record
    m.w8(WINDOW + 0x1E, MAP_STRIDE) # map row stride
    m.w8(WINDOW + 0x1F, 0)
    signed = low_byte - 0x100 if low_byte & 0x80 else low_byte
    m.call(HIGHLIGHT, WINDOW, signed, 11)
    m.call(CURSOR_ROW, LIST, low_byte)
    rows = [(dst - MAP) // 2 // MAP_STRIDE for _, dst, _ in copies]
    return rows, m.u8(LIST + 0x11), m.u16(LIST + 0x0E)


def main():
    rom = load_rom()
    source, fixed_obj = build_pair(rom, ADDRESS, EXTENT)
    print(f"source {source.relative_to(ROOT)}: default build == ROM bytes "
          f"[{ADDRESS:08X}, {ADDRESS + EXTENT:08X})")
    (original, rom_entry), (fixed, fixed_entry) = machines(rom, fixed_obj)
    c = Checks()

    print("\n1. Trigger: func_0804D840 removed the only entry of list 5.  The record")
    print("   holds the row the player picked it from, {top 0, selected 0}; the count")
    print("   is now 0.")
    got = clamp(original, rom_entry, 5, 0, 0, 0)
    c.check("ROM    {top, selected}", tuple(map(hex, got)), ("0x0", "0xffff"))
    want = clamp(fixed, fixed_entry, 5, 0, 0, 0)
    c.check("BUGFIX {top, selected}", tuple(map(hex, want)), ("0x0", "0x0"))

    print("\n   The same through func_0804D7E8, which removes the only entry of list 4:")
    c.check("ROM    {top, selected}", tuple(map(hex, clamp(original, rom_entry, 4, 0, 0, 0))),
            ("0x0", "0xffff"))
    c.check("BUGFIX {top, selected}", tuple(map(hex, clamp(fixed, fixed_entry, 4, 0, 0, 0))),
            ("0x0", "0x0"))

    print("\n2. Non-trigger: the last of three entries removed, cursor on it")
    print("   ({0, 2} with count 2): both step back to row 1.")
    c.check("ROM   ", clamp(original, rom_entry, 5, 0, 2, 2), (0, 1))
    c.check("BUGFIX", clamp(fixed, fixed_entry, 5, 0, 2, 2), (0, 1))

    print("\n3. Non-trigger: list 4 scrolled ({2, 3}) after its count fell to 7:")
    print("   both pull the page up one row and keep the cursor row.")
    c.check("ROM   ", clamp(original, rom_entry, 4, 2, 3, 7), (1, 3))
    c.check("BUGFIX", clamp(fixed, fixed_entry, 4, 2, 3, 7), (1, 3))

    print("\n4. Non-trigger: the list still fills the page ({0, 5} with count 9):")
    print("   neither changes the record.")
    c.check("ROM   ", clamp(original, rom_entry, 5, 0, 5, 9), (0, 5))
    c.check("BUGFIX", clamp(fixed, fixed_entry, 5, 0, 5, 9), (0, 5))

    print("\n5. Impact: the empty list is shown again from the category menu and")
    print("   func_0804F948 restores the saved row into the ROM consumers.")
    print(f"   (window: {ROWS}-row ring, {WIDTH} tiles wide, map stride {MAP_STRIDE} tiles)")
    print("   The highlight's CpuSet copies go to map rows (row << 1) and (row << 1) + 1,")
    print("   counted from the list's first map row; the ring size does not enter.")
    copies, row, y = consume(rom, got[1] & 0xFF)
    c.check("ROM    map rows written", copies, [-2, -1])
    c.check("ROM    list +0x11 / +0x0E (row, row << 4)", (row, hex(y)), (0xFF, "0xff0"))
    copies, row, y = consume(rom, want[1] & 0xFF)
    c.check("BUGFIX map rows written", copies, [0, 1])
    c.check("BUGFIX list +0x11 / +0x0E (row, row << 4)", (row, hex(y)), (0, "0x0"))
    c.finish()


if __name__ == "__main__":
    main()
