# 08127380 — Parked

Target: complete ROM function [0x08127380, 0x08127458), 216 bytes / 104 reachable instructions.

The reconstructed function forms current and target three-coordinate records, computes the maximum absolute X/Z separation, and updates a four-state mode according to two adjacent distance bands. ROM word-mask updates support signed 16-bit coordinate fields in word-aligned bitfield records. The state uses an object pointer at +4, mode at +0xF, and grid coordinates at +0x12/+0x14/+0x16. Grid coordinates become cell centers via coordinate * 32 + 16.

Latest fixed native matcher result: exit 1, compiled complete ELF symbol 220 bytes, closed leaf CFG, no relocations, source plausible, NOT MATCHING because bytes differ. The declared target span remains 216 bytes; no match credit is claimed. The native comparison reported 87/105 instructions and 204/220 bytes identical; its 220-byte comparison includes four ROM bytes beyond the indexed target, so those totals are diagnostic only.

The packed-coordinate construction and planar-distance calculation agree instruction-for-instruction apart from PC-relative literal offsets displaced by the later extra code. The candidate retains a redundant distance >= 16 test after the outer distance >= 8 / distance < 16 checks. ROM proceeds directly to a materialized distance <= 23 Boolean. The candidate also uses a different branch arrangement for the final mode-2/mode-3 return. These differences leave the compiled body four bytes longer and move the two mask literals.

Bounded natural reconstructions tried:

- Local coordinate values and direct absolute/max arithmetic: 196-byte symbol, rejected as shorter than the indexed span before plausibility.
- A semantic planar-distance helper without an inline declaration: local call emitted, rejected by linked CFG verification.
- Ordinary static inline planar-distance helper: naturally inlines and recovers both stack records and their exact arithmetic, but direct combined range expressions reduce to an unsigned contiguous-range test, producing 204 bytes and failing the short-symbol gate.
- Semantic distance-band predicate: separate band calls produce 228 bytes; a direct near-band guard with an inline outer-band predicate produces the retained 220-byte result. Both conjunction and early-return spellings retain the extra lower-bound comparison.

The semantic helpers use ordinary static inline declarations under unchanged agbcc -mthumb-interwork -O2. No forced-inline attributes, assembly, volatile, compiler changes, dead artificial expressions, or scheduling-only code were introduced. Full native invocation output remains in the sibling address scratch native-output.txt.

The unmatched active source/report were removed. This directory contains only the complete C reconstruction and this precise diagnosis.
