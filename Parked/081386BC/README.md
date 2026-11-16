# 0x081386BC - stat panel draw: bytes identical, refused (BIOS fill + stack buffer to func_080142DC) (896 bytes)

Attempt 2026-11-16, kit fcdf2d45. cpp + agbcc -O2 equals ROM 0x081386BC..0x08138A3C outside 48 relocations, each of
which resolves to the right address. plausible.py passes. Index correct; no new data symbols.
Refusals: default `buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification`;
addressed-native-bios-fill-buffer-data-v1 (siblings 081384B0, 08138A3C, 08138B4C) `buffer callee 0x080142DC: stack
aliases cannot cross calls in caller-clobbered registers`; bounded-buffer-bios-fill-source-v1 `buffer callee
0x080142DC: buffer callee 0x08002FB8: signed remainder requires numeric proof or fresh addressed-call provenance`
(same as 080458A4); named-data-buffer-v1 as default; bounded-buffer-bios-mixed-fast-fill-runtime-summaries-v1
`CpuFastSet fill requires only its actual direct wrapper calls`.
Choices the bytes do not fully pin: `text` assigned before each of five calls (ROM loads the string pointer before the
text context at 0x081386F2, 0x08138766, 0x081387FA, 0x08138816, 0x08138A04; inline puts it after) - possibly a spare
temporary; one `s32 value` for five numbers (signed ble at 0x0813871C, 0x0813879A, 0x08138842; r5 throughout);
if/else form of one_digit (field load first at 0x08138780-8E); (offset + 11 + one_digit) association
(0x081387E0-E4); func_080142DC(void *, u16, u32) from src/08025B54.c (callee narrows r1 at 0x080142E6).
