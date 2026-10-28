# 0814731C — bounded natural C attempt

The complete target is [0x0814731C, 0x081473E4): 200 bytes and 92 reachable instructions. The fixed compiler is agbcc with -mthumb-interwork -O2.

The recovered function clamps the inclusive palette endpoint to 511, raises each RGB555 channel to at least three, writes the adjusted source color, transforms that color with the same amount for all three channels, stores it in a 12-byte palette record, and returns the result of 08146E54. The original start, clamped endpoint, and mode reach that final call.

The preserved complete candidate compiles to 204 bytes. The fresh native matcher exits 1 with source plausible and verdict NOT MATCHING. Its aligned comparison prints 78/91 instructions and 190/204 bytes identical; those are not complete indexed-target match counts, since this candidate extends four bytes beyond the 200-byte target.

The remaining instruction difference is green extraction. The target constructs 0x3E0 in r2, copies r2 into r0, and ANDs r0 with the color in r1. The candidate constructs that mask in r0, copies it to r2, copies the color into r0, and ANDs r0 with r2. This adds one 16-bit move. Subsequent PC-relative loads, calls, and branch displacements shift; a further two-byte alignment word precedes the trailing literal pool. The remaining operation order, channel clamps, source-color store/reload, transformed-color store, loop, and result-preserving return are recovered.

Three natural forms were tested. Direct extraction with 32-bit channel locals produced a 196-byte symbol and failed the short-symbol gate. Separate mask/shift operations with 16-bit color and channel locals produced the preserved 204-byte shape. Reversing the green-mask operands produced identical compiled bytes and did not resolve the gap. No compiler flags, asm, pragmas, volatile accesses, dummy operations, or dead code were introduced. The unmatched source and generated report were removed from the private root's src and docs/match directories.
