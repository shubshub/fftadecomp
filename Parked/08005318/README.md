# 0x08005318 — Parked

Complete target: `[0x08005318, 0x080053D4)`, 188 bytes / 87 instructions.

The fixed native matcher exits 1: plausible C, complete 188-byte ELF function symbol, 178/188 bytes and 81/87 instructions identical. Typed linking resolves the direct call to `0x080051C4` and all three named data literals.

The recovered function bounds a range against a big-endian 16-bit entry count, reads a big-endian dictionary offset, resets output state, then processes each big-endian entry offset. A zero result from the entry processor returns 1; completing the range returns 0.

Seven native runs covered a separate loop index versus a mutable incoming start with a saved first index, distinct header/entry byte-pointer locals, natural generic-pointer interfaces, a local sentinel value, and the order of the independent output-state reset statements. The saved-first-index form and separate pointer locals recover the complete target register allocation and loop body.

The remaining difference is confined to output-state initialization at target `0x0800536A..0x08005382` and the corresponding literal ordering. The target materializes -1 into r1, stores the output pointer through r2 at `data_03002BB8`, then stores r1 at `data_03002BB4`. The closest complete-size candidate stores -1 first through r1 using r0, then stores the output pointer through r1. Every instruction outside this initialization block matches, including the full loop, direct call, branches and epilogue. The retained candidate therefore has the same resets but a different order of the two independent global stores. No exact-match claim is made.

Using the pointer-first reset order instead produces a 192-byte function and an extra copy from ip for the initial output byte store. Generic source data plus a local byte pointer recovered the target source register; generic destination types changed the incoming output-pointer register instead. The explicit -1 local did not change code generation.

No assembly, volatile, pragmas or artificial steering was used. The nonmatching active source and report were removed. The source-bound native report remains privately at `/home/user/.codex-work/ffta-ulw/audio-following-v67-matching/08005318/last-native-report.md`.
