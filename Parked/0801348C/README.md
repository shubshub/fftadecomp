# 0801348C — unresolved native byte mismatch

Target: 0x0801348C..0x08013526, 154 bytes and 76 reachable Thumb instructions.

The retained natural C calls func_0801344C with the original buffer and signed
16-bit index, then returns its signed 16-bit result. When the unsigned byte
offset is nonzero, its low nibble is replicated into a 16-bit increment pattern.
The function visits 64 halfwords, skips zero words, and conditionally adds the
matching increment nibble for each nonzero nibble. Every addition narrows to
16 bits before testing the next nibble, preserving carries and wrapping.

Fresh default native match.py with fixed agbcc -mthumb-interwork -O2 exited 1.
The complete compiled ELF symbol is 156 bytes. Typed direct-call linking and
byte comparison completed; the native source gate reported `source plausible`,
but bytes differ. This is not a match and receives no source credit.

The closest source emits one extra mask-load instruction for the lowest-nibble
test, uses a different equivalent mask operand for the next test, and initializes
the loop countdown before the increment-pattern shifts rather than afterward.
The extra instruction shifts later branch destinations and the function end by
two bytes. The tool reported 66/77 instructions identical (146/156 bytes) over
its compiled-length comparison; the actual indexed target remains 154 bytes
and 76 reachable instructions.

A shared named mask for each update produced a 144-byte complete symbol, so the
extent gate rejected that form before byte or plausibility checks. An ordinary
inline nibble-update helper produced a 160-byte symbol, reached byte comparison,
and passed source plausibility, but introduced additional register copies and
a wider saved-register set. The direct unrolled form retained here was restored
and freshly checked as the closest tested candidate. No compiler flags changed.
No artificial liveness, volatile access, dead expression, or assembly was added.

The generated differing native report and command output remain outside the
repository in the private address scratch directory as native-not-matching.md
and native-result.txt. Unmatched active source and report were removed.
