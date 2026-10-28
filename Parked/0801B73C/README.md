# 0801B73C — bounded natural-source encoding mismatch

Target: `0801B73C..0801B796`, 90 bytes / 44 reachable instructions.
The preserved candidate was tested with unchanged `agbcc -mthumb-interwork
-O2` and produces a complete 90-byte / 44-instruction ELF symbol. Native
extent/CFG/typed-linking and source plausibility passed; byte comparison
returned `NOT MATCHING`, exit 1. No match credit is claimed.

The native aligned diff score is 43/44 instructions and 88/90 bytes.
The sole instruction difference is the final tile-address addition:

- Target: `adds r0, r5, r0`.
- Compiled: `adds r0, r0, r5`.

These commute to the same address, but their instruction encodings differ.
All remaining instructions, including byte-index normalization, signed bounds,
64-column indexing, call, and clipped nested loops, agree with the target.

A 64-cell row-array type changed the address calculation and register
allocation (36/44 native instruction score). A named unsigned linear index
and an integer byte-address form retained the original one-instruction gap.
The simplest tested flat u16-pointer version is preserved. No assembly,
volatile RAM, forced inline, compiler changes, artificial instructions, or
commuted-subscript tricks were used to force that encoding. Unmatched active
source and report were removed.
