# 0x08027918 - three-category cost menu: bytes identical, refused (local MenuList cleared through a _call_via_r2 callback) (462 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. The function builds one menu from all three of a unit's
categories (the override bytes at +0x35..+0x37). For each non-zero category, `func_080CCE60` returns the entries and
their index range into the local `MenuList`, and every entry of type 1 or 4 that passes `func_080CD560` and
`func_080CCD50(id, 0x13)` is appended to `context->indices`. An entry is disabled in `context->enabled` when
`func_080CDB3C(unit)` holds and `func_080CCD50(id, 0x14)` does not, or when its cost (`func_080258C4`) exceeds the
unit's points less the cost reserved for the current selection, which is counted only when both bits of
`g_state_0200F390.flags & 0x60` are set. The menu gets the count and state 9. The matched `src/08027DA0.c` calls it.
This entry refreshes the earlier one; the source is unchanged.

The index row `08027918 08027AE6 462 231 return` has the right extent; 231 is half the byte count, and the reachable
count is 202 (the kit's own refinement and an independent CFG walk agree). The earlier entry called the row correct;
its extent is. No refusal below depends on the count.

## Byte identity

`08027918.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08027918, with every callee and data symbol bound to its
ROM address (9 `R_ARM_THM_CALL`, 9 `R_ARM_ABS32`). The 462-byte symbol equals the ROM span `[0x08027918, 0x08027AE6)`:
SHA-256 `59fdc9ecec26bf33bb45368ccebfb7a07d2b1fc9eb50df7cc98df2ca0e818ba2` for both. `.text` is 464 bytes: the symbol
and the assembler's `c0 46` alignment halfword. `match.py` refuses before its own byte comparison (below).
`plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08027918.c` (no data symbol to add): the
default run and the selectors the kit issue and the earlier notes discuss.

| Selector | Result |
|---|---|
| default | `buffer callee 0x0814224C: non-leaf indirect control flow requires linked CFG verification` |
| `bounded-buffer-guarded-switch-v1`, `bounded-buffer-nested-halfword-output-selective-scratch-v1`, `named-data-buffer-v1` | `acyclic owner excludes arithmetic runtimes and indirect thunks` |
| `--function-address-profile canonical-thunks-v1` | `stack aliases cannot cross calls in caller-clobbered registers` |
| `bounded-buffer-conditional-thunks-v1`, `bounded-buffer-conditional-thunks-discarded-scratch-v1`, `bounded-buffer-conditional-thunks-selective-scratch-v1`, `bounded-buffer-conditional-thunks-root-return-scratch-v1` | `conditional indirect call excludes local argument aliases and pointer words` |
| `static-callback-buffer-v1` | `owner requires sole complete Thumb ELF function` |
| `conditional-local-state-iterator-v1` | `state contract requires the exact four-byte state and initialized visitor interface` |
| `bounded-buffer-runtime-summaries-v1` | `runtime summary owner requires exact canonical division entries and no thunks` |
| `--switch-data-profile switch-thunks-frame-v1` | `switch thunks require a complete local switch, objects and no other runtime` |
| `--function-address-profile canonical-thunks-interposed-pool-v1` | `canonical-thunks-interposed-pool-v1 linking requires its complete local switch` |

## Cause

The 12-byte local `MenuList` at sp+0 is cleared by `g_callbacks_0836D4B8[0](&list, sizeof(list))`, entry 0 of a ROM
table that points into the code image installed at 0x03005E78, called through `_call_via_r2` with `mov r0, sp`
(0x0802792E). `&list.first` and `&list.last` are later passed to `func_080CCE60`. No selector admits a local buffer as
the argument of a `_call_via_rN` call outside the fixed four-byte shape of `conditional-local-state-iterator-v1`.
Behind the clear, `func_080CCE60` reaches `func_080C8570`, whose jump table is loaded before its guard, so a summary
of the clear alone does not admit it (the #190 comment measured this). Same gap: 0x080CCFB8, 0x080CD0EC.

## Source notes

Questions to settle before this could ship (from the earlier entry):

- The entry checks are a once-through `while (1) { ...; break; }` block, as in `src/08026D44.c`. The ROM keeps the
  `func_080CCD50(id, 0x14)` half of the first check after the cost check (0x08027A98, branching back to 0x08027A5C);
  the if/else spelling gives 218/462. A once-through loop written in a function body needs a ruling.
- `selected` (the cost entry of the current selection) is needed for the literal order: without it 434/462. It has the
  shape of the `resource` local in the loop and in `src/08026D44.c`, but a reviewer has to rule that it is not a spare
  temporary.
- `MenuState` names a `u16 count` at +4 (the ROM stores a halfword there at 0x08027AD4; `src/08027800.c` has `u16
  count` at the same place) and `MenuContext` a `u8 selection` at +0xA, where the sibling definitions have unknown
  bytes.
- `s32 cost` where the siblings use `u32`: this function compares signed (0x08027A80 `bge`).

## History

The earlier entry's refusal list (kit 18dcc516) reproduces string for string; the two switch-callee rows are new.

kit issue: shubshub/fftadecomp-kit#190 (comment to be posted); (to be filed - match.py: the generic buffer walk cannot inspect a callee that contains a jump table (`buffer callee 0x...: unresolved program-counter write`), although two buffer proofs already decode the layout)
