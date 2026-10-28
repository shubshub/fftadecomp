# 0805033C — Parked

Target: 0x0805033C..0x08050392, 86 bytes / 40 reachable instructions.

The recovered function reads the state pointer from its first argument and a
halfword button mask from its second. It returns the selection byte at state
+0x562 unchanged when the mode byte at +0x560 is 0x10 and the phase byte at
+0x563 is 2. Otherwise bit 0x10 selects increment or decrement with wrapping
between 0 and 5. The state is represented with packed byte fields.

Fresh native matching with fixed agbcc -mthumb-interwork -O2 exits 1.
The retained candidate produces a complete 86-byte ELF function with closed
leaf CFG and no relocations. Native plausibility passes; bytes differ.
The native aligned comparison reports 21/41 compiled instructions identical
and 67/86 identical bytes. This is not match credit.

The remaining difference is compiler representation: the ROM retains the
limit 5 in a saved register, while the candidate folds it to an immediate.
The candidate also emits a final byte narrowing, changes the saved-register
set, and consequently changes branch and literal-pool placement. A direct
wrap body and a guarded helper assignment produced shorter 84-byte symbols;
using a byte-sized helper limit with a word-valued return produced 82 bytes
and stopped at the extent gate. No byte or plausibility result is claimed
for those shorter builds. The retained helper is naturally inlined by O2;
only the target function is emitted.

The complete retained candidate was restored and freshly checked. Its
native differing report is preserved privately in the address scratch as
native-not-matching.md; no ROM-derived instruction diff is included here.
No flags, assembly, volatile accesses, forced inlining, or artificial
conditions were introduced. Active unmatched source and report were removed.
