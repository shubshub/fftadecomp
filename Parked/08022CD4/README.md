# 08022CD4: control-state type recovery remains unresolved

Target: complete `[0x08022CD4, 0x08022D48)`, 116 bytes and 48 reachable instructions.
The preserved candidate implements both switch cases and their complete call/store behavior.
It is an attempted type reconstruction, not a verified match.

Fresh native matching with agbcc `-mthumb-interwork -O2` exits 1:
`compiled symbol is shorter than the indexed span: 108 < 116`.
The native extent gate rejects the candidate before the plausibility gate runs;
no plausibility or complete-symbol equality claim is made.

The candidate has 44 instructions. In case 16, the target reads each control byte
before replacing its entire value:

- `0x08022D0E`: `ldrb r0, [r1]`, before storing 255 at state +0x4A.
- `0x08022D18`: `ldrb r0, [r3]`, before storing zero at state +0x4B.
- `0x08022D22`: `ldrb r2, [r0]`, before storing zero at state +0x4E.

The candidate omits these three old-value reads (six instruction bytes).
It also addresses +0x4E by adding 3 to the previous +0x4B address, whereas
the target copies the state base and adds 0x4E (two additional instruction bytes).
Case 15, parameter narrowing, signed duration forwarding, external calls,
control-byte values and offsets, and the ordinary return path are reconstructed.

Byte-wide fields were tested with packed u8 bitfields, packed u32 bitfields,
ordinary u32 bitfields, and ordinary u16 bitfields. All compiled to the same
108-byte body and omitted the three old-value reads. The preserved candidate
is the last tested ordinary-u16 bitfield hypothesis. Related captured control-state
functions exhibit the same read-before-full-byte-store pattern, but do not prove
that any particular smaller fields or containing declaration explains it.
No artificial discarded reads or volatile declarations were introduced.

The earlier dead-load deferral was only a selection heuristic. This fresh
accepted implementation attempt instead reached the actual native extent gate;
its remaining eight-byte difference is recorded here without asserting
unmatchability. Native output is retained in the private address scratch directory.
