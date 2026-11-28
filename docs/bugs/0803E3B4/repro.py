#!/usr/bin/env python3
"""Behavioural case for func_0803E3B4: paying a list-item cost clears every copy.

    python3 docs/bugs/0803E3B4/repro.py [path/to/baserom.bin]

Runs the ORIGINAL function bytes from your ROM and the -DBUGFIX build of
src/**/0803E3B4.c under a Thumb emulator, from the same memory states, in
state 10, the state that takes a row's cost.  A row of g_table_08564670
costs `count` copies of an item.  For the two item lists (ids from 0x178 up,
and ids with bit 0x4000) the ROM counts the copies held and then passes that
number, not the row's count, as the limit to the remover (func_080385A8 /
func_080386C8, run from the ROM): every copy found goes, while the message
and the plain-item branch use the row's count.  The BUGFIX build removes the
row's count.

Sections 1-2 use the two shipped rows that reach this code (44 and 46, one
copy each) with the player holding two and three copies.  Whether the game
can give the player two copies of those items is not established (see
README.md).  Section 3 adds a copy attached to a record, which both builds
remove before a free one.  Sections 4-6 are non-trigger states (one copy;
none; the plain-item sibling branch) where both builds agree.  Sections 7-8
put a synthetic row in the emulated ROM for the bit-0x4000 branch, which no
shipped row reaches.  Exits 0 when every assertion holds.

Dependencies
  * Python 3.8+ and unicorn (`pip install unicorn`; tested with 2.1.4).
  * The repository toolchain, as tools/match.py runs it: cpp,
    $HOME/agbcc/gcc/agbcc (override with AGBCC) and arm-none-eabi-as
    (override with CPP / AS).
  * Your ROM: argv[1], default <repo root>/baserom.bin.  No ROM bytes ship
    with this file.  FFTA_ROOT overrides the repository root.

ROM code that runs unchanged: func_080385E4 and func_080385A8 (count and
remove copies in the 64-entry list at g_state_02000000+0x2B08),
func_08038704 and func_080386C8 (the same for the 20 halfwords at +0x1F3C),
func_080CB2B4 and func_080CA9E8 (count and remove a plain item in the bank
g_state_02001940), the row table g_table_08564670 and the label table
data_085668B0.

Stubs (each entry is replaced by `bx lr` plus a Python behaviour):
  * func_0803E1C0 (the "handed over" message): records (id, count, label,
    kind).
  * func_08031708, func_08013364, func_0803E078, func_08141540,
    func_0808A604, func_08011C60: logged.
  * Every other callee, and __modsi3: records the call; the case asserts
    none is reached.
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
ADDRESS, EXTENT = 0x0803E3B4, 4764
MENU = 0x03002810                          # g_state_03002810: the MenuContext pointer
CONTEXT, WINDOW = EWRAM + 0x30000, EWRAM + 0x31000
SLOT_STATE = CONTEXT + 0x984 + 3           # slots[0].state
NEXT, REFRESH = 0x0201F498, 0x0201F499     # data_0201F498 (next state), data_0201F499
RENDERER_5 = 0x030009E0 + 5 * 0x4C + 5     # data_030009E0[5].enabled
SAVE = EWRAM                               # g_state_02000000
VALUES = SAVE + 0x1F3C                     # 20 u16: the bit-0x4000 list
LIST = SAVE + 0x2B08                       # 64 x {u8 id, u8, u16 holder}: the >=0x178 list
BANK = 0x02001940                          # g_state_02001940: {u16 id, u8 quantity, u8 in use}
TABLE, ROW = 0x08564670, 27
LABELS = 0x085668B0
MODSI3 = 0x08142950
SYNTHETIC = 200                            # a row index past the table's 124 rows
NATIVE = {"func_080385E4": 0x080385E4, "func_080385A8": 0x080385A8,
          "func_08038704": 0x08038704, "func_080386C8": 0x080386C8,
          "func_080CB2B4": 0x080CB2B4, "func_080CA9E8": 0x080CA9E8}
LOGGED = ("func_08031708", "func_08013364", "func_0803E078", "func_08141540",
          "func_0808A604", "func_08011C60")
PAID = ["func_08031708", "func_08013364", "func_0803E078", "func_0803E1C0",
        "func_08141540", "func_0808A604"]
_config_symbols = data_symbols


def data_symbols():
    """The harness's symbol table plus the runtime's __modsi3 (case 26/27's %)."""
    return {**_config_symbols(), "__modsi3": MODSI3}


def row(rom, index):
    item, count, reward = struct.unpack_from("<HBH", rom, TABLE - ROM_BASE + ROW * index + 7)
    return item, count, reward


def behaviours(fixed_obj):
    def logged(name):
        return lambda m: m.log.append(name)

    def message(m):
        m.log.append("func_0803E1C0")
        m.messages.append((hex(m.reg(0) & 0xFFFF), m.reg(1) & 0xFF, hex(m.reg(2)), m.reg(3)))

    def unreached(name):
        def stub(m):
            m.log.append(("UNREACHED", name))
            m.set_reg(0, 0)
        return stub
    table = {name: unreached(name) for _, _, name, local in fixed_obj[1]
             if (name.startswith("func_") or name == "__modsi3") and not local}
    table.update({name: logged(name) for name in LOGGED})
    table["func_0803E1C0"] = message
    for name in NATIVE:
        table.pop(name, None)
    return table


def machines(rom, fixed_obj):
    table = behaviours(fixed_obj)
    original = Machine(rom)
    for name, behaviour in table.items():
        original.stub(address_of(name, {"__modsi3": MODSI3}), behaviour)
    fixed = Machine(rom)
    entry = install_fixed(fixed, fixed_obj, {**table, **NATIVE})
    return (original, ADDRESS), (fixed, entry)


def prepare(m, selector, copies=None, values=None, bank=None, synthetic=None):
    """State 10 on row `selector`, with the given list entries and bank records."""
    m.log, m.messages = [], []
    m.uc.mem_write(SAVE, bytes(0x3000))
    m.uc.mem_write(CONTEXT, bytes(0xC10))
    m.uc.mem_write(WINDOW, bytes(0x100))
    m.w32(MENU, CONTEXT)
    m.w32(CONTEXT + 4, WINDOW)
    m.w8(WINDOW + 0xA8, selector)
    m.w8(SLOT_STATE, 10)
    m.w8(NEXT, 0)
    m.w8(REFRESH, 0)
    m.w8(RENDERER_5, 0)
    for index, (identifier, holder) in (copies or {}).items():
        m.w8(LIST + 4 * index, identifier)
        m.w16(LIST + 4 * index + 2, holder)
    for index, value in (values or {}).items():
        m.w16(VALUES + 2 * index, value)
    for index, (identifier, quantity) in (bank or {}).items():
        m.w16(BANK + 4 * index, identifier)
        m.w8(BANK + 4 * index + 2, quantity)
    if synthetic is not None:              # item, count; no reward, no flags
        m.uc.mem_write(TABLE + ROW * SYNTHETIC, bytes(ROW))
        m.uc.mem_write(TABLE + ROW * SYNTHETIC + 7, struct.pack("<HB", *synthetic))


def pay(m, entry):
    """func_0803E3B4(0) once, in state 10."""
    m.call(entry, 0)
    return {"list": {k: (hex(m.u8(LIST + 4 * k)), m.u16(LIST + 4 * k + 2))
                     for k in range(64) if m.u8(LIST + 4 * k)},
            "values": {k: hex(m.u16(VALUES + 2 * k)) for k in range(20) if m.u16(VALUES + 2 * k)},
            "bank": {k: (hex(m.u16(BANK + 4 * k)), m.u8(BANK + 4 * k + 2))
                     for k in range(0x177) if m.u16(BANK + 4 * k)},
            "next": hex(m.u8(NEXT)), "slot state": m.u8(SLOT_STATE),
            "renderer 5": m.u8(RENDERER_5), "messages": m.messages,
            "calls": [c for c in m.log if not isinstance(c, tuple)],
            "unreached": [c for c in m.log if isinstance(c, tuple)]}


def run_both(rom, fixed_obj, **state):
    results = []
    for m, entry in machines(rom, fixed_obj):
        prepare(m, **state)
        results.append(pay(m, entry))
    return results


def show(results, keys=("list",)):
    for label, result in zip(("ROM   ", "BUGFIX"), results):
        print(f"   {label} " + "; ".join(f"{k} {result[k]}" for k in keys)
              + f"; message {result['messages']}; next {result['next']}")


def main():
    rom = load_rom()
    source, fixed_obj = build_pair(rom, ADDRESS, EXTENT)
    print(f"source {source.relative_to(ROOT)}: default build == ROM bytes "
          f"[{ADDRESS:08X}, {ADDRESS + EXTENT:08X})")
    c = Checks()
    label = hex(struct.unpack_from("<I", rom, LABELS - ROM_BASE + 4 * 47)[0])
    c.check("row 46 costs item 0x1AB (list item 0x34) x1", row(rom, 46)[:2], (0x1AB, 1))
    c.check("row 44 costs item 0x1EE (list item 0x77) x1", row(rom, 44)[:2], (0x1EE, 1))
    c.check("row 42 costs plain item 0x177 x1", row(rom, 42)[:2], (0x177, 1))
    c.check("no row 0-123 costs an item of the bit-0x4000 list (0x4000-0x7FFF)",
            [k for k in range(124) if 0x4000 <= row(rom, k)[0] <= 0x7FFF], [])
    c.check("rows 0-123 with a >=0x178 list cost", [k for k in range(124) if 0x178 <= row(rom, k)[0] <= 0x3FFF],
            [44, 46])

    def paid(result, message):
        return {"next": result["next"], "slot state": result["slot state"], "renderer 5": result["renderer 5"],
                "messages": [message], "calls": PAID, "unreached": []}

    def keys(result):
        return {k: result[k] for k in ("next", "slot state", "renderer 5", "messages", "calls", "unreached")}

    print("\n1. Trigger: row 46 (one copy of list item 0x34); the player holds two free copies")
    print("   (entries 3 and 10), and one copy each of 0x77 and 0x12.")
    copies = {0: (0x77, 0), 3: (0x34, 0), 5: (0x12, 0), 10: (0x34, 0)}
    rom_result, fixed_result = run_both(rom, fixed_obj, selector=46, copies=copies)
    show((rom_result, fixed_result))
    for name, result in (("ROM   ", rom_result), ("BUGFIX", fixed_result)):
        c.check(f"{name} pays: message (0x34, 1, label 47, kind 1), next state 0x14, slot state 2",
                keys(result), paid(result, ("0x34", 1, label, 1)))
    c.check("ROM    clears both copies of 0x34", rom_result["list"], {0: ("0x77", 0), 5: ("0x12", 0)})
    c.check("BUGFIX clears one (the first, entry 3)", fixed_result["list"],
            {0: ("0x77", 0), 5: ("0x12", 0), 10: ("0x34", 0)})

    print("\n2. Trigger: row 44 (one copy of list item 0x77); the player holds three (entries 1, 2, 9).")
    copies = {1: (0x77, 0), 2: (0x77, 0), 4: (0x34, 0), 9: (0x77, 0)}
    rom_result, fixed_result = run_both(rom, fixed_obj, selector=44, copies=copies)
    show((rom_result, fixed_result))
    for name, result in (("ROM   ", rom_result), ("BUGFIX", fixed_result)):
        c.check(f"{name} pays: message (0x77, 1, label 47, kind 1)", keys(result),
                paid(result, ("0x77", 1, label, 1)))
    c.check("ROM    clears all three copies of 0x77", rom_result["list"], {4: ("0x34", 0)})
    c.check("BUGFIX clears one", fixed_result["list"], {2: ("0x77", 0), 4: ("0x34", 0), 9: ("0x77", 0)})

    print("\n3. Trigger with an attached copy: row 46; entry 2 holds 0x34 attached to record 0x11,")
    print("   entries 7 and 12 hold free copies.  func_080385E4 counts 2; the remover tests only the id.")
    copies = {2: (0x34, 0x11), 7: (0x34, 0), 12: (0x34, 0)}
    rom_result, fixed_result = run_both(rom, fixed_obj, selector=46, copies=copies)
    show((rom_result, fixed_result))
    c.check("ROM    clears the first two entries in table order (2, attached; 7) and keeps 12",
            rom_result["list"], {12: ("0x34", 0)})
    c.check("BUGFIX clears one entry, also the attached one (2)", fixed_result["list"],
            {7: ("0x34", 0), 12: ("0x34", 0)})
    c.check("both pay the same way", keys(rom_result), keys(fixed_result))

    cases = [("4. Non-trigger: row 46 and exactly one copy (entry 6)",
              dict(selector=46, copies={0: (0x77, 0), 6: (0x34, 0)}),
              {"list": {0: ("0x77", 0)}, "messages": [("0x34", 1, label, 1)], "next": "0x14"}),
             ("5. Non-trigger: row 46 and no copy of 0x34: the 'not enough' path",
              dict(selector=46, copies={0: (0x77, 0)}),
              {"list": {0: ("0x77", 0)}, "messages": [], "next": "0x11", "calls": ["func_08013364"]}),
             ("6. Non-trigger, the plain-item sibling: row 42 (item 0x177 x1), five held",
              dict(selector=42, bank={0x169: (0x177, 5)}),
              {"bank": {0x169: ("0x177", 4)}, "messages": [("0x177", 1, label, 0)], "next": "0x14"})]
    for title, state, want in cases:
        print(f"\n{title}.")
        results = run_both(rom, fixed_obj, **state)
        show(results, keys=tuple(k for k in ("list", "bank") if k in want))
        c.check("ROM and BUGFIX: identical stores, calls and messages", results[0], results[1])
        c.check("as expected", {k: results[0][k] for k in want}, want)

    print(f"\n7. Synthetic row {SYNTHETIC} (not in the shipped table): it costs item 0x40B1 x1, the")
    print("   bit-0x4000 branch; the halfword list holds 0x40B1 twice (entries 2 and 5).")
    rom_result, fixed_result = run_both(rom, fixed_obj, selector=SYNTHETIC, synthetic=(0x40B1, 1),
                                        values={0: 0x0012, 2: 0x40B1, 5: 0x40B1})
    show((rom_result, fixed_result), keys=("values",))
    for name, result in (("ROM   ", rom_result), ("BUGFIX", fixed_result)):
        c.check(f"{name} pays: message (0x40b1, 1, label 47, kind 2)", keys(result),
                paid(result, ("0x40b1", 1, label, 2)))
    c.check("ROM    clears both", rom_result["values"], {0: "0x12"})
    c.check("BUGFIX clears one", fixed_result["values"], {0: "0x12", 5: "0x40b1"})

    print(f"\n8. Non-trigger, synthetic row {SYNTHETIC} again: the list holds 0x00B1, the form in which")
    print("   state 12 stores a reward of 0x40B1 (id & 0xFFF); the cost looks for 0x40B1.")
    results = run_both(rom, fixed_obj, selector=SYNTHETIC, synthetic=(0x40B1, 1), values={2: 0x00B1})
    show(results, keys=("values",))
    c.check("ROM and BUGFIX: identical", results[0], results[1])
    c.check("count 0: the 'not enough' path, nothing cleared",
            {k: results[0][k] for k in ("values", "next", "messages")}, {"values": {2: "0xb1"}, "next": "0x11",
                                                                        "messages": []})
    c.finish()


if __name__ == "__main__":
    main()
