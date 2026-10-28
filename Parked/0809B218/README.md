# 0809B218 — unmatched natural C

Target: 0x0809B218..0x0809B470, complete 600 bytes / 286 captured reachable instructions.

The last default native matcher invocation exited 1. The candidate is plausible and its complete ELF symbol spans 600 bytes, but bytes differ. Native alignment reports 227/285 instructions and 520/600 bytes identical; a direct same-offset comparison finds 389/600 equal bytes. The aligned byte score is not a same-offset match count.

The packed-point construction, Manhattan distance, fixed-point time/height conversions, mode branches, coefficient call, and inclusive sampling loop are implemented. Remaining differences include allocation of the object pointer to stack slot 8 rather than sl, distance in sl rather than ip, displaced packed-point stack slots, and corresponding pointer allocation in the sample loop. The candidate additionally shares the case-1 height store differently, changing branch offsets and the reachable instruction count. The target uses sample cursor r4, times pointer r8, distance pointer sb, and object sl through the loop; the candidate uses a different assignment of those values.

Bounded natural reconstructions tested: reordered switch cases, early output-cursor initialization, separate store/cursor advancement, a generic callback argument with typed object local, and explicit interpolation-array locals. Early cursor initialization and explicit array locals produced short symbols (596 and 588 bytes); the remaining forms did not improve the complete candidate. No assembly, volatile, forced registers, compiler changes, dead operations, or shared-file edits were used.

The preserved candidate is the best complete tested form, restored and rerun freshly. Raw C SHA-256: b13f87639a6b546f8dc1bc3085f6b0efe2a0f1d77ad7c7c999ea592cc5cf02e4. Native report SHA-256: 9df2fa1650205a577468cfbfe162700af10fbcc3dc39c1f738515507359f57b9. The native report and command output remain in the address scratch directory as last-native-report.md and native-output.txt. Unmatched active private source and report were removed.
