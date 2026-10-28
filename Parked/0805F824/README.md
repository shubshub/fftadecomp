# 0805F824

Indexed full target: `[0x0805F824, 0x0805FA4C)`, 552 bytes / 248 reachable instructions.

The retained complete natural C passes source plausibility. Its latest native invocation exits 1 and verifies a complete 558-byte ELF symbol with no relocations, six bytes longer than the indexed target. The generated comparison reports 506/558 bytes and 194/246 instructions identical. Those native comparison denominators include the oversized compiled span and must not be represented as the indexed 552-byte / 248-instruction target counts.

The unresolved differences center on the reverse item-availability scan for mode 5. The target walks an item-pointer address backward by four bytes while retaining its remaining count in a separate register. The retained indexed C scan keeps the item-array base and a decreasing integer array index separately. That additional live value also causes the compiler to retain the cursor in r10 and save/restore a third high register; the target saves only r8 and r9. These differences alter the register allocation and following branch/literal offsets. The target's forward scan, signed cursor wrapping, preview selection and redraw behavior are all represented in the complete source.

Bounded natural attempts covered the direct indexed reverse scan, a separate array-index offset, pointer traversal in for and do/while loops, and a shared scan counter. Pointer traversal produced a 548-byte symbol, with different loop entry/address folding and register allocation; the other indexed variant produced 570 bytes. The retained source has the best completed native comparison among the tested full-span candidates. No assembly, fixed registers, volatile RAM, compiler barriers, dead code or artificial scheduling was used.

Latest raw native output and report are retained in the private address scratch directory as `native-output.txt` and `last-native-report.md`. Unmatched private `src/0805F824.c` and `docs/match/0805F824.md` have been removed.
