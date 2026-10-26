# 08068158 — not matched

Target: complete [0x08068158, 0x080681C4), 108 bytes / 51 reachable instructions.
The retained natural C compiles with fixed agbcc -mthumb-interwork -O2 to a
complete 100-byte symbol / 47 instructions. The final native matcher exits 1:
`compiled symbol is shorter than the indexed span: 100 < 108`.

The recovered operation writes four successive tiles per menu entry into two
tilemap rows and selects palette 15 or 9 using the signed selected-entry byte.
The retained tile-number narrowing, increments and stores reproduce the target
arithmetic. Remaining differences are the rotated loop (one initial jump to a
shared end-of-loop condition rather than a separate initial guard), opposite
row-pointer registers, and palette-shift ordering relative to the first tile
increment. These change the complete extent and literal-pool placement.

Tested ordinary two-row pointer and single-map/32-entry-stride forms; explicit
pointer increments; constant offsets versus successive tile increments;
signed-word and halfword tile/palette locals; conditional assignment and
ternary palette selection; and a guarded do-loop. The pointer-increment form
also reached 108 bytes but required an extra saved register and differed in
pointer, store and loop instructions. Other tested complete extents were 98,
100, 102 and 104 bytes. No compiler flags were changed and no assembly,
volatile accesses or inert code were introduced. No exact match is claimed.
