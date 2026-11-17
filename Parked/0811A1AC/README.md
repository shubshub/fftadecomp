# 0x0811A1AC - zoom-in effect task (BgAffineSet in a scheduler switch): bytes identical, refused (BgAffineSet wrapper in the buffer walk) (732 bytes)

Attempt 2026-11-18, kit 750d2fb7, decomp main 52ef3ba2f9.
`func_0811A1AC(task, descriptor, payload)` is a task callback with a phase switch. Phase 0 starts a sub-task through
`func_080E03F8`; 0x100 waits for it and looks up the target object; 0x101 places a sprite, computes the BG2 transform
with BgAffineSet from local structures (`func_08141864` at 0x0811A2E6), applies it with `func_080032F8`, enables BG2
in the display word (`func_080035A8(2)`) and starts the effect and record tasks; 0x102 steps the zoom and recomputes
the transform (0x0811A38C), then starts the particle and object tasks; 0x103 and 0x104 wait for them. No `bl` reaches
it: its address is a word of the table at 0x08395238.

The index row `0811A1AC 0811A488 732 366 return` has the right extent; 366 is half the byte count, and the reachable
count is 307 (the kit's own CFG refinement). `config/functions.json` has the same extent and count.

## Byte identity

`0811A1AC.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0811A1AC, with every callee and data symbol bound to its
ROM address (34 `R_ARM_THM_CALL`, 9 `R_ARM_ABS32`). The 732-byte symbol equals the ROM span `[0x0811A1AC,
0x0811A488)`: SHA-256 `2310ce4feac32eeab15f0ea103f2d42cdbf0d46e271984816f3bed1688de8e60` for both. `.text` is exactly
732 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 750d2fb7, `match.py --root . --no-write` with this source copied to `src/0811A1AC.c` and `data_083A65A4`,
`data_083A65D4`, `data_083A6604`, `data_083A6618`, `data_083A6620`, `data_088F378C`, `data_0894DEBC` added to
`config/data_symbols.json` (each at the address its name gives): the default run, the BIOS buffer selectors, the two
addressed BIOS-fill-buffer selectors, `named-data-buffer-v1`, and the selectors the #192 comment and earlier notes
name. None matched.

| Selector | Result |
|---|---|
| default, `bounded-buffer-guarded-bios-division-v1` and `named-data-buffer-v1` (3) | `buffer callee 0x08141864: non-leaf calls and interrupts require linked CFG verification` |
| `bounded-buffer-bios-sqrt-scratch-v1` | `BIOS Sqrt requires exact complete svc #8; bx lr wrapper` |
| `bounded-buffer-bios-fill-source-v1`, `bounded-buffer-bios-fill-local-source-semantics-v1` and `bounded-buffer-bios-fill-overwritten-control-stores-v1` (3) | `verdict NOT VERIFIED - the selector was not run` (`source IMPLAUSIBLE`), finding (a) |
| `bounded-buffer-bios-fast-fill-source-v1`, `bounded-buffer-bios-mixed-fast-fill-source-v1` and `bounded-buffer-bios-mixed-fast-fill-runtime-summaries-v1` (3) | `CpuFastSet fill requires only its actual direct wrapper calls` |
| `bounded-buffer-bios-bg-affine-set-v1` | `buffer callee 0x080035A8: BgAffineSet profile requires its exact bound root call` |
| `bounded-buffer-bios-bg-affine-set-transparent-leaf-scratch-v1` | `buffer callee 0x080032F8: stack aliases cannot cross calls in caller-clobbered registers` |
| `bounded-buffer-bios-bg-affine-set-discarded-scratch-v1` | `buffer callee 0x080032F8: consumer observes discarded return scratch before a killing write` |
| `bounded-buffer-bios-mixed-cpuset-fast-fill-source-v1` | `mixed CpuSet/CpuFastSet fill requires actual calls to both wrappers` |
| `bios-word-switch-local-buffers-v1` | `BIOS buffer requires one exact one-object-word switch without local BL` |
| `--addressed-signed-runtime-profile addressed-native-bios-fill-buffer-v1` | `addressed signed runtimes exclude data and irregular relocations` |
| `--addressed-signed-runtime-profile addressed-native-bios-fill-buffer-data-v1` | `addressed data overflows or aliases indexed code` |

Plausibility findings printed with `NOT VERIFIED` (verbatim):

- (a) `` allowlisted volatile semantic check: BIOS fill requires an actual direct call in its closed owner ``

## Cause

The default buffer walk follows a local address into the BIOS wrapper `func_08141864` (BgAffineSet) and refuses its
`svc` (`non-leaf calls and interrupts require linked CFG verification`). The BgAffineSet selectors admit the wrapper
and stop at the next callee: `func_080032F8` (`stack aliases cannot cross calls in caller-clobbered registers`, or the
discarded-scratch rule) or `func_080035A8` (`BgAffineSet profile requires its exact bound root call`). The #192
comment reports the same next obstacle with its prototype: a callee's own stack alias, via `080035A8`.

## Source notes

- Needs `data_083A65A4`, `data_083A65D4`, `data_083A6604`, `data_083A6618`, `data_083A6620`, `data_088F378C`,
  `data_0894DEBC` in `config/data_symbols.json`.

kit issue: shubshub/fftadecomp-kit#192 (comment)
