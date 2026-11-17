# 0x0801E954 - footprint placement on the map grid: bytes identical, refused (stack outputs and a _call_via_r2 clear in one walk) (724 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `func_0801E954(first, second, third, fourth, fifth, data,
flip_x, flip_z)` projects the point with `func_0801C918(first, second, third, &out_x, &out_z, &out_height)`
(0x0801E9A2; three `s16` stack outputs), decodes the entry's 32-bit layout word into a shape, a direction and signed
9- and 8-bit offsets, looks up the footprint and skew in `data_08149934` and `data_08149964`, and computes the anchor,
mirrored on request. It then clears the two 3-entry neighbour lists `data_0200F1A0` and `data_0200F1B8` through
`g_callbacks_0836D4B8[0]` (`_call_via_r2` at 0x0801EAAA and 0x0801EB44), fills them from `func_0801CC7C` and
`func_0801CC18` for the cells beside the start cell, and returns `func_0801E710(x, z, out_height, second >> 4, width,
depth)`. The matched `src/0801EC78.c` calls it.

The index row `0801E954 0801EC28 724 362 return` has the right extent; 362 is half the byte count, and the reachable
count is 332 (the kit's own refinement and an independent CFG walk agree). No refusal below depends on it.

## Byte identity

`0801E954.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0801E954, with every callee and data symbol bound to its
ROM address (14 `R_ARM_THM_CALL`, 6 `R_ARM_ABS32`). The 724-byte symbol equals the ROM span `[0x0801E954,
0x0801EC28)`: SHA-256 `c31240db34ca29ce4ecfa46b58f1a6af3b5de29699514777b48dec21c3e9628e` for both. `.text` is exactly
724 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0801E954.c` and `data_08149934`,
`data_08149964` added to `config/data_symbols.json` (each at the address its name gives): the default run and the
selectors the kit issue and the earlier notes discuss.

| Selector | Result |
|---|---|
| default | `buffer callee 0x0814224C: non-leaf indirect control flow requires linked CFG verification` |
| `--function-address-profile canonical-thunks-v1` | `function thunks require canonical calls` |
| `bounded-buffer-conditional-thunks-v1` | `refused: function-address evidence does not support runtime call thunks` |

## Cause

The three output addresses are passed to `func_0801C918` before the clears, and the default walk inspects the
`_call_via_r2` thunk at the first clear (0x0801EAAA) and refuses its indirect branch. The conditional-thunk selector
refuses on its function-address evidence and `canonical-thunks-v1` on the explicit thunk calls (below).

## Source notes

- As in 0x0801174C, the clears are explicit calls of the thunk (`func_0814224C(list, sizeof(list), callbacks[0])`).
  The indirect calls `callbacks[0](list, sizeof(list))` give the same bytes (same SHA-256) and the same default
  refusal, and should replace them before this ships. With them `canonical-thunks-v1` refuses with `unsupported
  stack-alias use or escape` and `bounded-buffer-conditional-thunks-v1` with `conditional indirect call excludes local
  argument aliases and pointer words`.
- Open questions from the attempt: the block-scoped `callbacks` pointer locals, and `data` copied into a typed `entry`
  pointer.
- `data_08149934` and `data_08149964` are not in `config/data_symbols.json`; the refusal runs add them (above).

kit issue: shubshub/fftadecomp-kit#190 (comment)
