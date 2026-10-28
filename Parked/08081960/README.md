# 08081960 — unmatched natural C

The complete target is 142 bytes / 71 reachable instructions, ending at
0x080819EE. Fixed compiler: agbcc -mthumb-interwork -O2.

The preserved candidate fills paired tile rows from the buffer pointer at
+0x0C, using the stride at +0x15 and row count at +0x17. It writes four border
tiles from the halfword at +0x1C, then 17 pairs of interior tiles with the
palette byte at +0x1F shifted into the tile attributes. The interior tile and
border counters each advance by 38 tiles per pair of rows. All halfword
counter truncations and dynamic stride reads are retained.

Fresh native verification exits 1: the source is plausible and its complete
ELF symbol is 142 bytes, the same extent as the indexed target. The native
diff reports 59/71 instructions identical and a 128/142-byte diff score; this
is not a byte-identical match and receives no match credit.

Remaining differences are register allocation and instruction placement:

- Target: border counter in r6, inner column countdown in r5. Candidate:
  border counter in r5, inner column countdown in r6.
- The target decrements the remaining-row counter and copies it into r8
  before initializing the interior cursor and column countdown. The candidate
  initializes that cursor/countdown first, then decrements and copies the row
  counter. The memory stores, arithmetic, branch structure, and complete
  symbol extent otherwise follow the recovered operations.

Natural for/while countdown forms and local-scope changes preserve the
142-byte allocation gap. Explicit middle-of-body decrement and guarded
do/while forms instead produce a 144-byte symbol with an early r8 row-counter
allocation. Post-decrement in the loop condition produces a 146-byte symbol
with a -1 termination comparison. None reproduces all target bytes. No
compiler flags, shared declarations, mappings, assembly, volatile accesses,
or inert operations were introduced.
