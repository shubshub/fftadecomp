# 080D5DD4

Complete natural-C reconstruction of resource-header decoding, object creation,
and palette assignment. Target: `0x080D5DD4..0x080D5E80`, 172 bytes and 84
reachable instructions. The retained source was freshly compiled with agbcc
`-mthumb-interwork -O2` through the unchanged native matcher and approved ROM.

Native exit 1: `compiled symbol is shorter than the indexed span: 170 < 172`.
The native extent guard stops before linked comparison and plausibility
acceptance, so this is not a match or a completed native validation.

Fresh compiler assembly isolates the remaining difference to the first
resource-header bit test. The target uses `movs r1, #4; adds r0, r2, #0;
ands r0, r1`; the candidate uses `movs r0, #4; ands r0, r2`. This removes one
halfword instruction and shifts subsequent branches and calls by two bytes.
The surrounding register assignments, 24-byte frame, parameter narrowing,
second bit test, object creation, palette call and return have the recovered
target structure. The missing copy cannot be supplied with artificial code.

Bounded natural forms tested: a halfword decoded-header local (164 bytes),
word decoded-header locals with signed or unsigned type (170 bytes), a word
render-flags accumulator (158 bytes), and named byte masks (162 bytes).
The retained source uses signed word header decoding and a halfword render
flags accumulator. No compiler flags, inline assembly, volatile RAM, forced
inlining, dead code or unrelated files were changed.
