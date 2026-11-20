# 0x08052870 - menu list controller: bytes identical, refused (same-function long BL jumps outside a switch-frame selector) (2096 bytes)

Attempt 2026-11-20, kit 3afe589f4, decomp main 81362adaf07.
`void func_08052870(u8 index, u8 *state)` is a task callback of the 0x0805 menu module (context `data_0200F428`). It
dispatches on `*state` through a compare tree (states 0, 1, 20, 21, 22, 100-103 and others; no jump table): it sets
up its three windows (item, quantity and totals) at the numeric VRAM addresses 0x0600D000, 0x0600D960 and
0x0600E2C0, fills the list
(`func_08053568(&count, &total)`) and starts its frame animation (`func_0802B3A8`), then runs the list: the cursor
row moves with up and down, L+up and L+down page the scroll by four rows, every change plays sound 0x6D and refreshes
the selection, and the confirm path asks a yes/no question through the message box before acting on the item.

## The index

The index row `08052870 080530A0 2096 1044 return` is right: `push {r4-r7, lr}` plus r8-r10 and `sub sp, #0x20`
(0x08052870-0x0805287A) pair with `add sp, #0x20`, `pop {r3-r5}` (restoring r8-r10), `pop {r4-r7}`, `pop {r0}` and
`bx r0` at 0x08053084-0x08053092, and the literal pool after it ends at the indexed end. No index change is needed.

## Byte identity

`08052870.c` (SHA-256 `60fc58592799a1691d71853c2d01989aed8261e991c2b931b9f3f78601d25ba2`) was compiled as
`match.py` compiles it (fixed flags, `-mthumb-interwork -O2`) and linked at 0x08052870 with every callee and data
symbol bound to its ROM address (107 relocations resolved). The 2096 linked bytes equal the ROM span
`[0x08052870, 0x080530A0)`, SHA-256 `17566c70ba3a91800a46a77743949bbfd092886e9e4ab3aca2a0fbc427220745`.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Two symbols are needed; neither is in `config/data_symbols.json`. Each address is exactly one aligned literal word
in the whole ROM, inside this function:

| Symbol | Literal word | Object |
|---|---|---|
| `data_08422764` | 0x08052B60 | a table of `u32` offsets stepping 0x1C (`2c000000 48000000 64000000 80000000 ...`): the frame table passed as the second argument of `func_0802B3A8` |
| `data_0841CE18` | 0x08052B64 | `u32` offsets followed by `u16` counts (`08000000 30000000 0900 0000 0400 0100 ...`), the layout `func_0802B3A8` reads |

The three VRAM addresses are written as numbers, as the merged sibling `08058D40` writes them.

## Refusals

Kit 3afe589f4 (every refusal line below was rerun there), `match.py --root . --no-write [selector] 0x08052870` with this source copied to `src/08052870.c` and
the symbols above added. None matched.

| Selector | Refusal |
|---|---|
| default | `call is not a validated external direct Thumb BL; function-data-buffer proof: call is not a validated external direct Thumb BL` |
| `--owner-runtime-profile named-data-buffer-v1` | `named-data buffer caller excludes local BL and word switches` |
| `--addressed-runtime-profile addressed-signed-runtime-thunks-data-v1` | `addressed data requires a mapped object and signed32 addend` |
| `--switch-data-profile u16-scalars-functions-frame-v2` | `u16 switch-data requires a mapped local switch without other runtimes; function literals require and are required by a function-literal selector` |
| `--switch-data-profile u16-scalars-functions-frame-v1` | the same |
| `--switch-data-profile u16-scalars-frame-v1` | the same |
| `--switch-data-profile switch-thunks-frame-v1` | `switch thunks require a complete local switch, objects and no other runtime` |

## Cause

The function is longer than the Thumb narrow-branch range, and its compare tree reaches the shared epilogue at
0x08053084 by two same-function long `bl` jumps: at 0x0805289A (after `cmp r4, #1; beq`) and at 0x080528B0 (after
`cmp r4, #0x64; bne`), both `bl 0x08053084`. In `verify_leaf_instructions` (`tools/match.py:4899`) a `bl` whose target
is inside the owner is taken as a local branch only with a double context, the outgoing-argument switch frame proof
(the selectors kit#433 extended for kit#412), or an addressed-signed-runtime thunk selector; otherwise it is refused
as a call at `tools/match.py:4918`. This function has none of those shapes: it has no jump table (the switch-frame
selectors refuse it for that), no runtime and no thunk. It is on the plain frame path with two address-taken byte
locals (`count` and `total` at sp+0x1C and sp+0x1D, passed to `func_08053568` at 0x08052AC8-0x08052AD0 and read
back at 0x08052ADC-0x08052AE0), three function literals (`func_08051084`, `func_080531F0` and `func_08051DB4`, at
0x08052B54, 0x08052E24 and 0x0805309C) and named data. The same long-BL edge proof would need to be available to the
plain and function-data-buffer paths.

## Source notes

1. **`MenuControls controls[1]` in the menu context, read as `controls->row`.** The ROM never folds the cursor row
   into the context offset: every row read forms the record's address and then loads `[base, #0x11]`. A plain
   nested member (`MenuControls controls;`, `controls.row`, `&...controls` where a pointer is passed) compiles to
   2152 bytes. The merged siblings' idiom, a plain member with block-scoped pointer locals (`0805BFC0`, `0805AB34`),
   gives 2096 bytes with 65 differing bytes from 0x08052C78: at the `func_08053348(scroll, row)` calls (0x08052C78,
   0x08052D40) the ROM loads `scroll` before forming the record address, which an inline decayed pointer gives and an
   earlier pointer local does not. A reviewer should judge whether the one-element array is an original-looking
   spelling.
2. **A block-scoped `MenuControls *controls` before each `func_080543CC` call**, as in the merged `0805BFC0` and
   `0805AB34`: the ROM forms the cursor's address before the list's (0x08052C9E, 0x08052D64). Passing
   `data_0200F428->menu.controls->row` inline instead gives 2124 bytes.
3. **The page clamp `if ((s16)(scroll - 4) < 0) scroll = 0; else scroll -= 4;`** (and the `+ 4` counterpart). The
   test is on the 16-bit result (`lsls #16` at 0x08052C6A) and both arms store. Two other spellings give the same
   bytes: `next = scroll - 4; if (next < 0) ...` with an `s16 next` local, and `else scroll = scroll - 4;`. The cast
   form is kept because the local is never stored.
4. **`changed = 1` in every arm, then one refresh block**: the ROM jump-threads the first arm straight into the
   refresh body (0x08052C5E); no `goto` is needed.

No original bug is reproduced.

kit issues: none for this shape yet. Related: shubshub/fftadecomp-kit#412 (closed by kit#433), which admits the same
long-BL edges only under the outgoing-argument switch frame selectors.
