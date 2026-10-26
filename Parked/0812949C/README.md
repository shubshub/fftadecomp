# 0x0812949C — register allocation differs

Target/indexed extent: `[0x0812949C, 0x081295C8)`, 300 bytes, 127 instructions. Compiled complete ELF symbol: 300 bytes. Fixed compiler: `agbcc -mthumb-interwork -O2`.

The native matcher exits 1 with plausible source. Its aligned diff score is 111/127 instructions and 273/300 bytes; this is not a count of equal bytes at identical offsets.

The target holds the incoming state pointer in r8 and the allocated icon buffer in r7; this candidate reverses those assignments. The difference propagates into the initial `state + 0x3a6` address, state and icon arguments, and both text-call address calculations. Control flow, literal placement, icon selection, palette arithmetic, tilemap writes, call targets, and final return otherwise align.

Six native invocations tried grouped/explicit switch cases, equivalent if/else selection, separate versus reused palette/index locals, ordinary declaration scopes, u16/u32 index widths, and byte/halfword tile-buffer pointer arithmetic. The final natural pointer/layout check emitted unchanged bytes. No forced registers, assembly, volatile, pragmas, inert code, or compiler-flag changes were used. This is not the unused-load-before-store family.

The best candidate is preserved unchanged here. The owned unmatched source and native report were removed from `src/0812949C.c` and `docs/match/0812949C.md`. The final failed native report and full target disassembly remain in the task-private directory.
