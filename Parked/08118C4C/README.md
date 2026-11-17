# 0x08118C4C - scene setup callback: two BIOS CpuSet clears from stack halfwords, then a script call: bytes identical, refused (BIOS CpuSet fills from stack halfwords; with the fill summarised, the jump table of 0x080E03F8) (212 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321 with the match batches then queued for merge (PRs #200 onward). `u32 func_08118C4C(task, descriptor, payload)` is a phase callback (switch on `descriptor->phase`: 0, 1, 0x100,
0x101) of the scene task `func_08118D20`, whose pool holds its function word (0x08118DFC). Phase 0 clears two palette
ranges with BIOS CpuSet in fill mode from a zero halfword on the stack, `func_0814186C(&fill, data_03003920,
0x01000040)` and `func_0814186C(&fill2, data_03003920 + 0x200, 0x01000070)`, and starts the script
`func_080E03F8(object, data_083A6208, 4, 6, &position, task)`, whose fifth argument, the address of a local word holding a
packed position, is passed in the outgoing word (`add r2, sp, #0xc; str r2, [sp]`). Phase 0x100 starts `func_080E5694(task)` and a 0x41-frame timer once the script is done; 0x101 calls `func_080DBED4(0, 1, 0, 0)` when the timer expires and waits for the task (`func_080E051C`). The siblings
`0x08118A08`, `0x08118AC0` and `0x08118B94` have the same shape with other constants.

## The index

`symbols/functions.txt` has `08118C4C 08118D20 212 106 return` and `config/functions.json` the same extent with 106 instructions (`thumb-prologue`). The CFG, closed by the kit's own `analyze.refine_function`, has 88 reachable instructions, so the instruction column is the halfword count (106). The selectors that compare it with the CFG are outside the families that fit this function: `restoring-owner-scalar-switch-v1`, `restoring-owner-switch-entry-word-v1`, `restoring-owner-switch-entry-two-words-data-v1` and 3 other selectors (6) give `complete-owner text reachable instruction count differs`; `conditional-finite-local-word-loops-v1` and `conditional-finite-spilled-scalar-loops-v1` (2) give `finite loop exact instruction counts differ`.

## Byte identity

`08118C4C.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08118C4C, with every callee bound to its ROM address and every data word to the address its symbol names (7 `R_ARM_THM_CALL`, 2 `R_ARM_ABS32`). The 212-byte symbol equals the ROM span `[0x08118C4C, 0x08118D20)`: SHA-256 `0908854eb0be864cd2121ffc1c1a9ed77d6ff07afe4c9ec41cbca270e1aefb14` for both. `.text` is exactly 212 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each is added with its address as the value (`"data_083A6208": "0x083A6208"`):

`data_083A6208`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08118C4C.c` and the data symbols above added: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, `--signed-quotient-profile positive-constant-frame-v1` and `--unsigned-quotient-profile positive-constant-frame-v1` (3) | `buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification` |
| `--addressed-runtime-profile addressed-native-bios-fill-buffer-data-v1`, `--addressed-runtime-profile addressed-native-bios-fill-scalar-control-numeric-mmio-code-image-data-v1`, `--addressed-runtime-profile addressed-native-bios-fill-scalar-control-code-image-data-v1` and 7 other addressed-runtime selectors (10) | `unsupported stack-alias use or escape` |
| `--addressed-runtime-profile addressed-native-bios-fill-buffer-v1`, `--addressed-runtime-profile addressed-native-bios-fill-readonly-two-words-v1`, `--addressed-runtime-profile addressed-native-bios-ordinary-v1` and 10 other addressed-runtime selectors (13) | `addressed signed runtimes exclude data and irregular relocations` |
| `bounded-buffer-runtime-summaries-v1`, `named-data-buffer-v1`, `named-data-buffer-dead-argument-aliases-v1` and 20 other selectors (23) | `buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification` |
| `bounded-buffer-bios-mixed-fast-fill-runtime-summaries-v1`, `bounded-buffer-bios-fast-fill-source-v1` and `bounded-buffer-bios-mixed-fast-fill-source-v1` (3) | `CpuFastSet fill requires only its actual direct wrapper calls` |
| `named-data-buffer-finite-small-copy-binding-v1` | `one actual canonical small-copy call required` |
| `named-data-buffer-compiler-copy80-binding-v1` | `compiler copy requires exactly one memcpy call and named data only` |
| `named-data-buffer-known-query-callee-v1`, `descriptor-output-alias-v1`, `descriptor-single-store-v1` and 7 other selectors (10) | `buffer callee 0x0814186C: structural inventory is not closed` |
| `bounded-buffer-bios-sqrt-scratch-v1` | `BIOS Sqrt requires exact complete svc #8; bx lr wrapper` |
| `bounded-buffer-bios-fill-source-v1`, `bounded-buffer-bios-fill-local-source-semantics-v1` and `bounded-buffer-bios-fill-overwritten-control-stores-v1` (3) | `buffer callee 0x080E03F8: unresolved program-counter write` |
| `bounded-buffer-bios-bg-affine-set-v1`, `bounded-buffer-bios-bg-affine-set-transparent-leaf-scratch-v1` and `bounded-buffer-bios-bg-affine-set-discarded-scratch-v1` (3) | `BgAffineSet requires an actual direct call in its closed owner` |
| `bounded-buffer-bios-mixed-cpuset-fast-fill-source-v1` | `mixed CpuSet/CpuFastSet fill requires actual calls to both wrappers` |
| `bounded-buffer-root-guarded-switch-v1` | `root buffer requires one exact guarded switch and ordinary calls` |
| `bios-word-switch-local-buffers-v1` | `BIOS buffer requires one exact one-object-word switch without local BL` |

The other 140 selector values are not listed one by one (none matched); by family: scheduler (25), addressed-runtime (19), callback and closure (19), private float and double (15), switch-layout (13), owner (12), restoring-owner (9), canonical-integer (8), function-address (6), arithmetic-runtime (5), bounded-buffer (5), descriptor and preservation (2), control-flow (1), -O0 (1).

## Cause

The default run walks the fill source into the BIOS CpuSet wrapper `func_0814186C` and stops there:
`buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification`. The BIOS fill selectors
summarise the fills and then walk `&position` into `func_080E03F8`, which dispatches through a jump table, and stop
at the dispatch: `buffer callee 0x080E03F8: unresolved program-counter write`. The #192 comment and the switch-callee
issue report the next refusal once both are summarised: `buffer callee 0x080E03F8: unsupported stack-alias use or
escape`, a stack alias inside the callee, which neither rule covers.

kit issue: shubshub/fftadecomp-kit#192 (comment) (the four callers of 080E03F8); shubshub/fftadecomp-kit#241 (with the BIOS summaries, past the table of 080E03F8)
