# 0x080F7160 - phase callback with coordinate outputs and one child task: bytes identical, refused (local s16 outputs forwarded by func_080DBDC8, and a scheduler descriptor) (334 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `u32 func_080F7160(void *task, Descriptor *descriptor, Payload *payload)` is a phase callback; its function word is in the table at `0x08394AF8`. Phase 0 starts a loader (`func_080E03F8` with the records `data_0839BAA8`). Phase 0x100 waits for it, gives up when `func_080D3B54(primary)` is set, and otherwise sets up the primary's entity (`func_080DD47C`, `func_080DE10C`, `func_080DE3BC`), reads its position into two local `s16` with `func_080DBDC8(entity, &x, &y)`, starts a coordinate effect (`func_080D6098(x, y, ..., &payload->unknown_10, data_0839BAF0, task)`) and a record task (`func_080DFD8C` with `data_0839BB08`), and waits 20 frames. Phase 0x101 then starts `func_080E4054` as a child with a 28-byte descriptor at `sp + 0x14` when `func_080D8858(primary, 0)` is non-zero; phase 0x102 waits for both tasks.

```
080F71F6  mov  r4, sp
080F71F8  adds r4, #0x12              @ &y, kept in R4 across the next two calls
080F71FA  add  r1, sp, #0x10          @ &x
080F71FC  adds r2, r4, #0
080F71FE  bl   0x080DBDC8
...
080F7262  add  r2, sp, #0x14          @ child descriptor
080F7264  movs r0, #0x65
080F7266  strh r0, [r2, #0x14]
...
080F7270  ldr  r0, =func_080E4054
080F7272  movs r1, #0x1c
080F7274  adds r3, r7, #0             @ task
080F7276  bl   0x08005B6C
```

## The index

The index row `080F7160 080F72AE 334 167 return` is right about the extent, but its instruction column is the halfword count (bytes/2), as is `config/functions.json`'s (167): the reachable CFG has 141 instructions (the kit's `analyze.refine_function` at 18dcc516 closes it over the indexed extent). Not corrected here: no draft needs it. The selectors that check the count against the CFG refuse on it (`restoring-owner-switch-aligned-v1`, `restoring-owner-switch-cycles-function-words-v1`: `complete-owner text reachable instruction count differs`).

## Byte identity

`080F7160.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080F7160, with every callee and data symbol bound to its ROM address (14 `R_ARM_THM_CALL`, 4 `R_ARM_ABS32`). The 334-byte symbol equals the ROM span `[0x080F7160, 0x080F72AE)`: SHA-256 `cc08984b33fb8f9d2b57d773081bc3429e59e0e5d2d28e299e9050e38941cde7` for both. `.text` is 336 bytes: the symbol and the assembler's 2-byte alignment padding. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each was added with its address as the value (`"data_0839BAA8": "0x0839BAA8"`) for the runs below: `data_0839BAA8`, `data_0839BAF0`, `data_0839BB08`. Each is the only aligned ROM word with its value, in this function's own pool (`0x080F71BC`, `0x080F7240`, `0x080F7244`), loaded as the record argument of `func_080E03F8`, `func_080D6098` and `func_080DFD8C`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080F7160.c` and the data symbols above: the default run and all 213 selector values. None matched. The default run prints the refusal after `compile failed:`, a selector run as `error (ValueError): <text>`.

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

Two calls receive local addresses: the coordinate wrapper `func_080DBDC8`, which stores `&y` into its own outgoing word for `func_0801C984`, and the scheduler. The function has named data and a function literal (`func_080E4054`), so the default run takes the function-literal path, which has no buffer proof and, with data relocations, no function-buffer fallback either, and refuses the first crossing. The scheduler selectors refuse on the caller's shape, and the three live-alias selectors get as far as the wrapper and refuse its forwarding store (`buffer callee 0x080DBDC8: unsupported buffer pointer use or escape`). The stack-index selectors admit the forwarding (kit #183) and stop in the scheduler. In the prototypes measured for the two kit issues below, the function needs both rules, the per-site scheduler summary and forwarded stack arguments, and gives `MATCH - byte identical` with both (not re-run here). That measurement used the raw-address copy (Source notes); with named data, as for `0x080F6A40`, a real rule also needs the buffer proof on the function-literal path with data (the separate issue on named data beside the buffer proof).

## Source notes

- An earlier copy wrote the three records as raw address casts (`(const void *)0x0839BAA8` and so on), with the same bytes and no data relocations; its default run added the function-buffer fallback (`stack aliases cannot cross calls in caller-clobbered registers; function-buffer proof: buffer callee 0x08005B6C: buffer callee 0x08005954: function-buffer evidence excludes runtime call thunks in inspected dependencies`), and 19 other selector values refused differently, none of them a scheduler, buffer or stack-index selector.
- `x` and `y` are declared in the block of phase 0x100, which gives the frame words the ROM uses (`sp + 0x10`, `sp + 0x12`).

kit issue: (to be filed - match.py: a scheduler call with a local descriptor verifies only under shape-bound owner selectors; a per-site summary admits 7 byte-identical functions alone and 14 with companion rules)
kit issue: (to be filed - match.py: forwarded callee stack arguments are admitted only under named-data-buffer-stack-index-v2; the generic buffer proofs refuse the 080DBDxx coordinate wrappers)
