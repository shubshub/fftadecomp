# 08038028 — parked

Target: [0x08038028, 0x08038238), 528 bytes / 244 reachable instructions.

The retained natural C reconstructs all four rendering branches, signed byte offsets, flag tests and eleven outgoing arguments. Its branch-local record pointers compile with fixed agbcc -mthumb-interwork -O2 to a complete 524-byte ELF function symbol. Native matcher exits 1 at the complete-span check (524 < 528), so it issues no byte comparison or plausibility verdict.

The retained form calculates each record pointer before loading the graphics pointer. The target loads graphics first, retains the incoming index in ip and then materializes the record address while evaluating coordinates. The target also copies the incoming panel pointer to r4 before the flag branches and retains that copy in its final branch. The retained candidate keeps the index in r2 and the panel in r6, without that initial panel copy. The resulting multiply operands, scratch registers and literal-pool order differ. All coordinate-field loads, signed extensions, flag narrowings and call arguments are present; the remainder is address/value lifetime and evaluation order rather than an identified missing data read.

Tested natural forms: direct indexed structure accesses (508 bytes); signed index with direct accesses (508 bytes); per-branch record pointers (retained, 524 bytes); and an inline record accessor used in coordinate expressions (512 bytes). Every form failed the native complete-span check. No flags, headers, mappings, target boundaries or compiler-generated assembly were modified.
