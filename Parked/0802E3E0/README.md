# 0802E3E0: unresolved transfer setup code generation

The complete indexed target is `[0x0802E3E0, 0x0802E520)`: 320 bytes and 132 reachable instructions. The candidate implements both row transfers, the conditional row update, the cursor increment and termination test, and the closing transfer. Native source plausibility is accepted, but byte identity is unresolved; this is not a claim of unmatchability.

The fixed native matcher (`agbcc -mthumb-interwork -O2`, approved ROM referenced directly) exits 1. The compiled ELF symbol is the complete 320 bytes. The report's instruction alignment is 100/126 instructions and 281/320 bytes. A direct same-offset comparison of its complete byte strings differs in 133 bytes across 76 halfwords; the larger count reflects shifted instruction placement.

The principal remaining difference is register retention across calls: the compiler retains the address of `data_0200F444` and the current source pointer, whereas the target retains the shared two-row transfer count and reloads the global's address. This also changes the registers holding the base row and cursor-field offset. Consequent instruction placement differs in the row-source calculation, repeated transfer arguments, and closing-transfer setup/epilogue. The cursor increment is part of the termination comparison, preserving the target's use of the incremented value despite reloading the global pointer.

Natural pointer and integer address types, separate map-index locals, shared transfer-dimension locals, and distinct versus reused transfer-source locals were tested. The closest tested complete form is retained. The extended transfer call uses the existing callee's integer source/destination address parameters. No assembly, volatile accesses, pragmas, compiler flag changes, inert code, or artificial register constraints were used. No runtime-helper or metadata extension is required.

Frozen native report: `/home/user/.codex-work/ffta-ulw/audio-following-v81-matching/0802E3E0/native-match.md`.

Main `src/0802E3E0.c` and `docs/match/0802E3E0.md` are absent. The reservation release remains with root.
