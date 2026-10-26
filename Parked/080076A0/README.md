# 080076A0 — instruction-order mismatch

Target: 080076A0..080076F4, 84 bytes / 42 instructions.

The retained natural candidate updates a signed motion accumulator while
its remaining tick count is positive. It advances y, adds a remainder
increment, advances x for each full period, and applies the final positive
threshold correction.

The actual fixed native matcher reports a complete 84-byte ELF symbol,
closed leaf CFG, no relocations, and plausible source. Its exit status is 1
because bytes differ: 41/42 instructions and 82/84 bytes are identical.
The full generated native report is retained privately outside the repository.

The only remaining difference is the ordering of the adjacent period-value
preservation and threshold-load operations.

Bounded natural formulations included local accumulators, direct state
updates, field versus cached-period accesses, and equivalent while versus
guarded do loops. The earlier forms produced 82-byte spans or different
register allocation; the retained guarded do loop produces the complete
span and the two-instruction ordering difference above. No compiler flags,
inline assembly, volatile qualifiers, pragmas, redundant operations, fake
bindings, or matcher profiles were introduced. This is an ordinary C
code-generation mismatch; no tool limitation is asserted.
