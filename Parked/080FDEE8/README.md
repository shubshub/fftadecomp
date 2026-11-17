# 0x080FDEE8 - area check around an object (ROM rectangles, Sqrt in a callee): bytes identical, refused (Sqrt wrapper three callees deep) (168 bytes)

Attempt 2026-11-18, kit 750d2fb7, decomp main 52ef3ba2f9.
`func_080FDEE8(object, target)` copies two 8-byte rectangles from `data_08149DA4` and `data_08149DAC` to the stack.
With a target it calls `func_080DBF90(target, &area, 1, &alternate)` (0x080FDF10); otherwise it reads the object's
position (`func_080D8C58(object, &x, &y)`, 0x080FDF2A), builds a 32 by 16 box around it and calls
`func_080D8604(&bounds, &area, 1, &alternate)` (0x080FDF7A). Its caller is 0x080FE2E8 (0x080FE4EA), which has a
`Parked/` entry.

The index row `080FDEE8 080FDF90 168 71 return` is right: 71 reachable instructions, the count the kit's own CFG
refinement gives. `config/functions.json` has the same extent and count.

## Byte identity

`080FDEE8.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080FDEE8, with every callee and data symbol bound to its
ROM address (3 `R_ARM_THM_CALL`, 2 `R_ARM_ABS32`). The 168-byte symbol equals the ROM span `[0x080FDEE8, 0x080FDF90)`:
SHA-256 `2683507b4b4799bcc7aa6635dae733e6da4752ffb78f394d8d5fd6078e7e254d` for both. `.text` is exactly 168 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 750d2fb7, `match.py --root . --no-write` with this source copied to `src/080FDEE8.c` and `data_08149DA4`,
`data_08149DAC` added to `config/data_symbols.json` (each at the address its name gives): the default run, the BIOS
buffer selectors, the two addressed BIOS-fill-buffer selectors, `named-data-buffer-v1`, and the selectors the #192
comment and earlier notes name. None matched.

| Selector | Result |
|---|---|
| default, `bounded-buffer-guarded-bios-division-v1` and `named-data-buffer-v1` (3) | `buffer callee 0x080DBF90: buffer callee 0x080D8604: buffer callee 0x0801BB94: buffer callee 0x08141898: non-leaf calls and interrupts require linked CFG verification` |
| `bounded-buffer-bios-sqrt-scratch-v1` | `buffer callee 0x080DBF90: buffer callee 0x080D8604: inconsistent possible pointer offsets at control-flow join` |
| `bounded-buffer-bios-fill-source-v1`, `bounded-buffer-bios-fill-local-source-semantics-v1` and `bounded-buffer-bios-fill-overwritten-control-stores-v1` (3) | `BIOS fill requires an actual direct call in its closed owner` |
| `bounded-buffer-bios-fast-fill-source-v1`, `bounded-buffer-bios-mixed-fast-fill-source-v1` and `bounded-buffer-bios-mixed-fast-fill-runtime-summaries-v1` (3) | `CpuFastSet fill requires only its actual direct wrapper calls` |
| `bounded-buffer-bios-bg-affine-set-v1`, `bounded-buffer-bios-bg-affine-set-transparent-leaf-scratch-v1` and `bounded-buffer-bios-bg-affine-set-discarded-scratch-v1` (3) | `BgAffineSet requires an actual direct call in its closed owner` |
| `bounded-buffer-bios-mixed-cpuset-fast-fill-source-v1` | `mixed CpuSet/CpuFastSet fill requires actual calls to both wrappers` |
| `bios-word-switch-local-buffers-v1` | `BIOS buffer requires one exact one-object-word switch without local BL` |
| `--addressed-signed-runtime-profile addressed-native-bios-fill-buffer-v1` | `addressed signed runtimes exclude data and irregular relocations` |
| `--addressed-signed-runtime-profile addressed-native-bios-fill-buffer-data-v1` | `addressed runtime ELF requires actual addressed calls and no unresolved symbols` |

## Cause

The default walk follows the local rectangles through `func_080DBF90`, `func_080D8604` and `func_0801BB94` into the
Sqrt wrapper `func_08141898` and refuses its `svc`. `bounded-buffer-bios-sqrt-scratch-v1` stops earlier, in
`func_080D8604` (`inconsistent possible pointer offsets at control-flow join`). The #192 comment reports that with its
prototype summary this function gets past the wrapper and stops at a pointer use in `080D8C58`.

## Source notes

- The rectangles are read as `*(const struct Rect080FDEE8 *)data_08149DA4` from `const s16[]` declarations; declaring
  the two tables with the structure type would be cleaner (not compiled).
- Needs `data_08149DA4` and `data_08149DAC` in `config/data_symbols.json`.

kit issue: shubshub/fftadecomp-kit#192 (comment)
