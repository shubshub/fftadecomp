# 0x08137CC4 - display reset (palette clear, LCD shadows and background records): bytes identical, refused (CpuSet fill from a stack halfword; dead-load window of the volatile check) (512 bytes)

Attempt 2026-11-18, kit 750d2fb7, decomp main 52ef3ba2f9.
`func_08137CC4()` is the same reset as 0x08030E50 with other values: it clears both halves of the palette buffer
`data_03003860` with CpuSet fills from stack zeros (0x08137CE0, 0x08137CF8), resets the offsets, control words, window
and blend fields of `g_control_flags_03000940`, points the four background records at `data_06008000` and their maps,
and copies the map pointers into the state `data_030027D8` points to. Callers: 0x08138EFC (0x08138F3C) and 0x08139C70
(0x0813A098).

The index row `08137CC4 08137EC4 512 219 return` is right: 219 reachable instructions, the count the kit's own CFG
refinement gives. `config/functions.json` has the same extent and count.

## Byte identity

`08137CC4.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08137CC4, with every callee and data symbol bound to its
ROM address (2 `R_ARM_THM_CALL`, 12 `R_ARM_ABS32`). The 512-byte symbol equals the ROM span `[0x08137CC4,
0x08137EC4)`: SHA-256 `84fe7512ff4cf7e79397e10fdc3a0b37badb49cfe7ea60937951a7fac9065aca` for both. `.text` is exactly
512 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 750d2fb7, `match.py --root . --no-write` with this source copied to `src/08137CC4.c` and `data_06006800` added to
`config/data_symbols.json` (each at the address its name gives): the default run, the BIOS buffer selectors, the two
addressed BIOS-fill-buffer selectors, `named-data-buffer-v1`, and the selectors the #192 comment and earlier notes
name. None matched.

| Selector | Result |
|---|---|
| default | `buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification` |
| `bounded-buffer-bios-sqrt-scratch-v1`, `bounded-buffer-bios-fill-source-v1`, `bounded-buffer-bios-fast-fill-source-v1` and 11 other selectors (14) | `verdict NOT VERIFIED - the selector was not run` (`source IMPLAUSIBLE`), finding (a) |
| `bounded-buffer-bios-fill-local-source-semantics-v1` and `bounded-buffer-bios-fill-overwritten-control-stores-v1` (2) | `verdict NOT VERIFIED - the selector was not run` (`source IMPLAUSIBLE`), finding (b) |

Plausibility findings printed with `NOT VERIFIED` (verbatim, with the tab inside the quoted instruction shown as a
space):

- (a) `` allowlisted volatile semantic check: func_08137CC4: `ldrb r0, [r5]` (instruction 63) is a dead load of
  g_control_flags_03000940+0x43 that is not directly followed by a store to the same member (only constants, the
  store's own operand copies, register operations that neither read the load nor feed the store, and arithmetic that
  builds only the stored value may sit between them); only the read-modify-write load of a member store is the
  qualifier's documented effect ``
- (b) `` allowlisted volatile semantic check: real compile of func_08137CC4: bounded local fill source has unknown
  content at `bl func_0814186C` ``

## Cause

The default buffer walk follows a local address into the BIOS wrapper `func_0814186C` (CpuSet) and refuses its `svc`
(`non-leaf calls and interrupts require linked CFG verification`). The selectors that get further stop at the
allowlisted volatile check: a spilled zero is reloaded between the dead read of a control-block member and its store
(`ldrb r0, [r5]; ldr r3, [sp, #4]; strb r3, [r5]` at 0x08137D44-0x08137D48; finding (a)), or the fill's content is
unknown to the local-source selectors (finding (b)). That window is shubshub/fftadecomp-kit#165, which cites this
function; the #192 comment counts it among the three refused by it after a BIOS summary.

## Source notes

- The fill temporaries are written as `u16 *p = &first; *p = 0;`, standing in for the SDK CpuFill16 `vu16` temporary;
  shubshub/fftadecomp-kit#164 discusses this function (the CpuFill16 macro cannot be used in a
  `g_control_flags_03000940` user).
- Needs `data_06006800` in `config/data_symbols.json`.

kit issue: shubshub/fftadecomp-kit#192 (comment); related: shubshub/fftadecomp-kit#165 (the dead-load window), shubshub/fftadecomp-kit#164 (the fill temporary)
