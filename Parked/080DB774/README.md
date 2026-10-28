# 080DB774 — Parked

The complete indexed target spans 0x080DB774..0x080DB838: 196 bytes and 87 reachable Thumb instructions, including its internal literal pool and alignment. The reconstruction preserves all states: copying initial settings and delay, waiting for the countdown, selecting and copying a 16-color palette, starting the operation with its recovered arguments, polling its handle, and restoring palette 15 on completion. The zero-duration path also preserves the observed state write followed by continued processing.

The final canonical native invocation exited 1 with a complete 196-byte ELF symbol and `source plausible`, but `NOT MATCHING - bytes differ`. Its aligned comparison reports 86/87 instructions and 194/196 bytes identical. A direct same-offset comparison of the emitted target/got bytes gives 192/196 identical bytes.

Only two adjacent halfwords differ. At 0x080DB7DA the target executes `lsrs r0, r0, #0x13`, then at 0x080DB7DC loads the palette base with `ldr r4, [pc, #0x30]`. The candidate loads that same base at 0x080DB7DA using `ldr r4, [pc, #0x34]`, then executes the shift at 0x080DB7DC. Both loads resolve to the same internal literal at 0x080DB810. Every other same-offset byte is identical. The remaining gap is the order of the palette-base load and the final source-index shift.

Bounded natural attempts covered an initial direct switch, a local settings pointer to preserve the recovered single settings read, a source-offset local, explicit narrowing of a word-return declaration, and a naturally inlined helper for the repeated 16-color palette lookup. After the settings-pointer correction, the latter forms retained the same ordering gap. The simpler direct indexed-palette form was restored and freshly retested. No assembly, flags, volatile accesses, forced inlining or steering constructs were used; the preserved candidate has no local helper.

Final native output and the generated comparison report are retained in sibling address scratch as `native-output.txt` and `native-report.md`. The unmatched active source and report have been removed.
