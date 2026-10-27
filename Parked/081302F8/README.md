# 081302F8

Bounded natural-C attempt using fixed agbcc `-mthumb-interwork -O2`.

The complete indexed ROM target is `081302F8..0813034A`, 82 bytes and 38 reachable instructions. The preserved candidate emits one 80-byte ELF function symbol, with 37 instructions. The fresh native matcher exits 1 at the extent gate: `compiled symbol is shorter than the indexed span: 80 < 82`. It does not reach the byte-comparison or plausibility verdict, so this is not a match or a native plausibility acceptance.

The remaining difference is argument register allocation around the first height lookup. The ROM retains the first coordinate pair in r1/r2, then copies them to r0/r1 before calling 0801CC18. The candidate narrows that pair into r4/r1 and needs only the r4-to-r0 copy. It also swaps the saved registers used for the second coordinate pair (candidate r6/r5, ROM r5/r6). Both forms then narrow the byte lookup results, subtract them, call 0813034C, and sign-extend its halfword result; branch/call displacements differ with the two-byte extent change.

Tested a direct subtraction expression, explicit byte/word lookup locals, an accumulated signed halfword difference, and the preserved semantic height-difference helper. They remain 80 bytes. The helper naturally inlines; object inspection shows only the target FUNC. The existing 0801CC18 source confirms byte arguments and a byte return. No compiler flags, assembly, volatile accesses, artificial statements, shared declarations, or metadata were changed.

The unmatched active source/report were removed. Parent integration owns reservation release.
