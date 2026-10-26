# 0x081493AC: seven-byte table lookup

Target: complete [0x081493AC, 0x081493C0), **20 bytes / 10 instructions**.
Preserved best tested natural candidate: **20-byte complete ELF symbol** with
fixed `agbcc -mthumb-interwork -O2`; native exit 1, source plausible. Native
reports 9/10 instructions and 18/20 bytes identical for this candidate.

The function returns byte +4 from a seven-byte entry selected by row*16+column.
All arithmetic, addressing and the return match in the preserved candidate.
Remaining difference is conversion scheduling: target emits column lsl24,
row lsl24, row lsr20, then column lsr24. Candidate emits column lsl24/lsr24
before row lsl24/lsr20.

Bounded natural forms: a record structure was rounded to eight bytes by agbcc
and produced an 18-byte symbol; a seven-byte array view produced 20 bytes but
also changed address-result registers; explicit raw-byte entry addressing
resolved that difference (preserved); column-first index arithmetic remained
20 bytes but changed arithmetic registers and did not fix conversion ordering.
No asm, volatile, pragmas, artificial operations or compiler flag changes.

Owned unmatched src/report removed. Root owns lease release.
