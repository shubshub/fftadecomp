# 0801E204

Unmatched after three bounded plausible native candidates under
`agbcc -mthumb-interwork -O2`. Every execution exited 1. The target has 160
complete bytes and 67 instructions. The final candidate compiles to 168 bytes.

The recovered function initializes the four state bytes, selects format 1,
builds two packed halfword fields from integer operands 0x06007000/0x06006000
and 0x06000000, invokes the layer setter, then stores the three integer words
and final byte/halfword state. No pointer semantics or pointer casts were
introduced for those numeric packed operands.

The existing definitions establish `u16 func_08003A74(u32 packed)` and
`u32 func_08003A80(u32 packed)`. Bounded complete ROM inspection establishes
the setter argument narrowing to `(u16 value, u8 layer)` at 080034B8 and the
byte-sized format input at 0801E098. Helper bodies and exact identity hashes
are retained in the task packet. These are caller declaration observations,
not independent callee contracts or termination proofs.

Three forms were checked:

1. Local integer address values, a local state pointer, and a combined u16
   packed expression: 160 compiled bytes, raw 103/160 byte comparison.
2. Direct integer constants/global fields and a staged u32 packed accumulator:
   160 compiled bytes, raw 94/160 byte comparison.
3. Direct integer constants/global fields and a staged u16 packed accumulator:
   168 compiled bytes, raw 123/168 byte comparison.

The first form loads constants before the initial stores and assigns different
registers. The second retains additional constants and widens the u16 helper
result. The final form uses the target accumulator register but inserts extra
halfword narrowing after helper results and at intermediate compound updates;
it also schedules the final OR and constant loads differently. The target
narrows only after each complete combined packed field. Register assignment,
literal offsets, BL displacements, and instruction scheduling still differ.

`match.md` is the exact final native report. Its 168-byte comparison includes
eight bytes beyond the 160-byte target; its side-by-side decoder misdecodes
some target Thumb BL pairs. These raw metrics are not byte-exact match claims.
The authoritative complete target/decode is `target.json` in the handover-root
`state/matching-0801E204-author/` packet. That packet also preserves both prior
sources/reports/logs, the final log, helper evidence, and a source-bound
current-machine receipt. No assembly, volatile, pragmas, dead operations,
artificial register pressure, invented pointer casts, helper edits, or toolkit
changes were attempted.
