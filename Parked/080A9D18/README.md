# 080A9D18: retained unmatched form

One natural C form and one original default native match invocation were attempted under accepted claim6536618514 (sol-9D18).

The native matcher exited1 with `compiled symbol is shorter than the indexed span: 280 < 340`. No match report, native byte-comparison count, or source-plausibility verdict was produced. This is not a match and earns no match credit.

The unchanged-source compiler-only diagnostic confirms a complete280-byte ELF symbol against the complete340-byte target. Both have five direct BL sites. The candidate allocates40 local bytes; the target allocates44. The candidate holds the next outer index in r10 and uses a typed record pointer for compact indexed halfword accesses. The target spills the outer index and materializes the larger entry-relative member addresses before those loads. Register allocation and address calculations differ. No second source form was attempted. No unsupported-selector or impossibility claim is made.

Diagnostic equal-position comparison records57 equal bytes,223 differing shared positions and60 target bytes beyond the candidate symbol. These are compiler-only diagnostic facts, not native comparison or plausibility verdicts.

Frozen source SHA-256:6e8832f0b898e9577b528c7f2529573c43433d421e431be3109fc0b8afaa3c54.
Frozen source-plus-nine-headers composite SHA-256:6fa19b199dbcb9c36f1274c80a185b5eb28ae302f3a768dbf9bf4297c7fdebe5.
Complete target body SHA-256:907ab6dfbd287d2b32ca6a322be56b0ba63f74503eaeda9b2a95b14cee672b63.
Complete diagnostic body SHA-256:6878fced2c51d5e4ddec84e89865722963239336c3a0510e600e482cc23f3b9c.

The original stdout, stderr, exit/elapsed receipt, actual115 toolkit sources, nine headers, six maps, nine selected binaries, current runtime, compiler assembly, linked ELF, complete body and exact diff are retained under `state/matching-080A9D18-author/` in the handover workspace. The original native command used explicit isolated `--root` with no selector flags. There were no ROM/helper rereads, shared input changes, native retries or successful replays.
