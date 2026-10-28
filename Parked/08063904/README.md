# 08063904 reconstruction (not matching)

Target: 08063904..08063ABC, complete 440 bytes and 202 reachable instructions.
Accepted claim: 6461064870. No matching credit.

The complete natural reconstruction polls the task result, updates the selected object and task state, and appends the recovered history sequences. The state layout, callee signatures, global bindings, field widths, constants, and every branch's complete behavior are retained.

Fixed native command uses agbcc -mthumb-interwork -O2 and the approved ROM. Final native exit 1: source plausible; complete original compiler function 448 bytes/206 instructions; 190/206 instructions identical (428/448 bytes). The failing gate is byte equality, not eligibility, ABI, ownership, or source plausibility. Fresh report_matches is false.

Precise remaining gap: the single-history-entry branch allocates its value/base in r2/r1 and emits an address addition, store, and base copy before jumping to the final 0x32 append. ROM keeps the value/base in r3/r2 and shares the final address addition/store with the longer branch. The final 0x32 append in the compiler output also copies the base to r3 and uses r2 for the value; ROM retains r2 for the base and r3 for the value. These choices add eight bytes/four instructions and shift the later branch displacements and pool placement. The initialization/call sequence and repeated long history blocks otherwise match.

Bounded natural refinements tested direct current-field reads, a semantic inline append helper, a shared history pointer, chained assignment, and a status switch. Direct forms and the inline helper retained the same eight-byte gap; the explicit pointer and chained form changed allocation more broadly. The simplest complete direct-field reconstruction is preserved here. No compiler flags, assembly, volatile, padding, dead code, runtime aliases, forced inlining, manufactured constant joins, or shared metadata were used.

Unmodified compiler relocatable ELF and the full native diagnostic report are retained outside matching-root in the sibling 08063904 artifact directory. Active unmatched source/report were removed.
