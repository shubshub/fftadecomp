# 0x0813F22C - display reset with CpuSet and CpuFastSet clears: bytes identical, refused (CpuSet fill from a stack halfword; dead-load window of the volatile check) (524 bytes)

Attempt 2026-11-18, kit 750d2fb7, decomp main 52ef3ba2f9.
`func_0813F22C()` clears the two halves of the palette buffer `data_03003860` with CpuSet fills from stack zeros, in
an order chosen by `func_080C9540(0x44)` (0x0813F24E-0x0813F292), clears 0x18000 bytes of VRAM from a stack zero with
CpuFastSet (`func_08141868` at 0x0813F2A6), sets the offsets, control words, blend and window fields of
`g_control_flags_03000940` and the display word 0x1940, points three background records at their tiles and maps, and
clears buffers through `g_callbacks_0836D4B8[0]` (`_call_via_r2` at 0x0813F3CA-0x0813F3E2: three 0x800-byte maps)
after `func_0813FB7C(data_06004C00, 1)`. Its caller is 0x0813C0EC (0x0813C184).

The index row `0813F22C 0813F438 524 213 return` is right: 213 reachable instructions, the count the kit's own CFG
refinement gives. `config/functions.json` has the same extent and count.

## Byte identity

`0813F22C.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0813F22C, with every callee and data symbol bound to its
ROM address (10 `R_ARM_THM_CALL`, 13 `R_ARM_ABS32`). The 524-byte symbol equals the ROM span `[0x0813F22C,
0x0813F438)`: SHA-256 `2ddff1d75be9f058df510766bb83d550f75463412c5dc5bf3e42f57e2ff7907f` for both. `.text` is exactly
524 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 750d2fb7, `match.py --root . --no-write` with this source copied to `src/0813F22C.c` and `data_06004C00` added to
`config/data_symbols.json` (each at the address its name gives): the default run, the BIOS buffer selectors, the two
addressed BIOS-fill-buffer selectors, `named-data-buffer-v1`, and the selectors the #192 comment and earlier notes
name. None matched.

| Selector | Result |
|---|---|
| default | `buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification` |
| `bounded-buffer-bios-sqrt-scratch-v1`, `bounded-buffer-bios-fast-fill-source-v1`, `bounded-buffer-bios-bg-affine-set-v1` and 10 other selectors (13) | `verdict NOT VERIFIED - the selector was not run` (`source IMPLAUSIBLE`), finding (a) |
| `bounded-buffer-bios-fill-source-v1`, `bounded-buffer-bios-fill-local-source-semantics-v1` and `bounded-buffer-bios-fill-overwritten-control-stores-v1` (3) | `verdict NOT VERIFIED - the selector was not run` (`source IMPLAUSIBLE`), finding (b) |

Plausibility findings printed with `NOT VERIFIED` (verbatim, with the tab inside the quoted instruction shown as a
space):

- (a) `` allowlisted volatile semantic check: func_0813F22C: `ldrh r0, [r5, #10]` (instruction 55) is a dead load of
  g_control_flags_03000940+0xa that is not directly followed by a store to the same member (only constants, the
  store's own operand copies, register operations that neither read the load nor feed the store, and arithmetic that
  builds only the stored value may sit between them); only the read-modify-write load of a member store is the
  qualifier's documented effect ``
- (b) `` allowlisted volatile semantic check: function-address evidence does not support runtime call thunks ``

## Cause

The default buffer walk follows a local address into the BIOS wrapper `func_0814186C` (CpuSet) and refuses its `svc`
(`non-leaf calls and interrupts require linked CFG verification`). The selectors that get further stop at the
allowlisted volatile check: a spilled zero is reloaded between the dead read of the member at +0xA (`bg0hofs`) and its
store (`ldrh r0, [r5, #0xa]; movs r2, #0; ldr r3, [sp, #8]; strh r3, [r5, #0xa]` at 0x0813F2AC-0x0813F2B2; finding
(a)), or the check's own walk refuses the `_call_via_r2` thunk (finding (b)). That window is
shubshub/fftadecomp-kit#165, which cites this function; the #192 comment counts it among the three refused by it after
a BIOS summary.

## Source notes

- The fill temporaries `first` and `second` are used crosswise in the two branches, to reproduce the ROM's slot order;
  earlier notes flag that as a doubt (the CpuFill16 temporary of shubshub/fftadecomp-kit#164).
- Needs `data_06004C00` in `config/data_symbols.json`.

kit issue: shubshub/fftadecomp-kit#192 (comment); related: shubshub/fftadecomp-kit#165 (the dead-load window)
