#!/usr/bin/env python3
"""Behavioural case for func_08148B60: a full path queue freezes the search.

    python3 docs/bugs/08148B60/repro.py [path/to/baserom.bin]

Writes a 16x16 grid into a PathState, seeds it at category 2 (the start
cell is queued next, then the search expands one queued cell per step), and
runs the ORIGINAL func_08148B60 from your ROM and the -DBUGFIX build of
src/**/08148B60.c under a Thumb emulator with no step limit (share -1).  On
the trigger grid the ROM's search never returns: 128 queue entries are
valid and the scan in requeue() looks for a cell that is not among them.
The BUGFIX build finishes, and every cell it gives a route walks back to the
start through the ROM's own reader, func_08148A0C.  On an open grid and on
seeded random terrain the two builds leave the same state, byte for byte.
Exits 0 when every assertion holds.

Dependencies
  * Python 3.8+ and unicorn (`pip install unicorn`; tested with 2.1.4).
  * The repository toolchain, as tools/match.py runs it: cpp,
    $HOME/agbcc/gcc/agbcc (override with AGBCC) and arm-none-eabi-as
    (override with CPP / AS).
  * Your ROM: argv[1], default <repo root>/baserom.bin.  No ROM bytes ship
    with this file.  FFTA_ROOT overrides the repository root.

Nothing is stubbed.  The grid is written directly, as func_081491C0 writes
a cell (cost mode 1, the only mode it sets), so categories 0 and 1, which
fill the grid through the caller's callback, do not run.  func_081443FC
(the memcpy the expansion calls) and func_08148A0C run from the ROM; the
BUGFIX build reaches func_081443FC and the call thunks through veneers.
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
import random

from unicorn import UC_HOOK_MEM_WRITE
from unicorn.arm_const import UC_ARM_REG_R7, UC_ARM_REG_R10

ADDRESS, EXTENT = 0x08148B60, 1488
STATE = EWRAM + 0x10000            # a PathState: 256 cells of 7 bytes, the queue at +0x700
QUEUE, HEAD, TAIL = STATE + 0x700, STATE + 0x988, STATE + 0x989
SIZE = 0x98A                       # func_0814913C's stride
WALK = 0x08148A0C                  # func_08148A0C(grid, NULL, x, y): route length, -1 if none
MEMCPY = 0x081443FC
THUNKS = {"_call_via_r2": 0x0814224C, "_call_via_r4": 0x08142254,
          "_call_via_r6": 0x0814225C}
SCAN = (0x08148FF0, 0x0814906E)    # the ROM's requeue() scan loop
_config_symbols = data_symbols


def data_symbols():
    """The harness's symbol table plus the call thunks, which agbcc emits
    for the callback calls and whose names carry no address."""
    return {**_config_symbols(), **THUNKS}


BUDGET = 5_000_000                 # instructions; a finished search takes well under 1,000,000

# The trigger, found by a search over grids that ran this ROM function.
# '.' no entry; '#' a cell; 'S' a cell with flag5 (no two-cell move starts
# there); 'U' a cell with flag4 (no move ends there; a two-cell move may pass
# over it); 'J' both flags.  Heights are the cells' 7-bit values.
TRIGGER_MAP = [
    "SUUJ.SS##..#.U##",
    "..#S.S#SJ.#S#.#.",
    ".S###S##U####S..",
    "#S######S##S###S",
    "S#S#S#S###S#S#SS",
    "#####S.S.#S.S.S.",
    "#S#S#S.S.S.##SS.",
    "S#S###S##S#.S###",
    "#SSS.S.#U.#SSS#S",
    "..SS##S#######S#",
    "J#S#SSS.S.#####S",
    ".#S#S##S#S##SSSS",
    "S####S#S#S###SSS",
    "#SS#S#SS######S.",
    "..S####SSSS##S..",
    "...#S.SS.##SS#US",
]
TRIGGER_HEIGHTS = [
     93,  11,  84,  80,  49,   8,  11,  65,  25,  36,   2,  42,   2,  46,  48,   7,
     59,  52,  45,  40,  54,  52,  59,  41,  31,  11,  65,  40,  47,  62,  40,   8,
     58,  41,  39,  42,  41,  48,  49,  55, 106,  43,  40,  43,  41,  42,   9,  73,
     45,  48,  45,  41,  58,  51,  60,  54,  13,  43,  43,  46,  47,  49,  43,  46,
     43,  44,  44,  46,  46,  55,  59,  58,  56,  48,  39,  48,  43,  45,  47,  45,
     47,  44,  47,  48,  52,  52,  62,  54, 100,  48,  41, 108,  54,  12,  49,  67,
     49,  41,  43,  41,  43,  49, 102,  55,  65,  49,  72,  55,  52,  51,  52,  36,
     40,  44,  42,  45,  55,  51,  48,  50,  48,  52,  53,  40,  53,  57,  45,  55,
     37,  44,  51,  47,  74,  67,  48,  51,  74,  93,  54,  58,  57,  50,  46,  50,
     36,  51,  41,  44,  46,  54,  50,  51,  52,  52,  48,  38,  21,  44,  44,  43,
     46,  49,  39,  42,  40,  49,  50, 127,  64, 105,  50,  35,  47,  37,  46,  45,
    114,  46,  43,  46,  49,  51,   6,  41,  47,  49,  54,  39,  43,  39,  39,  42,
     46,  44,  50,  43,  54,  51,  47,  45,  44,  45,  44,  47,  46,  49,  46,  47,
     22,  43,  41,  44,  47,  41,  44,  53,  51,  49,  53,  41,  43,  44,  45,  39,
     57,  72,  53,  40,  53,  54,  45,  44,  54,  51,  45,  41,  45,  42,   9,  40,
     67,  40,  85,  44,  51,  39,  43,  48,  29,  57,  53,  56,  41,  58,  33,  24,
]
FLAGS = {".": (0, 0, 0), "#": (1, 0, 0), "S": (1, 0, 1), "U": (1, 1, 0), "J": (1, 1, 1)}


def grid(rows, heights):
    """256 cells (value, enabled, flag4, flag5), row by row."""
    return [(heights[16 * y + x],) + FLAGS[rows[y][x]] for y in range(16) for x in range(16)]


def random_terrain(rng):
    """Rolling heights, a few holes and a few flag5 cells."""
    heights, rows = [], []
    for y in range(16):
        row = ""
        for x in range(16):
            base = heights[-1] if x else 50
            if y:
                base = (base + heights[-16]) // 2
            heights.append(max(0, min(127, base + rng.randint(-2, 2))))
            row += "." if rng.random() < 0.08 else "S" if rng.random() < 0.1 else "#"
        rows.append(row)
    return grid(rows, heights)


def seed(m, cells, start, climb, drop):
    """A PathState at category 2 (active), no cost limit (max_cost 0xFF)."""
    state = bytearray(SIZE)
    for k, (value, enabled, flag4, flag5) in enumerate(cells):
        state[7 * k] = value | enabled << 7
        state[7 * k + 1] = 1 | flag4 << 4 | flag5 << 5      # cost mode 1
    state[0x980] = 0x82
    state[0x981], state[0x982], state[0x983] = climb & 0xFF, drop & 0xFF, 0xFF
    state[0x986], state[0x987] = start
    m.load(STATE, bytes(state))


def watch(m):
    """Peak count of valid queue entries, from the head and tail stores."""
    m.front, m.peak = 0, 1
    def store(uc, access, address, size, value, _):
        if address == HEAD:
            m.front = uc.mem_read(HEAD, 1)[0]
        else:
            m.peak = max(m.peak, (value - m.front) % 128 or 128)
    m.uc.hook_add(UC_HOOK_MEM_WRITE, store, begin=HEAD, end=TAIL)


def search(m, entry, cells, start, climb=4, drop=-4):
    """Runs the search to the end; returns (returned, pc)."""
    seed(m, cells, start, climb, drop)
    m.front, m.peak = 0, 1
    for k, value in enumerate((STATE, 0, 0xFF, 0)):           # share -1: no step limit
        m.set_reg(k, value)
    m.uc.reg_write(UC_ARM_REG_SP, STACK_TOP - 0x40)
    m.uc.reg_write(UC_ARM_REG_LR, RETURN | 1)
    m.uc.emu_start(entry | 1, RETURN, count=BUDGET)
    pc = m.uc.reg_read(UC_ARM_REG_PC) & ~1
    return pc == RETURN, pc


def queued(m):
    entries = [bytes(m.uc.mem_read(QUEUE + 5 * k, 5)) for k in range(128)]
    return [(e[3] & 0x7F, e[4]) for e in entries if e[0] & 0x80]


def routes(m):
    """func_08148A0C's route length for every cell the search reached."""
    lengths = {}
    for y in range(16):
        for x in range(16):
            if m.u8(STATE + 7 * (16 * y + x) + 2) & 0x80:
                n = m.call(WALK, STATE, 0, x, y)
                lengths[(x, y)] = n - (1 << 32) if n & 0x80000000 else n
    return lengths


def main():
    rom = load_rom()
    source, fixed_obj = build_pair(rom, ADDRESS, EXTENT)
    print(f"default build of {source.relative_to(ROOT)} reproduces the ROM bytes")
    original = Machine(rom)
    fixed = Machine(rom)
    entry = install_fixed(fixed, fixed_obj, {"func_081443FC": MEMCPY, **THUNKS})
    for m in (original, fixed):
        watch(m)
    c = Checks()
    trigger = grid(TRIGGER_MAP, TRIGGER_HEIGHTS)

    print("\n1. Trigger, ROM: start (7, 7), climb 4, drop -4, on this grid (TRIGGER_MAP):")
    for row in TRIGGER_MAP:
        print("     " + row)
    returned, pc = search(original, ADDRESS, trigger, (7, 7))
    c.check("the search returns", returned, False)
    c.check("it is in requeue()'s scan", SCAN[0] <= pc < SCAN[1], True)
    entries = queued(original)
    c.check("valid queue entries (of 128)", len(entries), 128)
    sought = (original.uc.reg_read(UC_ARM_REG_R10) & 0x7F, original.uc.reg_read(UC_ARM_REG_R7) & 0xFF)
    print(f"  the scan looks for cell {sought}")
    c.check("that cell is queued", sought in entries, False)
    again = sum(original.u8(STATE + 7 * (16 * y + x) + 2) >> 7 for x, y in entries)
    costs = sorted(original.u8(QUEUE + 5 * k + 2) for k in range(128))
    print(f"  {again} of them are cells expanded before (the node being expanded among them);")
    print(f"  the costs of the 128 run from {costs[0]} to {costs[-1]}")
    before = bytes(original.uc.mem_read(STATE, SIZE))
    original.uc.emu_start(pc | 1, RETURN, count=1_000_000)
    pc = original.uc.reg_read(UC_ARM_REG_PC) & ~1
    c.check("a million instructions later: still in the scan, state unchanged",
            SCAN[0] <= pc < SCAN[1] and bytes(original.uc.mem_read(STATE, SIZE)) == before, True)

    print("\n2. Trigger, BUGFIX build: the same state.")
    returned, _ = search(fixed, entry, trigger, (7, 7))
    c.check("the search returns", returned, True)
    c.check("category (4 = done)", fixed.u8(STATE + 0x980) & 0x7F, 4)
    c.check("result (0 = done)", fixed.reg(0), 0)
    c.check("peak valid queue entries", fixed.peak, 128)
    c.check("valid queue entries at the end", len(queued(fixed)), 0)
    lengths = routes(fixed)
    print(f"  {len(lengths)} cells have a route")
    c.check("cells whose route does not walk back to the start", [k for k, n in lengths.items() if n < 1], [])

    print("\n3. Non-trigger: an open flat grid, every start.  Both builds leave the")
    print("   same state; the queue never holds more than 32 entries.")
    flat = [(0, 1, 0, 0)] * 256
    same, peak = 0, 0
    for start in ((x, y) for y in range(16) for x in range(16)):
        a, b = search(original, ADDRESS, flat, start)[0], search(fixed, entry, flat, start)[0]
        same += a and b and original.uc.mem_read(STATE, SIZE) == fixed.uc.mem_read(STATE, SIZE)
        peak = max(peak, original.peak)
    c.check("starts where both return the same state", same, 256)
    c.check("peak valid queue entries", peak, 32)

    print("\n4. Non-trigger: 100 seeded random terrains, random starts and limits.")
    rng = random.Random(0x08148B60)
    same, peak = 0, 0
    for _ in range(100):
        cells = random_terrain(rng)
        start = (rng.randrange(16), rng.randrange(16))
        climb, drop = rng.choice([1, 2, 4, 34]), -rng.choice([1, 2, 4, 34])
        a = search(original, ADDRESS, cells, start, climb, drop)[0]
        b = search(fixed, entry, cells, start, climb, drop)[0]
        same += a and b and original.uc.mem_read(STATE, SIZE) == fixed.uc.mem_read(STATE, SIZE)
        peak = max(peak, original.peak)
    c.check("terrains where both return the same state", same, 100)
    print(f"  peak valid queue entries over the 100: {peak}")
    c.finish()


if __name__ == "__main__":
    main()
