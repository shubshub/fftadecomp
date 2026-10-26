# 08044158 — Parked

The fixed native matcher returned exit 1 with source plausibility `plausible`.
The complete compiled symbol is 662 bytes, matching the indexed target extent
`[0x08044158, 0x080443EE)` and its 312 reachable instructions. The comparison
finds 659/662 identical bytes and 309/312 identical instructions; only three
single-byte instruction differences remain.

At target addresses `0x08044182`, `0x08044244`, and `0x08044314`, the target
uses `adds r4, r7, r6` (`bc19`) and the candidate uses `adds r4, r6, r7`
(`f419`). These are commuted entry-address additions. Every other byte,
including control flow, packed field accesses, literal pools, and function
extent, matches. This candidate has no match credit.

Tested natural forms: raw panel flag operations (650-byte symbol), panel
bitfields with an independent cursor counter (662 bytes, with preheader
ordering differences), cursor derived from the loop index (current extent
and three remaining operand-order differences), indexing through the parent
collection (658-byte symbol), and equivalent array indexing versus pointer
addition (same three differences). No assembly, volatile accesses, pragmas,
or forced operand-order source forms were introduced.

The retained C is the last tested candidate, unchanged. Its native report
is preserved in the private address scratch as `native-report.md`.
