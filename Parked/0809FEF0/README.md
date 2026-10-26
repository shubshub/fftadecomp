# 0809FEF0 recovered, not matched

Target: complete indexed 0x0809FEF0..0x080A0012, 290 bytes and 140 reachable Thumb instructions.

The preserved natural C recovers target-cell validation, terrain flag rejection, source/target equality rejection, the three special identifier types, the alternate-mode helper result handling, and signed Manhattan-distance/range fallback.

The fixed native matcher with agbcc `-mthumb-interwork -O2` accepted source plausibility and verified the complete 290-byte ELF symbol, but returned exit 1: 266/290 bytes equal and 118/140 instructions aligned. The candidate reserves a 32-byte local frame rather than the target 28 bytes. It allocates the identifier and target-x temporary differently and spills target-x to `[sp, #0x1c]`; the target keeps this value in r8 and reuses sl for target-y. The resulting register operands, frame adjustment, and incoming stacked-argument offsets account for the remaining differences. The calls, branch locations, return cases, signed arithmetic, and symbol extent align.

Bounded natural forms tried: unsigned coordinate parameters produced a short 250-byte body; signed byte parameters produced the preserved complete body. Signed/unsigned range and boolean local widths, a promoted helper-result local, and scoped fallback declarations retained the same 290-byte mismatch. A switch for the three excluded types shortened the symbol to 288 bytes. Explicit signed coordinate locals produced a 292-byte body with the desired 28-byte frame but different entry normalization and stack-slot placement. A byte return type did not change the best mismatch. No compiler flags, assembly, volatile accesses, or steering constructs were introduced.

Native evidence is retained in the address scratch directory as `best-report.md`; the preserved candidate is unchanged from the source tested for that report. No match credit is claimed, and this is a bounded unresolved allocation gap rather than a claim of permanent impossibility.
