# 0x08101410 - child-status effect phase callback (effect 0xD0): bytes identical, refused (a scheduler call with a local descriptor and three local coordinate outputs through the forwarder 0x080DBD78, with named data) (556 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `u32 func_08101410(void *task, Descriptor08101410 *descriptor, Payload08101410 *payload)` is the phase callback of effect 0xD0 in the table `data_083947D8` that `func_080D3508` reads (function word at `0x08394E50`); no `bl` reaches it. Phase 0 starts a first child with `func_080E03F8(actor, data_0839EAD4, mode, 0, 0, task)`. 0x100 waits for it, stops when `func_080D3B54(actor)` is set, and starts the 0x90-byte child `func_08100EF0` through `func_08005B6C` with a local 28-byte descriptor at `sp + 0x10` (flag, actor and a pointer to `payload->status`). 0x101 to 0x103 step on the child's status values 1, 3 and a 0x10-frame countdown. 0x104 either reads the actor object's position into three local `s16` outputs and starts `func_080DFA30(object, 0x3D1, 6, x, z, 0, task)` (flag set), or starts a coordinate task (`func_080D6098(..., data_0839EB04, task)`), `func_080DCFE4(object, data_0839EB34, 12, 20, 4, task, 20)` and `func_080DFD8C(data_0839EB50, 1, 4, 0, task)`. 0x105 waits for the tasks.

```
081014D0  str  r0, [sp, #0x14]        @ descriptor +4 = actor
081014D2  adds r0, r6, #7
081014D4  str  r0, [sp, #0x18]        @ descriptor +8 = &payload->status
081014D6  ldr  r0, =func_08100EF0
081014D8  movs r1, #0x90
081014DA  add  r2, sp, #0x10
081014DE  bl   0x08005B6C
...
08101562  add  r5, sp, #0x2c          @ &x
08101564  mov  r2, sp
08101566  adds r2, #0x2e              @ &y
08101568  add  r4, sp, #0x30          @ &z
0810156E  bl   0x080DBD78
08101574  ldrb r3, [r5]               @ x, read back after the call
```

`func_080DBD78` (40 bytes) is a forwarder: it keeps `&x` in a register and stores `&y` and `&z` into its own outgoing words (`str r2, [sp]; str r3, [sp, #4]`) for `func_0801C9F0`.

## The index

The index row `08101410 0810163C 556 278 return` is right about the extent, but its instruction column is the halfword count (bytes/2), as is `config/functions.json`'s (278): the reachable CFG has 237 instructions (the kit's `analyze.refine_function` at 18dcc516 closes it over the indexed extent). Not corrected here: no draft needs it. The selectors that check the count against the CFG refuse on it (`restoring-owner-scalar-switch-v1`, `restoring-owner-switch-entry-word-v1`, `restoring-owner-switch-entry-two-words-data-v1`, `restoring-owner-acyclic-v1` and 2 more: `complete-owner text reachable instruction count differs`).

## Byte identity

`08101410.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08101410, with every callee and data symbol bound to its ROM address (20 `R_ARM_THM_CALL`, 5 `R_ARM_ABS32`). The 556-byte symbol equals the ROM span `[0x08101410, 0x0810163C)`: SHA-256 `5aa5097d5cc38236a0a4f94833d9ba7c1ea3a89815f36011802125a6e26759c3` for both. `.text` is exactly 556 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each was added with its address as the value (`"data_0839EAD4": "0x0839EAD4"`) for the runs below: `data_0839EAD4`, `data_0839EB04`, `data_0839EB34`, `data_0839EB50`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08101410.c` and the data symbols above: the default run and all 213 selector values. None matched. The default run prints the refusal after `compile failed:`, a selector run as `error (ValueError): <text>`.

| Selector | Refusal |
|---|---|
| default, and 2 other selector values | `stack aliases cannot cross calls in caller-clobbered registers` |
| `conditional-scheduler-projected-outputs-v1` | `projected outputs require four ordered helpers and one scheduler` |
| `conditional-scheduler-descriptor-calls-v1`, `conditional-scheduler-descriptor-payload-calls-v1`, `conditional-scheduler-descriptor-payload8-calls-v1`, `conditional-scheduler-two-payload-calls-v1` (4) | `scheduler contract requires one actual scheduler call` |
| `conditional-scheduler-branch-descriptor-calls-v1`, `conditional-scheduler-following-call-v1`, `conditional-scheduler-eight-target-branches-v1` (3) | `scheduler branches exceed the explicit call-site or target bounds` |
| `conditional-scheduler-twenty-four-target-branches-v1`, `conditional-scheduler-three-per-path-calls-v1` | `ordinary branch calls exclude every live local alias and pointer word` |
| `conditional-scheduler-live-local-alias-calls-v1`, `conditional-scheduler-sequential-live-alias-counted-loops-v1`, `conditional-scheduler-three-per-path-live-alias-v1` (3) | `buffer callee 0x080DBD78: unsupported buffer pointer use or escape` |
| `conditional-scheduler-live-local-alias-payload-calls-v1` | `scheduler payload contract requires a frame of exactly the descriptor and one adjacent nonempty payload` |
| `conditional-scheduler-twenty-four-target-following-calls-v1` | `following-call contract requires one scheduler site and a reached following ordinary call` |
| `conditional-scheduler-sequential-leaf-output-calls-v1` | `scheduler leaf output excludes preserved-register aliases` |
| `conditional-scheduler-sequential-killed-alias-calls-v1` | `alias kill excludes preserved-register aliases` |
| `conditional-scheduler-u16-counted-loop-v1` | `counted scheduler requires exactly one backward edge` |
| `conditional-scheduler-guarded-descriptor-calls-v1` | `predicate helper contains an unsupported or memory-writing instruction` |
| `conditional-scheduler-halfword-output-payload-v1` | `halfword payload requires one exact output leaf and one scheduler site` |
| `conditional-scheduler-entry-descriptor-calls-v1` | `scheduler entry contract requires one actual pinned entry call` |
| `conditional-scheduler-entry-branch-descriptor-calls-v1` | `scheduler entry branches require exactly two pinned wrapper call sites` |
| `conditional-scheduler-indirect-manager-v1` | `indirect manager contract requires one direct scheduler call` |
| `conditional-scheduler-manager-offset-v1` | `manager offset contract requires one direct scheduler call` |
| `conditional-scheduler-manager-paths-v1` | `manager paths contract requires one direct scheduler call` |
| `named-data-buffer-stack-index-v1`, `named-data-buffer-stack-index-v2`, and 16 other selector values | `buffer callee 0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification` |

The other 168 selector values give 57 other refusals, none of them a match; the most frequent are `addressed data requires a mapped object and signed32 addend` (26), `private float requires unique undefined pinned helper symbols` (15), `addressed signed runtimes exclude data and irregular relocations` (13).

## Cause

The function has named data and function literals, so the default run takes the function-literal path and refuses the first crossing local address (`stack aliases cannot cross calls in caller-clobbered registers`). The buffer selectors walk the scheduler call first and stop at its callback thunk (`buffer callee 0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification`), both stack-index selectors included. The scheduler selectors that admit this scheduler site and walk on stop at the forwarder (`conditional-scheduler-live-local-alias-calls-v1`, `-sequential-live-alias-counted-loops-v1` and `-three-per-path-live-alias-v1`: `buffer callee 0x080DBD78: unsupported buffer pointer use or escape`), which is what the forwarding issue below reports for its scheduler-summary prototype. In the prototypes measured for the two issues below (not re-run here), the per-site scheduler summary and the forwarding rule together give `MATCH - byte identical`, and each alone leaves the other refusal.

## Source notes

- The descriptor's +8 word is a payload pointer (`&payload->status`), not a local.
- The coordinate branch passes `x` and `z` to `func_080DFA30`; `y` is written by the wrapper and not read again, as in the ROM.

kit issue: shubshub/fftadecomp-kit#237; shubshub/fftadecomp-kit#238
