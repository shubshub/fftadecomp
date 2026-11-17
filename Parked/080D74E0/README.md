# 0x080D74E0 - background control word from two ROM tables: bytes identical, refused (two local copies of ROM tables through func_081443FC, indexed by arguments) (172 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `void func_080D74E0(u8 layer, u8 first, u8 second, u16 x, u16 y, u32 tiles, u32 map)` writes the control word and the two offsets of background `layer`; 8 functions call it (14 `bl` sites, among them `0x0810EF0C`, `0x08112594` and `0x0811F95C`). It copies two 8-byte `u16[4]` ROM tables to its 16-byte frame with `func_081443FC`: `g_object_08149AC4` (`0x0000`, `0x4000`, `0x8000`, `0xC000`) to `sp` and `g_object_08149ACC` (0 to 3) to `sp + 8`. It then calls `func_080034B8(first_values[first] | func_08003A74(map) | func_08003A80(tiles) | second_values[second], layer)`, `func_08003508((s16)x, layer)` and `func_08003558((s16)y, layer)`. It is the two-table sibling of `0x0801E458`.

```
080D7512  ldr  r1, =g_object_08149AC4
080D7514  mov  r0, sp                @ u16 first_values[4]
080D7516  movs r2, #8
080D7518  bl   0x081443FC
080D751C  add  r2, sp, #8
080D751E  mov  sb, r2                @ u16 second_values[4], kept in R9
...
080D7546  lsls r6, r6, #1
080D7548  add  sb, r6
080D754A  mov  r2, sb                @ &second_values[second]
080D754C  ldrh r1, [r2]
...
080D7556  bl   0x080034B8            @ R2 still holds the stack address
```

## The index

The index row `080D74E0 080D758C 172 86 return` is right about the extent, but its instruction column is the halfword count (bytes/2), as is `config/functions.json`'s (86): the reachable CFG has 75 instructions (the kit's `analyze.refine_function` at 18dcc516 closes it over the indexed extent). Not corrected here: no draft needs it. The selectors that check the count against the CFG refuse on it (`restoring-owner-scalar-switch-v1`, `restoring-owner-switch-entry-word-v1`, `restoring-owner-switch-entry-two-words-data-v1`, `restoring-owner-acyclic-v1` and 2 more: `complete-owner text reachable instruction count differs`).

## Byte identity

`080D74E0.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080D74E0, with every callee and data symbol bound to its ROM address (7 `R_ARM_THM_CALL`, 2 `R_ARM_ABS32`). The 172-byte symbol equals the ROM span `[0x080D74E0, 0x080D758C)`: SHA-256 `5bb0a46c45f6de42e57f5b60d1f59d0ca641095849fa86060575a037fb8e7cc3` for both. `.text` is exactly 172 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each was added with its address as the value (`"g_object_08149AC4": "0x08149AC4"`) for the runs below: `g_object_08149AC4`, `g_object_08149ACC`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080D74E0.c` and the data symbols above: the default run and all 213 selector values. None matched. The default run prints the refusal after `compile failed:`, a selector run as `error (ValueError): <text>`.

| Selector | Refusal |
|---|---|
| default, and 31 other selector values | `buffer callee 0x081443FC: unsupported buffer pointer use or escape` |
| `named-data-buffer-rom-table-copy-v1` | `unsupported stack-alias use or escape` |
| `named-data-buffer-stack-index-v1`, `named-data-buffer-stack-index-v2` | `stack index: ranged stack address escapes through a call argument register` |
| `local-rom-halfword-table-v1`, and 5 other selector values | `complete-owner text reachable instruction count differs` |

The other 173 selector values give 62 other refusals, none of them a match; the most frequent are `addressed runtime ELF requires actual addressed calls and no unresolved symbols` (29), `private float requires unique undefined pinned helper symbols` (15), `addressed signed runtimes exclude data and irregular relocations` (13).

## Cause

Both copies pass a frame address in R0 to `func_081443FC`. On the default path, and under every buffer selector without a copy summary, the walk enters the helper and stops at its alignment test, which uses the pointer as a number. `named-data-buffer-rom-table-copy-v1` summarises both copies (constant ROM sources, count 8) and then refuses the owner's register indexes `first_values[first]` and `second_values[second]` (`unsupported stack-alias use or escape`). The stack-index selectors admit those indexes, but the indexed address `&second_values[second]` is still in R2 at the next call, `func_080034B8` at `0x080D7556`, and they refuse that as an escape. In the prototype measured for the kit issue below, a `func_081443FC` summary for local buffers takes this function past the helper, and it then stops at the owner's register index into the copied table (not re-run here).

## Source notes

- Both tables are named ROM objects at their literals' addresses (`0x080D7584`, `0x080D7588`); the copies are written as the calls the ROM makes.
- `func_08003A74` is declared `u16`, as the matched `src/08003A74.c` defines it. `func_08003A80` is declared `u32`, while the matched `src/08003A80.c` returns `u16`; with `u16` the bytes are the same (same SHA-256).
- `local-rom-halfword-table-v1` refuses on the index's instruction count (table above). With the row corrected to 75 in both index files it refuses `complete aligned forty-byte local table owner required` instead: it admits one 40-byte table, and this function copies two 8-byte ones.

kit issue: shubshub/fftadecomp-kit#240
