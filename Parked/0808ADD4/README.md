# 0808ADD4 — unresolved native match

Complete target: 0x0808ADD4..0x0808B0EE, 794 bytes / 383 instructions.

The preserved natural C passes the native plausibility check and emits the full
794-byte symbol. Fresh fixed-flag native matcher exit status: 1 (NOT MATCHING).
Result: 793/794 bytes and 382/383 instructions identical.

Only remaining difference is at 0x0808AEA6: target loads requested width with
`ldr r0, [sp, #4]` (0198); compiled C loads its identical local copy `count`
with `ldr r0, [sp, #0xc]` (0398). The local count was assigned from requested
width at the beginning of the centered last-row branch. All other instructions,
three literal pools, both plane copies, clipping, and row loops match exactly.

Bounded natural forms tested: direct four-bit flags, separate disabled/mode
bitfields, requested-width versus clipped-count centering, assigning the count
after geometry setup, and separate last-row/body counts. The separate bitfield
form resolves the full extent; the other count forms retain the one-byte gap,
move the assignment and register allocations, or shorten the symbol. The best
complete plausible form is preserved here without assembly or steering.

Full target, fresh native output, and last generated report remain in the
address-specific private scratch directory. Unmatched private src/report removed.
