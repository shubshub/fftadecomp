# 0806B460: complete-symbol extent mismatch

Target: complete 0x0806B460..0x0806B4C4, 100 bytes and 37 reachable
instructions. Accepted claim 6461361149. Fixed agbcc flags:
`-mthumb-interwork -O2`; default native selector.

The preserved natural C implements both state tests through genuine
`func_0806FE14`, the sound calls, the command-byte updates, and the state
byte at 0x446C. Its state layout follows already matched neighboring
0806B228, 0806B4C4 and 0806D2B4; the callee's matched body returns the
first byte of its argument. No aliases, helpers, volatile accesses,
assembly, padding or changed flags were introduced.

Three natural alternatives were compiled: an ordinary u8 command pointer
with if/else-if, an early return after the first successful branch, and
a one-byte command structure with if/else-if (the preserved candidate).
Every native run refused at the complete ELF extent gate:
`compiled symbol is shorter than the indexed span: 96 < 100`.
The byte-comparison and source-plausibility gates were therefore not reached;
there is no match or plausibility credit and no current active report.

The candidate merges the two command-byte stores into one common tail
(STRB at object offset 0x46), using one preserved command pointer. The ROM
has distinct STRB instructions at 0x0806B482 and 0x0806B4AA and preserves
the incoming pointer in both r4 and r6. Those two additional Thumb
instructions account for the four-byte complete-symbol difference. The
candidate has 35 reachable instructions versus the target's 37, with the
same four calls and the same literal values. Register allocation, branch
displacements and PC-relative pool offsets also differ. No complete byte
comparison was accepted.

No grounded type or layout requirement was found that explains the ROM's
duplicate pointer representation and prevents this tail merging. Artificial
pointer aliases or forced retained stores were not added to obtain it.
The original unmodified final compiler relocatable ELF and its disassembly
are retained outside matching-root in sibling 0806B460/candidate.o and
candidate-disassembly.txt. The native refusal is in native-match.log.
