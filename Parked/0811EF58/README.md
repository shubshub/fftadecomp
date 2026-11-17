# 0x0811EF58 - window sweep callback spawning children from a frame table: bytes identical, refused (local aliases across calls on the function-literal path; every selector stops at the volatile check bound) (820 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321 with the match batches then queued for merge (PRs #200 onward). `u32 func_0811EF58(owner, request, state)` is a phase callback of the task `func_08120724`, whose pool holds its
function word (0x081207E0). It returns at once while bit 15 of `state->flags` is set; otherwise it switches on
`request->phase` (0, 1, 0x100 to 0x103). Phase 0 starts an animation (`func_080D7A70(data_083A7394, 3, owner)`); 0x100
waits for it and sets the flag bits; 0x101 sets up a BG object (`func_080D49FC`, `func_0800BD24`,
`func_080D4B64(1, data_088F3A38, 0x2F5, 6)`), a sound and an effect (`func_080D4704(data_0894CF90)`,
`func_080D3E9C(data_0894DED0)`), two 0x177-frame interpolations and window 0 in `g_control_flags_03000940`; 0x102
steps the interpolations, moves the window and the BG object (`func_0800BC08`), walks the frame table `data_083A7504`
from `first_index` up to entry 0x15 and, on a matching frame, starts a child with a 28-byte stack descriptor
(`func_08005B6C(func_0811ED40, 0x2C, &d, owner)` at 0x0811F0D0), and every eighth frame starts another
(`func_08005B6C(func_0811EE48, 0x2C, &d, owner)` at 0x0811F19A), each into an 8-slot array; 0x103 waits for everything
and restores the display.

## The index

`symbols/functions.txt` has `0811EF58 0811F28C 820 346 return` and `config/functions.json` the same extent with 346 instructions (`thumb-prologue`). The CFG, closed by the kit's own `analyze.refine_function`, has 346 reachable instructions, so the row is right.

## Byte identity

`0811EF58.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0811EF58, with every callee bound to its ROM address and every data word to the address its symbol names (30 `R_ARM_THM_CALL`, 11 `R_ARM_ABS32`). The 820-byte symbol equals the ROM span `[0x0811EF58, 0x0811F28C)`: SHA-256 `12a0792d9109595c45128b51650d316bc5ce1dd0794ab738ae867d8cef49c3a2` for both. `.text` is exactly 820 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each is added with its address as the value (`"data_083A7394": "0x083A7394"`):

`data_083A7394`, `data_083A7504`, `data_088F3A38`, `data_0894CF90`, `data_0894CFBC`, `data_0894DED0`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0811EF58.c` and the data symbols above added: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, `--signed-quotient-profile positive-constant-frame-v1` and `--unsigned-quotient-profile positive-constant-frame-v1` (3) | `stack aliases cannot cross calls in caller-clobbered registers` |
| `conditional-scheduler-projected-outputs-v1`, `conditional-scheduler-descriptor-calls-v1`, `conditional-scheduler-branch-descriptor-calls-v1` and 186 other selectors (189) | `verdict NOT VERIFIED - the selector was not run`, with the plausibility finding `allowlisted volatile semantic check: real compile of func_0811EF58: more than 32 unknown branch conditions on one path (loops with unknown exit conditions are not modelled)` |

The other 22 selector values are not listed one by one (none matched); by family: switch-layout (10), function-address (6), BIOS buffer (3), arithmetic-runtime (2), control-flow (1).

## Cause

The callback words (`func_0811ED40`, `func_0811EE48`) and the named data put the default run on the
function-literal path, which has no buffer proof: `stack aliases cannot cross calls in caller-clobbered registers`. Every selector stops earlier, at the allowlisted volatile semantic check of
`plausible.py`, which the source reaches through `control_flags.h`: `more than 32 unknown branch conditions on one path
(loops with unknown exit conditions are not modelled)`, verdict `NOT VERIFIED - the selector was not run` (189 of the
213 values; the rest stop on their own requirements).

The scheduler call-site issue reports that its per-site rule makes the function byte-identical under the kit and that
it is then refused by this same bound; the #137 comment lists it among the functions for which the bound is the last
refusal.

## Source notes

From the attempt, not reviewed: `slot` and `next_slot` are separate `u8` locals for the two slot
indices (`i & 7` and `second_index & 7`); the window and BG fields are written through `control_flags.h`, whose
volatile fields give the ROM's dead `ldrb` before each `strb` (0x0811F11C, 0x0811F124).

kit issue: (to be filed - match.py: a scheduler call with a local descriptor verifies only under shape-bound owner selectors; a per-site summary admits 7 byte-identical functions alone and 14 with companion rules) (byte-identical under the prototype, then #137); shubshub/fftadecomp-kit#137 (comment to be posted)
