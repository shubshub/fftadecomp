# 080CBDC0

Complete plausible C reconstructs the 370-byte indexed target (167 reachable
instructions). It builds an item list filtered by category and rank flags,
then appends qualifying owner items while copying inventory quantities and
the adjacent record byte.

The fixed native matcher (`agbcc -mthumb-interwork -O2`) exits 1: the complete
ELF extent is exactly 370 bytes, source is plausible, and the supported direct
Thumb-call/ordinary ARM ABI profile reaches byte comparison. The best tested
candidate matches 368/370 bytes and 165/167 instructions.

The only remaining differences are commuted address-add operands:

- 080CBE4C: target `adds r4, r0, r1`; compiled `adds r4, r1, r0`.
- 080CBECA: target `adds r4, r0, r1`; compiled `adds r4, r1, r0`.

Both calculate the selected output record from its scaled index and buffer
base. Only the first encoding byte differs at each site (target 44, compiled
0C); all other complete-function bytes are identical.

Tested natural forms: scoped record temporaries with signed range locals
(358-byte extent, stopping at the extent gate); shared record/index locals
and unsigned 16-bit range locals (370 bytes); range/mask declaration order;
initializing the range iterator before the output count and expressing the
bound as length plus first; an opaque byte-buffer output declaration (370
bytes, 361 matching). The typed record-buffer candidate above was restored
and freshly recompiled with the stated 368-byte result. No flags changed.

Unmatched active source and report were removed. The private address scratch
retains the complete last native report and result. No exact-match credit.
