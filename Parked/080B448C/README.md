# 080B448C

Complete indexed target: `[0x080B448C, 0x080B44F8)`, 108 bytes and 50
reachable instructions. The candidate implements the complete property lookup:
use parameter property 5 or default 1 when action is zero or action property 4
has bit 0x80; otherwise use action property 7 masked to six bits when property
4 has bits 0xC0, or return its low byte.

The final native invocation used agbcc `-mthumb-interwork -O2` and exited 1.
Its complete compiled ELF symbol is 112 bytes. Ordinary direct-call proof and
source plausibility pass; byte identity does not.

The remaining difference is in target `0x080B44D8..0x080B44F2`, at the final
mask and result join. The candidate keeps the byte result in r1, copies the
property helper's r0 result into r1, loads mask 0x3F into r0, and ANDs into r1.
It also copies r1 back into r0 at the final return. The target loads the mask
into r1 and keeps the result in r0 throughout. Those two additional moves make
the candidate four bytes longer and change the preceding join branch offsets.
The earlier complete fallback call blocks agree apart from those offsets.

The matcher compares the compiled extent, so its final aligned score includes
four bytes beyond this target's indexed end. That score is not a statement of
same-offset equality for the 108-byte target and is not match credit.

Tried direct early returns, nested assignments with one result variable, an
explicit full-width helper intermediate followed by a byte result, and
explicit byte conversions. Direct returns let the compiler merge the two
fallback calls and shorten the body. A shared full-width intermediate removes
necessary byte conversions. A byte result with a full-width intermediate
preserves the complete fallback blocks but retains the final register moves.
Compound masking and an early masked return change the code structure further.
Only the fixed flags were used, and the callee declarations follow existing
matched sources. This is a bounded unresolved result-allocation difference,
not a finding of unmatchability.

Final native output is retained at `../080B448C/match-current.log` outside the
matching root. Unmatched src/report files were removed.
