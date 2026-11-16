# 0x0805F6EC - event 0x103 request: bytes identical, refused by the callback-buffer gap (28 bytes)

Attempt 2026-11-16, kit fcdf2d45. Source: a local 0x1C-byte request with event 0x103, passed with owner->task (+0xC) to
func_08005C04 (prototype from matched src/08005C04.c); the request type follows the neighbouring 0x0805F69C (event
0x102, same shape). Linked by hand with func_08005C04 at its ROM address, all 28 bytes equal ROM
[0x0805F6EC, 0x0805F708). plausible.py exit 0.
Refused (default): `buffer callee 0x08005C04: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG
verification` - func_08005C04 calls the task callback through _call_via_r3 with a pointer into the caller's frame.
Five conditional-scheduler / local-output / stack-index selectors refuse on shape. Same gap: 0x0805F69C, 0x080651C8;
nearest kit issue #190 (a local buffer passed through _call_via_r2). Index row correct; no data symbols.
