# 0x0811E034 - window effect callback: a BIOS CpuSet fill from a stack halfword and one scheduler call followed by another call: bytes identical, refused (local aliases across calls on the function-literal path: a CpuSet fill source and a scheduler descriptor) (452 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321 with the match batches then queued for merge (PRs #200 onward). `u32 func_0811E034(owner, event, context)` is a phase callback (switch on `event->state`: 0, 1, 0x100 to 0x102)
registered by its function word at 0x08395428 in the ROM callback table. Phase 0 reads the object's position into the
context (`func_080DBDC8`), starts an animation (`func_080D7A70(data_083A72D0, 3, owner)`) and fills 16 palette halfwords
at `0x03003920` with white through BIOS CpuSet (`func_0814186C(source, data_03003920, 0x01000010)` at 0x0811E092, the
source a stack halfword); phase 0x100 starts a child with a 28-byte stack descriptor (`selector = 0x18C`,
`option = 0`, the object), `func_08005B6C(func_080E9554, 0x70, &descriptor, owner)` at 0x0811E0D2, and right after it a
record (`func_080DFD8C(data_083A730C, ...)` at 0x0811E0E2); 0x101 waits, starts an effect (`func_080D6098`) and sets the
window registers in `g_control_flags_03000940` (`func_080035D0`, `func_080D7220(data_088F46CC)`, `func_080D4704`,
`func_080D3E9C`); 0x102 waits and restores the display.

## The index

`symbols/functions.txt` has `0811E034 0811E1F8 452 178 return` and `config/functions.json` the same extent with 178 instructions (`thumb-prologue`). The CFG, closed by the kit's own `analyze.refine_function`, has 178 reachable instructions, so the row is right.

## Byte identity

`0811E034.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0811E034, with every callee bound to its ROM address and every data word to the address its symbol names (18 `R_ARM_THM_CALL`, 10 `R_ARM_ABS32`). The 452-byte symbol equals the ROM span `[0x0811E034, 0x0811E1F8)`: SHA-256 `19bca488c4f61d9c5f19241ce59fdc3435c801eb3bc86adde0a71a3c095155dc` for both. `.text` is exactly 452 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each is added with its address as the value (`"data_083A72D0": "0x083A72D0"`):

`data_083A72D0`, `data_083A72F4`, `data_083A730C`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0811E034.c` and the data symbols above added: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, `--signed-quotient-profile positive-constant-frame-v1` and `--unsigned-quotient-profile positive-constant-frame-v1` (3) | `stack aliases cannot cross calls in caller-clobbered registers` |
| `--addressed-runtime-profile addressed-native-bios-fill-buffer-data-v1`, `--addressed-runtime-profile compiler-signed-runtime-data-v1`, `--addressed-runtime-profile addressed-native-bios-fill-scalar-control-numeric-mmio-code-image-data-v1` and 26 other addressed-runtime selectors (29) | `addressed data overflows or aliases indexed code` |
| `--addressed-runtime-profile addressed-native-bios-fill-buffer-v1`, `--addressed-runtime-profile addressed-native-bios-fill-readonly-two-words-v1`, `--addressed-runtime-profile addressed-native-bios-ordinary-v1` and 10 other addressed-runtime selectors (13) | `addressed signed runtimes exclude data and irregular relocations` |
| `conditional-scheduler-descriptor-calls-v1`, `conditional-scheduler-descriptor-payload-calls-v1`, `conditional-scheduler-descriptor-payload8-calls-v1` and `conditional-scheduler-two-payload-calls-v1` (4) | `scheduler contract requires one actual scheduler call` |
| `conditional-scheduler-branch-descriptor-calls-v1`, `conditional-scheduler-following-call-v1` and `conditional-scheduler-eight-target-branches-v1` (3) | `scheduler branches exceed the explicit call-site or target bounds` |
| `conditional-scheduler-twenty-four-target-branches-v1`, `conditional-scheduler-live-local-alias-calls-v1` and `conditional-scheduler-live-local-alias-payload-calls-v1` (3) | `scheduler branches exclude every call after a scheduler return` |
| `conditional-scheduler-twenty-four-target-following-calls-v1` and `conditional-scheduler-three-per-path-calls-v1` (2) | `ordinary branch calls exclude every live local alias and pointer word` |
| `conditional-scheduler-sequential-leaf-output-calls-v1` | `non-leaf calls and interrupts require linked CFG verification` |
| `conditional-scheduler-u16-counted-loop-v1` | `counted scheduler requires exactly one backward edge` |
| `conditional-scheduler-sequential-live-alias-counted-loops-v1`, `conditional-scheduler-three-per-path-live-alias-v1`, `bounded-buffer-runtime-summaries-v1` and 20 other selectors (23) | `buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification` |
| `conditional-scheduler-entry-descriptor-calls-v1` | `scheduler entry contract requires one actual pinned entry call` |
| `bounded-buffer-bios-mixed-fast-fill-runtime-summaries-v1`, `bounded-buffer-bios-fast-fill-source-v1` and `bounded-buffer-bios-mixed-fast-fill-source-v1` (3) | `CpuFastSet fill requires only its actual direct wrapper calls` |
| `named-data-buffer-finite-small-copy-binding-v1` | `one actual canonical small-copy call required` |
| `named-data-buffer-compiler-copy80-binding-v1` | `compiler copy requires exactly one memcpy call and named data only` |
| `named-data-buffer-known-query-callee-v1`, `descriptor-output-alias-v1`, `descriptor-single-store-v1` and 7 other selectors (10) | `buffer callee 0x0814186C: structural inventory is not closed` |
| `bounded-buffer-bios-sqrt-scratch-v1` | `BIOS Sqrt requires exact complete svc #8; bx lr wrapper` |
| `bounded-buffer-bios-fill-source-v1`, `bounded-buffer-bios-fill-local-source-semantics-v1` and `bounded-buffer-bios-fill-overwritten-control-stores-v1` (3) | `verdict NOT VERIFIED - the selector was not run`, with the plausibility finding `allowlisted volatile semantic check: buffer callee 0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification` |
| `bounded-buffer-bios-bg-affine-set-v1`, `bounded-buffer-bios-bg-affine-set-transparent-leaf-scratch-v1` and `bounded-buffer-bios-bg-affine-set-discarded-scratch-v1` (3) | `BgAffineSet requires an actual direct call in its closed owner` |
| `bounded-buffer-bios-mixed-cpuset-fast-fill-source-v1` | `mixed CpuSet/CpuFastSet fill requires actual calls to both wrappers` |
| `bios-word-switch-local-buffers-v1` | `BIOS buffer requires one exact one-object-word switch without local BL` |

9 more selectors of these families refuse on contracts for other shapes: `projected outputs require four ordered helpers and one scheduler` (`conditional-scheduler-projected-outputs-v1`); `structural inventory is not closed` (`conditional-scheduler-sequential-killed-alias-calls-v1`, `restoring-owner-ignored-leaf-alias-v1`); `guarded scheduler excludes calls after scheduler return` (`conditional-scheduler-guarded-descriptor-calls-v1`); `halfword payload requires one exact output leaf and one scheduler site` (`conditional-scheduler-halfword-output-payload-v1`); `scheduler entry branches require exactly two pinned wrapper call sites` (`conditional-scheduler-entry-branch-descriptor-calls-v1`); `indirect manager contract requires one direct scheduler call` (`conditional-scheduler-indirect-manager-v1`); `manager offset contract requires one direct scheduler call` (`conditional-scheduler-manager-offset-v1`); `manager paths contract requires one direct scheduler call` (`conditional-scheduler-manager-paths-v1`).

The other 98 selector values are not listed one by one (none matched); by family: callback and closure (21), private float and double (15), switch-layout (13), owner (12), canonical-integer (8), restoring-owner (8), function-address (6), arithmetic-runtime (5), bounded-buffer (5), descriptor and preservation (2), control-flow (1), -O0 (1), guarded-switch buffer (1).

## Cause

The callback word `func_080E9554` and the named data put the default run on the function-literal path, which
has no buffer proof: `stack aliases cannot cross calls in caller-clobbered registers`. As in the sibling `0x0811D4A0`,
each half has a selector and none has both:

- the BIOS fill selectors prove the fill and then reach the scheduler's callback thunk; here they report it through
  the allowlisted volatile semantic check that the source reaches through `control_flags.h` (`verdict NOT VERIFIED -
  the selector was not run`, finding `buffer callee 0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250:
  non-leaf indirect control flow requires linked CFG verification`);
- `conditional-scheduler-three-per-path-live-alias-v1` and one more accept the descriptor and stop at the CpuSet wrapper
  (`buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification`); three others refuse the
  record call right after the scheduler (`scheduler branches exclude every call after a scheduler return`).

The scheduler call-site issue and the #192 comment report `MATCH - byte identical` with both rules prototyped, and a refusal
with either one alone.

## Source notes

From the attempt, not reviewed: the fill source is written through a pointer local (`u16 *source = &fill;
*source = 0x7FFF;`), as in the parked sibling `0x0811D4A0`; with a plain `fill = 0x7FFF;` and `&fill` 12 halfwords
differ, so the pointer is load-bearing. Whether it stands for the SDK's fill macro or only steers registers is a review
question; the source rules refuse a temporary that only moves registers.

kit issue: shubshub/fftadecomp-kit#237 (with the BIOS fill call-site summary); shubshub/fftadecomp-kit#192 (comment) (the fill summary at root call sites)
