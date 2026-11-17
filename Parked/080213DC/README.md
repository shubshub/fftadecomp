# 0x080213DC - free-range search in a list (literal callbacks to 080C7CC0 and 080C7D18): bytes identical, refused (an 8-byte local range passed with a function literal to the 080C7D18 iterator) (166 bytes)

Attempt 2026-11-18, kit 750d2fb7, decomp main 52ef3ba2f9.
`func_080213DC(owner, width, start, limit)` calls `func_080C79E0(owner->list)`; if `func_080C7B08` returns 0 or less
it returns `start`, or -1 when `start + width` reaches `limit`. Otherwise it visits the list with `func_080C7CC0(list,
func_080220E8, list)` (0x0802140E), then passes a local `{start, end, width, flags}` record with the callback
`func_08021378` to the iterator `func_080C7D18` (0x08021436), and returns the adjusted start, or -1 when flag 2 is set
or the range is too short. Its caller is the matched `src/08021C90.c` (0x08021CA4).

The index row `080213DC 08021482 166 83 return` has the right extent; 83 is half the byte count, and the reachable
count is 68 (the kit's own CFG refinement). `config/functions.json` has the same extent and count.

## Byte identity

`080213DC.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080213DC, with every callee and data symbol bound to its
ROM address (6 `R_ARM_THM_CALL`, 2 `R_ARM_ABS32`). The 166-byte symbol equals the ROM span `[0x080213DC, 0x08021482)`:
SHA-256 `633491d0e2e8a8e88af0a3b565898354a13b53b77295841a1c2c7338319a9350` for both. `.text` is 168 bytes: the symbol
and the `c0 46` alignment halfword after it. `match.py` refuses before its own byte comparison (below). `plausible.py
--strict` exits 0.

## Refusals

Kit 750d2fb7, `match.py --root . --no-write` with this source copied to `src/080213DC.c` (no data symbol to add): the
default run, the 20 callback, closure, static-callback and state-iterator selectors the #89 comment measures, and the
known-query stack-buffer selector. None matched.

| Selector | Result |
|---|---|
| default | `stack aliases cannot cross calls in caller-clobbered registers; function-buffer proof: buffer callee 0x080C7D18: function-buffer evidence excludes runtime call thunks in inspected dependencies` |
| `conditional-two-word-callback-closure-v1` and `conditional-two-word-tree-callback-closure-v1` (2) | `two-word closure requires exact typed bindings before effect proof` |
| `conditional-two-word-literal-callback-closure-v1` | `literal closure requires one complete natural root form` |
| `conditional-known-query-native-closure-v1` | `known-query closure requires exact genuine typed bindings` |
| `conditional-known-list-query-closure-v1` | `unsupported known-list query root` |
| `conditional-local-state-iterator-v1` | `state contract requires the exact four-byte state and initialized visitor interface` |
| `static-callback-buffer-v1`, `static-callback-unwritten-r7-v1`, `static-callback-restoring-r6-v1` and 2 other selectors (5) | `owner requires sole complete Thumb ELF function` |
| `static-callback-restoring-r6-target-aligned-v1` and `static-callback-restoring-r6-target-leaf-alias-aligned-v1` (2) | `buffer callee 0x080C79E0: buffer callee 0x08007170: buffer callee 0x08006FCC: local branch frame excludes stack-address materialization` |
| `static-callback-restoring-r6-target-leaf-alias-local-scratch-aligned-v1`, `static-callback-restoring-r6-target-leaf-alias-scratch-leaf-kill-aligned-v1`, `static-callback-restoring-r6-target-movs-frame-aligned-v1` and `static-callback-restoring-r6-target-optional-local-frame-aligned-v1` (4) | `buffer callee 0x080C7CC0: named-data buffer dependency budget exceeded` |
| `static-callback-restoring-r6-target-compact-closure-aligned-v1` | `buffer callee 0x080C7CC0: buffer callee 0x080220E8: buffer callee 0x080C7AB4: descriptor call does not prove preservation of a live alias register` |
| `static-callback-restoring-entry-aliases-aligned-v1` | `buffer callee 0x080C7CC0: buffer callee 0x080220E8: buffer callee 0x080C7AB4: buffer callee 0x08007138: buffer callee 0x08006EC0: buffer callee 0x08006C88: scratch leaf kill requires a complete no-call no-frame leaf` |
| `static-callback-restoring-scratch-prefix-aligned-v1` | `buffer callee 0x080C7CC0: buffer callee 0x080220E8: buffer callee 0x080C7AB4: buffer callee 0x08007138: buffer callee 0x08006EC0: structural inventory is not closed` |
| `conditional-known-query-stack-buffer-v1` | `known-query stack buffer requires exact call/data-only original bindings` |

## Cause

The default path refuses the local record held across calls, and its function-buffer fallback enters the iterator
`func_080C7D18`, which calls the callback through a runtime thunk (`function-buffer evidence excludes runtime call
thunks in inspected dependencies`). None of the 20 callback, closure, static-callback and state-iterator selectors
admits it (table above); the #89 comment proposes passing a caller's constant callback literal into the callee walk.

kit issue: shubshub/fftadecomp-kit#89 (comment)
