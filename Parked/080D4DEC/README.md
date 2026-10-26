# 080D4DEC

Unmatched complete natural-C reconstruction of the command-driven timed-effect
state machine. Target: `0x080D4DEC..0x080D5128`, 828 bytes and 404 reachable
instructions. The retained source was freshly tested with the approved ROM,
unchanged native matcher, and agbcc `-mthumb-interwork -O2`.

Native result: exit 1, source plausible, compiled complete symbol 832 bytes,
not byte-identical. Both bodies use a 76-byte stack frame. Native alignment
score was 650/832 bytes and 243/398 decoded instructions; these are the native
diff scores, not same-offset byte equality or the captured target instruction
count. Typed direct-call linking and return verification passed.

The remaining gap is register allocation and its resulting instructions. In
state 0x100 the target retains accumulated flags in SB and the loop index in
SL. The candidate spills them to SP+0x1C and SP+0x20, keeps the mask 4 in IP,
and assigns coordinate/mode/transform temporaries to different registers.
The target reloads the mask locally instead. The candidate also emits a
separate command-state increment store rather than sharing the target's final
halfword store with state 0x101. These differences propagate through both
spawn paths and their branch displacements; matching extent alone would not
close the gap.

Bounded natural forms tested: a shared inline spawn helper, signed word
coordinate temporaries, explicit low/high-byte little-endian decoding,
helper parameters passed as scalar rendering inputs, a semantic little-endian
reader, and the retained direct duplicated spawn blocks. Signed word locals
recovered the target's early signed halfword loads. The inline and direct
forms both reached 832 bytes with the same remaining allocation differences;
the reader form was 838 bytes. No compiler flags, assembly, volatile RAM,
forced inlining, dead code, or unrelated files were changed.
