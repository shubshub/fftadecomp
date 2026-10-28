# 08146DC8 — bounded natural C attempt

Complete target: `[0x08146DC8, 0x08146E52)`, 138 bytes / 63 reachable Thumb instructions. The retained candidate recovers the complete linked-list interval routine. Incoming arguments are unsigned halfword lower bound, upper bound, and flags. It walks the list at `data_03003C60 + 4`, checks node kind and required flags, destroys handles for contained/containing intervals, and otherwise trims an overlapping endpoint. Each handle passed to `func_08148498` is the return value from `func_0814873C(entry)`. Node traversal uses the pointer at offset 0x28.

The fixed native matcher (`agbcc -mthumb-interwork -O2`) exits 1 for the retained source:

```
compiled symbol is shorter than the indexed span: 134 < 138
```

This extent refusal occurs before native byte comparison or source plausibility checking. No exact match or native plausibility claim is made for the retained candidate.

The remaining code-generation gap concerns endpoint narrowing and register preservation. The ROM initially loads the first endpoint into r0 and copies it to r2, keeping the last endpoint in r1. It later emits three explicit halfword-narrowing pairs for the endpoint comparisons. The retained candidate loads the first endpoint directly into r2, keeps the last endpoint in r0, replaces the first endpoint's narrowing pair with a register copy, and reuses an already shifted last endpoint for its final comparison. Alignment around the middle literal pool also differs. The indexed extent and verifier were not changed.

Bounded attempts: ordinary halfword endpoint locals emitted 126 bytes; wider cached values with explicit halfword narrowing emitted 134 bytes; a naturally inlined interval-containment predicate emitted 172 bytes and passed source plausibility but did not match; full-width 16-bit fields emitted 126 bytes. The 134-byte complete candidate is retained. No assembly, artificial volatile accesses, forced inline, compiler changes, or inert operations were introduced. This result does not establish unmatchability.

The final native log and diagnostic assembly for the retained candidate remain in the batch's `08146DC8` scratch directory.
