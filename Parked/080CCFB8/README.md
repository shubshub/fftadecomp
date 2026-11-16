# 0x080CCFB8 - level-filtered selection list (flag bit 0x80): bytes identical, refused (local buffer cleared through a _call_via_r2 callback) (306 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp 1dbc8297df. Compiled with agbcc -mthumb-interwork -O2 and linked by hand at
0x080CCFB8 with every callee and data symbol bound to its ROM address and _call_via_r2 at 0x0814224C, the source gives
all 306 bytes of [0x080CCFB8, 0x080CD0EA), the 12-byte literal pool and its padding included. Index row correct; no
new data symbols (all three are already mapped). plausible.py --strict exits 0.

The function first collects, in a local `u8 found[0x20]`, the values of the effect pairs whose marker equals
unit->category, from the record g_table_08520080[func_080CA7A4(entry, 0x12)] of each non-zero entry among the unit's
five. It then walks the unit's selection row g_table_0851BA84[func_080C7EA4(unit, 3)] from index 1 to
unit->count - 1 and writes to list each index whose level equals the level argument and that is either flagged on
the unit (bit 0x80 of the byte at +0x40 + index) or in found[]. It returns how many it wrote. 0x080CD0EC is the same
walk with a plain non-zero flag test.

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

Cause: found[] at sp+0 is cleared by g_callbacks_0836D4B8[0](found, sizeof(found)), entry 0 of a ROM table that
points into the code image installed at 0x03005E78, called through _call_via_r2 with `mov r0, sp` (0x080CCFE6). No
selector admits a local buffer as the argument of a _call_via_rN call outside the fixed four-byte shape of
conditional-local-state-iterator-v1. Same gap: 0x08027918, 0x080CD0EC.

The call is written through the table, as most sources on main write it. The by-address spelling
`func_0814224C(found, sizeof(found), g_callbacks_0836D4B8[0])` gives the same bytes and the same default refusal
(kit #133).

Source notes:
- IsFlagged is the text of the matched func_080CD560 (src/080CD560.c, out of line at 0x080CD560), inlined. The ROM
  shows it as a null test of unit after unit has already been dereferenced (0x080CD06E), a 0/1 result that is tested
  again (0x080CD082, 0x080CD094, 0x080CD096) and the u8 narrowing of the index (0x080CD068).
- The bytes depend on two spellings: `row++` is its own statement (`row = g_table_0851BA84[...] + 1` gives
  279/306), and the loop increments are `i++, row++` (`row++, i++` gives 302/306).

Tracked upstream: https://github.com/shubshub/fftadecomp-kit/issues/190
