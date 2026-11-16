# 0x0800E268 - near miss (492 bytes): 484 compiled; byte-identical only with volatile on ROM data

Retry of Parked/0800E268 on 2026-11-16, kit fcdf2d45, default flags. The source here has plain `s16 count`: match.py says 'compiled symbol is
shorter than the indexed span: 484 < 492'; plausible.py exits 0. With `volatile s16 count` in the shape header the bytes are identical (492/492,
239/239) and match.py refuses: source IMPLAUSIBLE, ERROR: volatile, 'HAND-ASM REQUIRED BUT NOT ALLOWED - byte identical, yet 0x0800E268 is not
on the hand-asm allow list'.

Not shipped: volatile is admitted only on evidence-backed declarations in include/ on the plausible.py allow list; this is non-MMIO ROM data
reached through a computed pointer. The volatile variant also depends on draw_shape, a static inline used once with no shared text in a matched
source and no identified out-of-line twin, which the helper rule does not admit either.

Remaining difference: the two reads of shape->count in the scanline loop. ROM: loop entry `ldrh r0,[r6]; lsls r0,#16; movs r4,#0; cmp r0,#0; ble; b`,
loop bottom `ldrh r0,[r6]; lsls r0,#16; asrs r0,#16; cmp r4,r0; bge`. agbcc from plain C: `movs r5,#0; b <bottom>` and
`movs r1,#0; ldrsh r0,[r6,r1]; cmp r5,r0; bge` (combine folds load+lsl+asr into sign_extend(mem); the duplicated entry test is then cross-jumped
away: 8 bytes short; knock-on register swaps r4/r5, r2/r3 and ldr r3/r1,[sp]).
Per combine.c/optabs.c/thumb.md the load stays unmerged only if the memory is volatile, the loaded register has a second use, or a block boundary
sits between load and shift. ROM-wide the ldrh; lsls #16; asrs #16 sequence occurs in 5 of 6782 functions; the other four (080A0DEC, 080EBB58,
0813DC3C, 081465E8) load from an sp-based stack struct; this is the only register-pointer case.

Recovered shape (each needed for 492/492 in the volatile variant): static inline draw_shape(const Shape *shape, s16 x, s16 y, Scanline *lines)
holding the loop with `if (scanY >= 0) { if (scanY >= 160) break; ... }`; all-signed header and lines (s16 count, originY; ShapeLine {s16 left,
right;}); packed Frame and PositionedFrame; u16 frameCount (4-byte spill); object->frame++ as its own statement before the compare; per-arm
statements in the tail; frame and positionedFrame at function scope; declaration order shape, x, y, frameCount, frame, positionedFrame.
Ruled out (all still ldrsh): u16 count with (s16) cast; s32 count:16; local s16 n; inline accessors/predicate; const s16 * deref; HImode compares;
field-level packed. Other failures: struct-level packed (byte loads); explicit if (count > 0) around do/while (cross-jumped); no inline helper
(the older parked form, 389/492 bytes); u16 fields; block-scoped frame pointers; u32 frameCount.
