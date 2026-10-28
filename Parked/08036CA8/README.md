# 08036CA8

Complete target: 156 bytes / 66 reachable Thumb instructions, ending at
0x08036D44. Fixed agbcc `-mthumb-interwork -O2`.

The preserved complete candidate passed the native extent, CFG and plausibility
gates, then returned exit 1: 146/156 bytes and 57/66 instructions identical.
The coordinate clamps and complete rendering call match. The remaining opening
lookup differs in register allocation and load order: the target loads the
position-table pointer at 0x08036CBE before multiplying the selected index;
the candidate retains the pointer-field address, multiplies the index first,
then loads the table pointer. This also changes the context and position
registers through 0x08036CD0. The rest of the body is identical.

Tested the direct table-index expression preserved here, then an explicit
context plus table local, then a table local without the context local. Both
local-table forms also produced complete 156-byte plausible bodies, but only
132/156 bytes and 42/66 instructions identical, with another saved register.
No compiler flags, assembly or artificial accesses were used. No exact match
is claimed; unmatched active source and report were removed.
