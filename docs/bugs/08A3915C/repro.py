#!/usr/bin/env python3
"""Behavioural case for func_08A3915C: the vertical clip of the OAM list
builder takes a piece's bottom edge from its x position.

    python3 docs/bugs/08A3915C/repro.py [path/to/baserom.bin]

Runs the ORIGINAL function bytes from your ROM and the -DBUGFIX build of
src/**/08A3915C.c under a Thumb emulator from the same memory states and
compares the OAM entries each one appends.  The last case also runs the
ROM's own screen test func_08A38EA0, with which the render tree's builder
skips objects that have nothing on the screen.  Exits 0 when every
assertion holds.

The function belongs to the code image that func_0808F74C copies from
[0x08A38ADC, 0x08A3991C) to IWRAM 0x03005F28; the case makes the same copy
and runs the original at its installed address 0x030065A8, the value of
callback slot 0x0839402C.  The image's last 64 bytes are the piece size
table the function reads at 0x03006D28.

Dependencies
  * Python 3.8+ and unicorn (`pip install unicorn`; tested with 2.1.4).
  * The repository toolchain, as tools/match.py runs it: cpp,
    $HOME/agbcc/gcc/agbcc (override with AGBCC) and arm-none-eabi-as
    (override with CPP / AS).
  * Your ROM: argv[1], default <repo root>/baserom.bin.  No ROM bytes ship
    with this file.  FFTA_ROOT overrides the repository root.

Stubs: none.  The function calls nothing.
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
ADDRESS, EXTENT = 0x08A3915C, 764
IMAGE_ROM, IMAGE_END, IMAGE_RAM = 0x08A38ADC, 0x08A3991C, 0x03005F28
INSTALLED = ADDRESS - IMAGE_ROM + IMAGE_RAM       # 0x030065A8
SCREEN_TEST = 0x08A38EA0 - IMAGE_ROM + IMAGE_RAM  # 0x030062EC, slot 0x08394028
SELECT, COUNTS, BUFFERS = 0x03000028, 0x03000020, 0x03000030
LIST, PRIORITY = 0x02000100, 0x02000200           # the case's own inputs
SQUARE, WIDE, TALL = 0, 1, 2                      # OAM shapes
SIZES = {(SQUARE, 0): (8, 8), (SQUARE, 3): (64, 64), (WIDE, 1): (32, 8),
         (WIDE, 3): (64, 32)}


def machine(rom, fixed_obj=None):
    m = Machine(rom)
    m.load(IMAGE_RAM, rom[IMAGE_ROM - ROM_BASE:IMAGE_END - ROM_BASE])
    entry = INSTALLED
    if fixed_obj is not None:
        entry = install_fixed(m, fixed_obj, {})
    return m, entry


def write_list(m, pieces):
    """Writes a piece list of (shape, size, piece_x, piece_y) at LIST."""
    m.w16(LIST, len(pieces))
    for k, (shape, size, px, py) in enumerate(pieces):
        m.w16(LIST + 2 + 6 * k, (py & 0xFF) | shape << 14)
        m.w16(LIST + 4 + 6 * k, (px & 0x1FF) | size << 14)
        m.w16(LIST + 6 + 6 * k, 0)
        m.w8(PRIORITY + k, 0)


def on_screen(m, pieces, x=0, y=0):
    """The ROM's func_08A38EA0 (run from the same IWRAM copy): 1 when one of
    the pieces placed at (x, y) touches the screen.  func_0808EFCC calls it
    through slot 0x08394028 (0x0808F0F6) and skips an object it returns 0
    for, so only objects it passes reach func_08A3915C."""
    write_list(m, pieces)
    return m.call(SCREEN_TEST, LIST, x, y, 0, 0)


def build(m, entry, pieces, x=0, y=0):
    """Runs the builder on a list of (shape, size, piece_x, piece_y) pieces
    placed at (x, y), into an empty buffer 0.  Returns the (x, y) of each
    entry it appended, as the OAM fields hold them (x 9 bits, y 8 bits)."""
    m.w8(SELECT, 0)
    m.w32(COUNTS, 0)
    for k in range(0, 0x400, 4):
        m.w32(BUFFERS + k, 0x00F800A8)            # hidden entries, as func_0800105C leaves them
    write_list(m, pieces)
    # (data, x, y, mode, mosaic, bpp, flip_x, flip_y, tile, priority, palette, limit)
    m.call(entry, LIST, x, y, 0, 0, 0, 0, 0, 0, PRIORITY, 0, 0)
    count = m.u32(COUNTS)
    return [(m.u16(BUFFERS + 8 * k + 2) & 0x1FF, m.u8(BUFFERS + 8 * k)) for k in range(count)]


def rows_on_screen(entry_y, height):
    """Screen rows an OAM entry covers; OAM y wraps at 256."""
    return [row % 256 for row in range(entry_y, entry_y + height) if row % 256 < 160]


def main():
    rom = load_rom()
    source, fixed_obj = build_pair(rom, ADDRESS, EXTENT)
    print(f"source {source.relative_to(ROOT)}: default build == ROM bytes "
          f"[{ADDRESS:08X}, {ADDRESS + EXTENT:08X})")
    original = machine(rom)
    fixed = machine(rom, fixed_obj)
    c = Checks()
    both = lambda pieces, **at: (build(*original, pieces, **at), build(*fixed, pieces, **at))

    print("\n1. Dropped although visible: a 32x8 piece at (-20, -4) covers rows 0..3")
    print("   and columns 0..11.  The ROM tests px + height = -12 < 0 and drops it.")
    got, want = both([(WIDE, 1, -20, -4)])
    c.check("ROM entries", got, [])
    c.check("BUGFIX entries (x, y)", want, [(-20 & 0x1FF, -4 & 0xFF)])
    got, want = both([(WIDE, 3, -40, -16)])
    c.check("64x32 at (-40, -16): ROM entries", got, [])
    c.check("64x32 at (-40, -16): BUGFIX entries", want, [(-40 & 0x1FF, -16 & 0xFF)])

    print("\n2. Kept although above the screen: an 8x8 piece at (100, -50).  The ROM")
    print("   tests px + height = 108 >= 0 and keeps it; the entry shows nothing")
    print("   (rows 206..213) but takes one of the 128 OAM entries.")
    got, want = both([(SQUARE, 0, 100, -50)])
    c.check("ROM entries (x, y)", got, [(100, 206)])
    c.check("ROM entry rows on screen", rows_on_screen(got[0][1], 8), [])
    c.check("BUGFIX entries", want, [])

    print("\n3. Kept although below the screen, and wrapped to the top: a 64x64")
    print("   piece at (10, 0) of a list placed at y = 200.  The ROM tests")
    print("   px + height = 74 <= 159 and keeps it; OAM y wraps at 256, so rows")
    print("   0..7 of the screen show the piece's last rows.")
    got, want = both([(SQUARE, 3, 10, 0)], y=200)
    c.check("ROM entries (x, y)", got, [(10, 200)])
    c.check("ROM entry rows on screen", rows_on_screen(got[0][1], 64), list(range(8)))
    c.check("BUGFIX entries", want, [])

    print("\n4. Non-triggers: both builds agree.")
    for label, pieces, y, expect in (
            ("on screen, 8x8 at (100, 50)", [(SQUARE, 0, 100, 50)], 0, [(100, 50)]),
            ("crossing the top edge at the right, 32x8 at (200, -4)",
             [(WIDE, 1, 200, -4)], 0, [(200, 252)]),
            ("crossing the top edge, 64x64 at (10, -56)", [(SQUARE, 3, 10, -56)], 0, [(10, 200)]),
            ("left of the screen, 8x8 at (-30, 50)", [(SQUARE, 0, -30, 50)], 0, []),
            ("above the screen at the left edge, 32x8 at (-20, -50)", [(WIDE, 1, -20, -50)], 0, []),
            ("below the screen at the right, 64x64 at (150, 170)", [(SQUARE, 3, 150, 0)], 170, [])):
        got, want = both(pieces, y=y)
        c.check(label + ": ROM == BUGFIX", (got, want), (expect, expect))

    print("\n5. Through the render tree's screen test: objects that straddle the")
    print("   bottom edge.  func_08A38EA0 adds the height to py and passes each")
    print("   object, because its first piece, 8x8 at (100, 150), is on screen;")
    print("   the ROM builder then also keeps the second piece, which is wholly")
    print("   below the screen: an 8x8 one at (100, 170) takes an entry and shows")
    print("   nothing, a 64x64 one at (10, 200) shows its last rows at the top.")
    for label, second, rows in (("8x8 at (100, 170)", (SQUARE, 0, 100, 70), 8),
                                ("64x64 at (10, 200)", (SQUARE, 3, 10, 100), 64)):
        pieces = [(SQUARE, 0, 100, 50), second]
        c.check(label + ": func_08A38EA0 (ROM)", on_screen(original[0], pieces, y=100), 1)
        got, want = both(pieces, y=100)
        c.check(label + ": ROM entries (x, y)", got, [(100, 150), (second[2], second[3] + 100)])
        c.check(label + ": rows of the second entry on screen",
                rows_on_screen(got[1][1], rows), [] if rows == 8 else list(range(8)))
        c.check(label + ": BUGFIX entries", want, [(100, 150)])
    c.finish()


if __name__ == "__main__":
    main()
