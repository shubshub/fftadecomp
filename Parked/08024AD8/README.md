# 08024AD8 — bounded natural-C mismatch

Target: 0x08024AD8..0x08025174, 1692 bytes and 786 reachable instructions.
The complete reconstruction preserves both input-orientation modes, all eight directional paths, bounded diagonal tile fallbacks, movement notification, previous-position copy, and coordinate updates.

The retained candidate was tested with the unchanged native match.py command, approved ROM, and fixed agbcc -mthumb-interwork -O2. Native exit was 1: NOT MATCHING — bytes differ. Native complete-ELF verification, direct-Thumb-call CFG verification, and source plausibility passed. The emitted target symbol is 1936 bytes, 244 bytes longer than the indexed target. Native comparison reported 264/855 identical instructions and 1007/1936 identical bytes; these comparison denominators include ROM bytes beyond the indexed target and are not match credit for the complete 1692-byte symbol.

Concrete remaining difference: the natural inline tile predicate's short-circuit Boolean return introduces separate live result values and stack spill slots for repeated calls. Candidate stack allocation is 64 bytes versus the target's 4 bytes; candidate position/state register allocation and branch layout consequently differ. The target materializes each predicate's 0/1 result after the two tile calls.

Bounded attempts: an ordinary static predicate emitted an extra helper and was refused by the single-function extent gate. Making the semantic predicate inline produced the retained plausible complete candidate above. An explicit early-return predicate produced a 1032-byte symbol; native refused it as shorter than the indexed 1692-byte span, before plausibility. No flags, forced-inline attributes, assembly, volatile, or artificial dead expressions were introduced.

The retained source is the tested 1936-byte candidate. Its raw C SHA-256 is 70adbfc577505aa6fbd8501b11eed18ee97f771b63e8eb9ae4633f8980f2a490; the native report's source dependency fingerprint was 6f45dda566d450ab85f11ae920dff9b40d8cdcfbfdf02b913f5ecbc9db18f842. Unmatched active source and generated report have been removed. No exact-match credit is claimed.
