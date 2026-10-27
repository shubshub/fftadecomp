# 080114FC — unresolved base-register setup

Target: 0x080114FC..0x08011564, 104 bytes and 50 reachable Thumb instructions.

The recovered C scans the counted array of 64-byte entries at data_02009170.
It clears each active entry whose channel byte at offset 0x1C matches the
unsigned byte argument, then clears the selected channel state pointer. Cases
0, 1, 2 and 3 clear offsets 8, 0xC, 4 and 0x10 respectively; other channel
values only perform the scan. The loop reloads the entry count as in the ROM.

The retained source was freshly checked using the default native match.py
command with fixed agbcc -mthumb-interwork -O2. Native exit: 1. Its complete ELF
symbol is 104 bytes, the closed-leaf CFG and data linking passed, byte comparison
completed, and the source gate reported `source plausible`. Bytes differ:
48/50 instructions identical (100/104 bytes). This is not a match.

The remaining difference is the register setup around the initial loop guard.
The ROM loads the shared state address into one base register and copies it to
the switch-state register before reading the initial count. This candidate
loads the switch-state register directly and creates the count-base copy after
the guard, inside the nonempty-loop block. The loop body, count reload, four
switch cases, literal-pool position, return and complete symbol length match.
No added condition or artificial liveness was used to force the copy earlier.

A conventional for loop accessing the state through one local pointer compiled
to 100 bytes; the extent gate rejected it before byte or plausibility checks.
Direct global access during the scan produced the retained 104-byte candidate.
An explicit initial guard and do/while scan also compiled to 104 bytes and
passed source plausibility, but changed further base registers and alignment,
leaving only 34/49 instructions identical in its compiled-length comparison.
The closer for-loop candidate was restored and freshly checked before parking.
All attempts used the fixed compiler flags and only natural C.

The generated differing report and command output are retained outside the
repository in the private address scratch directory as native-not-matching.md
and native-result.txt. Unmatched active source and report were removed.
