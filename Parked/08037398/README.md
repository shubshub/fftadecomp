# 08037398 — Parked

Target: complete [0x08037398, 0x08037428), 144 bytes / 56 reachable instructions.

The complete natural reconstruction draws a sprite through func_0804C598 using the surface at data_03000E30 + 4, entry slot + 3, narrowed coordinates, zero mode/delay, and the graphics/layout tables at 0x08950000/0x08950F4C. Nonzero variants select the byte-sized variant + 25 with attribute 0x52; variant zero selects 1 with attribute 0x38.

The preserved tested form compiles to 140 bytes under fixed agbcc -mthumb-interwork -O2. Native match.py returns exit 1 at the short-symbol extent gate (140 < 144), before plausibility and full comparison. No plausibility or match credit is claimed.

The remaining instruction difference is the nonzero-variant byte addition before the first call. The target emits five instructions at 0x080373AC..0x080373B4: shift variant left 24, materialize 0x19000000 through two instructions, add, then shift right 24. The candidate emits four instructions: copy variant, add 25, shift left 24, shift right 24. This is two bytes shorter in executable instructions and also changes literal-pool alignment, making the complete symbol four bytes short. Compiler assembly otherwise agrees with the recovered call arguments, branch structure, 24-byte stack argument area, and return sequence.

Bounded forms tested: direct (u8)(variant + 25) call argument; byte-local variant += 25 (preserved); unsigned-constant byte update; and a genuine naturally inlined shared drawing helper. Every form compiled to 140 bytes. The byte-local form places the calculation before the surface load as in the target, but cannot reproduce its arithmetic expansion. No unusual constant identities, shifts added solely to force code, compiler flags, or gate changes were introduced.

Native output remains in the private address scratch directory. Unmatched active source/report and obsolete compiler scratch were removed. Only this C/README pair is retained for integration as Parked.
