# 080270CC

Complete recovered ability-list update for 0x080270CC..0x08027208, including all branches and literal pools. Target and preserved candidate are both 316 bytes / 142 reachable instructions. The fixed native command with agbcc `-mthumb-interwork -O2` exited 1: source plausible, bytes differ. This is not an exact match.

The preserved candidate has 292/316 equal bytes at the same offsets. The native aligned instruction score is 118/142. Exactly 24 byte positions differ, all from the R4/R5 register assignment: the target keeps the list in R4 and the entry pointer (later the context-pointer address) in R5; the candidate uses R5 and R4 respectively. Instruction order, branch destinations and literal-pool positions/values agree. Differing relative byte offsets: 0x00E, 0x016, 0x018, 0x01E, 0x028, 0x02A, 0x02C, 0x036, 0x042, 0x06E, 0x08E, 0x096, 0x09E, 0x0B3, 0x0B4, 0x0C2, 0x0CA, 0x0D2, 0x0D4, 0x100, 0x106, 0x10C, 0x112, 0x120.

Natural forms tested under the fixed flags:

- Byte-sized cost locals produced an extra move before the normal resource comparison; promoting the returned byte once to `u32` removed that move and produced the preserved 316-byte/142-instruction form.
- Hoisting entry/info declarations to function scope left the same R4/R5 residual.
- Early `continue` filters for entry kind/category left the same residual.
- Direct repeated `list->entries[index]` accesses produced a broader difference (139 compiled instructions; native aligned score 95/139), so the explicit entry-pointer form was restored and freshly checked.

The preserved source is the best tested natural candidate. No compiler options, inline assembly, volatile accesses, forced inlining or inert code were used. This bounded attempt establishes the remaining fixed-profile register-allocation difference, not permanent impossibility. Native output and the source-bound nonmatching report remain in the private address scratch directory; unmatched active source/report were removed.
