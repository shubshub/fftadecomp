# 0x0811CC9C — recovered, not matched

Target: `[0x0811CC9C, 0x0811CD4C)`, 176 bytes / 83 instructions.
Compiler: agbcc `-mthumb-interwork -O2`, unchanged throughout the attempt.

The final natural candidate produced a 170-byte complete symbol. The native
matcher exited 1 because the indexed target is 176 bytes. This is an unresolved
match at the fixed flags, not evidence that the function cannot be matched.

The target keeps `i * 16` and `(i + 6) * 16` as separate loop invariants, adds
`j + 0x100` inside the palette loop before the color-conversion call, and
recomputes that column offset after the call for the output store. The final
candidate instead combines `0x100` with the row offsets and hoists those sums.
The initial object loop was reproduced exactly in relevant candidates.

Tried natural arithmetic grouping, multiplication and shift forms, typed
source/destination index locals, a separate color-conversion assignment, and
a local palette-buffer pointer. Candidate extents ranged from 164 to 176 bytes;
the 176-byte form still differed in register allocation and palette indexing.
No compiler flags, shared mappings, or headers were changed; no assembly,
volatile accesses, pragmas, dead code, or steering constructs were used.

The source is the unchanged final candidate. No source or native match report
is retained under `src/` or `docs/match/` for this address.
