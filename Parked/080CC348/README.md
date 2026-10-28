# 080CC348 — bounded natural reconstruction

Target: 0x080CC348..0x080CC3C8, 128 bytes and 54 reachable instructions.

The complete C reconstructs the category/index/count parameter widths, subtracts
0x16A from the 16-bit index, obtains the per-count increase from 080CC3C8, reads
the current byte at state + 0x2E7F + category * 16, and extracts the eight-bit
limit spanning bits 5..12 of the final two bytes of each seven-byte table record.
It clamps the increase to the remaining capacity, returning zero when the
current value is already at or above the limit.

The final unchanged native match command exited 1: the complete compiled symbol
is 124 bytes, shorter than the indexed 128 bytes. Its assembly contains 53
instructions, versus the target's 54. The matcher stops at this extent check;
no final full byte comparison or plausibility verdict was produced.

The target preserves the multiplication result in R7 after an additional move
from R0, then loads the current byte into R6 and copies it to R4. The candidate
multiplies into R6, loads the current byte into R4 and copies it to R7. The
missing two-byte product move and the resulting two-byte pool alignment account
for the four-byte extent gap. The target compares the total/current against R1
and subtracts using the original limit in R0 and current byte in R6; the
candidate compares against R0 and subtracts using its limit copy in R1 and
current byte in R7. Control-flow decisions, field extraction and constants are
reconstructed; register allocation and this instruction difference remain.

Eight bounded natural forms were compiled with fixed agbcc
-mthumb-interwork -O2: direct versus separately calculated total, byte/word
current and limit locals, signed/16-bit increase, multiplication operand order,
a genuine fully inlined clamp helper, separate base/multiply assignments, and
an explicit base-gain byte. Each remained 124 bytes. No assembly, volatile,
optimization changes, padding instructions or manufactured control flow was
used. The final tested C is preserved here; unmatched active source/report were
removed. Native output and final compiler assembly remain in the private
080CC348 scratch directory.
