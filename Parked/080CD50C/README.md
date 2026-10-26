# 080CD50C — Parked

The complete natural reconstruction reads the selection byte at unit offset
0x3B when the unit is nonnull. If that byte is nonzero, it reads the job byte at
offset 6, indexes the corresponding row of g_table_0851BA84, and returns byte 4
of the selected eight-byte record. Otherwise it returns zero.

The final canonical native match used unchanged agbcc -mthumb-interwork -O2
and exited 1. Both the target and compiled complete ELF function are 54 bytes
with 24 reachable instructions. Source plausibility passed. The native aligned
comparison reports 9/24 identical instructions and 36/54 bytes; this is not a
same-offset byte count and does not earn exact-match credit.

Target bytes:
00b5002803d0011c3b31097800e0002100290dd081793b300278044889000918d20008688018007903e0000084ba5108002002bc0847

Compiled bytes:
00b5011c002902d03b30007800e0002000280dd088793b310978044a800080180068c9000918087903e0000084ba5108002002bc0847

The remaining difference is register allocation and dependent addressing:
the target keeps the unit in r0 through the nullable selection check, computes
that check in r1, then loads job into r1 and selection into r2 before loading
the table base into r0. The candidate copies the unit to r1 immediately,
computes the check in r0, then uses r0/r1 for job/selection and r2 for the table
base. The branch structure, table/record offsets, literal placement, and full
extent otherwise agree.

Five natural forms were tested: a conditional-expression selection read
(56-byte complete candidate), a naturally inlined nullable getter with a
single result variable (54 bytes), an explicit nullable selection assignment
(54 bytes), promoted u32 row/selection indices (54 bytes), and a named row
pointer (54 bytes, preserved here). The last four emit the same bytes.
No compiler flags, assembly, volatile access, or scheduling scaffolding were
used. Final native output and generated report remain in the private address
scratch directory. Unmatched active source and report were removed.
