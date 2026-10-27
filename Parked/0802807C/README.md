# 0802807C — Parked

Target: complete indexed Thumb span 0x0802807C..0x080280F4, 120 bytes and 56 reachable instructions.

The complete reconstruction separates interleaved 32-byte tile rows in two 256-byte blocks using the mapped copy callback at data_0836D4BC. Each block copies four first-lane rows into its first 128 bytes and four second-lane rows into its second 128 bytes. Source rows advance by 64 bytes; destination rows advance by 32 bytes.

The retained candidate is the second tested form: ordinary counted outer loop and signed descending inner loop, with explicit source/destination pointer induction. Under unchanged agbcc -mthumb-interwork -O2 it generates a 120-byte body with the same frame, pointer registers, copy calls, strides and loop bounds, but different setup ordering and scratch-register allocation. The ROM increments and spills the outer counter at 0x0802808E/0x08028090 before initializing the four row pointers and inner counter; the candidate performs that increment/spill after those initializations. The first copy callback load and the second copy callback load use r0/r1 in the opposite order, and the inner decrement/compare also use the opposite r0/r1 allocation.

Native match.py with --function-address-profile canonical-thunks-v1 exited 1 with "inert-spin complete body differs from ROM" for this retained form. That diagnostic is the profile's complete-byte comparison gate, not evidence of an inert-spin implementation. The plausibility gate was not reached; no plausible or exact-match credit is claimed.

Bounded attempts: (1) a do/while block counter with its increment at the top was converted into a countdown and failed the complete-span gate; (2) the retained ordinary for loop reached the complete-body comparison and differed as described; (3) a genuine naturally inlined per-block helper generated the same differing instructions as the retained form; (4) indexed block offsets instead of advancing outer pointers failed the complete-span gate. No flags, assembly, volatile, artificial aliases, forced inlining or scheduling contrivances were used.

The unmatched active source/report were removed. Only this complete recovered C and diagnosis remain in Parked.
