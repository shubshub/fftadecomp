# 080B4D70 — select an object by tile coordinates

Complete target: `0x080B4D70..0x080B4DE8`, 120 bytes / 60 reachable instructions. The natural C searches the pointer list using signed fixed-point coordinates shifted right by five, stores the found index, and wraps the signed selected byte against the signed count.

The preserved candidate was freshly tested with the approved ROM and fixed agbcc `-mthumb-interwork -O2`. Native matcher exit 1: source plausible; complete 120-byte ELF symbol; closed leaf CFG; no relocations; 101/120 identical bytes and 43/60 identical instructions. This is not a match.

Remaining difference is count-pointer and loop-index lifetime/allocation: target keeps index in r3 and count address in r4, then derives a second count address in r3 after storing the index. Candidate keeps index in r4 and count address in r3, then recomputes the count address at the loop bottom. Consequently two conditional branches have different destinations, while the fixed-point comparisons and index-normalization behavior are recovered.

Tested direct field accesses with break and early return (both 126 bytes); local selected/count byte pointers (120 bytes); a loop-level count pointer with direct normalization fields (116 bytes, rejected at the extent gate, no fresh byte verdict); moving index initialization before that pointer (116 bytes); an inner count pointer introduced after the selected store (preserved 120-byte candidate); and separate loop/normalization count pointers (124 bytes). No flags were changed and no assembly, volatile memory, padding, or dead code were introduced. The bounded attempt stops with the best complete 120-byte candidate. Unmatched active source/report are removed; private address scratch retains the last native report.
