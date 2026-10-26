# 080894AC

Bounded natural-C attempt; not a match.

The complete target is `[0x080894AC, 0x0808953E)`: 146 bytes including middle literal pools and 63 reachable Thumb instructions. The preserved complete recovered C body compiles to a 142-byte ELF symbol under fixed agbcc `-mthumb-interwork -O2`. Fresh native matcher exit 1: `compiled symbol is shorter than the indexed span: 142 < 146`. The tool stops at that check, so no linked byte comparison, instruction-match count, or plausibility verdict was generated. No match credit.

Recovered behavior: select the pointer at offset 0x18 or 0x1C from a 0x4C-byte record; fill `count << 10` halfwords with tile values chosen by index bits 1 and 0, adding 0x0800 when index bit 5 is set.

Remaining native-code gap: target holds the masks 1, 0x20, and 0x0800 in r6, r5, and r7. The preserved form uses r7, r6, and r5, with an additional setup copy. At the final conditional value merge, target emits `lsls r0,r3,#16; lsrs r0,r0,#16` for the unflagged branch followed by `mov r3,r0; strh r3,[r2]`; the preserved form uses `mov r0,r3` for the unflagged branch and `strh r0,[r2]`. Buffer selection, signed loop bound, tile-selection branches, and conditional flag operation are recovered.

Tested forms: initialized u16 tile with increment/decrement (128 bytes); integer tile selection plus u16 output (preserved, 142 bytes); one u16 tile with conditional assignment (140 bytes); whole-result halfword cast (128 bytes); integer tile with narrowing on the unflagged branch (140 bytes); reversed OR operands (140 bytes). The preserved 142-byte form was rerun unchanged and again rejected at the same extent check. Flags and metadata were unchanged; no assembly, volatile accesses, or compiler pragmas were used.

Unmatched active source/report were removed. The fresh native rejection text remains in private address scratch.
