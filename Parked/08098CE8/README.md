# 0x08098CE8 - collect, sort and re-insert units (inlined 08099CDC collect): bytes identical, refused (a local address stored in the closure word) (402 bytes)

Attempt 2026-11-18, kit 750d2fb7, decomp main 52ef3ba2f9.
`func_08098CE8(context)` collects up to 13 objects of the context's list into a local array with the closure `{&state,
func_0809AC20}` passed to `func_080C7CC0(list, func_0809ABE8, &closure)` (0x08098D08), calls `func_080971F8` for each,
sorts them by their unit's order, and re-inserts each one into the owner's first, second or third list
(`func_080C7BF4`, `func_080C7A74`, `func_080C7AB4`) according to `func_080C8298` and `func_080C8240`. Its caller is
the matched `src/0809A9A8.c` (0x0809A9B2).

The index row `08098CE8 08098E7A 402 201 return` has the right extent; 201 is half the byte count, and the reachable
count is 178 (the kit's own CFG refinement). `config/functions.json` has the same extent and count.

## Byte identity

`08098CE8.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08098CE8, with every callee and data symbol bound to its
ROM address (18 `R_ARM_THM_CALL`, 2 `R_ARM_ABS32`). The 402-byte symbol equals the ROM span `[0x08098CE8,
0x08098E7A)`: SHA-256 `a897285ea11b861c7bee0a53c5d091b43273ea7412457c072057f44e06ab1915` for both. `.text` is 404
bytes: the symbol and the `c0 46` alignment halfword after it. `match.py` refuses before its own byte comparison
(below). `plausible.py --strict` exits 0.

## Refusals

Kit 750d2fb7, `match.py --root . --no-write` with this source copied to `src/08098CE8.c` (no data symbol to add): the
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
| `static-callback-buffer-v1`, `static-callback-unwritten-r7-v1`, `static-callback-restoring-r6-v1` and 2 other selectors (5) | `owner requires sole complete Thumb ELF function` |
| `static-callback-restoring-r6-target-aligned-v1`, `static-callback-restoring-r6-target-leaf-alias-aligned-v1`, `static-callback-restoring-r6-target-leaf-alias-local-scratch-aligned-v1` and 6 other selectors (9) | `stack aliases cannot be stored or spilled` |
| `conditional-known-query-stack-buffer-v1` | `known-query stack buffer requires exact call/data-only original bindings` |

## Cause

As for 0x08098C20: `stack aliases cannot be stored or spilled` on the default path and its function-buffer fallback.
None of the 20 callback and closure selectors admits it (table above).

## Source notes

- The collect step is a `static inline` helper with the body of `func_08099CDC`, which the ROM also has as a separate
  function; here the compiler inlined it. Its statements are those of the matched `src/08099CDC.c` (shared text).

kit issue: shubshub/fftadecomp-kit#89 (comment)
