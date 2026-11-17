# 0x080D89D0 - scheduler entry with a local payload: bytes identical, refused (a local payload address stored in a scheduler descriptor) (136 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `void *func_080D89D0(...)` takes 14 arguments (four `u8` in R0-R3, the rest on the stack) and starts a task with `func_08005954(data_0200F430, func_080D7B08, 0x103C, &descriptor, parent)`; six functions call it (`0x0810EA78`, `0x08110FE0`, `0x081112A0`, `0x08112AEC`, `0x08113FEC`, `0x081208C8`). It packs thirteen of the arguments into a 24-byte payload at `sp + 0x20` (bytes at +0-+3 and +0x14-+0x17, halfwords at +4-+8, two words at +0xC and +0x10), stores the payload's address in word +4 of a 28-byte descriptor at `sp + 4`, and passes the last argument through as the parent word:

```
080D89F2  ldr  r4, [sp, #0x7c]
080D89F4  str  r4, [sp]               @ parent, fifth argument of func_08005954
...
080D8A02  add  r4, sp, #0x20          @ payload
...
080D8A2A  str  r4, [sp, #8]           @ descriptor +4 = &payload
080D8A2C  ldr  r0, =data_0200F430
080D8A2E  ldr  r0, [r0]
080D8A30  ldr  r1, =func_080D7B08
080D8A32  ldr  r2, =0x103C
080D8A34  add  r3, sp, #4             @ descriptor
080D8A36  bl   0x08005954
```

`data_0200F430` (the scheduler) is its only named data word.

## The index

The index row `080D89D0 080D8A58 136 60 return` is right: the kit's `analyze.refine_function` at 18dcc516 closes the CFG at 60 reachable instructions over the indexed extent, and `config/functions.json` agrees.

## Byte identity

`080D89D0.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080D89D0, with every callee and data symbol bound to its ROM address (1 `R_ARM_THM_CALL`, 2 `R_ARM_ABS32`). The 136-byte symbol equals the ROM span `[0x080D89D0, 0x080D8A58)`: SHA-256 `3b451ae59cc831fec62dec3079cd7e9218f3437a512d3c6cf23c4e473ca63b06` for both. `.text` is exactly 136 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

None needed: every data symbol the source names is already in `config/data_symbols.json`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080D89D0.c`: the default run and all 213 selector values. None matched. The default run prints the refusal after `compile failed:`, a selector run as `error (ValueError): <text>`.

| Selector | Refusal |
|---|---|
| default, and 4 other selector values | `unsupported stack-alias use or escape` |
| `named-data-buffer-v1`, and 15 other selector values | `buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification` |
| `conditional-scheduler-projected-outputs-v1` | `projected outputs require four ordered helpers and one scheduler` |
| `conditional-scheduler-descriptor-calls-v1`, `conditional-scheduler-descriptor-payload-calls-v1`, `conditional-scheduler-descriptor-payload8-calls-v1`, `conditional-scheduler-two-payload-calls-v1` (4) | `scheduler contract requires one actual scheduler call` |
| `conditional-scheduler-branch-descriptor-calls-v1`, `conditional-scheduler-following-call-v1`, `conditional-scheduler-eight-target-branches-v1`, `conditional-scheduler-twenty-four-target-branches-v1`, `conditional-scheduler-live-local-alias-calls-v1`, `conditional-scheduler-live-local-alias-payload-calls-v1` and 4 others (10) | `scheduler branches exceed the explicit call-site or target bounds` |
| `conditional-scheduler-u16-counted-loop-v1` | `counted scheduler requires exactly one backward edge` |
| `conditional-scheduler-sequential-live-alias-counted-loops-v1`, `conditional-scheduler-three-per-path-live-alias-v1` | `scheduler loop composition exceeds the explicit call-site or target bounds` |
| `conditional-scheduler-guarded-descriptor-calls-v1` | `guarded scheduler requires predicates and exactly one scheduler site` |
| `conditional-scheduler-halfword-output-payload-v1` | `halfword payload requires one exact output leaf and one scheduler site` |
| `conditional-scheduler-entry-descriptor-calls-v1` | `scheduler entry contract excludes additional register or pointer-word aliases` |
| `conditional-scheduler-entry-branch-descriptor-calls-v1` | `scheduler entry branches require exactly two pinned wrapper call sites` |
| `conditional-scheduler-indirect-manager-v1` | `manager field requires exactly two zero-offset word dereferences` |
| `conditional-scheduler-manager-offset-v1` | `manager pointer requires a zero-offset first dereference` |
| `conditional-scheduler-manager-paths-v1` | `manager path pointer requires a zero-offset first dereference` |

The other 168 selector values give 60 other refusals, none of them a match; the most frequent are `addressed data requires a mapped object and signed32 addend` (26), `private float requires unique undefined pinned helper symbols` (15), `addressed signed runtimes exclude data and irregular relocations` (13).

## Cause

Storing a stack address into a stack word is refused on the default path (`unsupported stack-alias use or escape`), before the scheduler call is considered. The scheduler selectors that count `func_08005B6C` calls do not apply to a direct `func_08005954` call. `conditional-scheduler-entry-descriptor-calls-v1`, which binds exactly that call, refuses the payload pointer in the descriptor (`scheduler entry contract excludes additional register or pointer-word aliases`), and the payload selectors bind only `func_08005B6C`. The `named-data-buffer-*` selectors walk into the scheduler and stop at its `_call_via_r3` thunk. In the prototype measured for the kit issues below, the function needs both rules: the descriptor contract as a per-site summary, and pointer slots on the function-literal path with named data. With either alone it is still refused (not re-run here).

## Source notes

- The parameters keep positional names (`a0`-`a12`, `parent`): the callers have not been read for meaning. The payload's members are `unknown_*` at the offsets the stores give; argument `a8` goes to +4, ahead of `a4` and `a5` at +6 and +8, as the ROM stores them.

kit issue: shubshub/fftadecomp-kit#237
kit issue: shubshub/fftadecomp-kit#236
