# 08089D84 — Parked

Target: 0x08089D84..0x08089E1C, 152 bytes / 76 reachable instructions.

The complete C candidate copies a signed rectangle from one tile buffer to another. Coordinates and rectangle dimensions are signed bytes passed in small value structs; each buffer has its tile pointer at offset 0x18 and row width at offset 0x28. The inline row-copy loop skips nonpositive widths and copies halfwords forward.

The final default native matcher invocation exited 1: `compiled symbol is shorter than the indexed span: 136 < 152`. The native extent guard stopped before byte comparison and source plausibility assessment. No exact-match credit is claimed.

Compiler output has the same forward halfword-copy countdown loop, but differs in invariant placement and register allocation. It keeps the source row base and source Y coordinate in high registers, computes the signed copy width inside the outer loop, and caches the height. The target spills the source row base and Y coordinate, retains separately narrowed width values across rows, and extracts height again before each outer-loop backedge. The unresolved gap is 16 bytes under fixed agbcc `-mthumb-interwork -O2`.

Bounded alternatives tested a positive-count while loop, signed rectangle bitfields, narrowing the width inside an integer-argument helper, and a signed width accessor. None recovered the complete target. The retained indexed-loop candidate preserves the target's countdown copy behavior without compiler steering.

Raw native output and captured disassembly remain outside the matching root in the private address scratch directory. No unmatched active source or match report is retained.
