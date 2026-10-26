# 08089E1C — Parked

Target: 0x08089E1C..0x08089EB4, complete 152 bytes / 76 reachable Thumb instructions.

The preserved candidate copies a signed-byte rectangle of halfword tiles between surfaces. Source point and destination rectangle are passed by value. Tile pointers are at offset 0x1C and unsigned byte row strides at offset 0x28. Nonpositive width or height copies no tiles.

Fresh default native matching with agbcc `-mthumb-interwork -O2` exits 1 before byte/plausibility comparison: `compiled symbol is shorter than the indexed span: 136 < 152`. The complete candidate is 136 bytes / 68 Thumb instructions, ending at 0x08089EA4 when placed at the target start. No exact-match credit is claimed.

The target hoists a signed width extraction followed by another byte-width conversion (`lsl 24; asr 24`), retaining both the shifted width in r7 and signed guard in sb. It spills the source x-adjusted base and source y to an 8-byte frame, keeps source in r8, destination in ip, rectangle in r6, and destination x-adjusted base in sl. The candidate extracts width once per row, has no stack frame, and uses r7/source, r4/row, sl/source base, sb/source y, and r8/destination base. Both use a positive-width guard and decrement-to-zero halfword-copy loop; register lifetimes and invariant width handling remain different.

Bounded natural attempts included ascending integer columns (136 bytes), signed-byte columns (168 bytes with narrowing in each iteration), unsigned-byte columns (152 bytes with an ascending narrowed loop rather than target countdown), signed-halfword columns (164 bytes), byte countdown (142 bytes), and the preserved guarded integer countdown (136 bytes). Plain byte rectangle members and signed 8-bit bitfield members were tested. A byte width local and signed interpretation of an unsigned width local did not produce the target's additional hoisted conversion. No assembly, volatile accesses, compiler changes, padding, or artificial operations were added.

Unmatched active source and generated report were removed. Native refusal is retained in the address scratch directory.
