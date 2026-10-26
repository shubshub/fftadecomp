# 080CCA20 — Parked

Target: 080CCA20..080CCA54, complete 52 bytes / 22 reachable instructions.

The candidate returns the first byte of a four-byte record from `data_0839475C` for values above 0xAA, indexed by value minus 0xAB. Lower values select a sixteen-byte record from `g_table_08528F34`; values above 0x55 use value minus 0x55. Both genuine mapped tables are referenced naturally.

The fixed native agbcc command (`-mthumb-interwork -O2`) compiles a complete 52-byte symbol with 21 decoded instructions and accepts the source as plausible. Native exit 1 reports 15/21 compiled instructions and 45/52 bytes identical. The upper-range path and initial working-index copy match. In the lower-range path the compiler compares and adjusts the working index directly, omitting the target's separate index copy and assigning the table pointer a different register. This also changes branch/literal offsets and alignment.

Natural signed/unsigned working indices, direct and compound index adjustment, an entry lookup helper, and an index normalization helper were tested. The entry lookup helper retained here gave the closest byte comparison. It is naturally inlined with only the target emitted under the native gate. No compiler flags or shared metadata were changed.

The differing native report is retained outside the matching root in the private address scratch directory as `native-not-matching.md`. Unmatched active source and report were removed. This candidate has no matching credit.
