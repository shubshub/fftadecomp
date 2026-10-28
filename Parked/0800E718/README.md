# 0800E718 — recovered, not byte matching

Target: `[0x0800E718, 0x0800E878)`, 352 bytes / 173 reachable instructions.

The preserved candidate implements midpoint-circle span generation. It emits four symmetric scanline spans per iteration, adds the mapped `data_02009160` byte to each right edge, optionally clips rows to `[0, 159]`, and uses the radius as the vertical center when clipping is disabled. Coordinate, decision, and loop updates narrow to halfwords.

At fixed agbcc `-mthumb-interwork -O2`, the native matcher exits 1 because the preserved candidate's complete symbol is 336 bytes, 16 bytes shorter than the indexed target. The native full-body guard stops before an instruction-agreement verdict, so no byte/instruction match count is claimed. The target reserves a four-byte stack slot for the signed vertical center and saves its two shifted loop-coordinate values in r3/r5; the candidate keeps the vertical center in r7, needs no local stack slot, and uses r1/r5 for those values. Initial radius conversion and decision setup also differ.

Bounded natural type forms tried:

- Preserved signed-halfword coordinates, radius, offsets, and decision: 336 bytes.
- Unsigned-halfword inputs/offsets with explicit signed coordinate/loop interpretations: 310 bytes, rejected as shorter.
- Unsigned-halfword inputs with signed local offsets/decision and decision initialized from the input radius: 332 bytes, rejected as shorter.

No exact match was obtained within these forms. This records a bounded fixed-flag attempt, not permanent impossibility. The nonmatching source and any generated report were removed. No assembly, volatile access, compiler pragmas, dead code, or compiler-steering constructs were used.
