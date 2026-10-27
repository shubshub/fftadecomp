# 08050B9C

Complete recovered C for 08050B9C..08050BF0: 84 bytes, 38 reachable instructions.
The default native matcher with agbcc -mthumb-interwork -O2 exits 1:
complete ELF extent accepted, source plausible, bytes differ.

The best tested candidate has the correct 84-byte extent. Its lookup uses
`lsls r0, r0, #16; ldr r1, [r4]; ldr r2, literal; adds r1, r1, r2;
lsrs r0, r0, #14`. The ROM places that final shift immediately after
`ldr r1, [r4]`, before the literal load and base addition. The remaining
instructions and literal agree. Native aligned diff: 37/38 instructions,
82/84 aligned bytes; direct same-offset equality: 78/84 bytes.

Natural forms tried: indexed pointer-table access; an explicit selected-slot
pointer; u16 and promoted u32 identifiers; a legacy trailing table member;
and an explicit byte offset. The selected-slot form fixed operand order but
retained the shift placement difference. The trailing-member and byte-offset
forms instead combined the constant offset with the index before loading the
owner. An incomplete trailing array is unsupported by this compiler.

The preserved candidate uses the best tested explicit-slot form. No assembly,
volatile, compiler flag changes, forced inline, or artificial operations were
used. This is a bounded unresolved scheduling difference, not proof that no
natural C form can match. Native output and report remain in the private
address scratch directory.
