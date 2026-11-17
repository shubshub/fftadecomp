# 0x08097814 - movement-cell evaluation with three closure walks: bytes identical, refused (three two-word closures with a function literal to 080C7CC0) (494 bytes)

Attempt 2026-11-18, kit 750d2fb7, decomp main 52ef3ba2f9.
`func_08097814(context, x, y, argument)` evaluates one map cell for a unit. For negative coordinates it builds a
two-word closure `{&pair, func_0809779C}` on the stack and walks the owner's list with `func_080C7CC0(list,
func_0809ABE8, &closure)` (0x080978BC); the three paths that do so (by `func_080C8298` and `func_080C8240`) each fill
their own closure slot (sp+0x18, sp+0x20, sp+0x28). Otherwise it reads the cell's height and terrain (`func_0801CC7C`,
`func_0801CC18`, `func_0801CD08`) and reports the cell through `func_081491C0` with flags chosen by the terrain and
the unit's state and mode. No `bl` reaches it: its address is the literal word at 0x0809A600 in the matched
`src/0809A5E0.c`.

The index row `08097814 08097A02 494 247 return` has the right extent; 247 is half the byte count, and the reachable
count is 227 (the kit's own CFG refinement). `config/functions.json` has the same extent and count.

## Byte identity

`08097814.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08097814, with every callee and data symbol bound to its
ROM address (10 `R_ARM_THM_CALL`, 4 `R_ARM_ABS32`). The 494-byte symbol equals the ROM span `[0x08097814,
0x08097A02)`: SHA-256 `6b15e5e0cc61fb3cf7436d3345b03b3f0d575d418b2ca6d7781361fabfc24410` for both. `.text` is 496
bytes: the symbol and the `c0 46` alignment halfword after it. `match.py` refuses before its own byte comparison
(below). `plausible.py --strict` exits 0.

## Refusals

Kit 750d2fb7, `match.py --root . --no-write` with this source copied to `src/08097814.c` (no data symbol to add): the
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
| `static-callback-buffer-v1`, `static-callback-unwritten-r7-v1`, `static-callback-restoring-r6-v1` and 2 other selectors (5) | `owner requires sole complete Thumb ELF function` |
| `static-callback-restoring-r6-target-aligned-v1` | `buffer callee 0x0801CC7C: buffer callee 0x0801CD4C: descriptor call does not prove preservation of a live alias register` |
| `static-callback-restoring-r6-target-leaf-alias-aligned-v1` | `buffer callee 0x0801CC7C: local stack pointer escapes through a return register` |
| `static-callback-restoring-r6-target-leaf-alias-local-scratch-aligned-v1` | `buffer callee 0x0801CC7C: consumer observes projected return scratch before a killing write` |
| `static-callback-restoring-r6-target-leaf-alias-scratch-leaf-kill-aligned-v1` | `local branch frame excludes stack-address materialization` |
| `static-callback-restoring-r6-target-movs-frame-aligned-v1` | `discarded exit scratch requires exact local-offset provenance` |
| `static-callback-restoring-r6-target-optional-local-frame-aligned-v1`, `static-callback-restoring-r6-target-compact-closure-aligned-v1`, `static-callback-restoring-entry-aliases-aligned-v1` and `static-callback-restoring-scratch-prefix-aligned-v1` (4) | `buffer callee 0x081491C0: structural inventory is not closed` |
| `conditional-known-query-stack-buffer-v1` | `known-query stack buffer requires exact call/data-only original bindings` |

## Cause

The default path refuses the local closure (`unsupported stack-alias use or escape`), and its function-buffer fallback
stops in the iterator's runtime thunk. None of the 20 callback and closure selectors admits it (table above); the #89
comment's proposal covers the closure.

## Source notes

- The ROM tests `func_080C8240`'s result and both arms build the same closure (`beq 0x080978A8` at 0x08097892; the
  arms at 0x08097894 and 0x080978A8 differ only in the stack slot); the source writes that as `if
  (func_080C8240(object)) visit_units(unit, &pair); else visit_units(unit, &pair);`. Without the test the function
  is shorter (measured: 466 bytes with the call kept and its result unused, 458 without the call, against 494). That
  is the identical-arms question of shubshub/fftadecomp-kit#201, so this does not ship before that is decided.
- The closure set-up is a `static inline visit_units` helper, used at the three sites: it walks the owner's list with
  the pair closure, and the ROM has three copies of it, each with its own closure slot. Written out in place at the
  three sites (one block each) the bytes are the same (measured), so the helper is a factoring, not a byte device.
  Earlier notes also flag `Unit08097814 *unit = argument;` (the `void *` parameter copied to a typed local).

kit issue: shubshub/fftadecomp-kit#89 (comment); related: shubshub/fftadecomp-kit#201 (identical arms)
