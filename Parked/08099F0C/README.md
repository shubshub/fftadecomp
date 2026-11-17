# 0x08099F0C - unit lookup by position (two-word closure): bytes identical, refused (a two-word closure with a function literal to 080C7CC0) (76 bytes)

Attempt 2026-11-18, kit 750d2fb7, decomp main 52ef3ba2f9.
`func_08099F0C(object, x, z)` builds an eight-byte state `{object, x, z}` and the closure `{&state, func_0809AC30}`
and walks the lookup's list with `func_080C7CC0(list, func_0809ABE8, &closure)` (0x08099F3C). No `bl` or literal word
in the ROM reaches it.

The index row `08099F0C 08099F58 76 29 return` is right: 29 reachable instructions, the count the kit's own CFG
refinement gives. `config/functions.json` has the same extent and count.

## Byte identity

`08099F0C.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08099F0C, with every callee and data symbol bound to its
ROM address (1 `R_ARM_THM_CALL`, 2 `R_ARM_ABS32`). The 76-byte symbol equals the ROM span `[0x08099F0C, 0x08099F58)`:
SHA-256 `7a69e6c254146063dbaaf6afeffbbee42faa222cbb41cd77f92745da37ad81ab` for both. `.text` is exactly 76 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 750d2fb7, `match.py --root . --no-write` with this source copied to `src/08099F0C.c` (no data symbol to add): the
default run, the 20 callback, closure, static-callback and state-iterator selectors the #89 comment measures, and the
known-query stack-buffer selector. None matched.

| Selector | Result |
|---|---|
| default | `unsupported stack-alias use or escape; function-buffer proof: buffer callee 0x080C7CC0: function-buffer evidence excludes runtime call thunks in inspected dependencies` |
| `conditional-two-word-callback-closure-v1` and `conditional-two-word-tree-callback-closure-v1` (2) | `two-word closure requires exact typed bindings before effect proof` |
| `conditional-two-word-literal-callback-closure-v1` | `literal closure requires one complete natural root form` |
| `conditional-known-query-native-closure-v1` | `known-query closure requires exact genuine typed bindings` |
| `conditional-known-list-query-closure-v1` | `unsupported known-list query root` |
| `conditional-local-state-iterator-v1` | `state contract requires the exact four-byte state and initialized visitor interface` |
| `static-callback-buffer-v1`, `static-callback-unwritten-r7-v1`, `static-callback-restoring-r6-v1` and `static-callback-restoring-r6-target-v1` (4) | `buffer callee 0x080C7CC0: buffer callee 0x0809ABE8: buffer access overlaps a pointer-bearing argument slot` |
| `static-callback-restoring-r6-target-aligned-v1`, `static-callback-restoring-r6-target-leaf-alias-aligned-v1`, `static-callback-restoring-r6-target-leaf-alias-local-scratch-aligned-v1` and 6 other selectors (9) | `aligned owner requires actual external two-byte Thumb alignment` |
| `static-callback-local-output-word-return-r7-v1` | `word-result callback root requires one bound call and one typed callback literal` |
| `conditional-known-query-stack-buffer-v1` | `known-query stack buffer requires exact call/data-only original bindings` |

## Cause

The default path refuses the closure (`unsupported stack-alias use or escape`), and its function-buffer fallback stops
in the iterator's runtime thunk. None of the 20 callback and closure selectors admits it (table above); the
literal-closure selector knows only the 36-, 40- and 44-byte root forms.

kit issue: shubshub/fftadecomp-kit#89 (comment)
