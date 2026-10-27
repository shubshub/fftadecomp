# 08023AA0

Complete natural C candidate: 84 bytes, equal to the complete indexed target. Fixed agbcc `-mthumb-interwork -O2`; final native matcher exit 1, source plausible, 82/84 bytes and 33/35 instructions identical.

Two result-register differences remain. At 08023AC8 the target has `lsrs r1, r0, #16`, while the candidate has `lsrs r0, r0, #16`. At 08023ACE the target has `lsls r0, r1, #16`, while the candidate has `lsls r0, r0, #16`. The target keeps the narrowed poll result in R1 while the candidate reuses R0. All other instructions, literal pools and alignment bytes agree.

Three bounded natural forms were tested: word-return poll with a separate u16 local initializer; word-return poll assigned to the u16 local in its nonzero condition; and signed-halfword return with the same conditional assignment. Every form produced the same complete 84-byte output and remaining two-instruction register-allocation gap. No assembly, compiler flag changes, artificial volatile, forced inline, or dead code was used.

The retained source is the final tested signed-status-return form. Last native evidence remains in private address scratch as `last-native-report.md`. Unmatched active source and report were removed. No exact match is claimed.
