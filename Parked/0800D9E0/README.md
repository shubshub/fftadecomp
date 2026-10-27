# 0800D9E0

Target: complete 102-byte Thumb function, 47 reachable instructions,
0x0800D9E0 .. 0x0800DA46. Tested with the fixed agbcc
`-mthumb-interwork -O2` native matcher.

The preserved complete candidate passed the extent, direct-call CFG and
source-plausibility gates. Native exit 1 reported 100/102 bytes and 46/47
instructions identical. The remaining difference is the order of two call
argument setup instructions: the target moves the byte count from r8 to r2
at 0x0800DA2E, then loads the source pointer from [sp, #0x1c] into r0 at
0x0800DA30. The candidate performs that load before the move. Other target
instructions and the complete extent agree.

Grouped mode-1/mode-2 switch labels produced an 82-byte symbol and stopped
at the extent gate. Separate cases with the same row calculation produced
the preserved 102-byte result. Correcting the copy routine declaration to
the established void-return, source-first signature retained that result.
Advancing the destination pointer in a separate statement produced 106 bytes
and additional register-allocation differences, so that form was discarded.

The unmatched active source and report were removed. This is a Parked
candidate, not an exact match.
