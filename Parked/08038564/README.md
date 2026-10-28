# 08038564 — not matching

Target: 0x08038564..0x080385A6, 66 bytes and 27 reachable instructions.
Compiler: fixed agbcc -mthumb-interwork -O2.

The retained natural C searches 64 four-byte records beginning at state
0x02000000 offset 0x2B08. On the first byte identifier matching the incoming
u16, it clears that byte and the halfword at record offset 2, then returns 1.
It returns 0 when no record matches.

Fresh default native matching exits 1 before byte comparison or source
plausibility: "compiled symbol is shorter than the indexed span: 56 < 66".
No native byte-identical or plausibility result is claimed.

Fixed-flag assembly diagnostics show the compiler combines the two record
field addresses. It advances one identifier pointer and clears the halfword
through that pointer plus 2. The target advances both an identifier pointer
and a separate record base, retains the additional 0x2B0A offset literal,
and calculates the halfword address from the separate base. The resulting
register allocation and saved-register set also differ.

Three natural forms were tried: direct typed record accesses, an ordinary
naturally inlined entry-clearing helper, and byte/halfword views of the same
four-byte serialized records. Each compiled to 56 bytes. The simple typed
record source was restored and freshly tested again with the same refusal.
Compiler options were unchanged, and no artificial loads or address
calculations were introduced.

The native refusal remains in private address scratch. No unmatched active
source or report remains.
