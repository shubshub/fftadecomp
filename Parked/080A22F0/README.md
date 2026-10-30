# 080A22F0: Parked, not matching

The native check returned exit 1, `NOT MATCHING - bytes differ`, for a plausible complete 200-byte ELF symbol covering [0x080A22F0, 0x080A23B8). No matching credit is claimed.

The final candidate has the same instructions and literals except for one load's order. At 0x080A230C the ROM executes `ldrh r1, [r4, #6]` before `lsls r0, r0, #16; asrs r0, r0, #16`. The candidate executes the sign extension first and then the halfword load. The following subtraction and every subsequent byte match at their original addresses. The native alignment metric is 86/87 instructions and 198/200 bytes; this is an alignment score, not the count of equal bytes at fixed offsets. The parking receipt records all fixed-offset byte differences.

Three natural forms were checked:

1. Combined signed-halfword expression and byte counter temporary. Plausible, complete 200-byte symbol, mismatching initial narrowing and counter update.
2. Separate signed-halfword assignments and a wide unsigned counter temporary. Plausible, complete 200-byte symbol, native alignment 84/87 instructions and 195/200 bytes.
3. A signed wide intermediate for the narrowed getter result, signed-halfword adjusted value, and wide unsigned counter temporary. Plausible, complete 200-byte symbol; only load order differs as described above.

The actual defining helper signatures are retained, including the s32 result of `func_080C7EA4`. No fake narrow-return declaration, assembly, volatile access, dead operation, compiler steering, or toolkit modification was used. All six helper definitions were read; no helper proof was replayed. Earlier candidates, reports and native receipts remain in `state/matching-080A22F0-author/` at the handover root. The active source and generated report were moved here after the bounded failure.

Native command: `python3 /home/user/Desktop/FFTA-handover-2026-10-30/repos/fftadecomp-kit/tools/match.py --root . 0x080A22F0` from the isolated batch3 game worktree.
