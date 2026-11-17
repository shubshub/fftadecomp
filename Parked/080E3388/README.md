# 0x080E3388 - BG3 effect phase callback (effects 0x164 and 0x165): bytes identical, refused (two local halfword outputs passed to func_080DC224, whose callee chain reaches a jump table and then the scheduler) (580 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `u32 func_080E3388(void *parent, EffectTask *task, EffectState *state)` is the phase callback of effects 0x164 and 0x165 in the table `data_08395280` that `func_080D3508` reads (function words at `0x083952F0` and `0x083952F8`); no `bl` reaches it, and effect 0x165 sets `state->special`. Phase 0x100 waits for `func_080DE488` and starts `func_080D7A70(data_083960A8, 2, parent)`; 0x101 waits for it and starts a VRAM loader (`func_080DC1E8`, `0x0600F9E0` to `0x06005000`); 0x102 waits for the loader, sets the BG3 control word, enables BG3 in `g_control_flags_03000940`, reads the object's position into the payload (`func_080DBDC8(object, &state->x, &state->y)`), converts it into two local `s16` outputs and writes them as the BG3 offsets, then starts the script `func_080D3E9C(data_083960F8, parent)`, for effect 0x165 a particle task (`func_080D6098`), and `func_080DFD8C(data_0839610C, 1, 4, 0, parent)`. 0x103 and 0x104 run the second script (`data_08396102`) and the particle task for effect 0x164, wait for both and disable BG3.

The locals are the pair at `sp + 0x10` and `sp + 0x12`:

```
080E34A0  mov  r4, sp
080E34A2  adds r4, #0x12              @ &y, kept in R4
080E34A4  str  r4, [sp]               @ fifth argument
080E34A6  add  r3, sp, #0x10          @ &x
080E34A8  bl   0x080DC224
080E34AC  add  r0, sp, #0x10
...
080E34BA  ldrsh r0, [r4, r2]          @ y, after the call to func_08003508
...
080E34C6  bl   0x080D3E9C             @ R4 still holds sp + 0x12
```

`func_080DC224` (68 bytes) stores `16 - x` through R3 and `48 - y` through its fifth argument, keeps that pointer in R4 across `bl 0x080DD6E0`, and subtracts 4 from it when the result is 0x51. `func_080DD6E0` reaches the jump table of `func_080C7EA4`.

## The index

The index row `080E3388 080E35CC 580 290 return` is right about the extent, but its instruction column is the halfword count (bytes/2), as is `config/functions.json`'s (290): the reachable CFG has 232 instructions (the kit's `analyze.refine_function` at 18dcc516 closes it over the indexed extent). Not corrected here: no draft needs it. The selectors that check the count against the CFG refuse on it (`restoring-owner-scalar-switch-v1`, `restoring-owner-switch-entry-word-v1`, `restoring-owner-switch-entry-two-words-data-v1`, `restoring-owner-acyclic-v1` and 2 more: `complete-owner text reachable instruction count differs`).

## Byte identity

`080E3388.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080E3388, with every callee and data symbol bound to its ROM address (26 `R_ARM_THM_CALL`, 8 `R_ARM_ABS32`). The 580-byte symbol equals the ROM span `[0x080E3388, 0x080E35CC)`: SHA-256 `eb9af75a910cba5c040b3541f7d0a197373c25d740fe3cb591c9a3f9c0c6f787` for both. `.text` is exactly 580 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each was added with its address as the value (`"data_083960A8": "0x083960A8"`) for the runs below: `data_083960A8`, `data_083960F0`, `data_083960F8`, `data_08396102`, `data_0839610C`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080E3388.c` and the data symbols above: the default run and all 213 selector values. None matched. The default run prints the refusal after `compile failed:`, a selector run as `error (ValueError): <text>`.

| Selector | Refusal |
|---|---|
| default, `named-data-buffer-v1`, `bounded-buffer-direct-halfword-output-v1` (3), and 14 other selector values | `buffer callee 0x080DC224: buffer callee 0x080DD6E0: buffer callee 0x080C7EA4: unresolved program-counter write` |
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
| `bounded-buffer-guarded-switch-v1` | `buffer callee 0x080DC224: consumer observes discarded return scratch before a killing write` |
| `bounded-buffer-root-guarded-switch-v1` | `root buffer requires one exact guarded switch and ordinary calls` |
| `bounded-buffer-nested-halfword-output-selective-scratch-v1`, `bounded-buffer-guarded-callee-aliases-v1`, `bounded-buffer-guarded-bios-division-v1` (3) | `buffer callee 0x080D3E9C: buffer callee 0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification` |
| `descriptor-single-store-v1`, and 5 other selector values | `buffer callee 0x080D6098: buffer callee 0x08005B6C: descriptor call does not prove preservation of a live alias register` |

The other 161 selector values give 54 other refusals, none of them a match; the most frequent are `addressed runtime ELF requires actual addressed calls and no unresolved symbols` (29), `private float requires unique undefined pinned helper symbols` (15), `addressed signed runtimes exclude data and irregular relocations` (13).

## Cause

The default run walks `&y` into `func_080DC224`, then into `func_080DD6E0` and `func_080C7EA4`, and refuses at that callee's `mov pc` dispatch (`unresolved program-counter write`), the case of the switch-callee issue below. Three selectors whose proofs handle the walk differently get past that chain today and stop where the switch-callee prototype stops (not re-run here): `bounded-buffer-nested-halfword-output-selective-scratch-v1`, `bounded-buffer-guarded-callee-aliases-v1` and `bounded-buffer-guarded-bios-division-v1` refuse at the scheduler inside `func_080D3E9C`, which the walk enters because R4 still holds `&y` at that call: `buffer callee 0x080D3E9C: buffer callee 0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification`. The scheduler issue's per-site summary applies only to the owner's own scheduler calls, so it does not reach this one, as that issue says. The 25 `conditional-scheduler-*` selectors refuse on the caller's shape (it makes no `func_08005B6C` call of its own), and `bounded-buffer-guarded-switch-v1` stops in `func_080DC224` (`consumer observes discarded return scratch before a killing write`).

## Source notes

- The file declares its own `extern u16 g_control_flags_03000940;` and updates it through a `u16` temporary (`flags |= mask;`), as other sources on main write the display-control update.
- `special` selects the particle table entry (`data_083960F0[state->special]`) and which phase starts the particle task; both paths are in the ROM.

kit issue: (to be filed - match.py: the generic buffer walk cannot inspect a callee that contains a jump table (`buffer callee 0x...: unresolved program-counter write`), although two buffer proofs already decode the layout); (to be filed - match.py: a scheduler call with a local descriptor verifies only under shape-bound owner selectors; a per-site summary admits 7 byte-identical functions alone and 14 with companion rules)
