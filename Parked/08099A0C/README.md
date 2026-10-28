# 08099A0C — unmatched

Target: complete `[0x08099A0C, 0x08099A46)`, 58 bytes / 28 instructions in the captured target.

The retained complete candidate calls `func_0809E830(owner, object, 0)` when the objects differ, stores its return value as a halfword at offset 0x5C, and returns zero only when the other object is nonnull and the full return value is zero. When both pointers identify the same object, it clears the halfword and returns one.

Fresh final native result: exit 1, complete 58-byte compiled extent, source plausible, bytes differ. Native readout: `25/27 instructions identical (51/58 bytes)`; this is not a match.

Remaining gap: the target explicitly copies saved r4 into r0 before adding 0x80 and loading the owner. The candidate reuses the original r0. In the equal-object branch, the target uses the original r1 directly for the halfword address, while the candidate reloads saved r5 into r1. Those placements also shift the conditional-branch and call encodings. The rest of the visible operation sequence agrees.

Bounded source families tested:

- Early-return form, with both equality/inequality branch order and either equal pointer used for the clearing store: same 58-byte result, retained.
- A return-status variable initialized to one: 60 bytes with an additional saved register and changed branch layout.
- A return-status variable assigned in both branches: 60 bytes with changed branch layout and boolean materialization.

The best first form was restored and freshly matched before parking. No assembly, padding, volatile access, register variables, or compiler flag changes were used. The unmatched active source/report were removed; the last generated report remains in private address scratch as `last-native-report.md`.
