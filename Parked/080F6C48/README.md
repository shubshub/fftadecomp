# 0x080F6C48 - two-sprite actor effect phase callback: bytes identical, refused (five local copies of ROM tables through func_081443FC, whose addresses are then stored in local pointer arrays) (556 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `u32 func_080F6C48(void *task, Descriptor080F6C48 *descriptor, Payload080F6C48 *payload)` is an effect phase callback; its only reference is the function word at `0x080F711C`, in the pool of 0x080F6E74. Phase 0 stores the descriptor's side, flags, variant and actor, reads the actor's position into the payload (`func_080DD748`), raises it by 16 when `func_080DD73C` says so, and calls `func_080DB838`. Phase 0x100 copies five 4-byte ROM tables to the frame with `func_081443FC`: the sprite frames for two layers (`data_08149D2C`, `data_08149D30`), the palettes (`data_08149D34`) and the animation arguments for two layers (`data_08149D38` and `data_08149D2C` again), and keeps the layer tables' addresses in two local `s8 *[2]` arrays. For each layer whose frame for `side` is not -1 it creates a sprite with `func_080D5E80(&data_085000D8, frame, x, y, z, 0x392, 6)`, sets its palette and either stops or animates it. It then starts one of two resources (`data_08949DD8` or `data_0894848C`, by variant), the actor's animation `func_080DCFE4(actor, &data_0839BA28[variant], 12, 26, mode, task, 26)` and the record `data_0839BA60`. Phase 0x101 waits for the sprites, the resource and the animation.

```
080F6CC6  add  r4, sp, #0x10         @ s8 first_b[4]
080F6CC8  ldr  r1, =data_08149D30
080F6CCA  adds r0, r4, #0
080F6CCC  movs r2, #4
080F6CCE  bl   0x081443FC
080F6CD2  add  r0, sp, #0xc          @ &first_a
080F6CD4  str  r0, [sp, #0x20]       @ first[0] = first_a
080F6CD6  add  r1, sp, #0x20
080F6CD8  str  r4, [r1, #4]          @ first[1] = first_b
...
080F6CFE  str  r5, [sp, #0x28]       @ second[0] = second_a
080F6D00  add  r0, sp, #0x28
080F6D02  str  r4, [r0, #4]          @ second[1] = second_b
```

## The index

The index row `080F6C48 080F6E74 556 278 return` is right about the extent, but its instruction column is the halfword count (bytes/2), as is `config/functions.json`'s (278): the reachable CFG has 239 instructions (the kit's `analyze.refine_function` at 18dcc516 closes it over the indexed extent). Not corrected here: no draft needs it. The selectors that check the count against the CFG refuse on it (`restoring-owner-scalar-switch-v1`, `restoring-owner-switch-entry-word-v1`, `restoring-owner-switch-entry-two-words-data-v1`, `restoring-owner-acyclic-v1` and 2 more: `complete-owner text reachable instruction count differs`).

## Byte identity

`080F6C48.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080F6C48, with every callee and data symbol bound to its ROM address (18 `R_ARM_THM_CALL`, 9 `R_ARM_ABS32`). The 556-byte symbol equals the ROM span `[0x080F6C48, 0x080F6E74)`: SHA-256 `bf6c4df5bd239885c608796e4ccfc875055c4bac6afdf5774acf21cd9ba44e99` for both. `.text` is exactly 556 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each was added with its address as the value (`"data_08149D2C": "0x08149D2C"`) for the runs below: `data_08149D2C`, `data_08149D30`, `data_08149D34`, `data_08149D38`, `data_0839BA28`, `data_0839BA60`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080F6C48.c` and the data symbols above: the default run and all 213 selector values. None matched. The default run prints the refusal after `compile failed:`, a selector run as `error (ValueError): <text>`.

| Selector | Refusal |
|---|---|
| default, and 29 other selector values | `buffer callee 0x081443FC: unsupported buffer pointer use or escape` |
| `named-data-buffer-rom-table-copy-v1` | `stack aliases cannot be stored or spilled` |
| `named-data-buffer-stack-index-v1`, `named-data-buffer-stack-index-v2` | `variable stack indices exclude pointer-bearing or return-carrying local words` |

The other 181 selector values give 64 other refusals, none of them a match; the most frequent are `addressed runtime ELF requires actual addressed calls and no unresolved symbols` (29), `private float requires unique undefined pinned helper symbols` (15), `addressed signed runtimes exclude data and irregular relocations` (13).

## Cause

All five copies pass a frame address in R0 to `func_081443FC` (count 4 each, a constant ROM source), and four of those addresses are then stored into the frame as pointer words (`first[0..1]` at `sp + 0x20`, `second[0..1]` at `sp + 0x28`) and loaded back to index the tables by `payload->side`. On the default path and under the buffer selectors without a copy summary, the walk stops inside `func_081443FC` at its alignment test. `named-data-buffer-rom-table-copy-v1` summarises the copies and refuses the stored addresses (`stack aliases cannot be stored or spilled`); the stack-index selectors refuse the variable index over frame words that hold pointers. In the prototype measured for the kit issue below, a `func_081443FC` summary for local buffers takes this function past the helper, and it then stops at the same stored addresses (not re-run here).

## Source notes

- The tables are named ROM objects at their literals' addresses, and the copies are written as the calls the ROM makes; the last copy reuses the first table's address, kept in R9 (`0x080F6CBA`, `0x080F6CF6`).
- A stack-index proof would also need `payload->side` (an `s8` copied from the descriptor's `u16`) to be 0 to 3; nothing here establishes it.
- 0x080F4C6C is the same five-copy shape.

kit issue: (to be filed - match.py: a local buffer passed to the pinned copy helper func_081443FC is refused in every buffer walk outside the ROM-table-copy selectors)
