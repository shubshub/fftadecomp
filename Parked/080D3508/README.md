# 0x080D3508 - effect task starter: bytes identical, refused (a local descriptor passed directly to func_08005954, no selector admits the call on its own) (208 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `struct Task *func_080D3508(u16 id, void *object, u32 arg)` starts effect `id` as a task; 23 functions call it (48 `bl` sites, among them `0x08091E48`, `0x080A5A7C`, `0x0811E890` and `0x0812B7F0`). It fills a 28-byte request on the stack at `sp + 4` (`id` at +0x14, `object` +4, `arg` +8, `mode` +0xC). For ids up to 0x155 it takes the callback and payload size from the 8-byte entry `data_083947D8[id - 1]`, sets `mode` to 2 when `func_080D3B98(object, id)` is non-zero, and stores `func_080D3B38(object)` at +0x16. Larger ids use `data_08395280[id - 0x156]`, and id 0x159 instead starts `func_080E2398` with a 0x28-byte payload, taking +0x16 from the first table's entry for `arg`. Both paths meet at one direct scheduler call:

```
080D359E  ldr  r0, =data_0200F430
080D35A0  ldr  r0, [r0]              @ scheduler
080D35A2  ldr  r1, =data_020159C0
080D35A4  ldr  r1, [r1]
080D35A6  str  r1, [sp]              @ parent, fifth argument
080D35A8  adds r1, r3, #0            @ callback (table entry or func_080E2398)
080D35AA  add  r3, sp, #4            @ 28-byte request
080D35AC  bl   0x08005954
```

## The index

The index row `080D3508 080D35D8 208 81 return` is right: the kit's `analyze.refine_function` at 18dcc516 closes the CFG at 81 reachable instructions over the indexed extent, and `config/functions.json` agrees.

## Byte identity

`080D3508.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080D3508, with every callee and data symbol bound to its ROM address (4 `R_ARM_THM_CALL`, 6 `R_ARM_ABS32`). The 208-byte symbol equals the ROM span `[0x080D3508, 0x080D35D8)`: SHA-256 `f5d37bec0341368abf3dd018b4c5835c8427d973a87051b764bfbaecface5062` for both. `.text` is exactly 208 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each was added with its address as the value (`"data_08395280": "0x08395280"`) for the runs below: `data_08395280`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080D3508.c` and the data symbols above: the default run and all 213 selector values. None matched. The default run prints the refusal after `compile failed:`, a selector run as `error (ValueError): <text>`.

| Selector | Refusal |
|---|---|
| default, and 3 other selector values | `stack aliases cannot cross calls in caller-clobbered registers` |
| `conditional-scheduler-projected-outputs-v1` | `projected outputs require four ordered helpers and one scheduler` |
| `conditional-scheduler-descriptor-calls-v1`, `conditional-scheduler-descriptor-payload-calls-v1`, `conditional-scheduler-descriptor-payload8-calls-v1`, `conditional-scheduler-two-payload-calls-v1` (4) | `scheduler contract requires one actual scheduler call` |
| `conditional-scheduler-branch-descriptor-calls-v1`, `conditional-scheduler-following-call-v1`, `conditional-scheduler-eight-target-branches-v1`, `conditional-scheduler-twenty-four-target-branches-v1`, `conditional-scheduler-live-local-alias-calls-v1`, `conditional-scheduler-live-local-alias-payload-calls-v1` and 4 others (10) | `scheduler branches exceed the explicit call-site or target bounds` |
| `conditional-scheduler-u16-counted-loop-v1` | `counted scheduler requires exactly one backward edge` |
| `conditional-scheduler-sequential-live-alias-counted-loops-v1`, `conditional-scheduler-three-per-path-live-alias-v1` | `scheduler loop composition exceeds the explicit call-site or target bounds` |
| `conditional-scheduler-guarded-descriptor-calls-v1` | `guarded scheduler requires predicates and exactly one scheduler site` |
| `conditional-scheduler-halfword-output-payload-v1` | `halfword payload requires one exact output leaf and one scheduler site` |
| `conditional-scheduler-entry-descriptor-calls-v1` | `scheduler entry contract requires one actual pinned entry call` |
| `conditional-scheduler-entry-branch-descriptor-calls-v1` | `scheduler entry branches require exactly two pinned wrapper call sites` |
| `conditional-scheduler-indirect-manager-v1` | `indirect manager contract requires one direct scheduler call` |
| `conditional-scheduler-manager-offset-v1` | `manager offset contract requires one direct scheduler call` |
| `conditional-scheduler-manager-paths-v1` | `manager paths contract requires one direct scheduler call` |

The other 185 selector values give 62 other refusals, none of them a match; the most frequent are `addressed data requires a mapped object and signed32 addend` (26), `buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification` (18), `private float requires unique undefined pinned helper symbols` (15).

## Cause

The request address in R3 at `0x080D35AC` is the only local address that reaches a call. The function has named data and a function literal (`func_080E2398`), so the default run takes the function-literal path, which has no buffer proof, and refuses the crossing. Each of the 25 `conditional-scheduler-*` selectors bounds the whole caller. Most of them count calls to `func_08005B6C`, which this function does not make (it calls `func_08005954` directly), and the entry selector, which binds a direct `func_08005954` call, requires it to be the only call (there are four). The `named-data-buffer-*` selectors walk into `func_08005954` and stop at its callback thunk `_call_via_r3` (`0x08142250`). In the prototype measured for the kit issue below, the descriptor contract applied as a per-site summary admits this function with no other change (not re-run here).

## Source notes

- `struct Task *task = 0;` is the spelling of the matched sibling `src/080D3818.c`. The ROM's `movs r7, #0` (`0x080D3514`) is the zero stored to `mode` and to +0x18, and the dead `adds r7, r0, #0` after the call (`0x080D35B0`) is the assignment of the result to the same variable. Without the initialiser the function is 204 bytes (10 halfwords differ).
- Request and entry layouts follow the reads and stores above; unknown members are named `unknown_*`.

kit issue: (to be filed - match.py: a scheduler call with a local descriptor verifies only under shape-bound owner selectors; a per-site summary admits 7 byte-identical functions alone and 14 with companion rules)
