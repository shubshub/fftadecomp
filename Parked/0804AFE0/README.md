# 0804AFE0

Full target: `[0x0804AFE0, 0x0804B7E6)`, 2054 bytes / 773 instructions.

Best tested complete natural C builds to 2054 bytes with the fixed agbcc `-mthumb-interwork -O2` configuration. Native matching exits 1: source plausibility passes, with 772/773 instructions and 2052/2054 bytes identical under the native report comparison.

The only remaining difference is an independent constant initialization in the menu-position loop. Target addresses `0x0804B136..0x0804B13A` contain `movs r4, #69; movs r0, #116; mov ip, r0`. The candidate emits `movs r0, #116; mov ip, r0; movs r4, #69`. All other instructions, literal pools, calls and function extent match.

Bounded natural attempts covered a computed row coordinate, an explicit coordinate induction variable, a local coordinate value, a while loop, and direct vertical-spacing arithmetic. The explicit induction variable also moved initialization before the loop guard and changed increment order. Narrowing the local coordinate generated additional instructions. The retained source is the complete plausible candidate with the single reordered initializer; no assembly, volatile values, compiler barriers, fixed registers or artificial scheduling was used.

Latest native output and generated report are retained in the private address scratch directory as `native-output.txt` and `last-native-report.md`. Unmatched private `src/0804AFE0.c` and `docs/match/0804AFE0.md` have been removed.
