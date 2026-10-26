# 08042774

Recovered complete selection, cancellation, cursor movement and page navigation handler.
Target: `[0x08042774, 0x08042B70)`, 1,020 bytes and 411 reachable instructions, including literal pools.

The retained source was checked with the default native matcher and fixed agbcc
`-mthumb-interwork -O2` flags. Native exit status was 1: source plausible, complete
ELF symbol 1,020 bytes, 402/411 instructions and 1,010/1,020 bytes identical.
It is not an exact match and earns no match credit.

The remaining nine instruction differences occupy `0x08042944..0x0804299E` in
the down-page calculation. The target holds the visible count in r3 and the top
row in r5; the candidate uses r5 and r3 respectively. The affected count/top
loads, address addition, page arithmetic, comparison and final subtraction
account for ten differing bytes. The remaining control flow, selection stores,
settings copy, cursor paths, helper calls, literal words and symbol extent match.

Natural forms tried included a typed cursor member, explicit cursor pointers,
a typed view over cursor storage, separate signed selection promotion, narrow
and promoted page arithmetic locals, scoped and shared page locals, direct
visible-count field reads, a mutable top-row pointer, named next-page/end
intermediates, and both addition operand orders. The pointer and shared-local
forms changed broader code generation; none closed the remaining allocation gap.
No custom flags, assembly, volatile RAM accesses or compiler directives were used.
This records a bounded unresolved source-form gap under the fixed flags, not a
claim that matching is impossible.

The exact native output and source-bound report remain in the private address
scratch directory as `last-native-output.txt` and `last-native-report.md`.
