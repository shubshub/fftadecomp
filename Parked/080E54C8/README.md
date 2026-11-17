# 0x080E54C8 - staged effect callback with child tasks: bytes identical, refused (three scheduler sites with stack descriptors and a slot-search loop) (460 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `u32 func_080E54C8(void *task, StagedEffectEvent *event, StagedEffectWork *work)` is a phase callback; its function word is in the table at `0x08394830`. Phase 0 starts a loader, `func_080E03F8(object, data_08396DDC, flag ? 0 : 5, 1, 0, task)`. Phase 0x100 waits for it; with the event's flag set it counts the targets (`func_080D8858(object, 0)`) and goes to 0x103, otherwise it starts `func_080E4EB0` as a child task and an effect from `data_0894ADAC` (`func_080D4704`). Phase 0x101 waits for the first child and starts `func_080E5310`; 0x102 waits for both and counts the targets. Phase 0x103 polls the four child slots (`func_080E0570`) and, every 30 frames, finds the first free slot in a short loop and starts `func_080E5438` for the next target in it. Phase 0x104 waits for all slots to finish. The three scheduler sites:

```
080E5578  ldr  r0, =func_080E4EB0     @ callback literal
080E557A  movs r1, #0x74              @ payload size
080E557C  add  r2, sp, #8             @ 28-byte descriptor
080E557E  mov  r3, r8                 @ parent
080E5580  bl   0x08005B6C
...
080E55AC  ldr  r0, =func_080E5310
080E55AE  add  r2, sp, #0x24
080E55B0  movs r1, #0x2c
080E55B2  mov  r3, r8
080E55B4  bl   0x08005B6C
...
080E5614  add  r6, sp, #0x40          @ spawn descriptor, kept in R6
...
080E5638  bl   0x080DD4A4             @ target object
080E563C  str  r0, [r6, #4]
080E563E  ldr  r0, =func_080E5438
080E5640  movs r1, #0x14
080E5642  adds r2, r6, #0
080E5644  mov  r3, r8
080E5646  bl   0x08005B6C
```

The slot search is the loop at `0x080E561E`-`0x080E5630`.

## The index

The index row `080E54C8 080E5694 460 230 return` is right about the extent, but its instruction column is the halfword count (bytes/2), as is `config/functions.json`'s (230): the reachable CFG has 194 instructions (the kit's `analyze.refine_function` at 18dcc516 closes it over the indexed extent). Not corrected here: no draft needs it. The selectors that check the count against the CFG refuse on it (`restoring-owner-scalar-switch-v1`, `restoring-owner-switch-entry-word-v1`, `restoring-owner-switch-entry-two-words-data-v1`, `restoring-owner-acyclic-v1` and 2 more: `complete-owner text reachable instruction count differs`).

## Byte identity

`080E54C8.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080E54C8, with every callee and data symbol bound to its ROM address (15 `R_ARM_THM_CALL`, 5 `R_ARM_ABS32`). The 460-byte symbol equals the ROM span `[0x080E54C8, 0x080E5694)`: SHA-256 `12131afb5ab526d987219084bc357eca524ab5f34751323d6226601d99406403` for both. `.text` is exactly 460 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each was added with its address as the value (`"data_08396DDC": "0x08396DDC"`) for the runs below: `data_08396DDC`, `data_0894ADAC`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080E54C8.c` and the data symbols above: the default run and all 213 selector values. None matched. The default run prints the refusal after `compile failed:`, a selector run as `error (ValueError): <text>`.

| Selector | Refusal |
|---|---|
| default, and 2 other selector values | `stack aliases cannot cross calls in caller-clobbered registers` |
| `conditional-scheduler-projected-outputs-v1` | `projected outputs require four ordered helpers and one scheduler` |
| `conditional-scheduler-descriptor-calls-v1`, `conditional-scheduler-descriptor-payload-calls-v1`, `conditional-scheduler-descriptor-payload8-calls-v1`, `conditional-scheduler-two-payload-calls-v1` (4) | `scheduler contract requires one actual scheduler call` |
| `conditional-scheduler-branch-descriptor-calls-v1`, `conditional-scheduler-following-call-v1`, `conditional-scheduler-eight-target-branches-v1`, `conditional-scheduler-twenty-four-target-branches-v1`, `conditional-scheduler-live-local-alias-calls-v1`, `conditional-scheduler-live-local-alias-payload-calls-v1`, `conditional-scheduler-twenty-four-target-following-calls-v1` (7) | `scheduler branches exceed the explicit call-site or target bounds` |
| `conditional-scheduler-three-per-path-calls-v1`, `conditional-scheduler-sequential-leaf-output-calls-v1`, `conditional-scheduler-sequential-killed-alias-calls-v1` (3) | `predicate composition excludes CFG cycles` |
| `conditional-scheduler-u16-counted-loop-v1` | `counted scheduler latch must use unsigned strict less-than` |
| `conditional-scheduler-sequential-live-alias-counted-loops-v1`, `conditional-scheduler-three-per-path-live-alias-v1` | `counted loop latch must be an unsigned lower or lower-or-same branch` |
| `conditional-scheduler-guarded-descriptor-calls-v1` | `guarded scheduler requires predicates and exactly one scheduler site` |
| `conditional-scheduler-halfword-output-payload-v1` | `halfword payload requires one exact output leaf and one scheduler site` |
| `conditional-scheduler-entry-descriptor-calls-v1` | `scheduler entry contract requires one actual pinned entry call` |
| `conditional-scheduler-entry-branch-descriptor-calls-v1` | `scheduler entry branches require exactly two pinned wrapper call sites` |
| `conditional-scheduler-indirect-manager-v1` | `indirect manager contract requires one direct scheduler call` |
| `conditional-scheduler-manager-offset-v1` | `manager offset contract requires one direct scheduler call` |
| `conditional-scheduler-manager-paths-v1` | `manager paths contract requires one direct scheduler call` |

The other 186 selector values give 58 other refusals, none of them a match; the most frequent are `addressed data requires a mapped object and signed32 addend` (26), `buffer callee 0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification` (18), `private float requires unique undefined pinned helper symbols` (15).

## Cause

The function has named data and callback literals, so the default run takes the function-literal path, which has no buffer proof, and refuses the first descriptor address that crosses a call. The 25 `conditional-scheduler-*` selectors each bound the whole caller: the branch selectors allow at most two scheduler sites (here three), the one-call selectors exactly one call, and the predicate and loop compositions exclude the slot-search loop or want a different latch. The per-site obligations are met at each of the three calls on their own: each passes one descriptor in R2, and the only other local alias at a call is R6, the third descriptor itself, at `0x080E5646`. In the prototype measured for the kit issue below, the descriptor contract applied as a per-site summary admits this function with no other change (not re-run here).

## Source notes

- The first two descriptors are passed without being written: the ROM forms `sp + 8` and `sp + 0x24` and stores nothing there in this function. The source declares them as two 28-byte locals (`BlankDescriptor first, second`), which is what the frame shows; nothing in the ROM says what the original wrote into them.
- `slot` is a `u8` (`lsls #0x18; lsrs #0x18` at `0x080E5620`), and the search is a `do`/`while` guarded by the first slot's test, as the ROM orders it.

kit issue: shubshub/fftadecomp-kit#237
