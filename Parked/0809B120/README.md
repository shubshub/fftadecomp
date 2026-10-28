# 0809B120 — unmatched

Target: complete `[0x0809B120, 0x0809B216)`, 246 bytes and 118 reachable instructions, including the literal pool and alignment.

The retained complete natural C candidate computes packed current/destination coordinates, takes the maximum absolute X/Z difference, selects the middle distance bands, and conditionally updates facing. With unchanged agbcc `-mthumb-interwork -O2`, the final native matcher invocation exits 1 before comparison: `compiled symbol is shorter than the indexed span: 234 < 246`. No byte-match count or native plausibility verdict was produced, and this is not a match.

Remaining gap: the target keeps both packed positions in a 16-byte stack area and reads signed halfwords directly. This candidate uses an 8-byte stack area and keeps the current position's two words in registers, producing shift-based signed extraction. The target also reloads the route index for each destination coordinate, while the candidate reuses one computed route-point address. Distance-band boolean materialization, facing-selection branches, and register allocation consequently differ.

Bounded tested forms:

- Separate signed 16-bit-field position structs with one combined interval condition: 220 bytes.
- Union positions with signed-halfword component views and explicit distance-band classification: 234 bytes, retained and freshly reconfirmed.
- A two-element packed position array with separately named old-facing values: 200 bytes; direct halfword stores replace the target's masked word updates.

The unmatched active source and any address report were removed. No padding, assembly, volatile accesses, or compiler flag changes were used.
