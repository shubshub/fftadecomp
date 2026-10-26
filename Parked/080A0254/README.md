# 080A0254 — bounded natural-C attempt

Target: `[0x080A0254, 0x080A0466)`, 530 bytes / 251 reachable instructions. The candidate implements the complete indexed validation, fallback, height, axis, diagonal and Manhattan-range body.

The best candidate was freshly rerun with the default native matcher and fixed agbcc `-mthumb-interwork -O2`: exit 1, source plausible, bytes differ. Its complete ELF symbol is 542 bytes, 12 bytes longer than the indexed target. Native alignment reports 204/255 instructions and 490/542 bytes identical; that comparison extends 12 bytes past the indexed target. Direct same-offset comparison within the actual 530-byte target matches 356/530 bytes.

Remaining differences:

- The mask literal is loaded directly into r0; target loads r1 and copies to r0. Signed height limit and first height result occupy opposite r4/r5 registers, and the first height result is narrowed after the second call rather than before it.
- The axis-range boolean comparison remains separate from the case-0x40 comparison. Target shares the second absolute-value/comparison tail; candidate emits an additional comparison/return sequence. Diagonal-case instructions otherwise align, with subsequent branch targets shifted by the extra code.
- Axis temporary register choices and the switch mask-load register differ. Prologue and validation/fallback instruction shapes align apart from shifted long-branch destinations.

Bounded attempts covered signed/unsigned coordinate normalization with the signed fallback ABI preserved in the retained candidate, manual versus builtin absolute values, signed halfword distances and maximum, explicit versus combined height-call temporaries, and equivalent range-comparison orientation. A shared comparison form produced a short 508-byte symbol; explicit height locals with the original comparison produced 546 bytes. The tested 542-byte plausible form is retained here. No compiler flags, shared mappings, headers or checker changes were made.

Fresh native output and the unmodified generated report are retained in the private address scratch directory as `native-output.txt` and `last-native-report.md`. Unmatched active source/report were removed. This is not an exact match.
