# 0x08132064 - eight-byte random shuffle: bytes identical, refused (signed % with a _call_via_r3 copy callback) (132 bytes)

Attempt 2026-11-13, kit fcdf2d45. Compiled with agbcc -mthumb-interwork -O2 and linked by hand at 0x08132064 with
every callee and data symbol bound to its ROM address, __modsi3 at 0x08142950 and _call_via_r3 at 0x08142250, the
source gives all 132 bytes of [0x08132064, 0x081320E8). Index row correct.

Unless bit 4 of obj->flags is set, the function copies eight bytes from data_083A8C0C into a local table through the
copy callback data_0836D4BC, then moves them in random order ((s16)func_08002804() % count) into
obj->buffer[0x0D..0x14], closing each gap in the table with the same callback.

Needs one data symbol (not in config/data_symbols.json): data_083A8C0C, the eight source bytes.

Refusals, with the symbol added:
- default: `signed remainder excludes mixed aliases, addressed calls with data, and other profiles`
- `--addressed-signed-runtime-profile addressed-signed-runtime-r3-callback-data-v1`: `function address requires a
  canonical addressed function`, on the compiler's __modsi3 name: the addressed selectors expect an explicit
  func_08142950 call, and the compiler-runtime selectors have no callback variant.

Kit issue: #134 (no selector combines an arithmetic runtime with compiler-emitted _call_via callbacks). A compiler-name
(__modsi3) variant of the r3 callback selector would cover it.
