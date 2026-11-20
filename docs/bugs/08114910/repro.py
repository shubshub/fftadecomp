#!/usr/bin/env python3
"""Behavioural case for func_08114910: phase 0x105 steps its counter before
it indexes a 20-entry scale table, so its twentieth lookup reads the halfword
after the table.  The -DBUGFIX build makes no lookup on that pass.

    python3 docs/bugs/08114910/repro.py [path/to/baserom.bin]

Runs the ORIGINAL function bytes from your ROM and the -DBUGFIX build of
src/**/08114910.c under a Thumb emulator, pass for pass, the way the game
runs this task: func_080D36B0 calls the task runner (func_08005A24, which
calls the callback once with the task's stored phase), then the object
update (func_08010DD0, through func_0800A640) and the object draw walk
(func_080D3024).  The run starts in phase 0x103, where the function creates
its first object, and goes on through the 50 waiting passes of phase 0x104
and the 20 passes of phase 0x105.  Exits 0 when every assertion holds.

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
    runs from IWRAM, is a byte copy.  The object allocator calls it to copy
    its 64-byte template into a free slot.
  * func_080DFD8C (starts a child task in phase 0x103) returns a token.
  * The twelve callees that only other phases use record that they were
    reached; the case asserts that none is.
Everything else runs from the ROM: the object creator func_080D5CC0 with its
allocator (func_08011348, func_0801093C, func_0801075C, func_08010D2C,
func_080105C4, func_08011138), the setters func_08011198, func_08011058,
func_080110F8 and func_080112E8, the interpolator func_080E0608 /
func_080E064C, the scale setter func_080112CC, the unlink func_08011428, and
per pass func_08010DD0 (with func_08010AFC) and func_080D3024 (with
func_0801E6F0, func_08011634, func_08011690, func_08010FEC, func_080110D8),
and the call-through-register thunk func_08142250.

The table entries are not shipped: the expected values come from the closed
form 256 * 608 / (608 - 31 * k), which the case first checks against the 20
halfwords in your ROM.

The case fails if any of these stops being true: the ROM bytes read index 20
on the pass that removes the object; the BUGFIX build does not; and the
draw walk hands the sprite routines the same values in both, on every pass.
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

ADDRESS, EXTENT = 0x08114910, 1196
TABLE, ENTRIES = 0x083A39A6, 20    # data_083A39A6: 20 halfwords, 0x083A39A6-0x083A39CD
NEXT_OBJECT = TABLE + 2 * ENTRIES  # data_083A39CE, the script src/081151A0.c starts
LOOKUP = 0x08114D00                # ldrsh r2, [r1, r3]: the table read
SET_SCALE = 0x080112CC             # func_080112CC(object, x, y, angle): three strh
CREATE_OBJECT = 0x080D5CC0         # func_080D5CC0(resource, index, x, y, ...)
UPDATE_OBJECTS = 0x08010DD0        # steps every object's animation
DRAW_WALK = 0x080D3024             # walks the object list, calls the sprite routines
DRAW_SCALED, DRAW_PLAIN = 0x080018A0, 0x08001F34
COPIER_TABLE = 0x0836D4BC          # data_0836D4BC[0]: copy(destination, source, size)
START_CHILD = 0x080DFD8C
RESOURCE = 0x08505FA4              # data_08505FA4, the sprite resource of both objects

POOL = 0x02009170                  # data_02009170: u16 count; four list heads at +4; slots at +0x14
DRAW_LIST = POOL + 4               # the list of objects created with list byte 2
SLOTS, SLOT_COUNT, SLOT_SIZE = EWRAM + 0x20000, 8, 0x40
TASK = EWRAM + 0x10000             # stands for the task; only passed on to callees
PAYLOAD = TASK + 0x18              # the runner passes task + 1 (0x18 bytes of header)
EVENT = EWRAM + 0x12000            # the event whose phase halfword the runner copies in and out
WALK_ARGUMENT = EWRAM + 0x30000    # func_080D3024's argument; only its 3D branch uses it
OBJECT, SCALED_OBJECT = PAYLOAD + 0x10, PAYLOAD + 0x14

# Callees of func_08114910 that phases 0x103-0x106 must not reach.
OTHER_PHASES = (0x080035A8, 0x080107D4, 0x08011040, 0x0801DCB8, 0x080D3904, 0x080D3E9C,
                0x080D3F08, 0x080D7220, 0x080D9B18, 0x080D9B64, 0x080D9BA8, 0x080E0690)
# Callees the BUGFIX build reaches in the ROM through a veneer.
FROM_ROM = (CREATE_OBJECT, 0x08011198, 0x08011058, 0x080110F8, 0x080112E8,
            0x080E0608, 0x080E064C, SET_SCALE, 0x08011428)
# Memory compared between the two builds: payload, event, pool header, slots.
REGIONS = ((PAYLOAD, 0x1A0), (EVENT, 0x1C), (POOL, 0x18), (SLOTS, SLOT_COUNT * SLOT_SIZE))


def model(k):
    """Entry k of the table: a size that falls linearly from 1 to 1/32 in 19
    steps, stored as its 8.8 reciprocal."""
    return 256 * 608 // (608 - 31 * k)


def words(values):
    return " ".join(f"{v:04X}" for v in values)


class Run:
    """One build of the function in its own machine, driven pass by pass."""

    def __init__(self, rom, fixed_obj=None):
        m = self.m = Machine(rom)
        self.unexpected = []
        self.lookups, self.scales, self.scaled_draws, self.draws = [], [], [], []
        copier, = struct.unpack_from("<I", rom, COPIER_TABLE - ROM_BASE)
        m.stub(copier, lambda m: m.uc.mem_write(m.reg(0), bytes(m.uc.mem_read(m.reg(1), m.reg(2)))))
        m.stub(DRAW_SCALED, self._draw_scaled)
        m.stub(DRAW_PLAIN, self._draw_plain)
        m.stub(START_CHILD, self._start_child)
        bindings = {f"func_{a:08X}": a for a in FROM_ROM}
        bindings[f"func_{START_CHILD:08X}"] = self._start_child
        for address in OTHER_PHASES:
            behaviour = lambda m, address=address: self.unexpected.append(f"func_{address:08X}")
            m.stub(address, behaviour)
            bindings[f"func_{address:08X}"] = behaviour
        self.entry = ADDRESS if fixed_obj is None else install_fixed(m, fixed_obj, bindings)
        m.uc.hook_add(UC_HOOK_CODE, self._set_scale, begin=SET_SCALE, end=SET_SCALE)
        m.uc.hook_add(UC_HOOK_MEM_READ, self._table_read, begin=TABLE - 0x40, end=NEXT_OBJECT + 0x40)
        m.w16(POOL, SLOT_COUNT)
        m.w32(POOL + 0x14, SLOTS)
        m.w16(EVENT, 0x103)

    def _start_child(self, m):
        m.set_reg(0, EWRAM + 0x14000)

    def _set_scale(self, uc, address, size, _):
        m = self.m
        self.scales.append((m.reg(0), m.reg(1) & 0xFFFF, m.reg(2) & 0xFFFF, m.reg(3) & 0xFFFF))

    def _table_read(self, uc, access, address, size, value, _):
        self.lookups.append((uc.reg_read(UC_ARM_REG_PC) & ~1, address, size))

    def _draw_scaled(self, m):
        # func_080018A0(frame, x, y, r3, nine stacked words): [5] x scale, [6] y scale, [7] angle
        node = m.u32(SCALED_OBJECT)
        own = node != 0 and m.u32(node + 0x18) == m.reg(0)
        self.scaled_draws.append((own, m.stack_arg(5) & 0xFFFF, m.stack_arg(6) & 0xFFFF,
                                  m.stack_arg(7) & 0xFFFF))
        self.draws.append(("scaled",) + tuple(m.reg(k) for k in range(4))
                          + tuple(m.stack_arg(k) for k in range(9)))

    def _draw_plain(self, m):
        # func_08001F34(frame, x, y, r3, seven stacked words)
        self.draws.append(("plain",) + tuple(m.reg(k) for k in range(4))
                          + tuple(m.stack_arg(k) for k in range(7)))

    phase = property(lambda self: self.m.u16(EVENT))
    counter = property(lambda self: self.m.u16(PAYLOAD))

    def step(self):
        """One pass.  Returns what the callback did and what was drawn after it."""
        m = self.m
        self.lookups, self.scales, self.scaled_draws, self.draws = [], [], [], []
        before = (self.phase, self.counter)
        result = m.call(self.entry, TASK, EVENT, PAYLOAD)
        lookups = self.lookups[:]
        m.call(UPDATE_OBJECTS)
        m.call(DRAW_WALK, WALK_ARGUMENT)
        return {"before": before, "result": result, "lookups": lookups, "scales": self.scales[:],
                "scaled_draws": self.scaled_draws[:], "draws": self.draws[:]}

    def memory(self):
        return b"".join(bytes(self.m.uc.mem_read(base, size)) for base, size in REGIONS)

    def linked(self):
        """The objects on the draw list, in order."""
        nodes, node = [], self.m.u32(DRAW_LIST)
        while node:
            nodes.append(node)
            node = self.m.u32(node + 0x3C)
        return nodes


def differing(a, b):
    """Addresses at which two memory() images differ."""
    out, offset = [], 0
    for base, size in REGIONS:
        out += [base + k for k in range(size) if a[offset + k] != b[offset + k]]
        offset += size
    return out


def main():
    rom = load_rom()
    source, fixed_obj = build_pair(rom, ADDRESS, EXTENT)
    print(f"source {source.relative_to(ROOT)}: default build == ROM bytes "
          f"[{ADDRESS:08X}, {ADDRESS + EXTENT:08X})")
    c = Checks()
    table = [struct.unpack_from("<H", rom, TABLE - ROM_BASE + 2 * k)[0] for k in range(ENTRIES)]
    after_table, = struct.unpack_from("<H", rom, NEXT_OBJECT - ROM_BASE)
    expected = [model(k) for k in range(ENTRIES)]

    print("\n1. The table data_083A39A6: 20 halfwords, 256 * 608 / (608 - 31 * k).")
    c.check("the ROM's 20 entries equal the closed form for k = 0..19", table == expected, True)
    print(f"  entries 0..19: {words(expected)}")
    c.check("the halfword after the table, at 0x083A39CE", f"{after_table:04X}", "00BF")

    # Both builds, pass by pass, from phase 0x103 until three passes into phase 0x106.
    original, fixed = Run(rom), Run(rom, fixed_obj)
    rom_passes, fix_passes, unequal = [], [], []
    while not (original.phase == 0x106 and original.counter == 7):
        rom_passes.append(original.step())
        fix_passes.append(fixed.step())
        unequal.append(differing(original.memory(), fixed.memory()))
        if len(rom_passes) == 51:
            first, scaled = original.m.u32(OBJECT), original.m.u32(SCALED_OBJECT)
            template = words(original.m.u16(scaled + k) for k in (0x32, 0x34, 0x36))
    in_phase = lambda passes, phase: [p for p in passes if p["before"][0] == phase]
    rom_spin, fix_spin = in_phase(rom_passes, 0x105), in_phase(fix_passes, 0x105)
    indexes = lambda passes: [(address - TABLE) // 2 for p in passes for _, address, _ in p["lookups"]]
    inside = lambda passes: all(TABLE <= a < NEXT_OBJECT for p in passes for _, a, _ in p["lookups"])

    print("\n2. Non-trigger: the passes before the lookups.  Phase 0x103 creates the")
    print("   first object and sets the counter to 50; phase 0x104 counts it down and,")
    print("   at 0, creates the object that phase 0x105 scales.")
    c.check("ROM / BUGFIX passes in phases 0x103 and 0x104, then (phase, counter)",
            [(len(passes[:51]), hex(passes[51]["before"][0]), passes[51]["before"][1])
             for passes in (rom_passes, fix_passes)], [(51, "0x105", 0)] * 2)
    c.check("lookups and func_080112CC calls made in those passes",
            [sum(len(p["lookups"]) + len(p["scales"]) for p in passes[:51])
             for passes in (rom_passes, fix_passes)], [0, 0])
    c.check("bytes of payload, event and object pool that differ between the builds",
            sum(unequal[:51], []), [])
    c.check("the new object's +0x32, +0x34, +0x36 (x scale, y scale, angle), from the template",
            template, "0100 0100 0000")

    print("\n3. Trigger: the twentieth pass of phase 0x105, which removes the object.")
    p = rom_spin[-1]
    c.check("ROM    (phase, counter) on entry", (hex(p["before"][0]), p["before"][1]), ("0x105", 19))
    c.check("ROM    table reads: instruction, address, bytes, inside [083A39A6, 083A39CE)",
            [(f"{pc:08X}", f"{a:08X}", n, TABLE <= a < NEXT_OBJECT) for pc, a, n in p["lookups"]],
            [(f"{LOOKUP:08X}", "083A39CE", 2, False)])
    c.check("ROM    func_080112CC(scaled object, x, y, angle)",
            [(o == scaled, words(v)) for o, *v in p["scales"]], [(True, "00BF 00BF 8000")])
    p = fix_spin[-1]
    c.check("BUGFIX (phase, counter) on entry", (hex(p["before"][0]), p["before"][1]), ("0x105", 19))
    c.check("BUGFIX table reads; func_080112CC calls",
            ([f"{a:08X}" for _, a, _ in p["lookups"]], [words(v) for _, *v in p["scales"]]), ([], []))
    for name, run, passes, left in (("ROM   ", original, rom_spin, "00BF 00BF 8000"),
                                    ("BUGFIX", fixed, fix_spin, "2000 2000 7A00")):
        p, after = passes[-1], (rom_passes if run is original else fix_passes)[71]
        c.check(f"{name} return value; then (phase, counter)",
                (p["result"], hex(after["before"][0]), after["before"][1]), (0, "0x106", 10))
        c.check(f"{name} payload->object, payload->scaled_object, objects on the draw list",
                (run.m.u32(OBJECT), run.m.u32(SCALED_OBJECT), run.linked()), (0, 0, []))
        c.check(f"{name} state bytes of the two objects; sprites drawn after this pass",
                (run.m.u8(first), run.m.u8(scaled), len(p["draws"])), (0, 0, 0))
        c.check(f"{name} x scale, y scale, angle left in the freed slot",
                words(run.m.u16(scaled + k) for k in (0x32, 0x34, 0x36)), left)
    c.check("bytes that differ between the builds after this pass, as offsets in the freed slot",
            [f"+0x{a - scaled:02X}" for a in unequal[70]], ["+0x32", "+0x33", "+0x34", "+0x35", "+0x37"])

    print("\n4. All of phase 0x105.  Passes 1 to 19 are the same in both builds.")
    c.check("ROM / BUGFIX passes in phase 0x105", [len(rom_spin), len(fix_spin)], [20, 20])
    c.check("ROM    counter on entry, first..last pass",
            [p["before"][1] for p in rom_spin], list(range(20)))
    c.check("ROM    table index read", indexes(rom_spin), list(range(1, 21)))
    c.check("BUGFIX table index read", indexes(fix_spin), list(range(1, 20)))
    c.check("ROM / BUGFIX every read inside the table", [inside(rom_spin), inside(fix_spin)],
            [False, True])
    c.check("ROM    x scale passed", words(s[1] for p in rom_spin for s in p["scales"]),
            words(expected[1:] + [after_table]))
    c.check("BUGFIX x scale passed", words(s[1] for p in fix_spin for s in p["scales"]),
            words(expected[1:]))
    c.check("y scale == x scale on every call, in both",
            all(s[1] == s[2] for passes in (rom_spin, fix_spin) for p in passes for s in p["scales"]),
            True)
    reads = lambda passes: [[a for _, a, _ in p["lookups"]] for p in passes[:19]]
    c.check("passes 1..19: same reads, same calls; bytes that differ between the builds",
            (reads(rom_spin) == reads(fix_spin),
             [p["scales"] for p in rom_spin[:19]] == [p["scales"] for p in fix_spin[:19]],
             len(sum(unequal[51:70], []))), (True, True, 0))

    print("\n5. What is drawn.  The draw walk runs after every pass.  Compared here is")
    print("   every word it hands the two sprite routines, on all passes of the run.")
    c.check("passes compared; passes on which the builds differ",
            (len(rom_passes), [k + 1 for k in range(len(rom_passes))
                               if rom_passes[k]["draws"] != fix_passes[k]["draws"]]), (74, []))
    drawn = {}
    for name, passes in (("ROM   ", rom_passes), ("BUGFIX", fix_passes)):
        drawn[name] = [d for p in passes for d in p["scaled_draws"]]
        c.check(f"{name} passes with a scaled draw (of 74); each is this object, y scale == x scale",
                ([k + 1 for k, p in enumerate(passes) if p["scaled_draws"]] == list(range(51, 71)),
                 all(own and x == y for own, x, y, _ in drawn[name])), (True, True))
        c.check(f"{name} x scales drawn, passes 51..70", words(d[1] for d in drawn[name]),
                words(expected))
    c.check("ROM / BUGFIX draw the 20 table entries once each, in order",
            [[d[1] for d in drawn[name]] == expected for name in drawn], [True, True])
    c.check("ROM    draws 00BF on any pass",
            after_table in [d[1] for d in drawn["ROM   "]], False)
    c.check("ROM    angles drawn (the BUGFIX build's are among the words compared above)",
            words(d[3] for d in drawn["ROM   "]),
            "0000 0600 0D00 1300 1A00 2000 2600 2D00 3300 3A00 "
            "4000 4600 4D00 5300 5A00 6000 6600 6D00 7300 7A00")
    print("   The ROM's allocator rebuilds a freed slot from its template (ROM machine):")
    reused = [original.m.call(CREATE_OBJECT, RESOURCE, 3, 120, 80, 0x388, 9, 0, 0) for _ in range(2)]
    c.check("two new objects take the two freed slots", reused == [first, scaled], True)
    c.check("x and y scale in the slot that held 00BF",
            words(original.m.u16(scaled + k) for k in (0x32, 0x34)), "0100 0100")

    print("\n6. Non-trigger: single passes of other phases.")
    for label, phase, counter in (("phase 0x104, counter 2", 0x104, 2),
                                  ("phase 0x106, counter 3", 0x106, 3)):
        results = []
        for build in (None, fixed_obj):
            run = Run(rom, build)
            run.step()                               # phase 0x103: creates the first object
            run.m.w16(EVENT, phase)
            run.m.w16(PAYLOAD, counter)
            p = run.step()
            results.append((run, (p["result"], hex(run.phase), run.counter,
                                  len(p["lookups"]) + len(p["scales"]))))
        (a, got_a), (b, got_b) = results
        want = (0, hex(phase), counter - 1, 0)
        c.check(f"{label}: ROM / BUGFIX (return, phase, counter, lookups + calls)",
                (got_a, got_b), (want, want))
        c.check(f"{label}: bytes that differ between the builds; other-phase callees reached",
                (differing(a.memory(), b.memory()), a.unexpected + b.unexpected), ([], []))
    c.check("other-phase callees reached in the main runs", original.unexpected + fixed.unexpected, [])
    c.finish()


if __name__ == "__main__":
    main()
