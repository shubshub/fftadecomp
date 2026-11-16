# 0x08003A08 - DMA busy wait at -O0: code bytes identical, refused by two verifier gaps (54 bytes)

Retry 2026-11-16, kit fcdf2d45. Source in the spelling of matched sibling src/08003A40.c (same first 14 instructions): look up the
channel's register block in data_0836D480 and spin while bit 31 of the control word is set. Compiled with agbcc -O0
all 50 code bytes and the pool word (the data_0836D480 relocation) equal the ROM, including the r7 frame, spills,
the `lsrs #31; lsls #31` test and the `bne; b exit; pool; b top` loop. plausible.py exit 0. No volatile: at -O0
every access reloads, and 08003A40 declares the table without it.

Refusals (`--flags "-mthumb-interwork -O0" --owner-runtime-profile compiler-orphan-address-constants-O0-v1`, the
profile of the six merged -O0 boot functions):
1. `orphan prerequisite requires sole complete sized Thumb function` (tools/compiler_orphan_constants_prerequisite.py:134-136):
   the assembler pads .text to 4 bytes with a trailing nop, so .text is 56 bytes for a 54-byte symbol. All six merged
   -O0 functions are multiples of 4.
2. With that check limited to the symbol (diagnostic kit copy only): `acyclic path states reject reachable CFG cycles`
   (tools/match.py:5090) - the O0 replay uses the acyclic owner selector, so no loop is admitted (0x08003A1E-0x08003A34).
Without the profile: `unexpected nonempty allocated section` (.rodata orphan); at -O2: 36 < 54 bytes.
Needs: the O0 prerequisite to accept trailing alignment padding, and an O0 replay that admits a bounded wait loop.
Index row `08003A08 08003A3E 54 25 return` correct; no data symbols needed. 0x08000718 (DMA wait loop) has the same gap.
