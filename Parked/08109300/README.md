# 0x08109300 - screen-shake effect callback with a child-task loop: bytes identical, refused (a local address stored to an outgoing argument word on the function-literal path; every selector stops at the volatile check bound) (868 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321 with the match batches then queued for merge (PRs #200 onward). `u32 func_08109300(task, descriptor, payload)` is a phase callback (switch on `descriptor->phase`: 0, 1, 0x100 to
0x108) registered by its function word at 0x08395050 in the ROM callback table. Phase 0 starts a loader
(`func_080E03F8(object, data_083A12E4, ...)`) and counts the group (`func_080DD494`); 0x100 starts a screen effect
(`func_080D7220`, `func_080D3E9C(data_0894DCD8)`, `func_080DFD8C`) and pans to the focus (`func_0801E6F0(&x, &y)`,
`func_0801BB0C`); 0x102 runs a `u8` loop over the group members (`func_080DE268`), opens a screen buffer
(`func_080D9A24`, `func_080D9BA8`), reads a position into three locals with `func_080DBDEC(0, 0, &x, &y, &z)` (the third
pointer in the outgoing word) and starts a transition; 0x103 and 0x107 step the transition and copy 0xA0 halfwords
from `data_083A1314` with BIOS CpuSet (`func_0814186C`); 0x104 and 0x105 loop over the members, each time creating a
child with a 28-byte stack descriptor, `func_08005B6C(func_08109214, 0x20, &child, task)` at 0x08109596; 0x106 to 0x108
wait and clean up.

## The index

`symbols/functions.txt` has `08109300 08109664 868 434 return` and `config/functions.json` the same extent with 434 instructions (`thumb-prologue`). The CFG, closed by the kit's own `analyze.refine_function`, has 367 reachable instructions, so the instruction column is the halfword count (434). No refusal below depends on it.

## Byte identity

`08109300.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08109300, with every callee bound to its ROM address and every data word to the address its symbol names (38 `R_ARM_THM_CALL`, 9 `R_ARM_ABS32`). The 868-byte symbol equals the ROM span `[0x08109300, 0x08109664)`: SHA-256 `99c9e3860c04043fa74c14db5dffde659b19bac728366abf3da2558a983f9fd5` for both. `.text` is exactly 868 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each is added with its address as the value (`"data_083A12E4": "0x083A12E4"`):

`data_083A12E4`, `data_083A1314`, `data_083A1700`, `data_088F63D8`, `data_0894DCCC`, `data_0894DCD8`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08109300.c` and the data symbols above added: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, `--signed-quotient-profile positive-constant-frame-v1` and `--unsigned-quotient-profile positive-constant-frame-v1` (3) | `unsupported stack-alias use or escape` |
| `--addressed-runtime-profile addressed-native-bios-fill-buffer-v1`, `--addressed-runtime-profile addressed-native-bios-fill-buffer-data-v1`, `conditional-scheduler-projected-outputs-v1` and 186 other selectors (189) | `verdict NOT VERIFIED - the selector was not run`, with the plausibility finding `allowlisted volatile semantic check: real compile of func_08109300: more than 32 unknown branch conditions on one path (loops with unknown exit conditions are not modelled)` |
| `bounded-buffer-bios-fill-source-v1`, `bounded-buffer-bios-fill-local-source-semantics-v1` and `bounded-buffer-bios-fill-overwritten-control-stores-v1` (3) | `verdict NOT VERIFIED - the selector was not run`, with the plausibility finding `allowlisted volatile semantic check: buffer callee 0x080DBDEC: buffer callee 0x0800A668: buffer callee 0x08007170: buffer callee 0x08006FCC: buffer callee 0x08006E28: buffer callee 0x08006C88: named-data buffer dependency budget exceeded` |

The other 19 selector values are not listed one by one (none matched); by family: switch-layout (10), function-address (6), arithmetic-runtime (2), control-flow (1).

## Cause

Two layers:

- **Default path.** The callback word `func_08109214` (0x081095B8) and the named data put the default run on the
  function-literal path without a buffer proof, and it refuses at the first local address stored to memory, `&z` (`sp+0x10`, kept in `r10`) written to the
  outgoing word of `func_080DBDEC` at 0x081094B4: `unsupported stack-alias use or escape`.
- **Every selector.** 189 of the 213 selector values stop before their profile at the allowlisted volatile semantic
  check of `plausible.py`, which this source reaches through `control_flags.h`: `more than 32 unknown branch
  conditions on one path (loops with unknown exit conditions are not modelled)` (kit #137's bound). The verdict is
  `NOT VERIFIED - the selector was not run`. The three BIOS-fill selectors stop at the same check with a dependency
  budget instead.

The #192 comment lists the function among the scalar-wrapper calls reached in walked callees: `func_080DBDEC` calls
the BIOS Div wrapper `func_08141870`. That rule was not measured together with the others here, so the refusal after
the volatile bound is not known.

## Source notes

From the attempt, not reviewed: phase 0x104 falls through into 0x105 (the ROM's 0x104 block continues
into 0x105's); the block-scoped `x`, `y` and `z` of phases 0x100 and 0x102 differ in type (`u16` for `func_0801E6F0`,
`s16` for `func_080DBDEC`).

kit issue: shubshub/fftadecomp-kit#137 (comment); shubshub/fftadecomp-kit#192 (comment) (a Div wrapper in a walked callee)
