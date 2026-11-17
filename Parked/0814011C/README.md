# 0x0814011C - three-step phase driver ending in a DMA3 VRAM clear from a stack halfword: bytes identical, refused (a local address written to the DMA3 source register) (164 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321 with the match batches then queued for merge (PRs #200 onward). `void func_0814011C(unused, phase)` is a phase driver called by `func_0813DB34` (0x0813DB3A). Phase 0 runs
`func_0813FD78()` and stores the object made by `func_081413F8()` in `data_0200F3C0`; phase 1 feeds the input halfwords
at `0x03000000` to `func_0814143C(object, pressed, held)` until it returns 0; phase 2 releases the object
(`func_08141474`), sets `g_state_0200F390` to 0xFF, clears 0xC000 halfwords of VRAM at `0x06000000` with DMA3 in
immediate, fixed-source, 16-bit mode (`0x8100C000`) from a zero halfword on the stack, and sets the DISPCNT copy in
`g_control_flags_03000940` to 0x40.

```
08140186  mov  r1, sp
08140188  movs r0, #0
0814018A  strh r0, [r1]           @ value = 0
0814018C  ldr  r1, =0x040000D4    @ DMA3SAD
0814018E  mov  r0, sp
08140190  str  r0, [r1]           @ SAD = &value
08140192  movs r0, #0xc0
08140194  lsls r0, r0, #0x13
08140196  str  r0, [r1, #4]       @ DAD = 0x06000000
08140198  ldr  r0, =0x8100C000
0814019A  str  r0, [r1, #8]       @ CNT: enable, immediate, fixed source, 0xC000 halfwords
0814019C  ldr  r0, [r1, #8]       @ read back
```

## The index

`symbols/functions.txt` has `0814011C 081401C0 164 60 return` and `config/functions.json` the same extent with 60 instructions (`thumb-prologue`). The CFG, closed by the kit's own `analyze.refine_function`, has 60 reachable instructions, so the row is right.

## Byte identity

`0814011C.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0814011C, with every callee bound to its ROM address and every data word to the address its symbol names (4 `R_ARM_THM_CALL`, 7 `R_ARM_ABS32`). The 164-byte symbol equals the ROM span `[0x0814011C, 0x081401C0)`: SHA-256 `1a3c9be95f300b13de390d4ada803c20d28725912fe7d0e2f02281c7d6b0efef` for both. `.text` is exactly 164 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

None: every data symbol the source names is already in `config/data_symbols.json` on main.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0814011C.c`: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, `--control-flow-profile mixed-return-inert-spin-v1`, `--signed-quotient-profile positive-constant-frame-v1` and `--unsigned-quotient-profile positive-constant-frame-v1` (4) | `unsupported stack-alias use or escape` |
| `--addressed-runtime-profile addressed-native-bios-fill-buffer-data-v1`, `--addressed-runtime-profile compiler-signed-runtime-data-v1`, `--addressed-runtime-profile addressed-native-bios-fill-scalar-control-numeric-mmio-code-image-data-v1` and 26 other addressed-runtime selectors (29) | `addressed runtime ELF requires actual addressed calls and no unresolved symbols` |
| `--addressed-runtime-profile addressed-native-bios-fill-buffer-v1`, `--addressed-runtime-profile addressed-native-bios-fill-readonly-two-words-v1`, `--addressed-runtime-profile addressed-native-bios-ordinary-v1` and 10 other addressed-runtime selectors (13) | `addressed signed runtimes exclude data and irregular relocations` |
| `bounded-buffer-runtime-summaries-v1`, `named-data-buffer-v1`, `named-data-buffer-known-query-callee-v1` and 32 other selectors (35) | `unsupported stack-alias use or escape` |
| `bounded-buffer-bios-mixed-fast-fill-runtime-summaries-v1`, `bounded-buffer-bios-fast-fill-source-v1` and `bounded-buffer-bios-mixed-fast-fill-source-v1` (3) | `CpuFastSet fill requires only its actual direct wrapper calls` |
| `named-data-buffer-finite-small-copy-binding-v1` | `one actual canonical small-copy call required` |
| `named-data-buffer-compiler-copy80-binding-v1` | `compiler copy requires exactly one memcpy call and named data only` |
| `bounded-buffer-bios-fill-source-v1`, `bounded-buffer-bios-fill-local-source-semantics-v1` and `bounded-buffer-bios-fill-overwritten-control-stores-v1` (3) | `verdict NOT VERIFIED - the selector was not run`, with the plausibility finding `allowlisted volatile semantic check: BIOS fill requires an actual direct call in its closed owner` |
| `bounded-buffer-bios-bg-affine-set-v1`, `bounded-buffer-bios-bg-affine-set-transparent-leaf-scratch-v1` and `bounded-buffer-bios-bg-affine-set-discarded-scratch-v1` (3) | `BgAffineSet requires an actual direct call in its closed owner` |
| `bounded-buffer-bios-mixed-cpuset-fast-fill-source-v1` | `mixed CpuSet/CpuFastSet fill requires actual calls to both wrappers` |
| `bios-word-switch-local-buffers-v1` | `BIOS buffer requires one exact one-object-word switch without local BL` |

The other 120 selector values are not listed one by one (none matched); by family: scheduler (25), callback and closure (21), private float and double (15), switch-layout (13), owner (12), canonical-integer (8), restoring-owner (7), function-address (6), arithmetic-runtime (5), bounded-buffer (4), descriptor and preservation (2), -O0 (1), guarded-switch buffer (1).

## Cause

Every run that reaches the walk refuses the store of the stack address into the DMA3 source register at
0x08140190: `unsupported stack-alias use or escape`. The address goes into a write-only register, and the transfer
(immediate start, fixed source, no repeat) reads the one halfword before the CPU continues; the control word is read
back at 0x0814019C. Nothing else in the function stops the walk: the DMA issue reports `MATCH - byte identical` with its
rule alone, and a refusal with the control changed to an incrementing source (`0x8000C000`), VBlank start (`0x9100C000`)
or repeat (`0x8300C000`).

## Source notes

From the attempt, not reviewed:

- The clear is a `static inline void fill_vram16(u16 value)` helper that writes the DMA3 block through a `volatile`
  pointer to `data_040000D4` (with a `plausible:` justification comment), the shape of the SDK's `DmaFill16`. It is a
  domain operation (a VRAM fill), which the inline-helper rule admits; it is used once.
- The source declares `func_0814143C` with three arguments; `src/0814143C.c` on main declares two.

kit issue: shubshub/fftadecomp-kit#239
