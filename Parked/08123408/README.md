# 0x08123408 - script command: resolve a coordinate pair, then pass the argument record to one of two handlers: bytes identical, refused (callback reached deep in a buffer callee chain) (108 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321 with the match batches then queued for merge (PRs #200 onward). This entry refreshes the earlier `Parked/08123408/` (written before the outgoing-argument store was accepted);
the source is unchanged (same file). `u32 func_08123408(context, script)` handles one script command. It builds an
eight-byte argument record on the stack (selector and mode as eight-bit `u32` bitfields, signed halfwords `x` and `y`, an unsigned halfword
amount), calls `func_08124E74(selector, (s8)script[2], (s8)script[3], &x, &y)` with `&x` (`sp+6`) in R3 and `&y`
(`sp+8`) in the outgoing word, stores `script[4]` as the mode and `script[6] | script[7] << 8` as the amount, and passes
the record by value to `func_08127C10(context, record)` when `script[5] == 1` (0x08123450) or to `func_08127BC4` otherwise
(0x08123462); it returns 0x115. It is the sibling of `0x08123398`, which makes the same `func_08124E74` call.

```
08123428  add  r6, sp, #4         @ the record
0812342A  mov  r3, sp
0812342C  adds r3, #6             @ &record.x
0812342E  add  r4, sp, #8         @ &record.y
08123430  str  r4, [sp]           @ -> fifth argument
08123432  bl   0x08124E74
```

## The index

`symbols/functions.txt` has `08123408 08123474 108 46 return` and `config/functions.json` the same extent with 46 instructions (`thumb-prologue`). The CFG, closed by the kit's own `analyze.refine_function`, has 46 reachable instructions, so the row is right.

## Byte identity

`08123408.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08123408, with every callee bound to its ROM address and every data word to the address its symbol names (3 `R_ARM_THM_CALL`). The 108-byte symbol equals the ROM span `[0x08123408, 0x08123474)`: SHA-256 `28e9749f4b1437e444bed0fecb834cce58748b73c794e6494f23e5d2581ef153` for both. `.text` is exactly 108 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

None: the function has no data relocation.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08123408.c`: the default run and all 213 selector values. None matched.

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

The same chain as the sibling `0x08123398`. The two coordinate pointers are addresses in the caller's frame,
so the buffer walk follows them into `func_08124E74` (matched, `src/08124E74.c`), which keeps them in callee-saved
registers across its calls, down to `func_08099560`; that function passes its own local search record and the fixed
callback `func_0809AB5C` to the list walk `func_080C7CC0`, which calls the callback through `_call_via_r6`
(`bl 0x0814225C`, `bx r6`). The walk refuses an indirect jump in a non-leaf callee: `buffer callee 0x08124E74: buffer
callee 0x08099560: buffer callee 0x080C7CC0: buffer callee 0x0814225C: non-leaf indirect control flow requires linked
CFG verification`. The callback is fixed two calls up, by `func_08099560`, but the walk examines `func_080C7CC0` on its
own; `static-callback-buffer-v1` says so (`static callback target register is not an exact Thumb function pointer`, at
`func_080C7CC0`).

None of the callback and closure selectors admits it: the two-word closure selectors give `two-word closure requires
exact typed bindings before effect proof`, `conditional-two-word-literal-callback-closure-v1` gives `literal closure
requires one complete natural root form`, the nine aligned static-callback selectors refuse the missing `c046` tail
(`aligned owner requires actual external two-byte Thumb alignment`), and three more refuse at `func_08124E74`
(`descriptor call does not prove preservation of a live alias register`). The #89 comment's suggestion, passing a
caller's constant arguments into the callee walk, would turn the `bl 0x0814225C` into a direct call to a known
function.

## History

- The earlier attempt, at an older kit, was refused with `unsupported stack-alias use or escape` at the
  outgoing-word store at 0x08123430; kit 18dcc516 accepts it and stops in the callee chain.
- The index row then ended at 0x08123434, inside the first `bl`; it is now the full `08123408 08123474 108 46`.
- The first natural C candidate was byte-identical; no other spelling was needed.

kit issue: shubshub/fftadecomp-kit#89 (comment)
