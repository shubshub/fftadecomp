# Parked: func_080C95C0

Not matched: the best plausible source reproduces 23 of 24 bytes with
`agbcc -mthumb-interwork -O2`. This is an unfinished attempt, not a finding
that the function is unmatchable.

The function narrows its first argument to an unsigned halfword and stores
the low byte of its second argument at EWRAM base plus `0x2030 + index`.
The ROM adds the field offset to the base first; the current source adds
the offset to the index first. One address-calculation instruction differs.

Both orders of the integer array-index expression produce the same mismatch.
A local pointer to the field, or chained pointer addition, folds the base and
field offset into one relocated literal and produces only 16 bytes.
An unsigned-word parameter with an explicit halfword cast also changes the
load order, matching only 21 bytes. That cast form at `-O1` is rejected by
the verifier for an unexpected nonempty allocated section.

The entry itself is corroborated by the direct Thumb call at `0x08122EB4`,
the callee's eight instructions ending in `bx lr`, and its two referenced
literal words. Its complete 24-byte extent ends at the next indexed entry,
`0x080C95D8`. Adding this missing leaf to the index allows the separate
caller `func_08122EA8` to be linked and verified without claiming this
callee's C is matched.
