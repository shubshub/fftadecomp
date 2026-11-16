# 0x080E29C4 - effect piece spawner: bytes identical, refused (inert spin together with named data) (536 bytes)

Attempt 2026-11-14, kit fcdf2d45. Compiled with agbcc -mthumb-interwork -O2 and linked by hand at 0x080E29C4 with every
callee and data symbol bound to its ROM address, the source gives all 536 bytes of [0x080E29C4, 0x080E2BDC). Index row
correct.

The function advances a palette slot, loads the requested palette, then for each piece of data_08395CC4[group] takes
a free object slot (or frees the slot whose age is 1 and ages the others) and spawns the piece with func_080D5CC0.
When a free slot is found but the next age would exceed 8, it spins forever (`if (age > 8) while (1);`, a `b .`
reached by a conditional branch). Every other path returns normally.

Needs two data symbols (not in config/data_symbols.json): data_08395CC4 (piece groups) and data_08395E64 (palette
entries).

Refusals, with both symbols added:
- default: `reachable control-flow region has no path to a verified return`
- `--control-flow-profile mixed-return-inert-spin-v1`: `inert spins exclude non-call relocations`

Cause: the inert-spin profile admits the self-branch but excludes every non-call relocation
(tools/inert_spin_profile.py:160), so named data cannot be combined with it. In a copy of the kit with only that
exclusion removed, match.py reports MATCH - byte identical.

Choice the bytes do not fully pin: the redundant zero test `slot = found; if (found == 0) slot = 0;`.

Same gap: 0x08118590 (inert spin with named data); 0x0800221C and 0x080231C0 need it too, together with a
non-returning arm that stores before it loops.
