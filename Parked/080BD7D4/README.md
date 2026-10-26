# 080BD7D4 — bounded natural C attempt

Target: `0x080BD7D4..0x080BD8CA` (exclusive end), complete 246 bytes / 121 reachable instructions. No match credit.

The preserved complete source was freshly run through the default matcher at fixed `-mthumb-interwork -O2`. Native exit 1: complete compiled ELF symbol 248 bytes; source plausible; direct typed calls, fixed 28-byte local frame and return provenance accepted; no remaining relocations.

Recovered behavior: save the unit's unsigned coordinates at offsets F6/F7, search successive outward diamond perimeters, call 08099F58 with signed-byte candidate coordinates and FF, temporarily assign eligible candidate coordinates to the unit, call 080BD35C through the context's offset-80 field with the signed-byte mode, restore both original coordinates, and return the first candidate with zero callback result through the two output bytes. The original center check and the direction flips/completion checks are preserved.

The remaining gap is loop layout. The target enters the candidate-check block immediately after each perimeter's coordinate/direction initialization and keeps its movement/turn blocks after the callback and center check. This compiler rotates a turn block ahead of the candidate check and adds an unconditional entry branch, yielding 248 bytes instead of 246. Relative BL/branch encodings and temporary register choices in the rotated region consequently differ. The saved-local offsets and initial coordinate/direction register assignments match the target after the declaration/initialization refinement.

Forms ruled out: nested infinite for loops with a shared found exit (248 bytes, rotated both turn blocks); do-loop with coordinate initialization before directions (248, same rotation); movement guarded by the positive not-at-center condition (preserved structure, 248, rotates a turn block); and direct success return instead of the shared found label (preserved, identical bytes to the preceding form). No optimizer flags, fixed-register constructs or artificial operations were added.

The native diff uses the longer compiled span and therefore includes two ROM bytes beyond the indexed target end in its displayed reference. Its instruction/byte alignment score is not the target's complete instruction count or same-offset equality; the captured target's complete count is 121.

Raw C SHA256: `a98f36acc5a851125ea1ef34d4151447109fe842a1f77ad397fcec320030395a`.
Generated nonmatching report SHA256 before removing the active report: `439dc25da8f5c5c79a08a858bac58448825387603517671bd5385aff791dc4ce`.
The full captured target and final native output remain in `audio-following-v234-matching/080BD7D4/`. Active unmatched source/report have been removed.
