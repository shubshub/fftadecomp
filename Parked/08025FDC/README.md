# 0x08025FDC - ability category availability test: bytes identical, refused (local range bytes passed through func_080CCE60 to a jump-table callee) (260 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `func_08025FDC(mode)` takes the unit's ability list for
category 1 or 2 (`mode` 6 or 7) from `func_080CCE60(record, category, &first, &last)` (0x08026000 and 0x08026022;
`first` and `last` are stack bytes) with that category's override byte. If `func_080970E8(func_08096D7C(), record)`
holds it returns 1 when an entry of kind 1 or 4 in `[first, last]` passes `func_080CD560` and `func_080CCD50(id,
0x15)`; otherwise it returns 1 when the override is 1 or such an entry passes `func_080CD560`. Its caller is
0x080261D8.

The index row `08025FDC 080260E0 260 116 return` is right (116 reachable instructions).

## Byte identity

`08025FDC.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08025FDC, with every callee and data symbol bound to its
ROM address (7 `R_ARM_THM_CALL`, 3 `R_ARM_ABS32`). The 260-byte symbol equals the ROM span `[0x08025FDC, 0x080260E0)`:
SHA-256 `fa28ac3ff768b22a251cd6c516da7ccbf4a5c916e738af1dab902e65f3157e0d` for both. `.text` is exactly 260 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08025FDC.c` (no data symbol to add): the
default run and the selectors the kit issue and the earlier notes discuss.

| Selector | Result |
|---|---|
| default | `buffer callee 0x080CCE60: buffer callee 0x080C8570: unresolved program-counter write` |
| `bounded-buffer-guarded-switch-v1`, `bounded-buffer-discarded-return-scratch-v1` | `buffer callee 0x080CCE60: consumer observes discarded return scratch before a killing write` |
| `bounded-buffer-nested-halfword-output-selective-scratch-v1` | `buffer callee 0x080970E8: buffer callee 0x08099CDC: buffer callee 0x080C7CC0: buffer callee 0x0814225C: non-leaf indirect control flow requires linked CFG verification` |
| `conditional-known-query-stack-buffer-v1` | `known-query caller private access must be an aligned word` |

## Cause

The walk follows `&first` and `&last` into `func_080CCE60` (matched) and from there into `func_080C8570` (matched),
whose jump table is loaded before its guard and whose default case loops to itself; it refuses at the dispatch.
Neither switch selector knows that layout: the guarded-switch selector refuses inside `func_080CCE60` on its scratch
rule, and the selective nested-output selector stops four calls down `func_080970E8`, at the `_call_via_r6` thunk
0x0814225C.

kit issue: (to be filed - match.py: the generic buffer walk cannot inspect a callee that contains a jump table (`buffer callee 0x...: unresolved program-counter write`), although two buffer proofs already decode the layout)
