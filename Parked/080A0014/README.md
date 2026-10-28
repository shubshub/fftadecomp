# 080A0014

Complete target: `[0x080A0014, 0x080A0252)`, 574 bytes and 272 reachable
instructions. This complete natural implementation is not byte-identical.

The final native matcher invocation used the approved ROM and fixed agbcc
`-mthumb-interwork -O2`. It accepted the complete caller CFG, fixed frame,
ordinary direct-call linking and source plausibility, then exited 1 for byte
differences. The compiled symbol is 574 bytes; the comparison reports
254/271 instructions and 554/574 bytes identical. The retained native output
is `../080A0014/match-current.log` relative to the matching root.

The remaining differences are confined to the height-limit check and scratch
register choices in the first distance case:

- At target 0x080A0134..0x080A0170, the height limit occupies r4 and the first
  height occupies r5; the candidate uses r5 and r4 respectively and retains
  the absolute difference in r4 instead of r0. The candidate also loads the
  0xFF3F mask directly into r0, whereas the target loads r3 then copies to r0.
  The candidate emits an additional move when capturing the first height.
- At target 0x080A0196..0x080A01AA, temporary registers for the two coordinate
  differences differ. The switch, explicit signed maximum, shared Manhattan
  comparison, call order, branches, frame and complete symbol size otherwise
  align in the final native comparison.

The source validates both coordinate pairs and destination terrain, handles
zero/disabled actions through 0x0809FEF0, checks action eligibility and height
limits, and applies the three recorded distance-shape rules. Standard `abs`
is expanded by the fixed compiler without an external helper call. The
0x080CCD50 property-selector type agrees with the existing matched callee.

Natural attempts included separate versus reused eligibility/property locals,
conditional versus explicit maximum branches, scoped coordinate-distance
locals, byte/halfword/full-width height temporaries, and signed or unsigned
range representations. The retained source has the best complete-size native
comparison. No alternate compiler flags, assembly, volatile accesses, dead
code or metadata changes were used. The remaining allocation gap does not
establish that this function is unmatchable.
