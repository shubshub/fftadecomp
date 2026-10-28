# 0812E130 — Parked

Target: 0x0812E130..0x0812E1A8, 120 bytes / 53 instructions.

The complete natural C candidate uses typed unit, ability and requirement-table records, a genuine signed remainder expression, and the existing data_0852736C binding. No runtime-address aliases or compiler steering are used.

The latest native matcher invocation exited 1 with: `signed remainder caller requires exact complete mapped ROM bytes`. The runtime caller prerequisite rejected the candidate before the normal byte-comparison and plausibility gates; no plausibility pass is claimed. The default function-address profile was used with fixed agbcc `-mthumb-interwork -O2` and the approved ROM.

Independent compilation with those fixed flags emits one 120-byte target FUNC symbol and 53 instructions. Its remaining observed difference is the flag-mask destination and dependent comparison: the candidate masks and compares r0, while the target masks and compares r6. The table address calculation, signed remainder expression, clamp and return layout follow the captured target.

Bounded natural alternatives covered early returns versus nested conditions, table indexing versus a typed table pointer, and byte versus promoted flag locals. The retained typed-pointer candidate recovered the table-address instruction order. Native exactness remains unresolved, and the unmatched active source/report have been removed.

Private native output is retained outside the repository at `../0812E130/native-result.txt` relative to the matching root.
