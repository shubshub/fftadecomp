# 080D7674 — Parked

Target: 080D7674..080D7796, complete 290 bytes / 136 reachable instructions.

The candidate selects a descriptor through a twelve-byte entry table, clamps the transfer chunk to the remaining count, dispatches by the format kind and flags, and advances the destination, source and remaining count only when the transfer is unfinished. The source advances by 0x400, and raw-copy counts use the selected entry's halfword size shifted right once. All eight callees use natural indexed function references.

The fixed native agbcc command (`-mthumb-interwork -O2`) produces a complete 290-byte symbol and accepts the source as plausible. Native exit 1 reports 128/136 instructions and 282/290 bytes identical. The remaining differences are the position of the format-pointer load relative to the clamp, the clamp's temporary register, and the destination registers for two flag-mask tests. Constructor/converter calls, their arguments, dispatch shape and final transfer updates otherwise match.

Direct adjacent field conditions compiled to a 296-byte symbol because the compiler merged kind and flag tests into halfword comparisons. A cached byte flag value avoids that merge and restores the 290-byte extent. Byte and promoted flag locals, a naturally inlined mask accessor, and loading the format pointer at its first dispatch use were tested. The last formulation retained here gave the closest comparison. No compiler flags or shared metadata were changed.

The differing native report is retained outside the matching root in the private address scratch directory as `native-not-matching.md`. Unmatched active source and report were removed. This candidate has no matching credit.
