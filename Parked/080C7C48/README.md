# 0x080C7C48 - tree rebuild from a list (literal callbacks to 080C7D70): bytes identical, refused (a local output word passed with a function literal to the 080C7D70 iterator) (120 bytes)

Attempt 2026-11-18, kit 750d2fb7, decomp main 52ef3ba2f9.
`func_080C7C48(context)` repeatedly asks the iterator `func_080C7D70(context, func_080C7E78, &node)` (0x080C7C9E) for
the next node through a local output word, unlinks it (`func_080C7858`), marks it and inserts it into the binary tree
at `context->root` by key; when no node is left it calls `func_080C7D70(context, func_080C7E94, 0)` (0x080C7CAE).
Callers: the matched `src/0809A018.c`, `src/0809A044.c` and `src/0809A070.c`.

The index row `080C7C48 080C7CC0 120 52 return` is right: 52 reachable instructions, the count the kit's own CFG
refinement gives. `config/functions.json` has the same extent and count.

## Byte identity

`080C7C48.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080C7C48, with every callee and data symbol bound to its
ROM address (3 `R_ARM_THM_CALL`, 2 `R_ARM_ABS32`). The 120-byte symbol equals the ROM span `[0x080C7C48, 0x080C7CC0)`:
SHA-256 `11d3c9ee322f91fea05bf16e12ea8430a2ba7e9456e9ce4250af598ce07a1b0c` for both. `.text` is exactly 120 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 750d2fb7, `match.py --root . --no-write` with this source copied to `src/080C7C48.c` (no data symbol to add): the
default run, the 20 callback, closure, static-callback and state-iterator selectors the #89 comment measures, and the
known-query stack-buffer selector. None matched.

| Selector | Result |
|---|---|
| default | `stack aliases cannot cross calls in caller-clobbered registers; function-buffer proof: buffer callee 0x080C7D70: function-buffer evidence excludes runtime call thunks in inspected dependencies` |
| `conditional-two-word-callback-closure-v1` and `conditional-two-word-tree-callback-closure-v1` (2) | `two-word closure requires exact typed bindings before effect proof` |
| `conditional-two-word-literal-callback-closure-v1` | `literal closure requires one complete natural root form` |
| `conditional-known-query-native-closure-v1` | `known-query closure requires exact genuine typed bindings` |
| `conditional-known-list-query-closure-v1` | `unsupported known-list query root` |
| `conditional-local-state-iterator-v1` | `state contract requires the exact four-byte state and initialized visitor interface` |
| `static-callback-buffer-v1` | `buffer callee 0x080C7D70: static callback target register is not an exact Thumb function pointer` |
| `static-callback-unwritten-r7-v1` | `local stack pointer escapes through a return register` |
| `static-callback-restoring-r6-v1` | `buffer callee 0x080C7D70: callback writes a required unwritten register or SP` |
| `static-callback-restoring-r6-target-v1` | `buffer callee 0x080C7D70: buffer callee 0x080C7E78: scratch projection requires its active exact callee` |
| `static-callback-restoring-r6-target-aligned-v1`, `static-callback-restoring-r6-target-leaf-alias-aligned-v1`, `static-callback-restoring-r6-target-leaf-alias-local-scratch-aligned-v1` and 6 other selectors (9) | `aligned owner requires actual external two-byte Thumb alignment` |
| `static-callback-local-output-word-return-r7-v1` | `word-result callback root requires one bound call and one typed callback literal` |
| `conditional-known-query-stack-buffer-v1` | `known-query stack buffer requires exact call/data-only original bindings` |

## Cause

The default path refuses the local output word held across calls, and its function-buffer fallback enters
`func_080C7D70`, which calls the callback through a runtime thunk. The sibling 0x080C7BC8 matched with
`static-callback-unwritten-r7-v1`; here the callback is kept in r6 and the iterator is called twice, and none of the
20 callback and closure selectors admits it (table above).

kit issue: shubshub/fftadecomp-kit#89 (comment)
