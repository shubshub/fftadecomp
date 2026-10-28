# 081459D0

Target: 0x081459D0..0x08145A98, 200 bytes / 96 reachable instructions.

The recovered routine advances a timed level change, updates active 80-byte
channel records, and stops channels when a downward change reaches zero.
The state has a channel count at offset 8, period and timer at 0x24/0x26,
a 16-bit level at 0x28, and a channel pointer at 0x2C. Channel flags and
volume are at offsets 0 and 0x13.

The retained source was tested by the canonical native matcher with agbcc
-mthumb-interwork -O2. Native exit 1: NOT MATCHING. The complete 200-byte ELF
symbol and supported direct-Thumb-call CFG passed their gates; source was
reported plausible. Byte comparison found 89/96 instructions and 191/200
bytes identical. No exact-match credit is requested.

The remaining differences concern level-load ordering and register allocation:
the target loads the level into a preserved register after the stop call and
in the channel-volume update, whereas the retained source uses low temporary
registers. The final level-bit test also places its mask constant and load in
the opposite order. Branch destinations, literal placement, and total extent
agree in the retained attempt.

Initially separate level updates and tests compiled to 190 bytes. Combining
the assignment and test naturally recovered the target's retained 16-bit mask
and its 200-byte extent. Full-width bitfield declarations and naturally inline
level getters did not resolve the load/register differences. A 16-bit local
level snapshot improved the result to the retained 191 matching bytes; widening
that snapshot hoisted the loop mask and changed the instruction count without
improving matching bytes. No artificial volatile accesses, dead expressions,
register constraints, or compiler flag changes were introduced.

The raw native result and differing report are retained outside the repository
in private v396/081459D0 scratch. Active unmatched source/report were removed.
