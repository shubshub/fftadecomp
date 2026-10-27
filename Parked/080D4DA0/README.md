# 080D4DA0

Target: 0x080D4DA0..0x080D4DEC, 76 bytes / 36 reachable instructions.

The recovered function takes two byte arguments. Unless an argument is 0xFF,
it clears the corresponding nibble of the control byte at state offset 0x46
and then ORs in the supplied value (the second argument is shifted left four).
The first argument is intentionally not restricted to four bits, matching the
target operations.

The retained direct byte-field source was compiled by the canonical native
matcher with agbcc -mthumb-interwork -O2. Native exit 1: the compiled function
symbol is 60 bytes, shorter than the indexed 76-byte span. The extent gate
stopped verification before byte comparison and source plausibility; neither
gate is claimed to have passed.

Full-width u8 and u32 bitfields, a packed u32 bitfield, and a naturally inline
byte setter were also tested with the same flags. Each produced the same
60-byte extent refusal. Compiler assembly from the first bitfield attempt
combines each clear-and-OR pair into a single masked-OR store. The target has
two stores for each updated nibble and an additional byte read immediately
before every store. The tested natural field types did not reproduce these
separate writes and unused reads. No artificial reads or volatile accesses
were added. Recovering an evidence-backed representation that preserves those
operations remains unresolved.

The canonical native output is retained outside the repository in the private
v392 address scratch directory. Unmatched active source and report have been
removed. No match credit is requested.
