# 0x0806EC60 - inventory category summary: bytes identical, refused (a local byte array written at a register index) (208 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `func_0806EC60(state)` clears a local `u8 present[5]`
(0x0806EC6C-0x0806EC7A), marks the category `func_080CBD34(id)` of every record with a quantity in the list
`func_080CB210(1, &count)` returns (`present[category] = 1` at 0x0806ECA2-0x0806ECA8), appends `data_08393B40[i]` to
`state->entries` for each marked category, and then appends category 5 once if a record of `func_080CB210(0x16A,
&count)` has category 5 and a quantity. `count` is a stack word passed by address to both calls. No `bl` or function
word in the ROM refers to 0x0806EC60.

The index row `0806EC60 0806ED30 208 104 return` has the right extent; 104 is half the byte count, and the reachable
count is 98 (the kit's own refinement and an independent CFG walk agree). No refusal below depends on it.

## Byte identity

`0806EC60.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0806EC60, with every callee and data symbol bound to its
ROM address (4 `R_ARM_THM_CALL`, 1 `R_ARM_ABS32`). The 208-byte symbol equals the ROM span `[0x0806EC60, 0x0806ED30)`:
SHA-256 `09a4e200738281ba6269e83bf26a0a8ec9605d04080b2c60db035772f4bf7151` for both. `.text` is exactly 208 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0806EC60.c` (no data symbol to add): the
default run and the selectors the kit issue and the earlier notes discuss.

| Selector | Result |
|---|---|
| default, `bounded-buffer-guarded-switch-v1`, `bounded-buffer-nested-halfword-output-selective-scratch-v1` | `unsupported stack-alias use or escape` |
| `named-data-buffer-stack-index-v1`, `named-data-buffer-stack-index-v2` | `buffer callee 0x080CBD34: buffer callee 0x080CA7A4: unresolved program-counter write` |

## Cause

The default walk refuses the first store at a register index into the local array (`mov r2, sp; adds r0, r2, r4` at
0x0806EC6C-0x0806EC6E). Only the stack-index selectors bound such an index; under them the walk gets past it and stops
in the callee chain, at the jump table of `func_080CA7A4` (matched) that `func_080CBD34` (matched) reaches.

kit issue: shubshub/fftadecomp-kit#200 (comment); shubshub/fftadecomp-kit#241
