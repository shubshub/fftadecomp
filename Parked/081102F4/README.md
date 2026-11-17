# 0x081102F4 - affine background effect task (CpuSet fills, BgAffineSet): bytes identical, refused (CpuSet fill from a stack halfword; BgAffineSet) (486 bytes)

Attempt 2026-11-18, kit 750d2fb7, decomp main 52ef3ba2f9.
`func_081102F4(unused, event, work)` is a task callback driven by `event->state`. State 0 fills `work->second` with
0xFFFF by a CpuSet fill from a stack halfword (0x08110356); 0x100 to 0x102 copy graphics to VRAM through
`func_08000A98` and sixteen CpuSet copies between `work` buffers; 0x103 sets up BG2 as an affine layer, computes its
transform with BgAffineSet from local source and destination structures (`func_08141864` at 0x08110454), applies it
with `func_080032F8`, and sets the blend and window masks from `func_0801E610` and `func_080035D0`. No `bl` reaches
it: its address is the literal word at 0x08110A80 in 0x08110888.

The index row `081102F4 081104DA 486 243 return` has the right extent; 243 is half the byte count, and the reachable
count is 191 (the kit's own CFG refinement). `config/functions.json` has the same extent and count.

## Byte identity

`081102F4.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x081102F4, with every callee and data symbol bound to its
ROM address (22 `R_ARM_THM_CALL`, 2 `R_ARM_ABS32`). The 486-byte symbol equals the ROM span `[0x081102F4,
0x081104DA)`: SHA-256 `f3694f876ad932c8c19d8b4fb4df8d1cd6dc4b6c4dc7d0d4d4dfda91d96af009` for both. `.text` is 488
bytes: the symbol and the `c0 46` alignment halfword after it. `match.py` refuses before its own byte comparison
(below). `plausible.py --strict` exits 0.

## Refusals

Kit 750d2fb7, `match.py --root . --no-write` with this source copied to `src/081102F4.c` (no data symbol to add): the
default run, the BIOS buffer selectors, the two addressed BIOS-fill-buffer selectors, `named-data-buffer-v1`, and the
selectors the #192 comment and earlier notes name. None matched.

| Selector | Result |
|---|---|
| default, `bounded-buffer-bios-bg-affine-set-v1`, `bounded-buffer-bios-bg-affine-set-transparent-leaf-scratch-v1` and 3 other selectors (6) | `buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification` |
| `bounded-buffer-bios-sqrt-scratch-v1` | `BIOS Sqrt requires exact complete svc #8; bx lr wrapper` |
| `bounded-buffer-bios-fill-source-v1`, `bounded-buffer-bios-fill-local-source-semantics-v1` and `bounded-buffer-bios-fill-overwritten-control-stores-v1` (3) | `verdict NOT VERIFIED - the selector was not run` (`source IMPLAUSIBLE`), finding (a) |
| `bounded-buffer-bios-fast-fill-source-v1`, `bounded-buffer-bios-mixed-fast-fill-source-v1` and `bounded-buffer-bios-mixed-fast-fill-runtime-summaries-v1` (3) | `CpuFastSet fill requires only its actual direct wrapper calls` |
| `bounded-buffer-bios-mixed-cpuset-fast-fill-source-v1` | `mixed CpuSet/CpuFastSet fill requires actual calls to both wrappers` |
| `bios-word-switch-local-buffers-v1` | `BIOS buffer requires one exact one-object-word switch without local BL` |
| `--addressed-signed-runtime-profile addressed-native-bios-fill-buffer-v1` | `addressed signed runtimes exclude data and irregular relocations` |
| `--addressed-signed-runtime-profile addressed-native-bios-fill-buffer-data-v1` | `buffer callee 0x08141864: non-leaf calls and interrupts require linked CFG verification` |

Plausibility findings printed with `NOT VERIFIED` (verbatim):

- (a) `` allowlisted volatile semantic check: owner literal requires genuine named object proof at 06005400 ``

## Cause

The default buffer walk follows a local address into the BIOS wrapper `func_0814186C` (CpuSet) and refuses its `svc`
(`non-leaf calls and interrupts require linked CFG verification`). The BIOS fill selectors stop at the allowlisted
volatile check (finding (a), the VRAM literal 0x06005400); the BgAffineSet selectors meet the CpuSet wrapper first.
The #192 comment reports that with its prototype summary this function gets past the wrappers and stops at a callee's
own stack alias in `080035D0`.

## Source notes

- Earlier notes record two doubts: the pointer-local fill temporary (`u16 *source = &fill`) and the `(u16)` cast in
  the control word passed to `func_080034B8`.

kit issue: shubshub/fftadecomp-kit#192 (comment)
