# 0x080458A4 - item window text (name and count): bytes identical, refused (CpuSet fill from a stack halfword; a digit buffer into func_080142DC) (608 bytes)

Attempt 2026-11-18, kit 750d2fb7, decomp main 52ef3ba2f9.
`func_080458A4(id, count)` opens text window 6 (`func_0808A268`, `func_0808AA18`), sets up its tile planes
(`func_08016800`, two `func_0808B7C0` rows), clears its 0xE00-byte tile buffer `data_0600C9E0` by a CpuSet fill from a
stack zero (0x080459A4) and draws a heading. For `id > 0x177` it draws item `id - 0x177` (`func_08038858`,
`func_08037A30`); otherwise it draws item `id`, formats `count` as two digits into a local `u16[8]` with
`func_080142DC` (0x08045A6C), replaces leading zero glyphs 0x1881 with 0x7340, and draws `data_08391918` and the
digits after the name. Its one caller is the `bl` at 0x0804974A, in code the index does not cover (no row between
0x08046A68 and 0x08049C24).

The index row `080458A4 08045B04 608 245 return` is right: 245 reachable instructions, the count the kit's own CFG
refinement gives. `config/functions.json` has the same extent and count.

## Byte identity

`080458A4.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080458A4, with every callee and data symbol bound to its
ROM address (20 `R_ARM_THM_CALL`, 8 `R_ARM_ABS32`). The 608-byte symbol equals the ROM span `[0x080458A4,
0x08045B04)`: SHA-256 `d99bccbd2bb77fa33c6e33149a8775043a84e5e398516c6e649503b8c2295197` for both. `.text` is exactly
608 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 750d2fb7, `match.py --root . --no-write` with this source copied to `src/080458A4.c` and `data_08391918` added to
`config/data_symbols.json` (each at the address its name gives): the default run, the BIOS buffer selectors, the two
addressed BIOS-fill-buffer selectors, `named-data-buffer-v1`, and the selectors the #192 comment and earlier notes
name. None matched.

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
(`non-leaf calls and interrupts require linked CFG verification`). The BIOS fill selectors admit the fill and then
walk the digit buffer into `func_080142DC` and its callee `func_08002FB8`, where they stop at the signed remainder
(`signed remainder requires numeric proof or fresh addressed-call provenance`). The #192 comment reports that with its
prototype summary this function gets past the wrapper and then stops in the digit loop of `08002FB8`, which stores
below its buffer.

## Source notes

- The fill value is written through a pointer to the local (`u16 *source = &fill;`), the spelling merged sources use
  for the SDK fill temporary (for example `src/0804DDCC.c`; see shubshub/fftadecomp-kit#164).
- Earlier notes record two doubts that were not resolved: the block-local placement of the fill temporary and of
  `digits`, and the `for`/`break` form of the zero-glyph loop.

kit issue: shubshub/fftadecomp-kit#192 (comment)
