# 08050734 recovered C

The complete indexed target spans `0x08050734..0x08050844`: 272 bytes and 116 reachable instructions. The recovered function handles three icon-source kinds, allocates a 128-byte temporary image, renders the appropriate resource, copies it to the output, frees the temporary buffer, and advances the output by 128 bytes.

The retained source passed native plausibility at fixed `agbcc -mthumb-interwork -O2`. The last default native matcher exited 1: compiled size 280 bytes versus the 272-byte target; its alignment report records 232/280 bytes and 84/113 instructions identical. The original target's reachable-instruction count is 116; the report's alignment denominator is not that target inventory count.

The packed ten-bit resource reads, category adjustment and override, switch dispatch, prologue register allocation, table-record stride and category-field access, allocator/copy/free calls and arguments, and output advancement are recovered. The remaining differences are cleanup placement/sharing and the final kind's entry-address evaluation. The compiler shares the trailing copy/free/advance sequence between kinds 3 and 5, while the target gives kind 3 its own sequence and shares the renderer/copy/free/advance sequence between kinds 4 and 5. It also adds the final entry index before the `0x424` displacement, while the target adds that displacement before the index. These change branches and literal-pool placement and leave eight extra compiled bytes.

Natural forms tried:

- Raw byte extraction versus the packed ten-bit resource record; the packed record reproduces the target resource loads exactly and is retained.
- A typed output parameter versus a generic output pointer converted locally; the generic callback-style output gives the target prologue and is retained.
- Expression narrowing versus a byte local followed by the category addition; the separate byte assignment reproduces the target shift/add sequence and is retained.
- Shared and case-local allocation buffers and 16/32-bit icon locals, direct/conditional icon selection, explicit entry-offset calculation, and a common post-switch icon-render path. These produced 252..296-byte candidates with different cleanup sharing or additional register differences. The best source tested is retained.

The exact last native source-bound report is retained privately as `08050734/last-native-report.md` in this matching batch. Unmatched `src/08050734.c` and `docs/match/08050734.md` have been removed. This bounded attempt does not establish permanent impossibility at the fixed flags. No assembly, volatile storage, custom flags, or compiler-steering constructs were used.
