# 080DA2D4

Parked complete natural-C attempt; no match credit.

- Target: `[0x080DA2D4, 0x080DA3B8)`, 228 bytes and 112 reachable instructions.
- Final native matcher: exit 1, `NOT MATCHING - bytes differ`.
- Retained complete ELF symbol: 230 bytes; native source plausibility passed.
- Fixed compiler: agbcc `-mthumb-interwork -O2`.
- The first 134 bytes match at the same offsets. Across the original 228-byte target span, 145/228 bytes match at the same offsets. The tool's aligned diff score is not an equality claim and includes a comparison window extending beyond the original target when the candidate is longer.

The source finds minimum/maximum Y vertices, writes the minimum index, selects two wrapped subsequent vertices through func_08141874, and returns the sign test of their cross product. The signed scan counter reproduces the target's countdown loop and shifted induction value. The final retained source matches the scan, first wrapped-index call, coordinate loads, and cross-product instruction structure.

The remaining discrepancy starts in preparation of the second wrapped index. The target copies maximum from sb to r1, compares r1 with the previous wrapped index, and conditionally increments/narrows the working value in r1. The candidate compares sb directly and updates/narrows maximum in sb, then copies it back for the call; this adds one instruction (two bytes). The candidate also emits the third-point address addition with commuted operands (`adds r0, r7, r0` versus target `adds r0, r0, r7`). Following calls/branches move by two bytes.

A 16-bit scan counter produced 218 bytes and did not reproduce the target loop. Signed scan plus unsigned-short wrapped indices recovered the target scan. Separate and scoped successor locals and a conditional call argument produced 222-byte symbols with different register allocation; reusing the previous wrapped-index local produced 224 bytes. The retained 230-byte source is the closest tested native-diff candidate. No assembly, volatile operations, compiler-option changes, forced inlining, or emission controls were used.

Final native log: `../../../080DA2D4/match-current.log` relative to this directory. Active unmatched source/report were removed. Root owns integration and reservation release.
