# 0x0813BDD0 - screen init: DMA3 palette fills from a stack halfword, a BIOS CpuFastSet fill, BG setup and one map clear: bytes identical, refused (a local address written to the DMA3 source register) (284 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321 with the match batches then queued for merge (PRs #200 onward). `void func_0813BDD0(void)` initialises a screen; its caller is `func_0813BCF0` (0x0813BD2E). It clears the two
256-halfword palette halves at `0x03003860` with DMA3 in immediate, fixed-source, 16-bit mode (`0x81000100`) from a zero
halfword on the stack (`data_040000D4` is the DMA3 register block; the control word is read back after each start),
clears 0x6000 words of VRAM at `0x06000000` with BIOS CpuFastSet in fill mode from a stack word
(`func_08141868(&fill, 0x06000000, 0x01006000)` at 0x0813BE0A), writes the BG, blend and window registers in
`g_control_flags_03000940`, sets up the BG map record `data_03000E60`, and clears the map at `0x06008000` through the
first callback of `g_callbacks_0836D4B8` with `_call_via_r2` (`func_0814224C`, 0x0813BEBE). It is the smaller sibling of
`0x08135B40`.

## The index

`symbols/functions.txt` has `0813BDD0 0813BEEC 284 123 return` and `config/functions.json` the same extent with 123 instructions (`thumb-prologue`). The CFG, closed by the kit's own `analyze.refine_function`, has 123 reachable instructions, so the row is right.

## Byte identity

`0813BDD0.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0813BDD0, with every callee bound to its ROM address and every data word to the address its symbol names (2 `R_ARM_THM_CALL`, 6 `R_ARM_ABS32`). The 284-byte symbol equals the ROM span `[0x0813BDD0, 0x0813BEEC)`: SHA-256 `fc91ac0d9c28b8c90f0cfffb2fbd88e094bcd6f38af2d24c360ccc0dfb488ca7` for both. `.text` is exactly 284 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

None: every data symbol the source names is already in `config/data_symbols.json` on main.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0813BDD0.c`: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, `--signed-quotient-profile positive-constant-frame-v1`, `--unsigned-quotient-profile positive-constant-frame-v1` and `--function-address-profile canonical-thunks-v1` (4) | `unsupported stack-alias use or escape` |
| `--addressed-runtime-profile addressed-native-bios-fill-buffer-v1`, `--addressed-runtime-profile addressed-native-bios-fill-buffer-data-v1`, `--addressed-runtime-profile compiler-signed-runtime-data-v1` and 37 other addressed-runtime selectors (40) | `function address requires a canonical addressed function` |
| `named-data-buffer-v1`, `named-data-buffer-known-query-callee-v1`, `named-data-buffer-dead-argument-aliases-v1` and 56 other selectors (59) | `acyclic owner excludes arithmetic runtimes and indirect thunks` |
| `bounded-buffer-runtime-summaries-v1` and `bounded-buffer-bios-mixed-fast-fill-runtime-summaries-v1` (2) | `runtime summary owner requires exact canonical division entries and no thunks` |
| `named-data-buffer-finite-small-copy-binding-v1` | `one actual canonical small-copy call required` |
| `named-data-buffer-compiler-copy80-binding-v1` | `compiler copy requires exactly one memcpy call and named data only` |
| `bounded-buffer-bios-fill-source-v1`, `bounded-buffer-bios-fill-local-source-semantics-v1` and `bounded-buffer-bios-fill-overwritten-control-stores-v1` (3) | `verdict NOT VERIFIED - the selector was not run`, with the plausibility finding `allowlisted volatile semantic check: function-address evidence does not support runtime call thunks` |

The other 104 selector values are not listed one by one (none matched); by family: scheduler (25), private float and double (15), switch-layout (13), callback and closure (13), owner (8), canonical-integer (8), arithmetic-runtime (5), function-address (5), restoring-owner (4), bounded-buffer (4), addressed-runtime (2), control-flow (1), -O0 (1).

## Cause

The default run refuses the first local address stored to memory, the DMA3 source register write of the first
fill: `unsupported stack-alias use or escape`. As in `0x08135B40`, the transfer is immediate with a fixed source and
reads the stack halfword before the CPU continues. The buffer selectors refuse the `_call_via_r2` callback call
(`acyclic owner excludes arithmetic runtimes and indirect thunks`), and the BIOS fill selectors refuse it through the
allowlisted volatile semantic check (`verdict NOT VERIFIED - the selector was not run`, finding `function-address
evidence does not support runtime call thunks`).

The DMA issue reports `MATCH - byte identical` in a prototype with its DMA rule and the #192 comment's BIOS fill
call-site summary, both on the default path, and a refusal with either one alone.

## Source notes

From the attempt, not reviewed: each DMA fill is a nested block with a pointer local (`u16 *source = &zero;
*source = 0;`) and a `volatile` pointer to `data_040000D4` with a `plausible:` justification comment, the inline shape
of the SDK's `DmaFill16` (`0x08003410` has the same idiom). Whether the pointer local is the macro's shape
or steering is a review question.

kit issue: (to be filed - match.py: an immediate DMA fill whose fixed source is a local word is refused as a stack-alias escape); shubshub/fftadecomp-kit#192 (comment to be posted) (the CpuFastSet fill at the root call site)
