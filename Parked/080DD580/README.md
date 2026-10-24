# 0x080DD580: normalized bit-7 predicate, not matching

Fixed `agbcc -mthumb-interwork -O2` produces the correct complete 24-byte Thumb function, but one instruction is scheduled differently. Compiled `movs r2,#0` appears immediately after `push {lr}`; the ROM places it after `ldrh r0,[r0,#12]; lsrs r0,r0,#7; movs r1,#1`. The other eleven instructions, all registers, branch target, loads and return agree. This displacement affects byte positions 2 through 9: positional equality is 16/24 bytes. The toolkit's aligned-instruction summary reports 11/12 instructions and 22/24 aligned bytes, not positional equality.

The source returns a byte boolean for bit 7 of the u16 flags at object offset +0x0C. The raw-bit inline helper follows the actual neighboring extractor at 080DD574. Explicit result initialization and conditional assignment follow the normalized predicate's observed control flow. Unknown prefix bytes express only the known offset; the whole game-object size and original typedefs remain unknown.

Two immutable candidates were checked. Returning the raw getter's equality with 1 directly yields 24 bytes but changes the result register and zero placement (9/12 aligned instructions). This explicit-result candidate reaches 11/12. Further declaration/initialization moves would target instruction order without new semantic evidence and were not attempted.

Targeted verification passes 40 native-C cases, 80 ROM cases, 80 compiled-Thumb cases and 16 real caller windows. Both return modes, unrelated low/high flag bits, exact field read, unchanged object and saved-register/SP restoration are checked. Caller witnesses are `080DDE1C -> BL080DDE5C` and `080DF9E4 -> BL080DF9F4`.

No matched source or success report is supplied. The author bundle contains the full diff, chronology and checksums. Its metadata patch proposes size 000010 -> 000018 only; do not mistake that independent index correction for a successful C match.
