# 0800A420 — sum selected actor values

**Parked: byte-identical natural C, but the current verifier correctly cannot
discharge its nested callback and stack-buffer obligations.**

The source compiles with canonical agbcc `-mthumb-interwork -O2` to the full
112-byte ROM span `[0x0800A420,0x0800A490)`: 106 code bytes containing 50
reachable instructions, two zero alignment bytes, and the trailing literal
`0x00000101`. The three typed calls target `0x08096D7C`, `0x08099CDC`, and
`0x080C8298`. Source plausibility passes.

The function obtains a list into a 13-pointer local array, sums actor byte
`+0x101` when the byte predicate is false, compares the full integer sum with
`instruction[1]`, and conditionally advances the context halfword at `+2`.
Nonpositive counts skip the loop; a zero sum can still take the update.

The official verifier rejects the real nested callback path
`08099CDC -> 080C7CC0 -> 0814225C -> 0809ABE8 -> 080C7B74 -> 0814224C ->
0809AC20`. Independent execution confirms that a finite, well-formed 14-node
list writes the fourteenth pointer at local-frame offset 52 and returns with
saved `r8` corrupted. Thirteen nodes preserve the frame. No evidence currently
establishes a game-wide `count <= 13` invariant, so adding that assumption to
the verifier would be unsound.

The callback-table row at `0x0836D5E6` has script length 4 and Thumb pointer
`0x0800A421`; that length is unrelated to list capacity. Promotion requires a
sound, independently verified callback proof and cardinality invariant, not a
waiver of the current rejection.

The author and independent review evidence is retained outside the repository;
both reproduce the 112 exact bytes, the canonical rejection, the hostile
14-node overwrite, the metadata corrections, and text-only artifact checksums.
