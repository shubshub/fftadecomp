# 0x080CFCD0 - byte-identical by hand link, refused by every selector (2240 bytes)

First attempt (no earlier parked source), 2026-11-16, kit fcdf2d45. Recorded as unmatchable: the evidence requires maintainer review (a verifier
gap, kit #134).

The source here, compiled with agbcc -mthumb-interwork -O2 and linked by hand at 0x080CFCD0 with every callee, data symbol and the
_call_via_r2 / _call_via_r3 thunks bound to their ROM addresses (0x0814224C, 0x08142250), gives 2240 bytes identical to the ROM, including the
nine thunk calls (4 through r2, 5 through r3). plausible.py --strict exits 0.

Needs two data symbols (not in config/data_symbols.json): data_03002850 = 0x03002850 (the 16-byte scratch Item, pool word at 0x080D001C) and
data_08529494 = 0x08529494 (a u16 [][20] table, pool words at 0x080D0070 and 0x080D0100).

Refusals (with both symbols added):
- no selector: signed remainder excludes mixed aliases, addressed calls with data, and other profiles
- --addressed-signed-runtime-profile addressed-signed-runtime-r2-callback-data-v1 / -r3-callback-data-v1 / addressed-signed-runtime-data-v1, and
  compiler-signed-runtime-data-v1 with plain %: function address requires a canonical addressed function (compiler-signed-runtime-data-v1 with the
  explicit call: compiler runtime identifiers cannot occur in preprocessed C)
- --function-address-profile canonical-thunks-v1 / canonical-thunks-interposed-pool-v1: signed remainder requires its isolated binding profile
- --owner-runtime-profile canonical-integer-scalar-source-v1: with explicit calls, division runtime requires its canonical versioned proof;
  with plain %, canonical integer source requires call-only compiler integer identities

Cause: the function mixes signed __modsi3 (func_08142950), named data, and callbacks through two thunk registers. callback_alias() in
tools/addressed_signed_runtime_profile.py admits exactly one of _call_via_r2 / _call_via_r3, so the r3 call reaches function_address_target and is
refused. Kit issue: #134 (no selector combines arithmetic runtimes with compiler-emitted _call_via callbacks; its 0802BC7C also calls through both
r2 and r3). The explicit func_08142950 call is kept as matched siblings 080D29D4 / 080D2F78 write it (plain % gives identical code).

Helpers: find_free_item and find_node are the text of the matched src/080CEDC8.c. find_item (an array walk; the matched sources' find_item walks
the node list), count_nodes, remove_item and append_item have no shared text and no identified out-of-line twin (080D17C4 also writes node
removal inline), so under the helper rule they would still need that evidence, or to be written out, before this could ship.

Open: an earlier attempt found a register contest between the constant 3 and the g_state + 0x28C8 address, so the result may depend on local
declaration order.
