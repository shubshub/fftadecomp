# 08022298 — compact stream token decoder

Complete indexed target: `[0x08022298, 0x080223B2)`, 282 bytes and 129 reachable Thumb instructions. Recovered C initializes the decoder input, output and context, decodes all seven token cases, and selects one of the four mapped handler functions.

The final fixed-toolchain attempt compiles to a complete 274-byte ELF function symbol. Native matching exits 1 before byte comparison with `function-address caller requires an exact mapped Thumb span`; the candidate extent differs from the accepted 282-byte target. All four external callback targets are genuinely mapped Thumb functions. This is a nonmatching caller, not a missing callback binding. No byte-identical or matched-instruction count is claimed.

The remaining assembly differences include the compact-distance branch: the target reads the next byte before its first bit test, retains two explicit halfword-normalization else paths, and stores through a precomputed state-plus-16 pointer. The candidate reads that byte in each conditional arm and eliminates those normalization paths. The target also advances its cursor in place, uses r4–r7, and merges the token-length store shared by the 0x20 and header-2 cases; the candidate retains an original-input base, uses r4–r6, and places these operations and literal pools differently.

Bounded natural iterations covered byte/halfword/word header and distance locals, typed versus generic state/input arguments, preincrement/postincrement/separate cursor updates, and direct versus common-tail callback assignment. None produced the full target. Fixed flags remained `-mthumb-interwork -O2`; no assembly, volatile, compiler pragmas, dead code, or artificial scheduling constructs were used. Standalone native plausibility passes.

The source-bound final native command output is retained in the private address scratch directory as `last-native-output.txt`; the final assembler symbol inspection measured 274 bytes. Only this recovered C and this diagnosis are parked.
