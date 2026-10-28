# 081342CC — parked

Target: complete indexed [0x081342CC, 0x081343C8), 252 bytes / 112 reachable instructions. Fixed agbcc -mthumb-interwork -O2; approved ROM; native matcher used.

Three bounded natural candidates were attempted:

1. Direct bit expressions and flat state fields: native exit 1, plausible source, 252-byte symbol; native comparison 75/104 instructions and 204/252 bytes identical. Register allocation and bit-test evaluation differ; marker halfword stores form +0x78 and store at offset zero.
2. Inline bit-test helper with local byte and shift values, nested context at state+0x60: native exit 1 because compiled symbol is only 244 bytes. Diagnostic assembly reproduces the target's initial argument registers, bit tests, and loop preparation, but selects literal g_state_0200F390+0x70 and stores at offsets 0/4/8. Target loads g_state_0200F390 itself, stores words at +0x70/+0x74, and forms +0x60 before each halfword store at +0x18.
3. Flat state fields plus an inline context-value reset: native exit 1, plausible source, 260-byte symbol; native comparison 76/105 instructions and 220/260 bytes identical. The compiler hoists g_state_0200F390+0x60 into an additional saved register and literal, changing the frame and extent.

The remaining issue is aggregate/address-expression representation for the overlapping global state. This is not the known unused-load-before-store family. No asm, volatile, pragmas, fixed registers, compiler changes, or shared edits were used. Nonmatching src/081342CC.c and docs/match/081342CC.md were removed. The final candidate is retained as 081342CC.c. The native report and attempt-2 assembly are in the private address directory.

Claim 6406395850 (codex-sol61-v59-081342cc); root owns release.
