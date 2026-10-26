# 080DDC18: bounded natural source gap

Target: `0x080DDC18..0x080DDD9E`, complete 390 bytes / 189 reachable instructions.

The C reconstructs the command-state handler: copy effect spawn settings, create the optional special effect, delay and spawn the entry effects, poll their handles, select completion sound behavior from flags, then release the special handle. Struct offsets follow the target loads and stores. The sound-selection helper naturally inlines; only the target function is emitted.

The final canonical native matcher invocation at fixed agbcc `-mthumb-interwork -O2` returned exit 1: source plausible, complete compiled symbol 390 bytes, NOT MATCHING. Native diff score is 188/189 instructions and 388/390 bytes; that score is not a claim of same-offset byte equality.

Only one instruction differs: target `0x080DDCB8` is `adds r4, r7, r0`; compiled code is `adds r4, r0, r7`. Both add the four-byte entry offset and loaded entry-table base with the same destination and result. All other reported instructions match.

The initial shared loop counter and narrow flag local compiled to 380 bytes. Separate counters for the independent command phases and a promoted flag local produced 388 bytes. Factoring the cohesive sound-selection operation into a naturally inlined semantic helper produced the complete 390-byte extent and matched its register usage. Direct entry indexing was also tested; it additionally moved the table load after the index scaling, so the better tested explicit table-base local is retained. No flags, assembly, volatile accesses, artificial operand reversal, forced inlining, or dead code were used. No exact-match credit is claimed. Unmatched active source/report were removed.
