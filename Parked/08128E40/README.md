# 0x08128E40 - random pick of up to `count` active entries: bytes identical, refused (variable index into a local u8[20]; the modulo runtime) (160 bytes)

Attempt 2026-11-18, kit 750d2fb7, decomp main 52ef3ba2f9.
`func_08128E40(count)` collects the indices of the nonzero entries of `g_state_02000000`'s 20-entry table into a local
`u8 order[20]`, shuffles them four times with `func_08002804() % total` (`__modsi3` at 0x08128E86), calls
`func_08038678` for the first `min(count, total)` entries and then `func_080CC2B4`. Its caller is 0x08128FC4
(0x08129162).

The index row `08128E40 08128EE0 160 71 return` is right: 71 reachable instructions, the count the kit's own CFG
refinement gives. `config/functions.json` has the same extent and count.

## Byte identity

`08128E40.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08128E40, with every callee and data symbol bound to its
ROM address (4 `R_ARM_THM_CALL`, 1 `R_ARM_ABS32`). The 160-byte symbol equals the ROM span `[0x08128E40, 0x08128EE0)`:
SHA-256 `41a7ee344d2fbc4d489b718aa01691b9893dfa307c8c047f7986019af2733fb8` for both. `.text` is exactly 160 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 750d2fb7, `match.py --root . --no-write` with this source copied to `src/08128E40.c` (no data symbol to add): the
default run, the two stack-index selectors and the ROM-table-copy selector the #200 comment discusses, and the
selectors earlier notes name. None matched.

| Selector | Result |
|---|---|
| default and `--addressed-signed-runtime-profile compiler-signed-runtime-data-v1` (2) | `unsupported stack-alias use or escape` |
| `named-data-buffer-stack-index-v1`, `named-data-buffer-stack-index-v2` and `named-data-buffer-rom-table-copy-v1` (3) | `function address requires a canonical addressed function` |

## Cause

The default path refuses the variable index into the local array (`unsupported stack-alias use or escape`). The
stack-index selectors refuse the `__modsi3` relocation (`function address requires a canonical addressed function`),
the #200 comment's row; `compiler-signed-runtime-data-v1` gives the default refusal.

kit issue: shubshub/fftadecomp-kit#200 (comment)
