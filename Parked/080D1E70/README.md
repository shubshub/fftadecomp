# 080D1E70 — parked recovery

This is a plausible, behavior-tested recovery, **not a byte match**. No active
source, private header or match report is installed for this address.

## Complete symbol and discrepancy

The actual ROM body is `[0x080D1E70, 0x080D2114)`: 676 bytes containing 280
reachable instructions, 590 code bytes, 18 literal words (72 bytes), and 14
internal zero-alignment bytes. There is no jump table or local long-BL branch.
The next function starts at `0x080D2114`; no external alignment is included.
The seven internal zero halfwords start at `0x080D1EEE`, `0x080D1F8E`,
`0x080D200E`, `0x080D202A`, `0x080D207E`, `0x080D20D2`, and `0x080D210A`.

ROM SHA-256:
`ee937e27d947054db845fe02777d753dce7152b40aa02f57c2a2dd141c29f634`.

The retained source emits exactly one ELF `STT_FUNC`, with the complete
`.text` and function symbol both 620 bytes: 258 reachable instructions,
546 code bytes, 15 literal words (60 bytes), and 14 alignment bytes. Normal
typed linking resolves every call/data relocation; no helper text or unresolved
relocation remains. Linked candidate SHA-256:
`b2fa8cb9a37845520fbda992b2dd469a22ad2664142cde646d7efc4d39e07424`.

Only 94 of the 676 target byte positions agree: 526 overlapping positions
differ and the final 56 target positions are absent. There are 21 identical
instructions at the same address, not an instruction-alignment score. The
frozen `2e2a664` official verifier correctly rejects the entire symbol:

```text
compiled symbol is shorter than the indexed span: 620 < 676
```

Both complete bodies independently pass the existing structural framed-call
CFG check, and the candidate's named data literals pass their binding check.
These structural checks do not override the failed full-symbol comparison or
prove opaque callees. Source/header plausibility passes.

## Natural forms tried

1. A byte-pointer record interface, ordinary indexed two-entry loop, and
   ordinary inline identifier lookup/node-removal helpers produce the retained
   620-byte body.
2. A grounded local bitfield view for the terminal category update produces
   628 bytes, still short. It was not retained because the byte view is simpler
   and does not add that typed record/alignment requirement.

The remaining mismatch includes different register allocation and loop address
calculations, four rather than eight local stack bytes, and fewer literal words.
The candidate uses signed-byte loads where the ROM loads a byte and explicitly
sign-extends it. It keeps the `0x5FF` threshold in a register rather than
reloading the ROM's repeated literals. Its terminal mask uses `0xE3`, whereas
the ROM constructs `-0x1D`. Branch/literal placement consequently differs.
No artificial locals, alternate compiler flags, forced registers, alignment,
assembly, volatile accesses or control-flow scaffolding were introduced to
recover those bytes. This is a bounded local code-generation mismatch, not a
claim that the function is inherently unmatchable.

## Recovered contract and order

The compatible interface is `void func_080D1E70(u8 *record, u16 enabled)`.
Only the record pointer and low 16 bits of the second argument are consumed;
there are no observed incoming stack arguments. The ROM saves 32 bytes and
allocates eight local bytes. No meaningful return value is established. These
observations do not uniquely establish original nominal types or the absence
of unused original parameters.

- Decode the ten-bit identifier from record bytes `0x00`/`0x01` and retain its
  original 70-byte definition at `g_table_0855AE4C`. A nonzero low-16 enable
  value first sets bit `identifier + 0x2FF`.
- Process two ascending definition adjustments. Nonzero enable chooses entries
  0/1; zero chooses 2/3. Entries start at `0x12`, stride four: two-byte index,
  operation byte, signed amount byte. Index values above `0x5FF` select counters
  after subtracting `0x600` and narrowing to `u16`.
- Operation 1 reads the counter before the signed amount, adds them, narrows
  to `u16` **before** the upper cap of 255, then stores the low byte. A negative
  sum therefore wraps and caps to 255, not zero. Operation 2 uses a signed
  comparison, conditionally subtracts, and stores the low byte without that
  cap. Operation 3 assigns the amount byte directly for counters; for lower
  indices it sets/clears a bit. Other operations, and low-index operations
  1/2, have no adjustment effect.
- After an operation-3 bit update, indices `0x587..0x59E` whose bit is clear
  call `080CFA48` with indices `0x07..0x1E`. The real category table gives
  positive remainder divisors for these observed indices.
- Reload the input identifier after both adjustments. Identifier `0x6E`
  selects flag `0x582`/`0x583` from counter `0x81 <= 3`, then clears that
  counter. Identifier `0x2E` clears flag `0x36D`.
- Call `080CF118(record, (u8)enabled)`. In particular, `enabled == 0x100`
  selects the enabled bank and terminal byte here but passes zero to the
  helper. The original definition pointer remains unchanged across helpers.
- Use original definition byte `0x3F` when enabled, otherwise `0x40`. A nonzero
  byte sets record byte `0x02` category bits `0x1C` to `0x0C`, then reloads the
  definition byte and writes record byte `0x03`.
- Otherwise search the 64 physical nodes at `0x020025C8` in ascending address
  order and remove the first whose record pointer matches. Unlink previous,
  next and head as applicable; invoke the callback from `0x0836D4B8` with the
  stored record pointer and byte count 16; then clear only the node's record
  pointer. A missing record produces a null-node read at address `0x00000004`,
  not a safe no-op. No guard was invented.

The private header gives meaningful reusable identifier, bounded node lookup,
and removal operations. Ordinary inlining is a recovery choice, not historical
source provenance. Target-compiler layout checks establish node size `0x0C`,
alignment four, fields `0x00`/`0x04`/`0x08`, and state head offset `0x28C8`.
The global state uses the existing compatible opaque `u8[]` declaration and a
local typed view. The definition table retains the compatible unsized
`const u8[][70]` declaration; no number of allocated rows is invented.

## Fresh behavioral evidence

The retained disk-backed reproducer is
`/home/user/.codex-work/ffta-ulw/d1e70-inventory/check_recovery.py`:

```sh
export PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp
export PATH=/home/user/armtc/root/usr/bin:$PATH
python3 /home/user/.codex-work/ffta-ulw/d1e70-inventory/check_recovery.py
```

It freshly compiles/typed-links this parked source, reproduces the official
short-symbol rejection in an isolated root, checks target layouts, and executes
actual target ROM bytes versus fresh candidate bytes. A separate Python semantic
model supplies expected final memory, helper calls and the missing-node fault.

All 377 paired cases (754 executions) pass: 374 returning pairs and three
explicit missing-node fault pairs. Twelve pairs use pristine definition/table
ROM; other cases use labeled synthetic definition/RAM fixtures. Six machine
alias fixtures exercise helper-driven input-identifier changes, including actual
category-helper counter writes. Tests also cover distinct banks and entry order,
signed adjustment boundaries, narrowing before the cap, all 24 positive-divisor
category indices, special identifiers, upper argument bits, first/last pool
positions, duplicate record matches, all unlink positions, and helper cleanup.

Both bodies execute the actual ROM bit/counter helpers, `080CFA48`, `080CF118`,
RNG `08002804`, signed remainder `08142950`, and thunk `0814224C`. The real
clear routine at `0x03005E78` is copied from ROM `0x08A38A2C`; the callback slot
contains its actual Thumb pointer. No helper is stubbed or replaced by parked
C. The separate semantic oracle models their effects but is not the executed
helper implementation.

All 280 target instructions and all 258 candidate instructions are covered.
Ordered nonstack data reads and writes agree in every pair, including accesses
to definition/category tables and callback slot; instruction fetches, literal
loads and stack traffic are excluded from that data-trace comparison. Full
EWRAM and nonstack IWRAM agree with the independent model. Helper call order and
arguments, return PC, restored SP, and saved registers `r4..r11` agree. Maximum
observed stack depth, including real callees, is 88 bytes for ROM and 84 for the
candidate. Coverage of helpers is partial except where explicitly exercised;
caller coverage is not a proof over every helper input.

Valid writable record/node/state storage, valid definition rows, proper typed
node alignment and callback initialization/ABI remain prerequisites. The
machine alias and missing-node cases are diagnostic observations, not claims
of defined ISO C behavior for arbitrary overlapping objects or null access.
Malformed links can fault; callback or other callee termination is not proved.
The bounded tests establish neither universal allocation bounds nor universal
behavioral equivalence. Full byte equality remains unresolved.
