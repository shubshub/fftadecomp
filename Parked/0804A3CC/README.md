# 0x0804A3CC - two-line text panel (name and count): bytes identical, refused (CpuSet fill from a stack halfword; a digit buffer into func_080142DC) (256 bytes)

Attempt 2026-11-18, kit 750d2fb7, decomp main 52ef3ba2f9.
`func_0804A3CC(index, count)` clears the 0x1A00-byte tile buffer `data_06009960` by a CpuSet fill from a stack zero
(0x0804A3F8), builds the first line in `data_02003CB0` from `g_table_08526680[index + 0x2CD]`, `data_083917FA` and
`data_085668B0[27]` (`func_08038D10`) and draws it (`func_08015110`). If `count` is nonzero it formats it as two
digits into a local `u8[16]` (`func_080142DC` at 0x0804A440), appends `data_085668B0[24]` (`func_08038CF0`) and draws
that as the second line; otherwise it draws `data_085668B0[69]`. Its one caller is the `bl` at 0x08048C54, in code
the index does not cover (no row between 0x08046A68 and 0x08049C24).

The index row `0804A3CC 0804A4CC 256 96 return` is right: 96 reachable instructions, the count the kit's own CFG
refinement gives. `config/functions.json` has the same extent and count.

## Byte identity

`0804A3CC.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0804A3CC, with every callee and data symbol bound to its
ROM address (10 `R_ARM_THM_CALL`, 6 `R_ARM_ABS32`). The 256-byte symbol equals the ROM span `[0x0804A3CC,
0x0804A4CC)`: SHA-256 `a6aac1bd3109138fea6fdf93f503dfe76c2b35e740c369c53bba0ce32e211726` for both. `.text` is exactly
256 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 750d2fb7, `match.py --root . --no-write` with this source copied to `src/0804A3CC.c` (no data symbol to add): the
default run, the BIOS buffer selectors, the two addressed BIOS-fill-buffer selectors, `named-data-buffer-v1`, and the
selectors the #192 comment and earlier notes name. None matched.

| Selector | Result |
|---|---|
| default, `bounded-buffer-guarded-bios-division-v1` and `named-data-buffer-v1` (3) | `buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification` |
| `bounded-buffer-bios-sqrt-scratch-v1` | `BIOS Sqrt requires exact complete svc #8; bx lr wrapper` |
| `bounded-buffer-bios-fill-source-v1`, `bounded-buffer-bios-fill-local-source-semantics-v1` and `bounded-buffer-bios-fill-overwritten-control-stores-v1` (3) | `buffer callee 0x080142DC: buffer callee 0x08002FB8: signed remainder requires numeric proof or fresh addressed-call provenance` |
| `bounded-buffer-bios-fast-fill-source-v1`, `bounded-buffer-bios-mixed-fast-fill-source-v1` and `bounded-buffer-bios-mixed-fast-fill-runtime-summaries-v1` (3) | `CpuFastSet fill requires only its actual direct wrapper calls` |
| `bounded-buffer-bios-bg-affine-set-v1`, `bounded-buffer-bios-bg-affine-set-transparent-leaf-scratch-v1` and `bounded-buffer-bios-bg-affine-set-discarded-scratch-v1` (3) | `BgAffineSet requires an actual direct call in its closed owner` |
| `bounded-buffer-bios-mixed-cpuset-fast-fill-source-v1` | `mixed CpuSet/CpuFastSet fill requires actual calls to both wrappers` |
| `bios-word-switch-local-buffers-v1` | `BIOS buffer requires one exact one-object-word switch without local BL` |
| `--addressed-signed-runtime-profile addressed-native-bios-fill-buffer-v1` | `addressed signed runtimes exclude data and irregular relocations` |
| `--addressed-signed-runtime-profile addressed-native-bios-fill-buffer-data-v1` | `buffer callee 0x080142DC: stack aliases cannot cross calls in caller-clobbered registers` |

## Cause

The default buffer walk follows a local address into the BIOS wrapper `func_0814186C` (CpuSet) and refuses its `svc`
(`non-leaf calls and interrupts require linked CFG verification`). The BIOS fill selectors admit the fill and stop in
`func_080142DC`'s callee `func_08002FB8` at the signed remainder, as for 0x080458A4. The #192 comment reports the same
next obstacle with its prototype: the digit loop of `08002FB8`, which stores below its buffer.

kit issue: shubshub/fftadecomp-kit#192 (comment)
