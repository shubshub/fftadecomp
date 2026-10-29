080032F8: affine display-shadow update

The complete target spans [0x080032F8, 0x0800337C): 132 bytes and 60 reachable instructions. It copies four signed halfword matrix coefficients and the low/high halves of two signed coordinates into the BG2 or BG3 register shadow at 0x03000940. Other layer values leave the shadow unchanged.

The preserved complete natural C compiles with fixed agbcc -mthumb-interwork -O2 to a 100-byte original ELF function containing 44 instructions. The final native match exits 1 at the complete-symbol extent gate: “compiled symbol is shorter than the indexed span: 100 < 132”. No MATCH report or fresh report replay is claimed. Independent native plausibility returns no findings.

The target performs sixteen old-destination LDRH reads, each immediately followed by a full STRH assignment. The candidate correctly emits the corresponding full halfword writes, coefficient loads, signed coordinate shifts, switch and return, but omits those sixteen unused RAM reads; register allocation, branch displacement and pool locations consequently differ. The 32-byte size gap equals those sixteen halfword instructions.

Ordinary halfword fields and nonpacked full-width u16/u32 bitfields all produce the 100-byte implementation without the reads. Packed u32 bitfields instead produce byte stores and a 224-byte function. The destination is ordinary IWRAM shadow storage, not MMIO. No RAM volatile qualifier, discarded artificial load, assembly, changed compiler option, or padding was introduced to force the reads.

The unmodified original compiler ET_REL and generated assembly are preserved outside the disposable matching-root in ../080032F8/original.o and compiled.s under the batch directory. This candidate is Parked, contributes zero matched bytes/functions, and has no active unmatched source or report.
