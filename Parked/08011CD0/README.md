# 0x08011CD0 - window text set-up with a prefix: bytes identical, refused (a local byte passed through func_08013E9C to a jump-table callee) (204 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `func_08011CD0(table, prefix, entry)` copies the optional
`prefix` string into the current window's text buffer (`data_0200918C->text`), expands table entry `entry` after it
with `func_08013E9C(&text[length], table, scratch, entry, 0, &lines)` (0x08011D28; `lines` is a stack byte at sp+8),
sets the window's width from `func_080144F4(text, 1) >> 3` when it is 0 and its height from `lines * 2`, and rewinds
its text and pixel cursors. Its caller is 0x0801174C.

The index row `08011CD0 08011D9C 204 96 return` is right (96 reachable instructions).

## Byte identity

`08011CD0.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08011CD0, with every callee and data symbol bound to its
ROM address (2 `R_ARM_THM_CALL`, 1 `R_ARM_ABS32`). The 204-byte symbol equals the ROM span `[0x08011CD0, 0x08011D9C)`:
SHA-256 `5442469545c135f8f40bd7df55344d70ad37e10f9c2ad8d6a79625b174844abc` for both. `.text` is exactly 204 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08011CD0.c` (no data symbol to add): the
default run and the selectors the kit issue and the earlier notes discuss.

| Selector | Result |
|---|---|
| default | `buffer callee 0x08013E9C: buffer callee 0x08013F20: unresolved program-counter write` |
| `bounded-buffer-guarded-switch-v1` | `buffer callee 0x08013E9C: buffer callee 0x08013F20: function-address evidence does not support runtime call thunks` |
| `bounded-buffer-nested-halfword-output-selective-scratch-v1` | `buffer callee 0x08013E9C: buffer callee 0x08013F20: jump-table buffer callee excludes calls and local BL control` |

## Cause

The walk follows `&lines` into `func_08013E9C` (matched) and from there into `func_08013F20` (matched), which
dispatches through a guarded jump table, and refuses at its `mov pc` (`unresolved program-counter write`).
`bounded-buffer-guarded-switch-v1` decodes that table and then refuses `func_08013F20`'s indirect call through
`data_0836D4BC` (`function-address evidence does not support runtime call thunks`), and the selective nested-output
selector, the only one that follows a jump table inside a callee, excludes calls there.

kit issue: shubshub/fftadecomp-kit#241
