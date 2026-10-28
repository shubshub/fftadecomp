# 08016E88: complete reconstruction, remaining register allocation gap

Target: complete [0x08016E88, 0x08016FE4), 348 bytes / 171 reachable instructions.
Compiler: agbcc -mthumb-interwork -O2, unchanged native matcher and approved ROM.
Final native result: exit 1, NOT MATCHING; complete 348-byte ELF symbol,
source plausible, no relocations. Native aligned comparison: 147/171
instructions, 322/348 bytes. Same-offset byte equality: 322/348.

The function measures left and right labels, derives bounded fill intervals
from alignment flags and available width, selects a halfword buffer and
palette/tile base, then writes sequential 16-bit tile values. Both fill
blocks, calls, branches, frame layout and return are reconstructed.

The remaining differences are operand registers at unchanged instruction
positions. At 0x08016EE2 and 0x08016EEE the target puts the initial index in
r3, while this candidate uses r4. Within both fill loops the target keeps the
16-bit tile value in r4 and the countdown in r3; this candidate swaps those
roles. The second measured length at 0x08016F5A uses target r2 versus candidate
r3, propagating into the subsequent arithmetic. No branch destinations or
call targets differ.

Bounded natural attempts:

- A separate u8 starting bound followed by a signed loop variable emitted
  368 bytes and one additional saved high register.
- Assigning the narrowed bound directly to the signed loop variable recovered
  the exact 348-byte extent and frame, leaving the register differences above.
- Grouping the ordinary local declarations did not change that result.
- A genuine shared sequential-fill inline helper fully inlined, but emitted
  370 bytes with extra copies and an additional saved high register; it was
  removed from the best candidate.

The preserved C was freshly rerun after restoring the simpler loops. No
assembly, volatile, optimization changes, forced inlining, or checker changes
were used. Unmatched active source/report were removed. Final native output
and report remain in the private address scratch directory.
