# 0x08113918 - window reveal callback: a scheduler call, BIOS Div and CpuSet calls, and object loops: bytes identical, refused (local aliases across calls on the function-literal path; every selector stops at the volatile check path bound) (848 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321 with the match batches then queued for merge (PRs #200 onward). `u32 func_08113918(task, descriptor, payload)` is a phase callback (switch on `descriptor->phase`: 0, 1, 0x100 to
0x103) of the task `func_08113CE0`, whose pool holds its function word (0x08113EFC). Phase 0x100 hides the handle object
and starts an effect and a window record (`func_080D3E9C(data_0894DC0C)`, `func_080DFD8C(data_083A37D8, ...)`); 0x101,
after a 40-frame wait, sets up a BG and window 0 in `g_control_flags_03000940`, starts a child with an uninitialised
28-byte stack descriptor (`func_08005B6C(func_081137BC, 0x5C, desc, task)` at 0x08113A40), reads a local bounds record
(`func_0801CAE0(&bounds)`) and computes a limit with two BIOS Div calls (`func_08141870`, 0x08113A5C and 0x08113A66);
0x102 and 0x103 loop over 17 object slots (`func_0800C148`, `func_0800C224`), create one object every 5 frames from the
header at `data_088F1310` (`func_0800B394`, `func_0800BEDC`, `func_0800BED8`, `func_0800BF04`) and finally clear 16
palette halfwords at `0x03003920` with BIOS CpuSet from a stack halfword (`func_0814186C(&clear, data_03003920,
0x01000010)` at 0x08113C2A) and start `func_080D7220(data_088F5F08, ...)`.

## The index

`symbols/functions.txt` has `08113918 08113C68 848 370 return` and `config/functions.json` the same extent with 370 instructions (`thumb-prologue`). The CFG, closed by the kit's own `analyze.refine_function`, has 370 reachable instructions, so the row is right.

## Byte identity

`08113918.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08113918, with every callee bound to its ROM address and every data word to the address its symbol names (31 `R_ARM_THM_CALL`, 9 `R_ARM_ABS32`). The 848-byte symbol equals the ROM span `[0x08113918, 0x08113C68)`: SHA-256 `b2c4f9365cdc414377f09b7684de512202d5bd82e3c7a63500121f31420628be` for both. `.text` is exactly 848 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each is added with its address as the value (`"data_083A37D8": "0x083A37D8"`):

`data_083A37D8`, `data_088F1310`, `data_088F5F08`, `data_0894DC0C`.

`data_088F5F08` is in the pending batches' `config/data_symbols.json` but not on main, so it is listed here.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08113918.c` and the data symbols above added: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, `--signed-quotient-profile positive-constant-frame-v1` and `--unsigned-quotient-profile positive-constant-frame-v1` (3) | `stack aliases cannot cross calls in caller-clobbered registers` |
| `--addressed-runtime-profile addressed-native-bios-fill-buffer-v1`, `--addressed-runtime-profile addressed-native-bios-fill-buffer-data-v1`, `conditional-scheduler-projected-outputs-v1` and 186 other selectors (189) | `verdict NOT VERIFIED - the selector was not run`, with the plausibility finding `allowlisted volatile semantic check: func_08113918 has more than 1024 paths; the semantic check is bounded` |
| `bounded-buffer-bios-fill-source-v1`, `bounded-buffer-bios-fill-local-source-semantics-v1` and `bounded-buffer-bios-fill-overwritten-control-stores-v1` (3) | `verdict NOT VERIFIED - the selector was not run`, with the plausibility finding `allowlisted volatile semantic check: buffer callee 0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification` |

The other 19 selector values are not listed one by one (none matched); by family: switch-layout (10), function-address (6), arithmetic-runtime (2), control-flow (1).

## Cause

The callback word `func_081137BC` and the named data put the default run on the function-literal path, which
has no buffer proof: `stack aliases cannot cross calls in caller-clobbered registers`. Every selector stops earlier, at
the allowlisted volatile semantic check of `plausible.py`, which the source reaches through `control_flags.h`:
`func_08113918 has more than 1024 paths; the semantic check is bounded` (189 of the 213 values, verdict `NOT VERIFIED -
the selector was not run`); the three BIOS fill selectors report the scheduler's callback thunk through the same check.

The function needs three rules before that bound is its last refusal: the scheduler descriptor contract at its one
site (the scheduler call-site issue), the BIOS fill summary at the root call site for the CpuSet clear (the #192
comment), and the plain version-2 buffer proof at its crossing calls on the function-literal path (the named-data
issue, part b). With all three prototyped, the #137 comment reports it byte-identical under the kit and refused by the
path bound.

## Source notes

From the attempt, not reviewed: phase 1 is an empty `break`; `flags` is `s16`; `body`, `low` and
`object` are separate locals of phase 0x102; the result of the first Div call is discarded, as the ROM discards it.

kit issue: shubshub/fftadecomp-kit#237 (then #137's path bound); shubshub/fftadecomp-kit#236 (part b: the plain v2 proof at its crossing calls); shubshub/fftadecomp-kit#192 (comment) (the fill summary at root call sites); shubshub/fftadecomp-kit#137 (comment)
