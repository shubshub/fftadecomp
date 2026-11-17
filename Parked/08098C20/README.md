# 0x08098C20 - collect, sort and re-insert the units of a list (direct 080C7CC0 closure): bytes identical, refused (a local address stored in the closure word) (200 bytes)

Attempt 2026-11-18, kit 750d2fb7, decomp main 52ef3ba2f9.
`func_08098C20(owner)` collects up to 13 entries of the owner's list into a local array with the closure `{&state,
func_0809AC20}` passed to `func_080C7CC0(list, func_0809ABE8, &closure)` (0x08098C40; `closure.argument = &state;`,
where `state` holds the count and a cursor into the array), sorts them by the unit's `(unknown_F6 << 8) + unknown_F7`,
highest first, and stores each one's rank in its unit (`unknown_104`). Its caller is the matched `src/0809A9A8.c`
(0x0809A9AC).

The index row `08098C20 08098CE8 200 100 return` has the right extent; 100 is half the byte count, and the reachable
count is 95 (the kit's own CFG refinement). `config/functions.json` has the same extent and count.

## Byte identity

`08098C20.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08098C20, with every callee and data symbol bound to its
ROM address (1 `R_ARM_THM_CALL`, 2 `R_ARM_ABS32`). The 200-byte symbol equals the ROM span `[0x08098C20, 0x08098CE8)`:
SHA-256 `415dc99b26362a5fc40cf232cebfffc8c8a4c365fd8caf4c88a53800f511eebe` for both. `.text` is exactly 200 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 750d2fb7, `match.py --root . --no-write` with this source copied to `src/08098C20.c` (no data symbol to add): the
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

The local state's address is stored into the closure word, which the default path refuses (`stack aliases cannot be
stored or spilled`), and so does its function-buffer fallback. None of the 20 callback and closure selectors admits it
(table above).

kit issue: shubshub/fftadecomp-kit#89 (comment)
