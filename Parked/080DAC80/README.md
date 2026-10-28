# 080DAC80

Complete recovered natural C; not a byte match. Target extent:
0x080DAC80..0x080DAD3A, 186 bytes and 87 reachable instructions.

The function obtains the task record's object pointer at offset 4 and passes
it to 0800C614 to obtain the output pointer. Coordinates are interpreted as
signed 16-bit values. Zero dimensions produce no drawing call. Equal nonzero
dimensions call 080D9F60. Unequal dimensions call 080DA074 using the larger
dimension shifted by 4, scale 0x100 on that axis, and the signed quotient of
squared dimensions scaled by 0x100 on the other axis.

The preserved source was tested through the default native matcher with fixed
agbcc -mthumb-interwork -O2. Native exit 1:
`signed quotient caller requires exact complete mapped ROM bytes`.
That provenance check requires complete equality and stops before producing
an ordinary linked byte-diff report. No aligned score, byte-equality count,
or successful native plausibility verdict is claimed.

The same fixed compiler's emitted ELF function symbol measures 190 bytes and
89 reachable instructions. The semantic draw_shape helper is fully inlined:
the object contains only func_080DAC80 as a defined function, with the two
ordinary object-access calls, two __divsi3 sites and the two drawing calls.

Precise remaining differences include a 20-byte local frame instead of the
target's 12-byte outgoing-argument frame, additional spills of the original
width and signed y coordinate at local offsets 12 and 16, different register
allocation for size/scales/output, and different common call-setup placement.
The target keeps signed x/y in r4/r5, width/height in r6/r7, output in sl,
size in sb and the horizontal scale in r8. The preserved candidate instead
moves signed x to sl, spills signed y, and keeps output in sb. The signed
quotient calculations and required external calls are recovered, but the
complete instruction sequence differs and is four bytes longer.

Bounded natural forms tried:

- Direct branch-specific calls with signed 16-bit coordinate declarations:
  extra coordinate conversions and a 24-byte local frame.
- Signed 32-bit coordinate locals with a shared scaled-call site:
  a 16-byte local frame and different branch/call ordering.
- Branch-specific calls using those signed coordinate locals:
  a 20-byte local frame and different register allocation.
- Signed rather than unsigned size/scale locals: unchanged generated layout.
- Ordinary inline helper separating task unwrapping from shape drawing:
  190-byte function, 20-byte frame.
- Word-sized helper dimensions with explicit signed fixed-point division,
  preserved here: the same 190-byte function and 20-byte frame.

No compiler flags, assembly, volatile storage, forced inlining, inert code,
or verification changes were used. The remaining issue is this bounded
source/code-generation mismatch; no permanent impossibility is asserted.
Native output and the final compiler assembly remain in address-private
scratch. Unmatched active source/report removed.
