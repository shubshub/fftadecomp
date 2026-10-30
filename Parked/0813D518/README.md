# 0813D518: bounded native mismatch

The recovered C describes the complete [0x0813D518, 0x0813D6A0) body (392 bytes). It uses the actual neighboring state/definition layouts, defined helper types, observed signed coordinate conversions, persistent reference values, and explicit u32-to-u8 predicate-result narrowing. The canonical compiler recipe remained `agbcc -mthumb-interwork -O2`; no shared input or native verification changes were made.

Three natural forms were tested:

1. Direct signed coordinate expressions with u16 reference variables: native exit 1, plausible complete 392-byte symbol. The native aligned comparison reported 352/392 bytes and 142/167 compiled instructions identical.
2. Word-sized reference variables receiving explicit u16 sums, with displacement-first addition: native exit 1 because the complete ELF symbol was only 384 bytes, shorter than the 392-byte indexed body. No successful report was generated for this attempt.
3. The second form with named signed16 draw-coordinate intermediates: native exit 1, plausible complete 392-byte symbol. The native aligned comparison reported 351/392 bytes and 145/170 instructions identical. This is the preserved source.

The final source remains different in literal/register allocation near the loop entry and in coordinate-expression scheduling, even though it retains the complete body extent and instruction count. The first differing instruction is at 0x0813D530: ROM `154a ldr r2, [pc, #0x54]`, compiled `1548 ldr r0, [pc, #0x54]`. An exact same-address comparison finds 61 differing bytes (331 identical); this differs from the native report aligned sequence summary. Every differing byte and full target/compiled hex are in `state/matching-0813D518-author/remaining-difference.json` at the handover root.

The current native failure report is preserved as `native-report.md`. It binds the original `src/0813D518.c` path and composite source fingerprint from the check, before the unmatched source was moved here. All three native command receipts/logs and the first two source forms are retained under `state/matching-0813D518-author/`. No match is claimed, no helper signature was widened to force code generation, and no native refusal was bypassed. Further matching remains possible; these bounded forms did not reproduce the target.
