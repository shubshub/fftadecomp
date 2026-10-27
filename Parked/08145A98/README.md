# 08145A98 — bounded natural C attempt

Complete indexed target: `[0x08145A98, 0x08145B4C)`, 180 bytes / 90 reachable Thumb instructions. The retained source recovers the entire routine: conditional volume and stereo-pan calculation, modulation, pan clamping, signed pitch accumulation, key/pitch byte stores, and update-flag clearing. The first player argument is unused; the second argument is the audio track.

The fixed native matcher (`agbcc -mthumb-interwork -O2`) exits 1 with:

```
compiled symbol is shorter than the indexed span: 178 < 180
```

The retained candidate emits 178 bytes / 89 instructions. This is an extent-gate refusal before byte comparison or source plausibility checking; no native plausibility or match claim is made.

The ROM loads the volume-scale byte into r3, loads volume into r1, then copies r3 to r0 before multiplication. The retained candidate loads scale directly into r0 and omits that two-byte copy. It also schedules the initial flag load before the mask constant, and assigns the bend/range/tune operands to different temporary registers during pitch accumulation. The remaining arithmetic stages, pan bounds, result stores, and final flag clearing are recovered.

Bounded attempts covered the initial promoted arithmetic, explicitly unsigned volume multiplication and shifts, a combined pitch expression with a separate bend product, and function-scope staged arithmetic. All compiled to 178 bytes. The initial signed volume shift was corrected to the target's unsigned shift. Ordinary intermediate variables did not reproduce the remaining copy and operand scheduling. No assembly, artificial volatile reads, forced inline, compiler-option changes, or inert expressions were added.

Native log and private compiler diagnostic assembly are retained in the batch's `08145A98` scratch directory. Further recovery would need a justified natural arithmetic/type formulation; this result does not prove unmatchability.
