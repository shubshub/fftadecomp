# 080A4274 recovered, not matched

Target: complete indexed 0x080A4274..0x080A433C, 200 bytes and 97 reachable Thumb instructions.

The complete natural C preserves the optional identifier-property gate, the counted 44-byte record traversal at owner offset 0x20, replacement lookup, flag 0x40 rejection, duplicate checks against both selection arrays, replacement notification and store, and the accumulated changed result.

The final fixed native agbcc `-mthumb-interwork -O2` run returned exit 1, with plausible source and a verified complete 200-byte ELF symbol. The matcher reported an aligned diff score of 80/97 instructions and 181/200 bytes. Direct comparison of the report's ROM and compiled byte strings gives 179/200 equal bytes at the same offsets; these are distinct measures.

The residual is register allocation and record-address formation. The candidate keeps the outer index in r4 and record pointer in r5; the target uses r5 and r4 respectively. The candidate multiplies the index into r0, adds 0x20, then adds the owner through a low register. The target copies the index into r4, multiplies there, adds the owner from sb, then adds 0x20. The corresponding inner-loop bound, record field accesses, and saved next index consequently use different registers. Calls, branch sites, the stack frame, and final extent otherwise align.

Bounded natural forms tried: combined duplicate checks produced the same 200-byte extent but a lower aligned score; separate early-return checks recovered the target's control flow. Direct record-pointer, indexed-owner, and record-array helper interfaces were tested. Word and byte boolean helper results and ordinary local declaration order retained the best 200-byte mismatch. Explicit signed and sizeof-based byte-offset record views produced 204-byte bodies. No compiler flags, assembly, volatile accesses, dead code, or steering constructs were used.

The preserved source is the final tested candidate. Its native report and output remain in the address scratch directory as `best-report.md` and `last-native-output.txt`. No match credit is claimed; the result records a bounded unresolved source/allocation gap rather than permanent impossibility.
