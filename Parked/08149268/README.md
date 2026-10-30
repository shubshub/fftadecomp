# 08149268: bounded natural C attempt

Target [0x08149268, 0x081492A8) is 64 bytes and 27 reachable Thumb
instructions, including its two literal words and alignment. Claim
6483407874 was accepted. The final native fixed agbcc -mthumb-interwork -O2
run returned 1 with: compiled symbol is shorter than the indexed span:
56 < 64. The native extent gate stopped before source plausibility, so no
plausibility or match credit is claimed.

Recovered operation: when the seven-bit category at state +0x980 is nonzero,
clear that category while retaining bit7, then zero bytes +0x984 and +0x985.
This is the conditional form of the already matched neighboring 081492A8
reset, using the same evidence-supported byte bitfield layout.

The complete best tested compiler function is 56 bytes and 23 instructions,
with no relocations. The compiler computes state +0x980 once and reuses both
that address and the byte loaded to test the category. The ROM recomputes the
address inside the nonzero branch with movs #0x98, lsls #4, adds, then ldrb.
Those four additional instructions account for the 8-byte residual. The
candidate also allocates the state base and category address differently as
a consequence. Both versions retain bit7 and conditionally clear the same
three fields; the original target byte sequence is not reproduced.

Bounded natural forms tested: direct guarded reset using u8 category/active
bitfields; raw-byte masked category condition with the same typed reset;
a u32 packed category/active/unknown-word view; and early null-category
return followed by the typed reset. The u8 forms produce 56 bytes; the u32
packed view produces 52 bytes. The preserved source is the clear early-return
u8 form. No helper aliases, assembly, volatile, optimization changes, register
bindings, artificial padding or dead code were introduced.

Original unmodified compiler ET_REL, assembly, refusal log, source and this
README are retained in the sibling 08149268 delivery directory outside the
disposable matching-root. The failed active source/report were removed.
This is a Parked attempt with zero C matching credit.
