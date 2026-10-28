# 08016800

Target: complete 298-byte Thumb body, 149 reachable instructions,
0x08016800 .. 0x0801692A. Fixed compiler: agbcc
`-mthumb-interwork -O2`.

The preserved complete implementation draws the four corners, horizontal
and vertical edges, and the interior of a tiled rectangle. The eight border
tiles and fill tile include the palette shifted by 12 bits. Width and height
must both exceed one; row stride is a byte and tile indices are halfwords.

Its native run exited 1 with a 302-byte complete ELF symbol. The framed
leaf CFG and source-plausibility gates passed. The native diff reported
178/302 bytes and 59/151 instructions identical; this denominator is the
compiled extent and includes four ROM bytes beyond the 298-byte target.
It is not a complete target match.

The remaining differences are substantial: the candidate allocates a
16-byte local frame rather than the target's 24-byte frame, retains the
right-column index in a high register rather than the target's stack slot,
combines halfword indices before address arithmetic at some corners and
edges, and uses different loop-counter lifetimes in the interior fill.

Two further natural forms used a bottom-row pointer and explicit row
pointers, positive countdown loops, and then a separate semantic border
helper. Both compiled to 292 bytes and were rejected at the extent gate,
before CFG, plausibility or byte comparison. They were discarded. No
compiler flags or forced inlining were used.

The preserved candidate's generated report is in address scratch as
`last-native-report.md`. Unmatched active source and report were removed.
