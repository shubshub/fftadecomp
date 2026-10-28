# 08016A08 — bounded natural reconstruction

The complete function draws four corner tile entries and the horizontal top/bottom frame edges. Width and height must exceed one. Tile 0x32 uses palette 11; horizontal/vertical flip bits are 0x400/0x800. The recovered TileEntry union describes that actual halfword format. Width, height and stride are unsigned bytes; offsets are unsigned halfwords.

Native fixed agbcc `-mthumb-interwork -O2` produced one complete 144-byte ELF function with 67 verified reachable instructions and no relocations. The source passed plausibility. Native match exited 1: 65/67 instructions and 140/144 same-offset bytes agree.

Exactly two commutative pointer additions differ:

- 0x08016A34: ROM `adds r2, r2, r5`; candidate `adds r2, r5, r2`.
- 0x08016A42: ROM `adds r0, r1, r5`; candidate `adds r0, r5, r1`.

Every other instruction, the complete alignment gap and both literal words match. This is not an exact match and earns zero match credit.

Bounded natural reconstructions covered a generic inline tile-frame helper, the recovered GBA tile-entry bitfields, halfword row offsets, and explicit corner/row pointers. The direct scalar tile form constant-folded into six literals. The bitfield union preserves the actual tile representation and recovers the ROM's shared base-plus-flip arithmetic. Ordinary commutative pointer-add spellings produce the same two remaining instruction encodings. No assembly, flag changes, volatile, padding, artificial control flow or register-steering workaround was used.

The untouched compiler-emitted ELF is preserved outside the disposable matching root at `../08016A08/original.o` relative to this matching root. Exact native logs, unmatched report, compiler assembly and frozen-result.json are in the same address scratch directory. Active unmatched source/report were removed after parking this tested candidate.
