# 0x0800221C - key input update: bytes identical, refused (store-then-spin arm with named data) (436 bytes)

Attempt 2026-11-14, kit fcdf2d45. Compiled with agbcc -mthumb-interwork -O2 and linked by hand at 0x0800221C with both
data symbols bound to their ROM addresses, the source gives all 436 bytes of [0x0800221C, 0x080023D0). Index row
correct; data_03000ED0 and data_03000E10 are already in config/data_symbols.json.

The function updates a key-input state from the current key mask: edge bits, held-key repeat with first and next
delays, and the lowest repeating key (func_0800221C_first_key, a static inline used at both repeat sites). When the
mask is exactly 0xF (A, B, Select and Start) it writes the soft-reset code 0xA3, 0x5D to data_03000ED0
(0x08002232-0x08002238) and spins (`b .` at 0x0800223A). Every other path returns normally.

Refusals:
- default: `reachable control-flow region has no path to a verified return`
- `--control-flow-profile mixed-return-inert-spin-v1`: `inert spins exclude non-call relocations`

Cause: two gaps. The inert-spin profile excludes every non-call relocation (tools/inert_spin_profile.py:160). With
only that exclusion removed in a copy of the kit, the next refusal is `every non-return-reaching node must itself be
an inert narrow self-branch` (tools/match.py:5157-5168): the arm stores the two bytes before it spins. It needs named
data with inert spins, and a non-returning arm made of a store prefix followed by the self-branch.

Same pair of stores: 0x080231C0 (the soft-reset request, which then loops on a call). Same data gap: 0x080E29C4,
0x08118590.
