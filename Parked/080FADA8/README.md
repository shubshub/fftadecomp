# 0x080FADA8 - effect 0x80 phase callback with a looped scheduler call: bytes identical, refused (a local copy of a ROM table through func_081443FC indexed by a callee's result, and a stack descriptor passed to func_08005B6C in a loop) (780 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `u32 func_080FADA8(void *task, Descriptor080FADA8 *descriptor, Payload080FADA8 *payload)` is the phase callback of effect 0x80: its function word is entry 0x7F of the effect table `data_083947D8` (`0x08394BD0`) that 0x080D3508 reads. Phase 0 starts the actor's first animation (`func_080E03F8(actor, data_0839CA84, ...)`). Phase 0x100 waits for it and either counts the targets and jumps to phase 0x103 or starts the scene child `func_080DDF68` and records the visual's facing. Phase 0x101 copies the 5-byte delay table `data_08149D70` (0, 40, 30, 20, 10) to the frame with `func_081443FC`, waits for the scene, reads the visual's position (`func_080DBDC8`, into the payload), starts the coordinate task with one of two tables (`data_0839CAB4`, `data_0839CAFC`) and a sound (`data_0894ABF0`), stores the `u8` result of `func_080D8924(actor, 0, 30, task)` in `payload->count`, and then, for each of the `count` targets, fills a stack descriptor and starts `func_080FACF8` with `func_08005B6C(func_080FACF8, 0x20, &params, task)` (`0x080FAF4A`), the first delay `delays[count]` and 10 more for each target. Phases 0x102 to 0x105 wait for the children, start one animation per target (`func_080DCFE4(object, data_0839CB74, ...)`) and wait for them.

```
080FAEAC  add  r5, sp, #0x30         @ u8 delays[5]
080FAEAE  ldr  r1, =data_08149D70
080FAEB0  adds r0, r5, #0
080FAEB2  movs r2, #5
080FAEB4  bl   0x081443FC
...
080FAF20  bl   0x080D8924
080FAF24  strb r0, [r4, #8]          @ payload->count
080FAF26  ldrb r1, [r4, #8]
080FAF28  adds r0, r5, r1
080FAF2A  ldrb r6, [r0]              @ delays[payload->count]
...
080FAF46  add  r2, sp, #0x14         @ 28-byte descriptor
080FAF48  mov  r3, sb                @ parent
080FAF4A  bl   0x08005B6C
```

## The index

The index row `080FADA8 080FB0B4 780 390 return` is right about the extent, but its instruction column is the halfword count (bytes/2), as is `config/functions.json`'s (390): the reachable CFG has 336 instructions (the kit's `analyze.refine_function` at 18dcc516 closes it over the indexed extent). Not corrected here: no draft needs it. The selectors that check the count against the CFG refuse on it (`restoring-owner-scalar-switch-v1`, `restoring-owner-switch-entry-word-v1`, `restoring-owner-switch-entry-two-words-data-v1`, `restoring-owner-acyclic-v1` and 2 more: `complete-owner text reachable instruction count differs`).

## Byte identity

`080FADA8.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080FADA8, with every callee and data symbol bound to its ROM address (25 `R_ARM_THM_CALL`, 9 `R_ARM_ABS32`). The 780-byte symbol equals the ROM span `[0x080FADA8, 0x080FB0B4)`: SHA-256 `63e1bc8cb5147315850b0c14f93886b362c6b0c9a363aa72d3fda382904ec0b1` for both. `.text` is exactly 780 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each was added with its address as the value (`"data_08149D70": "0x08149D70"`) for the runs below: `data_08149D70`, `data_0839CA84`, `data_0839CAB4`, `data_0839CAFC`, `data_0839CB74`, `data_0839CB88`, `data_0839CB8C`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080FADA8.c` and the data symbols above: the default run and all 213 selector values. None matched. The default run prints the refusal after `compile failed:`, a selector run as `error (ValueError): <text>`.

| Selector | Refusal |
|---|---|
| default, and 2 other selector values | `stack aliases cannot cross calls in caller-clobbered registers` |
| `conditional-scheduler-projected-outputs-v1` | `projected outputs require four ordered helpers and one scheduler` |
| `conditional-scheduler-descriptor-calls-v1`, `conditional-scheduler-descriptor-payload-calls-v1`, `conditional-scheduler-descriptor-payload8-calls-v1`, `conditional-scheduler-two-payload-calls-v1` (4) | `scheduler contract requires one actual scheduler call` |
| `conditional-scheduler-branch-descriptor-calls-v1`, `conditional-scheduler-following-call-v1`, `conditional-scheduler-eight-target-branches-v1` (3) | `scheduler branches exceed the explicit call-site or target bounds` |
| `conditional-scheduler-twenty-four-target-branches-v1`, `conditional-scheduler-live-local-alias-calls-v1`, `conditional-scheduler-live-local-alias-payload-calls-v1`, `conditional-scheduler-twenty-four-target-following-calls-v1`, `conditional-scheduler-three-per-path-calls-v1`, `conditional-scheduler-sequential-leaf-output-calls-v1` and 2 others (8) | `predicate composition excludes CFG cycles` |
| `conditional-scheduler-u16-counted-loop-v1` | `counted scheduler loop requires a complete bounded instruction graph` |
| `conditional-scheduler-sequential-live-alias-counted-loops-v1` | `scheduler loop composition requires a complete bounded instruction graph` |
| `conditional-scheduler-three-per-path-live-alias-v1`, and 17 other selector values | `buffer callee 0x081443FC: unsupported buffer pointer use or escape` |
| `conditional-scheduler-halfword-output-payload-v1` | `halfword payload requires one exact output leaf and one scheduler site` |
| `conditional-scheduler-entry-descriptor-calls-v1` | `scheduler entry contract requires one actual pinned entry call` |
| `conditional-scheduler-entry-branch-descriptor-calls-v1` | `scheduler entry branches require exactly two pinned wrapper call sites` |
| `conditional-scheduler-indirect-manager-v1` | `indirect manager contract requires one direct scheduler call` |
| `conditional-scheduler-manager-offset-v1` | `manager offset contract requires one direct scheduler call` |
| `conditional-scheduler-manager-paths-v1` | `manager paths contract requires one direct scheduler call` |
| `named-data-buffer-stack-index-v1`, `named-data-buffer-stack-index-v2` | `buffer callee 0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification` |
| `named-data-buffer-rom-table-copy-v1` | `unsupported stack-alias use or escape` |

The other 166 selector values give 56 other refusals, none of them a match; the most frequent are `addressed data requires a mapped object and signed32 addend` (26), `private float requires unique undefined pinned helper symbols` (15), `addressed signed runtimes exclude data and irregular relocations` (13).

## Cause

Two local addresses reach calls: the copy destination `delays` (`func_081443FC`, count 5, a constant ROM source), which stays in R5 across four calls until the index read at `0x080FAF2A`, and the scheduler descriptor at `sp + 0x14`, passed in R2 to `func_08005B6C` inside the loop. The function has named data and a function literal, so the default run takes the function-literal path, which has no buffer proof, and refuses the crossing. `named-data-buffer-rom-table-copy-v1` summarises the copy and refuses the register index `delays[payload->count]`. The stack-index selectors, which admit that index under a premise, walk the descriptor into the scheduler and stop at its callback thunk (`func_08005B6C` -> `func_08005954` -> `_call_via_r3`). The scheduler selectors refuse on the caller's shape: the loop (`predicate composition excludes CFG cycles`), and the two counted-loop selectors on their 256-instruction bound (this function has 336 reachable instructions). `conditional-scheduler-three-per-path-live-alias-v1`, the closest fit, stops at the copy helper. With the 256-instruction cap raised to 512 in a scratch copy of the kit, `conditional-scheduler-sequential-live-alias-counted-loops-v1` stops at the same copy (`buffer callee 0x081443FC`, the destination in R0 with its preserved copy in R5) (earlier measurement, not re-run here). In the prototype measured for the scheduler issue below, the descriptor contract as a per-site summary takes this function under `named-data-buffer-stack-index-v2` past the scheduler to the premise ledger, which asks for site `0x080FAF2A`, `(u32)u8[(entry_R2 + 8)]@0x080FAF26`, bound 5; with a throwaway entry it then refuses with `ROM table copy owner requires named data or an object initialiser and excludes function literals and switches` (not re-run here).

## Source notes

- `data_08149D70` is a named ROM object at its literal's address, and the copy is written as the call the ROM makes, at the top of the phase as the ROM orders it.
- **The index has no established bound.** `delays[payload->count]` needs `func_080D8924`'s result to be at most 4. That function (parked) returns a count of targets that has not been traced; the same open premise holds 0x080F7F70, which has the same shape (`delays` from `data_08149D5C`, `count` from `func_080D8924`). No premise entry should be written without that proof.
- `func_080FACF8` is declared without a parameter list (`u32 func_080FACF8();`), matching the callback type this file gives `func_08005B6C`.
- Siblings: 0x080EE4FC, 0x0810C8D0, 0x080FACF8 (the child).

kit issue: shubshub/fftadecomp-kit#200 (comment to be posted)
kit issue: (to be filed - match.py: a scheduler call with a local descriptor verifies only under shape-bound owner selectors; a per-site summary admits 7 byte-identical functions alone and 14 with companion rules)
