# 0813DF5C — recovered, not byte matching

Target: `[0x0813DF5C, 0x0813E030)`, 212 bytes / 106 reachable instructions.

The preserved natural candidate initializes the animation resource and relative-offset table, derives the track count from the first offset, clears each track's index/time/flags, reads its frame count and frame data, scans durations from the supplied elapsed time, clamps exhausted tracks to their final frame, and stores the mode.

The preserved candidate was checked by the native matcher with fixed agbcc `-mthumb-interwork -O2`: exit 1, plausible C, complete symbol 226 bytes instead of 212; 47/113 instructions identical (131/226 bytes). The compiler uses a 12-byte stack frame instead of the target's 20 bytes, assigns the loop invariants differently, and rotates the duration scan so its negative-time branch is at the bottom. The target keeps that scan at the top with the remaining-time store on the early exit.

Bounded natural alternatives tried:

- Explicit pointers for the frame index, remaining time, and current track: 196 bytes, rejected as shorter than the full indexed body.
- Explicit index/time pointers with direct indexed track fields: 216 bytes, 30/108 instructions identical (103/216 bytes), still different allocation and scan layout.
- A do/while duration scan followed by negative-time versus exhausted-track handling: 244 bytes, 49/122 instructions identical (136/244 bytes), with an extra post-loop sign check and different allocation.

No variant matched. These are fixed-flag attempt results, not a claim that a natural exact match is impossible. The nonmatching `src/0813DF5C.c` and generated native report were removed. No assembly, volatile access, compiler pragmas, dead code, or compiler-steering constructs were used.
