# 080CCCA0

Complete recovered implementation for 0x080CCCA0..0x080CCCF0: 80 bytes,
37 reachable instructions, including the literal pool. The routine scans 24
264-byte records after a 0x80-byte global header and calls 080CC65C for active,
non-busy records whose halfword flags contain bit 3.

The best tested candidate is plausible under the fixed native agbcc
`-mthumb-interwork -O2` command, but is not byte identical: 35/37 instructions
and 76/80 bytes match. Same-offset byte equality is also 76/80. Only these two
commutative additions differ; every other byte, including the pool, agrees:

- 080CCCB0: target `adds r1, r2, r5` (5119), candidate
  `adds r1, r5, r2` (a918).
- 080CCCD6: target `adds r0, r2, r6` (9019), candidate
  `adds r0, r6, r2` (b018).

Natural forms tried: direct indexed access through the global pool (80 bytes,
29/37 aligned instructions); a cached pointer to the records (80 bytes,
33/37); initializing the byte index before the pointers and using a do-while
loop (the preserved 80-byte candidate, 35/37); and pointer-arithmetic access
instead of array indexing (76-byte symbol, rejected as shorter than the full
indexed span). The preserved source is the unchanged best tested indexed
do-while candidate. No flags, shared metadata, or verification rules changed.
This is a bounded unresolved source-generation gap, not an impossibility claim.
