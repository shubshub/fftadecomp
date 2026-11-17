# 0x08099A70 - order assignment over a unit list (two closure walks and a heap buffer): bytes identical, refused (two two-word closures with function literals to 080C7CC0) (316 bytes)

Attempt 2026-11-18, kit 750d2fb7, decomp main 52ef3ba2f9.
`func_08099A70(owner, excluded)` walks the owner's list with the closure `{excluded, func_0809AD94}` (`func_080C7CC0`
at 0x08099A8E; the sequence 0x08099A80-0x08099A8E is the one the #89 comment quotes), allocates a 0x50-byte array
(`func_08022840`), fills it (`func_0809F78C`), numbers the entries whose order is -2, collects them with a second
closure `{&state, func_0809AC20}` (0x08099B00), sorts them by priority, numbers the rest, and frees the array
(`func_08022854`). Its caller is 0x08092784 (0x0809335A), which has a `Parked/` entry.

The index row `08099A70 08099BAC 316 158 return` has the right extent; 158 is half the byte count, and the reachable
count is 147 (the kit's own CFG refinement). `config/functions.json` has the same extent and count.

## Byte identity

`08099A70.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08099A70, with every callee and data symbol bound to its
ROM address (5 `R_ARM_THM_CALL`, 3 `R_ARM_ABS32`). The 316-byte symbol equals the ROM span `[0x08099A70, 0x08099BAC)`:
SHA-256 `24962ef2fea1a7a83fc309e58e1dd8e3871d0f66abc7af0427c4c65cd65e8fc8` for both. `.text` is exactly 316 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 750d2fb7, `match.py --root . --no-write` with this source copied to `src/08099A70.c` (no data symbol to add): the
default run, the 20 callback, closure, static-callback and state-iterator selectors the #89 comment measures, and the
known-query stack-buffer selector. None matched.

| Selector | Result |
|---|---|
| default | `stack aliases cannot cross calls in caller-clobbered registers; function-buffer proof: buffer callee 0x080C7CC0: function-buffer evidence excludes runtime call thunks in inspected dependencies` |
| `conditional-two-word-callback-closure-v1` and `conditional-two-word-tree-callback-closure-v1` (2) | `two-word closure requires exact typed bindings before effect proof` |
| `conditional-two-word-literal-callback-closure-v1` | `literal closure requires one complete natural root form` |
| `conditional-known-query-native-closure-v1` | `known-query closure requires exact genuine typed bindings` |
| `conditional-known-list-query-closure-v1` | `unsupported known-list query root` |
| `conditional-local-state-iterator-v1` | `state contract requires the exact four-byte state and initialized visitor interface` |
| `static-callback-buffer-v1` | `buffer callee 0x080C7CC0: static callback target register is not an exact Thumb function pointer` |
| `static-callback-unwritten-r7-v1`, `static-callback-restoring-r6-v1` and `static-callback-restoring-r6-target-v1` (3) | `buffer callee 0x080C7CC0: buffer callee 0x0809ABE8: static callback target register is not an exact Thumb function pointer` |
| `static-callback-restoring-r6-target-aligned-v1`, `static-callback-restoring-r6-target-leaf-alias-aligned-v1`, `static-callback-restoring-r6-target-leaf-alias-local-scratch-aligned-v1` and 6 other selectors (9) | `aligned owner requires actual external two-byte Thumb alignment` |
| `static-callback-local-output-word-return-r7-v1` | `word-result callback root requires one bound call and one typed callback literal` |
| `conditional-known-query-stack-buffer-v1` | `known-query stack buffer requires exact call/data-only original bindings` |

## Cause

The default path refuses the closures held across calls, and its function-buffer fallback stops in the iterator's
runtime thunk. None of the 20 callback and closure selectors admits it (table above).

## Source notes

- The callback `func_0809AD94` now has its index row (`0809AD94 0809ADDC 72 29 return`), which an earlier note asked
  for.

kit issue: shubshub/fftadecomp-kit#89 (comment)
