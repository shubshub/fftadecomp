# 0x08128C3C - stat drain by divisor: bytes identical, refused (switch with __udivsi3, __divsi3 and named data) (514 bytes)

Attempt 2026-11-16, kit fcdf2d45. `u8 func_08128C3C(State08128C3C *state, u8 kind)`: a 7-way switch. Cases 0-5 take
`func_080C92F0(unit, stat) / divisor`, clamp the result to 1..99 and lower one u16 field by it. Case 6 does the same
with `10 / divisor`, clamps to 1..10 and applies it to the s16 at +0xD2. The context follows sibling src/08128968.c
(unit at +8, key at +0xC, packed Key as 08128968 declares it).

Compiled with agbcc -mthumb-interwork -O2 and linked by hand at 0x08128C3C with every callee and the data symbol at its
ROM address (__udivsi3 at 0x08142AB0, __divsi3 at 0x081426B8), the source gives all 514 bytes of
[0x08128C3C, 0x08128E3E): instruction halfwords, jump-table words, call sites, pool words and the `c046` padding. The
index extent is correct.

Needs one data symbol (not in config/data_symbols.json): data_083A8260, a u8 divisor table indexed by a 3-bit field
(0a 05 02 01 03 05 0a 14; pool word at 0x08128C64).

Refusals, with the symbol added:
- default: `signed quotient excludes other runtime, literal, switch and thunk profiles` (tools/match.py:1040)
- `--addressed-runtime-profile compiler-signed-runtime-data-v1` / `addressed-integer-runtime-data-v1`: `addressed
  ABS32 requires an aligned unique undefined global with its exact type`
- `--owner-runtime-profile numeric-data-switch-source-v1`: `function address requires a canonical addressed function`
  (from the `__divsi3` call)
- `--owner-runtime-profile canonical-integer-scalar-source-v1`: `canonical integer source requires call-only compiler
  integer identities`
- `--owner-runtime-profile canonical-integer-scalar-data-source-v1`, `ordinary-multiple-switch-source-v1`,
  `restoring-owner-switch-entry-two-words-data-v1`: `owner requires sole complete Thumb ELF function` (516 bytes of
  .text against a 514-byte symbol; tools/owner_admission_profile.py:1001-1007 accepts the external two-byte pad only
  for listed selectors)

Kit gap: no profile combines a switch table with __udivsi3, __divsi3 and named data. The kit already holds a
default-off structural inventory for this shape, tools/one_object_mixed_switch_inventory.py
(`one-object-word-udiv-div-target-state-inventory-v1`, kit 580d5e9a), but no match.py profile uses it yet. Related:
kit #74 (switch compositions).
