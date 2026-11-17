# 0x0805F44C - task slot starter: bytes identical, refused (a spin inside a scheduler-entry function) (96 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. The function takes the first free one of two task slots in
`*data_0200F44C`, spinning forever when neither is free (`for (;;);`, `b 0x0805F472` at 0x0805F472), then fills a
local 0x1C-byte request with the value and slot and starts `func_0806094C` through the scheduler entry `func_08005954`
(task size 0x98; 0x0805F48A, request in R3 and the parent in the outgoing word). Its callers are the matched
`src/0805D534.c`, `src/0805D784.c`, `src/0805E798.c`, `src/0805E924.c`, `src/0805EAA8.c` and `src/0805EFEC.c`. This
entry refreshes the earlier one; the source is unchanged.

The index row `0805F44C 0805F4AC 96 48 return` has the right extent; 48 is half the byte count, and the reachable
count is 43 (the kit's own refinement and an independent CFG walk agree). The earlier entry called the row correct;
its extent is. No refusal below depends on the count. `data_0200F44C` is already in `config/data_symbols.json`.

## Byte identity

`0805F44C.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0805F44C, with every callee and data symbol bound to its
ROM address and `func_0806094C` as a Thumb function address (1 `R_ARM_THM_CALL`, 2 `R_ARM_ABS32`). The 96-byte symbol
equals the ROM span `[0x0805F44C, 0x0805F4AC)`: SHA-256
`910e98804419e60ead5eb9de8d3f6d90c6dc5db62d0ce8d0d35e932a4887874e` for both. `.text` is exactly 96 bytes. `match.py`
refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0805F44C.c` (no data symbol to add): the
default run and the selectors the kit issue and the earlier notes discuss.

| Selector | Result |
|---|---|
| default | `stack aliases cannot cross calls in caller-clobbered registers` |
| `--control-flow-profile mixed-return-inert-spin-v1` | `inert spins exclude function-address relocations` |
| all 25 `conditional-scheduler-*` values | `reachable control-flow region has no path to a verified return` |

## Cause

The local request reaches `func_08005954` in R3 on the function-literal path, which has no buffer proof (`stack
aliases cannot cross calls in caller-clobbered registers`). The scheduler selectors apply the descriptor contract but
require every reachable region to reach a verified return, which the spin does not; the inert-spin profile admits the
spin but not the function word. It needs the two composed.

## History

The earlier entry (kit fcdf2d45) quoted the inert-spin refusal as `inert spins exclude non-call relocations`; at
18dcc516 it is `inert spins exclude function-address relocations`. It ran two scheduler selectors; all 25 now give the
same refusal. It also named 0x080E29C4, 0x08118590 and 0x0800221C as having the same inert-spin gap (then the data word; not re-checked against the function-word refusal).

kit issue: shubshub/fftadecomp-kit#237 (there as one that stops at another check after the per-site summary)
