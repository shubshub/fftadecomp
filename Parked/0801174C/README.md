# 0x0801174C - window object set-up: bytes identical, refused (a _call_via_r2 clear with a local pointer word live, then a jump-table callee) (276 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `func_0801174C(object, kind, entry, parent, value, a, b, c,
d, e)` makes `object` the current window (`data_0200918C`), clears its 0x794 bytes through `g_callbacks_0836D4B8[0]`
(`_call_via_r2` at 0x080117A4), fills its fields from the arguments, sets `field_1c` from `func_080C9540(0x252)`, and
has `func_08018028(object, kind, &slot, flag)` (0x0801181A; `slot` and `u8 flag[4]` are locals) return the text table.
It then calls `func_08011CD0(result, flag[0] ? flag : 0, slot)` and clears the window state. It has 35 callers, 17 of
them matched on main (for example `src/08019A8C.c`, `src/08029544.c`, `src/0812A5BC.c`).

The index row `0801174C 08011860 276 125 return` is right (125 reachable instructions).

## Byte identity

`0801174C.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0801174C, with every callee and data symbol bound to its
ROM address (4 `R_ARM_THM_CALL`, 2 `R_ARM_ABS32`). The 276-byte symbol equals the ROM span `[0x0801174C, 0x08011860)`:
SHA-256 `1405e44886b3358a481cb5bc10e1f80efbbe6231e1b321ed410d188ff866c81b` for both. `.text` is exactly 276 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0801174C.c` (no data symbol to add): the
default run and the selectors the kit issue and the earlier notes discuss.

| Selector | Result |
|---|---|
| default | `buffer callee 0x0814224C: non-leaf indirect control flow requires linked CFG verification` |
| `bounded-buffer-guarded-switch-v1`, `bounded-buffer-nested-halfword-output-selective-scratch-v1`, `bounded-buffer-conditional-thunks-v1` | `refused: function-address evidence does not support runtime call thunks` |
| `--function-address-profile canonical-thunks-v1` | `function thunks require canonical calls` |

## Cause

At the `_call_via_r2` call the frame already holds a pointer to the local `slot` (`mov r1, sp; adds r1, #4; str r1,
[sp, #0x10]` at 0x08011792-0x08011796), so the default walk inspects the thunk and refuses its indirect branch. Behind
it, `flag` and `slot` reach `func_08018028` (matched), which dispatches through a jump table loaded before its guard.

## Source notes

- The clear is written as an explicit call of the thunk, `func_0814224C(data_0200918C, 0x794, callbacks[0])`. The
  indirect call `callbacks[0](data_0200918C, 0x794)` gives the same bytes (same SHA-256) and the same default refusal;
  it is the natural spelling and should replace the explicit thunk call before this ships. With it,
  `bounded-buffer-guarded-switch-v1` refuses with `acyclic owner excludes arithmetic runtimes and indirect thunks`,
  `--function-address-profile canonical-thunks-v1` with `unsupported stack-alias use or escape` and
  `bounded-buffer-conditional-thunks-v1` with `conditional indirect call excludes local argument aliases and pointer
  words`.
- `callbacks` (the table) and `entry_ptr` (`&slot`) are pointer locals; the ROM keeps `&slot` in a frame word (above).
  Whether either is needed was not tested.

kit issue: shubshub/fftadecomp-kit#190 (comment to be posted); (to be filed - match.py: the generic buffer walk cannot inspect a callee that contains a jump table (`buffer callee 0x...: unresolved program-counter write`), although two buffer proofs already decode the layout)
