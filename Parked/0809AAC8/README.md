# 0x0809AAC8 - clear a flag word of every collected object: bytes identical, refused (a local address stored in the closure word) (68 bytes)

Attempt 2026-11-18, kit 750d2fb7, decomp main 52ef3ba2f9.
`func_0809AAC8(state)` collects up to 13 objects of the state's list into a local array with the closure `{&output,
func_0809AC20}` (`func_080C7CC0` at 0x0809AAE2) and clears `unknown_04` of each. Its caller is 0x080A433C
(0x080A437A).

The index row `0809AAC8 0809AB0C 68 34 return` has the right extent; 34 is half the byte count, and the reachable
count is 28 (the kit's own CFG refinement). `config/functions.json` has the same extent and count.

## Byte identity

`0809AAC8.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0809AAC8, with every callee and data symbol bound to its
ROM address (1 `R_ARM_THM_CALL`, 2 `R_ARM_ABS32`). The 68-byte symbol equals the ROM span `[0x0809AAC8, 0x0809AB0C)`:
SHA-256 `a290a038737f7eff7f667d4753fca0f442432b69a6cac96112015b35944712cb` for both. `.text` is exactly 68 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 750d2fb7, `match.py --root . --no-write` with this source copied to `src/0809AAC8.c` (no data symbol to add): the
default run, the 20 callback, closure, static-callback and state-iterator selectors the #89 comment measures, and the
known-query stack-buffer selector. None matched.

| Selector | Result |
|---|---|
| default | `stack aliases cannot be stored or spilled; function-buffer proof: stack aliases cannot be stored or spilled` |
| `conditional-two-word-callback-closure-v1` and `conditional-two-word-tree-callback-closure-v1` (2) | `two-word closure requires exact typed bindings before effect proof` |
| `conditional-two-word-literal-callback-closure-v1` | `literal closure requires one complete natural root form` |
| `conditional-known-query-native-closure-v1` | `known-query closure requires exact genuine typed bindings` |
| `conditional-known-list-query-closure-v1` | `unsupported known-list query root` |
| `conditional-local-state-iterator-v1` | `state contract requires the exact four-byte state and initialized visitor interface` |
| `static-callback-buffer-v1`, `static-callback-unwritten-r7-v1`, `static-callback-restoring-r6-v1` and `static-callback-restoring-r6-target-v1` (4) | `stack aliases cannot be stored or spilled` |
| `static-callback-restoring-r6-target-aligned-v1`, `static-callback-restoring-r6-target-leaf-alias-aligned-v1`, `static-callback-restoring-r6-target-leaf-alias-local-scratch-aligned-v1` and 6 other selectors (9) | `aligned owner requires actual external two-byte Thumb alignment` |
| `static-callback-local-output-word-return-r7-v1` | `word-result callback root requires one bound call and one typed callback literal` |
| `conditional-known-query-stack-buffer-v1` | `known-query stack buffer requires exact call/data-only original bindings` |

## Cause

As for 0x0809AA38: `stack aliases cannot be stored or spilled`. None of the 20 callback and closure selectors admits
it (table above).

## Source notes

- The clearing loop is a `static inline Clear0809AAC8` helper; written out in place the bytes differ (13 halfwords,
  measured). No function in the ROM corresponds to it; it does a real operation (it clears `unknown_04` of each
  collected object), so it is not one of the refused helper shapes, but earlier notes flag it as a loop-order doubt
  and it is a review question.

kit issue: shubshub/fftadecomp-kit#89 (comment)
