#!/usr/bin/env python3
"""Behavioural case for func_081104DC: phase 0x102 steps its counter before
it indexes the 60-entry scale tables of its 11 rotating objects, so the
60th pass, the one that unlinks them, reads entry 60 of every table it
uses, one past the end.  The -DBUGFIX build makes no lookup on that pass.

    python3 docs/bugs/081104DC/repro.py [path/to/baserom.bin]

Runs the ORIGINAL function bytes from your ROM and the -DBUGFIX build of
src/**/081104DC.c under a Thumb emulator, pass for pass, the way the game
runs this task.  The task is created as func_08005954 creates it: its
memory is cleared by the ROM's own zero fill (g_callbacks_0836D4B8[0]) and
the callback runs phase 0 at once.  Each later pass is what func_080D36B0
does in its state 1: the task runner (func_08005A24, one call with the
task's stored phase), then the object update (func_08010DD0) and the object
draw walk (func_080D3024).  The run goes through phases 0x100 and 0x101,
the 60 passes of phase 0x102 and the pass of phase 0x103.  Exits 0 when
every assertion holds.

Dependencies
  * Python 3.8+ and unicorn (`pip install unicorn`; tested with 2.1.4).
  * The repository toolchain, as tools/match.py runs it: cpp,
    $HOME/agbcc/gcc/agbcc (override with AGBCC) and arm-none-eabi-as
    (override with CPP / AS).
  * Your ROM: argv[1], default <repo root>/baserom.bin.  No ROM bytes ship
    with this file.  FFTA_ROOT overrides the repository root.

Stubs (each callee entry is replaced by `bx lr` plus a Python behaviour):
  * func_080018A0 (draw a scaled, rotated sprite) and func_08001F34 (draw a
    plain sprite) only record what the draw walk passes them.
  * The callees of phases 0, 0x101 and 0x103 that set up the screen or
    start and end other tasks: func_080D3AF8 and func_08000B20 (the map
    fill), func_080D7220, func_08003620 and func_0801DB3C, func_080D3EC0,
    func_080DFD8C and func_080D4704 (each returns a task that is not run),
    func_080D47DC, and func_080D4774 and func_080D3F08 (each reports its
    task ended).  The case asserts that each is reached only in its own
    phase.
Everything else runs from the ROM, including the two routines the game
copies to IWRAM: the case copies the same 176 bytes from 0x08A38A2C to
0x03005E78, as the installer func_08002768 does, so the zero fill and the
copy routine the object allocator uses (data_0836D4BC[0]) are the ROM's.
The rest: the object creator func_080D5CC0 with its allocator, the setters
func_08011100, func_080110F8, func_080112E8 and func_080112CC, the
interpolator func_080E0608 / func_080E064C / func_080E0690, func_080107D4,
func_080035D0, func_080035A8, the unlink func_08011428, and per pass
func_08010DD0 and func_080D3024 with their callees.

The table entries are not shipped: the case checks your ROM's seven tables
against their closed form, and takes the expected values from the ROM.

The case fails if any of these stops being true: the ROM bytes read entry
60 of every table they use on the pass that unlinks the objects; the
BUGFIX build reads nothing on that pass; and the draw walk hands the sprite
routines the same values in both builds, on every pass.
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
from collections import Counter
from fractions import Fraction
from unicorn import UC_HOOK_MEM_READ, UC_HOOK_MEM_WRITE

ADDRESS, EXTENT = 0x081104DC, 940
DEFINITIONS, ROTATING, MOVING = 0x083A2FD8, 11, 14  # data_083A2FD8: 11 rows of 20 bytes
TABLES, TABLE_COUNT, ENTRIES = 0x083A39D8, 7, 60   # seven tables of 60 s16, back to back
TABLE_BYTES = 2 * ENTRIES
TABLES_END = TABLES + TABLE_COUNT * TABLE_BYTES    # 0x083A3D20: data_083A3D20 (src/0811584C.c)
LOOKUPS = {0x08110770: "x", 0x08110784: "y"}       # ldrh r1, [r0] / ldrh r2, [r0]
COUNTER_STORE = 0x08110716                         # strh r0, [r3]: payload->counter++
SET_SCALE = 0x080112CC             # func_080112CC(object, x scale, y scale, angle): three strh
UNLINK = 0x08011428
CREATE_OBJECT = 0x080D5CC0
UPDATE_OBJECTS = 0x08010DD0
DRAW_WALK = 0x080D3024
DRAW_SCALED, DRAW_PLAIN = 0x080018A0, 0x08001F34
IWRAM_IMAGE, IWRAM_CODE, IWRAM_BYTES = 0x08A38A2C, 0x03005E78, 176   # 88 halfwords
ZERO_FILL = 0x0836D4B8             # g_callbacks_0836D4B8[0]: zero(destination, size)
FILL_CODE = (0x03005E78, 0x03005EAA)               # where that routine runs
RESOURCE = 0x08501DB0              # data_08501DB0, the rotating objects' sprite resource

POOL = 0x02009170                  # data_02009170: u16 count; four list heads at +4; slots at +0x14
SLOTS, SLOT_COUNT, SLOT_SIZE = EWRAM + 0x20000, 32, 0x40
TASK = EWRAM + 0x10000
PAYLOAD, PAYLOAD_SIZE = TASK + 0x18, 0x35C         # func_08005954 passes task + 0x18
ALLOCATION = PAYLOAD_SIZE + 0x1C                   # and allocates and clears size + 0x1C
EVENT = EWRAM + 0x12000            # the 0x1C-byte event; +4 is the parent's status pointer
STATUS = EWRAM + 0x13000           # the status byte; func_08110888 waits for 7 in its phase 0x109
CONTROL = 0x03000940               # g_control_flags_03000940
WALK_ARGUMENT = EWRAM + 0x30000    # func_080D3024's argument; only its 3D branch uses it
ROTATING_AT, MOVING_AT = PAYLOAD + 8, PAYLOAD + 0x1C8   # 0x20-byte and 0x1C-byte entries

# Stubbed callees: (phase that calls them, value returned in r0 or None).
STUBS = {0x080D3AF8: (0, EWRAM + 0x15000), 0x08000B20: (0, None),
         0x080D7220: (0x101, None), 0x08003620: (0x101, None), 0x080D3EC0: (0x101, EWRAM + 0x16000),
         0x0801DB3C: (0x101, None), 0x080DFD8C: (0x101, EWRAM + 0x16100),
         0x080D4704: (0x101, EWRAM + 0x16200), 0x080D47DC: (0x101, None),
         0x080D4774: (0x103, 0), 0x080D3F08: (0x103, 0)}
# Callees the BUGFIX build reaches in the ROM through a veneer.
FROM_ROM = (CREATE_OBJECT, 0x08011100, 0x080110F8, 0x080112E8, SET_SCALE, 0x080E0608, 0x080035D0,
            0x080E064C, 0x080107D4, 0x080E0690, UNLINK, 0x080035A8)
# Memory compared between the two builds.
REGIONS = ((PAYLOAD, PAYLOAD_SIZE), (EVENT, 0x1C), (STATUS, 1), (POOL, 0x18),
           (SLOTS, SLOT_COUNT * SLOT_SIZE), (CONTROL, 0x60))

# Each table's shape: (first entry, last entry, size there, size there).  An
# entry is 256 / size, the 8.8 reciprocal an affine sprite takes; a negative
# size is a mirrored sprite.
SHAPES = {0x083A39D8: ((0, 59, 1, 2),),
          0x083A3A50: ((0, 59, 1, Fraction(1, 2)),),
          0x083A3AC8: ((0, 59, 1, Fraction(1, 4)),),
          0x083A3B40: ((0, 59, 1, Fraction(1, 16)),),
          0x083A3BB8: ((0, 29, 1, Fraction(1, 16)), (30, 59, Fraction(-1, 16), -1)),
          0x083A3C30: ((0, 19, 1, Fraction(1, 16)), (20, 59, Fraction(-1, 16), -1)),
          0x083A3CA8: ((0, 39, 1, Fraction(1, 16)), (40, 59, Fraction(-1, 16), Fraction(-1, 2)))}


def shape(segments, k):
    """256 / size(k), with size moving in equal steps across each segment."""
    for first, last, a, b in segments:
        if first <= k <= last:
            return Fraction(256) / (Fraction(a) + Fraction(b - a) * (k - first) / (last - first))


def run_of(values):
    """(first, last, whether each value is one more than the one before)."""
    return values[0], values[-1], values == list(range(values[0], values[0] + len(values)))


def words(values):
    return " ".join(f"{v & 0xFFFF:04X}" for v in values)


class Run:
    """One build of the task in its own machine, created and then driven pass by pass."""

    def __init__(self, rom, fixed_obj=None):
        m = self.m = Machine(rom)
        m.load(IWRAM_CODE, rom[IWRAM_IMAGE - ROM_BASE:][:IWRAM_BYTES])
        self.in_task = False
        self.reads, self.scales, self.unlinked, self.draws, self.stubbed = [], [], [], [], []
        self.counter_writes, self.stub_phases = [], []
        m.stub(DRAW_SCALED, lambda m: self.draws.append(
            ("scaled",) + tuple(m.reg(k) for k in range(4)) + tuple(m.stack_arg(k) for k in range(9))))
        m.stub(DRAW_PLAIN, lambda m: self.draws.append(
            ("plain",) + tuple(m.reg(k) for k in range(4)) + tuple(m.stack_arg(k) for k in range(7))))
        bindings = {f"func_{a:08X}": a for a in FROM_ROM}
        for address, (_, value) in STUBS.items():
            behaviour = lambda m, address=address, value=value: self._stub(address, value)
            m.stub(address, behaviour)
            bindings[f"func_{address:08X}"] = behaviour
        self.entry = ADDRESS if fixed_obj is None else install_fixed(m, fixed_obj, bindings)
        m.uc.hook_add(UC_HOOK_MEM_READ, self._table_read, begin=TABLES - 0x40, end=TABLES_END + 0x3F)
        m.uc.hook_add(UC_HOOK_MEM_WRITE, self._counter_write, begin=PAYLOAD, end=PAYLOAD + 1)
        m.uc.hook_add(UC_HOOK_CODE, self._set_scale, begin=SET_SCALE, end=SET_SCALE)
        m.uc.hook_add(UC_HOOK_CODE, self._unlink, begin=UNLINK, end=UNLINK)
        m.w16(POOL, SLOT_COUNT)
        m.w32(POOL + 0x14, SLOTS)
        # Creation, as func_08005954 does it: the allocation is cleared by the
        # ROM's zero fill, then the callback runs phase 0 with a copy of the
        # parent's descriptor; the task's stored phase becomes 0x100.
        m.uc.mem_write(TASK, b"\xA5" * ALLOCATION)
        self.phase = "fill"
        m.call(m.u32(ZERO_FILL), TASK, ALLOCATION)
        m.w16(EVENT, 0)
        m.w32(EVENT + 4, STATUS)
        self.phase = 0
        self.created = self._callback()
        self.state = 0x100

    def _stub(self, address, value):
        self.stub_phases.append((self.phase, address))
        if value is not None:
            self.m.set_reg(0, value)

    def _table_read(self, uc, access, address, size, value, _):
        if self.in_task:
            self.reads.append((uc.reg_read(UC_ARM_REG_PC) & ~1, address, size))

    def _counter_write(self, uc, access, address, size, value, _):
        self.counter_writes.append((self.phase, uc.reg_read(UC_ARM_REG_PC) & ~1, size, value))

    def _set_scale(self, uc, address, size, _):
        if self.in_task:
            m = self.m
            self.scales.append((m.reg(0), m.reg(1) & 0xFFFF, m.reg(2) & 0xFFFF, m.reg(3) & 0xFFFF))

    def _unlink(self, uc, address, size, _):
        if self.in_task:
            self.unlinked.append(self.m.reg(0))

    def _callback(self):
        self.in_task = True
        result = self.m.call(self.entry, TASK, EVENT, PAYLOAD)
        self.in_task = False
        return result

    counter = property(lambda self: self.m.u16(PAYLOAD))

    def rotating(self, i):
        return self.m.u32(ROTATING_AT + 0x20 * i)

    def moving(self, j):
        return self.m.u32(MOVING_AT + 0x1C * j)

    def step(self):
        """One pass: the runner's call with the stored phase, the object update and the draw walk."""
        m = self.m
        self.reads, self.scales, self.unlinked, self.draws = [], [], [], []
        before = (self.state, self.counter)
        self.phase = self.state
        m.w16(EVENT, self.state)
        result = self._callback()
        self.state = m.u16(EVENT)
        self.phase = "objects"
        record = {"before": before, "result": result, "reads": self.reads[:],
                  "scales": self.scales[:], "unlinked": self.unlinked[:]}
        m.call(UPDATE_OBJECTS)
        m.call(DRAW_WALK, WALK_ARGUMENT)
        record["draws"] = self.draws[:]
        return record

    def memory(self):
        return b"".join(bytes(self.m.uc.mem_read(base, size)) for base, size in REGIONS)


def differing(a, b):
    """Addresses at which two memory() images differ."""
    out, offset = [], 0
    for base, size in REGIONS:
        out += [base + k for k in range(size) if a[offset + k] != b[offset + k]]
        offset += size
    return out


def scaled(draws):
    """(x scale, y scale, angle) of each scaled draw: func_080018A0's stacked words 5, 6 and 7."""
    return [(d[10] & 0xFFFF, d[11] & 0xFFFF, d[12] & 0xFFFF) for d in draws if d[0] == "scaled"]


def main():
    rom = load_rom()
    source, fixed_obj = build_pair(rom, ADDRESS, EXTENT)
    print(f"source {source.relative_to(ROOT)}: default build == ROM bytes "
          f"[{ADDRESS:08X}, {ADDRESS + EXTENT:08X})")
    c = Checks()
    h16 = lambda a: struct.unpack_from("<h", rom, a - ROM_BASE)[0]
    u32 = lambda a: struct.unpack_from("<I", rom, a - ROM_BASE)[0]
    starts = [TABLES + TABLE_BYTES * t for t in range(TABLE_COUNT)]
    table = {t: [h16(t + 2 * k) for k in range(ENTRIES + 1)] for t in starts}   # and the halfword after
    rows = [DEFINITIONS + 20 * i for i in range(ROTATING)]
    x_of, y_of = [u32(r + 8) for r in rows], [u32(r + 12) for r in rows]
    spin = [u32(r + 16) & 0xFFFF for r in rows]
    used = sorted({t for t in x_of + y_of if t})
    # The lookups of one pass, in the order the function makes them: (object, axis, table).
    lookups = [(i, axis, t) for i in range(ROTATING) for axis, t in (("x", x_of[i]), ("y", y_of[i])) if t]

    def entry(t, k):
        """Entry k of a table, as a halfword; 0x0100 for an object with no table."""
        return (table[t][k] if t else 0x100) & 0xFFFF

    def expected(k):
        """(x scale, y scale, angle) of each object after k steps."""
        return [(entry(x_of[i], k), entry(y_of[i], k), k * spin[i] & 0xFFFF) for i in range(ROTATING)]

    def addresses(p):
        """(address, bytes) of each read of a pass; the instruction differs between the builds."""
        return [(a, n) for _, a, n in p["reads"]]

    def indexes(p):
        """The index each read of a pass makes into the table its lookup names."""
        return [(a - t) // 2 for (_, _, t), (_, a, _) in zip(lookups, p["reads"])]

    print("\n1. The scale tables: seven of 60 s16, back to back at 0x083A39D8-0x083A3D1F.")
    c.check("tables the 11 rows of data_083A2FD8 name (object: x, y; '-' for none)",
            " ".join(f"{i}:{x and f'{x:08X}' or '-'},{y and f'{y:08X}' or '-'}"
                     for i, (x, y) in enumerate(zip(x_of, y_of))),
            "0:083A3AC8,083A3A50 1:-,083A3A50 2:083A39D8,083A3BB8 3:083A39D8,083A39D8 "
            "4:083A3C30,083A3A50 5:-,- 6:083A39D8,083A39D8 7:083A3A50,083A3CA8 "
            "8:083A39D8,083A3BB8 9:083A3AC8,083A3A50 10:083A39D8,083A39D8")
    c.check("each named table is one of the seven; the one none of them names",
            (set(used) <= set(starts), [f"{t:08X}" for t in starts if t not in used]), (True, ["083A3B40"]))
    exact = near = 0
    for t in starts:
        for k in range(ENTRIES):
            model = shape(SHAPES[t], k)
            if table[t][k] == int(model):
                exact += 1
            elif model.denominator == 1 and abs(table[t][k]) == abs(int(model)) - 1:
                near += 1
    c.check("of the 420 entries: equal to 256 / size(k) truncated; one nearer 0 where that is whole",
            (exact, near), (414, 6))
    c.check("entry 0 of every table; entry 59, the end of its shape",
            ([words([table[t][0]]) for t in starts], [words([table[t][59]]) for t in starts]),
            (["0100"] * 7, ["0080", "0200", "0400", "1000", "FF00", "FF00", "FE00"]))
    c.check("entry 60 of each table this function names: the halfword after it",
            [f"{t:08X}:{entry(t, 60):04X}" for t in used],
            ["083A39D8:0100", "083A3A50:0100", "083A3AC8:0100", "083A3BB8:0100",
             "083A3C30:0100", "083A3CA8:000A"])
    c.check("that is the next table's entry 0; after 0x083A3CA8 it is 0x083A3D20, past the seventh",
            ([table[t][60] == table[t + TABLE_BYTES][0] for t in used[:-1]],
             f"{used[-1] + 2 * 60:08X}" if used[-1] + TABLE_BYTES == TABLES_END else None),
            ([True] * 5, "083A3D20"))

    # Both builds, from creation to three passes after phase 0x103.
    original, fixed = Run(rom), Run(rom, fixed_obj)
    rom_passes, fix_passes, unequal = [], [], []
    while len(rom_passes) < 66:
        rom_passes.append(original.step())
        fix_passes.append(fixed.step())
        unequal.append(differing(original.memory(), fixed.memory()))
        if len(rom_passes) == 2:
            objects = [original.rotating(i) for i in range(ROTATING)]
            movers = [original.moving(j) for j in range(MOVING)]
            created = [words(original.m.u16(o + k) for k in (0x32, 0x34, 0x36)) for o in objects]
    in_phase = lambda passes, phase: [p for p in passes if p["before"][0] == phase]
    rom_spin, fix_spin = in_phase(rom_passes, 0x102), in_phase(fix_passes, 0x102)

    print("\n2. Non-trigger: creation and the two passes before phase 0x102.  Phase 0")
    print("   stores the status pointer, 0x100 moves on, 0x101 creates the objects.")
    for name, run, passes in (("ROM   ", original, rom_passes), ("BUGFIX", fixed, fix_passes)):
        c.check(f"{name} (phase, counter) on entry to passes 1, 2, 3",
                [(hex(p["before"][0]), p["before"][1]) for p in passes[:3]],
                [("0x100", 0), ("0x101", 0), ("0x102", 0)])
        c.check(f"{name} writes to payload->counter before phase 0x102: (by, bytes, value)",
                [("zero fill" if FILL_CODE[0] <= pc < FILL_CODE[1] else f"{pc:08X}", size, value)
                 for phase, pc, size, value in run.counter_writes if phase in ("fill", 0, 0x100, 0x101)],
                [("zero fill", 4, 0)])
        c.check(f"{name} writes to it by the object update and the draw walk, on any pass",
                [w for w in run.counter_writes if w[0] == "objects"], [])
    c.check("table reads in passes 1 and 2; distinct func_080112CC (x, y, angle), and calls",
            [(len(p["reads"]), sorted(set(words(s[1:]) for s in p["scales"])), len(p["scales"]))
             for p in rom_passes[:2]], [(0, [], 0), (0, ["0100 0100 0000"], 11)])
    c.check("objects created: rotating, moving; all distinct and nonzero",
            (len(objects), len(movers), len(set(objects + movers)) == 25 and 0 not in objects + movers),
            (11, 14, True))
    c.check("the 11 rotating objects' +0x32, +0x34, +0x36 (x scale, y scale, angle) after pass 2",
            sorted(set(created)), ["0100 0100 0000"])
    c.check("bytes of payload, event, object pool and register image that differ between the builds",
            sum(unequal[:2], []), [])

    print("\n3. Trigger: pass 62, the 60th of phase 0x102, which unlinks the objects.")
    p = rom_spin[-1]
    c.check("ROM    (pass, phase, counter) on entry",
            (rom_passes.index(p) + 1, hex(p["before"][0]), p["before"][1]), (62, "0x102", 59))
    c.check("ROM    table reads: 19, by the two lookups, each at index 60 of its own table",
            ([(LOOKUPS.get(pc, f"{pc:08X}"), a, n) for pc, a, n in p["reads"]] ==
             [(axis, t + 2 * 60, 2) for _, axis, t in lookups], indexes(p) == [60] * 19), (True, True))
    c.check("ROM    reads inside the table they index",
            sum(t <= a < t + TABLE_BYTES for (_, _, t), (_, a, _) in zip(lookups, p["reads"])), 0)
    print("   ROM    the 19 reads (object axis: address = value):")
    shown = [f"{i}{axis}:{a:08X}={h16(a) & 0xFFFF:04X}" for (i, axis, _), (_, a, _) in zip(lookups, p["reads"])]
    for k in range(0, len(shown), 5):
        print("     " + "  ".join(shown[k:k + 5]))
    c.check("ROM    func_080112CC: (x, y, angle) passed to all 11 objects are entry 60 and 60 steps",
            [s[1:] for s in p["scales"]] == expected(60), True)
    c.check("ROM    func_080112CC(object 7, x, y, angle)",
            [words(s[1:]) for s in p["scales"] if s[0] == objects[7]],
            [words([0x0100, 0x000A, 60 * spin[7]])])
    p = fix_spin[-1]
    c.check("BUGFIX (pass, phase, counter) on entry",
            (fix_passes.index(p) + 1, hex(p["before"][0]), p["before"][1]), (62, "0x102", 59))
    c.check("BUGFIX table reads; func_080112CC calls", (p["reads"], p["scales"]), ([], []))
    for name, run, passes, spun in (("ROM   ", original, rom_passes, rom_spin),
                                    ("BUGFIX", fixed, fix_passes, fix_spin)):
        p, after = spun[-1], passes[62]
        c.check(f"{name} return value; phase after it; the status byte",
                (p["result"], hex(after["before"][0]), run.m.u8(STATUS)), (0, "0x103", 7))
        c.check(f"{name} the 25 objects unlinked in this pass; object pointers left in the payload",
                (sorted(p["unlinked"]) == sorted(objects + movers),
                 sorted(set([run.rotating(i) for i in range(ROTATING)] + [run.moving(j) for j in range(MOVING)]))),
                (True, [0]))
        c.check(f"{name} state bytes of the 25 objects; sprites drawn after this pass",
                (sorted(set(run.m.u8(o) for o in objects + movers)), len(p["draws"])), ([0], 0))
    left = lambda run: words(run.m.u16(objects[7] + k) for k in (0x32, 0x34, 0x36))
    c.check("x scale, y scale and angle left in object 7's freed slot: ROM, BUGFIX",
            (left(original), left(fixed)), (words(expected(60)[7]), words(expected(59)[7])))
    slot_of = lambda a: next((o for o in objects if o <= a < o + SLOT_SIZE), None)
    c.check("bytes that differ after this pass: offsets in freed rotating slots; anywhere else",
            (sorted(set(f"+0x{a - slot_of(a):02X}" for a in unequal[61] if slot_of(a))),
             [f"{a:08X}" for a in unequal[61] if not slot_of(a)]),
            (["+0x32", "+0x33", "+0x34", "+0x35", "+0x37"], []))

    print("\n4. All of phase 0x102.  Passes 1 to 59 are the same in both builds.")
    c.check("ROM / BUGFIX passes in phase 0x102", [len(rom_spin), len(fix_spin)], [60, 60])
    c.check("ROM    counter on entry: first pass, last pass, one more on each pass",
            run_of([p["before"][1] for p in rom_spin]), (0, 59, True))
    stores = [(pc, v) for phase, pc, _, v in original.counter_writes if phase == 0x102]
    c.check("ROM    stores to the counter in phase 0x102: by; values first, last, one more each",
            (sorted(set(f"{pc:08X}" for pc, _ in stores)), run_of([v for _, v in stores])),
            ([f"{COUNTER_STORE:08X}"], (1, 60, True)))
    c.check("ROM    reads on every pass; pass k reads index k, k = 1..60",
            ([len(p["reads"]) for p in rom_spin] == [19] * 60,
             [sorted(set(indexes(p))) for p in rom_spin] == [[k] for k in range(1, 61)]), (True, True))
    c.check("BUGFIX reads on passes 1..59; pass k reads index k; reads on pass 60",
            ([len(p["reads"]) for p in fix_spin[:59]] == [19] * 59,
             [sorted(set(indexes(p))) for p in fix_spin[:59]] == [[k] for k in range(1, 60)],
             len(fix_spin[59]["reads"])), (True, True, 0))
    inside = lambda passes: all(t <= a < t + TABLE_BYTES for p in passes
                                for (_, _, t), (_, a, _) in zip(lookups, p["reads"]))
    c.check("ROM / BUGFIX every read inside the table it indexes", [inside(rom_spin), inside(fix_spin)],
            [False, True])
    c.check("ROM    func_080112CC on pass k, k = 1..60: entry k of each object's tables, k steps of spin",
            all([s[1:] for s in p["scales"]] == expected(k) for k, p in enumerate(rom_spin, 1)), True)
    c.check("passes 1..59: same reads, same calls; bytes that differ between the builds",
            ([addresses(p) for p in rom_spin[:59]] == [addresses(p) for p in fix_spin[:59]],
             [p["scales"] for p in rom_spin[:59]] == [p["scales"] for p in fix_spin[:59]],
             len(sum(unequal[2:61], []))), (True, True, 0))

    print("\n5. What is drawn.  The draw walk runs after every pass.  Compared here is")
    print("   every word it hands the two sprite routines, on all passes of the run.")
    c.check("passes compared; passes on which the builds differ",
            (len(rom_passes), [k + 1 for k in range(len(rom_passes))
                               if rom_passes[k]["draws"] != fix_passes[k]["draws"]]), (66, []))
    for name, passes in (("ROM   ", rom_passes), ("BUGFIX", fix_passes)):
        counts = [(len(scaled(p["draws"])), len(p["draws"]) - len(scaled(p["draws"]))) for p in passes]
        c.check(f"{name} (scaled, plain) draws on passes 2..61; on passes 1 and 62..66",
                (sorted(set(counts[1:61])), counts[:1] + counts[61:]), ([(11, 14)], [(0, 0)] * 6))
        c.check(f"{name} pass 2 + k, k = 0..59: the 11 scaled draws are each object's entry k, k steps",
                all(Counter(scaled(passes[1 + k]["draws"])) == Counter(expected(k)) for k in range(60)), True)
    c.check("ROM    draws 000A on any pass", 0x000A in [v for p in rom_passes
                                                       for d in scaled(p["draws"]) for v in d[:2]], False)
    print("   object 7 (x 0x083A3A50, y 0x083A3CA8): the entries drawn on passes 2, 6, ..., 58 and 61")
    print("     x  " + words(entry(x_of[7], k) for k in list(range(0, 60, 4)) + [59]))
    print("     y  " + words(entry(y_of[7], k) for k in list(range(0, 60, 4)) + [59]))
    print("   The ROM's allocator rebuilds a freed slot from its template (ROM machine):")
    made = []
    while objects[7] not in made and len(made) < SLOT_COUNT:
        made.append(original.m.call(CREATE_OBJECT, RESOURCE, 7, 112, 112, 0x2F0, 6, 0, 0))
    c.check("a new object takes the slot that held 000A; its x and y scale",
            (objects[7] in made, words(original.m.u16(objects[7] + k) for k in (0x32, 0x34))),
            (True, "0100 0100"))

    print("\n6. Non-trigger: phase 0x103, and single passes of phase 0x102 in fresh machines.")
    c.check("pass 63, phase 0x103: ROM / BUGFIX (return, phase after, reads, calls)",
            [(p[62]["result"], hex(p[63]["before"][0]), len(p[62]["reads"]), len(p[62]["scales"]))
             for p in (rom_passes, fix_passes)], [(0, "0x2", 0, 0)] * 2)
    c.check("ROM / BUGFIX stubbed callees: all reached, each only in its own phase",
            [sorted(set(a for _, a in run.stub_phases)) == sorted(STUBS) and
             all(phase == STUBS[a][0] for phase, a in run.stub_phases) for run in (original, fixed)],
            [True, True])
    for counter in (29, 58):
        results = []
        for build in (None, fixed_obj):
            run = Run(rom, build)
            run.step()                           # phase 0x100
            run.step()                           # phase 0x101: creates the objects
            run.m.w16(PAYLOAD, counter)
            p = run.step()
            results.append((run, p, (p["result"], hex(run.state), run.counter, len(p["reads"]),
                                     len(p["scales"]), len(p["unlinked"]))))
        (a, pa, got_a), (b, pb, got_b) = results
        want = (0, "0x102", counter + 1, 19, 11, 0)
        c.check(f"counter {counter}: ROM / BUGFIX (return, phase, counter, reads, calls, unlinks)",
                (got_a, got_b), (want, want))
        c.check(f"counter {counter}: reads at index {counter + 1}; same reads, calls, draws; bytes that differ",
                (indexes(pa) == [counter + 1] * 19, addresses(pa) == addresses(pb), pa["scales"] == pb["scales"],
                 pa["draws"] == pb["draws"], differing(a.memory(), b.memory())),
                (True, True, True, True, []))
    c.finish()


if __name__ == "__main__":
    main()
