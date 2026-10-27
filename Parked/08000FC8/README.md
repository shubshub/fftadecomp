# 08000FC8 — Parked

Target: complete 0x08000FC8..0x0800105C, 148 bytes and 68 reachable instructions.

The recovered C searches the current bank's 32 occupied eight-byte records for
four equal halfwords. If none matches, it marks the first free slot occupied,
copies the four halfwords, and returns its index. With no available slot it
returns zero.

The fixed native matcher with agbcc `-mthumb-interwork -O2` exited 1 at the
complete-symbol extent gate: `compiled symbol is shorter than the indexed
span: 124 < 148`. Byte comparison and source plausibility were not reached;
there is no exact-match or plausibility claim.

In the plain-field candidate, the compiler combines the four halfword equality
checks into two word comparisons. The target retains four halfword comparisons.
The target also loads each destination halfword immediately before replacing
it; those four unused destination loads are absent from the compiled copy.
Together these account for the 24-byte size deficit. Loop setup register/order
differences are also visible in the compiler assembly.

Three bounded natural representations were tested: ordinary u16 fields and
full-width 16-bit bitfields with u32 and u16 storage declarations. Every native
run produced a 124-byte symbol and stopped at the extent gate. The retained
candidate uses ordinary u16 fields. No artificial destination reads, volatile,
assembly, compiler flags, or dead conditions were introduced.

Raw native output remains in the private address scratch, outside the
repository artifacts. Only this C file and README are retained in Parked.
