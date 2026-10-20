# 080CEA80 — recovered, not matching

The complete target is `[0x080CEA80, 0x080CEB34)`: 180 bytes, 68 reachable
Thumb instructions, and seven four-byte literal words. Its code occupies
`[0x080CEA80, 0x080CEAF8)` and `[0x080CEB0C, 0x080CEB2C)`; there are no
internal alignment gaps. All seven literal words belong to the function.

The retained natural candidate, compiled with the standard
`agbcc -mthumb-interwork -O2`, has one 168-byte function symbol and a
168-byte `.text`: 62 instructions, 140 code bytes, and 28 literal bytes.
It is 12 bytes and six instructions shorter than the target. The frozen
`2e2a664` matcher, run in an isolated root with the current headers and
audited bindings, exits 1 with:

```
compiled symbol is shorter than the indexed span: 168 < 180
```

This is a real code-generation mismatch, not a missing verifier feature.
There is no matching report or active source for this address. The source
passes the plausibility checker without exceptions.

## Recovered behavior

The compatible interface is `void(u8 flag)`. Two ordered calls to the
argument-free RNG construct a word from the first result narrowed to `s16`
and the second unsigned result shifted left 16 bits. The audited RNG returns
0 through 32767, so the signed narrowing is representable. The word is
stored at selection-state offset `0x98` for a nonzero flag, or `0x9C` for
zero, before a third RNG call. An odd third result sets flag `0x5A5` or
`0x5A6`, respectively; an even result does not clear the flag.

Only the nonzero branch scans records. It snapshots the halfword count at
`0x0854D1B4` once, advances an independent record pointer from `0x02000080`
by `0x108` per iteration, and calls `080C7EA4(record, 1)`. A zero first byte
of the selected 14-byte category-table row causes `080C9E00(record)`.
The helper order and conditional invocation are retained without replacing
their side effects or assuming that a matched C definition is available.

## Why the addressing differs

The target retains selection-state address `0x020020D0` and adds
`0xFFFFDFB0` to obtain record address `0x02000080`. The recovery uses the
independent actual record address. The numeric relationship does not prove
an enclosing C object, so no out-of-bounds state-relative arithmetic was
introduced.

The target loads `0x0854CD7C`, adds `0x438`, and reads the count. That base
also equals the existing script-table base `0x0854CD54` plus `0x28`, but
there is no recovered semantic count-container layout. The recovery instead
uses the grounded `const u16 g_count_0854D1B4` binding at the read address.
It does not invent a biased script-record view to reproduce that arithmetic.

The compiler also hoists the category-table base, saves `r6` in addition to
`r4`/`r5`, and produces different register allocation, pool placement, and
branch/call displacements. Both bounded natural forms tried—record-pointer
initialization at nonzero-branch entry and at loop entry after the flag
update—produced 168-byte symbols. The latter is retained. No compiler flags,
register constraints, artificial control flow, or storage qualifiers were
used to steer those differences.

## Integration prerequisites and domain

The local `SelectionState` is a provisional observed refinement: its two
words at `0x98`/`0x9C` replace part of the existing canonical
`unknown_00[0xA0]`, while preserving every later field offset. This local
aggregate is not C-type-compatible with the current canonical declaration
in `include/selection_state.h`. Before any future promotion, that shared
type must be deliberately refined, its existing users reverified, and this
local definition replaced by the canonical header. No active shared header
was changed for this nonmatching recovery.

The 14-byte category-table declaration matches the existing declaration;
the script-table declaration is not duplicated or changed. The raw RAM
record pointer is a target-specific byte view, not a claim about allocation
size. Execution requires enough valid record storage for the count, valid
category rows and pointees required by the ordinary helper contracts, and
normal ARM calling-convention behavior. Neither table allocation bounds
nor transitive helper termination or memory safety is established here.

## Bounded verification

Thirty-six paired cases (72 executions) compare actual ROM caller bytes
with a freshly compiled and diagnostically linked candidate. They exercise
flags `0`, `1`, `0x100`, and `0x101`; three RNG seeds; and counts `0`, `1`,
and `6`. All 68 target and 62 candidate instructions are covered.

The tests execute actual ROM bodies for `08002804`, `080C9574`, and
`080C7EA4`. Only `080C9E00` is explicitly modeled with record writes and
caller-clobbered registers; this is not execution or proof of its full
initializer behavior. RAM, category rows, and count values are synthetic
fixtures, including synthetic ROM-data overrides. The test does not infer
a game allocation from those fixture sizes.

Both bodies agree on ordered nonstack data accesses, helper calls, all three
RNG transitions, the state store before the third RNG, the single count
read, selected-record progression, category gating, final RAM and RNG seed,
and preserved callee-saved registers/SP/return. Diagnostic absolute symbol
binding is used only for this behavioral comparison, not as a replacement
for the official match gate. Generated compiler and emulator artifacts are
kept outside the repository and cleaned.
