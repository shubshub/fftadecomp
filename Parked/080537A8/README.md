# 080537A8

Recovered the complete 372-byte / 168-instruction function. The preserved
candidate is natural C and passed the native plausibility gate, but the default
agbcc `-mthumb-interwork -O2` matcher exits 1: 357/372 bytes are identical and
the native instruction comparison reports 157/168 identities. No match credit.

The remaining differences are the second tile-region address calculations near
0x08053816..0x08053824 and 0x080538E4..0x080538F4. The target computes
`(count * 2 + tile) * 32`; this candidate computes the equivalent byte offset
`count * 64 + tile * 32`. The shift/add sequence and scratch registers differ.
The complete extent, 24-byte frame, control flow, calls, literal pools, tilemap
fill/copy operations, and other instructions match.

Natural forms tried included the factored tile-index sum in both operand orders,
shift and addition spellings of the doubled count, a halfword tile-offset
intermediate, explicit 32-byte tile records, and advancing the tile pointer
before rendering the number. The factored forms reused the doubled count across
the address and clear call, changing allocation and stack use; pointer advancement
and the narrower intermediate also changed allocation. The distributed byte
offset retained here was the closest tested form. This is a bounded source gap
under the fixed flags, not a proof that matching C is impossible.

The full target and final native mismatch report remain in the address-private
scratch directory. The unmatched source and generated report were removed from
the private root's `src/` and `docs/match/` directories.
