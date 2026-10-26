# 0811BEC0: unresolved scanline boundary stores

Target: complete `[0x0811BEC0, 0x0811C018)`, **344 bytes / 167 reachable
instructions**, unchanged indexed endpoints. This candidate is **not a match**.

## Native result

Fixed compiler: `agbcc -mthumb-interwork -O2`. With the recovered candidate at
`src/0811BEC0.c`, the command from the game directory was:

```sh
env PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' python ../fftadecomp-kit/tools/match.py --root . 0x0811BEC0
```

Native exit **1**: `compiled symbol is shorter than the indexed span: 314 < 344`.
The matcher stops before emitting a complete native report or aligned diff.
No byte-exact match or plausibility-gate pass is claimed.

## Recovered behavior

The function first configures a window at `(120, 80)` using the supplied radius.
Unless the sixth argument is nonzero, it updates a two-byte left/right scanline
boundary record across twice that radius, centered on row 80. Only rows 0 through
159 are touched. Signed steps come from the table at `083A6BDC`; the left edge
is clamped below at zero, the right edge above at 240, and the right edge is
raised to the left edge when necessary. The two per-row table phases wrap at
20. Every second invocation, the initial left phase decrements with wrap and
the initial right phase increments with wrap.

## Remaining differences and attempts

The target reads the destination before complete-byte writes at `0811BF34`,
`0811BF40/44`, `0811BF68`, `0811BF6E/72`, and `0811BF86/88`. The natural
candidate omits those redundant reads. This is the same unresolved class
documented in `Parked/081104DC/README.md`; its exhausted signed/unsigned field
and mask permutations were not repeated.

An ordinary boundary struct has a four-byte stride under this compiler. A
packed two-byte record recovers the target stride. Packed plain-byte members
and packed unsigned-halfword eight-bit fields both produced a 314-byte symbol;
the retained candidate uses plain byte members. Separate negative-row and
upper-bound guards recover the target's two signed comparisons. The current
assembly also differs in register allocation, repeated table literal loads,
and signed-byte load expansion. The 30-byte size deficit is the precise native
result; no complete same-offset or aligned comparison was produced.

No assembly, volatile, pragmas, inert code, alternate compiler flags, endpoint
changes or shared header/map edits were used. The unmatched active source and
any report are absent. Claim release is owned by the coordinating session.
