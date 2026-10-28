# 0802DC60 — parked

Target: [0x0802DC60, 0x0802DD58), 248 bytes / 117 reachable instructions.

The retained packed-record C candidate is plausible but does not match. Fixed agbcc -mthumb-interwork -O2 emits a complete 250-byte ELF symbol, two bytes beyond the indexed function. Native matcher exits 1: 194/250 bytes and 72/116 candidate instructions identical in its complete-symbol comparison; 39/248 indexed bytes identical. The comparison includes two following-ROM bytes, which receive no function credit. Native report retained in private address scratch/native-report.md.

The candidate keeps owner in sl and active in sb rather than spilling owner and keeping active in sl. This changes the loop count/mask registers and removes the target's four-byte local stack allocation. Boolean conversion uses negate/OR/shift instead of the target's negate/shift. The candidate separately stores rank and clears its upper five bits; the target merges those updates into each branch, using a direct zero byte store for the null-member case. The packed u8 owner/option fields also reuse the mask register where the target uses separate masks. Pool placement, call displacements and branch offsets consequently differ.

Tested natural forms: ordinary aligned u32 bitfields (226 bytes); packed u32 bitfields with sequential rank/upper-bit assignments (254 bytes); packed u8 fields (retained, 250 bytes); and packed u32 fields with a conditional rank assignment (234 bytes). The 226- and 234-byte forms failed the complete-span check. The 254-byte form was plausible, with 196/254 bytes and 73/118 candidate instructions identical, including six bytes beyond the indexed target. No compiler flags, mappings, headers, or target bounds were changed.
