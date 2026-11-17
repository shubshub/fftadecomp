# 0x08071DC8 - unit list sort by mode: bytes identical, refused (word switch and an indexed stack list passed to a callee) (872 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `func_08071DC8(mode, order)` fills `order[24]` with 0xFF,
then switches on `mode & 0x7F` through a guarded six-entry jump table (dispatch at 0x08071E04, table at 0x08071E0C).
Each case collects the enabled units of `g_state_02000000` into a local `list[24]` of (key, index) pairs, keyed by the
field the mode selects (the level byte at +9, the halfwords at +0x1A, +0x1E or +0xD6, or the byte at +6, each shifted
left by 8 plus the index; or the enabled byte), sorts it with `func_08087D98(list, 0, count - 1, descending)`
(`descending` is bit 7 of `mode` inverted) and writes the indices to `order`. Callers: the matched `src/080611F0.c`
and `src/080B8100.c`, and 0x0805451C, 0x0805459C and 0x08067FFC, which are parked because their buffer walks stop at
this function's jump table. This entry refreshes the earlier one; the source is unchanged.

The index row `08071DC8 08072130 872 436 return` has the right extent; 436 is half the byte count, and the reachable
count is 392 (the kit's own refinement and an independent CFG walk agree). The earlier entry called the index correct;
its extent is. No refusal below depends on the count.

## Byte identity

`08071DC8.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08071DC8, with `g_state_02000000` and `func_08087D98`
bound to their ROM addresses (6 `R_ARM_THM_CALL`, 15 `R_ARM_ABS32`). The 872-byte symbol equals the ROM span
`[0x08071DC8, 0x08072130)`: SHA-256 `9ff041fd482b1ee09fa42d627cffcc2e7a2aa31c2dc25dbe01c469d027d2a2a4` for both.
`.text` is exactly 872 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits
0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08071DC8.c` (no data symbol to add): the
default run and the selectors the kit issue and the earlier notes discuss.

| Selector | Result |
|---|---|
| default, `bounded-buffer-root-guarded-switch-v1`, `--switch-data-profile u16-scalars-v2`, `--switch-data-profile u16-scalars-frame-v1` | `unsupported stack-alias use or escape` |
| `named-data-buffer-stack-index-v1`, `named-data-buffer-stack-index-v2`, `bounded-buffer-guarded-switch-v1`, `bounded-buffer-nested-halfword-output-selective-scratch-v1`, `named-data-buffer-v1` | `named-data buffer caller excludes local BL and word switches` |
| `conditional-finite-local-word-loops-v1` | `finite loops exclude local BL and word switches` |

## Cause

Every case stores to `list[n]` at a register index (`adds r1, r7, r0` at 0x08072052: sp + n * 8). The default switch
path and `bounded-buffer-root-guarded-switch-v1` refuse that store; the stack-index and named-data buffer selectors
refuse the word switch. The closest fit is the root-guarded switch with stack-index premises (n < 24 at each `list[n]`
holds because n <= i <= 23, a relation interval analysis cannot prove).

## Source notes

- A choice the bytes do not fully pin, possibly a spare temporary: each sort case counts into a case-local `u8 n` and
copies it with `count = n;` into a function-scope `u8 count`. The ROM has the six copies (`adds r4, rN, #0` at
0x08071E5E, 0x08071EC6, 0x08071F2E, 0x08071FA2, 0x0807200A and 0x0807206E); the sibling 0x08072130 (same callee, same
loops) stores the counter to `data_03002818->count` (`strb` at 0x0807221A and 0x080722A6) before its sort. One
variable, or an inline sort helper, compiles to 852 bytes. A reviewer has to rule on it before this ships.
- The `g_state_02000000` layout is that of the matched `src/0802DBA0.c`, with the field names of `src/0802C270.c`.

## History

The earlier entry's refusals reproduce at 18dcc516; the selective nested-output row is new.

kit issue: shubshub/fftadecomp-kit#200 (comment); shubshub/fftadecomp-kit#241 (there as the jump-table callee of 0x0805451C, 0x0805459C and 0x08067FFC)
