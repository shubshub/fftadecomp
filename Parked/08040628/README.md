# 08040628: bounded native mismatch

Target: [0x08040628, 0x080406D4), 172 complete indexed bytes and76 reached
instructions. The native function_span is positive172 and matches the complete
ROM body. The retained final source is natural form3, with the two observed
u32 record values loaded independently after the optional descriptor override.

The default native checker accepts the local12-byte descriptor copy, the genuine
32-byte scalar outgoing argument area, the defining12-argument08017424 widths,
the existing named globals, and the ordinary08016C90(state,u8) contract.
It reports plausible source and the complete172-byte compiled extent, with
verdict NOT MATCHING:72/76 aligned instructions and167/172 aligned bytes.
The related080853A0 scheduling risk identified before authoring occurred here.

The ROM materializes constant1 in r5 immediately after the optional descriptor
override, at08040660, then stores r5 as initializer argument11 at SP+0x18.
The compiler instead materializes1 in r0 immediately before that argument store.
Two intervening PC-relative load displacements differ with the scheduling.
The aligned comparison otherwise preserves the descriptor copy, observed field
accesses, conditional updates, genuine outgoing arguments, both direct calls,
restoring frame and literal values. Exact same-offset byte differences and both
complete bodies are retained in the source-bound author receipt.

Three distinct natural forms were checked with the same default command:

1. Direct record-word expressions in the initializer call. Plausible complete
   172-byte output, with the constant1 scheduling mismatch above.
2. A typed selected-record local after descriptor override, then its two u32
   members as initializer arguments. Native refusal: compiled symbol is shorter
   than the indexed span:164 <172. No new report was generated. The report left
   at that point belonged to attempt1 and was not treated as an attempt2 result.
3. Independently materialized u32 record values after the override, followed by
   the same12-argument call. Plausible complete172-byte output identical to
   attempt1, with the same scheduling mismatch. This exact source is retained.

Every normal native invocation was:
python3 /home/user/Desktop/FFTA-handover-2026-10-30/repos/fftadecomp-kit/tools/match.py --root /home/user/Desktop/FFTA-handover-2026-10-30/state/resumed-matching-batch3-20261030/game-worktree 0x08040628

The compiler flags were -mthumb-interwork -O2. The actual DEFAULT_CPP was cpp,
resolved to /usr/bin/x86_64-linux-gnu-cpp-13. All nine headers, three maps,
tool sources, actual binary roles and this machine's runtime were captured
before the first C/native work and remained unchanged through the final check.
The final report's source digest is the original src/08040628.c plus all nine
headers. The source and report were then moved here without changing bytes.

Accounting: three normal native checks and three agbcc invocations, two complete
plausible mismatches, one shorter-symbol refusal, zero matches, zero successful
replays, and zero separate compiler diagnostics. No fourth form was attempted.
No assembly, volatile, pragmas, fabricated ABI, inert operations, constant
liveness aliases, shared inputs or compiler profiles were used to force output.

Current-machine input pins, all source forms, native stdout/stderr/exit records,
complete available compiled bodies, raw and composite source hashes, report
hashes and precise diagnosis are retained in:
state/matching-08040628-author/receipt.json
