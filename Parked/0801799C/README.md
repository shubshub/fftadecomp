# 0801799C

Tile-row copy over a region record (layout as in `src/08017618.c` (and the parked `Parked/08017734/08017734.c`): +0x08 destination,
+0x0C tiles). Computes the tile row with `func_08142950` (signed remainder), substitutes the region's `palette` for a
0xFF palette, trims columns by flag bits 2 and 4, ORs `palette << 12` into two rows of entries and copies
with `func_0814186C` (CpuSet).

Not byte-identical. `0801799C.c` compiles to the target's 115 instructions with the same control flow,
frame and literal pool, but three register-allocation/scheduling differences remain:

1. `sb`/`sl` are swapped (the ROM keeps `i+1` in sb and `start*2` in sl);
2. `mov r5, sb` is scheduled one slot before `movs r0,#4; ands r0,r2`;
3. before the copy, the ROM loads `0x1FFFFF` then `[sp,#8]`; this build loads them in the other order.

Ruled out: declaration orders of `start/end/i/j`; `start`/`end`/`i` as u8/s8/u16/s16/u32/s32; `?:` vs `if`;
computing `end` before `start`; the sibling's byte-count forms; an explicit count local.
