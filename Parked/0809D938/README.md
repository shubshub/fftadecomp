# 0809D938 — unmatched

Target: complete `[0x0809D938, 0x0809D96A)`, 50 bytes / 23 reachable instructions.

The retained complete natural C candidate walks thirteen 0xB4-byte inline entries beginning at offset 0x0C. It frees each nonnull entry object, clears that pointer, then frees the container.

Fresh final native result: exit 1 before comparison, `compiled symbol is shorter than the indexed span: 46 < 50`. No native byte-match count or plausibility verdict was produced; this is not a match.

Remaining gap: target separately copies the index into r1, multiplies it by 0xB4, and materializes container + 0x0C in r0 before adding the product. Candidate multiplies directly into r0, adds 0x0C to that product, and adds the container base. The target thus has two additional address-calculation instructions. The observed per-entry null check, free/clear sequence, thirteen-iteration bound, and final container free otherwise agree in the compiler listing.

Bounded tested forms:

- Inline typed entry array and per-iteration indexed entry pointer: 46 bytes, retained and freshly reconfirmed.
- A separately named entries-base pointer initialized before the loop: 48 bytes, with a pointer/end-address loop, extra saved register, and an added literal.
- Byte-backed inline storage cast to the entry type at the indexed access: 46 bytes with the same shortened address calculation.

No assembly, padding, volatile access, register variables, or compiler flag changes were used. The unmatched active source and any address report were removed.
