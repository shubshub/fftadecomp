# 080031E8

Complete natural C implementation retained, but its complete ELF symbol is 72 bytes / 36 instructions versus the indexed 82-byte / 41-instruction target. Fixed agbcc `-mthumb-interwork -O2`; final native matcher exit 1: `compiled symbol is shorter than the indexed span: 72 < 82`. The extent gate refused before native CFG, plausibility, or byte-comparison evidence; no plausibility or match percentage is claimed.

The candidate holds the low-nibble mask 15 in saved R5, extracts each nibble directly, and shifts the already narrowed value right by four. The target saves only R4, shifts the value left by 16 each iteration, constructs mask 0xF0000, extracts the nibble with a signed right shift by 16, and explicitly narrows the updated value before its nonzero test. The final decrement-before-test space-padding loop has been reconstructed; the remaining gap is nibble/value lifetime and normalization, together with register allocation and saved-register use.

Bounded forms tested: direct low-nibble masking with a signed word digit; signed halfword digit local; a genuine naturally inlined hexadecimal-digit helper with a narrowed argument; a helper accepting the full value and extracting its nibble; and direct remainder-by-16 extraction. Initial direct forms compiled to 72 bytes; helper forms to 70 bytes; retained direct remainder form to 72 bytes. Both initial post-decrement padding and the target's decrement-before-test countdown were considered. No flags, assembly, artificial volatile, forced inline, or dead code were used.

The retained file is the last tested direct remainder implementation. Unmatched active source/report and temporary preprocessing/assembly diagnostics were removed. No exact match is claimed.
