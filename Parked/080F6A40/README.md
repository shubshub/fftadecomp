# 0x080F6A40 - phase callback with coordinate outputs and child tasks: bytes identical, refused (local s16 outputs forwarded by func_080DBDC8, and a scheduler descriptor) (518 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `u32 func_080F6A40(void *task, Descriptor080F6A40 *descriptor, Payload080F6A40 *payload)` is a phase callback; its function word is in the table at `0x08394AE8`. Phase 0 starts a loader (`func_080E03F8` with `data_0839B904`); phase 0x100 waits for it and either counts the targets (`func_080DD494`) or starts an animation child with `func_080DDF68`. Phase 0x101, once that child is ready, reads the object's position into two local `s16` with `func_080DBDC8(payload->object, &x, &y)`, starts a coordinate effect (`func_080D6098`) and three tasks from `data_0839B9B8` (`func_080D4870`), a record task (`func_080DFD8C`), and asks `func_080D8924` for the target count. Phase 0x102 starts `func_080F695C` for one target every 30 frames through the scheduler, with a 28-byte request at `sp + 0x18`. Phase 0x103 waits for everything.

```
080F6B06  mov  r4, sp
080F6B08  adds r4, #0x16
080F6B0A  add  r1, sp, #0x14          @ &x
080F6B0C  adds r2, r4, #0             @ &y
080F6B0E  bl   0x080DBDC8
...
080F6BB6  add  r4, sp, #0x18          @ request, kept in R4
080F6BB8  ldrh r1, [r5, #6]
080F6BBA  strh r1, [r4, #0x14]        @ request.index
...
080F6BC2  bl   0x080DD4A4
080F6BC6  str  r0, [r4, #4]           @ request.object
080F6BC8  ldr  r0, =func_080F695C
080F6BCA  movs r1, #0x28
080F6BCC  adds r2, r4, #0
080F6BCE  adds r3, r7, #0             @ task
080F6BD0  bl   0x08005B6C
```

`func_080DBDC8` (36 bytes) passes `&x` on as its own fourth argument and stores `&y` into its outgoing word (`str r2, [sp]` at `0x080DBDDA`) for the six-argument leaf `func_0801C984`, which writes both halfwords.

## The index

The index row `080F6A40 080F6C46 518 259 return` is right about the extent, but its instruction column is the halfword count (bytes/2), as is `config/functions.json`'s (259): the reachable CFG has 223 instructions (the kit's `analyze.refine_function` at 18dcc516 closes it over the indexed extent). Not corrected here: no draft needs it. The selectors that check the count against the CFG refuse on it (`restoring-owner-switch-aligned-v1`, `restoring-owner-switch-cycles-function-words-v1`: `complete-owner text reachable instruction count differs`).

## Byte identity

`080F6A40.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080F6A40, with every callee and data symbol bound to its ROM address (19 `R_ARM_THM_CALL`, 6 `R_ARM_ABS32`). The 518-byte symbol equals the ROM span `[0x080F6A40, 0x080F6C46)`: SHA-256 `93b4e1349f88bba1123458d9d424a03f446b98ef812fba816551899d424f8b74` for both. `.text` is 520 bytes: the symbol and the assembler's 2-byte alignment padding. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each was added with its address as the value (`"data_0839B904": "0x0839B904"`) for the runs below: `data_0839B904`, `data_0839B928`, `data_0839B9B8`, `data_0839B9E4`, `data_0839B9E8`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080F6A40.c` and the data symbols above: the default run and all 213 selector values. None matched. The default run prints the refusal after `compile failed:`, a selector run as `error (ValueError): <text>`.

| Selector | Refusal |
|---|---|
| default, and 2 other selector values | `stack aliases cannot cross calls in caller-clobbered registers` |
| `conditional-scheduler-projected-outputs-v1` | `projected outputs require four ordered helpers and one scheduler` |
| `conditional-scheduler-descriptor-calls-v1`, `conditional-scheduler-descriptor-payload-calls-v1`, `conditional-scheduler-descriptor-payload8-calls-v1`, `conditional-scheduler-two-payload-calls-v1` (4) | `scheduler contract requires one actual scheduler call` |
| `conditional-scheduler-branch-descriptor-calls-v1`, `conditional-scheduler-following-call-v1`, `conditional-scheduler-eight-target-branches-v1` (3) | `scheduler branches exceed the explicit call-site or target bounds` |
| `conditional-scheduler-twenty-four-target-branches-v1`, `conditional-scheduler-three-per-path-calls-v1` | `ordinary branch calls exclude every live local alias and pointer word` |
| `conditional-scheduler-live-local-alias-calls-v1`, `conditional-scheduler-sequential-live-alias-counted-loops-v1`, `conditional-scheduler-three-per-path-live-alias-v1` (3) | `buffer callee 0x080DBDC8: unsupported buffer pointer use or escape` |
| `conditional-scheduler-live-local-alias-payload-calls-v1` | `scheduler payload contract requires one descriptor+4 word addressing the payload` |
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

The other 168 selector values give 49 other refusals, none of them a match; the most frequent are `owner requires sole complete Thumb ELF function` (32), `addressed data requires a mapped object and signed32 addend` (26), `addressed signed runtimes exclude data and irregular relocations` (13).

## Cause

Two calls receive local addresses: the coordinate wrapper and the scheduler. The function has named data and a function literal, so the default run takes the function-literal path, which has no buffer proof, and refuses the first crossing. The scheduler selectors refuse on the caller's shape, and the three live-alias selectors get as far as the wrapper and refuse its forwarding store (`buffer callee 0x080DBDC8: unsupported buffer pointer use or escape`). The stack-index selectors, the only proofs that admit a forwarded stack argument today (kit #183), get past the wrapper and stop in the scheduler at its `_call_via_r3` thunk. In the prototypes measured for the two kit issues below, the function needs both rules, the per-site scheduler summary and forwarded stack arguments in the generic buffer proof, and gives `MATCH - byte identical` with both (not re-run here).

## Source notes

- `x` and `y` are declared first, so they get the frame words the ROM uses (`sp + 0x14`, `sp + 0x16`); the request is declared in the block of phase 0x102.

kit issue: (to be filed - match.py: a scheduler call with a local descriptor verifies only under shape-bound owner selectors; a per-site summary admits 7 byte-identical functions alone and 14 with companion rules)
kit issue: (to be filed - match.py: forwarded callee stack arguments are admitted only under named-data-buffer-stack-index-v2; the generic buffer proofs refuse the 080DBDxx coordinate wrappers)
