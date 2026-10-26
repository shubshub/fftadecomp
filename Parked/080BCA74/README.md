# 080BCA74 — Parked

Target: unchanged indexed range 0x080BCA74..0x080BCB2C, 184 bytes / 92 reachable instructions.

The preserved complete natural C candidate passed source plausibility. Fresh default native match.py exited 1: complete 184-byte ELF symbol, 78/92 aligned instructions and 167/184 aligned bytes. Direct same-offset comparison is 163/184 bytes. No exact-match credit is claimed.

Behavior is recovered: search the 16-entry pool from its saved unsigned 16-bit cursor for an entry whose active byte at +0x11 and pointer words at +0x18 and +0x14 are zero. If that suffix has no free entry, search the complete pool. Return null if both searches fail; otherwise select the found entry, advance the cursor, and wrap it to zero at 16. Entry stride is 0x1C; cursor is at +0x1C4. Search-completion labels join the full signed index/-1 result before signed 16-bit narrowing, preserving the target's result checks without helper functions.

The remaining first-search difference is register allocation and setup: the candidate uses R1 for its running entry pointer, R2 for its index, and R3 for the remaining count; the target uses R3 for the pointer, R1 for the index, and R2 for the count, with a different addition operand order. The fallback search agrees apart from cmp R2,#15 / ble versus target cmp R2,#16 / blt. The final cursor update, wrapping, returned pointer, and function extent agree.

Four bounded natural reconstructions covered direct signed-16 result assignment versus narrowing a full search result at the common exit, advancing pointers versus indexed struct searches, and shared versus separate search-pointer/index lifetimes. Indexed searches added address calculations and grew to 202 bytes; direct signed-16 result assignment used a literal and grew to 192 bytes. The preserved separate-pointer version is the best tested complete form. The repeated search bodies may have originated from an inlined helper; this remains an inference, and no helper was added.

Verification used the approved ROM and shared native match.py with fixed agbcc -mthumb-interwork -O2, PYTHONDONTWRITEBYTECODE=1, TMPDIR=/home/user/tmp and the approved ARM toolchain PATH. Full target, final native output, and last-native-report.md remain in the private address scratch directory. Unmatched active source/report were removed. No assembly, pragmas, volatile objects, dead code, flags changes, or shared/main edits were used.
