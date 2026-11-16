# 0x08027918 - three-category cost menu: bytes identical, refused (local MenuList cleared through a _call_via_r2 callback) (462 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp 1dbc8297df. Compiled with agbcc -mthumb-interwork -O2 and linked by hand at
0x08027918 with every callee and data symbol bound to its ROM address and _call_via_r2 at 0x0814224C, the source gives
all 462 bytes of [0x08027918, 0x08027AE6). Index row correct; no new data symbols (all five are already mapped).
plausible.py --strict exits 0.

The function builds one menu from all three of a unit's categories (the override bytes at +0x35..+0x37). For each
non-zero category, func_080CCE60 returns the entries and their index range into the local MenuList, and every entry
of type 1 or 4 that passes func_080CD560 and func_080CCD50(id, 0x13) is appended to context->indices. An entry is
disabled in context->enabled when func_080CDB3C(unit) holds and func_080CCD50(id, 0x14) does not, or when its cost
(func_080258C4) exceeds the unit's points less the cost reserved for the current selection, which is counted only
when both bits of g_state_0200F390.flags & 0x60 are set. The menu gets the count and state 9.

Refusals:
- default: `buffer callee 0x0814224C: non-leaf indirect control flow requires linked CFG verification`
- `--function-address-profile canonical-thunks-v1`: `stack aliases cannot cross calls in caller-clobbered registers`
- `--owner-runtime-profile bounded-buffer-conditional-thunks-v1`, `-discarded-scratch-v1`, `-selective-scratch-v1`,
  `-root-return-scratch-v1`: `conditional indirect call excludes local argument aliases and pointer words`
- `--owner-runtime-profile static-callback-buffer-v1`: `owner requires sole complete Thumb ELF function`
- `--owner-runtime-profile conditional-local-state-iterator-v1`: `state contract requires the exact four-byte state and
  initialized visitor interface`
- `--owner-runtime-profile named-data-buffer-v1`: `acyclic owner excludes arithmetic runtimes and indirect thunks`
- `--owner-runtime-profile bounded-buffer-runtime-summaries-v1`: `runtime summary owner requires exact canonical
  division entries and no thunks`
- `--switch-data-profile switch-thunks-frame-v1`: `switch thunks require a complete local switch, objects and no
  other runtime`
- `--function-address-profile canonical-thunks-interposed-pool-v1`: `canonical-thunks-interposed-pool-v1 linking
  requires its complete local switch`

Cause: the 12-byte local MenuList at sp+0 is cleared by g_callbacks_0836D4B8[0](&list, sizeof(list)), entry 0 of a
ROM table that points into the code image installed at 0x03005E78, called through _call_via_r2 with `mov r0, sp`
(0x0802792E). &list.first and &list.last are later passed to func_080CCE60. No selector admits a local buffer as the
argument of a _call_via_rN call outside the fixed four-byte shape of conditional-local-state-iterator-v1. Same gap:
0x080CCFB8, 0x080CD0EC.

Source notes, to settle before this could ship:
- The entry checks are a once-through `while (1) { ...; break; }` block, as in src/08026D44.c. The ROM keeps the
  func_080CCD50(id, 0x14) half of the first check after the cost check (0x08027A98, branching back to 0x08027A5C);
  the if/else spelling gives 218/462. A bare once-through loop in a function body needs a ruling before it ships.
- `selected` (the cost entry of the current selection) is needed for the literal order: without it 434/462. It has
  the shape of the `resource` local in the loop and in src/08026D44.c, but a reviewer has to rule that it is not a
  spare temporary.
- `MenuState` names a u16 count at +4 (the ROM stores a halfword there at 0x08027AD4; src/08027800.c has `u16 count`
  at the same place) and `MenuContext` a u8 selection at +0xA, where the sibling definitions have unknown bytes.
- `s32 cost` where the siblings use u32: this function compares signed (0x08027A80 `bge`).

Tracked upstream: https://github.com/shubshub/fftadecomp-kit/issues/190
