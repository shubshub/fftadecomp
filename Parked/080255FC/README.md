# 080255FC — not matching

Target: 0x080255FC..0x08025688, 140 bytes and 59 reachable instructions.
Compiler: fixed agbcc -mthumb-interwork -O2.

The retained natural C clears the requested pair of halfwords for indices
0..15. Index 4 additionally clears entry 5, entries 6..8 and entries 13..15,
then clears flag 0x20 at control-state offset 0x94. Index 2 clears the pointer
at menu-state offset 0x18.

Fresh default native matching of this retained source exits 1. The complete
ELF symbol is 140 bytes, its leaf CFG is supported, and source plausibility
passes. Comparison reports 40/59 instructions and 118/140 bytes identical.
The initial entry clearing and final index-2 branch match. The remaining
mismatch is register allocation in the two three-entry clearing loops and
the placement of the control flag address calculation. The compiler assigns
the first loop's zero and counter to r1 and r2, respectively, while the target
uses r2 and r1. It also calculates the flag address before the second loop,
uses different registers for that loop, and stores the flag through r4
instead of the target's r2.

Direct indexed field stores produced a 156-byte plausible differing body.
Using a local pair pointer reduced the body to 140 bytes (37/59 instructions,
115/140 bytes identical). Factoring the repeated range operation into an
ordinary naturally inlined helper produced the retained 140-byte candidate.
Passing the menu pointer to that helper produced 136 bytes and was refused
by the extent gate before byte or plausibility checks. A post-decrement
countdown loop produced a 144-byte plausible differing body. Comparisons of
larger bodies included bytes beyond the indexed target and do not establish
a complete match. The retained candidate was restored and freshly matched
again with the 140-byte result above. No compiler options were changed.

The native differing report remains in private address scratch, outside the
matching root. No unmatched active source or report remains.
