# 080CF51C — recovered, not byte-identical

## Result

The complete ROM function occupies `[0x080CF51C, 0x080CF68E)`: 370 bytes,
156 instructions, 332 code bytes, nine four-byte literal words, and two
internal zero alignment bytes. The following zero halfword is external.
The full ROM body SHA-256 is
`472e988a3daa77100e84decd32f9519e5efc52034938b8dcf321c313eb9ec70d`.

The retained natural recovery produces one `STT_FUNC`, with the complete
`.text` equal to that symbol: 352 bytes, 151 instructions, 322 code bytes,
seven four-byte literals, and two alignment bytes. Its linked bytes have
SHA-256 `04b2e4650d28b1b481b19a1f8f5002a36e8c9d6ec25e819b6295bc0dda869841`.
The ordinary inline operation emits no separate function.

The reviewed `2e2a664` matcher, using the standard agbcc
`-mthumb-interwork -O2` flags, rejects this candidate with:

```text
compiled symbol is shorter than the indexed span: 352 < 370
```

This is a local code-generation mismatch, not an inherently impossible
function or a missing verifier feature. The official check stops before a
byte comparison; no official matching-byte count, successful report, or
MATCH verdict is claimed. No active source or match report is retained.

## Grounded recovery

The interface is `void func_080CF51C(void)`. No incoming argument or stack
argument is consumed. The ROM saves five words and allocates no local frame.
Entry evidence is its prologue, complete closed CFG, and adjoining function
boundaries; an incoming cross-reference is not asserted.

The first calls compare the low 16 bits of `func_080CE8A8()` and
`func_080CED2C()`. Equality conditionally sets flag `0x5AE` when it was clear.
The second condition reads flags `0x258` and `0x48C` in short-circuit order
and sets `0x48C` when both were already set. That redundant write is retained.

The list head is the word at `g_state_02000000 + 0x28C8`. Each 12-byte node
contains a record pointer, previous pointer, and next pointer at offsets
`0x00`, `0x04`, and `0x08`. Records are 16 bytes. Their identifier is the
10-bit value from bytes `0x00` and `0x01`; definition rows are 70 bytes at
`g_table_0855AE4C`. No outer table length is invented.

The countdown at record byte `0x03` remains unchanged when zero or `0xFF`;
otherwise it is decremented and stored. Zero then triggers processing of
the three-bit status at record byte `0x02`, bits `0x1C`:

- Status zero calls `func_080CF060(record)` and, only on a zero result,
  `func_080CF118(record, 0)`, then continues through the status-one/two logic.
- Status one or two, including that fallthrough, reads definition byte
  `0x40`. A nonzero value replaces status bits with `0x0C`, stores the status,
  reloads definition byte `0x40`, and stores it as the countdown.
- A zero definition duration, or status three, removes the record.
- Status four through seven performs no status transition.

Removal scans exactly 64 nodes at RAM `0x020025C8`, stride 12, for the first
matching record pointer. It unlinks that node with the observed previous,
next, and head update order. It then invokes the function pointer in ROM
slot `0x0836D4B8` with the record and byte count 16, before clearing only the
node's record pointer. The traversal reloads its current node's next pointer
after these mutations and calls.

The slot contains Thumb address `0x03005E79`. The audited startup copy places
176 bytes from ROM `[0x08A38A2C, 0x08A38ADC)` at RAM
`[0x03005E78, 0x03005F28)`. That copied block has SHA-256
`ce26dd719323641c1c4cbfa501368306ce6e31e193dabce7e84c7067f7590130`.
The actual initializer is the first 50 bytes and clears the requested
positive byte count. The call through the actual `bx r2` thunk at
`0x0814224C` is preserved. The local `void (void *, u32)` pointer contract
describes this call with positive count 16; it does not assert behavior for
every possible full-word count or an arbitrary replacement callback.

The private header expresses a genuinely reused lookup/removal operation at
the two status transitions. Ordinary inlining is a plausible organization,
not proof of the original historical source. It uses no forced-inline
attribute, register binding, artificial control flow, or extra emitted code.

## Bounded natural attempts and remaining difference

Only the standard compiler flags were used:

1. A shared removal block with direct previous/next member expressions:
   320 bytes.
2. The same shared operation with ordinary previous/next snapshots:
   312 bytes.
3. The retained private inline operation invoked from the two meaningful
   status transitions: 352 bytes.

The retained candidate still folds the head address into one literal
`0x020028C8`; the ROM separately loads `0x02000000` and `0x28C8` and adds
them. Status-bit clearing uses an immediate `0xE3` rather than the ROM's
longer negative-mask construction. Search-loop layout and register choices
also differ. The candidate shares the callback-slot literal at the common
removal tail, while the ROM loads it in each removal path. Thus both code
and literal placement differ: ten fewer code bytes and eight fewer literal
bytes. These differences were not hidden by truncation, address arithmetic
steering, or manufactured storage/control flow.

## Behavioral evidence and limits

The retained reproducer is
`/home/user/.codex-work/ffta-ulw/080CF51C/check_recovery.py`. From the game
root it can be rerun with:

```sh
PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH python3 /home/user/.codex-work/ffta-ulw/080CF51C/check_recovery.py Parked/080CF51C/080CF51C.c
```

It freshly compiles and typed-links the entire candidate, checks its sole
function symbol, closes the data bindings, and executes the real ROM caller
and candidate against matching fixtures. All callees are actual machine
code: `080CE8A8`, `080CED2C`, `080C9540`, `080C9574`, `080CF060`, `080CF118`,
the interworking thunk, and the copied RAM initializer. No helper stub is
used. Synthetic RAM supplies finite lists and records; eight fixtures retain
pristine ROM definition-table data, while the others use explicitly
synthetic definition bytes. The actual count table remains unchanged.

All 119 paired fixtures, 238 executions, agree on ordered calls and
arguments, ordered state/record/table/callback-slot data reads, ordered
nonstack writes, and final RAM. Instruction-literal fetches and stack reads
are excluded from the data-read comparison. The fixtures cover
countdown values zero, one, two, and `0xFF`; all eight statuses; zero/nonzero
duration; both status-zero helper results; head/interior/tail removal;
successive deletion; first/last pool slots; initial flags and counts; and
the special identifier path. Returning cases preserve registers `r4` through
`r11` and SP. ROM tables, callback-slot contents, and copied code remain
unchanged. There were zero observed read-footprint differences; this is
bounded fixture evidence, not a universal alias-equivalence proof.

Two pairs deliberately omit pool membership and are machine-only invalid
domain tests: both bodies fault while reading address `0x00000004`.
They do not establish valid C behavior after a failed lookup. Including
those fault paths, instruction coverage is 155 of 156 ROM instructions and
150 of 151 candidate instructions. The sole unexecuted branch in each body
(`0x080CF5BA` and `0x080CF5B6`, respectively) would require a negative value
after extracting an unsigned three-bit status, so it is infeasible.

The meaningful source domain requires valid aligned node objects, valid
record/definition storage, a consistent list whose removed records have a
pool node, and the audited initialized callback target. The ordinary typed
views do not establish arbitrary overlapping object lifetimes or allocation
bounds. Cyclic or corrupt lists are not guaranteed to terminate. These
limits are not replaced by invented guards, `restrict`, or null checks.
The plausibility checker reports no findings for the source or header.
