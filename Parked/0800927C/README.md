# 0800927C — Parked: oversized first-form body overlaps next entry

The first natural typed C form compiles with fixed agbcc
`-mthumb-interwork -O2` to a complete **294-byte** symbol. The actual ROM
function is **278 bytes**. No source-form, declaration, register, flag or
artificial-control search followed. The source is plausible but is not a match.

## Complete extent and metadata

The owned ROM span `[0800927C,08009392)` contains266 code bytes /117 reachable
instructions. Three internal literal words at92F0,92F4 and9364 hold the active
pointer-slot address02009188 and two copies of03000000. None is code.
The two zero bytes at9392..9394 are external alignment, not an extra
instruction or a required pool. The next indexed function starts at9394.
Independent raw decoding, Capstone CFG and Binary Ninja instruction lengths
agree. The separate metadata proposal changes count139→117 only.

The candidate has288 code bytes /128 instructions, two internal alignment bytes
at92FE..9300 and one required literal at9300. Its original and linked function
symbols are294 bytes; the296-byte text section contains an additional external
two-byte Thumb NOP `c046`, excluded from the function comparison. All16
`R_ARM_THM_CALL` relocations bind eight unique mapped odd Thumb function symbols.
There are no final relocations, hidden pools or additional allocated payload.

At the original address the candidate ends93A2,16 bytes beyond the target span
and14 bytes beyond the next function entry9394. The first difference is+2:
ROM `00` begins the input shift, candidate `47` saves r8 through r7. The ROM
has a20-byte saved-register frame; the candidate uses24 bytes. Candidate byte
argument conversions, register allocation, address materialization, branches
and epilogue differ. The compiler synthesizes03000000 instead of using its two
ROM literals. There are278 unequal byte positions over the combined extent:
262 within the ROM span plus16 excess candidate bytes.

- Source SHA256: `10ae02143f24eccafffe08a28509fef0146ba4736c925e663615d30514494f68`
- ROM body SHA256: `e77cb4e2e1b2a768b74abc6659527d14f2da4b7a2e7460827967007dc155643e`
- Diagnostic candidate SHA256: `4a8ed7e55e8a029a47e2057691b087f82e59016151d1f60d7d7d3a1e53423f89`

## Official result versus diagnostic link

The unchanged approved `kit-software-double-candidate-v3`, using the requested
ordinary `--mode thumb --no-write` command, exits1:

```text
recursive or intra-function calls are unsupported
```

The call to09394 falls inside the oversized candidate's own claimed extent.
The source is not recursive; the rejection correctly prevents an overlapping
body from being accepted. No map, verifier or source was changed to bypass it.
No successful report exists, and successful-report replay is inapplicable.

A separately labeled diagnostic link resolves the complete original ELF using
typed symbols at the actual mapped addresses, solely to expose all bytes and
the discrepancy. Runtime tests cannot execute that overlapping placement as
two independent functions. They instead link the **identical original object**
at08040000, leaving helpers at their real addresses. The harness verifies
equal size and every unchanged byte outside the16 BL relocation slots, as well
as each relocated BL destination. This relocation is a diagnostic experiment,
not an official match, deployable ROM replacement or new function mapping.

## Behavior and type limits

The low16 key bits select direction0x80 first, otherwise0x40. The function
updates the input-state object at03000000, reads a signed scroll position,
optionally updates the list, and increments/decrements that signed byte. It
returns8 for a local move,1 for a scrolling move and0 when neither applies.
Local moves play sound109 only when the freshly reloaded active count exceeds1;
scrolling moves play it unconditionally. List/scroll pointers stay cached from
entry even when a helper changes the active pointer.

The source uses the existing compatible sparse helper definitions and scalar
signatures, including17B68'su32 argument and17AF4'su8 parameters. The first
three parameters of09394 are grounded as low-byte consumers by its entry.
Tests retain raw handoff registers separately from canonical byte arguments.
No claim is made that a matching machine representation alone makes arbitrary
different C function types compatible.

Signed byte increment/decrement is performed after integer promotion, so the
arithmetic itself ranges only[-129,128]. Conversion back tos8 outside its range
is implementation-defined; the fixed compiler's low-byte behavior is tested,
including127→-128 and-128→127. Helper results preserve the distinction between
u16 clamp/count returns and the signed16 final-index result. Negative list
limits and wrapped list offsets are included in bounded tests rather than
silently treated as nonnegative. No signed integer arithmetic overflow is
required by this source.

Valid aligned live storage and initialized fields remain premises. Sparse
helper views do not recover a complete engine allocation or prove ISO C
effective-type/aliasing compatibility for every game object. Asynchronous
mutation, arbitrary allocation/frame overlap, downstream negative-index domains
and full engine behavior are not established.

## Bounded execution evidence

64 executions compare actual ROM against the relocated candidate across16
cases and ARM/Thumb returns. They cover no-key, both directions, priority when
both bits are set, high input bits, local/scroll/no-op outcomes, signed-byte
wraps, negative limits, halfword offsets, active-pointer replacement and cached
position behavior. All117 ROM and128 candidate instructions, and all80
instructions across the five actual leaves, execute. Checks include all helper
arguments, defined RAM reads, exact non-stack writes, bounded frame writes,
unchanged remaining RAM, restored r4-r11/SP and returned0/1/8.

Actual complete bodies execute for023D0,17B68,17BE8,17B50 and17A90. The other
three helpers—17AF4,09394 and141540—are whole-call ABI/effect models, not actual
execution. Their synthetic writes, pointer/position changes and volatile
register clobbers exercise caller observations without asserting the helpers'
real effects. The actual input helper's conditional byte copy and unconditional
halfword clear are checked. Nine executed runtime negatives and17 target
layout/arithmetic assertions pass. This is bounded evidence, not universal
equivalence or an official verifier acceptance.

## Reproduction

Author evidence is in `/home/user/.codex-work/ffta-ulw/0800927C-author/`.
`probe.py` creates a private fixture from immutable `game-next-e299a92`, copies
all nine headers, applies only the count proposal, runs the requested official
command and captures complete diagnostic ELF evidence. `check.py` recompiles
the same fixed source and runs the bounded checks. Inputs, mapped helper
spans and the existing helper source interfaces are pinned/rechecked. All
generated fixtures and binaries are removed. Shared files and prior freezes
remain untouched; parent owns independent review and integration.
