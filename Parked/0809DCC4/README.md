# 0809DCC4 — unmatched natural C

Target: 0x0809DCC4..0x0809DE00, 316 bytes / 156 captured reachable instructions.

The latest fixed native matcher invocation exited 1. Source is plausible and the complete ELF symbol spans 316 bytes. Native alignment reports 143/155 instructions and 297/316 bytes identical. Direct same-offset comparison finds 213/316 equal bytes; the native alignment score is not the same-offset score.

The countdown/direction update, signed oscillating offset, four-state switch, byte counters, lookup calls, and halfword timer transitions are implemented. The opening block now matches exactly. The remaining differences are the case-1 range-result computation (target compares against 13 then 10, produces the Boolean in r0, and stores once; candidate uses a conditional Boolean in r1 and has one extra instruction), the case-3 lookup result comparison (target transfers r0 to r1 and loads the current signed byte into r0; candidate leaves the result in r0 and loads the byte into r1, with one fewer instruction), and branch/call offsets affected by those two regions. The final case and epilogue align again.

Five bounded natural candidates were tested. They covered an ordinary logical range test, upper-first bounds, explicit bounds branches, conditional Boolean computation, a separate countdown read/decrement, and signed/unsigned word lookup results with natural comparison ordering. Boolean forms produced 318-, 310-, 312-, and 316-byte symbols. Moving the current-value read before the lookup changed its observable ordering and register allocation; that form was discarded. No assembly, volatile, pragmas, dead operations, compiler changes, or forced registers were used.

Raw C SHA-256: d52266adfe426004246ad3ebf987824dcade336683bf6bb2398cfc25fd79b1d7.
Native report SHA-256: 6e94183b3ad33b657c5ba3040099b8ac9185682172129cb4ebd306a57aaeaabe.

The best complete tested C is preserved here. The native report and output remain in address scratch as last-native-report.md and native-output.txt. Unmatched active source/report were removed.
