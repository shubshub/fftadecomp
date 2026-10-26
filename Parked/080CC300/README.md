# 080CC300

The complete candidate compacts a 20-byte list by filling each empty slot
with the next nonzero slot and clearing the old slot. Both loop indices
are unsigned bytes, matching the target's narrowing and bounds checks.

Fixed native matcher: exit 1, plausible source, exact 72-byte complete ELF
extent, supported closed leaf CFG. Byte comparison matches 62/72 bytes and
26/34 instructions against the complete 72-byte / 34-instruction target.

Remaining source-generation gap:

- At 080CC306/080CC308 the target forms the outer slot address in r0 and
  loads through r0; the candidate retains that address in r2.
- The target keeps the outer increment in r5; the candidate uses r4.
- At 080CC318/080CC31A the target reloads the real array base into r4 from
  the same literal and recomputes the destination in r3. The candidate copies
  the already loaded base r7 into r5 and the retained destination r2 into r3.
- The inner source address and final outer increment consequently use the
  opposite saved index/base registers. Loop control, move/clear operations,
  literal placement, complete size, and return structure otherwise agree.

Tested the direct nested loops, an entirely inlined helper to fill one empty
slot, and that helper plus an inlined byte-slot reader. All three emitted
identical complete bytes. The simple direct-loop source was restored and
freshly matched to confirm the stated result. Flags remained unchanged;
no steering or unsupported operations were introduced.

The unmatched active source/report were removed. Native result and report
remain in private address scratch. This is not an exact match.
