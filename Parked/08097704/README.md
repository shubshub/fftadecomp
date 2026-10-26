# 08097704 — Parked

Target: 0x08097704..0x0809779C, 152 bytes / 69 reachable instructions.

The complete C candidate updates two handles at rows 1 and 2. Owner attribute 0x28 bit 1 suppresses the signed displacement. Each update uses the corresponding byte from data_08394352, the resource at context offset 0x34, and the renderer at offset 0x40. A result other than -1 replaces the handle and updates its palette; failure destroys and clears a previously nonzero handle.

The final default native matcher invocation exited 1: `compiled symbol is shorter than the indexed span: 144 < 152`. The extent guard stopped before byte comparison and source plausibility assessment. No exact-match credit is claimed.

The remaining gap is the predicate's Boolean representation. The target branches to materialize a separate 0/1 result and then tests it before clearing the displacement. The retained conditional-expression predicate instead becomes a bit extraction followed by one test, saving four Thumb instructions / eight bytes. Diagnostic compiler output otherwise follows the captured handle-update and cleanup sequence, including the exclusive row bound of three and signed displacement addition.

Bounded natural attempts used a comparison predicate, explicit return branches, an assigned Boolean result, an unsigned-byte predicate result, and the retained conditional expression. They did not recover the target's separate Boolean materialization under fixed agbcc `-mthumb-interwork -O2`.

The raw matcher output and captured target remain in the private address scratch directory outside the matching root. Unmatched active source and report have been cleared.
