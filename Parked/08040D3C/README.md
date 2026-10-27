# 08040D3C

Target: 102 bytes / 51 reachable Thumb instructions, ending at 0x08040DA2.
Fixed agbcc `-mthumb-interwork -O2`.

The preserved complete candidate passes extent, closed-leaf CFG and plausibility,
then returns native exit 1: 97/102 bytes and 48/51 instructions identical.
It fills pairs of tile rows, advancing a 16-bit tile index after each store.

Remaining differences are the outer-loop condition and destination lifetime:
the target uses BEQ at 0x08040D5A and BNE at 0x08040D96; the candidate uses
BLE and BGT for its positive signed countdown. The candidate initializes
the row destination before decrementing the outer counter, while the target
initializes it after the inner width check. The tile stores and increments
otherwise match, as do the complete 102-byte extent and saved registers.

Tested natural unsigned post-decrement loops (124-byte complete body), explicit
unsigned zero countdowns (98-byte short symbol), signed ascending loops
(110-byte complete body), the preserved positive signed outer countdown
(102 bytes), and decrement-before-row setup with a zero test and ascending
inner loop (100-byte short symbol). The short forms stop at the extent gate;
they have no CFG/plausibility/byte-comparison verdict. The matching candidate's
native report is retained in address scratch as last-native-report.md.
No compiler flags or artificial accesses were used. No exact match is claimed;
unmatched active source and report were removed.
