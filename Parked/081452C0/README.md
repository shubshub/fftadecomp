# 081452C0

Target and preserved candidate both have complete 52-byte function symbols.
Native match.py exits 1: direct-Thumb-call CFG accepted, source plausible,
47/52 bytes and 15/20 reachable instructions identical. No match credit.

The function narrows its song index to u16, looks up an eight-byte song record,
uses its halfword player index to select a twelve-byte player-table record,
and compares the player's current header with the requested song header.
Matching headers cause a call to 08145100 with the player pointer.

The remaining mismatch is register allocation: ROM holds the player-table
base in R2 and its index in R3. The candidate holds the base in R3 and the
index in R2. This changes five instruction bytes in the table-base LDR,
index LDRH and stride/address calculations. Header comparison, branch,
call, return, literal values and complete extent match.

Bounded tested forms: named table-base pointers with direct indexing;
an explicit promoted u32 player-index local (same bytes); direct global
table expressions (same extent, reordered loads/pool, 42/52 bytes); and
the preserved named-base pointer-addition form (47/52 bytes). No asm,
forced registers, artificial volatile, flag changes or padding were used.
The last native report is saved in address scratch as last-native-report.md.
