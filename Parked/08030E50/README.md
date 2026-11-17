# 0x08030E50 - display reset (palette clear, LCD shadows and background records): bytes identical, refused (CpuSet fill from a stack halfword; dead-load window of the volatile check) (528 bytes)

Attempt 2026-11-18, kit 750d2fb7, decomp main 52ef3ba2f9.
`func_08030E50()` clears the 0x400-byte palette buffer `data_03003860` in two halves with CpuSet fills from stack
zeros (0x08030E6C, 0x08030E84), resets the background offsets, control words, window and blend fields of
`g_control_flags_03000940`, points the four background records `data_03000E60`, `data_03000E80`, `data_030008B0`,
`data_03000990` at their VRAM tiles and maps, and copies the four map pointers into `g_state_03002810`. Callers: five
sites in 0x08030200 (0x0803061C, 0x08030674, 0x08030760, 0x08030996, 0x080309F0) and the matched `src/0803172C.c`
(0x0803175E).

The index row `08030E50 08031060 528 228 return` is right: 228 reachable instructions, the count the kit's own CFG
refinement gives. `config/functions.json` has the same extent and count.

## Byte identity

`08030E50.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08030E50, with every callee and data symbol bound to its
ROM address (2 `R_ARM_THM_CALL`, 12 `R_ARM_ABS32`). The 528-byte symbol equals the ROM span `[0x08030E50,
0x08031060)`: SHA-256 `7eb667f6a4edb557565c01929192c83c428a1916e1f9b6f208a36b90c6505a13` for both. `.text` is exactly
528 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 750d2fb7, `match.py --root . --no-write` with this source copied to `src/08030E50.c` (no data symbol to add): the
default run, the BIOS buffer selectors, the two addressed BIOS-fill-buffer selectors, `named-data-buffer-v1`, and the
selectors the #192 comment and earlier notes name. None matched.

| Selector | Result |
|---|---|
| default | `buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification` |
| `bounded-buffer-bios-sqrt-scratch-v1`, `bounded-buffer-bios-fill-source-v1`, `bounded-buffer-bios-fast-fill-source-v1` and 11 other selectors (14) | `verdict NOT VERIFIED - the selector was not run` (`source IMPLAUSIBLE`), finding (a) |
| `bounded-buffer-bios-fill-local-source-semantics-v1` and `bounded-buffer-bios-fill-overwritten-control-stores-v1` (2) | `verdict NOT VERIFIED - the selector was not run` (`source IMPLAUSIBLE`), finding (b) |

Plausibility findings printed with `NOT VERIFIED` (verbatim, with the tab inside the quoted instruction shown as a
space):

- (a) `` allowlisted volatile semantic check: func_08030E50: `ldrb r0, [r5]` (instruction 63) is a dead load of
  g_control_flags_03000940+0x43 that is not directly followed by a store to the same member (only constants, the
  store's own operand copies, register operations that neither read the load nor feed the store, and arithmetic that
  builds only the stored value may sit between them); only the read-modify-write load of a member store is the
  qualifier's documented effect ``
- (b) `` allowlisted volatile semantic check: real compile of func_08030E50: bounded local fill source has unknown
  content at `bl func_0814186C` ``

## Cause

The default buffer walk follows a local address into the BIOS wrapper `func_0814186C` (CpuSet) and refuses its `svc`
(`non-leaf calls and interrupts require linked CFG verification`). Every selector that gets further runs the
allowlisted volatile check first and stops there: the ROM reloads a spilled zero between the dead read of a
`g_control_flags_03000940` member and its store (`ldrb r0, [r5]; ldr r3, [sp, #4]; strb r3, [r5]` at
0x08030ED0-0x08030ED4), which the check does not admit (finding (a)); the two local-source fill selectors stop at the
fill's unknown content instead (finding (b)). That window is shubshub/fftadecomp-kit#165; the #192 comment counts this
function among the three that become byte-identical with a BIOS summary and are then refused by it.

## Source notes

- The two fill temporaries are written as in the matched sibling `src/08031060.c` (`source = &clear; *source = 0;`,
  and a one-element array), the open-coded CpuFill16 temporary that shubshub/fftadecomp-kit#164 asks about.

kit issue: shubshub/fftadecomp-kit#192 (comment); related: shubshub/fftadecomp-kit#165 (the dead-load window)
