# 08004EC8 — bounded natural reconstruction, not matched

Accepted claim: 6455560695, v656. No match credit.

The function constructs a 20-byte packet, copies sixteen payload bytes using the
original indexed CpuSet wrapper, computes the complemented halfword checksum,
and conditionally stops/restarts timer 3 at the real MMIO register 0x0400010E.
Only that hardware register is qualified volatile; RAM fields are ordinary.

Final canonical match.py run with the approved ROM and unchanged agbcc
-mthumb-interwork -O2 exited 1: NOT MATCHING, source plausible, complete ELF
symbol 108 bytes. Both bodies contain 47 reachable instructions; 40/47
instructions and 100/108 same-offset bytes are identical. All instructions before
0x08004EFC, the literal pool and the function endpoint are identical.

The remaining instructions are:

| Address | ROM | Candidate |
| --- | --- | --- |
| 08004EFC | `adds r2, r4, #0` | `ldr r2, [pc, #0x28]` |
| 08004EFE | `ldr r1, [r2, #0x28]` | `ldr r0, [r2, #0x28]` |
| 08004F00 | `mvns r0, r5` | `mvns r1, r5` |
| 08004F02 | `strh r0, [r1, #2]` | `strh r1, [r0, #2]` |
| 08004F12 | `ldrsb r0, [r4, r0]` | `ldrsb r0, [r2, r0]` |
| 08004F14 | `str r0, [r4, #0x14]` | `str r0, [r2, #0x14]` |
| 08004F16 | `ldrb r0, [r4]` | `ldrb r0, [r2]` |

The compiler reloads the state address from the literal pool instead of copying
r4 to r2, exchanges the checksum destination/value registers, then uses r2
instead of r4 for the timeout update and final timer-enabled test.

Bounded attempts included a natural local state pointer, ordinary direct global
access, and an explicit checksum-complement step. The local state pointer removed
one instruction and changed alignment; the explicit complement changed the
checksum accumulator allocation. A scalar MMIO pointer declaration failed the
existing plausibility policy and was replaced by documented direct hardware
accesses, which the unchanged policy accepts. No compiler flags, runtime aliases,
assembly, padding or RAM qualifiers were introduced.

The preserved C is the final tested direct-global form. The final native output
and exact remaining difference are retained in the owned sibling scratch:
`08004EC8/final-native.log` and `08004EC8/remaining-difference.json`.
Unmatched active source and match report have been removed.
