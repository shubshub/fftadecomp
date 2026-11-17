# 0x080DF31C - background-layer effect phase callback: bytes identical, refused (a local copy of a ROM table through func_081443FC, a `_call_via_r3` copy and stack outputs in one task callback) (804 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `u32 func_080DF31C(void *task, DF31CDescriptor *descriptor, DF31CState *state)` is the phase callback of an effect that shows a background layer at an object; its only reference is the function word at `0x080DFACC`, in the pool of `func_080DFA70`. Phase 0 copies the source record (layer, palette, priority, size, tile source and destination) into the state, copies the two 24-byte entries `data_0839562C` into the state with the copy callback `data_0836D4BC[0]` (through `_call_via_r3`) and patches their sizes and priorities, and starts the object's graphics task (`func_080DC1E8`). Phase 0x101 copies the 8-byte `u16` priority table `data_08149B80` (0 to 3) to the frame with `func_081443FC`, waits out the delay, writes the layer's control word from `func_08003A74`, `func_08003A80(0x06008000)` and `controls[(flags & 8) != 0]`, reads the object's position (`func_080DBDC8`, into the state) and its screen offset (`func_080DC224`, into two local `s16` words, one passed as the fifth argument), sets the layer offsets, and optionally fades the palette and starts the `data_0839565C` script. Phases 0x102 to 0x104 run the script, start the coordinate task `func_080D6098` with the state's entries, set the window and display bits of `g_control_flags_03000940`, start `data_08395668` and clear the bits when the delay runs out.

```
080DF43A  ldr  r1, =data_08149B80
080DF43C  add  r0, sp, #0x10         @ u16 controls[4]
080DF43E  movs r2, #8
080DF440  bl   0x081443FC
...
080DF476  mov  r0, sp
080DF478  adds r0, r0, r4            @ ((flags & 8) != 0) * 2
080DF47A  adds r0, #0x10
080DF47C  ldrh r0, [r0]              @ controls[index]
...
080DF4A4  add  r4, sp, #0x18         @ &offset_x
080DF4A6  mov  r5, sp
080DF4A8  adds r5, #0x1a             @ &offset_y
080DF4AA  str  r5, [sp]              @ fifth argument
080DF4AC  adds r3, r4, #0
080DF4AE  bl   0x080DC224
```

## The index

The index row `080DF31C 080DF640 804 349 return` is right: the kit's `analyze.refine_function` at 18dcc516 closes the CFG at 349 reachable instructions over the indexed extent, and `config/functions.json` agrees.

## Byte identity

`080DF31C.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080DF31C, with every callee and data symbol bound to its ROM address (21 `R_ARM_THM_CALL`, 9 `R_ARM_ABS32`). The 804-byte symbol equals the ROM span `[0x080DF31C, 0x080DF640)`: SHA-256 `e2bc55a3666d809bf61b9a7209825b889350f82f4eb7c175783f3a0d0777814d` for both. `.text` is exactly 804 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each was added with its address as the value (`"data_08149B80": "0x08149B80"`) for the runs below: `data_08149B80`, `data_0839562C`, `data_0839565C`, `data_08395668`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080DF31C.c` and the data symbols above: the default run and all 213 selector values. None matched. The default run prints the refusal after `compile failed:`, a selector run as `error (ValueError): <text>`.

| Selector | Refusal |
|---|---|
| default, and 6 other selector values | `buffer callee 0x081443FC: unsupported buffer pointer use or escape` |
| `named-data-buffer-rom-table-copy-v1`, `named-data-buffer-stack-index-v1`, `named-data-buffer-stack-index-v2` (3), and 56 other selector values | `acyclic owner excludes arithmetic runtimes and indirect thunks` |

The other 148 selector values give 47 other refusals, none of them a match; the most frequent are `function address requires a canonical addressed function` (43), `private float requires unique undefined pinned helper symbols` (15), `aligned owner requires actual external two-byte Thumb alignment` (12).

## Cause

Two local addresses reach calls: the copy destination `controls` (`func_081443FC`, count 8, a constant ROM source) and the two offset outputs of `func_080DC224`, one of them in the outgoing argument word. On the default path the walk enters `func_081443FC` and stops at its alignment test. The `named-data-buffer-*` selectors, the ROM-table-copy and stack-index ones included, and 56 other owner selectors refuse earlier, on the owner: the phase-0 copy is an indirect call through `_call_via_r3` (`bl 0x08142250` at `0x080DF3C4`, with no local argument), and the acyclic owner rule excludes indirect thunks. In the prototype measured for the kit issue below, a `func_081443FC` summary for local buffers takes this function past the helper on the default path, and it then stops at the owner's register index into the copied table (not re-run here).

## Source notes

- `data_08149B80` is a named ROM object at its literal's address (`0x080DF508`), and the copy is written as the call the ROM makes. The index is the Boolean `(flags & 8) != 0` (`ands`, `rsbs`, `lsrs #31` at `0x080DF458`-`0x080DF462`), so the copy's other two entries are never read.
- The source includes `control_flags.h` for the window and display bits; `plausible.py --strict` exits 0.

kit issue: shubshub/fftadecomp-kit#240
