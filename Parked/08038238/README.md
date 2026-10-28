# 08038238

Complete recovered cursor drawing/update routine for 0x08038238..0x08038324. It reads the selected 76-byte window geometry, computes/clamps the cursor X coordinate, draws upper/lower cursors according to flag bits 2/3 with the frame-dependent vertical offset, and increments the 16-bit frame counter.

Fresh canonical matching with fixed agbcc `-mthumb-interwork -O2` exited 1 at the extent gate: `compiled symbol is shorter than the indexed span: 232 < 236`. Target: 236 bytes / 110 reachable instructions. Preserved source: 232-byte complete ELF symbol; the fixed compiler assembly contains 109 instructions. No native byte-diff or plausibility verdict was reached, so neither an exact nor a gate-accepted plausibility claim is made.

The direct candidate has the same drawing arithmetic, field offsets, calls and call arguments visible in the capture. It retains geometry in R4 and state in R5. The target retains state in R4, geometry in R5, and makes an additional persistent copy of the state base in R7 at 0803823E for its final counter update. Its table lookup also loads the table base before multiplying the index into R0; the direct candidate multiplies into R1 before loading the base. The missing state-base copy accounts for one instruction; literal-pool alignment contributes the remaining extent difference. This is a bounded code-generation residual, not a proof of permanent impossibility or verified semantic equivalence.

Natural forms tried:

- Direct typed state pointer and indexed geometry entry: preserved 232-byte candidate.
- A separate word-pointer view for the frame counter and a table-base pointer followed by indexing: still 232 bytes; the compiler shared the state base and used the geometry pointer for the initial base load.
- A naturally inline rendering helper, with frame advancement in the outer function and separately named table base/entry: still 232 bytes and refused by the extent gate; removed.

The simplest complete source was restored and freshly checked. Fixed compiler assembly and the native extent refusal remain in private address scratch. No flags, forced inlining, assembly, volatile access or inert code were used. Unmatched active source/report were removed.
