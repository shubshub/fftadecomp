# 0x080BAB90 - event set-up that finds or spawns the scene object (08099CDC query): bytes identical, refused (the 080C7CC0 callback reached inside the matched 08099CDC) (352 bytes)

Attempt 2026-11-18, kit 750d2fb7, decomp main 52ef3ba2f9.
`func_080BAB90(state, context, id)` clears the state through `g_callbacks_0836D4B8[0]` (`_call_via_r2`, 0x080BABAA),
stores the context, id and group `&data_0854CD54[id]`, and queries up to 13 entries with `func_08099CDC(context,
entries)` (0x080BABC6). If one passes `func_080C8298` it keeps it and queues states 8 and 4; otherwise, if
`func_080BC7AC(id)` allows, it takes the first free unit of `data_02002FC4`, initialises it from `data_0854D1DC`
(`func_080C9644`), creates its scene object (`func_08092440`) and queues state 2. Its caller is the matched
`src/080BC780.c` (0x080BC78C).

The index row `080BAB90 080BACF0 352 176 return` has the right extent; 176 is half the byte count, and the reachable
count is 158 (the kit's own CFG refinement). `config/functions.json` has the same extent and count.

## Byte identity

`080BAB90.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080BAB90, with every callee and data symbol bound to its
ROM address (8 `R_ARM_THM_CALL`, 4 `R_ARM_ABS32`). The 352-byte symbol equals the ROM span `[0x080BAB90, 0x080BACF0)`:
SHA-256 `876878bacdf9a7dc78955f18c41cb212eaa8143d038b9ef24e01c17a2a8cfdea` for both. `.text` is exactly 352 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 750d2fb7, `match.py --root . --no-write` with this source copied to `src/080BAB90.c` and `data_0854D1DC` added to
`config/data_symbols.json` (each at the address its name gives): the default run, the 20 callback, closure,
static-callback and state-iterator selectors the #89 comment measures, and the known-query stack-buffer selector. None
matched.

| Selector | Result |
|---|---|
| default | `buffer callee 0x08099CDC: buffer callee 0x080C7CC0: buffer callee 0x0814225C: non-leaf indirect control flow requires linked CFG verification` |
| `conditional-two-word-callback-closure-v1`, `conditional-two-word-tree-callback-closure-v1`, `conditional-two-word-literal-callback-closure-v1` and 7 other selectors (10) | `acyclic owner excludes arithmetic runtimes and indirect thunks` |
| `conditional-local-state-iterator-v1` | `state contract requires the exact four-byte state and initialized visitor interface` |
| `static-callback-restoring-r6-target-aligned-v1`, `static-callback-restoring-r6-target-leaf-alias-aligned-v1`, `static-callback-restoring-r6-target-leaf-alias-local-scratch-aligned-v1` and 6 other selectors (9) | `aligned owner requires actual external two-byte Thumb alignment` |
| `conditional-known-query-stack-buffer-v1` | `refused: function-address evidence does not support runtime call thunks` |

## Cause

The default walk enters the matched `func_08099CDC` with the local array and descends into the iterator
`func_080C7CC0`, whose callback call goes through `_call_via_r6` (`bl 0x0814225C`): `non-leaf indirect control flow
requires linked CFG verification`. The closure and most static-callback selectors refuse the owner's own
`_call_via_r2` call first (`acyclic owner excludes arithmetic runtimes and indirect thunks`), which is the
literal-closure row the #89 comment quotes.

## Source notes

- `data_0854D1DC` is declared as its own symbol; it may be entry 29 of `data_0854CD54`, but only a separate symbol
  reproduces the literal word (earlier note). Needs `data_0854D1DC` in `config/data_symbols.json`.
- The history pushes are written in place (`state->history[state->count++] = state->current;`), as in the matched
  sibling `src/080BC3B0.c`. An earlier text routed them through a `static inline push_current` helper; it gives the
  same bytes (same SHA-256, measured), so the helper was only a spelling and is not used.

kit issue: shubshub/fftadecomp-kit#89 (comment)
