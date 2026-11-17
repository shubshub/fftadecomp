# 0x08107AA0 - screen pan callback (two coordinate pairs through func_080DC224, one scheduler call): bytes identical, refused (a local address stored to an outgoing argument word on the function-literal path; with a buffer proof, the jump table of 0x080C7EA4) (774 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321 with the match batches then queued for merge (PRs #200 onward). `u32 func_08107AA0(owner, event, s)` is a phase callback (switch on `event->phase`: 0, 1, 0x100 to 0x106)
registered by its function word at 0x08395018, in a ROM table of 8-byte entries (callback, payload size 0x48, ...).
Phase 0 starts a loader (`func_080E03F8(resource, data_083A0D60, ...)`); 0x100 and 0x101 wait for it and set up the
actor (`func_080DD47C`, `func_080DE10C`, `func_080DC1E8`); 0x102 reads two actors' positions (`func_080DBDC8`), converts
each pair to screen coordinates with `func_080DC224`, writes the BG offsets (`func_08003508`, `func_08003558`) and starts
two interpolations (`func_080E0608`); 0x103 steps them (`func_080E064C`); 0x104 starts a child task with a 28-byte
stack descriptor, `func_08005B6C(func_080E4054, 0x1C, &d, owner)` at 0x08107D46; 0x105 and 0x106 wait for it and for
`func_080DF8E8`.

`func_080DC224(object, x, y, &ax, &ay)` takes its fifth argument in the outgoing word:

```
08107C38  mov  r4, sp
08107C3A  adds r4, #0xe
08107C3C  str  r4, [sp]          @ &ay -> fifth argument
08107C3E  add  r3, sp, #0xc      @ &ax
08107C40  bl   0x080DC224        @ second pair at 0x08107C50-0x08107C58
```

`func_080DC224` calls `func_080DD6E0`, which calls `func_080C7EA4`, a function with a jump table.

## The index

`symbols/functions.txt` has `08107AA0 08107DA6 774 387 return` and `config/functions.json` the same extent with 387 instructions (`thumb-prologue`). The CFG, closed by the kit's own `analyze.refine_function`, has 323 reachable instructions, so the instruction column is the halfword count (387). The selectors that compare it with the CFG are outside the families that fit this function: `restoring-owner-switch-aligned-v1` and `restoring-owner-switch-cycles-function-words-v1` (2) give `complete-owner text reachable instruction count differs`.

## Byte identity

`08107AA0.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08107AA0, with every callee bound to its ROM address and every data word to the address its symbol names (37 `R_ARM_THM_CALL`, 11 `R_ARM_ABS32`). The 774-byte symbol equals the ROM span `[0x08107AA0, 0x08107DA6)`: SHA-256 `37ef4870f0b205b8e51c65caed5458ec8664ba6eeda1f4a5490b2fa02895a898` for both. `.text` is 776 bytes: the symbol and the assembler's `c0 46` alignment halfword. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each is added with its address as the value (`"data_0600F860": "0x0600F860"`):

`data_0600F860`, `data_083A0D60`, `data_083A0D9C`, `data_083A0DA4`, `data_0894DC5C`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08107AA0.c` and the data symbols above added: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, `--signed-quotient-profile positive-constant-frame-v1` and `--unsigned-quotient-profile positive-constant-frame-v1` (3) | `unsupported stack-alias use or escape` |
| `conditional-scheduler-descriptor-calls-v1`, `conditional-scheduler-descriptor-payload-calls-v1`, `conditional-scheduler-descriptor-payload8-calls-v1` and `conditional-scheduler-two-payload-calls-v1` (4) | `scheduler contract requires one actual scheduler call` |
| `conditional-scheduler-branch-descriptor-calls-v1`, `conditional-scheduler-following-call-v1`, `conditional-scheduler-eight-target-branches-v1` and 4 other scheduler selectors (7) | `scheduler branches exceed the explicit call-site or target bounds` |
| `conditional-scheduler-three-per-path-calls-v1` | `ordinary branch calls exclude every live local alias and pointer word` |
| `conditional-scheduler-sequential-leaf-output-calls-v1` | `scheduler leaf output excludes pointer-bearing slots` |
| `conditional-scheduler-sequential-killed-alias-calls-v1` | `alias kill requires an indexed ordinary call without pointer slots` |
| `conditional-scheduler-u16-counted-loop-v1` | `counted scheduler loop requires a complete bounded instruction graph` |
| `conditional-scheduler-sequential-live-alias-counted-loops-v1` | `scheduler loop composition requires a complete bounded instruction graph` |
| `conditional-scheduler-three-per-path-live-alias-v1` | `live-alias calls exclude pointer-bearing slots and word provenance` |
| `conditional-scheduler-entry-descriptor-calls-v1` | `scheduler entry contract requires one actual pinned entry call` |
| `named-data-buffer-v1`, `named-data-buffer-known-query-callee-v1`, `named-data-buffer-dead-argument-aliases-v1` and 10 other selectors (13) | `buffer callee 0x080DC224: buffer callee 0x080DD6E0: buffer callee 0x080C7EA4: unresolved program-counter write` |
| `named-data-buffer-finite-small-copy-binding-v1` | `one actual canonical small-copy call required` |
| `named-data-buffer-compiler-copy80-binding-v1` | `compiler copy requires exactly one memcpy call and named data only` |
| `named-data-buffer-stack-index-v1` and `named-data-buffer-stack-index-v2` (2) | `variable stack indices exclude pointer-bearing or return-carrying local words` |
| `bounded-buffer-guarded-switch-v1` | `buffer callee 0x080DC224: consumer observes discarded return scratch before a killing write` |
| `bounded-buffer-guarded-callee-aliases-v1`, `bounded-buffer-guarded-bios-division-v1` and `bounded-buffer-nested-halfword-output-selective-scratch-v1` (3) | `buffer callee 0x080D3E9C: buffer callee 0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification` |
| `bounded-buffer-root-guarded-switch-v1` | `root buffer requires one exact guarded switch and ordinary calls` |

7 more selectors of these families refuse on contracts for other shapes: `projected outputs require four ordered helpers and one scheduler` (`conditional-scheduler-projected-outputs-v1`); `predicate helper contains an unsupported or memory-writing instruction` (`conditional-scheduler-guarded-descriptor-calls-v1`); `halfword payload requires one exact output leaf and one scheduler site` (`conditional-scheduler-halfword-output-payload-v1`); `scheduler entry branches require exactly two pinned wrapper call sites` (`conditional-scheduler-entry-branch-descriptor-calls-v1`); `indirect manager contract requires one direct scheduler call` (`conditional-scheduler-indirect-manager-v1`); `manager offset contract requires one direct scheduler call` (`conditional-scheduler-manager-offset-v1`); `manager paths contract requires one direct scheduler call` (`conditional-scheduler-manager-paths-v1`).

The other 164 selector values are not listed one by one (none matched); by family: addressed-runtime (40), callback and closure (23), private float and double (15), BIOS buffer (13), switch-layout (13), owner (12), descriptor and preservation (12), restoring-owner (9), canonical-integer (8), function-address (6), bounded-buffer (6), arithmetic-runtime (5), control-flow (1), -O0 (1).

## Cause

The callback word `func_080E4054` (pool 0x08107D5C) puts the default run on the function-literal path,
and the function also has named data, so that path runs its walk without a buffer proof and does not fall back to
the function-buffer proof. It refuses the first store of a local address to memory, the outgoing-word store at
0x08107C3C: `unsupported stack-alias use or escape`. The selectors that carry a buffer proof get past that store and
stop inside the callee chain, at the dispatch of `func_080C7EA4`
(`buffer callee 0x080DC224: buffer callee 0x080DD6E0: buffer callee 0x080C7EA4: unresolved program-counter write`),
which is the walk the switch-callee issue asks for; that issue lists this function among the callers that its rule
alone does not reach, because the default path never gets to the callee walk. `bounded-buffer-guarded-callee-aliases-v1` and two relatives get past
the coordinate calls and stop at the scheduler reached inside `func_080D3E9C`
(`buffer callee 0x080D3E9C: buffer callee 0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250: non-leaf
indirect control flow requires linked CFG verification`). The stack-index selectors refuse the
pointer-bearing outgoing words, and the scheduler selectors refuse the function's shape (six phases with calls, two
live local aliases).

## Source notes

Recorded by the attempt, not reviewed: the flag update of phase 0x102 goes through `mask` and `flags`
temporaries (`u32 mask = func_080035A8(3); u32 flags = g_control_flags_03000940.display; ...`), and the four `s16`
outputs are block-scoped locals of phase 0x102.

kit issue: shubshub/fftadecomp-kit#241 (listed under "Not covered": on the function-literal path the callee walk is not reached); shubshub/fftadecomp-kit#236 (part b, the function-literal path)
