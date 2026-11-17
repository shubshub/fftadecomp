# 0x08135B40 - screen init: DMA3 palette fills from a stack halfword, a BIOS CpuFastSet fill, BG setup and three map clears: bytes identical, refused (a local address written to the DMA3 source register) (444 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321 with the match batches then queued for merge (PRs #200 onward). `void func_08135B40(void)` initialises a screen; its caller is `func_08136084` (0x08136144). It picks a fill
colour from `func_08137B14()` (0 when it returns 2, else 0x7FFF), stores it in a stack halfword and fills the two
256-halfword palette halves at `0x03003860` with DMA3 in immediate, fixed-source, 16-bit mode (`0x81000100`, the
`SAD`/`DAD`/`CNT` block `data_040000D4`, control read back); clears 0x6000 words of VRAM at `0x06000000` with BIOS
CpuFastSet in fill mode from a stack word (`func_08141868(&zero, 0x06000000, 0x01006000)` at 0x08135B8E); writes the BG,
blend and window registers in `g_control_flags_03000940`; sets up three BG map records (`data_03000E60`, `data_03000E80`,
`data_030008B0`); and clears three 0x800-byte maps through the first callback of `g_callbacks_0836D4B8` with
`_call_via_r2` (`func_0814224C`, 0x08135C90, 0x08135C9A, 0x08135CA6).

```
08135B5C  strh r4, [r0]           @ fill (r0 = sp)
08135B5E  ldr  r0, =0x040000D4    @ DMA3SAD
08135B60  mov  r1, sp
08135B62  str  r1, [r0]           @ SAD = &fill
08135B64  ldr  r2, =0x03003860
08135B66  str  r2, [r0, #4]       @ DAD
08135B68  ldr  r3, =0x81000100
08135B6A  str  r3, [r0, #8]       @ CNT: enable, immediate, fixed source, 0x100 halfwords
08135B6C  ldr  r1, [r0, #8]       @ read back
...                               @ second half at 0x08135B6E-0x08135B7E
08135B82  str  r5, [sp, #4]       @ zero = 0
08135B84  add  r0, sp, #4
08135B8A  ldr  r2, =0x01006000    @ fill mode, 0x6000 words
08135B8E  bl   0x08141868         @ CpuFastSet
```

## The index

`symbols/functions.txt` has `08135B40 08135CFC 444 180 call` and `config/functions.json` the same extent with 180 instructions (`call`). The CFG, closed by the kit's own `analyze.refine_function`, has 180 reachable instructions, so the row is right.

## Byte identity

`08135B40.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08135B40, with every callee bound to its ROM address and every data word to the address its symbol names (5 `R_ARM_THM_CALL`, 12 `R_ARM_ABS32`). The 444-byte symbol equals the ROM span `[0x08135B40, 0x08135CFC)`: SHA-256 `65f2f45b417ff6dcecc1d215edfbc97835405d539b29514dfafe946153fb0ec0` for both. `.text` is exactly 444 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each is added with its address as the value (`"data_0600E800": "0x0600E800"`):

`data_0600E800`, `data_0600F000`, `data_0600F800`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08135B40.c` and the data symbols above added: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, `--signed-quotient-profile positive-constant-frame-v1` and `--unsigned-quotient-profile positive-constant-frame-v1` (3) | `unsupported stack-alias use or escape` |
| `--addressed-runtime-profile addressed-native-bios-fill-buffer-v1`, `--addressed-runtime-profile addressed-native-bios-fill-buffer-data-v1`, `bounded-buffer-runtime-summaries-v1` and 149 other selectors (152) | `function-address evidence does not support runtime call thunks` |
| `bounded-buffer-bios-fill-source-v1`, `bounded-buffer-bios-fill-local-source-semantics-v1` and `bounded-buffer-bios-fill-overwritten-control-stores-v1` (3) | `verdict NOT VERIFIED - the selector was not run`, with the plausibility finding `allowlisted volatile semantic check: function-address evidence does not support runtime call thunks` |

The other 56 selector values are not listed one by one (none matched); by family: private float and double (15), switch-layout (13), callback and closure (9), function-address (6), arithmetic-runtime (5), owner (3), restoring-owner (2), control-flow (1), -O0 (1), canonical-integer (1).

## Cause

The default run (named data, direct calls; the three `_call_via_r2` calls carry no local alias, so the plain path
treats them as ordinary calls) refuses the first local address stored to memory, the DMA3 source register write at
0x08135B62: `unsupported stack-alias use or escape`. The DMA transfer is immediate with a fixed source, so it reads the
stack halfword before the next instruction, and the address goes to a write-only register.

Every buffer and BIOS selector refuses earlier, at the callback calls: `function-address evidence does not support
runtime call thunks` (the three BIOS fill selectors report it through the allowlisted volatile semantic check, as
`verdict NOT VERIFIED - the selector was not run`). The CpuFastSet fill from the local `zero` would need the BIOS
summary even without that.

The DMA issue reports `MATCH - byte identical` in a prototype with its DMA rule and the #192 comment's BIOS fill
call-site summary, both on the default path, and a refusal with either one alone (the DMA store without the DMA
rule; `buffer callee 0x08141868: non-leaf calls and interrupts require linked CFG verification` without the BIOS
rule). Its negative control is this function with the CpuFastSet control changed to copy mode, which the BIOS rule
refuses.

## Source notes

From the attempt, not reviewed:

- The DMA register block is the typed data symbol `data_040000D4` accessed through a `volatile` pointer local, with a
  `plausible:` justification comment in the source; `plausible.py --strict` accepts it.
- In the colour-0 arm the fill is written through a pointer local (`u16 *p = &fill; *p = 0;`), in the other arm
  directly (`fill = 0x7FFF;`). With the plain store in both arms 2 halfwords differ, so the pointer is load-bearing;
  the attempt noted that the SDK's `DmaFill16`, with its `vu16` temporary, reproduces the bytes without it but needs a
  volatile local. Whether the pointer is the fill macro's shape or steering is a review question; the source rules
  refuse a temporary that only moves registers.
- The DMA sequence is written in both arms; the ROM has it once after the two colour loads (the arms join at
  0x08135B5C).

kit issue: (to be filed - match.py: an immediate DMA fill whose fixed source is a local word is refused as a stack-alias escape); shubshub/fftadecomp-kit#192 (comment to be posted) (the CpuFastSet fill at the root call site)
