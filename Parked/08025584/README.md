# 0x08025584 - selected entry of a three-flag set: bytes identical, refused (a local flag array filled by a jump-table callee) (120 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `func_08025584()` has
`func_080C9208(func_080CE410(data_0200F438->object) + 0xCA, flags)` fill a local `u8 flags[4]` (0x080255A0, `mov r1,
sp`), finds the `data_0200F438->selected`-th non-zero flag among the first three, and returns
`func_080C9134(flags[result])`. Its caller is 0x08092784.

The index row `08025584 080255FC 120 60 return` has the right extent; 60 is half the byte count, and the reachable
count is 54 (the kit's own refinement and an independent CFG walk agree). No refusal below depends on it.

## Byte identity

`08025584.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08025584, with every callee and data symbol bound to its
ROM address (3 `R_ARM_THM_CALL`, 1 `R_ARM_ABS32`). The 120-byte symbol equals the ROM span `[0x08025584, 0x080255FC)`:
SHA-256 `a3c028a50421d00dc00bffad338514399cef7bfbac6b3c609b284ef0119380f0` for both. `.text` is exactly 120 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08025584.c` (no data symbol to add): the
default run and the selectors the kit issue and the earlier notes discuss.

| Selector | Result |
|---|---|
| default | `buffer callee 0x080C9208: unresolved program-counter write` |
| `bounded-buffer-guarded-switch-v1` | `buffer callee 0x080C9208: unsupported buffer pointer use or escape` |
| `bounded-buffer-nested-halfword-output-selective-scratch-v1` | `buffer callee 0x080C9208: jump-table buffer callee excludes calls and local BL control` |

## Cause

The walk enters `func_080C9208` (matched `src/080C9208.c`), whose writes sit behind a guarded jump table, and refuses
at the dispatch. `bounded-buffer-guarded-switch-v1` decodes the table and refuses a use of the pointer inside the
callee (`unsupported buffer pointer use or escape`); the selective nested-output selector excludes the callee's calls.

kit issue: (to be filed - match.py: the generic buffer walk cannot inspect a callee that contains a jump table (`buffer callee 0x...: unresolved program-counter write`), although two buffer proofs already decode the layout)
