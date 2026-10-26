# 080B4C90: recovered, not byte matching

Complete target: `0x080B4C90..0x080B4D6E`, 222 bytes including literal pools, 98 reachable Thumb instructions.

The preserved complete natural C candidate passed native source plausibility and compiled to the full 222-byte ELF symbol under fixed agbcc `-mthumb-interwork -O2`. Native matching exited 1: bytes differ. Best aligned diff score was 73/94 decoded instructions and 189/222 bytes; pool placement affects that decoder's instruction count. Actual same-offset equality is 102/222 bytes. This is not a match and earns no match credit.

Recovered behavior includes the three-category exemption scan, object eligibility check, zero-identifier path, selection flags, all three selection passes and their calls, and final boolean result. The remaining native gap is object storage in r8 rather than target r7, the accumulated result in r7 rather than target r8, an extra right shift normalizing the zero-identifier byte return, and resulting store moves, branch offsets, alignment, and literal-pool placement.

Bounded natural forms tried: flat versus nested selection-state access; a cached selection pointer; direct boolean returns versus shared positive/negative result tests; u8 and u32 result accumulators; signed-byte loop-counter initialization before pointer setup; a coherent inline selection-evaluation helper; and a conditional expression selecting the zero-identifier or selection result. Candidates ranged from 208 to 222 bytes. The preserved 222-byte candidate had the best aligned score. The final helper/conditional-expression form also reached 222 bytes but scored 69/94 decoded instructions and 188/222 aligned bytes. No asm, volatile, pragmas, dead code, or compiler steering was used. These attempts do not establish permanent impossibility at the fixed flags.

Source-bound native evidence remains in the private address scratch directory as `best-report.md` and `best-native-output.txt`, alongside the full target capture. Unmatched active source/report were removed.
