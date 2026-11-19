#!/usr/bin/env python3
"""Behavioural case for func_08148914: the priority-tree walks visit a node
again when they climb back from its left child.

    python3 docs/bugs/08148914/repro.py [path/to/baserom.bin]

Builds trees with the ROM's own inserter (func_08148860, after the ROM's
reset func_08148830), then runs the ORIGINAL func_08148914 from your ROM and
the -DBUGFIX build of src/**/08148914.c under a Thumb emulator on the same
tree, and compares the shares and the func_08148B60 dispatches with an
independent model: a recursive right-node-left walk that visits each node
once.  Exits 0 when every assertion holds.

Dependencies
  * Python 3.8+ and unicorn (`pip install unicorn`; tested with 2.1.4).
  * The repository toolchain, as tools/match.py runs it: cpp,
    $HOME/agbcc/gcc/agbcc (override with AGBCC) and arm-none-eabi-as
    (override with CPP / AS).
  * Your ROM: argv[1], default <repo root>/baserom.bin.  No ROM bytes ship
    with this file.  FFTA_ROOT overrides the repository root.

Stubs (each callee entry is replaced by `bx lr` plus a Python behaviour):
  * func_08148B60 (runs an object's script for `share` steps, -1 = no
    limit) only records (object, value_08, share as s8, value_0C).
Everything else runs from the ROM: func_08148830, func_08148860, the
done-test func_08149368 it calls, and func_0809A5E0 in the game case.
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

ADDRESS, EXTENT = 0x08148914, 242
TREE = 0x03005F30                  # g_state_03005F30: PriorityNode nodes[16]; root at +0x1C0
RESET, INSERT, DISPATCH = 0x08148830, 0x08148860, 0x08148B60
ADD_AND_RUN = 0x0809A5E0           # func_0809A5E0(owner, amount, context): the only caller
SCRIPT_CALLBACK = 0x08097815       # func_08097814, the value_08 func_0809A5E0 passes
OBJECTS = EWRAM + 0x10000          # objects: 0x990 bytes, category byte at +0x980
OWNER, CONTEXT = EWRAM + 0x30000, EWRAM + 0x30100


def obj(k):
    return OBJECTS + 0x990 * k


def record_dispatch(m):
    share = m.reg(2) & 0xFF
    m.dispatched.append((m.reg(0), m.reg(1), share - 0x100 if share & 0x80 else share, m.reg(3)))


def machine(rom, fixed_obj=None):
    m = Machine(rom)
    m.stub(DISPATCH, record_dispatch)
    entry = ADDRESS
    if fixed_obj is not None:
        entry = install_fixed(m, fixed_obj, {"func_08148B60": record_dispatch})
    return m, entry


def build(m, priorities):
    """Empties the tree and inserts object k with priorities[k], in order."""
    m.call(RESET)
    for k, priority in enumerate(priorities):
        m.w8(obj(k) + 0x980, 0)
        m.call(INSERT, obj(k), priority, 0x1000 + k, 0x2000 + k)


def walk(m, entry, priorities, amount):
    build(m, priorities)
    m.dispatched = []
    m.call(entry, amount)
    shares = [m.s16(TREE + 0x1C * k + 6) for k in range(len(priorities))]
    calls = [(o, share) for o, _, share, _ in m.dispatched]
    return shares, [((o - OBJECTS) // 0x990, s) for o, s in calls]


def model(priorities, amount):
    """The intended walk: highest priority first, each node visited once."""
    nodes = [{"p": p, "v": 0, "l": None, "r": None} for p in priorities]
    for k in range(1, len(nodes)):
        at = 0
        while True:
            side = "l" if nodes[at]["p"] >= nodes[k]["p"] else "r"
            if nodes[at][side] is None:
                nodes[at][side] = k
                break
            at = nodes[at][side]
    def order(k):
        if k is None:
            return []
        return order(nodes[k]["r"]) + [k] + order(nodes[k]["l"])
    budget = amount
    stop = False
    while budget > 0 and not stop:
        remaining = budget
        for k in order(0):
            if nodes[k]["p"] > 254:
                nodes[k]["v"] = -1
                stop = True
                break
            nodes[k]["v"] += nodes[k]["p"]
            remaining -= nodes[k]["p"]
            if remaining <= 0:
                stop = True
                break
        budget = remaining
    shares = [n["v"] for n in nodes]
    calls = [(k, (shares[k] + 0x80 & 0xFF) - 0x80) for k in order(0) if shares[k]]
    return shares, calls


def main():
    rom = load_rom()
    source, fixed_obj = build_pair(rom, ADDRESS, EXTENT)
    print(f"source {source.relative_to(ROOT)}: default build == ROM bytes "
          f"[{ADDRESS:08X}, {ADDRESS + EXTENT:08X})")
    original = machine(rom)
    fixed = machine(rom, fixed_obj)
    c = Checks()

    print("\n1. The game: func_08096E78 empties the tree, then one script step calls")
    print("   func_0809A5E0 once (amount 1, priority 0xFF).  One node, one dispatch.")
    m = original[0]
    m.call(RESET)
    m.w32(OWNER + 0x1C, obj(0))
    m.w8(obj(0) + 0x980, 0)
    m.dispatched = []
    m.call(ADD_AND_RUN, OWNER, 1, CONTEXT)
    c.check("ROM func_0809A5E0 dispatches (object, value_08, share, value_0C)",
            [(hex(o), hex(v8), s, hex(vc)) for o, v8, s, vc in m.dispatched],
            [(hex(obj(0)), hex(SCRIPT_CALLBACK), -1, hex(CONTEXT))])
    c.check("ROM walk / BUGFIX walk on that tree",
            (walk(*original, [0xFF], 1), walk(*fixed, [0xFF], 1)),
            (([-1], [(0, -1)]), ([-1], [(0, -1)])))

    print("\n2. Trigger (the game never does this): two func_0809A5E0 calls with no")
    print("   reset between them.  Both nodes have priority 0xFF, so the second goes")
    print("   left of the first; the first walk stops at the root (priority > 254).")
    got, want = walk(*original, [0xFF, 0xFF], 1), walk(*fixed, [0xFF, 0xFF], 1)
    c.check("ROM    shares, dispatches", got, ([-1, 0], [(0, -1), (0, -1)]))
    c.check("BUGFIX shares, dispatches", want, ([-1, 0], [(0, -1)]))
    c.check("model  shares, dispatches", model([0xFF, 0xFF], 1), want)

    print("\n3. Trigger in the first walk too: priorities A 4 (root), B 8 (right),")
    print("   C 2 (left), amount 20.  A is charged again when the walk climbs back")
    print("   from C, and dispatched twice.")
    got, want = walk(*original, [4, 8, 2], 20), walk(*fixed, [4, 8, 2], 20)
    c.check("ROM    shares, dispatches", got, ([8, 16, 2], [(1, 16), (0, 8), (2, 2), (0, 8)]))
    c.check("BUGFIX shares, dispatches", want, ([4, 16, 2], [(1, 16), (0, 4), (2, 2)]))
    c.check("model  shares, dispatches", model([4, 8, 2], 20), want)

    print("\n4. Non-trigger: no node has a left child (priorities rising: each new")
    print("   node goes right).  Both agree with the model.")
    for priorities, amount in (([3, 5, 9], 40), ([1, 2, 3, 4], 7)):
        got, want = walk(*original, priorities, amount), walk(*fixed, priorities, amount)
        c.check(f"{priorities} amount {amount}: ROM == BUGFIX == model",
                got == want == model(priorities, amount), True)

    print("\n5. 300 seeded random trees (2-8 nodes, priorities 1-60 or 0xFF):")
    rng = random.Random(0x08148914)
    agree = differ = 0
    for _ in range(300):
        n = rng.randint(2, 8)
        priorities = [rng.choice([0xFF] + list(range(1, 61))) for _ in range(n)]
        amount = rng.randint(1, 255)
        got, want = walk(*original, priorities, amount), walk(*fixed, priorities, amount)
        expected = model(priorities, amount)
        agree += want == expected
        differ += got != want
    c.check("BUGFIX equals the model on all 300", agree, 300)
    print(f"  the ROM walk differs from it on {differ} of them")
    c.check("the ROM walk differs on some", differ > 0, True)
    c.finish()


if __name__ == "__main__":
    main()
