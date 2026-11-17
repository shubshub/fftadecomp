# 0x08109B64 - target effect callback with a stack copy of a four-entry offset table: bytes identical, refused (the forwarding wrapper func_080DBDC8 on the default path; under named-data-buffer-stack-index-v2 only an unproven premise row) (860 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321 with the match batches then queued for merge (PRs #200 onward). `u32 func_08109B64(task, descriptor, payload)` is a phase callback (switch on `descriptor->phase`: 0, 1, 0x100 to
0x105) registered by its function word at 0x08395068 in the ROM callback table. Phase 0 starts a loader
(`func_080E03F8(actor, data_083A1920, ...)`); 0x100 checks `func_080D3B54` and starts the output task
`func_080DDF68(actor, &payload->output, mode, 1, &payload->ready, data_083A19AC, ...)`; 0x101 copies the 16-byte ROM
table `data_08149EE4` to the stack (a structure assignment, `ldm`/`stm` through the pool word at 0x08109C88), reads the
output object's facing (`func_080DBC88` at 0x08109C8E) and position (`func_080DBDC8(output, &x, &y)` at 0x08109CA4, with
two local `u16` outputs) and starts an animation at the position plus `table.entry[facing]` (`func_080D6098`); 0x102
to 0x105 run two more animations and an object task and toggle display bits through `func_080035A8(2)`.

```
08109C8E  bl   0x080DBC88        @ facing
08109C92  adds r4, r0, #0
08109C94  lsls r4, r4, #0x18
08109C96  lsrs r4, r4, #0x18
08109C9A  add  r5, sp, #0x24     @ &x
08109C9C  mov  r6, sp
08109C9E  adds r6, #0x26         @ &y
08109CA4  bl   0x080DBDC8
08109CA8  lsls r4, r4, #2
08109CAA  mov  r1, sp
08109CAC  adds r1, r1, r4
08109CAE  adds r1, #0x14
08109CB0  ldrh r0, [r1]          @ table.entry[facing].x
08109CBA  ldrh r1, [r1, #2]      @ table.entry[facing].y
```

## The index

`symbols/functions.txt` has `08109B64 08109EC0 860 430 return` and `config/functions.json` the same extent with 430 instructions (`thumb-prologue`). The CFG, closed by the kit's own `analyze.refine_function`, has 358 reachable instructions, so the instruction column is the halfword count (430). The selectors that compare it with the CFG are outside the families that fit this function: `restoring-owner-scalar-switch-v1`, `restoring-owner-switch-entry-word-v1`, `restoring-owner-switch-entry-two-words-data-v1` and 3 other selectors (6) give `complete-owner text reachable instruction count differs`; `conditional-finite-local-word-loops-v1` and `conditional-finite-spilled-scalar-loops-v1` (2) give `finite loop exact instruction counts differ`.

## Byte identity

`08109B64.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08109B64, with every callee bound to its ROM address and every data word to the address its symbol names (31 `R_ARM_THM_CALL`, 14 `R_ARM_ABS32`). The 860-byte symbol equals the ROM span `[0x08109B64, 0x08109EC0)`: SHA-256 `2b3efe49748127394603326bf15c3e5cdac2f5f5ed9e7832e534a8d67202ca3c` for both. `.text` is exactly 860 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each is added with its address as the value (`"data_08149EE4": "0x08149EE4"`):

`data_08149EE4`, `data_083A1920`, `data_083A1950`, `data_083A1980`, `data_083A1998`, `data_083A19AC`, `data_083A19B0`, `data_083A19B8`, `data_083A19C0`, `data_083A19C8`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08109B64.c` and the data symbols above added: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, `--signed-quotient-profile positive-constant-frame-v1` and `--unsigned-quotient-profile positive-constant-frame-v1` (3) | `buffer callee 0x080DBDC8: unsupported buffer pointer use or escape` |
| `conditional-scheduler-descriptor-calls-v1`, `conditional-scheduler-descriptor-payload-calls-v1`, `conditional-scheduler-descriptor-payload8-calls-v1` and `conditional-scheduler-two-payload-calls-v1` (4) | `scheduler contract requires one actual scheduler call` |
| `conditional-scheduler-branch-descriptor-calls-v1`, `conditional-scheduler-following-call-v1`, `conditional-scheduler-eight-target-branches-v1` and 7 other scheduler selectors (10) | `scheduler branches exceed the explicit call-site or target bounds` |
| `conditional-scheduler-u16-counted-loop-v1` | `counted scheduler loop requires a complete bounded instruction graph` |
| `conditional-scheduler-sequential-live-alias-counted-loops-v1` | `scheduler loop composition requires a complete bounded instruction graph` |
| `conditional-scheduler-three-per-path-live-alias-v1` | `scheduler loop composition exceeds the explicit call-site or target bounds` |
| `conditional-scheduler-entry-descriptor-calls-v1` | `scheduler entry contract requires one actual pinned entry call` |
| `named-data-buffer-v1`, `named-data-buffer-known-query-callee-v1`, `named-data-buffer-dead-argument-aliases-v1` and 14 other selectors (17) | `buffer callee 0x080DBDC8: unsupported buffer pointer use or escape` |
| `named-data-buffer-finite-small-copy-binding-v1` | `one actual canonical small-copy call required` |
| `named-data-buffer-compiler-copy80-binding-v1` | `compiler copy requires exactly one memcpy call and named data only` |
| `named-data-buffer-stack-index-v2` | `stack index: the premise rows of 0x08109B64 need a reviewed entry in config/stack_index_premises.json that repeats them exactly (none found); after checking every caller, add:` |

7 more selectors of these families refuse on contracts for other shapes: `projected outputs require four ordered helpers and one scheduler` (`conditional-scheduler-projected-outputs-v1`); `guarded scheduler requires predicates and exactly one scheduler site` (`conditional-scheduler-guarded-descriptor-calls-v1`); `halfword payload requires one exact output leaf and one scheduler site` (`conditional-scheduler-halfword-output-payload-v1`); `scheduler entry branches require exactly two pinned wrapper call sites` (`conditional-scheduler-entry-branch-descriptor-calls-v1`); `indirect manager contract requires one direct scheduler call` (`conditional-scheduler-indirect-manager-v1`); `manager offset contract requires one direct scheduler call` (`conditional-scheduler-manager-offset-v1`); `manager paths contract requires one direct scheduler call` (`conditional-scheduler-manager-paths-v1`).

The other 166 selector values are not listed one by one (none matched); by family: addressed-runtime (40), callback and closure (22), private float and double (15), BIOS buffer (13), switch-layout (13), owner (12), descriptor and preservation (12), restoring-owner (9), canonical-integer (8), bounded-buffer (8), function-address (6), arithmetic-runtime (5), control-flow (1), -O0 (1), guarded-switch buffer (1).

## Cause

The default run (named data, direct calls) walks `&x` and `&y` into `func_080DBDC8`, which forwards one of
them as a stack argument of its own six-argument callee, and refuses there:
`buffer callee 0x080DBDC8: unsupported buffer pointer use or escape`. That is the forwarding issue's wrapper.

`named-data-buffer-stack-index-v2`, which already has #183's forwarding rule, gets past the wrapper and the whole
walk and stops at the premise ledger:

```
stack index: the premise rows of 0x08109B64 need a reviewed entry in config/stack_index_premises.json that repeats
them exactly (none found); after checking every caller, add:
  site 0x08109CB0, (u32)(ret(0x08109C8E) & 255), bound 4
  site 0x08109CBA, (u32)(ret(0x08109C8E) & 255), bound 4
```

So under that selector the function needs no kit change, only a premise: the facing byte returned by `func_080DBC88`
(the output object's +0x1F) is below 4 at 0x08109C8E. That is not established. The facing byte can be written with
-1 (0xFF) on several ROM paths where a direction is computed from a zero vector, and `(u8)0xFF` is out of the table.
No premise entry is proposed, and the function does not ship until the invariant is settled.

The forwarding issue lists this function among those whose innermost refused callee is a forwarder, measured
with the forwarding flag turned on in the plain proof (not repeated here). Under
`named-data-buffer-stack-index-v2`, which already forwards, the premise row is all that remains.

## Source notes

From the attempt, not reviewed:

- The source declares its own `extern u16 g_control_flags_03000940;` and updates it through `mask` and `flags`
  temporaries, as 91 sources on main do, instead of including `control_flags.h`; with the header the allowlisted
  volatile check would run on the selector path.
- The table copy is the assignment `table = data_08149EE4;` at the top of phase 0x101, before the `ready` test, where
  the ROM performs it.

kit issue: shubshub/fftadecomp-kit#238 (second family; under named-data-buffer-stack-index-v2 only the premise row remains)
