# 0x0809A204 - guarded flag query over a unit list (two-word closure): bytes identical, refused (a two-word closure with a function literal to 080C7CC0) (64 bytes)

Attempt 2026-11-18, kit 750d2fb7, decomp main 52ef3ba2f9.
`func_0809A204(owner)` returns 1 when bit 0 of the owner's flags is clear; otherwise it walks the list with the
closure `{&found, func_0809AC88}` (`func_080C7CC0` at 0x0809A226) and returns `found`. Callers: 0x08092784
(0x08095A96; it has a `Parked/` entry) and 0x0809ED38 (0x0809F03A).

The index row `0809A204 0809A244 64 32 return` has the right extent; 32 is half the byte count, and the reachable
count is 26 (the kit's own CFG refinement). `config/functions.json` has the same extent and count.

## Byte identity

`0809A204.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0809A204, with every callee and data symbol bound to its
ROM address (1 `R_ARM_THM_CALL`, 2 `R_ARM_ABS32`). The 64-byte symbol equals the ROM span `[0x0809A204, 0x0809A244)`:
SHA-256 `6f02544a2552c555d9390a8f2e5556b6befd1b4b68499fc386ce96c04528fc11` for both. `.text` is exactly 64 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 750d2fb7, `match.py --root . --no-write` with this source copied to `src/0809A204.c` (no data symbol to add): the
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

The default path refuses the closure, and its function-buffer fallback stops in the iterator's runtime thunk. None of
the 20 callback and closure selectors admits it (table above).

## Source notes

- The callback is first assigned to a local (`callback = func_0809AC88; closure.callback = callback;`), as in the
  merged `src/08099D34.c` and its siblings; assigning the literal directly changes 3 halfwords (measured).

kit issue: shubshub/fftadecomp-kit#89 (comment)
