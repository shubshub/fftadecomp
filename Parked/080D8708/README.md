# 080D8708: bounded natural source gap

Target: `0x080D8708..0x080D8858`, complete 336 bytes / 155 reachable instructions.

The tested natural C reconstructs pattern-relative coordinates, bounds and availability checks, absolute height-difference filtering, invalid-coordinate sentinels, and preserved-index or compact output. The final canonical native matcher invocation at fixed agbcc `-mthumb-interwork -O2` returned exit 1: source plausible, complete compiled symbol 336 bytes, NOT MATCHING. Native diff score: 154/155 instructions and 334/336 bytes; this score is not a claim of same-offset byte equality.

The only reported instruction difference is the commutative pointer addition at target `0x080D8764`: target `adds r1, r4, r1`, compiled `adds r1, r1, r4`. All other reported instructions match. Both forms add the pattern offset-table base and the four-byte entry offset, with the same destination and result.

Bounded natural attempts used a four-byte offset structure, a four-byte signed-byte row, and a flat signed-byte table; explicit invalid-value assignment and direct stores in the preserved/compact branches corrected the earlier allocation and control-flow differences. The remaining ADD operand order did not change with the equivalent table layouts. No assembly, volatile access, compiler flags, artificial pointer arithmetic, or addressed helper aliases were introduced. No exact-match credit is claimed. Active unmatched source and report were removed.
