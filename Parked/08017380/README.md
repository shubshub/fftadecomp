# 08017380 — bounded natural-source mismatch

Target: `08017380..08017424`, 164 bytes / 81 reachable instructions.
The preserved candidate was compiled with the unchanged native matcher and
`agbcc -mthumb-interwork -O2`. Its complete ELF symbol is also 164 bytes /
81 instructions. Native extent validation and source plausibility passed;
byte comparison returned `NOT MATCHING`, exit 1. No match credit is claimed.

The native aligned diff score was 67/81 instructions and 149/164 bytes.
These are native diff scores, not same-offset byte equality.

The candidate preserves the window coordinate adjustments, flag branches,
signed initial height division, byte-truncated rounded height, final row
calculation, and eight-argument draw call. Remaining differences are register
allocation and the associated odd-height arithmetic: the target keeps Y in
r5, original height in r2, and row count in r4; the candidate uses r4, r5,
and r2 respectively. In the rounding branch the target tests original r2
and computes r1 = r2 + 1; the compiler tests its copied r1 and increments
r1 in place. Those choices propagate through coordinate updates and call
argument preparation.

Natural byte and promoted-height forms and a naturally inlined row-height
helper were tested. The helper retained the same 164-byte allocation gap;
a byte-cached form added one instruction. The preserved promoted-height
candidate is the tested 164-byte form. No assembly, volatile RAM, forced
inlining, compiler changes, or register steering was used. Unmatched active
source and report were removed.
