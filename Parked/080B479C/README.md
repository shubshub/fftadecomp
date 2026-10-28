# 080B479C

Complete target: `[0x080B479C, 0x080B48CC)`, 304 bytes and 147 reachable
instructions. The candidate reconstructs the entire function: determine the
range, advance signed byte coordinates along the supplied direction, select
the appropriate position validator, and append accepted coordinates and height
to four-byte output records.

The final native invocation used the fixed agbcc `-mthumb-interwork -O2`
toolchain and exited 1. It accepted the complete 304-byte ELF symbol, ordinary
direct-call/frame proof, and source plausibility, but reported bytes differing.
The tool's aligned score is 139/146 instructions and 293/304 bytes; these are
alignment scores, not same-offset equality or match credit.

The remaining difference is the range-selection block, approximately target
`0x080B47D6..0x080B4806`. The candidate hoists the constant 1 into r2 before
testing mode, assigns 4 into r2 on the other branch, and moves the range helper's
r0 result into r2. The target branches to separate assignments of 4 or 1 into
r0 and joins directly with the helper's r0 result before one byte narrowing.
The following coordinate loop, validator calls, output stores, and epilogue
align after that block.

Unsigned coordinate locals let the compiler eliminate signed-byte operations
and produced a shorter symbol. Signed byte parameters and locals recover those
operations. A byte range narrows only the helper branch and produces 302
bytes. Keeping a full-width range and narrowing once before iteration restores
the full 304-byte extent. Ordinary if/else, a conditional expression, and a
two-way switch did not recover the target range-selection sequence. No other
compiler flags or forbidden source constructs were used. This is a bounded
unresolved compiler-expression difference, not a finding of unmatchability.

Final native output is retained outside the matching root at
`../080B479C/match-current.log`. The unmatched src/report files were removed.
