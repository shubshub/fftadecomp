#!/usr/bin/env python3
"""Behavioural case for func_080922CC: the first heading of a camera pan is
taken from |dx| and |dy|, so it always points into the first quadrant.

    python3 docs/bugs/080922CC/repro.py [path/to/baserom.bin]

Runs the ORIGINAL function bytes from your ROM and the -DBUGFIX build of
src/**/080922CC.c under a Thumb emulator from the same memory states, then
steps each pan with the ROM's own updater (func_08092390, which calls the
motion stepper func_08007AD0) until it arrives.  Exits 0 when every assertion
holds.

Dependencies
  * Python 3.8+ and unicorn (`pip install unicorn`; tested with 2.1.4).
  * The repository toolchain, as tools/match.py runs it: cpp,
    $HOME/agbcc/gcc/agbcc (override with AGBCC) and arm-none-eabi-as
    (override with CPP / AS).
  * Your ROM: argv[1], default <repo root>/baserom.bin.  No ROM bytes ship
    with this file.  FFTA_ROOT overrides the repository root.

Stubs (each callee entry is replaced by `bx lr` plus a Python behaviour):
  * func_0801C918 (map -> screen projection) writes the screen point the
    case asks for into its three outputs.
  * func_08141860 is BIOS ArcTan2 (svc 0x0A), which unicorn does not have.
    The stub returns round(atan2(y, x) * 0x8000 / pi) & 0xFFFF.  It is exact
    on the four axes, which is where the assertions on headings sit; the
    other comparisons are original-against-BUGFIX through the same stub.
  * func_0801E5E0 (set the camera) stores the camera position at
    0x02007F64/0x02007F66, where func_0801E6F0 reads it, and records it.
Everything else runs from the ROM: func_0801E6F0, func_08092390,
func_08007AD0, the sine/cosine readers func_08007A4C/func_08007A60 and the
divide at func_081426B8.
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
import math

ADDRESS, EXTENT = 0x080922CC, 194
UPDATE = 0x08092390                # func_08092390(state): one step; 0 once arrived
STATE = 0x0200F4C0                 # data_0200F4C0, the state every caller passes
CAMERA = 0x02007F40                # camera x at +0x24, y at +0x26
PROJECT, ARCTAN2, SET_CAMERA = 0x0801C918, 0x08141860, 0x0801E5E0
OFFSET_X, OFFSET_Y, DIVISOR = -120, -86, 4     # what all four callers pass
START = (100, 80)                  # camera position when the pan is set up


def arctan2(m):
    x = m.reg(0) - 0x100000000 if m.reg(0) & 0x80000000 else m.reg(0)
    y = m.reg(1) - 0x100000000 if m.reg(1) & 0x80000000 else m.reg(1)
    m.set_reg(0, round(math.atan2(y, x) * 0x8000 / math.pi) & 0xFFFF)


def project(m):
    # func_0801C918(x, y, z, s16 *screen_x, s16 *screen_y, s16 *depth)
    m.w16(m.reg(3), m.screen[0])
    m.w16(m.stack_arg(0), m.screen[1])
    m.w16(m.stack_arg(1), 0)


def set_camera(m):
    m.w16(CAMERA + 0x24, m.reg(0))
    m.w16(CAMERA + 0x26, m.reg(1))
    m.camera_path.append((m.s16(CAMERA + 0x24), m.s16(CAMERA + 0x26)))


def machine(rom, fixed_obj=None):
    m = Machine(rom)
    m.stub(ARCTAN2, arctan2)
    m.stub(PROJECT, project)
    m.stub(SET_CAMERA, set_camera)
    entry = ADDRESS
    if fixed_obj is not None:
        entry = install_fixed(m, fixed_obj, {"func_0801C918": project,
                                             "func_0801E6F0": 0x0801E6F0,
                                             "func_08141860": arctan2})
    return m, entry


def pan(m, entry, dx, dy, turn_percent, steps=600):
    """Sets up a pan to camera + (dx, dy) and steps it to the end.  Returns
    the heading right after set-up, the per-step (x, y, heading) and the
    camera positions written."""
    for k in range(0, 0x28, 4):
        m.w32(STATE + k, 0)
    m.w16(CAMERA + 0x24, START[0])
    m.w16(CAMERA + 0x26, START[1])
    m.camera_path = []
    m.screen = (START[0] + dx - OFFSET_X, START[1] + dy - OFFSET_Y)
    m.call(entry, STATE, 0, 0, 0, OFFSET_X, OFFSET_Y, DIVISOR, turn_percent)
    first = m.s32(STATE + 0x10)
    path = []
    for _ in range(steps):
        if not m.call(UPDATE, STATE):
            break
        path.append((m.s32(STATE + 8) >> 8, m.s32(STATE + 12) >> 8, m.s32(STATE + 0x10)))
    return first, path, m.camera_path


def off_line(path, dx, dy):
    """Largest distance, in pixels, of the path from the straight line."""
    length = math.hypot(dx, dy)
    return max(abs((x - START[0]) * dy - (y - START[1]) * dx) / length for x, y, _ in path)


def main():
    rom = load_rom()
    source, fixed_obj = build_pair(rom, ADDRESS, EXTENT)
    print(f"source {source.relative_to(ROOT)}: default build == ROM bytes "
          f"[{ADDRESS:08X}, {ADDRESS + EXTENT:08X})")
    original = machine(rom)
    fixed = machine(rom, fixed_obj)
    # func_0801E6F0 runs from the ROM in both: the BUGFIX build's call to it
    # is bound to the ROM function, not to a stub.
    c = Checks()

    print("\n1. Set-up heading (0..255, 64 = +y), target 40 px from the camera:")
    for name, dx, dy, rom_heading, true_heading in (
            ("right", 40, 0, 0, 0), ("down", 0, 40, 64, 64),
            ("left", -40, 0, 0, 128), ("up", 0, -40, 64, 192)):
        got = pan(original[0], original[1], dx, dy, 100, steps=0)[0]
        want = pan(fixed[0], fixed[1], dx, dy, 100, steps=0)[0]
        c.check(f"{name:5} ROM / BUGFIX", (got, want), (rom_heading, true_heading))

    print("\n2. The game: every caller passes turn_percent 100.  The first step")
    print("   replaces the heading before it moves the camera, so the ROM and the")
    print("   BUGFIX pans are identical step for step, in every direction:")
    for dx, dy in ((40, 0), (40, 40), (0, 40), (-40, 40), (-40, 0), (-40, -40),
                   (0, -40), (40, -40), (-37, 23), (51, -9), (-5, -60), (90, -70)):
        a = pan(original[0], original[1], dx, dy, 100)
        b = pan(fixed[0], fixed[1], dx, dy, 100)
        same = a[1] == b[1] and a[2] == b[2]
        c.check(f"({dx:4},{dy:4}) set-up heading {a[0]:3} vs {b[0]:3}; "
                f"{len(a[1]):3} steps, camera paths equal", same, True)

    print("\n3. Trigger (no caller does this): turn_percent 50, target 40 px left.")
    a = pan(original[0], original[1], -40, 0, 50)
    b = pan(fixed[0], fixed[1], -40, 0, 50)
    c.check("first step heading ROM / BUGFIX", (a[1][0][2], b[1][0][2]), (64, 128))
    c.check("first step position ROM (moves down, not left)", a[1][0][:2], (100, 82))
    c.check("first step position BUGFIX (moves left)", b[1][0][:2], (98, 80))
    c.check("ROM path leaves the straight line (> 1 px)", off_line(a[1], -40, 0) > 1, True)
    c.check("BUGFIX path stays on it, px", off_line(b[1], -40, 0), 0.0)
    c.check("ROM pan takes more steps", len(a[1]) > len(b[1]), True)
    print(f"  ROM: {len(a[1])} steps, up to {off_line(a[1], -40, 0):.0f} px off the line; "
          f"BUGFIX: {len(b[1])} steps, on the line")

    print("\n4. Non-trigger at turn_percent 50: target down and right (+30, +20).")
    a = pan(original[0], original[1], 30, 20, 50)
    b = pan(fixed[0], fixed[1], 30, 20, 50)
    c.check("set-up heading equal", a[0] == b[0], True)
    c.check("camera paths equal", a[1] == b[1] and a[2] == b[2], True)
    c.finish()


if __name__ == "__main__":
    main()
