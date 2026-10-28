# 08029D48

The preserved complete natural C candidate compiles to the target's 138-byte
extent with fixed agbcc `-mthumb-interwork -O2`. The native matcher exits 1,
passes the direct-call CFG and source plausibility checks, and reports
136/138 identical bytes and 64/66 identical instructions.

The remaining difference is the result register for the tile address:
at 08029D6C the target has `adds r0, r0, r1`, followed at 08029D6E by
`mov ip, r0`; the candidate has `adds r1, r1, r0` and `mov ip, r1`.
Every other instruction and the referenced middle literal pool match.

Tested forms were separate pointer additions with a named palette attribute
(138 bytes, 131/138 equal), one grouped cell offset with palette expressions
at the stores (142 bytes, over the target extent), and an explicitly loaded
map base with the grouped offset (138 bytes, 136/138 equal). Naming the cell
index and using array-address syntax preserved the same final two-byte gap.
The overlong form compared four bytes beyond the target boundary and is not
match evidence. No compiler flags or verifier boundaries were changed.

The final native report is retained in the private address scratch as
`last-native-report.md`; unmatched active source and report were removed.
