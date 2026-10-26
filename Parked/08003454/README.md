# 08003454 — parked

Target: complete [0x08003454, 0x080034B6), 98 bytes / 49 instructions.
Fixed native agbcc `-mthumb-interwork -O2`: complete 98-byte candidate, source plausible, NOT MATCHING (exit 1); 43/49 instructions identical and 91/98 bytes identical.

The candidate initializes 128 hidden OAM entries and 32 identity affine matrices. All stores, pointer increments, and loop operations match. The counter is initialized before the loop-invariant halfword constants, causing the identity value to use r5 temporarily and requiring push/pop of r5. The target initializes the constants first, using r3 temporarily, then initializes the counter. No unused-load discrepancy is involved.

Tested natural forms: literal stores with a descending for loop; explicit u16 and u32 hardware-value locals before the counter (both compile to 94 bytes, omitting the two target constant-copy instructions); and the retained equivalent pre-decrement while loop (98 bytes, same register-allocation difference as the original literal-store form). No compiler flags or artificial operations were changed. Matching stopped after this bounded reconstruction attempt.
