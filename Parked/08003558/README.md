# 08003558 — Parked

Target: 0x08003558..0x080035A8, 80 bytes / 30 reachable instructions.

The function takes a halfword value and a byte selector. Selectors 0, 1,
and 2 replace the low halfword at offsets 0x0C, 0x10, and 0x14 of
g_control_flags_03000940; every other selector replaces the halfword at
0x18. The retained natural type models four word-sized records containing
16-bit value and unknown fields.

One natural fixed-agbcc -mthumb-interwork -O2 attempt was native checked.
Native exit 1: the complete ELF symbol is 72 bytes, shorter than the
80-byte indexed target, so the extent gate stops before byte comparison
and native plausibility. Neither gate is claimed to have passed.

The compiler's assembly reproduces the argument narrowing, value copy,
selector comparisons, store registers, four separate global literals,
and return shape. The target additionally reads the selected halfword
immediately before each of the four stores. Those loaded values are
unused; ordinary 16-bit bitfield assignments eliminate all four loads.
Their eight instruction bytes explain the remaining extent difference,
with consequent branch and literal-pool displacement changes.

This is the unused-load-before-store family. No artificial discarded
reads, volatile qualifiers, assembly, compiler flag changes, or codegen
conditions were added. The bounded attempt stops here. The native extent
refusal remains in the private address scratch as native-result.txt.
Active unmatched source and report have been removed.
