# 0812E3B0

Target and preserved candidate both have complete 56-byte function symbols.
Native match.py exit 1: direct-Thumb-call CFG accepted, source plausible,
50/56 bytes and 20/25 reachable instructions identical. No match credit.

The function looks up an entry using bytes at incoming offsets 6 and 3C.
A zero halfword table index at returned offset 4 gives zero. Otherwise it
decodes a five-bit value from bits 5..7 of table byte 1 and bits 0..1 of
table byte 2, in records of stride four.

The preserved candidate reproduces the repeated index LDRH, branch layout,
table literal, complete extent and all code before the final byte decode.
ROM holds the low three bits in R2, loads the second byte into R0, then
loads mask 3 into R1. The candidate holds the low three bits in R1 and
loads mask 3 into R2 before loading the second byte into R0. Corresponding
AND/OR source registers differ. The remaining six bytes differ only in
this register allocation and mask-load ordering.

Bounded tested forms: a direct byte expression with an early zero guard
(58 bytes, plausible; its comparison included two adjacent ROM bytes);
a natural five-bit field in a four-byte record (48 bytes, rejected at the
extent gate before CFG/plausibility); a positive-index guard with explicit
low/high portions (56 bytes, plausible, 50/56 bytes); and the preserved
named-mask byte decode (56 bytes, plausible, 50/56 bytes). No asm, forced
registers, artificial volatile, compiler flags, forced inline or padding.
The last native report is saved in address scratch as last-native-report.md.
