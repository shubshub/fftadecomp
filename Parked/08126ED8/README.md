# 08126ED8

The complete indexed ROM target is [0x08126ED8, 0x08126FCC): 244 bytes and
112 reachable instructions. The recovered function concatenates selected
coordinate lists into a destination buffer, in either forward or reverse
order. Each list contains 32 four-byte coordinate records and a signed count.
Intermediate lists omit their shared endpoint; the final list includes it.
Copies use the genuine typed callback at data_0836D4BC through the compiler's
canonical _call_via_r3 thunk.

Three natural candidates were tested with the fixed agbcc
`-mthumb-interwork -O2` configuration and the native
`--function-address-profile canonical-thunks-v1` matcher. The preserved final
candidate emits one complete 240-byte function with 110 instructions. It
recovers both traversal paths, list stride, callback reloads, endpoint counts,
reverse record indexing and destination advancement.

The remaining difference is selector setup and register allocation. The
candidate saves the destination to r8 before narrowing the first selector
into r0. The target narrows the selector in r1, saves the destination later,
and explicitly moves r1 into r0 before the forward lookup. In the reverse
path, the candidate adds the high-register list count directly to r0; the
target first moves the count to r2 and adds r1 plus r2. The two omitted
instructions make the candidate four bytes shorter and change subsequent
call and literal positions. The later loop bodies otherwise reproduce the
recovered instruction operations and register roles.

The first candidate used a const callback declaration and conventional
post-increment reverse indexing; the compiler cached the callback across
copies and introduced an additional stack slot. A mutable callback declaration
and an explicit copied-record counter recover the target's reload and reverse
copy behavior. Initializing that counter immediately before its own loop also
recovers the target's local register lifetimes. No assembly, volatile access,
compiler flag changes, dummy expressions, padding or address aliases were used.

The final native run exits 1 with
`inert spins require an exact unique nonoverlapping Thumb span` because the
compiled extent is 240 bytes rather than 244. The native plausibility stage
was not reached, and no match or plausibility credit is claimed. This is a
source code-generation mismatch, not a requested metadata-boundary change.

The final native output remains at
`../../../08126ED8/match-current.log` relative to this README. The active
unmatched source and report were removed; this pair preserves the complete
best tested implementation.
