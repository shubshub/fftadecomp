# 0x080ECD8C - three-task effect phase callback (effect 0x31): bytes identical, refused (three scheduler calls with two local descriptors, plus local coordinate outputs through a Div-calling wrapper) (694 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `u32 func_080ECD8C(void *owner, Event080ECD8C *event, State080ECD8C *s)` is the phase callback of effect 0x31 in the table `data_083947D8` that `func_080D3508` reads (function word `0x080ECD8D` at `0x08394958`); no `bl` reaches it. Phase 0 records the mode and resource and, in mode 0, reads the resource's position into three local `s16` outputs through `func_080DBDEC(6, func_080DD47C(resource), &x, &y, &z)`, rounds `x - 120` and `y - 80` down to multiples of 8, and starts a child with `func_080E03F8(resource, data_083990C8, 3, 6, &position, owner)`, `position` being a local pair. Phase 0x101 starts two tasks with one local 28-byte descriptor (`func_080EC7DC` with a 0x1060-byte payload and `func_080EC6D8` with 0x94) and `func_080DFD8C(data_0839923C, 1, 4, 0, owner)`; 0x102 starts `func_080ECCDC` with a second local descriptor; 0x103 steps the first task through the 11 entries of `data_08399160`, then starts the script `func_080D3E9C(data_0894D710, owner)`; 0x104 ends the three tasks (`func_08005B58`), and the remaining phases wait for the script and a fade and run the ending through `func_080EDB98`/`func_080EDBDC`.

Locals: `x`, `y`, `z` at `sp + 8`, `sp + 0xA`, `sp + 0xC` (the third through the outgoing word), `position` at `sp + 0x48`, the descriptors at `sp + 0x10` and `sp + 0x2C`:

```
080ECECA  add  r4, sp, #0x10          @ descriptor, kept in R4
080ECED4  ldr  r0, =func_080EC7DC
080ECED6  movs r1, #0x83
080ECED8  lsls r1, r1, #5             @ 0x1060
080ECEDA  adds r2, r4, #0
080ECEDC  adds r3, r7, #0             @ owner
080ECEDE  bl   0x08005B6C
080ECEE4  ldr  r0, =func_080EC6D8
080ECEE6  movs r1, #0x94
080ECEE8  adds r2, r4, #0             @ same descriptor, R4 live across the first call
080ECEEC  bl   0x08005B6C
...
080ECF28  add  r2, sp, #0x2c          @ second descriptor
080ECF2E  bl   0x08005B6C
```

`func_080DBDEC` (200 bytes) computes the three coordinates and divides each with the Div wrapper `func_08141870` before storing them through the three pointers.

## The index

The index row `080ECD8C 080ED042 694 347 return` is right about the extent, but its instruction column is the halfword count (bytes/2), as is `config/functions.json`'s (347): the reachable CFG has 302 instructions (the kit's `analyze.refine_function` at 18dcc516 closes it over the indexed extent). Not corrected here: no draft needs it. The selectors that check the count against the CFG refuse on it (`restoring-owner-switch-aligned-v1`, `restoring-owner-switch-cycles-function-words-v1`: `complete-owner text reachable instruction count differs`).

## Byte identity

`080ECD8C.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080ECD8C, with every callee and data symbol bound to its ROM address (26 `R_ARM_THM_CALL`, 7 `R_ARM_ABS32`). The 694-byte symbol equals the ROM span `[0x080ECD8C, 0x080ED042)`: SHA-256 `5db9e2ff45c1799b86a52f0eaf20326be777a3dc5ad52fac3af43809a73d55a5` for both. `.text` is 696 bytes: the symbol and the assembler's 2-byte alignment padding. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each was added with its address as the value (`"data_083990C8": "0x083990C8"`) for the runs below: `data_083990C8`, `data_08399160`, `data_0839923C`, `data_0894D710`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080ECD8C.c` and the data symbols above: the default run and all 213 selector values. None matched. The default run prints the refusal after `compile failed:`, a selector run as `error (ValueError): <text>`.

| Selector | Refusal |
|---|---|
| default, and 2 other selector values | `stack aliases cannot cross calls in caller-clobbered registers` |
| `conditional-scheduler-projected-outputs-v1` | `projected outputs require four ordered helpers and one scheduler` |
| `conditional-scheduler-descriptor-calls-v1`, `conditional-scheduler-descriptor-payload-calls-v1`, `conditional-scheduler-descriptor-payload8-calls-v1`, `conditional-scheduler-two-payload-calls-v1` (4) | `scheduler contract requires one actual scheduler call` |
| `conditional-scheduler-branch-descriptor-calls-v1`, `conditional-scheduler-following-call-v1`, `conditional-scheduler-eight-target-branches-v1`, `conditional-scheduler-twenty-four-target-branches-v1`, `conditional-scheduler-live-local-alias-calls-v1`, `conditional-scheduler-live-local-alias-payload-calls-v1`, `conditional-scheduler-twenty-four-target-following-calls-v1` (7) | `scheduler branches exceed the explicit call-site or target bounds` |
| `conditional-scheduler-three-per-path-calls-v1` | `ordinary branch calls exclude every live local alias and pointer word` |
| `conditional-scheduler-sequential-leaf-output-calls-v1` | `scheduler leaf output excludes pointer-bearing slots` |
| `conditional-scheduler-sequential-killed-alias-calls-v1` | `alias kill requires an indexed ordinary call without pointer slots` |
| `conditional-scheduler-u16-counted-loop-v1` | `counted scheduler loop requires a complete bounded instruction graph` |
| `conditional-scheduler-sequential-live-alias-counted-loops-v1` | `scheduler loop composition requires a complete bounded instruction graph` |
| `conditional-scheduler-three-per-path-live-alias-v1` | `live-alias calls exclude pointer-bearing slots and word provenance` |
| `conditional-scheduler-guarded-descriptor-calls-v1` | `guarded scheduler requires predicates and exactly one scheduler site` |
| `conditional-scheduler-halfword-output-payload-v1` | `halfword payload requires one exact output leaf and one scheduler site` |
| `conditional-scheduler-entry-descriptor-calls-v1` | `scheduler entry contract requires one actual pinned entry call` |
| `conditional-scheduler-entry-branch-descriptor-calls-v1` | `scheduler entry branches require exactly two pinned wrapper call sites` |
| `conditional-scheduler-indirect-manager-v1` | `indirect manager contract requires one direct scheduler call` |
| `conditional-scheduler-manager-offset-v1` | `manager offset contract requires one direct scheduler call` |
| `conditional-scheduler-manager-paths-v1` | `manager paths contract requires one direct scheduler call` |
| `named-data-buffer-v1`, `bounded-buffer-guarded-bios-division-v1`, and 16 other selector values | `buffer callee 0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification` |
| `bounded-buffer-three-output-dynamic-division-v1` | `dynamic division requires a bounded complete ordinary DIV-only callee` |

The other 167 selector values give 50 other refusals, none of them a match; the most frequent are `owner requires sole complete Thumb ELF function` (32), `addressed data requires a mapped object and signed32 addend` (26), `addressed signed runtimes exclude data and irregular relocations` (13).

## Cause

The function has named data and function literals, so the default run takes the function-literal path, which has no buffer proof, and refuses the first local address that crosses a call (`stack aliases cannot cross calls in caller-clobbered registers`). The `conditional-scheduler-*` selectors bound the caller's shape: the 24-target and branch selectors count more call sites or targets than they allow, the three-per-path selectors refuse the local aliases that stay live across calls (the descriptor in R4 between the two scheduler calls; `position` and the coordinate outputs), and the loop selectors need a bounded instruction graph. The `named-data-buffer-*` and guarded-division selectors walk the first scheduler call and stop at the callback thunk inside `func_08005954`. With the per-site scheduler summary of the issue below, its prototype (not re-run here) stops this function at the Div wrapper reached inside `func_080DBDEC`, which is the scalar BIOS summary inside a walked callee asked for on kit #192.

## Source notes

- `second` in phase 0x102 is passed to the scheduler without being written: the ROM passes `sp + 0x2C` (`0x080ECF28`) and stores nothing there first.
- `x`, `y` and `z` are written by `func_080DBDEC`; `z` is not read again, as in the ROM.

kit issue: shubshub/fftadecomp-kit#237; shubshub/fftadecomp-kit#192 (comment)
