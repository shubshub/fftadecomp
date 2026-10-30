# 0809B6D0: bounded natural forms remain nonmatching

Complete indexed target: [0x0809B6D0, 0x0809B7BE), 238 bytes and 119
reached instructions, entirely code. No external calls, literals, second entry,
or body-boundary correction is involved.

Three natural source forms were checked with the native match command:

1. Direct compound clamp comparisons: 228 bytes. Native exit 1, shorter-symbol
   refusal before report generation.
2. Shared inline ternary clamp, with signed step multiplied before direction:
   234 bytes. Native exit 1, shorter-symbol refusal before report generation.
3. Direction-separated clamp with a nested maximum expression: 246 bytes.
   Native exit 1. Source plausible and closed leaf CFG; bytes differ.

The final source and native report are retained here without changes. Its
first byte difference is at 0x0809B744: compiled `adds r1, r3, r0`, expected
`adds r0, r3, r0`. Clamp branching and register transfers then differ. The
final symbol is eight bytes longer than the indexed target. The native report
compares 246 ROM bytes because the compiled symbol has that size, including
eight bytes beyond the indexed owner. That comparison does not extend the
owned target or claim that a following function belongs to this body.

The complete direction conversion, signed state/actor reads, and multiplication
prefix through 0x0809B742 match in the final form. The actual local direction
helper and movement-family fields are grounded in existing 0809B544, 0809B470,
and 0809B818 C. No source steering or shared-input changes were attempted.

Exact sources for all three forms, native logs, current-machine input pins,
failed-candidate diagnostics, and source-bound receipt are retained under
state/matching-0809B6D0-author in the handover root. There were three native
checks, no successful match, two diagnostic compilations of failed candidates,
and one diagnostic invocation that failed before preprocessing because its
Runner inherited the primary root. That temporary workspace was removed by
the native Runner context manager; subsequent diagnostics used an explicit
isolated root. No primary source or report changed.
