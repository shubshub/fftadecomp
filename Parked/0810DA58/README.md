# 0x0810DA58 - three-ring effect callback: a 3-byte ROM table copy and a looped scheduler call: bytes identical, refused (local aliases across calls on the function-literal path; under named-data-buffer-stack-index-v2 the scheduler callback thunk) (972 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321 with the match batches then queued for merge (PRs #200 onward). `u32 func_0810DA58(task, descriptor, payload)` is a phase callback (switch on `descriptor->phase`: 0, 1, 0x100
to 0x104) registered by its function word at 0x08395128 in the ROM callback table. Phase 0 starts a loader
(`func_080E03F8(actor, data_083A2800, ...)`); 0x100 starts the output task `func_080DDF68(actor, &payload->output, size,
mode, &payload->ready, table, 0, 0, task)`; 0x101 copies the 3-byte ROM table `data_08149F30` to the stack with
`func_081443FC(kinds, data_08149F30, 3)` (0x0810DB5C), reads positions into local `s16` outputs with `func_080DBDC8` and
`func_080DBDA0` (both forward a pointer as their callee's stack argument), and then, in a `u8` loop over three
children, fills a 28-byte stack descriptor with `kind = kinds[i]` and calls
`func_08005B6C(func_0810D728, 0xCC, &child, task)` at 0x0810DC76; 0x102 waits for the three children and sets their
states in a second, call-free `u8` loop; 0x103 and 0x104 run the follow-up animation and wait.

## The index

`symbols/functions.txt` has `0810DA58 0810DE24 972 486 return` and `config/functions.json` the same extent with 486 instructions (`thumb-prologue`). The CFG, closed by the kit's own `analyze.refine_function`, has 422 reachable instructions, so the instruction column is the halfword count (486). The selectors that compare it with the CFG are outside the families that fit this function: `restoring-owner-scalar-switch-v1`, `restoring-owner-switch-entry-word-v1`, `restoring-owner-switch-entry-two-words-data-v1` and 3 other selectors (6) give `complete-owner text reachable instruction count differs`.

## Byte identity

`0810DA58.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0810DA58, with every callee bound to its ROM address and every data word to the address its symbol names (32 `R_ARM_THM_CALL`, 12 `R_ARM_ABS32`). The 972-byte symbol equals the ROM span `[0x0810DA58, 0x0810DE24)`: SHA-256 `59ede03015a1ef218d2a5d0c10fbf5868dee9e39d2ae6e2a2fb6655428aeaaee` for both. `.text` is exactly 972 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each is added with its address as the value (`"data_08149F30": "0x08149F30"`):

`data_08149F30`, `data_083A2800`, `data_083A2848`, `data_083A2878`, `data_083A28C0`, `data_083A28FC`, `data_083A2900`, `data_083A2908`, `data_083A2910`, `data_083A2918`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0810DA58.c` and the data symbols above added: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, `--signed-quotient-profile positive-constant-frame-v1` and `--unsigned-quotient-profile positive-constant-frame-v1` (3) | `stack aliases cannot cross calls in caller-clobbered registers` |
| `conditional-scheduler-descriptor-calls-v1`, `conditional-scheduler-descriptor-payload-calls-v1`, `conditional-scheduler-descriptor-payload8-calls-v1` and `conditional-scheduler-two-payload-calls-v1` (4) | `scheduler contract requires one actual scheduler call` |
| `conditional-scheduler-branch-descriptor-calls-v1`, `conditional-scheduler-following-call-v1` and `conditional-scheduler-eight-target-branches-v1` (3) | `scheduler branches exceed the explicit call-site or target bounds` |
| `conditional-scheduler-twenty-four-target-branches-v1`, `conditional-scheduler-live-local-alias-calls-v1`, `conditional-scheduler-live-local-alias-payload-calls-v1` and 5 other scheduler selectors (8) | `predicate composition excludes CFG cycles` |
| `conditional-scheduler-u16-counted-loop-v1` | `counted scheduler loop requires a complete bounded instruction graph` |
| `conditional-scheduler-sequential-live-alias-counted-loops-v1` | `scheduler loop composition requires a complete bounded instruction graph` |
| `conditional-scheduler-three-per-path-live-alias-v1` | `counted loop increments a different or caller-clobbered counter` |
| `conditional-scheduler-entry-descriptor-calls-v1` | `scheduler entry contract requires one actual pinned entry call` |
| `named-data-buffer-v1`, `named-data-buffer-known-query-callee-v1`, `named-data-buffer-dead-argument-aliases-v1` and 14 other selectors (17) | `buffer callee 0x080DBDC8: unsupported buffer pointer use or escape` |
| `named-data-buffer-finite-small-copy-binding-v1` | `small-copy prefix excludes ordinary memory accesses` |
| `named-data-buffer-compiler-copy80-binding-v1` | `compiler copy requires exactly one memcpy call and named data only` |
| `named-data-buffer-stack-index-v2` | `buffer callee 0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification` |

6 more selectors of these families refuse on contracts for other shapes: `projected outputs require four ordered helpers and one scheduler` (`conditional-scheduler-projected-outputs-v1`); `halfword payload requires one exact output leaf and one scheduler site` (`conditional-scheduler-halfword-output-payload-v1`); `scheduler entry branches require exactly two pinned wrapper call sites` (`conditional-scheduler-entry-branch-descriptor-calls-v1`); `indirect manager contract requires one direct scheduler call` (`conditional-scheduler-indirect-manager-v1`); `manager offset contract requires one direct scheduler call` (`conditional-scheduler-manager-offset-v1`); `manager paths contract requires one direct scheduler call` (`conditional-scheduler-manager-paths-v1`).

The other 166 selector values are not listed one by one (none matched); by family: addressed-runtime (40), callback and closure (22), private float and double (15), BIOS buffer (13), switch-layout (13), owner (12), descriptor and preservation (12), restoring-owner (9), canonical-integer (8), bounded-buffer (8), function-address (6), arithmetic-runtime (5), control-flow (1), -O0 (1), guarded-switch buffer (1).

## Cause

The callback word `func_0810D728` (0x0810DC90) and the named data put the default run on the
function-literal path, which runs without a buffer proof and refuses the first local address held in R0-R3 across a
call: `stack aliases cannot cross calls in caller-clobbered registers`. The selectors that carry a buffer proof stop
at the first coordinate wrapper (`buffer callee 0x080DBDC8: unsupported buffer pointer use or escape`), except
`named-data-buffer-stack-index-v2`, whose forwarding rule passes the wrappers and which then stops at the scheduler:
`func_08005B6C` calls `func_08005954`, which calls the task callback through `_call_via_r3` at 0x08142250. That is the
refusal the #200 comment reports for this function. The scheduler selectors refuse the loop (`predicate composition
excludes CFG cycles`; `counted loop increments a different or caller-clobbered counter`, because the call-free loop of
phase 0x102 counts in R1) or its size (the loop-composition selectors cap the CFG at 256 instructions; it has 422).

With the scheduler call-site summary and forwarding prototyped, the #200 comment reports the next refusal as #200's
item 6 (`stack index: the owner passes stack pointers to a callee after a callee released a forwarded pointer word`);
that was not re-run here. The `kinds[i]` index is the loop counter, bounded by the loop itself.

## Source notes

From the attempt, not reviewed: the second loop uses its own block-scoped `u8 j` (the ROM counts it in
R1, the first loop in R4); the table copy is an explicit `func_081443FC` call, as in the siblings; the declaration order
of the locals decides their stack slots.

kit issue: shubshub/fftadecomp-kit#200 (comment); shubshub/fftadecomp-kit#238 (the forwarding wrappers clear; the memcpy of #200 is next); shubshub/fftadecomp-kit#237
