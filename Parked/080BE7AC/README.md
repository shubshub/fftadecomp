# 0x080BE7AC - scored position list: bytes identical, refused (buffer chain without loop replay, local passed to a copy callback) (308 bytes)

Attempt 2026-11-14, kit fcdf2d45. Compiled with agbcc -mthumb-interwork -O2 and linked by hand at 0x080BE7AC with
every callee bound to its ROM address and _call_via_r3 at 0x08142250, the source gives all 308 bytes of
[0x080BE7AC, 0x080BE8E0). Index row correct; no new data symbols (data_0836D4BC is already mapped).

The function asks func_080B4A1C for the positions reachable from (x, y), scores each with func_080BE5F4, keeps those
with a positive score in results[], and sorts them by score, highest first, swapping the 8-byte records through the
copy callback data_0836D4BC[0] and a local temporary.

Refusals:
- default: `buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification`
- `--owner-runtime-profile bounded-buffer-conditional-thunks-v1`: `buffer callee 0x0812F0D8: buffer callee
  0x0812E55C: buffer callee 0x0812E4F4: inconsistent possible pointer offsets at control-flow join` - bounded loop
  replay (kit #153) is not enabled for the conditional-thunk proofs
- `--function-address-profile canonical-thunks-interposed-pool-v1`: `canonical-thunks-interposed-pool-v1 linking
  requires its complete local switch`

With loop replay enabled for the conditional-thunk proofs, the next refusal is `conditional indirect call excludes
local argument aliases and pointer words`: the address of the local `swap` is passed to the _call_via_r3 copier. Kit
issue: #190 (a local buffer passed to a callback thunk).

Choices the bytes do not fully pin: `if (found <= 1) return found;` and `last = found - 1` as the outer loop bound,
both chosen for the register allocation.
