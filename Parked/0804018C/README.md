# 0804018C — unresolved register allocation

Target: `[0x0804018C, 0x080401F2)`, 102 bytes, 51 reachable instructions.
The retained complete natural C candidate also emits a 102-byte ELF symbol
with fixed agbcc `-mthumb-interwork -O2`.

The final native matcher invocation exited 1 and reported:

```
extent    102 bytes (complete ELF symbol; closed leaf CFG; no relocations)
bytes   DIFFER
source  plausible
verdict NOT MATCHING - bytes differ
39/51 instructions identical (90/102 bytes)
```

The instruction/byte counts in the last line are the matcher's aligned diff
score, not a claim of same-offset byte equality. No exact-match credit is
claimed.

Recovered behavior: initialize a wrapping 16-bit tile value from the palette
byte shifted by 12 plus the first-tile halfword. For each block-height unit,
write block-width tile pairs into two consecutive map rows: one tile at the
current column, then the next tile at the current column plus the width read
from the block. Advance the destination by two rows after each iteration.
The width field is reloaded after the first halfword store, preserving its
potential byte aliasing with the destination.

The remaining differences are register allocations. The candidate keeps the
tile in r5 and inner column counter in r4, while the target uses r4 and r5.
The candidate keeps cached width in ip and the outer row counter in r8;
the target uses r8 and ip. The native aligned diff identifies the resulting
12 differing instructions. Control flow, symbol size, and tile operations
are otherwise recovered; this is not a proof of unmatchability.

Natural countdown-loop forms emitted 98 or 100 bytes; the retained counted
outer loop with guarded inner loop emits the target's complete 102 bytes.
A genuine naturally inline tile-pair helper emitted 100 bytes and was not
retained. The restored 102-byte candidate was freshly checked before parking.

The complete captured target and final native output remain in the sibling
address scratch directory as `target-disassembly.md` and `match-current.log`.
The unmatched active source and report were removed. No shared metadata,
headers, toolkit, main-game files, or other addresses were changed.
