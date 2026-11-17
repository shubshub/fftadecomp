# 0x0811802C - scene entrance callback: two BIOS CpuSet fills from stack halfwords, a script call with a local point, two scheduler calls: bytes identical, refused (local aliases across calls on the function-literal path; with a buffer proof, the BIOS fill or the jump table of 0x080E03F8) (832 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321 with the match batches then queued for merge (PRs #200 onward). `u32 func_0811802C(task, descriptor, payload)` is a phase callback (switch on `descriptor->phase`: 0, 1, 0x100 to
0x107) registered by its function word at 0x083951E0 in the ROM callback table. Phase 0 reads the focus position into
two local halfwords (`func_0801E6F0(pos, &pos[1])`), packs it into a local point and starts the script
`func_080E03F8(owner, data_083A5144, mode, 6, &point, task)` (the point's address in the outgoing word, 0x081180E8),
counts the group and runs a `u8` loop over it (`func_080DE268(func_080DD4B4(...))`), and clears two palette ranges with
BIOS CpuSet from stack halfwords (`func_0814186C(fill_a, data_03003920, 0x01000010)` at 0x08118134, the second at
0x08118144); 0x100 starts an effect and an animation (`func_080DFD8C(data_083A6000)`, `func_080D6098(..., data_083A51A4)`);
0x101 starts a child, `func_08005B6C(func_081179B4, 0x30, &sched_a, task)` at 0x081181D6, and a second animation; 0x103
starts another, `func_08005B6C(func_08117B9C, 0x174, &sched_b, task)` at 0x08118256; 0x105 to 0x107 run one
`func_080DCFE4` effect per member.

## The index

`symbols/functions.txt` has `0811802C 0811836C 832 416 return` and `config/functions.json` the same extent with 416 instructions (`thumb-prologue`). The CFG, closed by the kit's own `analyze.refine_function`, has 355 reachable instructions, so the instruction column is the halfword count (416). The selectors that compare it with the CFG are outside the families that fit this function: `restoring-owner-scalar-switch-v1`, `restoring-owner-switch-entry-word-v1`, `restoring-owner-switch-entry-two-words-data-v1` and 3 other selectors (6) give `complete-owner text reachable instruction count differs`.

## Byte identity

`0811802C.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0811802C, with every callee bound to its ROM address and every data word to the address its symbol names (28 `R_ARM_THM_CALL`, 10 `R_ARM_ABS32`). The 832-byte symbol equals the ROM span `[0x0811802C, 0x0811836C)`: SHA-256 `41c9928af63d768865ae8933ccc6a72d2805135cbc2d35033514fd8222d7b353` for both. `.text` is exactly 832 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each is added with its address as the value (`"data_083A5144": "0x083A5144"`):

`data_083A5144`, `data_083A51A4`, `data_083A51D4`, `data_083A5FEC`, `data_083A6000`, `data_083A6018`, `data_083A6028`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0811802C.c` and the data symbols above added: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, `--signed-quotient-profile positive-constant-frame-v1` and `--unsigned-quotient-profile positive-constant-frame-v1` (3) | `stack aliases cannot cross calls in caller-clobbered registers` |
| `--addressed-runtime-profile addressed-native-bios-fill-buffer-data-v1`, `--addressed-runtime-profile compiler-signed-runtime-data-v1`, `--addressed-runtime-profile addressed-native-bios-fill-scalar-control-numeric-mmio-code-image-data-v1` and 23 other addressed-runtime selectors (26) | `addressed data requires a mapped object and signed32 addend` |
| `--addressed-runtime-profile addressed-native-bios-fill-buffer-v1`, `--addressed-runtime-profile addressed-native-bios-fill-readonly-two-words-v1`, `--addressed-runtime-profile addressed-native-bios-ordinary-v1` and 10 other addressed-runtime selectors (13) | `addressed signed runtimes exclude data and irregular relocations` |
| `conditional-scheduler-descriptor-calls-v1`, `conditional-scheduler-descriptor-payload-calls-v1`, `conditional-scheduler-descriptor-payload8-calls-v1` and `conditional-scheduler-two-payload-calls-v1` (4) | `scheduler contract requires one actual scheduler call` |
| `conditional-scheduler-branch-descriptor-calls-v1`, `conditional-scheduler-following-call-v1` and `conditional-scheduler-eight-target-branches-v1` (3) | `scheduler branches exceed the explicit call-site or target bounds` |
| `conditional-scheduler-twenty-four-target-branches-v1`, `conditional-scheduler-live-local-alias-calls-v1`, `conditional-scheduler-live-local-alias-payload-calls-v1` and 4 other scheduler selectors (7) | `predicate composition excludes CFG cycles` |
| `conditional-scheduler-u16-counted-loop-v1` | `counted scheduler loop requires a complete bounded instruction graph` |
| `conditional-scheduler-sequential-live-alias-counted-loops-v1` | `scheduler loop composition requires a complete bounded instruction graph` |
| `conditional-scheduler-three-per-path-live-alias-v1` | `live-alias calls exclude pointer-bearing slots and word provenance` |
| `conditional-scheduler-entry-descriptor-calls-v1` | `scheduler entry contract requires one actual pinned entry call` |
| `bounded-buffer-runtime-summaries-v1`, `named-data-buffer-v1`, `named-data-buffer-dead-argument-aliases-v1` and 17 other selectors (20) | `buffer callee 0x080E03F8: unresolved program-counter write` |
| `bounded-buffer-bios-mixed-fast-fill-runtime-summaries-v1`, `bounded-buffer-bios-fast-fill-source-v1` and `bounded-buffer-bios-mixed-fast-fill-source-v1` (3) | `CpuFastSet fill requires only its actual direct wrapper calls` |
| `named-data-buffer-finite-small-copy-binding-v1` | `one actual canonical small-copy call required` |
| `named-data-buffer-compiler-copy80-binding-v1` | `compiler copy requires exactly one memcpy call and named data only` |
| `named-data-buffer-known-query-callee-v1`, `descriptor-output-alias-v1`, `descriptor-single-store-v1` and 3 other descriptor and preservation selectors (6) | `buffer callee 0x080E03F8: structural inventory is not closed` |
| `named-data-buffer-stack-index-v1` and `named-data-buffer-stack-index-v2` (2) | `variable stack indices exclude pointer-bearing or return-carrying local words` |
| `bounded-buffer-bios-bg-affine-set-v1`, `bounded-buffer-bios-bg-affine-set-transparent-leaf-scratch-v1` and `bounded-buffer-bios-bg-affine-set-discarded-scratch-v1` (3) | `BgAffineSet requires an actual direct call in its closed owner` |
| `bounded-buffer-bios-mixed-cpuset-fast-fill-source-v1` | `mixed CpuSet/CpuFastSet fill requires actual calls to both wrappers` |
| `bounded-buffer-guarded-switch-v1`, `bounded-buffer-guarded-callee-aliases-v1` and `bounded-buffer-guarded-bios-division-v1` (3) | `buffer callee 0x080E03F8: unsupported stack-alias use or escape` |
| `bounded-buffer-root-guarded-switch-v1` | `root buffer requires one exact guarded switch and ordinary calls` |
| `bios-word-switch-local-buffers-v1` | `BIOS buffer requires one exact one-object-word switch without local BL` |

7 more selectors of these families refuse on contracts for other shapes: `projected outputs require four ordered helpers and one scheduler` (`conditional-scheduler-projected-outputs-v1`); `guarded scheduler requires predicates and exactly one scheduler site` (`conditional-scheduler-guarded-descriptor-calls-v1`); `halfword payload requires one exact output leaf and one scheduler site` (`conditional-scheduler-halfword-output-payload-v1`); `scheduler entry branches require exactly two pinned wrapper call sites` (`conditional-scheduler-entry-branch-descriptor-calls-v1`); `indirect manager contract requires one direct scheduler call` (`conditional-scheduler-indirect-manager-v1`); `manager offset contract requires one direct scheduler call` (`conditional-scheduler-manager-offset-v1`); `manager paths contract requires one direct scheduler call` (`conditional-scheduler-manager-paths-v1`).

The other 105 selector values are not listed one by one (none matched); by family: callback and closure (21), private float and double (15), switch-layout (13), owner (12), restoring-owner (9), canonical-integer (8), function-address (6), bounded-buffer (6), arithmetic-runtime (5), descriptor and preservation (5), addressed-runtime (3), control-flow (1), -O0 (1).

## Cause

The callback words (`func_081179B4`, `func_08117B9C`) and the named data put the default run on the
function-literal path, which has no buffer proof: `stack aliases cannot cross calls in caller-clobbered registers`. That
is why the switch-callee issue lists this function under "Not covered": its rule is in the buffer walk, which the
default path never reaches. The selectors that carry a buffer proof walk `&point` into `func_080E03F8` and stop at its
dispatch (`buffer callee 0x080E03F8: unresolved program-counter write`); `bounded-buffer-guarded-switch-v1`, which can
inspect that guarded table, gets past it and stops at a stack alias inside the callee (`buffer callee 0x080E03F8:
unsupported stack-alias use or escape`), the next refusal the #192 comment reports for the four other callers of
`func_080E03F8`. The scheduler selectors refuse the member loop of phase 0 (`predicate composition excludes CFG cycles`,
7 of 25) or the pointer words.

## Source notes

From the attempt, not reviewed: `second`, `fill_a` and `fill_b` are pointer locals into `pos[4]`
(`second = &pos[1]; func_0801E6F0(pos, second); ... *fill_a = 0x56E; func_0814186C(fill_a, ...)`); they are the kind
of local the source rules look at as possible steering. The loop counter `i` is reused as the effect count (`i =
(index & 1) ? 4 : 2`) in phase 0x106. The descriptor `payload->owner` is read as `*(void **)((u8 *)descriptor + 4)`.

kit issue: (to be filed - match.py: the generic buffer walk cannot inspect a callee that contains a jump table (`buffer callee 0x...: unresolved program-counter write`), although two buffer proofs already decode the layout) (listed under "Not covered": on the function-literal path the callee walk is not reached)
