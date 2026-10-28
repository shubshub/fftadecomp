# 0804E358 — not matching

Target: 0x0804E358..0x0804E3BA, 98 bytes and 41 reachable instructions.
Compiler: fixed agbcc -mthumb-interwork -O2.

The retained C selects a four-byte window record at state offset 0x53C,
preserves the target's initial call to func_08050E74, then obtains the byte
count from func_08050E74 for index 4 or func_08050E84 otherwise. It adjusts
the window when its first position plus the visible limit of six exceeds
that count. The length comparison preserves the target's byte truncation,
and the first position is decremented only when nonzero.

Fresh default native matching exits 1 before byte comparison or source
plausibility: "compiled symbol is shorter than the indexed span: 96 < 98".
No native byte-identical or plausibility result is claimed.

Fixed-flag assembly diagnostics show that the target materializes the
visible limit with mov r4, #6 and compares the count against that register.
The compiler folds the same local limit into cmp count, #6, removing the
two-byte move. Its count and first-position registers consequently differ
from the target. The observed call sequence and window operations remain
present in the diagnostic body.

Both the direct body with a named byte limit and an ordinary naturally
inlined window-adjustment helper taking that limit were tried. Both produce
a 96-byte body with the same constant folding. The simple direct form was
restored and freshly tested again. Compiler options were unchanged; no
artificial control flow or register constraints were added.

The native refusal remains only in private address scratch. No unmatched
active source or report remains.
