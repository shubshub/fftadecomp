# 08127594

Target: 0x08127594..0x081276D6, 322 bytes / 149 reachable instructions.

Recovered behavior updates two movement axes, derives nonnegative tile
coordinates from the entity's movement and directions, looks up tile height,
updates facing when height agrees, and completes the movement when both axes
finish. The observed state and entity fields are represented by local types.

The retained source was freshly checked with the canonical native matcher and
agbcc -mthumb-interwork -O2. Native exit 1: NOT MATCHING. The complete 322-byte
ELF extent and supported direct-Thumb-call CFG passed; the source was reported
plausible. Byte comparison found 146/149 instructions and 319/322 bytes
identical. No exact-match credit is requested.

The three differing instructions are confined to the height comparison. The
target shifts the tile-height temporary into one register, then loads the
entity pointer and signed entity height through the other. The compiler
instead shifts in place and uses the opposite register for the pointer and
entity-height load. Both forms perform the same comparison. Branch locations,
call sites, literal placement and the remainder of the function match.

An int-returning facing-change helper initially compiled to 314 bytes because
the compiler merged its boolean result into the caller's branch. A byte return
naturally preserves the target's boolean materialization and 322-byte extent.
Reversing the comparison operands recovered the target's load order. A local
calculated-height value and ordinary fully inline height accessors were tested
but changed register/evaluation order without reaching equality. Explicit
shift and multiplication forms produced the same best 319-byte agreement.
No artificial volatile accesses, dead expressions, register constraints,
forced inline attributes, or compiler flag changes were used.

Raw native output and the differing report remain outside the repository in
private v397/08127594 scratch. Unmatched active source/report were removed.
