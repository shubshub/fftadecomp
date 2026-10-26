# 080BF5A4: recovered, not byte matching

Complete target: `0x080BF5A4..0x080BF7C2`, 542 bytes including literal pools and 257 reachable Thumb instructions.

The preserved complete natural C candidate passes native source plausibility and compiles to the complete 542-byte ELF symbol under fixed agbcc `-mthumb-interwork -O2`. Native matching exits 1: bytes differ. Aligned diff score is 254/257 instructions and 539/542 bytes. Actual same-offset equality is 539/542 bytes; the only differing byte addresses are 0x080BF600, 0x080BF6AA, 0x080BF712.

The three differing instructions are map row-address additions at `0x080BF600`, `0x080BF6AA`, and `0x080BF712`. Candidate: `adds r0, r0, r3`; target: `adds r0, r3, r0`. Both compute the same sum. Every other byte, including the 16-byte frame, signed-coordinate handling, branches, calls and fifth stack argument, field accesses, maximum-score comparison, and literal-pool layout, matches.

Recovered behavior checks the completion status and matching actor/target, updates the unit-derived value, accepts a valid current position, or scans the 16-by-16 map for the highest-scoring eligible position while respecting the restriction flag and updating both coordinate pairs and the position flag.

Bounded natural forms tried: wide versus byte helper return types; compound candidate conditions; state-based versus grid-based map helpers; nested status handling and an early return after the current-position path; 2D and flat map views; flat indexing and explicit row-pointer arithmetic; an integer map-address representation; coordinate-first helper arguments; and the equivalent `best < score` comparison. Byte helper returns and grid arguments recovered the target's materialized boolean checks and frame. The preserved ordinary pointer form has the best full-extent score. The remaining credible address forms did not reproduce the three addition encodings. No asm, volatile, pragmas, dead code, or compiler steering was used. These bounded attempts do not establish permanent impossibility at the fixed flags.

Source-bound native evidence remains in the private address scratch directory as `best-report.md` and `best-native-output.txt`, alongside the complete target capture. Unmatched active source/report were removed. No match credit is claimed.
