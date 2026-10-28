# 0805F708

Complete recovered menu-selection update for 0x0805F708..0x0805F772. It initializes the secondary cursor, either sets the primary selection directly or updates selection plus the list, then updates the list using the primary cursor's signed selection byte.

Fresh canonical native matching with fixed agbcc `-mthumb-interwork -O2` exited 1: source plausible, bytes differ. Target and candidate are both 106 bytes / 48 reachable instructions. Native aligned diff score: 47/48 instructions, 104/106 bytes. Independent same-offset equality: 102/106 bytes. These are different measurements.

All same-offset differences are at relative offsets 0x32, 0x33, 0x34, 0x35. Before the call to 08017FB0, the target at 0805F73A prepares R1 from R6 and then moves SB into R0; the candidate emits those two independent argument moves in reverse order. Every other byte agrees, including the prologue, branches and all direct-call relocations.

Natural forms tried:

- Explicit typed pointers for the primary/secondary cursors and list: preserved candidate, with the two-move ordering gap.
- A promoted integer declaration for the setter parameter: same residual; reverted. The existing matched 08017FB0 source confirms a byte-sized setter parameter, which is retained in this candidate.
- A wide selection input normalized to a local byte: additionally reordered input narrowing, reducing aligned equality to 100/106; reverted.
- A direct `&state->cursor` expression at the setter call instead of the named pointer: same two-move residual; restored the simpler shared pointer.

This bounded attempt records an argument-setup scheduling difference under the fixed profile, not permanent impossibility. No assembly, volatile access, compiler flags, forced inlining or inert code were used. Native output and the source-bound nonmatching report remain in private address scratch. Unmatched active C/report were removed.
