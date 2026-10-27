# 08017618 recovered tile writer

Target 0x08017618..0x08017732: 282 bytes / 141 reachable instructions.
The complete candidate writes sequential 16-bit tile IDs to paired tile rows,
including optional two-column left/right borders and the encoded palette.

The final fixed native invocation (agbcc -mthumb-interwork -O2) returned exit 1:
complete ELF symbol 282 bytes, source plausible, bytes differ. Both bodies have
141 instructions. Same-offset equality is 280/282 bytes, with differences at
0xC8, 0xC9. The only differing instruction is at 0x080176E0:

- ROM: adds r3, r3, r7
- C output: adds r3, r7, r3

These compute the same right-border tile pointer and arithmetic flags, but the
operand order gives different instruction bytes. No exact match is claimed.

Natural forms tested: post-decrement outer while and indexed inner stores
initially produced 300 bytes. A counted outer loop, a column destination pointer
and direct flag reads recovered the target's 282-byte layout. Using a nonzero
row-count condition recovered its beq/bne branches. Right-border pointer forms
row + end, &row[end], end + row and an ordinary cursor advance all retained the
single commuted ADD. Direct right-border array indexing instead produced 286
bytes and changed allocation/address arithmetic. The last tested pointer-cursor
candidate is preserved unchanged.

This is a bounded source reconstruction gap, not a claim of permanent
unmatchability. Native output is retained in private address scratch as
last-native-output.txt. Unmatched active source/report were removed.
