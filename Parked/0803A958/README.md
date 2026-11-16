# 0x0803A958 - recursive pattern step: bytes identical, refused because self calls are excluded from runtime/buffer profiles (944 bytes)

Attempt 2026-11-16, kit fcdf2d45. With relocations filled by hand (two data symbols, eight callees, __modsi3, the self call) the
source equals ROM [0x0803A958, 0x0803AD08). plausible.py exit 0. Index correct; no new data symbols.
Refusals: default `self calls are admitted only on the plain direct-call path` (kit README "Self calls": intentional;
this function has 8 self bls, __modsi3 and two CpuSet fills from stack locals); compiler-signed-runtime-data-v1
`addressed calls require unique undefined zero-valued global functions` (the self-call target is defined);
addressed-native-bios-fill-buffer-data-v1 `function address requires a canonical addressed function`;
entry-recursive-ordinary-call-v1 `entry saved-only owner excludes local frames and stack-address materialization`;
canonical-integer-scalar-data-source-v1 `owner requires unique undefined zero-valued global symbols`.
Source: the first part is matched src/0803AD08.c's text inline (indices[4], values[4] stack arrays), then a 1..4
decision on the collected count, a pattern byte update at +8..+B and recursion with depth - 1.
Choices the bytes do not fully pin: one `u8 value` as link byte and result (r6 in both; separate result: 940 bytes); the
`if (count != 0) { switch ... }` guard (0x0803AAC4); nested redundant 0xFF tests with ROM-citing comments
(0x0803AB0E/1A, 0x0803ABCE/D2, 0x0803AC52/56; the && form merges them, 940 bytes); plain `% 21` (ROM forms the store
address between the random call and the modulo, 0x0803AB72-76; the explicit call is 928 bytes); s32 count/depth
(bgt/ble), u32 entry.
Needs a kit selector that admits a self call together with a runtime helper and local CpuSet buffers.
