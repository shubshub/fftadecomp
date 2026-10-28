# 080CD4D4 — Parked

Target: 54 bytes / 24 reachable instructions, 080CD4D4..080CD50A. A null object or zero byte at offset 0x3A returns zero. Otherwise the byte at offset 6 selects an entry table from g_table_0851BA84; the byte at offset 0x3A selects an eight-byte record, and the function returns its byte at record offset 4.

The preserved complete natural C was freshly compiled with the unchanged native gate: exit 1, complete 54-byte ELF symbol, closed leaf CFG, no relocations, plausible C. Native comparison reports 36/54 bytes and 9/24 instructions identical.

Remaining gap: target retains the object in r0, copies its nullable index address into r1 only after the null test, and keeps the nullable value in r1. The candidate saves the object in r1 before testing it, then reads/compares the nullable index in r0. The lookup consequently uses different kind/index/base/result registers and a different table-load/shift order. The candidate preserves both index-byte loads and the target's complete extent, null/zero behavior, record stride, member offsets, and return branches.

Bounded tested forms: direct byte ternary plus positive guarded lookup emitted 56 bytes; an early zero return emitted 54 bytes (33/54 bytes identical); a nullable inline getter with named lookup inputs emitted 54 bytes (36/54 bytes identical); promoted ternary and explicit if/else nullable checks with named lookup inputs produced the same complete 54-byte code; byte versus unsigned-int wrapper return types also produced the same complete code. The preserved final explicit-if/else candidate has an unsigned-int return type. No variant removed an executable target operation, and no compiler flags or verifier boundaries were changed.

Unmatched active source and report were removed. Last native report is retained in the private address scratch as last-native-report.md.
