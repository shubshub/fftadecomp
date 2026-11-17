# 0x080F7F70 - phase callback with a stack-indexed ROM table copy and a looped scheduler call: bytes identical, refused (no selector admits a stack-indexed ROM table copy together with a looped func_08005B6C call) (924 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `u32 func_080F7F70(void *task, Descriptor *descriptor, Payload *payload)` is a phase callback (function word in the table at `0x08394B28`) with an eight-case switch on `descriptor->phase` (0, 1, 0x100-0x105). Phase 0x101:

- copies the five-byte ROM table at `0x08149D5C` (`00 28 1E 14 0A`) to the stack with `func_081443FC`;
- stores the `u8` result of `func_080D8924` in `payload->count` (the byte at `payload + 8`) and reads `delays[payload->count]`;
- in a `u8` loop over `i < payload->count`, fills a 28-byte stack descriptor at `sp + 0x14` and calls `func_08005B6C(func_080F7EC0, 0x20, &child, task)` at `0x080F815C`, adding 10 to the delay each time.

```
080F8138  ldrb r1, [r4, #8]      @ payload->count, stored at 0x080F8136 from func_080D8924's result
080F813A  adds r0, r5, r1
080F813C  ldrb r6, [r0]          @ delays[payload->count]
```

The table has five bytes, so a stack-index profile needs a premise for the load at `0x080F813C`: the byte read at `0x080F8138` is at most 4 (bound 5). That is not proven: `func_080D8924` (parked, see `Parked/080D8924/`) returns `func_080D8858`'s count on one path, the result of `func_080DD494` on another and 0 on the third, and none of them has been bounded.

## The index

The index row `080F7F70 080F830C 924 462 return` is right about the extent, but its instruction column is the halfword count (bytes/2), as is `config/functions.json`'s (462): the reachable CFG has 387 instructions (the kit's `analyze.refine_function` at 18dcc516 closes it over the indexed extent). Not corrected here: no draft needs it. The selectors that check the count against the CFG refuse on it (`restoring-owner-scalar-switch-v1`, `restoring-owner-switch-entry-word-v1`, `restoring-owner-switch-entry-two-words-data-v1`, `restoring-owner-acyclic-v1` and 2 more: `complete-owner text reachable instruction count differs`).

## Byte identity

`080F7F70.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080F7F70, with every callee and data symbol bound to its ROM address (33 `R_ARM_THM_CALL`, 14 `R_ARM_ABS32`). The 924-byte symbol equals the ROM span `[0x080F7F70, 0x080F830C)`: SHA-256 `eab34501817a6b139ec23df63650c29e82889ae8f3c8c96602aee8f4b7d8b786` for both. `.text` is exactly 924 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

This entry refreshes the README of `Parked/080F7F70/` (2026-11-16, kit fcdf2d45); the source is unchanged. The refusals that README quoted reproduce at 18dcc516. It also recorded that `u8 delays[5] = {0, 40, 30, 20, 10};` in a block of the case gives the same 924 bytes, with the table emitted as `.rodata` and a `memcpy` call; the default run and `conditional-scheduler-three-per-path-live-alias-v1` then refuse with `unexpected nonempty allocated section`, and `named-data-buffer-stack-index-v2` and `named-data-buffer-rom-table-copy-v1` as below (kit fcdf2d45, not re-run).

## Data symbols

Not in `config/data_symbols.json` on main; each was added with its address as the value (`"data_08149D5C": "0x08149D5C"`) for the runs below: `data_08149D5C`, `data_0839BE74`, `data_0839BE7C`, `data_0839BEB0`, `data_0839BEB8`, `data_0839BEBC`, `data_0839BED0`, `data_0839BED4`, `data_0894A370`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080F7F70.c` and the data symbols above: the default run and all 213 selector values. None matched. The default run prints the refusal after `compile failed:`, a selector run as `error (ValueError): <text>`.

| Selector | Refusal |
|---|---|
| default, and 2 other selector values | `stack aliases cannot cross calls in caller-clobbered registers` |
| `conditional-scheduler-projected-outputs-v1` | `projected outputs require four ordered helpers and one scheduler` |
| `conditional-scheduler-descriptor-calls-v1`, `conditional-scheduler-descriptor-payload-calls-v1`, `conditional-scheduler-descriptor-payload8-calls-v1`, `conditional-scheduler-two-payload-calls-v1` (4) | `scheduler contract requires one actual scheduler call` |
| `conditional-scheduler-branch-descriptor-calls-v1`, `conditional-scheduler-following-call-v1`, `conditional-scheduler-eight-target-branches-v1`, `conditional-scheduler-twenty-four-target-branches-v1`, `conditional-scheduler-live-local-alias-calls-v1`, `conditional-scheduler-live-local-alias-payload-calls-v1`, `conditional-scheduler-twenty-four-target-following-calls-v1` (7) | `scheduler branches exceed the explicit call-site or target bounds` |
| `conditional-scheduler-three-per-path-calls-v1`, `conditional-scheduler-sequential-leaf-output-calls-v1`, `conditional-scheduler-sequential-killed-alias-calls-v1`, `conditional-scheduler-guarded-descriptor-calls-v1` (4) | `predicate composition excludes CFG cycles` |
| `conditional-scheduler-u16-counted-loop-v1` | `counted scheduler loop requires a complete bounded instruction graph` |
| `conditional-scheduler-sequential-live-alias-counted-loops-v1` | `scheduler loop composition requires a complete bounded instruction graph` |
| `conditional-scheduler-three-per-path-live-alias-v1`, and 21 other selector values | `buffer callee 0x081443FC: unsupported buffer pointer use or escape` |
| `conditional-scheduler-halfword-output-payload-v1` | `halfword payload requires one exact output leaf and one scheduler site` |
| `conditional-scheduler-entry-descriptor-calls-v1` | `scheduler entry contract requires one actual pinned entry call` |
| `conditional-scheduler-entry-branch-descriptor-calls-v1` | `scheduler entry branches require exactly two pinned wrapper call sites` |
| `conditional-scheduler-indirect-manager-v1` | `indirect manager contract requires one direct scheduler call` |
| `conditional-scheduler-manager-offset-v1` | `manager offset contract requires one direct scheduler call` |
| `conditional-scheduler-manager-paths-v1` | `manager paths contract requires one direct scheduler call` |
| `named-data-buffer-stack-index-v1`, `named-data-buffer-stack-index-v2` | `buffer callee 0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification` |
| `named-data-buffer-rom-table-copy-v1` | `unsupported stack-alias use or escape` |

The other 162 selector values give 53 other refusals, none of them a match; the most frequent are `addressed data requires a mapped object and signed32 addend` (26), `private float requires unique undefined pinned helper symbols` (15), `addressed signed runtimes exclude data and irregular relocations` (13).

## Cause

The default run refuses the descriptor address crossing the scheduler call. The stack-index selectors, which own the table copy and the variable index, follow `&child` into the scheduler: `0x08005B6C` calls `0x08005954`, which calls the callback through `_call_via_r3` at `0x08142250`, and the walk stops there. `named-data-buffer-rom-table-copy-v1` refuses the stack aliases beyond its copy. The live-alias scheduler selector stops at the table copy, where the address of `delays` is passed to `func_081443FC`; the counted-loop scheduler selectors allow 256 instructions and this function has 387 reachable ones, 33 call sites and 28 ordinary call targets. So the function needs the descriptor contract inside the stack-index walk (kit #200, item 1), and then a proven bound for the index. In the prototype measured for the scheduler issue below, the per-site rule takes it past the scheduler under `named-data-buffer-stack-index-v2` to the premise ledger, where it then needs that bound (not re-run here).

## Source notes

- The table copy is written as a call, `func_081443FC(delays, data_08149D5C, sizeof(delays));`. The literal at `0x080F8188` is the only aligned word in the ROM with the table's address.
- The file declares its own `extern u16 g_control_flags_03000940;`, as many sources on main do, instead of including `control_flags.h`. With the header and `.display` the bytes are the same and `plausible.py --strict` still exits 0, but a selector run (checked with `named-data-buffer-stack-index-v2` and `conditional-scheduler-three-per-path-live-alias-v1`) then stops before its profile at the allowlisted volatile semantic check: `more than 32 unknown branch conditions on one path (loops with unknown exit conditions are not modelled)` (kit #137; measured at fcdf2d45).
- The flag update of phase 0x101 goes through a `u16` temporary, the spelling of the matched `src/08108D9C.c` and `src/081072B0.c`. Written as `g_control_flags_03000940 |= func_080035A8(2);` the function is 922 bytes.
- `parity` in phase 0x104 is `u32`. With `u8`, as the matched `src/080FFEC0.c` has it, the function is 924 bytes of which 14 differ.

kit issue: shubshub/fftadecomp-kit#200 (comment to be posted)
kit issue: (to be filed - match.py: a scheduler call with a local descriptor verifies only under shape-bound owner selectors; a per-site summary admits 7 byte-identical functions alone and 14 with companion rules)
