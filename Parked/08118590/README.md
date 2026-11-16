# 0x08118590 - three-object effect event: bytes identical, refused (inert spin together with named data) (410 bytes)

Attempt 2026-11-13, kit fcdf2d45. Compiled with agbcc -mthumb-interwork -O2 and linked by hand at 0x08118590 with every
callee and data symbol bound to its ROM address, the source gives all 410 bytes of [0x08118590, 0x0811872A). Index row
correct; data_08501200 is already in config/data_symbols.json.

An event callback on event->phase: phase 0 reads a position from the event text; 0x100 spawns three objects from
data_08501200 and starts three motions; 0x101 steps the motions, moves the objects and ends the event when the first
motion finishes. Phase 1 spins forever (`b .` at 0x081185E0) if any of the three objects is still set; every other
path returns 0.

Refusals:
- default: `reachable control-flow region has no path to a verified return`
- `--control-flow-profile mixed-return-inert-spin-v1`: `inert spins exclude non-call relocations` (the data_08501200
  pool word)

Cause: the inert-spin profile excludes every non-call relocation (tools/inert_spin_profile.py:160). In a copy of the
kit with only that exclusion removed, match.py reports MATCH - byte identical. Same gap: 0x080E29C4.
