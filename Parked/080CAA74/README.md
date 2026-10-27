# 080CAA74 — recovered, not matched

Target: complete `[0x080CAA74, 0x080CAB22)`, 174 bytes and 73 reachable instructions.

The function counts occupied four-byte records in the 64-entry table at state offset `0x968`. It returns zero for an empty table. Otherwise it shifts later records over each empty slot through the existing copy callback, clears the newly vacated tail record through the existing clear callback, and returns the original occupied count. The reconstructed record only names the tested occupied byte; the other three bytes remain unknown.

Four bounded natural candidates were tested with the fixed agbcc `-mthumb-interwork -O2` and native `canonical-thunks-v1` matcher. The initial maintained-pointer and indexed-loop forms generated a different complete extent. Factoring the meaningful remove-empty-record operation into a naturally inlined helper produced the correct complete extent; the final pointer-counting form retained it. The final ELF contains only `func_080CAA74`, exactly 174 bytes, with 73 emitted instructions. Its undefined symbols are the two canonical call thunks and the three genuine mapped global symbols.

The last native invocation exited 1 with `inert-spin complete body differs from ROM`. This is the complete-byte gate used by the canonical-thunk path, before source plausibility; no native plausible or match verdict is claimed. The final source remains a complete natural recovery, without assembly, volatile accesses, compiler-option changes, artificial expressions or invented aliases.

Remaining differences: the target counting loop uses r1 for the record pointer and r6 for the countdown, whereas the final candidate uses r2 and r1. The target initializes r8 via r0 and the candidate via r1. In the compaction loop the target uses r6 for the index and r7 for the next-record pointer; the candidate assigns those roles to r7 and r6. The base, occupied count, hole count, constant 64, destination pointer, copy/clear sequence and arithmetic are recovered, but the register encodings are not byte-identical. Equal byte/instruction counts are not an equality score.

The exact tested source is preserved here. Active unmatched source/report were removed. The captured target and last native log remain in the batch's `080CAA74` scratch directory. No shared metadata, headers or toolkit files were changed.
