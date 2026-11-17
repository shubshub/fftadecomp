# 0x08126E34 - queue request built from two actor records, through the scheduler entry func_08121B8C: bytes identical, refused (a stack descriptor passed to the scheduler entry func_08121B8C after three helper calls) (112 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321 with the match batches then queued for merge (PRs #200 onward). `void func_08126E34(object, a, b)` clears `object->ready`, looks up two actor records with `func_08125578(a)`
and `func_08125578(b)`, asks `func_08124ACC(x->first, x->second, y->first, y->second)` for a selector (0xFF means "use
`x->fallback`", the byte at record +0xF8), and queues a 28-byte stack request with the scheduler entry
`func_08121B8C(func_08126BFC, 12, &request, 0)` at 0x08126E92. Its caller is `func_0812302C` (0x08123034).

```
08126E86  mov  r0, sp
08126E88  strh r1, [r0, #0x16]    @ request.second
08126E8A  ldr  r0, =func_08126BFC
08126E8C  movs r1, #0xc
08126E8E  mov  r2, sp             @ &request
08126E90  movs r3, #0
08126E92  bl   0x08121B8C
```

## The index

`symbols/functions.txt` has `08126E34 08126EA4 112 56 return` and `config/functions.json` the same extent with 56 instructions (`thumb-prologue`). The CFG, closed by the kit's own `analyze.refine_function`, has 49 reachable instructions, so the instruction column is the halfword count (56). The selectors that compare it with the CFG are outside the families that fit this function: `restoring-owner-scalar-switch-v1`, `restoring-owner-switch-entry-word-v1`, `restoring-owner-switch-entry-two-words-data-v1` and 3 other selectors (6) give `complete-owner text reachable instruction count differs`.

## Byte identity

`08126E34.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08126E34, with every callee bound to its ROM address and every data word to the address its symbol names (4 `R_ARM_THM_CALL`, 1 `R_ARM_ABS32`). The 112-byte symbol equals the ROM span `[0x08126E34, 0x08126EA4)`: SHA-256 `dd433add4fd9a0e1dffb48efbfe6e590ac7d8fa8eb898a4845ec6bbfe4bc5b16` for both. `.text` is exactly 112 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

None: the function has no data relocation.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08126E34.c`: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, `--signed-quotient-profile positive-constant-frame-v1` and `--unsigned-quotient-profile positive-constant-frame-v1` (3) | `stack aliases cannot cross calls in caller-clobbered registers; function-buffer proof: buffer callee 0x08121B8C: buffer callee 0x08005954: function-buffer evidence excludes runtime call thunks in inspected dependencies` |
| `conditional-scheduler-descriptor-calls-v1`, `conditional-scheduler-descriptor-payload-calls-v1`, `conditional-scheduler-descriptor-payload8-calls-v1` and `conditional-scheduler-two-payload-calls-v1` (4) | `scheduler contract requires one actual scheduler call` |
| `conditional-scheduler-branch-descriptor-calls-v1`, `conditional-scheduler-following-call-v1`, `conditional-scheduler-eight-target-branches-v1` and 7 other scheduler selectors (10) | `scheduler branches exceed the explicit call-site or target bounds` |
| `conditional-scheduler-u16-counted-loop-v1` | `counted scheduler requires exactly one backward edge` |
| `conditional-scheduler-sequential-live-alias-counted-loops-v1` and `conditional-scheduler-three-per-path-live-alias-v1` (2) | `scheduler loop composition exceeds the explicit call-site or target bounds` |
| `conditional-scheduler-entry-descriptor-calls-v1` | `scheduler entry contract requires one actual pinned entry call` |
| `named-data-buffer-v1`, `named-data-buffer-dead-argument-aliases-v1`, `named-data-buffer-rom-table-copy-v1` and 15 other selectors (18) | `buffer callee 0x08121B8C: buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification` |
| `named-data-buffer-finite-small-copy-binding-v1` | `one actual canonical small-copy call required` |
| `named-data-buffer-compiler-copy80-binding-v1` | `compiler copy requires exactly one memcpy call and named data only` |
| `named-data-buffer-known-query-callee-v1` | `buffer callee 0x08121B8C: buffer callee 0x08005954: buffer callee 0x08142250: structural inventory is not closed` |

7 more selectors of these families refuse on contracts for other shapes: `projected outputs require four ordered helpers and one scheduler` (`conditional-scheduler-projected-outputs-v1`); `guarded scheduler requires predicates and exactly one scheduler site` (`conditional-scheduler-guarded-descriptor-calls-v1`); `halfword payload requires one exact output leaf and one scheduler site` (`conditional-scheduler-halfword-output-payload-v1`); `scheduler entry branches require exactly two pinned wrapper call sites` (`conditional-scheduler-entry-branch-descriptor-calls-v1`); `indirect manager contract requires one direct scheduler call` (`conditional-scheduler-indirect-manager-v1`); `manager offset contract requires one direct scheduler call` (`conditional-scheduler-manager-offset-v1`); `manager paths contract requires one direct scheduler call` (`conditional-scheduler-manager-paths-v1`).

The other 165 selector values are not listed one by one (none matched); by family: addressed-runtime (40), callback and closure (23), private float and double (15), BIOS buffer (13), switch-layout (13), owner (12), descriptor and preservation (12), restoring-owner (9), canonical-integer (8), function-address (6), bounded-buffer (6), arithmetic-runtime (5), control-flow (1), -O0 (1), guarded-switch buffer (1).

## Cause

The callback word `func_08126BFC` puts the default run on the function-literal path; with no named data it
falls back to the function-buffer proof, which walks `&request` through `func_08121B8C` into `func_08005954` and refuses
there: `stack aliases cannot cross calls in caller-clobbered registers; function-buffer proof: buffer callee
0x08121B8C: buffer callee 0x08005954: function-buffer evidence excludes runtime call thunks in inspected dependencies`.
The buffer selectors stop at the scheduler's callback thunk (`buffer callee 0x08121B8C: buffer callee 0x08005954:
buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification`). The one selector that pins
`func_08121B8C`, `conditional-scheduler-entry-descriptor-calls-v1`, requires the entry call to be the function's only
call (`len(calls) == 1` in `tools/scheduler_entry_profile.py:65`), and this one makes three helper calls first:
`scheduler entry contract requires one actual pinned entry call`. Ten other scheduler selectors give `scheduler branches
exceed the explicit call-site or target bounds`.

The scheduler call-site issue reports `MATCH - byte identical` for this function under its per-site rule alone.

kit issue: shubshub/fftadecomp-kit#237 (admitted by the per-site rule alone in the prototype)
