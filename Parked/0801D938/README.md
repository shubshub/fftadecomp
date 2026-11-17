# 0x0801D938 - map display buffer reset: bytes identical, refused (a CpuFastSet fill from a stack word beside a _call_via_r2 clear) (72 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `func_0801D938()` fills the buffer that `data_02008168 +
0x10` points to with the halfword at `data_02008168 + 8`, using CpuFastSet from a stack word (`func_08141868(&value,
dst, 0x01001000)`, 0x0801D948), clears the 0x200 bytes at `data_02008168 + 0x28` through `g_callbacks_0836D4B8[0]`
(`_call_via_r2` at 0x0801D958), and sets bit 1 of the halfword at `data_02008168 - 0x228 + 0x2C` (pool word
0xFFFFFDD8). Callers: 0x0801D2B8, 0x08092784, 0x08098A88 and 0x080B5A08.

The index row `0801D938 0801D980 72 26 return` is right (26 reachable instructions).

## Byte identity

`0801D938.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0801D938, with every callee and data symbol bound to its
ROM address (2 `R_ARM_THM_CALL`, 2 `R_ARM_ABS32`). The 72-byte symbol equals the ROM span `[0x0801D938, 0x0801D980)`:
SHA-256 `680538c770920efc964b5114d1c0ba38300a71ebb106caff65f6e6faa6f9b772` for both. `.text` is exactly 72 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0801D938.c` (no data symbol to add): the
default run and the selectors the kit issue and the earlier notes discuss.

| Selector | Result |
|---|---|
| default | `buffer callee 0x08141868: non-leaf calls and interrupts require linked CFG verification` |
| `named-data-buffer-v1`, `bounded-buffer-bios-fill-source-v1`, `bounded-buffer-bios-fast-fill-source-v1` | `acyclic owner excludes arithmetic runtimes and indirect thunks` |
| `--addressed-signed-runtime-profile addressed-native-bios-fill-saved-scalar-control-numeric-mmio-data-v1` | `function address requires a canonical addressed function` |
| `conditional-known-query-stack-buffer-v1` | `refused: function-address evidence does not support runtime call thunks` |

## Cause

The stack word is the CpuFastSet fill source, so the default walk enters the wrapper `func_08141868` and refuses its
`svc`. The fill selectors and `named-data-buffer-v1` refuse the `_call_via_r2` call through the named table (`acyclic
owner excludes arithmetic runtimes and indirect thunks`).

## Source notes

- The state flags are reached as `((State0801D938 *)((u8 *)display - 0x228))->flags`. The ROM computes `0x02008168 -
  0x228` (pool word 0xFFFFFDD8 at 0x0801D97C), and so does 0x0801D818, whose source reaches the same word through one
  `g_state_02007F40` structure with the map at +0x228. That form was not compiled for this function; a reviewer should
  prefer it to the cast.

kit issue: shubshub/fftadecomp-kit#236; shubshub/fftadecomp-kit#192 (comment)
