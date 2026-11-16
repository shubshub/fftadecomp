# 0x08072130 - grid sort by mode: bytes identical, refused by the switch + stack-array verifier gap (1160 bytes)

Attempt 2026-11-16, kit fcdf2d45. The source compiles (agbcc -O2, linked at 0x08072130, data symbols g_state_02000000 and
data_03002818) to the ROM's 1160 bytes exactly. plausible.py exit 0. Index row correct; no new data symbols.
Refusals: default `switch requires one exact adjacent unsigned guard and five-op dispatch` (three pool words -
g_state_02000000, data_03002818, 0x9EF - sit between the dispatch and the table pointer; the analyzer reports
`unresolved jump at 0x080721A8`); `--switch-data-profile u16-scalars-v2` / `u16-scalars-frame-v1` accept the switch,
then `unsupported stack-alias use or escape` (a local 24-entry order array indexed by a variable, `mov r6,sp;
adds r2,r6,r0`, passed to func_08087D98); bounded-buffer / named-data-buffer owner selectors: `structural inventory is
not closed`. Close to kit #135, but the array is an ordinary local, not a ROM-table copy.
Choices the bytes do not fully pin: one block-scoped u8 counter per case (the ROM gives each case its own register - r2 in cases
1-5, r1 in case 6, r5 in default; one shared counter needs an extra saved register and changes every case);
GridState `__attribute__((packed, aligned(4)))` as matched caller src/08072B74.c (slots at 0x9EE; status written at
0x9EF), plus count at 0x95C from every case's pool words.
