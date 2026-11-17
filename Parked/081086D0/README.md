# 0x081086D0 - spawn callback: a stack copy of a 5-byte ROM table indexed by a count, and a looped scheduler call: bytes identical, refused (the initialiser's .rodata on the default path; under the stack-index selectors, the scheduler callback thunk) (932 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321 with the match batches then queued for merge (PRs #200 onward). This entry refreshes the earlier `Parked/081086D0/` (kit fcdf2d45) at kit 18dcc516; the source is unchanged
(same file). `u32 func_081086D0(task, descriptor, state)` is a phase callback with an eight-case switch on
`descriptor->phase` (0, 1, 0x100 to 0x105), registered by three function words at 0x08394BB0, 0x08394BB8 and
0x08394BC0 in the ROM callback table. Phase 0x101:

- copies the five-byte ROM table at 0x08149EDC (`00 28 1E 14 0A`) to the stack, written as the initialiser
  `u8 delays[5] = {0, 40, 30, 20, 10};`;
- stores the `u8` result of `func_080D8924` in `state->count` (the byte at `state + 8`) and reads
  `delays[state->count]`;
- in a `u8` loop over `i < state->count`, fills a 28-byte stack descriptor and calls
  `func_08005B6C(func_08108630, 0x10, &child, task)` at 0x081088CA, adding 10 to the delay each time.

## The index

`symbols/functions.txt` has `081086D0 08108A74 932 466 return` and `config/functions.json` the same extent with 466 instructions (`thumb-prologue`). The CFG, closed by the kit's own `analyze.refine_function`, has 393 reachable instructions, so the instruction column is the halfword count (466). No refusal below depends on it.

## Byte identity

`081086D0.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x081086D0, with every callee bound to its ROM address and every data word to the address its symbol names (34 `R_ARM_THM_CALL`, 14 `R_ARM_ABS32`); the five bytes of `.rodata` that the initialiser produces resolve to 0x08149EDC, where the ROM holds the same bytes (`00 28 1E 14 0A`), and the compiler's `memcpy` to 0x081443FC; the pool word that holds the table's address, at `0x08108908`, is the only aligned word in the ROM with that value. The 932-byte symbol equals the ROM span `[0x081086D0, 0x08108A74)`: SHA-256 `306a274ab996bec0de721a5550be2a71560b258b9df37bf24ba29adc22fd312d` for both. `.text` is exactly 932 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each is added with its address as the value (`"data_083A1038": "0x083A1038"`):

`data_083A1038`, `data_083A1050`, `data_083A1058`, `data_083A1070`, `data_083A1094`, `data_083A10AC`, `data_083A10C0`, `data_083A10C4`, `data_0894A26C`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/081086D0.c` and the data symbols above added: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, `--control-flow-profile mixed-return-inert-spin-v1`, `--signed-quotient-profile positive-constant-frame-v1` and 18 other selectors (21) | `unexpected nonempty allocated section` |
| `conditional-scheduler-projected-outputs-v1`, `conditional-scheduler-descriptor-calls-v1`, `conditional-scheduler-branch-descriptor-calls-v1` and 181 other selectors (184) | `unexpected nonempty allocated section` |
| `named-data-buffer-rom-table-copy-v1` | `unsupported stack-alias use or escape` |
| `named-data-buffer-stack-index-v1` and `named-data-buffer-stack-index-v2` (2) | `buffer callee 0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification` |

The other 6 selector values are not listed one by one (none matched); by family: switch-layout (3), arithmetic-runtime (1), -O0 (1), owner (1).

## With the table copy written as a call

Replacing the initialiser by `u8 delays[5];` and `func_081443FC(delays, data_08149EDC, sizeof(delays));` as the
first statement of the case gives the same 932 bytes (SHA-256 as above; it also needs `data_08149EDC`). The same run,
default and all 213 selector values, at kit 18dcc516:

| Selector | Refusal |
|---|---|
| default, `--signed-quotient-profile positive-constant-frame-v1` and `--unsigned-quotient-profile positive-constant-frame-v1` (3) | `stack aliases cannot cross calls in caller-clobbered registers` |
| `conditional-scheduler-descriptor-calls-v1`, `conditional-scheduler-descriptor-payload-calls-v1`, `conditional-scheduler-descriptor-payload8-calls-v1` and `conditional-scheduler-two-payload-calls-v1` (4) | `scheduler contract requires one actual scheduler call` |
| `conditional-scheduler-branch-descriptor-calls-v1`, `conditional-scheduler-following-call-v1`, `conditional-scheduler-eight-target-branches-v1` and 4 other scheduler selectors (7) | `scheduler branches exceed the explicit call-site or target bounds` |
| `conditional-scheduler-three-per-path-calls-v1`, `conditional-scheduler-sequential-leaf-output-calls-v1`, `conditional-scheduler-sequential-killed-alias-calls-v1` and `conditional-scheduler-guarded-descriptor-calls-v1` (4) | `predicate composition excludes CFG cycles` |
| `conditional-scheduler-u16-counted-loop-v1` | `counted scheduler loop requires a complete bounded instruction graph` |
| `conditional-scheduler-sequential-live-alias-counted-loops-v1` | `scheduler loop composition requires a complete bounded instruction graph` |
| `conditional-scheduler-three-per-path-live-alias-v1`, `named-data-buffer-v1`, `named-data-buffer-known-query-callee-v1` and 19 other selectors (22) | `buffer callee 0x081443FC: unsupported buffer pointer use or escape` |
| `conditional-scheduler-entry-descriptor-calls-v1` | `scheduler entry contract requires one actual pinned entry call` |
| `named-data-buffer-finite-small-copy-binding-v1` | `small-copy prefix excludes ordinary memory accesses` |
| `named-data-buffer-compiler-copy80-binding-v1` | `compiler copy requires exactly one memcpy call and named data only` |
| `named-data-buffer-rom-table-copy-v1` | `unsupported stack-alias use or escape` |
| `named-data-buffer-stack-index-v1` and `named-data-buffer-stack-index-v2` (2) | `buffer callee 0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification` |

6 more selectors of these families refuse on contracts for other shapes: `projected outputs require four ordered helpers and one scheduler` (`conditional-scheduler-projected-outputs-v1`); `halfword payload requires one exact output leaf and one scheduler site` (`conditional-scheduler-halfword-output-payload-v1`); `scheduler entry branches require exactly two pinned wrapper call sites` (`conditional-scheduler-entry-branch-descriptor-calls-v1`); `indirect manager contract requires one direct scheduler call` (`conditional-scheduler-indirect-manager-v1`); `manager offset contract requires one direct scheduler call` (`conditional-scheduler-manager-offset-v1`); `manager paths contract requires one direct scheduler call` (`conditional-scheduler-manager-paths-v1`).

The other 160 selector values are not listed one by one. None matched.

The function has 393 reachable instructions, more than the 256 that the two `requires a complete bounded
instruction graph` selectors allow.

## The stack index

```
081088A2  ldrb r1, [r4, #8]      @ state->count, stored at 0x081088A0 from func_080D8924's result
081088A4  adds r0, r5, r1
081088A6  ldrb r7, [r0]          @ delays[state->count]
```

The table has five bytes, so a stack-index profile needs a premise for the load at 0x081088A6: the byte read at
0x081088A2 is at most 4 (bound 5). That is not proven. `func_080D8924` returns 0 or a selection count kept at
`object + 0x2C0`, and the writers of that byte have not been traced. With the scheduler call-site summary prototyped,
the scheduler call-site issue and the #200 comment report that `named-data-buffer-stack-index-v2` takes this function past the
scheduler to the premise ledger.

## Source notes

- The file declares its own `extern u16 g_control_flags_03000940;`, as 91 sources on main do, instead of
  including `control_flags.h`. With the header and `.display` the bytes are the same and `plausible.py --strict` still
  exits 0, but a selector run then stops before its profile, at the allowlisted volatile semantic check, which says of
  the compiler's `bl memcpy`: `the callee has no prototype with a fixed argument list, so its arguments cannot be
  compared` (earlier attempt).
- The flag update of phase 0x101 goes through a `u16` temporary, the spelling of the matched `src/08108D9C.c` and
  `src/081072B0.c`. Written as `g_control_flags_03000940 |= func_080035A8(2);` the function is 930 bytes.
- `child` is declared before `delays`. The other order gives 936 bytes.
- The callback `func_08108630` is not matched.

kit issue: shubshub/fftadecomp-kit#200 (comment to be posted); (to be filed - match.py: a scheduler call with a local descriptor verifies only under shape-bound owner selectors; a per-site summary admits 7 byte-identical functions alone and 14 with companion rules) (under named-data-buffer-stack-index-v2, with the rule, the premise ledger is next)
