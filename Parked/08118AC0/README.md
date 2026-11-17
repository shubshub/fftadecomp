# 0x08118AC0 - scene setup callback: two BIOS CpuSet clears from stack halfwords, then a script call: bytes identical, refused (BIOS CpuSet fills from stack halfwords; with the fill summarised, the jump table of 0x080E03F8) (210 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321 with the match batches then queued for merge (PRs #200 onward). `u32 func_08118AC0(task, descriptor, payload)` is a phase callback (switch on `descriptor->phase`: 0, 1, 0x100,
0x101) of the scene task `func_08118D20`, whose pool holds its function word (0x08118F10). Phase 0 clears two palette
ranges with BIOS CpuSet in fill mode from a zero halfword on the stack, `func_0814186C(&fill, data_03003920,
0x01000040)` and `func_0814186C(&fill2, data_03003920 + 0x200, 0x01000070)`, and starts the script
`func_080E03F8(object, data_083A616C, 5, 6, &position, task)`, whose fifth argument, the address of a local word holding a
packed position, is passed in the outgoing word (`add r2, sp, #0xc; str r2, [sp]`). Phase 0x100 starts `func_080F2E40(3, object, task)` and an overlay (`func_080D4704(data_0894AB00, task)`) once the script is done; 0x101 waits for both (`func_080D4774`, `func_080F1210`). The siblings
`0x08118A08`, `0x08118B94` and `0x08118C4C` have the same shape with other constants.

## The index

`symbols/functions.txt` has `08118AC0 08118B92 210 105 return` and `config/functions.json` the same extent with 105 instructions (`thumb-prologue`). The CFG, closed by the kit's own `analyze.refine_function`, has 84 reachable instructions, so the instruction column is the halfword count (105). The selectors that compare it with the CFG are outside the families that fit this function: `restoring-owner-switch-aligned-v1` and `restoring-owner-switch-cycles-function-words-v1` (2) give `complete-owner text reachable instruction count differs`; `conditional-finite-local-word-loops-v1` and `conditional-finite-spilled-scalar-loops-v1` (2) give `finite loop exact instruction counts differ`.

## Byte identity

`08118AC0.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08118AC0, with every callee bound to its ROM address and every data word to the address its symbol names (8 `R_ARM_THM_CALL`, 3 `R_ARM_ABS32`). The 210-byte symbol equals the ROM span `[0x08118AC0, 0x08118B92)`: SHA-256 `fc61eb9ad6fba9d1e97012a9739eabcea2effe40f0e1dfb7bbb09a6c755a5fdd` for both. `.text` is 212 bytes: the symbol and the assembler's `c0 46` alignment halfword. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each is added with its address as the value (`"data_083A616C": "0x083A616C"`):

`data_083A616C`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08118AC0.c` and the data symbols above added: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, `--signed-quotient-profile positive-constant-frame-v1` and `--unsigned-quotient-profile positive-constant-frame-v1` (3) | `buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification` |
| `--addressed-runtime-profile addressed-native-bios-fill-buffer-data-v1`, `--addressed-runtime-profile addressed-native-bios-fill-scalar-control-numeric-mmio-code-image-data-v1`, `--addressed-runtime-profile addressed-native-bios-fill-scalar-control-code-image-data-v1` and 7 other addressed-runtime selectors (10) | `unsupported stack-alias use or escape` |
| `--addressed-runtime-profile addressed-native-bios-fill-buffer-v1`, `--addressed-runtime-profile addressed-native-bios-fill-readonly-two-words-v1`, `--addressed-runtime-profile addressed-native-bios-ordinary-v1` and 10 other addressed-runtime selectors (13) | `addressed signed runtimes exclude data and irregular relocations` |
| `bounded-buffer-runtime-summaries-v1`, `named-data-buffer-v1`, `named-data-buffer-dead-argument-aliases-v1` and 15 other selectors (18) | `buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification` |
| `bounded-buffer-bios-mixed-fast-fill-runtime-summaries-v1`, `bounded-buffer-bios-fast-fill-source-v1` and `bounded-buffer-bios-mixed-fast-fill-source-v1` (3) | `CpuFastSet fill requires only its actual direct wrapper calls` |
| `named-data-buffer-finite-small-copy-binding-v1` | `one actual canonical small-copy call required` |
| `named-data-buffer-compiler-copy80-binding-v1` | `compiler copy requires exactly one memcpy call and named data only` |
| `named-data-buffer-known-query-callee-v1` | `buffer callee 0x0814186C: structural inventory is not closed` |
| `bounded-buffer-bios-sqrt-scratch-v1` | `BIOS Sqrt requires exact complete svc #8; bx lr wrapper` |
| `bounded-buffer-bios-fill-source-v1`, `bounded-buffer-bios-fill-local-source-semantics-v1` and `bounded-buffer-bios-fill-overwritten-control-stores-v1` (3) | `buffer callee 0x080E03F8: unresolved program-counter write` |
| `bounded-buffer-bios-bg-affine-set-v1`, `bounded-buffer-bios-bg-affine-set-transparent-leaf-scratch-v1` and `bounded-buffer-bios-bg-affine-set-discarded-scratch-v1` (3) | `BgAffineSet requires an actual direct call in its closed owner` |
| `bounded-buffer-bios-mixed-cpuset-fast-fill-source-v1` | `mixed CpuSet/CpuFastSet fill requires actual calls to both wrappers` |
| `bounded-buffer-root-guarded-switch-v1` | `root buffer requires one exact guarded switch and ordinary calls` |
| `bios-word-switch-local-buffers-v1` | `BIOS buffer requires one exact one-object-word switch without local BL` |

The other 154 selector values are not listed one by one (none matched); by family: scheduler (25), callback and closure (22), addressed-runtime (19), private float and double (15), switch-layout (13), owner (12), descriptor and preservation (12), restoring-owner (9), canonical-integer (8), function-address (6), bounded-buffer (6), arithmetic-runtime (5), control-flow (1), -O0 (1).

## Cause

The default run walks the fill source into the BIOS CpuSet wrapper `func_0814186C` and stops there:
`buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification`. The BIOS fill selectors
summarise the fills and then walk `&position` into `func_080E03F8`, which dispatches through a jump table, and stop
at the dispatch: `buffer callee 0x080E03F8: unresolved program-counter write`. The #192 comment and the switch-callee
issue report the next refusal once both are summarised: `buffer callee 0x080E03F8: unsupported stack-alias use or
escape`, a stack alias inside the callee, which neither rule covers.

kit issue: shubshub/fftadecomp-kit#192 (comment) (the four callers of 080E03F8); shubshub/fftadecomp-kit#241 (with the BIOS summaries, past the table of 080E03F8)
