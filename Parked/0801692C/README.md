# 0801692C — rectangle-fill counter and register-allocation gap

The complete indexed target is 0x0801692C..0x08016A08: 220 bytes and 110 reachable Thumb instructions, with no literal pool or calls. The preserved candidate compiled with the fixed agbcc `-mthumb-interwork -O2` profile to 214 bytes / 107 Thumb instructions. The final native invocation exited 1 at `compiled symbol is shorter than the indexed span: 214 < 220`; source plausibility was not evaluated for this candidate.

The reconstructed operation requires width and height greater than one, writes four tile-map corners with 0x400/0x800/0xC00 flip bits, applies the palette to independent corner/fill tile values, fills the non-corner top/bottom cells, and fills the intervening rows. The fourth incoming argument is unused in the target. Right and bottom offsets are narrowed to 16 bits as observed.

The remaining compiled structure differs in counter lifetimes and allocation. The target keeps width in r7, the initial height/remaining-row value in ip, and later runs the outer row counter in r0. The preserved candidate keeps width in ip and the remaining-row counter in r7. The target advances the top pointer once after the paired border loop and has a separate row-loop advance; the compiler shares that advance in a common block and adds a branch from the paired border loop. The target also forms right/bottom addresses with different commutative operand ordering. These are actual whole-function instruction differences, not an exact match with only padding omitted.

Three natural forms were tested: direct indexed corners with a post-decrement row loop (226 bytes, native NOT MATCHING after extent/plausibility checks); explicit right-corner reuse with a separate row-count for-loop (210 bytes, extent refusal); and the preserved explicit row-count while-loop form (214 bytes, extent refusal). No artificial scheduling, asm, volatile accesses, forced inline or compiler-profile changes were used.

The unmatched active source/report were removed. This Parked candidate earns no match credit.
