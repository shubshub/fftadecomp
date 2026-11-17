# 0x080C68EC - slot set-up from an 08099CDC query: bytes identical, refused (the 080C7CC0 callback reached inside the matched 08099CDC) (220 bytes)

Attempt 2026-11-18, kit 750d2fb7, decomp main 52ef3ba2f9.
`func_080C68EC(owner, source)` clears 0xC4 bytes of the owner through `g_callbacks_0836D4B8[0]` (`_call_via_r2`,
0x080C6900), stores `source`, queries up to 13 entries with `func_08099CDC(source, found)` (0x080C690A), keeps at most
two of them that pass `func_08133BC4`, and queues the states 0x12, 5, 8 and 2. Its caller is the matched
`src/080C7554.c` (0x080C7556).

The index row `080C68EC 080C69C8 220 110 return` has the right extent; 110 is half the byte count, and the reachable
count is 104 (the kit's own CFG refinement). `config/functions.json` has the same extent and count.

## Byte identity

`080C68EC.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080C68EC, with every callee and data symbol bound to its
ROM address (3 `R_ARM_THM_CALL`, 1 `R_ARM_ABS32`). The 220-byte symbol equals the ROM span `[0x080C68EC, 0x080C69C8)`:
SHA-256 `7c9788a87bba6fae4251b264f669ea410a82f5f02ddeb72d8785cdd0cbcad05d` for both. `.text` is exactly 220 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 750d2fb7, `match.py --root . --no-write` with this source copied to `src/080C68EC.c` (no data symbol to add): the
default run, the 20 callback, closure, static-callback and state-iterator selectors the #89 comment measures, and the
known-query stack-buffer selector. None matched.

| Selector | Result |
|---|---|
| default | `buffer callee 0x08099CDC: buffer callee 0x080C7CC0: buffer callee 0x0814225C: non-leaf indirect control flow requires linked CFG verification` |
| `conditional-two-word-callback-closure-v1`, `conditional-two-word-tree-callback-closure-v1`, `conditional-two-word-literal-callback-closure-v1` and 9 other selectors (12) | `refused: function-address evidence does not support runtime call thunks` |
| `static-callback-restoring-r6-target-aligned-v1`, `static-callback-restoring-r6-target-leaf-alias-aligned-v1`, `static-callback-restoring-r6-target-leaf-alias-local-scratch-aligned-v1` and 6 other selectors (9) | `aligned owner requires actual external two-byte Thumb alignment` |

## Cause

As for 0x080BAB90, the default walk stops at `_call_via_r6` inside `func_080C7CC0`, two calls down. The closure,
state-iterator, known-query and five static-callback selectors refuse the owner's `_call_via_r2` call (`refused:
function-address evidence does not support runtime call thunks`), the literal-closure row the #89 comment quotes.

kit issue: shubshub/fftadecomp-kit#89 (comment)
