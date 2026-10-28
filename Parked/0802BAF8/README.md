# 0802BAF8

Target: complete 120-byte Thumb function, 56 reachable instructions. Fixed
`agbcc -mthumb-interwork -O2`, explicit `canonical-thunks-v1` native profile.

The retained second candidate splits three 256-byte blocks: each of four
64-byte source rows contributes 32 bytes to each 128-byte destination half.
It emits a complete 120-byte ELF function with 56 instructions. Its four row
pointers, copy operations, strides, high-register bases and framed return
agree structurally with the target. The remaining difference is the outer
counter increment/store appearing after row-pointer setup rather than before
it, plus the r0/r1 choices for the inner counter and callback-table loads.

Three natural forms were tested. Direct callback-table expressions and two
row pointers retain a function pointer in r7 and call `_call_via_r7` instead
of the target's `_call_via_r3`. The retained explicit row-half pointers and a
callback-table pointer produce the target extent and thunk but retain the
ordering/register gap. A pre-incrementing while loop instead turns the outer
loop into a countdown, with an extra stack load/store and a different extent.
No compiler flags or artificial source constructs were used.

Native exits were 1. The retained candidate was rejected with
`inert-spin complete body differs from ROM`; the other forms were rejected
with `inert spins require an exact unique nonoverlapping Thumb span`.
These profile failures precede normal plausibility/comparison reporting;
no accepted plausibility verdict or N/N equality is claimed. Active unmatched
source/report were removed. No match credit.
