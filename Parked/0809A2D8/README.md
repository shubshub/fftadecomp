# 0809A2D8 — unmatched

Target: complete `[0x0809A2D8, 0x0809A302)`, 42 bytes and 19 reachable instructions.

The complete candidate normalizes an unsigned 16-bit index and signed 8-bit value, calls `func_080975DC(context, index, value, 1)`, then calls `func_08097704(context, index, value)`.

The final native matcher invocation exits 1: source plausible, complete extent 42 bytes, 35/42 bytes and 12/19 instructions identical. The remaining difference is a consistent allocation swap: target context is saved in r6 and the signed byte value in r4; compiled context is in r4 and value in r6. The index uses r5 in both. Operation order, narrowing instructions, calls, and epilogue otherwise agree.

Bounded tested forms, all producing the same native bytes:

- Narrow wrapper arguments and narrow callee argument declarations.
- A full-width declaration for the second callee's integer arguments; the first callee's mode declaration was aligned with the existing s32 declaration.
- Full-width wrapper arguments with explicit u16/s8 normalization locals, retained here with narrow callee declarations.

No assembly, padding, volatile access, register variables, or compiler flag changes were used. The unmatched active source/report were removed; the final generated report remains in the private address scratch as `last-native-report.md`.
