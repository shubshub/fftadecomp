# 08026D44

Target: complete indexed Thumb body `0x08026D44..0x08026F9C`, 600 bytes and 269 reachable instructions.

The retained natural C builds with the required agbcc `-mthumb-interwork -O2` flags. Its complete ELF symbol is 600 bytes; the emitted assembler contains 266 instructions. The final native matcher exits 1, reports source plausible and **NOT MATCHING - bytes differ**, and gives an aligned diff score of 170/255 instructions and 517/600 bytes. Those scores are the native alignment metric, not same-offset byte equality or reachable-instruction counts.

The reconstruction filters eight-byte menu entries, records selected indices, applies unit/resource eligibility and cost checks, updates severity and maximum text width, and writes the result count. Resource records have a 28-byte stride. All named literals use the applied data bindings.

Remaining differences:

- The target keeps the loop index in r10, resource pointer in r8, and menu-entry pointer in r5. The retained compiler output uses r8, r10, and r4 respectively; the cached battle-global address consequently occupies different registers.
- The target places the category-31 rejection call to `func_080CCD50` in the later block at `0x08026F36` and branches back to the ordinary checks on success. The compiler emits that call immediately after the initial category-mode query. This changes branch encodings, literal-pool locations, and allocation lifetimes.
- The target uses a short unsigned-low branch followed by a long branch around the insufficient-points path. The compiler emits the inverse unsigned-high-or-same branch directly to the later join.
- Both functions use an eight-byte fixed frame, but the target instruction stream and literal-pool placement remain different despite equal total symbol extents.

Bounded attempts covered the direct rejection chain, a positive eligibility wrapper, a materialized eligibility result, a conditional expression, a shared rejection label, and an assigned query-result condition. Counter initialization was moved after the severity reset, which reproduced the initial store/load ordering. Keeping narrowed cost results in a word local removed a redundant register copy. The alternative wrapper/conditional/label forms produced 596-byte symbols and failed the native complete-extent gate. The retained 600-byte materialized-result form had the best complete native diff score and passed plausibility. No flags, assembly, volatile accesses, pragmas, helpers, or shared files were changed.
