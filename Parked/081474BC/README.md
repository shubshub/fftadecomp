# 081474BC — bounded natural C attempt

Target: complete indexed [0x081474BC, 0x081475A4), 232 bytes and 109 reachable instructions. Compiler: agbcc -mthumb-interwork -O2, unchanged native matcher and approved ROM.

The complete C recovers the seven arguments, clamps the inclusive palette endpoint to 511, extracts RGB555 channels, raises each component to at least three, transforms each color through 08148384, stores the result in 12-byte records at data_03003E68, and invokes 08146E54 with the original start and mode.

The final fresh native invocation exits 1: complete compiled extent 232 bytes, source plausible, bytes DIFFER, verdict NOT MATCHING. The native comparison reports 95/108 instructions identical and 220/232 bytes identical. No exact-match claim is made.

The principal remaining body difference is green extraction. Target uses mov r2,#248; lsl r2,#2; add r0,r2,#0; and r0,r1. This source uses mov r0,#248; lsl r0,#2; add r2,r0,#0; add r0,r1,#0; and r0,r2, adding one instruction. Subsequent relative branch/call and literal-load offsets consequently differ. The candidate also returns through pop {r0}; bx r0, while the target uses r1 and includes a final two-byte alignment word. Both complete symbols occupy 232 bytes.

Nine bounded native attempts tested direct conditional clamps with 32-bit and 16-bit channel locals; conditional-expression clamps with unsigned or signed 32-bit channels; unsigned 32-bit color with 16-bit channels; 16-bit color and channels; separate mask/shift assignments; and unsigned mask literals. The best full-span form is preserved here. The smaller forms compiled to 208, 216, or 228 bytes and failed the native short-symbol gate. The final sequential extraction form retains the best 220/232-byte result. No compiler flag changes, asm, pragmas, volatile, dummy operations, or steering were used.

The full native output and generated report are retained in the private address scratch directory. Unmatched source and report were removed from the private root's src and docs/match directories.
