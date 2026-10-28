# 08003134 — bounded natural-source extent gap

Target: `08003134..08003188`, 84 bytes / 42 reachable instructions.
The preserved six-cell hexadecimal formatter was tested with unchanged
`agbcc -mthumb-interwork -O2`. Its complete symbol is 80 bytes /
40 instructions. Native matching returned exit 1 with
`compiled symbol is shorter than the indexed span: 80 < 84`.
The extent gate stopped first; no native plausibility acceptance or match
credit is claimed for the preserved source.

The target normalizes the unsigned right-shift result with `lsl #16` and
`lsr #16`, comparing the shifted intermediate to zero. The compiler retains
the already bounded result without those two instructions. It also uses
logical rather than arithmetic shift for the known-nonnegative digit,
computes the digit before preserving/decrementing the output pointer, and
allocates the padding counter to r4 and saved byte pointer to r3; the target
uses r3 and r4 respectively. Both algorithms reverse-write uppercase hex,
pad the six-character field with spaces, and append a zero byte.

Direct conditional expressions with division by 16 or logical nibble shifts
produced complete 84-byte bodies. Those passed native CFG and plausibility
but differed substantially (13/42 native instruction diff score). The named
signed-digit form produced the preserved 80-byte body. A promoted digit
assigned within the conditional produced 76 bytes and also stopped at the
extent gate. No assembly, volatile RAM, forced inline, flag changes, or
artificial normalization was introduced. Unmatched active source and report
were removed.
