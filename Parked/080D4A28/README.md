# 0x080D4A28 - background layer setup from five ROM tables: bytes identical, refused (a local copy of a ROM table through func_081443FC, then indexed by a variable) (316 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `void func_080D4A28(u8 group, u8 layer, u16 index, u16 x, u16 y, u8 priority)` sets up background `layer` for one of two groups; it is called from `0x080D49FC`, `0x0811F95C` and `0x081204A8`. It first copies five small ROM tables to its 76-byte frame: the screen bases (`data_08149A88`, `0x06005800`/`0x06005000`) twice, the character bases (`data_08149A90`), the masks (`data_08149A98`) and the 16-byte priorities (`data_08149AA4`, 0 to 3), each as a structure assignment, and the two-halfword colour flags (`data_08149AA0`, `0x0000`/`0x0080`) with a call to the copy helper `func_081443FC`. It then calls `func_0800AFAC(screens[group], index, 0, group, masks[index])`, `func_0800BC90`, `func_0800BC08(group, x, y)`, `func_0800BCE0` and `func_0800BD24`, writes the control word `func_08003A74(maps[group]) | func_08003A80(characters[index]) | flags[index] | priorities[priority]` with `func_080034B8`, and clears both offsets of the layer (`func_08003508`, `func_08003558`).

```
080D4A82  ldr  r1, =data_08149AA0
080D4A84  add  r0, sp, #4            @ u16 flags[2]
080D4A86  movs r2, #4
080D4A88  bl   0x081443FC
080D4A8C  mov  r3, sp
080D4A8E  adds r3, #8                @ &priorities
080D4A90  str  r3, [sp, #0x40]       @ kept in the frame for the last read
...
080D4B0E  mov  r0, sp
080D4B10  add  r0, r8                @ index * 2
080D4B12  adds r0, #4
080D4B14  ldrh r0, [r0]              @ flags[index]
```

## The index

The index row `080D4A28 080D4B64 316 158 return` is right about the extent, but its instruction column is the halfword count (bytes/2), as is `config/functions.json`'s (158): the reachable CFG has 137 instructions (the kit's `analyze.refine_function` at 18dcc516 closes it over the indexed extent). Not corrected here: no draft needs it. The selectors that check the count against the CFG refuse on it (`restoring-owner-scalar-switch-v1`, `restoring-owner-switch-entry-word-v1`, `restoring-owner-switch-entry-two-words-data-v1`, `restoring-owner-acyclic-v1` and 2 more: `complete-owner text reachable instruction count differs`).

## Byte identity

`080D4A28.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080D4A28, with every callee and data symbol bound to its ROM address (11 `R_ARM_THM_CALL`, 5 `R_ARM_ABS32`). The 316-byte symbol equals the ROM span `[0x080D4A28, 0x080D4B64)`: SHA-256 `3b9e763b1ba8ff72f937e9531c12f6aad4dee436fbd87b6b04e898aa5980c4b1` for both. `.text` is exactly 316 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each was added with its address as the value (`"data_08149A88": "0x08149A88"`) for the runs below: `data_08149A88`, `data_08149A90`, `data_08149A98`, `data_08149AA0`, `data_08149AA4`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080D4A28.c` and the data symbols above: the default run and all 213 selector values. None matched. The default run prints the refusal after `compile failed:`, a selector run as `error (ValueError): <text>`.

| Selector | Refusal |
|---|---|
| default, and 31 other selector values | `buffer callee 0x081443FC: unsupported buffer pointer use or escape` |
| `named-data-buffer-rom-table-copy-v1` | `unsupported stack-alias use or escape` |
| `named-data-buffer-stack-index-v1`, `named-data-buffer-stack-index-v2` | `variable stack indices exclude pointer-bearing or return-carrying local words` |

The other 179 selector values give 63 other refusals, none of them a match; the most frequent are `addressed runtime ELF requires actual addressed calls and no unresolved symbols` (29), `private float requires unique undefined pinned helper symbols` (15), `addressed signed runtimes exclude data and irregular relocations` (13).

## Cause

The copy into `flags` is the first local address that reaches a call. On the default path, and under every buffer selector without a copy summary, the walk enters `func_081443FC` and stops at its alignment test, which uses the destination pointer as a number. `named-data-buffer-rom-table-copy-v1` summarises that copy (a constant ROM source, count 4, a destination alias only) and then refuses the owner's own register indexes into the copied tables (`unsupported stack-alias use or escape`): `screens[group]`, `masks[index]`, `maps[group]`, `characters[index]` and `flags[index]` are frame addresses plus a scaled argument. The two stack-index selectors, which admit such indexes, refuse on a pointer-bearing local word; the only one in this frame is `sp + 0x40`, which holds `&priorities`. In the prototype measured for the kit issue below, a `func_081443FC` summary for local buffers takes this function past the helper, and it then stops at the same register index into the copied table (not re-run here).

## Source notes

- Each table is a named ROM object at its literal's address (the five pool words at `0x080D4B50`-`0x080D4B60`). The structure assignments are inline loads and stores (`ldm`/`stm` for the 16-byte one); only the 4-byte halfword table goes through `func_081443FC`, which the source writes as that call.
- `screens` and `maps` are two copies of `data_08149A88`, stored from the same loads at `0x080D4A66`-`0x080D4A6C`.
- `func_08003A74` and `func_08003A80` are declared `u32`, while the matched `src/08003A74.c` and `src/08003A80.c` return `u16`; with `u16` the bytes are the same (same SHA-256).
- `x` and `y` are `u16` parameters passed as `s16`, as `include/ffta.h` declares `func_0800BC08(u8, s16, s16)`; `y` and `priority` are the fifth and sixth arguments (`[sp, #0x6c]`, `[sp, #0x70]`).

kit issue: (to be filed - match.py: a local buffer passed to the pinned copy helper func_081443FC is refused in every buffer walk outside the ROM-table-copy selectors)
