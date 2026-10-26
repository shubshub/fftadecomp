# 08026F9C

Recovered resource-list builder, target `[0x08026F9C, 0x080270CC)`.
At fixed `agbcc -mthumb-interwork -O2`, the native matcher verifies the whole
304-byte symbol and direct Thumb calls as plausible, with no unresolved
relocations. It exits 1: **295/304 bytes and 129/138 instructions identical**.

All nine differing bytes are the swapped descriptor and resource pointers:
the candidate keeps the list entry in r5 and the resource-table entry in r6;
the target uses r6 and r5 respectively. The first difference is the descriptor
address result at 0x08026FC2. The affected loads are kind, the three ID reads,
the resource address result, its two cost reads and its name read. Every other
instruction, call, branch, literal-pool byte and the complete extent agrees.

Natural forms tried include counter initialization at its point of use;
byte versus promoted cost snapshots inside or before the nonzero branch;
typed versus byte views of both records; explicit resource byte offsets;
function and block scopes for existing temporaries; early filter continues;
kind dispatch through if or switch; promoted text-width arithmetic; and a
cached descriptor-array base with indexed field accesses. The closest forms
produce identical 304-byte output with this register swap. Other forms add
initialization/cost copies, produce 300 or 308 bytes, or change the descriptor
address evaluation order. The preserved source is the simplest tested best
form. No alternate compiler flags, assembly, volatile operations, pragmas or
artificial code were used. This is a bounded attempt, not a permanent
impossibility claim.
