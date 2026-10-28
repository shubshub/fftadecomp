# 0802BD44 — Parked

Complete natural eight-word transparent-nibble merge. Fixed agbcc `-mthumb-interwork -O2`; final native matcher exit 1, complete ELF extent 74 bytes against the 74-byte target. Closed leaf CFG and source plausibility passed. Exact comparison: 70/74 bytes and 33/37 instructions identical.

Only the saved source pointer and row count use opposite high registers:

- 0802BD5A: target `mov ip, r3`; candidate `mov r8, r3`.
- 0802BD5E: target `mov r8, r0`; candidate `mov ip, r0`.
- 0802BD7A: target `mov r3, ip`; candidate `mov r3, r8`.
- 0802BD7E: target `mov r0, r8`; candidate `mov r0, ip`.

Tested natural countdown and ascending inner loops, nibble shift in the body versus the loop update, parameter versus local cursors, access postincrements versus outer-loop pointer increments, and outer-loop update order. Access postincrements produced 78-byte candidates; separate local cursors with pointer increments in the outer loop produced the preserved 74-byte form. No compiler flags or assembly steering used.

The restored best candidate was freshly checked. Native output and report remain in the private address scratch as `last-native-result.txt` and `last-native-report.md`. Unmatched active source and report were removed.
