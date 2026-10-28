# 0801A42C

Complete resource-copy reconstruction, parked after five natural mode-selection
forms compiled shorter than the indexed target with agbcc -mthumb-interwork -O2.

Target: [0x0801A42C, 0x0801A518), 236 bytes / 96 reachable instructions.
Retained candidate: complete ELF symbol 228 bytes, ending at 0x0801A510;
the compiler assembly contains 92 instructions. Native match.py exits 1 at
`compiled symbol is shorter than the indexed span: 228 < 236`. It does not
reach native byte comparison or the plausibility verdict; no matching score
or plausibility success is claimed.

The function resolves the -1 index sentinel, maps two state bits to a resource
mode, and selects one of three resource paths. Mode zero uses an 88-byte packed
record's bytewise-read offset, then dispatches an LZ77 resource or copies a
21-bit halfword count from the packed compression header. The other modes use
the record's byte at offset 0x56 and a halfword offset table in one of two banks.
All paths and layouts are represented in the retained C.

The target materializes modes 1, 2, or 0 through a common r0-to-r3 join and
compares the resulting mode with zero before selecting the record path. The
compiler threads known nonzero modes into the bank path and enters the zero
path without that materialization/join. The retained switch additionally tests
state value 1 before 2; the target tests 2 before 1. The shorter control flow
also shifts literal pools and branch offsets.

Tried an if/else mapping, cached and direct nested conditional expressions,
an unsigned-byte mode selector, and a switch mapping. All five native attempts
produced 228-byte symbols. The packed record/header reads, signed record index,
bank offset tables, and decompression/copy calls were reconstructed directly;
no helper, assembly, volatile access, pragma, or inert control flow was added.

The owned unmatched source and generated-report path were removed. Only this
README and the recovered C remain under Parked/0801A42C/.
