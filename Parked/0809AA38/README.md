# 0x0809AA38 - unit lookup by id (closure collect into a local array): bytes identical, refused (a local address stored in the closure word) (90 bytes)

Attempt 2026-11-18, kit 750d2fb7, decomp main 52ef3ba2f9.
`func_0809AA38(owner, id)` collects up to 13 units into a local array with the closure `{&state, func_0809AC20}`
(`func_080C7CC0` at 0x0809AA56) and returns the first whose record id equals `id`, or 0. Its caller is 0x08092784
(0x08092D52), which has a `Parked/` entry.

The index row `0809AA38 0809AA92 90 45 return` has the right extent; 45 is half the byte count, and the reachable
count is 40 (the kit's own CFG refinement). `config/functions.json` has the same extent and count.

## Byte identity

`0809AA38.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0809AA38, with every callee and data symbol bound to its
ROM address (1 `R_ARM_THM_CALL`, 2 `R_ARM_ABS32`). The 90-byte symbol equals the ROM span `[0x0809AA38, 0x0809AA92)`:
SHA-256 `b149a50623b610a02b619c180fe5efdf34a20de632c7662e97b1859945fa2fbb` for both. `.text` is 92 bytes: the symbol
and the `c0 46` alignment halfword after it. `match.py` refuses before its own byte comparison (below). `plausible.py
--strict` exits 0.

## Refusals

Kit 750d2fb7, `match.py --root . --no-write` with this source copied to `src/0809AA38.c` (no data symbol to add): the
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

The default path and its function-buffer fallback refuse the state address stored in the closure word (`stack aliases
cannot be stored or spilled`). None of the 20 callback and closure selectors admits it (table above).

kit issue: shubshub/fftadecomp-kit#89 (comment)
