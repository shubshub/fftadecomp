# 081352CC — parked natural attempt

Target: complete indexed Thumb body `[0x081352CC, 0x0813554E)`, 642 bytes,
300 reachable instructions, including the branch-skipped literal `0x149`.

The best candidate compiles to a complete 634-byte ELF symbol, corresponding to
`[0x081352CC, 0x08135546)` at the target base. Its generated assembly contains
296 instructions. The native matcher exits 1 before comparison/report generation:
`compiled symbol is shorter than the indexed span: 634 < 642`.
No byte-equality score or native plausibility verdict was produced.

The recovered C performs the initial record pass, accumulates entry amounts,
selects the mode and optional paired group, then evaluates either paired entries
or eligible entries across matching groups. Record fields use the observed
pointer, flag, kind, mode, payload and amount offsets. No external data binding
is needed: the sole literal is the scalar mode `0x149`.

## Remaining differences

At target `0x08135316..0x08135320` and `0x0813542E..0x08135438`, the accumulator
is sign-extended from 16 bits before adding an unsigned 16-bit entry amount,
then truncated back to 16 bits. The fixed compiler removes each pre-add sign
extension from the natural typed candidate because the sum is truncated.
These are four missing instructions (eight bytes), not an unused byte load.

The target uses r7 for the accumulator and r6 for the initial/final inner index;
the candidate uses r6 and r7 respectively. The target spills count/mode/base/
paired-group at SP+0x10/0x14/0x18/0x1C; the candidate uses SP+0x18/0x1C/0x14/0x10.
Both use r8 for the group, r9 for the active flag or regular entry count, r10
for the outer index, and a 36-byte frame. The candidate also drops the target's
zero initialization before the mode branch and uses one extra move when setting
the paired-entry active flag.

## Bounded attempts

Three native matcher invocations used the required agbcc
`-mthumb-interwork -O2` configuration. The initial unsigned-16 accumulator and
shared counters produced 626 bytes. Signed-16 accumulation, counter reuse
following the nesting, and direct secondary-header access produced 630 bytes.
A wide accumulator with explicit signed interpretation and 16-bit normalization,
plus branch-local entry counts, produced the preserved 634-byte candidate.
No compiler flags, assembly, volatile accesses, pragmas, invented helpers, or
shared files were changed. Native src/report paths were removed before handoff.

Claim: accepted request 6406395899, label `codex-sol61-v59-081352cc`.
Root owns release and integration.
