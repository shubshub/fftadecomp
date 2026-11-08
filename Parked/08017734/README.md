# 08017734

Tile-row copy over a region record (layout as in the matched sibling `src/08017618.c`). Doubles
`func_08017B50(region)` for the row count; per row takes `func_08142950(row, rows*2)` as the source row, and
if the callback at +0 is set (called through `_call_via_r3`) patches the first two tiles' palette nibble
before copying the rest with `func_0814186C` (CpuSet); with `flags & 4` the last two tiles get palette 0xD.

Not byte-identical: same 128-instruction count (bl counted once), 40 differ.

1. `region` and the source-row pointer are in r6/r5 instead of the ROM's r5/r6, and the 0xFFF/0xD000
   temporaries follow them.
2. The ROM hoists `(width - 2) << 1` out of the loop and keeps `asrs #1` inside; every in-loop spelling
   folds to `width - 2`, and computing it before the loop orders it after the 0xFFF load, unlike the ROM.

Even with exact bytes the verifier needs a selector for this call mix: with no profile, "signed remainder
excludes mixed aliases, addressed calls with data, and other profiles"; `addressed-signed-runtime-r3-callback-data-v1`
refuses with "requires actual addressed calls and no unresolved symbols".
