# 0x0804D9D0 - map screen display set-up: bytes identical, refused (CpuSet fills from stack halfwords; volatile pointers into the control block) (552 bytes)

Attempt 2026-11-18, kit 750d2fb7, decomp main 52ef3ba2f9.
`func_0804D9D0()` sets up the four background layers with `func_0801E458`, stores the addresses of the BGxCNT, BGxHOFS
and BGxVOFS members of `g_control_flags_03000940` (from 0x03000942 up) into the layer records `data_03000E60`,
`data_03000E80`, `data_030008B0`, `data_03000990`, clears the blend fields, sets the display word to 0x840, and fills
the map buffers by CpuSet from stack halfwords (0x1111 into the tiles of the fourth layer, zeros into three maps;
0x0804DAB4-0x0804DB0A); between them `func_08000B20` fills the fourth map. It copies two palettes and one of
`data_0841A780`, `data_0841B280`, `data_0841BD60` (by `g_state_02000000`'s mode bits) into `data_03003860` through
`data_0836D4BC[0]` (`_call_via_r3`) and finishes with `func_08148318`. Its caller is the matched `src/0804D86C.c`
(0x0804D8C4).

The index row `0804D9D0 0804DBF8 552 210 return` is right: 210 reachable instructions, the count the kit's own CFG
refinement gives. `config/functions.json` has the same extent and count.

## Byte identity

`0804D9D0.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0804D9D0, with every callee and data symbol bound to its
ROM address (16 `R_ARM_THM_CALL`, 18 `R_ARM_ABS32`). The 552-byte symbol equals the ROM span `[0x0804D9D0,
0x0804DBF8)`: SHA-256 `36fa6232c8f8de24232c36550223c4dcb73499fbb2a9223fabf4f7ed9e0ef46d` for both. `.text` is exactly
552 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 1 (see Source
notes).

## Refusals

Kit 750d2fb7, `match.py --root . --no-write` with this source copied to `src/0804D9D0.c` and `data_0841A780`,
`data_0841B280`, `data_0841BD60` added to `config/data_symbols.json` (each at the address its name gives): the default
run, the BIOS buffer selectors, the two addressed BIOS-fill-buffer selectors, `named-data-buffer-v1`, and the
selectors the #192 comment and earlier notes name. None matched.

| Selector | Result |
|---|---|
| default | `buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification` |
| `bounded-buffer-bios-sqrt-scratch-v1`, `bounded-buffer-bios-fast-fill-source-v1`, `bounded-buffer-bios-bg-affine-set-v1` and 10 other selectors (13) | `verdict NOT VERIFIED - the selector was not run` (`source IMPLAUSIBLE`), finding (a) |
| `bounded-buffer-bios-fill-source-v1`, `bounded-buffer-bios-fill-local-source-semantics-v1` and `bounded-buffer-bios-fill-overwritten-control-stores-v1` (3) | `verdict NOT VERIFIED - the selector was not run` (`source IMPLAUSIBLE`), finding (b) |

Plausibility findings printed with `NOT VERIFIED` (verbatim, with the tab inside the quoted instruction shown as a
space):

- (a) `` allowlisted volatile semantic check: after preprocessing: g_control_flags_03000940 may only be used as
  `g_control_flags_03000940.member`: the whole object (its size, alignment, address or a copy) depends on the pinned
  layout ``
- (b) `` allowlisted volatile semantic check: function-address evidence does not support runtime call thunks ``

## Cause

The default buffer walk follows a local address into the BIOS wrapper `func_0814186C` (CpuSet) and refuses its `svc`
(`non-leaf calls and interrupts require linked CFG verification`). The selectors that get further stop at the
allowlisted volatile check: the source takes the address of `g_control_flags_03000940` (finding (a)), or, for the BIOS
fill selectors, the check's own walk refuses the `_call_via_r3` copies (finding (b)). The #192 comment counts it among
the functions that become byte-identical with a BIOS summary and are then refused statically: `volatile` in the
source, and whole-object and `&` use of the control block.

## Source notes

- The layer records hold `volatile u16 *` members and are given `(volatile u16 *)&g_control_flags_03000940 + n`.
  `plausible.py --strict` exits 1 with 39 findings (`volatile` on lines 6-8 and 66-77, and two `volatile-allowlist`
  findings on each of lines 66-77). The members are bit-fields, so their addresses cannot be taken by name. This needs
  a maintainer decision on a sanctioned spelling for register addresses; shubshub/fftadecomp-kit#224 lists this
  function as one that stores member addresses into records. It does not ship as written.
- The fill values are written through a pointer to a local (`source = &fill;`), the spelling merged sources use for
  the SDK fill temporary (for example `src/0804DDCC.c`; see shubshub/fftadecomp-kit#164).
- Needs `data_0841A780`, `data_0841B280`, `data_0841BD60` in `config/data_symbols.json`.

kit issue: shubshub/fftadecomp-kit#192 (comment); shubshub/fftadecomp-kit#224 (lists it: member addresses of the control block stored into records)
