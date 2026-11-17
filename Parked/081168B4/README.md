# 0x081168B4 - group effect callback with one scheduler call and a member loop: bytes identical, refused (local aliases across calls on the function-literal path; every selector stops at the volatile check bound) (570 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321 with the match batches then queued for merge (PRs #200 onward). `u32 func_081168B4(task, command, state)` is a phase callback (switch on `command->phase`: 0, 1, 0x100 to 0x105)
registered by its function word at 0x083951A0 in the ROM callback table. Phase 0 starts a loader
(`func_080E03F8(value, data_083A3E34, mode, 7, 0, task)`), counts the group (`func_080DD494`) and runs a `u8` loop over the
members (`func_080DE268(func_080DD4B4(value, i))`); 0x100 starts the screen effects (`func_080D7220(data_088F63D8, ...)`,
`func_080D3E9C(data_0894DCE4)`, `func_080D4704(data_0894C474)`, `func_080DFD8C(data_083A4C78, ...)`); 0x101 starts the
child task with an uninitialised 28-byte stack descriptor, `func_08005B6C(func_08116514, 0x16C, &descriptor, task)` at
0x081169E4; 0x102 waits for the effects and the child and clears a display bit (`func_080035A8(2)`); 0x103 and 0x104
(0x103 falls through) go over the members once each, `func_080DCFE4(member, data_083A4C64, ...)` into a 4-slot effect
array; 0x105 waits for the effects.

```
081169DA  ldr  r0, =func_08116514
081169DC  movs r1, #0xb6
081169DE  lsls r1, r1, #1         @ 0x16C
081169E0  add  r2, sp, #0xc       @ descriptor
081169E2  adds r3, r7, #0         @ task
081169E4  bl   0x08005B6C
```

## The index

`symbols/functions.txt` has `081168B4 08116AEE 570 285 return` and `config/functions.json` the same extent with 285 instructions (`thumb-prologue`). The CFG, closed by the kit's own `analyze.refine_function`, has 240 reachable instructions, so the instruction column is the halfword count (285). No refusal below depends on it.

## Byte identity

`081168B4.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x081168B4, with every callee bound to its ROM address and every data word to the address its symbol names (22 `R_ARM_THM_CALL`, 8 `R_ARM_ABS32`). The 570-byte symbol equals the ROM span `[0x081168B4, 0x08116AEE)`: SHA-256 `1548a42181aaa60d9236b043ef9a43a8fe9628eadbab7f80bac27ec3d3430b75` for both. `.text` is 572 bytes: the symbol and the assembler's `c0 46` alignment halfword. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each is added with its address as the value (`"data_083A3E34": "0x083A3E34"`):

`data_083A3E34`, `data_083A4C64`, `data_083A4C78`, `data_088F63D8`, `data_0894C474`, `data_0894DCE4`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/081168B4.c` and the data symbols above added: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, `--signed-quotient-profile positive-constant-frame-v1` and `--unsigned-quotient-profile positive-constant-frame-v1` (3) | `stack aliases cannot cross calls in caller-clobbered registers` |
| `conditional-scheduler-projected-outputs-v1`, `conditional-scheduler-descriptor-calls-v1`, `conditional-scheduler-branch-descriptor-calls-v1` and 186 other selectors (189) | `verdict NOT VERIFIED - the selector was not run`, with the plausibility finding `allowlisted volatile semantic check: real compile of func_081168B4: more than 32 unknown branch conditions on one path (loops with unknown exit conditions are not modelled)` |

The other 22 selector values are not listed one by one (none matched); by family: switch-layout (10), function-address (6), BIOS buffer (3), arithmetic-runtime (2), control-flow (1).

## Cause

The callback word `func_08116514` and the named data put the default run on the function-literal path,
which has no buffer proof: `stack aliases cannot cross calls in caller-clobbered registers`. Every selector stops earlier, at the allowlisted volatile semantic check of
`plausible.py`, which this source reaches through `control_flags.h`: `more than 32 unknown branch conditions on one
path (loops with unknown exit conditions are not modelled)`, verdict `NOT VERIFIED - the selector was not run`.

The scheduler call-site issue's prototype (the descriptor contract as a per-site summary) makes the function byte-identical
under the kit and then refused by that same bound, which is why the #137 comment lists it: with the scheduler summary,
#137's bound is the last refusal.

## Source notes

From the attempt, not reviewed: the source uses `control_flags.h`; with its own `extern u16`
declaration (as many sources on main) the volatile check would not run, and the scheduler selectors were reported to
refuse the shape instead (`predicate composition excludes CFG cycles`, the member loop; the `u16` counted-loop selector
needs a `+1` `u16` counter). Phase 0x103 falls through into 0x104, as the ROM's blocks do.

kit issue: (to be filed - match.py: a scheduler call with a local descriptor verifies only under shape-bound owner selectors; a per-site summary admits 7 byte-identical functions alone and 14 with companion rules) (byte-identical under the prototype, then #137); shubshub/fftadecomp-kit#137 (comment to be posted)
