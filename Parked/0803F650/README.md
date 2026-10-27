# 0803F650 — Parked

Target: complete [0x0803F650, 0x0803F6F8), 168 bytes / 73 reachable instructions.

The preserved complete natural reconstruction initializes the panel and two embedded 20-byte text segments, formats text into data_0201F4A0, scans the first 100 positions for the two-byte @c marker, and points the second segment after the marker when present. Without a marker, both segments retain the buffer start.

The unchanged native matcher returned exit 1 for the preserved candidate: complete ELF symbol 168 bytes, source plausible, 71/73 instructions and 166/168 same-offset bytes identical. Every frame instruction, call, branch target, initialization store, literal word, and final segment store agrees.

Only the lookahead-character address calculation differs. At 0x0803F6D0/0x0803F6D2 the target forms buffer + 1 first, then adds the loop index (adds r0, r1, #1; adds r0, r2, r0). The candidate instead forms index + 1 first, then adds buffer (adds r0, r2, #1; adds r0, r0, r1). Both compute the address of data_0201F4A0[i + 1]; two operand bytes remain different.

Bounded natural forms tested under fixed agbcc -mthumb-interwork -O2: direct global-array indexing (preserved 168-byte plausible candidate); scanning through the retained text pointer (158-byte extent refusal); a local cursor at buffer + i (164-byte extent refusal); and a genuine inline marker predicate (156-byte extent refusal). Short-symbol attempts were refused before plausibility/full comparison and receive no match credit. No source steering, artificial address arithmetic, compiler flags, or gate changes were used.

The report for the preserved direct-index candidate remains in the private address scratch directory. Unmatched active source/report were removed. This directory contains only the recovered C and this diagnosis.
