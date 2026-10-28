# 080D2CC4 — Parked

Captured target: 144 bytes / 64 reachable instructions, 080D2CC4..080D2D54.

The preserved complete natural C uses the selected ID at global-state offset 0x3C28 to search the linked list at offset 0x28C8. Each packed item has a ten-bit ID and two table indices at offsets 4 and 5. For each nonzero index, the function checks bit (kind - 1) of the byte at offset 7 of a sixteen-byte record in g_table_08521214, returning a byte boolean.

Fresh native matcher exit 1 on the restored best candidate: compiled complete symbol is 140 bytes, shorter than the indexed 144-byte span. The native gate stops at that extent failure; CFG, plausibility, and byte comparison were not reached for the preserved candidate. No exact instruction or byte-match count is claimed.

The closest diagnostic assembly has a different search return allocation/layout: node traversal uses r3 and the item/result uses r2, while target traversal uses r2, loads the item into r3, and has a separate found-result copy/branch before the loop body. Its flag-table inputs also use index r0/base r1 instead of target index r1/base r0. Literal-pool placement and entry/exit branches consequently differ. Packed ten-bit ID decoding and promoted signed arithmetic flag shifts are represented naturally.

Bounded forms tested: direct while search and direct flag checks emitted 136 bytes; explicit head and flag-query helpers also emitted 136 bytes; a guarded do/while search emitted 140 bytes; direct node-member return and byte flag-query return preserved 140 bytes; an initialized common search result with break grew to 152 bytes, passed native plausibility/complete closed-leaf proof, but had worse allocation/layout. The 140-byte guarded direct-return form was restored and freshly recompiled before parking. The 152-byte variant report is retained separately in address scratch as common-result-native-report.md and is not evidence for the preserved candidate.

Unmatched active source/report were removed. Obsolete private preprocessor/assembly diagnostic scratch was removed. Fixed native compiler flags and verifier boundaries were unchanged.
