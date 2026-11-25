#!/usr/bin/env python3
"""Behavioural case for func_08116514: phase 0x101 steps its timer before it
indexes its 150-entry curves, so the pass that removes the 24 pieces reads
entry 150 of every curve, one past the end.  The -DBUGFIX build makes no
lookup on that pass.

    python3 docs/bugs/08116514/repro.py [path/to/baserom.bin]

Runs the ORIGINAL function bytes from your ROM and the -DBUGFIX build of
src/**/08116514.c under a Thumb emulator, pass for pass, inside the effect
that starts it: the parent func_081168B4 (from the ROM) from its phase
0x100, the blend sequence that parent starts (func_080D3CB4 on
data_0894DCE4, from the ROM), and this task.  A pass is what func_080D36B0
does in its state 1: the task runner, then the object update
(func_08010DD0) and the object draw walk (func_080D3024).  The runner is
modelled in Python as src/08005A24.c and src/08005954.c have it: each live
task's callback once per pass with its stored phase, a parent before its
children, children in creation order; a task created during a pass runs
its phase 0 at creation and its phase 0x100 later in the same pass.  The
run goes on until five passes after the pieces are removed.  Exits 0 when
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
  * data_0836D4BC[0], the (destination, source, size) copy routine the game
    runs from IWRAM, is a byte copy (the object allocator uses it).
  * Task starts and ends, which the Python runner does instead:
    func_08005B6C (this task), func_080D3E9C (the blend sequence) and
    func_08005B58 (a task's removal).  func_080D4704 (a palette animation)
    and func_080DFD8C (a sound sequence) return a task that never ends;
    their callbacks are not run.  func_080E05DC reports the parent's set-up
    task done.
Everything else runs from the ROM: the parent's phases 0x100-0x102 with
func_080D7220 (BG2 set-up), func_080D3F08, func_080D4774 and func_080035A8;
the blend sequence with func_080D3BD0, func_080E0608, func_080E064C and
func_080E0690; and this task's callees, the object creator func_080D5CC0
with its allocator, the setters func_08011100, func_080110F8,
func_080112E8, func_08011118 and func_08011120, func_080112CC,
func_080112D4, func_080107D4, func_080035D0, func_080D7468 (BG2 scroll),
and func_080D5F74 with the unlink func_08011428; then per pass
func_08010DD0 and func_080D3024.

The case fails if any of these stops being true: the ROM bytes read entry
150 of every curve on the pass that removes the pieces; the BUGFIX build
reads nothing on that pass; BG2 is already hidden when the ROM writes its
scroll from outside the curve; and the sprites drawn and the LCD register
image are the same in both builds on every pass while BG2 is shown.
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
from unicorn import UC_HOOK_MEM_READ

ADDRESS, EXTENT = 0x08116514, 928
PARENT = 0x081168B4                # func_081168B4: effect id 0x13A; starts this task in its phase 0x101
SEQUENCE = 0x080D3CB4              # the blend sequence callback func_080D3E9C starts
BLEND = 0x0894DCE4                 # data_0894DCE4: the parent's blend sequence
ENTRIES = 150                      # entries per curve
SCALE_CURVES = 0x083A3E64          # four curves of 150 s16, to 0x083A4314
SCALE_TABLE = 0x083A4314           # data_083A4314: 12 pointers into them, or 0
BYTE_CURVES = 0x083A4344           # data_083A4344: thirteen curves of 150 bytes, to 0x083A4AE2
PAD = 0x083A4AE2                   # two bytes before the piece table
PIECES = 0x083A4AE4                # data_083A4AE4: 24 rows of 16 bytes
CONTROL = 0x03000940               # g_control_flags_03000940: the LCD register image
DISPCNT_BG2 = 0x0400               # DISPCNT: BG2 on
BG2VOFS = CONTROL + 0x14
UPDATE_OBJECTS = 0x08010DD0
DRAW_WALK = 0x080D3024
DRAW_SCALED, DRAW_PLAIN = 0x080018A0, 0x08001F34
COPIER_TABLE = 0x0836D4BC          # data_0836D4BC[0]: copy(destination, source, size)
SET_POSITION = 0x080107D4          # func_080107D4(object, x, y, z)
SET_SCALE = 0x080112CC             # func_080112CC(object, x scale, y scale, angle): three strh
UNLINK = 0x08011428
SETUP_DONE, START_SEQUENCE, START_PALETTE, START_SOUND = 0x080E05DC, 0x080D3E9C, 0x080D4704, 0x080DFD8C
CREATE_TASK, END_TASK = 0x08005B6C, 0x08005B58

POOL = 0x02009170                  # data_02009170: u16 count; four list heads at +4; slots at +0x14
SLOTS, SLOT_COUNT, SLOT_SIZE = EWRAM + 0x20000, 32, 0x40
WALK_ARGUMENT = EWRAM + 0x30000    # func_080D3024's argument; only its 3D branch uses it
HEADER = 0x18                      # a task: callback, previous, next, parent, child, state (+0x14), flags
CHILD_SIZE = 0x16C
# Callees the BUGFIX build reaches in the ROM through a veneer.
FROM_ROM = (0x080D5CC0, 0x08011100, 0x080110F8, 0x080112E8, 0x08011118, 0x08011120,
            SET_SCALE, 0x080112D4, 0x080035D0, 0x080D7468, SET_POSITION, 0x080D5F74)


class Task:
    def __init__(self, name, header, entry):
        self.name, self.header, self.entry = name, header, entry
        self.event, self.payload = header + 0x800, header + HEADER
        self.state, self.removed = 0x100, False


def run_of(values):
    """(first, last, whether each value is one more than the one before)."""
    return values[0], values[-1], values == list(range(values[0], values[0] + len(values)))


def hexes(values, width=4):
    return " ".join(f"{v & (1 << 4 * width) - 1:0{width}X}" for v in values)


class Run:
    """One build of the task in its own machine, inside the effect, pass by pass."""

    def __init__(self, rom, fixed_obj=None):
        m = self.m = Machine(rom)
        self.rom = rom
        copier, = struct.unpack_from("<I", rom, COPIER_TABLE - ROM_BASE)
        m.stub(copier, lambda m: m.uc.mem_write(m.reg(0), bytes(m.uc.mem_read(m.reg(1), m.reg(2)))))
        m.stub(DRAW_SCALED, lambda m: self.draws.append(
            ("scaled",) + tuple(m.reg(k) for k in range(4)) + tuple(m.stack_arg(k) for k in range(9))))
        m.stub(DRAW_PLAIN, lambda m: self.draws.append(
            ("plain",) + tuple(m.reg(k) for k in range(4)) + tuple(m.stack_arg(k) for k in range(7))))
        self.parent = Task("parent", EWRAM + 0x10000, PARENT)
        self.blend = Task("blend", EWRAM + 0x11000, SEQUENCE)
        self.child = None
        palette, sound = EWRAM + 0x13000, EWRAM + 0x14000
        for header in (palette, sound):
            m.w16(header + 0x14, 0x100)
        m.stub(SETUP_DONE, lambda m: m.set_reg(0, 0))
        m.stub(START_SEQUENCE, self._start_sequence)
        m.stub(START_PALETTE, lambda m: m.set_reg(0, palette))
        m.stub(START_SOUND, lambda m: m.set_reg(0, sound))
        m.stub(CREATE_TASK, self._create_task)
        m.stub(END_TASK, self._end_task)
        bindings = {f"func_{a:08X}": a for a in FROM_ROM}
        self.child_entry = ADDRESS if fixed_obj is None else install_fixed(m, fixed_obj, bindings)
        self.in_child = False
        self.reads, self.calls, self.unlinked, self.draws = [], [], [], []
        m.uc.hook_add(UC_HOOK_MEM_READ, self._read, begin=SCALE_CURVES, end=PIECES - 1)
        for address, name in ((SET_POSITION, "position"), (SET_SCALE, "scale")):
            m.uc.hook_add(UC_HOOK_CODE, lambda uc, a, s, _, name=name: self._call(name),
                          begin=address, end=address)
        m.uc.hook_add(UC_HOOK_CODE, lambda uc, a, s, _: self.unlinked.append(self.m.reg(0)),
                      begin=UNLINK, end=UNLINK)
        m.w16(POOL, SLOT_COUNT)
        m.w32(POOL + 0x14, SLOTS)
        self.tasks, self.created = [self.parent], []
        self.parent.state = 0x100       # its set-up task (phases 0 and 1) is done

    # -- the task runner -------------------------------------------------
    def _start_sequence(self, m):
        self.created.append(("blend", m.reg(0), m.reg(1)))
        m.set_reg(0, self.blend.header)

    def _create_task(self, m):
        self.created.append(("child", m.reg(0), m.reg(1)))
        self.child = Task("child", EWRAM + 0x12000, self.child_entry)
        m.set_reg(0, self.child.header)

    def _end_task(self, m):
        for task in self.tasks:
            if task.header == m.reg(0):
                task.removed = True

    def _run(self, task, phase):
        m = self.m
        m.w16(task.event, phase)
        self.in_child = task is self.child
        m.call(task.entry, task.header, task.event, task.payload)
        self.in_child = False
        task.state = m.u16(task.event)
        m.w16(task.header + 0x14, task.state)

    def _start(self, kind, first, _parent):
        m = self.m
        task = self.blend if kind == "blend" else self.child
        if kind == "blend":             # func_080D3E9C's descriptor: sequence, flags 0, delay 0
            m.w32(task.event + 4, first)
            m.w16(task.event + 0x14, 0)
            m.w16(task.event + 0x16, 0)
        self._run(task, 0)
        task.state = 0x100
        m.w16(task.header + 0x14, 0x100)
        self.tasks.append(task)

    def _read(self, uc, access, address, size, value, _):
        if self.in_child and not SCALE_TABLE <= address < BYTE_CURVES:
            self.reads.append((address, size))

    def _call(self, name):
        if self.in_child:
            m = self.m
            self.calls.append((name, m.reg(0)) + tuple(m.reg(k) & 0xFFFF for k in (1, 2, 3)))

    def step(self):
        """One pass: the runner, the object update and the draw walk."""
        m = self.m
        self.reads, self.calls, self.unlinked, self.draws = [], [], [], []
        entry = self.states()
        timer = m.u16(self.child.payload) if entry["child"] is not None else None
        k = 0
        while k < len(self.tasks):
            task = self.tasks[k]
            k += 1
            if task.removed:
                continue
            self.created = []
            self._run(task, task.state)
            for request in self.created:
                self._start(*request)
        reads, calls, unlinked = self.reads[:], self.calls[:], self.unlinked[:]
        m.call(UPDATE_OBJECTS)
        m.call(DRAW_WALK, WALK_ARGUMENT)
        return {"entry": entry, "exit": self.states(), "timer": timer, "reads": reads, "calls": calls,
                "unlinked": unlinked, "draws": self.draws[:],
                "control": bytes(m.uc.mem_read(CONTROL, 0x50))}

    def states(self):
        """Each task's stored phase, or None before it starts and after it ends."""
        live = lambda t: t is not None and t in self.tasks and not t.removed
        return {name: (t.state if live(t) else None)
                for name, t in (("parent", self.parent), ("blend", self.blend), ("child", self.child))}

    def regions(self):
        out = [(CONTROL, 0x50), (POOL, 0x18), (SLOTS, SLOT_COUNT * SLOT_SIZE)]
        for task in (self.parent, self.blend, self.child):
            if task is not None:
                out.append((task.header + 0x14, 2))
                out.append((task.payload, {"parent": 0x3C, "blend": 0x2C, "child": CHILD_SIZE}[task.name]))
        return out

    def memory(self):
        return [(base, bytes(self.m.uc.mem_read(base, size))) for base, size in self.regions()]


def differing(a, b):
    """Addresses at which two memory() images differ."""
    return [base + k for (base, x), (_, y) in zip(a, b) for k in range(len(x)) if x[k] != y[k]]


def expected_reads(run, t):
    """The lookups phase 0x101 makes with the stepped timer t: the BG2 curve,
    then per piece its byte curve and, if it is scaled, its scale curves."""
    m, payload = run.m, run.child.payload
    out = [(BYTE_CURVES + t, 1)]
    for j in range(24):
        out.append((m.u32(payload + 0x10C + 4 * j) + t, 1))
        if m.u8(payload + 2 + j):
            for field in (0x1A, 0x32):
                curve = m.u32(SCALE_TABLE + 4 * m.u8(payload + field + j))
                if curve:
                    out.append((curve + 2 * t, 2))
    return out


def lookup_index(run, p):
    """The single t whose lookups are exactly this pass's reads, or None."""
    if not p["reads"]:
        return None
    t = p["reads"][0][0] - BYTE_CURVES
    return t if p["reads"] == expected_reads(run, t) else "mismatch"


def curve_of(address, size):
    """(base, end) of the curve a read belongs to by the stepped index, given
    the curve layout: byte curves of 150, scale curves of 300 bytes."""
    if size == 1:
        base = BYTE_CURVES + (address - BYTE_CURVES) // ENTRIES * ENTRIES
        return base, base + ENTRIES
    base = SCALE_CURVES + (address - SCALE_CURVES) // (2 * ENTRIES) * 2 * ENTRIES
    return base, base + 2 * ENTRIES


def main():
    rom = load_rom()
    source, fixed_obj = build_pair(rom, ADDRESS, EXTENT)
    print(f"source {source.relative_to(ROOT)}: default build == ROM bytes "
          f"[{ADDRESS:08X}, {ADDRESS + EXTENT:08X})")
    c = Checks()
    u8 = lambda a: rom[a - ROM_BASE]
    s16 = lambda a: struct.unpack_from("<h", rom, a - ROM_BASE)[0]
    u32 = lambda a: struct.unpack_from("<I", rom, a - ROM_BASE)[0]

    print("\n1. The curves.  Thirteen byte curves and four s16 scale curves, 150")
    print("   entries each, back to back; the byte after the last byte curve is pad.")
    byte_curves = [BYTE_CURVES + ENTRIES * k for k in range(13)]
    table = [u32(SCALE_TABLE + 4 * k) for k in range(12)]
    scale_curves = sorted(set(table) - {0})
    pieces = [u32(PIECES + 16 * i + 12) for i in range(24)]
    c.check("byte curves end at the pad", byte_curves[-1] + ENTRIES == PAD, True)
    c.check("scale curves (data_083A4314's non-null words) are 300 bytes apart and end at the table",
            [f"{a:08X}" for a in scale_curves] + [scale_curves[-1] + 2 * ENTRIES == SCALE_TABLE],
            ["083A3E64", "083A3F90", "083A40BC", "083A41E8", True])
    c.check("every piece row of data_083A4AE4 points at the start of a byte curve",
            all(p in byte_curves for p in pieces), True)
    print("  byte curves, entries 149 and 150 (150 = the next curve's entry 0, or the pad):")
    print("   ", "  ".join(f"{u8(b + 149)}|{u8(b + 150)}" for b in byte_curves))
    print("  scale curves, entries 0, 149 and 150:")
    print("   ", "  ".join(hexes([s16(b), s16(b + 298), s16(b + 300)]) for b in scale_curves))
    c.check("entry 0 of every scale curve is +-0x100, the scale of an unscaled sprite",
            [abs(s16(b)) for b in scale_curves], [0x100] * 4)

    original, fixed = Run(rom), Run(rom, fixed_obj)
    rom_passes, fix_passes, unequal = [], [], []
    while not (rom_passes and rom_passes[-1]["entry"]["child"] == 0x102):
        rom_passes.append(original.step())
        fix_passes.append(fixed.step())
        unequal.append(differing(original.memory(), fixed.memory()))
    for _ in range(4):
        rom_passes.append(original.step())
        fix_passes.append(fixed.step())
        unequal.append(differing(original.memory(), fixed.memory()))
    passes = len(rom_passes)
    number = lambda passes, test: [k + 1 for k, p in enumerate(passes) if test(p)]
    child_phase = lambda passes, phase: number(passes, lambda p: p["entry"]["child"] == phase)
    spin = child_phase(rom_passes, 0x101)
    last = spin[-1]

    print("\n2. The effect, pass by pass (pass 1 = the parent's phase 0x100).")
    c.check("parent passes in phase 0x101 before it starts this task (state->delay = 60, 0x081169B2)",
            len(number(rom_passes, lambda p: p["entry"]["parent"] == 0x101)), 60)
    for name, passes_ in (("ROM   ", rom_passes), ("BUGFIX", fix_passes)):
        created = number(passes_, lambda p: p["entry"]["child"] is None and p["exit"]["child"] is not None)
        c.check(f"{name} pass that starts this task (phase 0, then its first phase 0x100 pass); "
                "timer after it", (created, passes_[created[0]]["timer"]), ([61], 9))
        c.check(f"{name} passes it starts in phases 0x100, 0x101, 0x102 (first..last)",
                [(ph[0], ph[-1]) for ph in (child_phase(passes_, 0x100), child_phase(passes_, 0x101),
                                             child_phase(passes_, 0x102))],
                [(62, 70), (71, 220), (221, 221)])
    c.check("ROM / BUGFIX the pass on which the blend sequence ends (its phase becomes 2)",
            [number(ps, lambda p: p["exit"]["blend"] == 2 and p["entry"]["blend"] != 2)
             for ps in (rom_passes, fix_passes)], [[211], [211]])
    c.check("ROM / BUGFIX the pass on which the parent removes it",
            [number(ps, lambda p: p["entry"]["blend"] is not None and p["exit"]["blend"] is None)
             for ps in (rom_passes, fix_passes)], [[212], [212]])
    shown = lambda p: bool(struct.unpack_from("<H", p["control"], 0)[0] & DISPCNT_BG2)
    c.check("ROM / BUGFIX passes after which BG2 is on (DISPCNT bit 10 in the register image)",
            [(number(ps, shown)[0], number(ps, shown)[-1]) for ps in (rom_passes, fix_passes)],
            [(1, 211), (1, 211)])

    print(f"\n3. Trigger: pass {last}, this task's 150th pass of phase 0x101, which removes")
    print("   the pieces.")
    p, q = rom_passes[last - 1], fix_passes[last - 1]
    c.check("ROM / BUGFIX timer on entry", (p["timer"], q["timer"]), (149, 149))
    c.check("ROM    index every lookup uses (the stepped timer)", lookup_index(original, p), 150)
    outside = [(f"{a:08X}", a >= curve_of(a - (150 if n == 1 else 300), n)[1]) for a, n in p["reads"]]
    c.check("ROM    lookups; each lands at or past the end of its own curve",
            (len(outside), all(o for _, o in outside)), (len(expected_reads(original, 150)), True))
    bg = p["reads"][0][0]
    c.check("ROM    the BG2 curve's lookup: address, value (the next curve's entry 0)",
            (f"{bg:08X}", u8(bg)), ("083A43DA", 0))
    scale_reads = sorted({(f"{a:08X}", f"{s16(a) & 0xFFFF:04X}") for a, n in p["reads"] if n == 2})
    c.check("ROM    scale lookups (address, value)", scale_reads,
            [("083A3F90", "0100"), ("083A40BC", "FF00"), ("083A41E8", "FF00")])
    c.check("ROM    BG2 vertical offset before / after this pass",
            hexes([struct.unpack_from("<H", r["control"], 0x14)[0] for r in rom_passes[last - 2:last]]),
            "FFFB 0000")
    scaled = sum(original.m.u8(original.child.payload + 2 + j) for j in range(24))
    c.check("ROM    calls made with the values read: func_080107D4, func_080112CC (scaled pieces)",
            [sum(1 for x in p["calls"] if x[0] == kind) for kind in ("position", "scale")], [24, scaled])
    c.check("BUGFIX lookups; func_080107D4 and func_080112CC calls", (q["reads"], q["calls"]), ([], []))
    c.check("BUGFIX BG2 vertical offset after this pass (unchanged)",
            hexes([struct.unpack_from("<H", q["control"], 0x14)[0]]), "FFFB")
    for name, r in (("ROM   ", p), ("BUGFIX", q)):
        c.check(f"{name} objects unlinked in this pass (func_080D5F74 -> func_08011428)", len(r["unlinked"]), 24)
    for name, run in (("ROM   ", original), ("BUGFIX", fixed)):
        c.check(f"{name} payload->objects after it; state bytes of the 24 objects",
                ([run.m.u32(run.child.payload + 0xAC + 4 * j) for j in range(24)] == [0] * 24,
                 [run.m.u8(o) for o in p["unlinked"]] == [0] * 24), (True, True))
    c.check("ROM / BUGFIX sprites drawn after this pass and after the next five",
            [sum(len(r["draws"]) for r in ps[last - 1:]) for ps in (rom_passes, fix_passes)], [0, 0])
    hidden = number(rom_passes, shown)[-1] + 1
    print(f"  The parent turns BG2 off on pass {hidden}; the ROM writes the offset from")
    print(f"  outside the curve on pass {last}, {last - hidden} passes later.")
    c.check("BG2 on after this pass, in either build", shown(p) or shown(q), False)

    print("\n4. All of phase 0x101.  Passes 1 to 149 are the same in both builds.")
    rom_spin = [rom_passes[k - 1] for k in spin]
    fix_spin = [fix_passes[k - 1] for k in spin]
    c.check("ROM    timer on entry: first pass, last pass, one more on each pass",
            run_of([r["timer"] for r in rom_spin]), (0, 149, True))
    print("  BG2 vertical offset after passes 70, 71, 211 (the last with BG2 on) and 219:",
          hexes(struct.unpack_from("<H", rom_passes[k - 1]["control"], 0x14)[0] for k in (70, 71, 211, 219)))
    c.check("ROM    lookup index: first pass, last pass, one more on each pass",
            run_of([lookup_index(original, r) for r in rom_spin]), (1, 150, True))
    indexes = [lookup_index(fixed, r) for r in fix_spin]
    c.check("BUGFIX lookup index: first pass, 149th pass, one more on each pass; 150th pass",
            (run_of(indexes[:149]), indexes[149]), ((1, 149, True), None))
    def placed(run, t):
        """The y each func_080107D4 call of a pass would get from entry t."""
        payload = run.child.payload
        return [run.m.u16(payload + 0x7A + 2 * j) + u8(run.m.u32(payload + 0x10C + 4 * j) + t) & 0xFFFF
                for j in range(24)]
    c.check("ROM    y passed to func_080107D4 on pass t = phase 0's y + entry t of the piece's curve, "
            "t = 1..149", all([x[3] for x in r["calls"] if x[0] == "position"] == placed(original, t)
                              for t, r in enumerate(rom_spin[:149], 1)), True)
    c.check("ROM / BUGFIX every lookup inside its curve",
            [all(a < curve_of(a - k * (1 if n == 1 else 2), n)[1]
                 for k, r in enumerate(ps, 1) for a, n in r["reads"]) for ps in (rom_spin, fix_spin)],
            [False, True])
    c.check("passes 1..149: same lookups, same calls; bytes that differ between the builds",
            ([r["reads"] for r in rom_spin[:149]] == [r["reads"] for r in fix_spin[:149]],
             [r["calls"] for r in rom_spin[:149]] == [r["calls"] for r in fix_spin[:149]],
             len(sum(unequal[:last - 1], []))), (True, True, 0))

    print("\n5. What reaches the screen: every word handed to the sprite routines and")
    print("   the LCD register image, after every pass of the run.")
    c.check("passes compared; passes whose sprite draws differ",
            (passes, number(range(passes), lambda k: rom_passes[k]["draws"] != fix_passes[k]["draws"])),
            (passes, []))
    for name, ps in (("ROM   ", rom_passes), ("BUGFIX", fix_passes)):
        c.check(f"{name} passes with the 24 pieces drawn (first, last); passes with some other count",
                (number(ps, lambda p: len(p["draws"]) == 24)[0], number(ps, lambda p: len(p["draws"]) == 24)[-1],
                 number(ps, lambda p: 0 < len(p["draws"]) != 24)), (61, last - 1, []))
    image_diff = [(k + 1, [f"+0x{o:02X}" for o in range(0x50)
                           if rom_passes[k]["control"][o] != fix_passes[k]["control"][o]])
                  for k in range(passes) if rom_passes[k]["control"] != fix_passes[k]["control"]]
    c.check("passes whose register images differ, and where",
            (image_diff[0][0], image_diff[-1][0], sorted({o for _, os in image_diff for o in os})),
            (last, passes, ["+0x14", "+0x15"]))
    c.check("BG2 on, on any of those passes", any(shown(rom_passes[k - 1]) for k, _ in image_diff), False)
    after = sorted({a for a in unequal[last - 1]})
    in_freed = [a for a in after if (a - SLOTS) // SLOT_SIZE * SLOT_SIZE + SLOTS in set(p["unlinked"])]
    c.check("bytes that differ between the builds after the trigger pass: in freed objects, BG2VOFS, other",
            (len(in_freed) > 0, [f"{a:08X}" for a in after if a in (BG2VOFS, BG2VOFS + 1)],
             [f"{a:08X}" for a in after if a not in in_freed and a not in (BG2VOFS, BG2VOFS + 1)]),
            (True, ["03000954", "03000955"], []))

    print("\n6. Non-trigger: one pass of phase 0x101 from timer 74, in fresh machines.")
    results = []
    for build in (None, fixed_obj):
        run = Run(rom, build)
        while run.child is None or run.child.removed or run.child.state != 0x101:
            run.step()
        run.m.w16(run.child.payload, 74)
        r = run.step()
        results.append((run, r))
    (a, ra), (b, rb) = results
    c.check("ROM / BUGFIX lookup index", [lookup_index(a, ra), lookup_index(b, rb)], [75, 75])
    c.check("same lookups, calls and draws; bytes that differ between the builds",
            (ra["reads"] == rb["reads"], ra["calls"] == rb["calls"], ra["draws"] == rb["draws"],
             differing(a.memory(), b.memory())), (True, True, True, []))
    c.finish()


if __name__ == "__main__":
    main()
