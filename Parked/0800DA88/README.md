# 0800DA88

Target: complete Thumb function [0x0800DA88, 0x0800DAB8), 48 bytes,
21 reachable instructions. Fixed agbcc `-mthumb-interwork -O2`.

Recovered behavior: for a signed 16-bit index below 160, obtain the object's
halfword buffer, copy the supplied byte-sized count of halfwords from the
source into buffer + index, then mark the object dirty. The target has no
lower-bound check.

The preserved complete candidate passes native extent, direct-call CFG and
source plausibility. The native matcher exits 1 because two call-argument
moves are reversed. At 0x0800DAA4 the ROM moves r5 into r2 (count), then at
0x0800DAA6 moves r7 into r0 (source). The compiled candidate moves source
first and count second. All other instructions and the complete 48-byte
extent agree. The matcher reports 20/21 aligned instructions and 46/48
aligned bytes identical; same-offset equality is also 46/48 bytes.

Three natural forms were tested: adding the index in the copy argument,
using an explicit widened transfer-count local, and advancing the destination
pointer before the copy. All produced the same complete bytes and move-order
difference. No assembly, volatile accesses, forced inline, compiler flag
changes or artificial operations were used.

The unmatched active source and native report were removed. This is a
Parked candidate, not an exact match.
