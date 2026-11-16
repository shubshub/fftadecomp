# 0x080E2398 - effect setup switch: bytes identical, refused by the switch + stack-descriptor verifier gap (952 bytes)

Attempt 2026-11-16, kit fcdf2d45. With relocations applied to the real addresses the source compiles to the ROM's
952 bytes.
plausible.py passes. Index row correct.
Needs 14 data symbols (none exist yet): 08395720, 08395738, 08395750, 0839575C (record arrays for func_080E03F8);
08395840 (pointer table) and 0839589C (u8 table) for func_080D7A70; 08395C1C (callback table: func_080E0E98 ...
func_080E1DBC, func_080E1EE0, func_080E21BC); 08395C3C (u16 size table); 088EA6D0, 088EA6D8, 088E9C60, 088EB260,
088EA66C, 088EAFB0 (rows for func_080D45D0).
Refusals with them added: default and u16-scalars-v1/-frame-v1 `stack aliases cannot cross calls in
caller-clobbered registers` (a 0x1C stack descriptor passed in r2 to func_08005B6C); owner selectors (scheduler,
named-data-buffer, bounded-buffer switch, watched-switch) `structural inventory is not closed` - the inner 23-entry
jump table has data_08395720 between the dispatch and the table pointer, and refine_function closes it only with
one_object_word_switch=True, which owner admission never passes; forced on in a modified copy of the kit, the next refusal is
`named-data buffer caller excludes local BL and word switches`.
Choices the bytes do not fully pin: `count = 2;` restated in cases 16 and 19 (ROM movs at 0x080E258A, 0x080E25CE; without it 944
bytes; each case sets its record array and count together); `u8 first = 0;` is case 0x16's value (movs r3,#0 at
0x080E2662); func_080DD47C(work->object) reuses r0 after the store; two func_080E03F8 calls as in sibling 080E41E4;
descriptor and request types as in 0811896C; locals declared request, reload, entries, count, code.
