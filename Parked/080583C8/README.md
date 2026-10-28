# 080583C8 — not matching

Target: 0x080583C8..0x080583FA, 50 bytes and 25 reachable instructions.
Compiler: fixed agbcc -mthumb-interwork -O2.

The retained C checks whether a three-item view can move in either direction.
Direction 0x40 requires a nonzero signed halfword position at offset 0x1A.
Direction 0x80 requires that position plus three be less than the signed
halfword count at offset 0x18. Other direction codes return zero.

The retained switch candidate was freshly checked with the default native
matcher. It exits 1 with a complete 50-byte ELF symbol, supported leaf CFG,
and passing source plausibility. Byte comparison reports 18/25 instructions
and 36/50 bytes identical.

The residual difference is branch layout. The target tests direction 0x40,
handles that case immediately, then tests 0x80 and handles the forward case;
both join success and failure blocks at the end. The compiler emits both
switch dispatch comparisons before the case bodies and places the common
zero-result block before those bodies. The signed field loads, arithmetic,
comparisons and final success value remain present.

Positive-return if/else, a combined condition and negative guard clauses
were also tried. Those compile to 48 bytes and are refused by the extent
gate before byte comparison or source plausibility. Fixed-flag assembly of
the direct positive-return form places the shared success block between the
two direction tests, eliminating one target branch. A result-variable form
produces a 54-byte plausible differing body, with arithmetic boolean
conversion and an extra saved register; its comparison extends beyond the
50-byte indexed target. The retained switch has the correct complete extent
and a directly observed native plausibility result. Compiler options were
unchanged throughout.

The native differing report remains only in private address scratch. No
unmatched active source or report remains.
