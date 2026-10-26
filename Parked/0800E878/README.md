# 0800E878

Complete midpoint-circle span reconstruction, parked because two Thumb addition
encodings differ. The indexed target is [0x0800E878, 0x0800EA0C), 404 bytes and
197 reachable instructions. The retained candidate has the same complete ELF
symbol extent and instruction count.

Native verification with agbcc -mthumb-interwork -O2 exited 1: source plausible,
NOT MATCHING - bytes differ. Its aligned diff score was 195/197 instructions
and 400/404 bytes. There are exactly two instruction differences:

- At 0x0800E8FC and 0x0800E964 the target has `adds r0, r7, r0` (3818).
- At both locations the candidate has `adds r0, r0, r7` (c019).

Both instructions add the signed center row and circle offset. All other
instructions, the eight-byte frame, loop branches, stores, and both linked
0x02009160 literal words agree. The function initializes midpoint-circle
coordinates and a 16-bit error term, selects a half-circle, clips nonnegative
rows optionally to 159, and writes left/right halfword span endpoints.

Eleven native attempts tested natural signed coordinate widths, scoped row
indices, explicit 16-bit row interpretation, and arithmetic operand order.
Compiled extents were 296, 340, 388, 372, 372, 404, 404, 372, 312, 404, and
404 bytes. Scoped unsigned row indices with signed 32-bit working centers
restored the complete target control flow. Reversing the two C addition
operands did not change their emitted operand order. A signed 16-bit working
center row retained the full extent but exchanged r6/r7 allocations and
increased the differences. The retained source uses the best complete form.

Command, run from the game checkout:

```
env PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' python ../fftadecomp-kit/tools/match.py --root . 0x0800E878
```

No matching source or generated report remains in src/ or docs/match/.
