# 080D7150 — Parked

The complete indexed target spans 0x080D7150..0x080D71A8: 88 bytes and 44 reachable Thumb instructions. The reconstruction expands each input byte into its low and high nibbles, writes both output pixels, and adds the palette high nibble only to nonzero pixels. Both loop counters retain the observed u16 truncation.

The final canonical native match exited 1 with `compiled symbol is shorter than the indexed span: 74 < 88`. Its generated assembly contains 37 Thumb instructions. The matcher stopped before plausibility and the full byte/instruction comparison, so neither is credited.

The remaining gap is register allocation and its associated setup/copy instructions. The target saves r8 and keeps input in r8, output in r4, length in r7, palette in r6, and the nibble mask in ip. The candidate keeps input in ip, output in r4, length in r6, palette in r5, and the mask in r7. The target retains the next outer index separately in r5 while using r1 for the decoded pixel; the candidate increments its outer index in r2 and uses r0 for the pixel. The target also copies its mask and palette into low registers within the inner loop. These differences account for the shorter prologue, body, and epilogue; no exact match is claimed.

Bounded natural attempts covered direct nested loops, u8/u32 pixel and packed-byte types, explicit palette composition, a pixel-writing inline helper, and a byte-expansion inline helper. Direct and pixel-helper forms produced 74 bytes; the byte-expansion helper produced 72 bytes. The final direct reconstruction was restored and freshly retested at 74 bytes. No flags, assembly, volatile accesses, or register-steering constructs were used.

Final native output and generated assembly are retained in the sibling address scratch directory as `native-output.txt` and `candidate.s`. The unmatched active source and report have been removed.
