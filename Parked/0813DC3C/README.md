# 0x0813DC3C - window rectangle setter: a BIOS CpuSet copy into a local rectangle, clamped to the screen: bytes identical, refused (a stack rectangle as the CpuSet destination; with a BIOS summary, named data beside the buffer proof) (284 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321 with the match batches then queued for merge (PRs #200 onward). `void func_0813DC3C(source, channel)` copies a four-halfword rectangle (`x`, `y`, `width`, `height`, signed) into
a local with BIOS CpuSet in copy mode (`func_0814186C(source, &rect, 4)` at 0x0813DC4A), clamps it to the 240 x 160
screen (an off-screen rectangle becomes all zero), and writes window 0 or window 1 (`channel`) as left/right and
top/bottom bytes into `g_control_flags_03000940`. Its callers are `func_0813DB44` (0x0813DB84, 0x0813DC08) and
`func_0813EBC0` (0x0813EBF6).

```
0813DC3C  push {r4, r5, lr}
0813DC3E  sub  sp, #8
0813DC40  lsls r1, r1, #0x18
0813DC42  lsrs r5, r1, #0x18      @ channel
0813DC44  mov  r4, sp
0813DC46  mov  r1, sp             @ &rect
0813DC48  movs r2, #4
0813DC4A  bl   0x0814186C         @ CpuSet copy: source -> stack
```

## The index

`symbols/functions.txt` has `0813DC3C 0813DD58 284 142 return` and `config/functions.json` the same extent with 142 instructions (`thumb-prologue`). The CFG, closed by the kit's own `analyze.refine_function`, has 137 reachable instructions, so the instruction column is the halfword count (142). The selectors that compare it with the CFG are outside the families that fit this function: `restoring-owner-scalar-switch-v1`, `restoring-owner-switch-entry-word-v1`, `restoring-owner-switch-entry-two-words-data-v1` and 3 other selectors (6) give `complete-owner text reachable instruction count differs`; `conditional-finite-local-word-loops-v1` and `conditional-finite-spilled-scalar-loops-v1` (2) give `finite loop exact instruction counts differ`.

## Byte identity

`0813DC3C.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0813DC3C, with every callee bound to its ROM address and every data word to the address its symbol names (1 `R_ARM_THM_CALL`, 2 `R_ARM_ABS32`). The 284-byte symbol equals the ROM span `[0x0813DC3C, 0x0813DD58)`: SHA-256 `c6b54342708db133bd353037cdb4341b5e4e454964ff0de1ad27476cb01fd364` for both. `.text` is exactly 284 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

None: every data symbol the source names is already in `config/data_symbols.json` on main.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0813DC3C.c`: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, `--signed-quotient-profile positive-constant-frame-v1` and `--unsigned-quotient-profile positive-constant-frame-v1` (3) | `buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification` |
| `--addressed-runtime-profile addressed-native-bios-fill-buffer-data-v1`, `--addressed-runtime-profile addressed-native-bios-fill-scalar-control-numeric-mmio-code-image-data-v1`, `--addressed-runtime-profile addressed-native-bios-fill-scalar-control-code-image-data-v1` and 7 other addressed-runtime selectors (10) | `BIOS fill requires only a local R0 source and an external destination` |
| `--addressed-runtime-profile addressed-native-bios-fill-buffer-v1`, `--addressed-runtime-profile addressed-native-bios-fill-readonly-two-words-v1`, `--addressed-runtime-profile addressed-native-bios-ordinary-v1` and 10 other addressed-runtime selectors (13) | `addressed signed runtimes exclude data and irregular relocations` |
| `bounded-buffer-runtime-summaries-v1`, `named-data-buffer-v1`, `named-data-buffer-dead-argument-aliases-v1` and 20 other selectors (23) | `buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification` |
| `bounded-buffer-bios-mixed-fast-fill-runtime-summaries-v1`, `bounded-buffer-bios-fast-fill-source-v1` and `bounded-buffer-bios-mixed-fast-fill-source-v1` (3) | `CpuFastSet fill requires only its actual direct wrapper calls` |
| `named-data-buffer-finite-small-copy-binding-v1` | `one actual canonical small-copy call required` |
| `named-data-buffer-compiler-copy80-binding-v1` | `compiler copy requires exactly one memcpy call and named data only` |
| `named-data-buffer-known-query-callee-v1`, `descriptor-output-alias-v1`, `descriptor-single-store-v1` and 3 other descriptor and preservation selectors (6) | `buffer callee 0x0814186C: structural inventory is not closed` |
| `bounded-buffer-bios-sqrt-scratch-v1` | `BIOS Sqrt requires exact complete svc #8; bx lr wrapper` |
| `bounded-buffer-bios-fill-source-v1`, `bounded-buffer-bios-fill-local-source-semantics-v1` and `bounded-buffer-bios-fill-overwritten-control-stores-v1` (3) | `verdict NOT VERIFIED - the selector was not run`, with the plausibility finding `allowlisted volatile semantic check: BIOS fill requires only a local R0 source and an external destination` |
| `bounded-buffer-bios-bg-affine-set-v1`, `bounded-buffer-bios-bg-affine-set-transparent-leaf-scratch-v1` and `bounded-buffer-bios-bg-affine-set-discarded-scratch-v1` (3) | `BgAffineSet requires an actual direct call in its closed owner` |
| `bounded-buffer-bios-mixed-cpuset-fast-fill-source-v1` | `mixed CpuSet/CpuFastSet fill requires actual calls to both wrappers` |
| `bios-word-switch-local-buffers-v1` | `BIOS buffer requires one exact one-object-word switch without local BL` |

The other 145 selector values are not listed one by one (none matched); by family: scheduler (25), addressed-runtime (19), callback and closure (19), private float and double (15), switch-layout (13), owner (12), restoring-owner (9), canonical-integer (8), function-address (6), bounded-buffer (6), arithmetic-runtime (5), descriptor and preservation (5), control-flow (1), -O0 (1), guarded-switch buffer (1).

## Cause

CpuSet here copies into the local rectangle, the reverse of a fill. The default run walks `&rect` into the CpuSet
wrapper and stops there: `buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification`.
Every BIOS selector that summarises CpuSet assumes a fill with a local source and an external destination and refuses
the copy: `BIOS fill requires only a local R0 source and an external destination` (ten addressed BIOS runtimes
directly, the three BIOS fill selectors through the allowlisted volatile semantic check, as `verdict NOT VERIFIED -
the selector was not run`).

The #192 comment's buffer-walk summary covers a memory wrapper whose destination is local; with it, the default path
meets its data gate (`buffer-call evidence does not support data relocations`, `tools/match.py:6043-6044`) because the
function writes the named `g_control_flags_03000940`, so it also needs named data beside the buffer proof. The
named-data issue reports `MATCH - byte identical` with both.

kit issue: shubshub/fftadecomp-kit#236 (part a); shubshub/fftadecomp-kit#192 (comment)
