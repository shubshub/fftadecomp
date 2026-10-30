# 080853A0: bounded native mismatch

Target: [0x080853A0, 0x08085450), 176 complete indexed bytes and 75 reached instructions.
The retained source is the third natural form (native attempt4), with two observed
word arguments materialized independently. The native report is source-bound to
that exact source and records plausible source, 176-byte extent, 71/75 aligned
instructions and 171/176 aligned bytes, with verdict NOT MATCHING.

The ROM executes movs r5,#1 immediately after the optional descriptor override,
then later str r5,[sp,#0x18] for initializer argument11. The compiler emits
movs r0,#1 at that argument's stack store and str r0,[sp,#0x18]. Two intervening
PC-relative load displacements change with this scheduling. The fixed frame,
12-byte descriptor copy, observed fields, other operations, direct calls,
alignment and literal values agree in the aligned native comparison.

Attempts used the same defining 12-argument initializer widths and genuine typed
layouts. All native commands were:
python3 -B /home/user/Desktop/FFTA-handover-2026-10-30/repos/fftadecomp-kit/tools/match.py --root . 0x080853A0
from the isolated batch3 game-worktree, with -mthumb-interwork -O2.

1. Inline root-record word arguments. The initial native invocation rejected a
   local Record typedef collision with include/ffta.h. Qualifying local typedef
   names corrected that compile error without changing the natural form. The
   corrected invocation produced plausible source and the 176-byte mismatch above.
2. A typed selected-record local after descriptor override. The native command
   refused its shorter complete symbol, 164 < 176 bytes, before report generation.
3. Independently materialized u32 word arguments. This produced the same plausible
   176-byte mismatch as the first compiled form and is retained here.

Accounting: four native match executions, one compiler-name failure, one
shorter-symbol refusal, two complete plausible byte mismatches, zero matches,
zero successful replays, and no separate diagnostic compiles. A pre-native input
capture error (string address passed to an integer API) was retained and corrected
before the first native invocation. It did not execute the compiler.

The attempt3 stale report snapshot in the author packet is the unchanged attempt2
report left by the shorter-symbol refusal; it is explicitly not an attempt3 result.
No constant-only aliases, repurposed parameters, assembly, volatile, pragmas,
dead operations, arbitrary pointer literals, shared edits or gate workarounds were
used. No further scheduling forms were attempted.

Current-machine input pins, source and report hashes, exact full ROM/compiled
bodies, all commands, logs, exit codes and accounting are retained in:
state/matching-080853A0-author/receipt.json
