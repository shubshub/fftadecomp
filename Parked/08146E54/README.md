# 0x08146E54 - palette fade interval set-up: bytes identical, refused (variable index into two local u8[3]; a _call_via_r2 clear) (356 bytes)

Attempt 2026-11-18, kit 750d2fb7, decomp main 52ef3ba2f9.
`func_08146E54(first, last, duration, setting)` calls `func_08146DC8(first, last, 29)`, allocates a 0x2C-byte interval
(`func_08007138`), clears it through `g_callbacks_0836D4B8[0]` (`_call_via_r2`, 0x08146E92) and appends it to the list
`data_03003C60`. For each colour in the range it splits the current colour (`data_03003860`) and the target
(`data_03003E68`) into five-bit channels in two local `u8[3]` arrays and stores the per-channel step and delta; it
then sets the interval's range, bounds, setting and flags and returns it. Callers: 14 matched functions from
`src/0814731C.c` to `src/08147F50.c`.

The index row `08146E54 08146FB8 356 162 return` is right: 162 reachable instructions, the count the kit's own CFG
refinement gives. `config/functions.json` has the same extent and count.

## Byte identity

`08146E54.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08146E54, with every callee and data symbol bound to its
ROM address (3 `R_ARM_THM_CALL`, 6 `R_ARM_ABS32`). The 356-byte symbol equals the ROM span `[0x08146E54, 0x08146FB8)`:
SHA-256 `89bb3697d39866cbc90ff564ae47c95f390ad586bc60c64ec4368a56e38b0940` for both. `.text` is exactly 356 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 750d2fb7, `match.py --root . --no-write` with this source copied to `src/08146E54.c` (no data symbol to add): the
default run, the two stack-index selectors and the ROM-table-copy selector the #200 comment discusses, and the
selectors earlier notes name. None matched.

| Selector | Result |
|---|---|
| default | `unsupported stack-alias use or escape` |
| `named-data-buffer-stack-index-v1`, `named-data-buffer-stack-index-v2` and `named-data-buffer-rom-table-copy-v1` (3) | `acyclic owner excludes arithmetic runtimes and indirect thunks` |
| `conditional-finite-local-word-loops-v1` and `conditional-finite-spilled-scalar-loops-v1` (2) | `refused: function-address evidence does not support runtime call thunks` |

## Cause

The default path refuses the variable channel index into the local arrays (`unsupported stack-alias use or escape`).
The stack-index and ROM-table-copy selectors refuse the `_call_via_r2` thunk (`acyclic owner excludes arithmetic
runtimes and indirect thunks`), the #200 comment's row; the finite-loop selectors give `refused: function-address
evidence does not support runtime call thunks`.

## Source notes

- The allocation and the range set-up are `static inline` helpers (`allocate_interval`, `initialize_range`); written
  out in place, the bytes differ (measured: the same length but different code without `allocate_interval`, 8 bytes
  shorter without `initialize_range`). `allocate_interval` has the statements of the helper in the merged
  `src/08146FB8.c`, `src/08147068.c` and `src/08147124.c`. Those three also have an `initialize_range`, but theirs
  sets more fields (`first` and `second`, and `active` or `data` and `count`); this one only sets `target` and
  `current` to the duration. Whether a one-statement helper with only the name and role in common passes the
  inline-helper rule is a review question.

kit issue: shubshub/fftadecomp-kit#200 (comment)
