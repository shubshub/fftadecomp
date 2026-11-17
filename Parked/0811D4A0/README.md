# 0x0811D4A0 - swap effect callback: a BIOS CpuSet fill from a stack halfword and one scheduler call: bytes identical, refused (local aliases across calls on the function-literal path: a CpuSet fill source and a scheduler descriptor) (348 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321 with the match batches then queued for merge (PRs #200 onward). `int func_0811D4A0(owner, event, state)` is a phase callback (switch on `event->state`: 0, 1, 0x100 to 0x103)
registered by its function word at 0x08395408 in the ROM callback table. Phase 0 records the object and the actor,
reads the object's position into the state (`func_080DBDC8(object, &state->x, &state->y)`), starts an animation
(`func_080D7A70(data_083A6DC4, 8, owner)`) and fills 16 palette halfwords at `0x03003940` with white through BIOS CpuSet
in fill mode from a stack halfword; phase 0x100 waits for the animation (`func_080D7ABC`) and starts a child with a
28-byte stack descriptor holding the object; 0x101 waits for it and starts `func_080E5694(owner)`; 0x102 swaps the two
units' visibility and state (`func_080DBEB4`, `func_080DD720`, `func_080DE10C`, `func_0809A570`, `func_0809A530`); 0x103
ends with `func_080DE150`.

```
0811D4F6  ldr  r2, =0x7FFF
0811D4FA  strh r0, [r1]           @ color = 0x7FFF (r1 = sp)
0811D4FC  ldr  r1, =0x03003940
0811D4FE  ldr  r2, =0x01000010    @ fill mode, 16 halfwords
0811D500  mov  r0, sp
0811D502  bl   0x0814186C         @ CpuSet
...
0811D52A  add  r2, sp, #4         @ descriptor
0811D52E  str  r0, [r2, #4]       @ descriptor.object
0811D530  ldr  r0, =func_0811D218
0811D532  movs r1, #0x40
0811D534  adds r3, r4, #0
0811D536  bl   0x08005B6C
```

## The index

`symbols/functions.txt` has `0811D4A0 0811D5FC 348 174 return` and `config/functions.json` the same extent with 174 instructions (`thumb-prologue`). The CFG, closed by the kit's own `analyze.refine_function`, has 146 reachable instructions, so the instruction column is the halfword count (174). The selectors that compare it with the CFG are outside the families that fit this function: `restoring-owner-scalar-switch-v1`, `restoring-owner-switch-entry-word-v1`, `restoring-owner-switch-entry-two-words-data-v1` and 3 other selectors (6) give `complete-owner text reachable instruction count differs`.

## Byte identity

`0811D4A0.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0811D4A0, with every callee bound to its ROM address and every data word to the address its symbol names (17 `R_ARM_THM_CALL`, 3 `R_ARM_ABS32`). The 348-byte symbol equals the ROM span `[0x0811D4A0, 0x0811D5FC)`: SHA-256 `c327ef70aa7cbd9e0debf887aa3b0eba901090fe8c3fbede4ab5f67f1af5a01d` for both. `.text` is exactly 348 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each is added with its address as the value (`"data_083A6DC4": "0x083A6DC4"`):

`data_083A6DC4`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0811D4A0.c` and the data symbols above added: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, `--signed-quotient-profile positive-constant-frame-v1` and `--unsigned-quotient-profile positive-constant-frame-v1` (3) | `stack aliases cannot cross calls in caller-clobbered registers` |
| `--addressed-runtime-profile addressed-native-bios-fill-buffer-data-v1`, `--addressed-runtime-profile compiler-signed-runtime-data-v1`, `--addressed-runtime-profile addressed-native-bios-fill-scalar-control-numeric-mmio-code-image-data-v1` and 26 other addressed-runtime selectors (29) | `addressed data overflows or aliases indexed code` |
| `--addressed-runtime-profile addressed-native-bios-fill-buffer-v1`, `--addressed-runtime-profile addressed-native-bios-fill-readonly-two-words-v1`, `--addressed-runtime-profile addressed-native-bios-ordinary-v1` and 10 other addressed-runtime selectors (13) | `addressed signed runtimes exclude data and irregular relocations` |
| `conditional-scheduler-descriptor-calls-v1`, `conditional-scheduler-descriptor-payload-calls-v1`, `conditional-scheduler-descriptor-payload8-calls-v1` and `conditional-scheduler-two-payload-calls-v1` (4) | `scheduler contract requires one actual scheduler call` |
| `conditional-scheduler-branch-descriptor-calls-v1`, `conditional-scheduler-following-call-v1` and `conditional-scheduler-eight-target-branches-v1` (3) | `scheduler branches exceed the explicit call-site or target bounds` |
| `conditional-scheduler-twenty-four-target-branches-v1` and `conditional-scheduler-three-per-path-calls-v1` (2) | `ordinary branch calls exclude every live local alias and pointer word` |
| `conditional-scheduler-live-local-alias-calls-v1`, `conditional-scheduler-live-local-alias-payload-calls-v1`, `conditional-scheduler-sequential-live-alias-counted-loops-v1` and 22 other selectors (25) | `buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification` |
| `conditional-scheduler-sequential-leaf-output-calls-v1` | `non-leaf calls and interrupts require linked CFG verification` |
| `conditional-scheduler-u16-counted-loop-v1` | `counted scheduler requires exactly one backward edge` |
| `conditional-scheduler-entry-descriptor-calls-v1` | `scheduler entry contract requires one actual pinned entry call` |
| `bounded-buffer-bios-mixed-fast-fill-runtime-summaries-v1`, `bounded-buffer-bios-fast-fill-source-v1` and `bounded-buffer-bios-mixed-fast-fill-source-v1` (3) | `CpuFastSet fill requires only its actual direct wrapper calls` |
| `named-data-buffer-finite-small-copy-binding-v1` | `one actual canonical small-copy call required` |
| `named-data-buffer-compiler-copy80-binding-v1` | `compiler copy requires exactly one memcpy call and named data only` |
| `named-data-buffer-known-query-callee-v1`, `descriptor-output-alias-v1`, `descriptor-single-store-v1` and 7 other selectors (10) | `buffer callee 0x0814186C: structural inventory is not closed` |
| `bounded-buffer-bios-sqrt-scratch-v1` | `BIOS Sqrt requires exact complete svc #8; bx lr wrapper` |
| `bounded-buffer-bios-fill-source-v1`, `bounded-buffer-bios-fill-local-source-semantics-v1` and `bounded-buffer-bios-fill-overwritten-control-stores-v1` (3) | `buffer callee 0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification` |
| `bounded-buffer-bios-bg-affine-set-v1`, `bounded-buffer-bios-bg-affine-set-transparent-leaf-scratch-v1` and `bounded-buffer-bios-bg-affine-set-discarded-scratch-v1` (3) | `BgAffineSet requires an actual direct call in its closed owner` |
| `bounded-buffer-bios-mixed-cpuset-fast-fill-source-v1` | `mixed CpuSet/CpuFastSet fill requires actual calls to both wrappers` |
| `bios-word-switch-local-buffers-v1` | `BIOS buffer requires one exact one-object-word switch without local BL` |

9 more selectors of these families refuse on contracts for other shapes: `projected outputs require four ordered helpers and one scheduler` (`conditional-scheduler-projected-outputs-v1`); `following-call contract requires one scheduler site and a reached following ordinary call` (`conditional-scheduler-twenty-four-target-following-calls-v1`); `structural inventory is not closed` (`conditional-scheduler-sequential-killed-alias-calls-v1`); `predicate helper contains an unsupported or memory-writing instruction` (`conditional-scheduler-guarded-descriptor-calls-v1`); `halfword payload requires one exact output leaf and one scheduler site` (`conditional-scheduler-halfword-output-payload-v1`); `scheduler entry branches require exactly two pinned wrapper call sites` (`conditional-scheduler-entry-branch-descriptor-calls-v1`); `indirect manager contract requires one direct scheduler call` (`conditional-scheduler-indirect-manager-v1`); `manager offset contract requires one direct scheduler call` (`conditional-scheduler-manager-offset-v1`); `manager paths contract requires one direct scheduler call` (`conditional-scheduler-manager-paths-v1`).

The other 99 selector values are not listed one by one (none matched); by family: callback and closure (21), private float and double (15), switch-layout (13), owner (12), restoring-owner (9), canonical-integer (8), function-address (6), arithmetic-runtime (5), bounded-buffer (5), descriptor and preservation (2), control-flow (1), -O0 (1), guarded-switch buffer (1).

## Cause

The callback word `func_0811D218` and the named data put the default run on the function-literal path, which
has no buffer proof: `stack aliases cannot cross calls in caller-clobbered registers`. The two halves each have a
selector, but no selector has both:

- the BIOS fill selectors (`bounded-buffer-bios-fill-source-v1` and its two relatives) prove the CpuSet fill and then
  walk the descriptor into the scheduler, stopping at its callback thunk (`buffer callee 0x08005B6C: buffer callee
  0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification`);
- the scheduler selectors that accept a live local alias (`conditional-scheduler-live-local-alias-calls-v1`,
  `-three-per-path-live-alias-v1` and two more) apply the descriptor contract and then walk the fill source into the
  CpuSet wrapper, stopping there (`buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG
  verification`); the others refuse the shape.

The scheduler call-site issue and the #192 comment report `MATCH - byte identical` with both rules prototyped (the scheduler
descriptor contract as a per-site summary and the BIOS fill as a root call-site summary), and a refusal with either
one alone.

## Source notes

From the attempt, not reviewed: the fill source is written through a pointer local (`u16 *source = &color;
*source = 0x7FFF;`), the idiom of the parked sibling `0x0811E034`; with a plain `color = 0x7FFF;` and `&color` 13 halfwords
differ, so the pointer is load-bearing. Whether it stands for the SDK's fill macro or only steers registers is a review
question; the source rules refuse a temporary that only moves registers. Locals are
block-scoped per phase.

kit issue: (to be filed - match.py: a scheduler call with a local descriptor verifies only under shape-bound owner selectors; a per-site summary admits 7 byte-identical functions alone and 14 with companion rules) (with the BIOS fill call-site summary); shubshub/fftadecomp-kit#192 (comment to be posted) (the fill summary at root call sites)
