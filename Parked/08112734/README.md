# 0x08112734 - menu sequence callback with seven scheduler sites: bytes identical, refused (local aliases across calls on the function-literal path; with a buffer proof, the scheduler callback thunk; the scheduler selectors bound the number of sites) (812 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321 with the match batches then queued for merge (PRs #200 onward). `u32 func_08112734(owner, request, state)` is a phase callback (switch on `request->phase`: 0, 1, 0x100 to 0x10A)
registered by its function word at 0x08395178 in the ROM callback table (and at 0x083A60D0 in a second table). It runs
seven child tasks one after the other, each with its own 28-byte stack descriptor: `func_08005B6C(func_081112A0, 0x2C,
&d0, owner)` (0x081127A2), `func_0811166C` (0x08112884), `func_08111A5C` (0x081128C0), `func_081120CC` (0x081128EC),
`func_08112360` (0x08112932), `func_08112594` (0x08112966) and `func_08112A60` (0x08112992), waiting for each with
`func_080E051C`. The first descriptor holds the address of an 8-byte local `extent` record (pointers to the state's
width and height):

```
08112790  add  r0, sp, #0xd0     @ extent
08112792  str  r1, [r0]          @ extent.width = &state->width
08112796  str  r1, [r0, #4]      @ extent.height = &state->height
08112798  str  r0, [sp, #0x14]   @ d0.extent = &extent
0811279A  ldr  r0, =func_081112A0
0811279C  movs r1, #0x2c
0811279E  add  r2, sp, #8        @ &d0
081127A2  bl   0x08005B6C
```

Around the children it fades (`func_080DFD68`, `func_080DFED8`), saves and restores 0x5F halfwords of the window state at
`data_03003862` with BIOS CpuSet (`func_0814186C`, three calls), and sets display bits from `func_0801E610(&first,
&second)` through `func_080035A8`.

## The index

`symbols/functions.txt` has `08112734 08112A60 812 406 return` and `config/functions.json` the same extent with 406 instructions (`thumb-prologue`). The CFG, closed by the kit's own `analyze.refine_function`, has 332 reachable instructions, so the instruction column is the halfword count (406). The selectors that compare it with the CFG are outside the families that fit this function: `restoring-owner-scalar-switch-v1`, `restoring-owner-switch-entry-word-v1`, `restoring-owner-switch-entry-two-words-data-v1` and 3 other selectors (6) give `complete-owner text reachable instruction count differs`.

## Byte identity

`08112734.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08112734, with every callee bound to its ROM address and every data word to the address its symbol names (38 `R_ARM_THM_CALL`, 11 `R_ARM_ABS32`). The 812-byte symbol equals the ROM span `[0x08112734, 0x08112A60)`: SHA-256 `3bfbdf4302f3edba6581edb72a0170a549225dee3ad08466cd0888d5438ffb2a` for both. `.text` is exactly 812 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each is added with its address as the value (`"data_083A31E0": "0x083A31E0"`):

`data_083A31E0`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08112734.c` and the data symbols above added: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, `--signed-quotient-profile positive-constant-frame-v1` and `--unsigned-quotient-profile positive-constant-frame-v1` (3) | `stack aliases cannot cross calls in caller-clobbered registers` |
| `conditional-scheduler-descriptor-calls-v1`, `conditional-scheduler-descriptor-payload-calls-v1`, `conditional-scheduler-descriptor-payload8-calls-v1` and `conditional-scheduler-two-payload-calls-v1` (4) | `scheduler contract requires one actual scheduler call` |
| `conditional-scheduler-branch-descriptor-calls-v1`, `conditional-scheduler-following-call-v1`, `conditional-scheduler-eight-target-branches-v1` and 7 other scheduler selectors (10) | `scheduler branches exceed the explicit call-site or target bounds` |
| `conditional-scheduler-u16-counted-loop-v1` | `counted scheduler loop requires a complete bounded instruction graph` |
| `conditional-scheduler-sequential-live-alias-counted-loops-v1` | `scheduler loop composition requires a complete bounded instruction graph` |
| `conditional-scheduler-three-per-path-live-alias-v1` | `scheduler contract excludes additional register or pointer-word aliases` |
| `conditional-scheduler-entry-descriptor-calls-v1` | `scheduler entry contract requires one actual pinned entry call` |
| `named-data-buffer-v1`, `named-data-buffer-dead-argument-aliases-v1`, `named-data-buffer-rom-table-copy-v1` and 15 other selectors (18) | `buffer callee 0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification` |
| `named-data-buffer-finite-small-copy-binding-v1` | `one actual canonical small-copy call required` |
| `named-data-buffer-compiler-copy80-binding-v1` | `compiler copy requires exactly one memcpy call and named data only` |
| `named-data-buffer-known-query-callee-v1` | `buffer callee 0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250: structural inventory is not closed` |

7 more selectors of these families refuse on contracts for other shapes: `projected outputs require four ordered helpers and one scheduler` (`conditional-scheduler-projected-outputs-v1`); `guarded scheduler requires predicates and exactly one scheduler site` (`conditional-scheduler-guarded-descriptor-calls-v1`); `halfword payload requires one exact output leaf and one scheduler site` (`conditional-scheduler-halfword-output-payload-v1`); `scheduler entry branches require exactly two pinned wrapper call sites` (`conditional-scheduler-entry-branch-descriptor-calls-v1`); `indirect manager contract requires one direct scheduler call` (`conditional-scheduler-indirect-manager-v1`); `manager offset contract requires one direct scheduler call` (`conditional-scheduler-manager-offset-v1`); `manager paths contract requires one direct scheduler call` (`conditional-scheduler-manager-paths-v1`).

The other 165 selector values are not listed one by one (none matched); by family: addressed-runtime (40), callback and closure (23), private float and double (15), BIOS buffer (13), switch-layout (13), owner (12), descriptor and preservation (12), restoring-owner (9), canonical-integer (8), function-address (6), bounded-buffer (6), arithmetic-runtime (5), control-flow (1), -O0 (1), guarded-switch buffer (1).

## Cause

The seven callback words and the named data put the default run on the function-literal path, which has no
buffer proof: `stack aliases cannot cross calls in caller-clobbered registers`. The buffer selectors, including
`named-data-buffer-stack-index-v2`, walk the first descriptor into the scheduler and stop at its callback thunk
(`buffer callee 0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires
linked CFG verification`), the refusal the #200 comment reports. The scheduler selectors refuse the number of sites
(10 of 25 give `scheduler branches exceed the explicit call-site or target bounds`), and
`conditional-scheduler-three-per-path-live-alias-v1` refuses the `extent` pointer word in the first descriptor
(`scheduler contract excludes additional register or pointer-word aliases`).

The function has no variable stack index of its own. Its stack index is inside the callee `func_080035A8` (matched,
`src/080035A8.c`), which copies the 8-byte ROM table `g_object_08149550` to its own stack with `func_081443FC` and
returns `values[index]`; it is called at 0x081129BE and 0x081129CC with the two bytes `func_0801E610` wrote. Both the
copy and the variable index are in the callee. With the scheduler call-site summary prototyped, the #200 comment
reports `variable stack indices exclude pointer-bearing or return-carrying local words` next.

## Source notes

From the attempt, not reviewed: the seven descriptors are separate locals `d0` to `d6` (the frame is
0xD8 bytes, seven 28-byte descriptors and the `extent` record); `d4` is passed uninitialised, as the ROM does (no store
into it before 0x08112932).

kit issue: shubshub/fftadecomp-kit#200 (comment to be posted) (four more functions with the refusal); (to be filed - match.py: a scheduler call with a local descriptor verifies only under shape-bound owner selectors; a per-site summary admits 7 byte-identical functions alone and 14 with companion rules) (listed under "Not covered": #200 stops it after the rule)
