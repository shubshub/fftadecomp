# 0805E5C0 - Parked

Complete target: [0x0805E5C0, 0x0805E798), 472 bytes and 175 reachable instructions.

The retained complete C reconstructs the grouped mode dispatch, conditional setup and cleanup, selected-entry release, and ordered state writes. The default native matcher with fixed agbcc `-mthumb-interwork -O2` compiles a complete 472-byte symbol, accepts the direct Thumb call profile and source plausibility, and exits 1 with `NOT MATCHING - bytes differ`: 159/175 instructions and 456/472 bytes are identical. This is not a complete match and receives no match credit.

The remaining sixteen differing instruction encodings are confined to the two selected-entry address calculations at target 0x0805E6C6..0x0805E6D8 and 0x0805E710..0x0805E71E. The compiled form keeps the state/array base in r0 and the scaled index in r1; the target uses the reverse roles for these calculations. Other reachable instructions and literal words match. This is an ordinary code-generation gap, not an unsupported linker/profile boundary.

Bounded natural attempts covered a separate full-width entry-index local, direct repeated array expressions, a full-width helper-result local, and a cached state pointer. The first three retained the same 472-byte differing output. The cached-state form worsened allocation and layout to a 476-byte symbol; it was discarded. The original complete candidate was restored and freshly native-tested with the result above. No alternative compiler flags or source steering were used.

The full captured target and differing native report remain outside this matching root in `/home/user/.codex-work/ffta-ulw/audio-following-v97-matching/0805E5C0/target-disassembly.md` and `native-not-matching.md`. Unmatched source and report were removed from `src/` and `docs/match/`.
