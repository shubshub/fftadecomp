# 081269E4 — parked

One natural C candidate, fixed agbcc `-mthumb-interwork -O2`.
The supplied native matcher exits 1: `compiled symbol is shorter than the indexed span: 192 < 196`.

The target reads both control bytes immediately before replacing them:

- `0x08126A62`: `ldrb r3, [r1]`, followed by `strb r2, [r1]` at `0x08126A64`.
- `0x08126A6A`: `ldrb r2, [r0]`, followed by `strb r1, [r0]` at `0x08126A6C`.

The loaded values are unused. The natural byte-field assignments omit these two reads, accounting for four missing bytes; register allocation and branch/literal displacements around that block also differ. Unchanged-candidate assembly is preserved privately as `candidate.s` beside the full target disassembly.

No variant search, alternate flags, forced reads, volatile fields, assembly, or steering constructs were attempted. Native matching stopped before producing a report. Original complete control-field declarations remain unknown.
