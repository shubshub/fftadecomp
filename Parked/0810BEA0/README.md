# 0x0810BEA0 - spawn callback: a stack copy of a 3-byte ROM table and a looped scheduler call: bytes identical, refused (the initialiser's .rodata on the default path; under the stack-index selectors, the forwarding wrapper or the scheduler callback thunk) (932 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321 with the match batches then queued for merge (PRs #200 onward). This entry refreshes the earlier `Parked/0810BEA0/` (kit fcdf2d45) at kit 18dcc516; the source is unchanged
(same file). `u32 func_0810BEA0(task, descriptor, payload)` is a phase callback with an eight-case switch on
`descriptor->phase` (0, 1, 0x100 to 0x105), registered by its function word at 0x083950E8 in the ROM callback table.
Phase 0x101:

- copies the three-byte ROM table at 0x08149F20 (`06 00 0C`) to the stack, written as the initialiser
  `u8 delays[3] = {6, 0, 12};`;
- passes the addresses of local `s16` values to `func_080DBDC8` and, twice, to `func_080DBDA0`;
- in a `u8` loop over 0..2, fills a 28-byte stack descriptor with `delay = delays[i]` and calls
  `func_08005B6C(func_0810BB70, 0xCC, &child, task)` at 0x0810C05C (the child is `0x0810BB70`).

Phase 0x103 has a second counted loop, with no call in it.

## The index

`symbols/functions.txt` has `0810BEA0 0810C244 932 466 return` and `config/functions.json` the same extent with 466 instructions (`thumb-prologue`). The CFG, closed by the kit's own `analyze.refine_function`, has 404 reachable instructions, so the instruction column is the halfword count (466). No refusal below depends on it.

## Byte identity

`0810BEA0.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0810BEA0, with every callee bound to its ROM address and every data word to the address its symbol names (32 `R_ARM_THM_CALL`, 10 `R_ARM_ABS32`); the three bytes of `.rodata` that the initialiser produces resolve to 0x08149F20, where the ROM holds the same bytes (`06 00 0C`), and the compiler's `memcpy` to 0x081443FC; the pool word that holds the table's address, at `0x0810C080`, is the only aligned word in the ROM with that value. The 932-byte symbol equals the ROM span `[0x0810BEA0, 0x0810C244)`: SHA-256 `0fd35614b7ff66cea882cdfc740e8fad9e56c2c3fac7c41600d91279902154be` for both. `.text` is exactly 932 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each is added with its address as the value (`"data_083A2218": "0x083A2218"`):

`data_083A2218`, `data_083A2260`, `data_083A2290`, `data_083A22C0`, `data_083A22C4`, `data_083A22C8`, `data_083A22D0`, `data_083A22D8`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0810BEA0.c` and the data symbols above added: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, `--control-flow-profile mixed-return-inert-spin-v1`, `--signed-quotient-profile positive-constant-frame-v1` and 18 other selectors (21) | `unexpected nonempty allocated section` |
| `conditional-scheduler-projected-outputs-v1`, `conditional-scheduler-descriptor-calls-v1`, `conditional-scheduler-branch-descriptor-calls-v1` and 181 other selectors (184) | `unexpected nonempty allocated section` |
| `named-data-buffer-rom-table-copy-v1` and `named-data-buffer-stack-index-v1` (2) | `buffer callee 0x080DBDC8: unsupported buffer pointer use or escape` |
| `named-data-buffer-stack-index-v2` | `buffer callee 0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification` |

The other 6 selector values are not listed one by one (none matched); by family: switch-layout (3), arithmetic-runtime (1), -O0 (1), owner (1).

## With the table copy written as a call

Replacing the initialiser by `u8 delays[3];` and `func_081443FC(delays, data_08149F20, sizeof(delays));` as the
first statement of the case gives the same 932 bytes (it also needs `data_08149F20`). The same run, default and all
213 selector values, at kit 18dcc516:

| Selector | Refusal |
|---|---|
| default, `--signed-quotient-profile positive-constant-frame-v1` and `--unsigned-quotient-profile positive-constant-frame-v1` (3) | `stack aliases cannot cross calls in caller-clobbered registers` |
| `conditional-scheduler-descriptor-calls-v1`, `conditional-scheduler-descriptor-payload-calls-v1`, `conditional-scheduler-descriptor-payload8-calls-v1` and `conditional-scheduler-two-payload-calls-v1` (4) | `scheduler contract requires one actual scheduler call` |
| `conditional-scheduler-branch-descriptor-calls-v1`, `conditional-scheduler-following-call-v1`, `conditional-scheduler-eight-target-branches-v1` and 4 other scheduler selectors (7) | `scheduler branches exceed the explicit call-site or target bounds` |
| `conditional-scheduler-three-per-path-calls-v1`, `conditional-scheduler-sequential-leaf-output-calls-v1`, `conditional-scheduler-sequential-killed-alias-calls-v1` and `conditional-scheduler-guarded-descriptor-calls-v1` (4) | `predicate composition excludes CFG cycles` |
| `conditional-scheduler-u16-counted-loop-v1` | `counted scheduler loop requires a complete bounded instruction graph` |
| `conditional-scheduler-sequential-live-alias-counted-loops-v1` | `scheduler loop composition requires a complete bounded instruction graph` |
| `conditional-scheduler-three-per-path-live-alias-v1` | `counted loop increments a different or caller-clobbered counter` |
| `conditional-scheduler-entry-descriptor-calls-v1` | `scheduler entry contract requires one actual pinned entry call` |
| `named-data-buffer-v1`, `named-data-buffer-known-query-callee-v1`, `named-data-buffer-dead-argument-aliases-v1` and 14 other selectors (17) | `buffer callee 0x081443FC: unsupported buffer pointer use or escape` |
| `named-data-buffer-finite-small-copy-binding-v1` | `small-copy prefix excludes ordinary memory accesses` |
| `named-data-buffer-compiler-copy80-binding-v1` | `compiler copy requires exactly one memcpy call and named data only` |
| `named-data-buffer-rom-table-copy-v1` and `named-data-buffer-stack-index-v1` (2) | `buffer callee 0x080DBDC8: unsupported buffer pointer use or escape` |
| `named-data-buffer-stack-index-v2` | `buffer callee 0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification` |

6 more selectors of these families refuse on contracts for other shapes: `projected outputs require four ordered helpers and one scheduler` (`conditional-scheduler-projected-outputs-v1`); `halfword payload requires one exact output leaf and one scheduler site` (`conditional-scheduler-halfword-output-payload-v1`); `scheduler entry branches require exactly two pinned wrapper call sites` (`conditional-scheduler-entry-branch-descriptor-calls-v1`); `indirect manager contract requires one direct scheduler call` (`conditional-scheduler-indirect-manager-v1`); `manager offset contract requires one direct scheduler call` (`conditional-scheduler-manager-offset-v1`); `manager paths contract requires one direct scheduler call` (`conditional-scheduler-manager-paths-v1`).

The other 164 selector values are not listed one by one. None matched.

The counted-loop rule wants the counter in R4-R7. The scheduler loop keeps its counter in R4; the phase 0x103
loop keeps it in R1 (`adds r0, r1, #1` at 0x0810C112). The function has 404 reachable instructions, more than the 256
the two `requires a complete bounded instruction graph` selectors allow.

## Cause

Under `named-data-buffer-stack-index-v2` the forwarding rule passes the coordinate wrappers, and the walk
follows `&child` into the scheduler: `func_08005B6C` calls `func_08005954`, which calls the callback through
`_call_via_r3` at 0x08142250, and the walk stops there. `-v1` and `named-data-buffer-rom-table-copy-v1` stop at the
first wrapper, `func_080DBDC8`, which forwards a local pointer as its callee's stack argument. The index of the copy is
the loop counter (0..2), which needs no premise. With the scheduler call-site summary prototyped, the #200 comment
reports the next refusal as #200's item 6 (`stack index: the owner passes stack pointers to a callee after a callee
released a forwarded pointer word`).

## Source notes

- One function-scope `u8 i` in place of the two block-scoped ones gives 932 bytes of which 10 differ, all in
  the phase 0x103 loop.
- The `extern void *memcpy(...)` declaration does not change the bytes. The matched `src/0810533C.c` has the same line.
- `payload->countdown = 10` is stored on every iteration of the scheduler loop; moved after the loop, 14 bytes differ.
- The callback `func_0810BB70` is parked (`Parked/0810BB70/`).

kit issue: shubshub/fftadecomp-kit#200 (comment)
