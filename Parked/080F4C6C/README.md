# 0x080F4C6C - two-sprite placement phase callback: bytes identical, refused (five local copies of ROM tables through func_081443FC, whose addresses are then stored in local pointer arrays) (400 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `u32 func_080F4C6C(void *task, Descriptor080F4C6C *descriptor, Payload080F4C6C *payload)` is an effect phase callback; its only reference is the function word at `0x080F5100`, in the pool of `func_080F4DFC`. Phase 0 stores the descriptor's index and turns its placement bytes into a position (`x = p[0] * 32 + 16`, `y = p[1] * 16`, `p[2] * 32 + 16`). Phase 0x100 copies five 4-byte ROM tables to its 48-byte frame with `func_081443FC`, the sprite frames for two layers (`data_08149D14`: 1, 1, 0, 0 and `data_08149D18`: 2, 2, -1, -1), the palettes (`data_08149D1C`) and the animation arguments for two layers (`data_08149D20` and `data_08149D14` again), and keeps the layer tables' addresses in two local `s8 *[2]` arrays. When its countdown expires it creates, for each layer whose frame for `index` is not -1, a sprite with `func_080D5E80(data_085000D8, frame, x, y, z, 0x392, 6)`, sets its palette (`func_08011118`) and either stops it (`func_08010884`) or animates it (`func_08011058`). Phase 0x101 waits for both sprites (`func_080D5F24`).

```
080F4CE0  add  r4, sp, #0x10         @ s8 a1[4]
080F4CE2  ldr  r1, =data_08149D18
080F4CE4  adds r0, r4, #0
080F4CE6  movs r2, #4
080F4CE8  bl   0x081443FC
080F4CEC  add  r2, sp, #0xc          @ &a0
080F4CEE  str  r2, [sp, #0x20]       @ a[0] = a0
080F4CF0  add  r0, sp, #0x20
080F4CF2  str  r4, [r0, #4]          @ a[1] = a1
...
080F4D34  lsls r5, r6, #2
080F4D36  adds r0, r5, #0
080F4D38  add  r0, sp, r0
080F4D3A  adds r0, #0x20
080F4D3C  ldrb r1, [r7]              @ payload->index
080F4D3E  ldr  r0, [r0]              @ a[i]
080F4D40  adds r1, r0, r1
080F4D44  ldrsb r0, [r1, r0]         @ a[i][index]
```

## The index

The index row `080F4C6C 080F4DFC 400 200 return` is right about the extent, but its instruction column is the halfword count (bytes/2), as is `config/functions.json`'s (200): the reachable CFG has 178 instructions (the kit's `analyze.refine_function` at 18dcc516 closes it over the indexed extent). Not corrected here: no draft needs it. The selectors that check the count against the CFG refuse on it (`restoring-owner-scalar-switch-v1`, `restoring-owner-switch-entry-word-v1`, `restoring-owner-switch-entry-two-words-data-v1`, `restoring-owner-acyclic-v1` and 2 more: `complete-owner text reachable instruction count differs`).

## Byte identity

`080F4C6C.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080F4C6C, with every callee and data symbol bound to its ROM address (10 `R_ARM_THM_CALL`, 5 `R_ARM_ABS32`). The 400-byte symbol equals the ROM span `[0x080F4C6C, 0x080F4DFC)`: SHA-256 `27a316c2503d4d66f2816d2ceb7a312cbff6f4a0035335fc36f5e4a5a85311bb` for both. `.text` is exactly 400 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each was added with its address as the value (`"data_08149D14": "0x08149D14"`) for the runs below: `data_08149D14`, `data_08149D18`, `data_08149D1C`, `data_08149D20`. Each is the only aligned ROM word with its value, in this function's own pool (`0x080F4D9C`, `0x080F4DA0`, `0x080F4DA4`, `0x080F4DA8`), loaded as the source of a 4-byte `func_081443FC` copy. `data_085000D8`, the sprite resource, is already mapped.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080F4C6C.c` and the data symbols above: the default run and all 213 selector values. None matched. The default run prints the refusal after `compile failed:`, a selector run as `error (ValueError): <text>`.

| Selector | Refusal |
|---|---|
| default, and 31 other selector values | `buffer callee 0x081443FC: unsupported buffer pointer use or escape` |
| `named-data-buffer-rom-table-copy-v1` | `stack aliases cannot be stored or spilled` |
| `named-data-buffer-stack-index-v1`, `named-data-buffer-stack-index-v2` | `variable stack indices exclude pointer-bearing or return-carrying local words` |

The other 179 selector values give 63 other refusals, none of them a match; the most frequent are `addressed runtime ELF requires actual addressed calls and no unresolved symbols` (29), `private float requires unique undefined pinned helper symbols` (15), `addressed signed runtimes exclude data and irregular relocations` (13).

## Cause

All five copies pass a frame address in R0 to `func_081443FC` (count 4 each, a constant ROM source), and four of those addresses are then stored into the frame as pointer words (`a[0..1]` at `sp + 0x20`, `b[0..1]` at `sp + 0x28`) and loaded back to index the tables by `payload->index`. On the default path and under the buffer selectors without a copy summary, the walk stops inside `func_081443FC` at its alignment test. `named-data-buffer-rom-table-copy-v1` summarises the five copies (named constant sources, count 4) and then refuses the stored table addresses (`stack aliases cannot be stored or spilled`); the two stack-index selectors refuse the variable index through those pointer-bearing locals (`variable stack indices exclude pointer-bearing or return-carrying local words`). In the prototype measured for the kit issue below, a `func_081443FC` summary for local buffers takes this function past the helper on the other buffer paths too, and it then stops at the same `stack aliases cannot be stored or spilled` (not re-run here); so the summary alone does not admit it, and the stored pointers need a rule of their own.

## Source notes

- An earlier copy passed the tables as raw ROM addresses (`(const void *)0x08149D14` and so on), with the same bytes and no data relocations; under it the ROM-table-copy and stack-index selectors stopped at the helper (`buffer callee 0x081443FC: copy source is neither the compiler initialiser nor a named ROM table`), and 21 other selector values refused differently (runtime, switch-constant, multiple-switch and one native-bridge selector, which now meet the data words), with the default run unchanged.
- The natural spelling, initialised local arrays, puts the tables in `.rodata`, which the default path refuses as an allocated section (recorded by the earlier attempt; not re-measured here).
- A stack-index proof would also need `payload->index` bounded by 4; nothing here establishes it.
- 0x080F6C48 is the same five-copy shape with named objects.

kit issue: shubshub/fftadecomp-kit#240
