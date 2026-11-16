# 0x080A5580 - entry walk with three switches: bytes identical, refused (multiple switches inside a loop) (1042 bytes)

Attempt 2026-11-16, kit fcdf2d45. agbcc -O2 linked at 0x080A5580 equals the ROM's 1042 bytes (three jump tables, 31 calls in
order; plus the usual 2-byte alignment nop). plausible.py exit 0. No data symbols. Layout and prototypes from siblings
080A52D4, 080A54E0, 080A5A7C, 080A1A14 and callees 0812EE98, 0809A570, 0809D854, 080A8390.
Refusals: default `switch words must describe an adjacent table and forward local cases`;
`--owner-runtime-profile ordinary-multiple-switch-source-v1` `multiple-switch dual-index instruction count differs
from complete CFG`, and with corrected index counts (in a local copy of the index) `multiple-switch prerequisite excludes local CFG cycles`
(the real gap: the for loop over the entries contains the switches); restoring-owner-switch-* `scalar switch requires
one exact zero-interposed-word switch and ordinary calls`; restoring-owner-scalar-switch-v1 / -runtime-v1 `owner
requires sole complete Thumb ELF function`.
Index fixes the selector needs: 080A5580 instrs 521 -> 390 (functions.txt + functions.json); callee rows must agree
across the two files: 0809836C (800 vs 627; 627 unchecked) and 0809A570 (29 vs 27; 27 is right: 58 bytes, 2 BLs).
Choices the bytes do not fully pin: `s32 direction` locals (func_0809D6BC called at 0x080A563E/0x080A570A before the object loads);
`u16 item = state->item` (ldrh r4 at 0x080A588C reused at 0x080A5920); two case groups both doing `moved = 1` kept
separate (blocks 0x080A579C, 0x080A57A2; merged: 968 bytes; commented); declaration order played, hit, moved
(0x080A558E); s8 left/right (0x080A56B0, 0x080A56C8); func_080A1D84 with s8 arguments as 080A8390.
