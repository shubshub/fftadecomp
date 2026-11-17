# 0x080FB0B4 - effect 0x81 phase callback with a direction-indexed sprite: bytes identical, refused (local copies of two ROM tables through func_081443FC, one address kept in the frame, indexed by a direction) (680 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `u32 func_080FB0B4(void *task, Descriptor080FB0B4 *descriptor, Payload080FB0B4 *payload)` is the phase callback of effect 0x81: its function word is entry 0x80 of the effect table `data_083947D8` (`0x08394BD8`) that 0x080D3508 reads. Phase 0 starts the actor's first animation (`func_080E03F8(actor, data_0839CBB4, ...)`); phase 0x100 waits for it and starts the scene child `func_080DDF68`; phase 0x101 waits for it, calls `func_080DBFFC` and falls into phase 0x102 with a countdown of 10. Phase 0x102 copies the two 4-byte tables `data_08149D78` (animations 1, 0, 0, 1) and `data_08149D7C` (1, 0, 1, 0) to the frame with `func_081443FC`, waits out the countdown, reads the actor's tile (`func_080D8B5C`, two local `s16`) and the target's (`func_080DBD78`, three local `s16`), takes the direction between them from `func_0809D6BC`, and creates a sprite with frame `animations[direction]` and the `func_08011118` argument `directions[direction]` (`func_080D5CC0(data_08502560, ...)`). It then starts a child, an effect and a record; phases 0x103 and 0x104 start the actor's animation `data_0839CBCC` and wait for everything.

```
080FB1B0  ldr  r1, =data_08149D78
080FB1B2  add  r0, sp, #0x14         @ u8 animations[4]
080FB1B4  movs r2, #4
080FB1B6  bl   0x081443FC
080FB1BA  mov  r2, sp
080FB1BC  adds r2, #0x18             @ u8 directions[4]
080FB1BE  str  r2, [sp, #0x28]       @ its address, kept in the frame
080FB1C0  ldr  r1, =data_08149D7C
080FB1C2  adds r0, r2, #0
080FB1C4  movs r2, #4
080FB1C6  bl   0x081443FC
...
080FB1DC  bl   0x080D8B4C
080FB1E0  lsls r0, r0, #0x18
080FB1E2  lsrs r0, r0, #0x18
080FB1E4  str  r0, [sp, #0x2c]       @ its result, reused later as an argument
```

## The index

The index row `080FB0B4 080FB35C 680 340 return` is right about the extent, but its instruction column is the halfword count (bytes/2), as is `config/functions.json`'s (340): the reachable CFG has 287 instructions (the kit's `analyze.refine_function` at 18dcc516 closes it over the indexed extent). Not corrected here: no draft needs it. The selectors that check the count against the CFG refuse on it (`restoring-owner-scalar-switch-v1`, `restoring-owner-switch-entry-word-v1`, `restoring-owner-switch-entry-two-words-data-v1`, `restoring-owner-acyclic-v1` and 2 more: `complete-owner text reachable instruction count differs`).

## Byte identity

`080FB0B4.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080FB0B4, with every callee and data symbol bound to its ROM address (26 `R_ARM_THM_CALL`, 8 `R_ARM_ABS32`). The 680-byte symbol equals the ROM span `[0x080FB0B4, 0x080FB35C)`: SHA-256 `a140807b176ba1be63cafae59c78562c59b2bb5c29ac1be8e47e2d1a35ed5ccb` for both. `.text` is exactly 680 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each was added with its address as the value (`"data_08149D78": "0x08149D78"`) for the runs below: `data_08149D78`, `data_08149D7C`, `data_0839CBB4`, `data_0839CBCC`, `data_0839CBE0`, `data_0839CBE4`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080FB0B4.c` and the data symbols above: the default run and all 213 selector values. None matched. The default run prints the refusal after `compile failed:`, a selector run as `error (ValueError): <text>`.

| Selector | Refusal |
|---|---|
| default, and 20 other selector values | `buffer callee 0x081443FC: unsupported buffer pointer use or escape` |
| `named-data-buffer-rom-table-copy-v1` | `buffer callee 0x081443FC: copy helper receives only a destination alias and no stack-passed pointers` |
| `named-data-buffer-stack-index-v1`, `named-data-buffer-stack-index-v2` | `variable stack indices exclude pointer-bearing or return-carrying local words` |

The other 190 selector values give 67 other refusals, none of them a match; the most frequent are `addressed runtime ELF requires actual addressed calls and no unresolved symbols` (29), `private float requires unique undefined pinned helper symbols` (15), `addressed signed runtimes exclude data and irregular relocations` (13).

## Cause

Local addresses reach calls at the two copies (`func_081443FC`, count 4 each, a constant ROM source) and at the two tile readers (`func_080D8B5C` at `0x080FB230`, `func_080DBD78` at `0x080FB242`). On the default path and under the buffer selectors without a copy summary, the walk stops inside `func_081443FC` at its alignment test. `named-data-buffer-rom-table-copy-v1` refuses the second copy because a pointer-bearing local word is live there: `&directions`, stored at `sp + 0x28` before the call (`0x080FB1BE`). The stack-index selectors refuse the variable index for the same frame words: `sp + 0x28` holds a pointer and `sp + 0x2c` holds the result of `func_080D8B4C`. In the prototype measured for the kit issue below, a `func_081443FC` summary for local buffers takes this function past the helper, and it then stops at the library row `0x08144D84` (a `bx r3` call; not re-run here).

## Source notes

- Both tables are named ROM objects at their literals' addresses (`0x080FB204`, `0x080FB208`), and the copies are written as the calls the ROM makes, before the countdown test, as the ROM orders them.
- **The index is not bounded.** `direction` is `(u8)func_0809D6BC(...)`, which is 0 to 3, or -1 (0xFF) when the two tiles coincide; a stack-index premise would need proof that this effect never targets the actor's own tile, and none is established.
- Phase 0x101 falls into 0x102 (no `break`), as the ROM does.

kit issue: shubshub/fftadecomp-kit#240; shubshub/fftadecomp-kit#200 (comment) (the pointer-bearing frame word at the second copy, under `named-data-buffer-rom-table-copy-v1`)
