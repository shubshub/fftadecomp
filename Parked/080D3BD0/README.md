# 080D3BD0 — Parked

Captured target: 228 bytes / 105 reachable instructions, 080D3BD0..080D3CB4.

One complete natural C attempt was tested under the unchanged native gate. Native exit 1: plausible C, complete 248-byte ELF symbol, direct Thumb BL with ordinary ARM ABI call summaries, no relocations. The candidate is 20 bytes longer than the target. The tool's aligned comparison reports 196/248 bytes and 76/111 instructions identical; those comparison denominators reflect the longer compiled extent and must not be reported as the captured target's counts.

The candidate reads packed sequence entries, skips 0xFFFF duration records while updating current values and optionally wrapping the index, initializes two transition states, and publishes control bytes. Explicit packed types preserve the target's bytewise little-endian halfword loads and four-byte record stride.

Specific gaps:

- The loop is rotated/duplicated by the compiler: its initial sentinel comparison and bottom record reload differ from the target's single top-tested loop. The 0xFFFF constant, zero value, and loop register allocation also differ, shifting later calls and branch displacements.
- Target 080D3C92 loads r3 from the control byte at global offset 0x4C immediately before overwriting that byte. The loaded value is unused. The natural direct byte assignment emits only the store.
- Target 080D3CA6 loads r2 from the destination control byte immediately before its common store. The destination is global offset 0x4D in mode 1 or 0x4E otherwise. The loaded value is unused. The natural direct assignments emit no corresponding loads and do not share the same store tail.

This known unused-load-before-store family was limited to one complete natural attempt. No dead reads, volatile qualifiers, assembly, padding, compiler changes, or artificial bitfield declarations were added to reproduce the unused loads. The unmatched active source/report were removed; last-native-report.md is retained in the private address scratch.
