# 080D2BF4

Complete recovered implementation for 0x080D2BF4..0x080D2CC2: 206 bytes,
92 reachable target instructions, including literal pools. It finds the
selected ten-bit descriptor ID in the global linked list, then sums the
requested category (10 through 13) from up to two 16-byte modifier records.
The byte accumulator preserves the target's modulo-256 arithmetic.

The preserved complete-span candidate is plausible with fixed native agbcc
`-mthumb-interwork -O2`, but does not match. Native aligned diff: 33/92
instructions and 129/206 bytes. Actual same-offset byte equality: 95/206.
The search and modifier logic differ in register allocation and block/pool
placement. For example, category uses r5 rather than r4, total uses r7 rather
than r5, the node and descriptor use r3/r4 rather than r2/r3, and the search
mask is kept in ip rather than r7. The first three global/offset literal
words are emitted with the first modifier-table pool instead of the target's
pool immediately before the search body. The successful-search assignment
also branches from a later block rather than the target's preceding stub.
These shifts affect branch and PC-relative-load encodings as well.

Natural forms tried: the preserved inline list-search helper with a promoted
low byte and direct mask expression (complete 206-byte symbol); explicit
word-sized mask/high-byte locals (202 bytes); a word-sized helper ID argument
(202 bytes); a descriptor-search helper owning the global list lookup and a
do-while traversal (202 bytes); and a direct in-function list walk with an
explicit result pointer (202 bytes). Each shorter candidate was rejected by
the ordinary native full-extent check. The preserved candidate was rerun
unchanged for fresh full-span evidence, saved privately as best-native-report.md
and last-native-output.txt.

No compiler flags, shared metadata, or native verification rules changed.
This is a bounded unresolved source-generation gap, not an impossibility claim.
