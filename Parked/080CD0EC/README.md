# 0x080CD0EC - level-filtered selection list (non-zero flag): bytes identical, refused (local buffer cleared through a _call_via_r2 callback) (270 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp 1dbc8297df. Compiled with agbcc -mthumb-interwork -O2 and linked by hand at
0x080CD0EC with every callee and data symbol bound to its ROM address and _call_via_r2 at 0x0814224C, the source gives
all 270 bytes of [0x080CD0EC, 0x080CD1FA), the 12-byte literal pool included. Index row correct; no new data symbols
(all three are already mapped). plausible.py --strict exits 0.

The function is 0x080CCFB8 with a different flag test. It collects, in a local `u8 found[0x20]`, the values of the
effect pairs whose marker equals owner->category, from the record g_table_08520080[func_080CA7A4(effect, 0x12)] of
each non-zero effect among the owner's five. It then walks the owner's slot row
g_table_0851BA84[func_080C7EA4(owner, 3)] from index 1 to owner->slot_count - 1 and writes to out each index whose
group equals the group argument and that is either enabled on the owner (a non-zero byte at +0x40 + index) or in
found[]. It returns how many it wrote.

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

Cause: found[] at sp+0 is cleared by g_callbacks_0836D4B8[0](found, 0x20), entry 0 of a ROM table that points into
the code image installed at 0x03005E78, called through _call_via_r2 with `mov r0, sp` (0x080CD118). No selector
admits a local buffer as the argument of a _call_via_rN call outside the fixed four-byte shape of
conditional-local-state-iterator-v1. Same gap: 0x08027918, 0x080CCFB8.

Source notes: nothing against the evidence-first rules. The bytes depend on the same two spellings as 0x080CCFB8:
`entry++` is its own statement (`+ 1` in the initializer gives 38/270), and the loop increments are `i++, entry++`
(`entry++, i++` gives 266/270). At integration, the file-local types, which name the same layout as 0x080CCFB8's
differently (SlotOwner/SlotEntry against Unit/SelectionInfo), are merged with that file's.

Tracked upstream: https://github.com/shubshub/fftadecomp-kit/issues/190
