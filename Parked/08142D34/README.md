# 0x08142D34 - libgcc dp-bit __unpack_d: byte-identical under old_agbcc, not under agbcc (220 bytes)

Retry 2026-11-16, kit fcdf2d45. The source is the fp-bit.c `unpack_d` text (renamed types). Under old_agbcc (-mthumb-interwork -O2)
it is 220/220 bytes; under agbcc 216/220: at 0x08142D4C..0x08142D54 the halfword and byte loads go to r0 where the
ROM loads them into r3 and r2. Cause: `s_register_operand` in agbcc's thumb.c rejects a `(subreg (mem))` operand, so
combine cannot merge the loads into the shifts (confirmed in gdb in agbcc's combine.c); old_agbcc accepts it, and reload
then picks r3/r2 as the ROM has. With agbcc the surviving r2 also triggers the verifier refusal `inconsistent stack
aliases at control-flow join`. Whole fp-bit-base.c compiled as dp-bit.c with agbcc: every other dp-bit function
matches (apart from unlinked bl/pool words); only __pack_d (0x08142BE8, same cause) and __unpack_d differ.
Ruled out: bit-field types/packing/union order/read order/declaration order/const/pointer locals/shift-and-mask
spellings; -g, -O, -Os, -O3, no -mthumb-interwork, ~25 single -f switches (diagnostic only).
Index 08142D34 08142E10 220 97 correct. Needs a kit toolchain lane that builds libgcc's dp-bit unit with old_agbcc.
