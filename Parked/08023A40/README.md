# 08023A40

Complete natural C candidate: 96 bytes, matching the complete 96-byte target extent. Fixed agbcc `-mthumb-interwork -O2`; final native matcher exit 1, source plausible, 94/96 bytes and 42/44 instructions identical.

Only two instructions differ. At 08023A70 the target has `lsrs r1, r0, #16`, while the candidate has `lsrs r0, r0, #16`. At 08023A76 the target has `lsls r0, r1, #16`, while the candidate has `lsls r0, r0, #16`. The target retains the narrowed poll result in R1; the candidate reuses R0. All other bytes, including the middle literal pool, agree. This is an unresolved result-lifetime/register-allocation difference, not a semantic or indexed-extent gap.

Tested natural forms: u16 poll result with u16 or word-return declaration; promoted unsigned and signed word locals after u16 conversion; signed versus unsigned nonzero predicates; and a raw word result narrowed independently at each use. All complete 96-byte forms retained this same two-instruction difference. The raw word/per-use-cast form compiled to 92 bytes and was rejected by the short-symbol extent gate before plausibility or comparison. No compiler flags, assembly, artificial volatile, forced inline, or dead code were used.

The retained source is the tested signed promoted-result form. Last complete native report remains in private address scratch as `last-native-report.md`. Unmatched active source and report were removed. No exact match is claimed.
