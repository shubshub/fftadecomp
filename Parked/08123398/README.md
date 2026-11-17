# 0x08123398 - script command: resolve a coordinate pair, then queue the argument record: bytes identical, refused (callback reached deep in a buffer callee chain) (96 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321 with the match batches then queued for merge (PRs #200 onward). This entry refreshes `Parked/08123398/` with the revision the #89 comment measured. The function handles one script command. It builds an
eight-byte argument record on the stack at `sp+4` (selector and mode bytes, signed halfwords `x` and `y`, an unsigned
halfword value): `script[1]` goes into the selector byte by a read-modify-write of the record's first word
(0x081233A4-0x081233AE). It calls `func_08124E74(selector, (s8)script[2], (s8)script[3], &x, &y)` (0x081233C6), with
`&x` = `sp+6` in r3 and `&y` = `sp+8` in the outgoing stack word (`add r4, sp, #8; str r4, [sp]` at
0x081233C2-0x081233C4); that callee resolves the two coordinates in place. It then stores `script[4]` as the mode
(0x081233CC) and `script[5] | script[6] << 8` as the value (0x081233D6), passes the record by value in r1/r2 to
`func_08127B80(context, record)` (0x081233DE) and returns 0x115. The matched `src/08123320.c` builds the same record
from other script bytes and makes the same call. The index row `08123398 081233F8 96 42 return` is right (42
instructions; literal words 0xFFFFFF00 at 0x081233F0 and 0x115 at 0x081233F4). The previous revision of this entry
recorded an index row covering only 48 bytes; main's row is now the full 96. No data symbol is needed.

## The index

`symbols/functions.txt` has `08123398 081233F8 96 42 return` and `config/functions.json` the same extent with 42 instructions (`thumb-prologue`). The CFG, closed by the kit's own `analyze.refine_function`, has 42 reachable instructions, so the row is right.

## Byte identity

`08123398.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08123398, with every callee bound to its ROM address and every data word to the address its symbol names (2 `R_ARM_THM_CALL`). The 96-byte symbol equals the ROM span `[0x08123398, 0x081233F8)`: SHA-256 `70622af84b4851aedd5b5cfef65bf6b9c9bdb19076742da693eee592fd84ae5d` for both. `.text` is exactly 96 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

None: the function has no data relocation.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08123398.c`: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, `--signed-quotient-profile positive-constant-frame-v1` and `--unsigned-quotient-profile positive-constant-frame-v1` (3) | `buffer callee 0x08124E74: buffer callee 0x08099560: buffer callee 0x080C7CC0: buffer callee 0x0814225C: non-leaf indirect control flow requires linked CFG verification` |
| `static-callback-restoring-r6-target-aligned-v1`, `static-callback-restoring-r6-target-leaf-alias-aligned-v1`, `static-callback-restoring-r6-target-leaf-alias-local-scratch-aligned-v1` and 9 other selectors (12) | `aligned owner requires actual external two-byte Thumb alignment` |
| `named-data-buffer-v1`, `named-data-buffer-dead-argument-aliases-v1`, `named-data-buffer-rom-table-copy-v1` and 13 other selectors (16) | `buffer callee 0x08124E74: buffer callee 0x08099560: buffer callee 0x080C7CC0: buffer callee 0x0814225C: non-leaf indirect control flow requires linked CFG verification` |
| `named-data-buffer-finite-small-copy-binding-v1` | `one actual canonical small-copy call required` |
| `named-data-buffer-compiler-copy80-binding-v1` | `compiler copy requires exactly one memcpy call and named data only` |
| `conditional-two-word-callback-closure-v1` and `conditional-two-word-tree-callback-closure-v1` (2) | `two-word closure requires exact typed bindings before effect proof` |
| `conditional-two-word-literal-callback-closure-v1` | `literal closure requires one complete natural root form` |
| `conditional-known-query-native-closure-v1` | `known-query closure requires exact genuine typed bindings` |
| `named-data-buffer-known-query-callee-v1` | `buffer callee 0x08124E74: buffer callee 0x08099560: stack-passed pointer words cannot reach a pinned list-query family` |
| `named-data-buffer-stack-index-v1` and `named-data-buffer-stack-index-v2` (2) | `variable stack indices exclude pointer-bearing or return-carrying local words` |
| `static-callback-buffer-v1` | `buffer callee 0x08124E74: buffer callee 0x08099560: buffer callee 0x080C7CC0: static callback target register is not an exact Thumb function pointer` |
| `static-callback-unwritten-r7-v1`, `static-callback-restoring-r6-v1`, `static-callback-restoring-r6-target-v1` and 8 other descriptor and preservation selectors (11) | `buffer callee 0x08124E74: descriptor call does not prove preservation of a live alias register` |
| `static-callback-local-output-word-return-r7-v1` | `word-result callback root requires one bound call and one typed callback literal` |
| `ordinary-formal-output-spill-v1` and `ordinary-formal-output-spill-bios-remainder-v1` (2) | `formal output caller cannot create pointer descriptors` |
| `descriptor-disjunctive-restoring-callee-alias-v1`, `descriptor-restoring-callee-constant-v1` and `bounded-disjunctive-restoring-callee-scratch-v1` (3) | `callee alias saves permit only private PUSH/POP stack access` |
| `--control-flow-profile mixed-return-inert-spin-v1`, `restoring-owner-acyclic-v1` and `restoring-owner-ignored-leaf-alias-v1` (3) | `unsupported stack-alias use or escape` |

6 more selectors of these families refuse on contracts for other shapes: `state contract requires the exact four-byte state and initialized visitor interface` (`conditional-local-state-iterator-v1`); `unsupported known-list query root` (`conditional-known-list-query-closure-v1`); `one known query must be the first complete root call` (`conditional-known-list-query-continuation-v1`, `conditional-nested-known-query-continuation-v1`); `private load reads an uninitialized local word` (`conditional-known-query-stack-buffer-v1`); `known query quotient requires canonical unsigned division only` (`conditional-known-query-stack-buffer-unsigned-quotient-v1`).

The other 147 selector values are not listed one by one (none matched); by family: addressed-runtime (40), scheduler (25), private float and double (15), BIOS buffer (13), switch-layout (13), owner (11), canonical-integer (7), function-address (6), restoring-owner (5), arithmetic-runtime (5), bounded-buffer (5), -O0 (1), guarded-switch buffer (1).

## Cause

The two coordinate pointers are addresses in the caller's frame, so the buffer walk follows them into `func_08124E74`
(matched, `src/08124E74.c`). That function keeps them in callee-saved registers (`&x` in r7 at 0x08124E7A, `&y` in r8
at 0x08124E7E) across its calls to `func_08121CB4`, `func_080C83CC`, `func_08096D7C` and `func_08099560`
(0x08124ED4-0x08124EEC); the refusal shows the walk descending from there into `func_08099560`. `func_08099560`
(`src/08099560.c`) passes its own local search record and the fixed callback `func_0809AB5C` (the literal at
0x0809957C) to `func_080C7CC0` (`src/080C7CC0.c`), a list walk that copies the callback into r6 (0x080C7CC2) and calls
it through `_call_via_r6` (`bl 0x0814225C` at 0x080C7CD4). The thunk is `bx r6`, an indirect jump, and the walk
refuses any indirect jump in a non-leaf callee (`match.py:4837-4838`). The target is fixed two calls up, by
`func_08099560`, but the walk examines `func_080C7CC0` on its own and does not carry that binding down; the
`static-callback-buffer-v1` run says as much
(`static callback target register is not an exact Thumb function pointer`, at `func_080C7CC0`, where r6 is a copy of
its second parameter). None of the calls below `func_08124E74` is passed the caller's two pointers.

None of the callback and closure selectors admits it: the two-word closure selectors give `two-word closure
requires exact typed bindings before effect proof`, `conditional-two-word-literal-callback-closure-v1` gives `literal
closure requires one complete natural root form`, and `static-callback-local-output-word-return-r7-v1` gives
`word-result callback root requires one bound call and one typed callback literal`. The #89 comment proposes passing a
caller's constant arguments into the callee walk, which would make the `bl 0x0814225C` a direct call to a known
function.

## Source notes

- `selector` and `mode` are `u32 : 8` bit-fields, as in `src/08123320.c`. The bytes do not pin that: with plain
  `u8 selector; u8 mode;` members the function compiles to the same 96 bytes, including the read-modify-write of the
  uninitialised first word at 0x081233A8-0x081233AE.
- `x` and `y` are plain `s16` members because their addresses are taken; `src/08123320.c` declares the same halfwords
  as `s32 : 16` bit-fields. The layout is the same. `src/08127B80.c` calls the record `Args08127B80` and declares its
  first parameter as `Owner08127B80 *`; here it is `void *context`.
- The `func_08124E74` prototype matches `src/08124E74.c`.
- This revision differs from the previous one on main only in names (`ScriptArguments`, `value`, following
  `src/08123320.c`) and the header comment; both compile to the same bytes (same SHA-256).

## Ruled out

- Earlier attempt (previous revision, earlier kit; not re-run here): the refusal was
  `unsupported stack-alias use or escape`, at the outgoing-argument store `str r4, [sp]` (0x081233C4). Kit 18dcc516
  accepts that store and stops later, in the callee chain above.
- No alternative spelling was needed for byte identity; the only variant compiled in this attempt is the plain-`u8`
  selector/mode layout above, which is also identical.

kit issue: shubshub/fftadecomp-kit#89 (comment)
