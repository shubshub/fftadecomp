# 081303AC — bounded unmatched attempt

Target: complete 78-byte Thumb function, 35 reachable instructions,
[0x081303AC, 0x081303FA). The retained C computes the signed 16-bit selected
value divided by eight, adds a signed 16-bit random value modulo eleven minus
five, and clamps the signed 16-bit result to at least one. It preserves the
initial flag-query call whose result is unused by the captured body.

The fixed agbcc `-mthumb-interwork -O2` candidate emits one 72-byte function
symbol (32 instructions). It omits the target's unused 8-bit query-result
narrowing and intermediate unsigned 16-bit normalization before the signed
conversion. It also schedules the subtraction and signed quotient conversion
after the remainder call and allocates one fewer preserved register. The
retained C uses the genuine signed `% 11` operator and emits `__modsi3`.

Three native attempts tested the direct arithmetic expression, a separate
wide base intermediate, and a separately typed signed 16-bit random value.
The wide base allowed further shortening; the retained direct arithmetic with
a typed random value preserves the closest 72-byte form. No artificial use of
the discarded query result, dead expressions, volatile, runtime-address alias,
assembly, compiler flag change, or register steering was introduced.

Final native command exited 1 at the signed-remainder caller gate:
`signed remainder caller requires exact complete mapped ROM bytes`.
Complete byte identity, the runtime manifest proof/replay, and the native
plausibility gate were not reached. The unchanged target and native diagnostic
remain in the private address scratch directory; no ROM-derived diff is kept
in this Parked pair. Unmatched active source/report files were removed.
