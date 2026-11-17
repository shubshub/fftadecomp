# 0x080F41C8 - three-child effect phase callback (effect 0x55): bytes identical, refused (a 3-byte ROM table copied to the stack and indexed in a loop of scheduler calls whose descriptor points at another local) (646 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `u32 func_080F41C8(void *task, Request080F41C8 *request, Payload080F41C8 *payload)` is the phase callback of effect 0x55 in the table `data_083947D8` that `func_080D3508` reads (function word `0x080F41C9` at `0x08394A78`); no `bl` reaches it. Phase 0 starts a first child with `func_080E03F8(object, data_0839AF60, mode, 0, 0, task)`; 0x100 waits for it and either counts the targets (`func_080D8858`) or starts the script `func_080DDF68(..., data_0839B01C, ...)`. Phase 0x101 copies the 3-byte table `data_08149D10` (`10 1C 28`) to the local `kinds` with `func_081443FC` and, once the script is ready, reads the resource's position (`func_080DBDC8`), starts a coordinate task (`func_080D6098(..., data_0839AF90, task)`), packs the position into the local word `position` and, in a loop over `i < 3`, starts `func_080F3F7C` three times through `func_08005B6C` with one local 28-byte descriptor whose +4 word is `&position` and whose kind is `kinds[i]`; then `func_080D4724(data_08949F18, task, 0x10)` and `func_080DFD8C(data_0839B024, 1, 4, 0, task)`. 0x102 waits for those, 0x103 starts one `func_080F40DC` pair task per target every 50 frames with a second local descriptor, 0x104 waits for the end.

```
080F42B4  add  r4, sp, #0x30          @ kinds
080F42B6  ldr  r1, =data_08149D10
080F42B8  adds r0, r4, #0
080F42BA  movs r2, #3
080F42BC  bl   0x081443FC
...
080F4304  str  r0, [sp, #0x50]        @ position
080F4306  add  r0, sp, #0x50
080F4308  str  r0, [sp, #0x18]        @ descriptor +4 = &position
080F430A  movs r5, #0                 @ i
080F4314  mov  r1, sl                 @ kinds
080F4316  adds r0, r1, r5
080F4318  ldrb r0, [r0]               @ kinds[i]
080F431A  strh r0, [r4, #0x14]
080F431E  ldr  r0, =func_080F3F7C
080F4320  movs r1, #0x1c
080F4322  add  r2, sp, #0x14          @ descriptor
080F4326  bl   0x08005B6C
```

The literal at `0x080F4360` is the only aligned ROM word with the table's address.

## The index

The index row `080F41C8 080F444E 646 323 return` is right about the extent, but its instruction column is the halfword count (bytes/2), as is `config/functions.json`'s (323): the reachable CFG has 278 instructions (the kit's `analyze.refine_function` at 18dcc516 closes it over the indexed extent). Not corrected here: no draft needs it. The selectors that check the count against the CFG refuse on it (`restoring-owner-switch-aligned-v1`, `restoring-owner-switch-cycles-function-words-v1`: `complete-owner text reachable instruction count differs`).

## Byte identity

`080F41C8.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080F41C8, with every callee and data symbol bound to its ROM address (20 `R_ARM_THM_CALL`, 8 `R_ARM_ABS32`). The 646-byte symbol equals the ROM span `[0x080F41C8, 0x080F444E)`: SHA-256 `c3ccfea3075a3aaf8c7dbaa198f19629412bc0baf061537ce7a1f9a95c4d3521` for both. `.text` is 648 bytes: the symbol and the assembler's 2-byte alignment padding. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each was added with its address as the value (`"data_08149D10": "0x08149D10"`) for the runs below: `data_08149D10`, `data_0839AF60`, `data_0839AF90`, `data_0839B01C`, `data_0839B024`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080F41C8.c` and the data symbols above: the default run and all 213 selector values. None matched. The default run prints the refusal after `compile failed:`, a selector run as `error (ValueError): <text>`.

| Selector | Refusal |
|---|---|
| default, and 2 other selector values | `stack aliases cannot cross calls in caller-clobbered registers` |
| `conditional-scheduler-projected-outputs-v1` | `projected outputs require four ordered helpers and one scheduler` |
| `conditional-scheduler-descriptor-calls-v1`, `conditional-scheduler-descriptor-payload-calls-v1`, `conditional-scheduler-descriptor-payload8-calls-v1`, `conditional-scheduler-two-payload-calls-v1` (4) | `scheduler contract requires one actual scheduler call` |
| `conditional-scheduler-branch-descriptor-calls-v1`, `conditional-scheduler-following-call-v1`, `conditional-scheduler-eight-target-branches-v1` (3) | `scheduler branches exceed the explicit call-site or target bounds` |
| `conditional-scheduler-twenty-four-target-branches-v1`, `conditional-scheduler-live-local-alias-calls-v1`, `conditional-scheduler-live-local-alias-payload-calls-v1`, `conditional-scheduler-twenty-four-target-following-calls-v1`, `conditional-scheduler-three-per-path-calls-v1`, `conditional-scheduler-sequential-leaf-output-calls-v1`, `conditional-scheduler-sequential-killed-alias-calls-v1` (7) | `predicate composition excludes CFG cycles` |
| `conditional-scheduler-u16-counted-loop-v1` | `counted scheduler loop requires a complete bounded instruction graph` |
| `conditional-scheduler-sequential-live-alias-counted-loops-v1` | `scheduler loop composition requires a complete bounded instruction graph` |
| `conditional-scheduler-three-per-path-live-alias-v1` | `buffer callee 0x081443FC: unsupported buffer pointer use or escape` |
| `conditional-scheduler-guarded-descriptor-calls-v1` | `guarded scheduler requires predicates and exactly one scheduler site` |
| `conditional-scheduler-halfword-output-payload-v1` | `halfword payload requires one exact output leaf and one scheduler site` |
| `conditional-scheduler-entry-descriptor-calls-v1` | `scheduler entry contract requires one actual pinned entry call` |
| `conditional-scheduler-entry-branch-descriptor-calls-v1` | `scheduler entry branches require exactly two pinned wrapper call sites` |
| `conditional-scheduler-indirect-manager-v1` | `indirect manager contract requires one direct scheduler call` |
| `conditional-scheduler-manager-offset-v1` | `manager offset contract requires one direct scheduler call` |
| `conditional-scheduler-manager-paths-v1` | `manager paths contract requires one direct scheduler call` |
| `named-data-buffer-stack-index-v1`, `named-data-buffer-stack-index-v2`, `named-data-buffer-rom-table-copy-v1` (3), and 15 other selector values | `buffer callee 0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification` |

The other 168 selector values give 50 other refusals, none of them a match; the most frequent are `owner requires sole complete Thumb ELF function` (32), `addressed data requires a mapped object and signed32 addend` (26), `addressed signed runtimes exclude data and irregular relocations` (13).

## Cause

The function has named data and function literals, so the default run takes the function-literal path and refuses the first crossing local address (`stack aliases cannot cross calls in caller-clobbered registers`). Under both stack-index selectors and `named-data-buffer-rom-table-copy-v1`, which summarise the copy, the walk follows the descriptor into the scheduler and stops at its callback thunk (`buffer callee 0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification`), the refusal of kit #200's first item. The scheduler selectors refuse the loop (`predicate composition excludes CFG cycles`, `... requires a complete bounded instruction graph`) or, for `conditional-scheduler-three-per-path-live-alias-v1`, the copy itself (`buffer callee 0x081443FC: unsupported buffer pointer use or escape`). With the per-site scheduler summary in the prototype measured for the issue and comment below (not re-run here), `named-data-buffer-stack-index-v2` then refuses `variable stack indices exclude pointer-bearing or return-carrying local words`: the descriptor holds `&position` while `kinds[i]` is read with a variable index.

## Source notes

- The position packing goes through a block-local `u32 high = (u16)payload->y << 16;` before `position = (u16)payload->x | high;`. Without the temporary, as one expression, 5 halfwords differ: the ROM loads and shifts `y` (`0x080F42FC`) before it loads `x`. The temporary's only evidence is that order, so a reviewer may count it as steering.
- `u8 slot = payload->pairs[0] != 0;` in phase 0x103 is load-bearing: indexing with the comparison directly gives 650 bytes (93 halfwords differ).
- The table copy runs on every frame of phase 0x101, before the ready test, as in the ROM.

kit issue: (to be filed - match.py: a scheduler call with a local descriptor verifies only under shape-bound owner selectors; a per-site summary admits 7 byte-identical functions alone and 14 with companion rules); shubshub/fftadecomp-kit#200 (comment to be posted)
