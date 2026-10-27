# 0812DAEC — bounded natural C attempt

Complete indexed target: `[0x0812DAEC, 0x0812DB5A)`, 110 bytes / 52 reachable Thumb instructions. The retained source recovers the entire function: absolute difference between the two bytes at offset 0xF8, the low-byte state check on the second object, the required difference of two, five selectors 0x1D through 0x21, and low-byte validation of every nonzero selected entry. Entry identifiers narrow to u16 for the validator, while its third incoming context word is passed unchanged. Any failed check returns zero; success returns 100.

The fixed native matcher (`agbcc -mthumb-interwork -O2`) exits 1 on the retained candidate:

```
compiled symbol is shorter than the indexed span: 100 < 110
```

This is an extent-gate refusal before native byte comparison and source plausibility checking. No native match or plausibility claim is made.

The direct candidate uses r4 for the selector induction variable, r6 for the slot counter, and r7 for context. The ROM instead holds each returned entry in r4, uses r6/r7 for selector/counter, and preserves context in r8. The missing entry-result copy accounts for two bytes; the additional high-register save/restore instructions account for eight bytes. The direct candidate passes the same narrowed entry value to the validator and recovers every target branch and call, but does not reproduce that register lifetime.

Bounded natural formulations included combined versus nested entry checks, a function-scope entry temporary, and explicit identifier/result temporaries. These all emitted 100 bytes. A genuine naturally inlined slot-validation helper emitted 104 bytes by adding null-entry success branches, while still omitting the target's r8 preservation, so the simpler direct candidate is retained. No assembly, artificial volatile accesses, dead expressions, forced inline, or compiler flag changes were introduced. The result does not prove unmatchability.

The final native log is retained in the batch's `0812DAEC/match-current.log`.
