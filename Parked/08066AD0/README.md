# 0x08066AD0 — bounded natural C attempt

Complete target: `[0x08066AD0, 0x08066BC4)`, 244 bytes and 102 reachable instructions. Fixed compiler: agbcc `-mthumb-interwork -O2`.

The preserved candidate implements cancel/confirm handling and wrapping left/right selection. A fresh native match exits 1 with a complete 244-byte symbol and source plausibility accepted: 242/244 bytes and 100/102 instructions identical.

The only remaining difference is the destination register in the cancel branch flag update:

- At `0x08066B18`, target `orrs r0, r1` (`0843`); candidate `orrs r1, r0` (`0143`).
- At `0x08066B1A`, target `strh r0, [r4, #4]` (`a080`); candidate `strh r1, [r4, #4]` (`a180`).

Eight natural candidate forms were tested. Direct compound updates merge the cancel/confirm tails and shorten the symbol; a shared completion label and explicit decrement local recover the target control flow. The preserved u16 flag accumulator keeps the complete extent and all other bytes. Initializing the accumulator from its mask, using a structured common return, or assigning binary-OR expressions permits tail merging again. Separate branch-local accumulators shorten the symbol to 236 bytes. A u32 accumulator retains 244 bytes but changes constant materialization and leaves the destination-register gap. No compiler flags, assembly, volatile, dead code, or shared files were changed.

The unmatched private source and generated match report were removed. Fresh native output and the report are retained in the address scratch directory.
