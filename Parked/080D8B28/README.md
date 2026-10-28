# 080D8B28 — Parked

Target extent: 0x080D8B28..0x080D8B4C, 36 bytes and 17 reachable instructions.

The recovered function accepts two signed 16-bit coordinates, calls
func_0801BB94 with constants 4, 16, 4, narrows its result to 16 bits, and returns
whether that result is nonzero.

The fixed native matcher was run with agbcc -mthumb-interwork -O2. The retained
candidate is plausible, but native verification exits 1: its complete symbol is
40 bytes and 18 instructions. The call setup matches. The remaining difference
is the result-to-boolean conversion: the compiler copies the result to another
register and combines the value with its negation, whereas the target narrows
and negates in place. This adds four bytes.

Tested natural representations were a direct nonzero comparison of a u16
callee result, an int callee result captured in a u16 local, explicit conditional
returns, and a positive comparison of the u16 local. The first, second, and
fourth produce the same 40-byte code. Explicit conditional returns also produce
40 bytes, using branches instead. The retained candidate is the positive
comparison form.

The native comparison reports 14/18 identical instructions and 33/40 identical
bytes. Its 40-byte comparison extends four bytes beyond the indexed target;
those figures are not a complete-target match claim. No byte-exact credit is
claimed. The differing native report remains outside this tree in the private
address scratch directory as native-not-matching.md. Unmatched active source
and report have been removed.
