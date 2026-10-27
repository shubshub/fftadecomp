# 0813E348 — bounded natural-C nonmatch

The complete recovered function remains unmatched under fixed agbcc
`-mthumb-interwork -O2`. The repaired ROM owner is
`[0x0813E348, 0x0813E750)`: 1032 bytes and 468 reachable instructions.
The preserved candidate emits a complete 1012-byte ELF function symbol and
457 decoded instructions. Native typed linking succeeds against the current
unchanged mappings. Exactly 263 bytes equal the ROM at the same offsets
within the 1012-byte candidate; this is not an aligned-diff score or partial
match credit.

## Remaining difference

The target anchor cases at 0x0813E424..0x0813E470 reload the selected global
coordinate pair from g_control_flags_03000940 after calculating the local
coordinate offsets. The candidate reuses those loaded values, shares the
second offset calculation, and merges the two cases' negated-coordinate
stores. Its anchor setup is eleven instructions shorter. The target also
shifts each saved coordinate left by 16 before negation in the movement call
at 0x0813E612..0x0813E61A; the candidate negates before the shift, with the
same subsequent arithmetic narrowing. No artificial memory observability,
volatile, optimization changes, or code-generation controls were introduced.
Other recovered spawn/update/draw instruction sequences align under the
address-normalized diagnostic, which is only a diagnostic and not byte-match
proof. The complete symbol differs by 20 bytes, including pool alignment.

## Natural forms tried

- An external u16 array and a field-based control structure with ordinary local
  pointers; signed/unsigned coordinate members did not recover the repeated
  global reads or separate stores.
- Scalar u32/u16 coordinate-offset locals and a genuine two-element u32
  coordinate array. The array altered initialization/register allocation and
  did not repair the anchor loads; scalar offsets are preserved.
- Natural signed-narrowing placements around coordinate negation retained
  the negation/shift ordering difference.
- Direct indexed spawn-table expressions, instead of a separately loaded
  table local, and the observed signed second-coordinate argument fixed the
  table loads and signed argument preparation. Those corrections are retained.

The final canonical matcher invocation exited 1 with both explicit selectors:
`--software-double-profile convert-sub-div-target-v1` and
`--software-double-remainder-profile target-state-v1`. It stopped at the
exact-span ownership gate with
`software double requires exact unique nonoverlapping Thumb spans/counts`.
The candidate's 1012-byte extent does not equal the proven 1032-byte owner;
no metadata or toolkit repair is indicated. Byte equality, plausibility and
fresh-source replay were not reached, and no match/plausibility credit is
claimed. This records a bounded fixed-profile source gap, not a permanent
impossibility claim.

The original ELF, assembly, linked diagnostic bytes, diagnostic.json,
diagnostic.diff and final native match.log remain in the private sibling
0813E348 scratch directory. Active unmatched source/report were removed.
