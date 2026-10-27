# 0812E1A8 — Parked

Target: complete indexed 0x0812E1A8..0x0812E366, 446 bytes / 216 reachable instructions.

Preserved complete natural C compiles to 452 bytes with fixed agbcc `-mthumb-interwork -O2`. The final native matcher exits 1, reaches native CFG/ABI and source plausibility checks, and reports NOT MATCHING: 180/217 instructions identical (408/452 bytes). Its comparison spans the compiled extent, including six bytes after the indexed target; these counts are not exact target-only credit.

The coordinate/height calculations, signed midpoint averages and byte narrowing reproduce the target operations. Remaining differences are shared comparison-block placement: the special flag path duplicates the byte-range comparison instead of joining the extended-range path; the negative-midpoint height bounds are shared at the final default path instead of earlier in the midpoint chain. Associated conditional directions and branch displacements differ. No exact full-symbol match was obtained.

Bounded tested forms included midpoint shift with byte locals (446-byte complete extent, 399/446 bytes), signed midpoint averages (this preserved 452-byte form), a common final failure return (444-byte short extent, later gates not reached), direct final boolean return (472 bytes), and explicit height-range rejection guards (458 bytes). The first natural form was 444 bytes and stopped at the short-extent gate. No compiler flags, assembly, artificial volatile, padding or forced-inline changes were used.

Final generated native report is preserved in address scratch as `last-native-report.md`. Unmatched active source/report were removed.
