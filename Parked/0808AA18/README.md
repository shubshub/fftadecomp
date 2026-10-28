# 0808AA18

Bounded natural-C attempt; not a match.

Target: complete `[0x0808AA18, 0x0808AAF0)`, 216 bytes including literal pools and 101 reachable Thumb instructions. The preserved fourth candidate has a complete 216-byte ELF symbol and 101 decoded instructions. Native fixed agbcc `-mthumb-interwork -O2` result: exit 1, source plausible, 171/216 identical bytes and 71/101 identical instructions. No match credit.

Recovered behavior: if the first rectangle buffer exists, compute the signed rectangle origin and dimensions, copy each row from both 32-halfword-stride grids into corresponding packed buffers using `func_0814186C`, then copy the packed rectangle bounds to the saved bounds field. All offsets follow the 0x4C-byte record.

Remaining gap: the target holds the global array base in r12, the indexed coordinate-record base in r5, the two grid pointers in r10/r9, the first packed buffer in r8, the second packed buffer in r6, row byte width in r5, and masked copy count in r7. The preserved candidate instead uses r5/r6 for the initial bases, r10/r8 for grid pointers, r7/r5 for packed buffers, r6 for byte width, and r9 for the masked count, requiring extra high-register transfers. It also computes the doubled row width before the zero-height test; the target computes it after that test. The final saved-bounds load/store sequence matches. No unused-load-before-store issue was identified.

Five natural forms tested: initial halfword buffer local before the null check (216 bytes, 170/216 identical bytes); null check followed by buffer locals (220 bytes); named array-base and count locals (184 bytes, rejected as shorter than indexed extent); byte-addressed packed buffers with explicit row byte width (preserved, 216 bytes, 171/216 identical bytes); and halfword buffers with named copy count (220 bytes). No compiler flags or metadata changed. No assembly, volatile accesses, or pragmas were used.

Unmatched active source and generated report were removed. Full target disassembly remains in the private address scratch directory.
