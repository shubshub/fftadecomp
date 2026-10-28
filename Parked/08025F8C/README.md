# 08025F8C

Complete recovered predicate for 0x08025F8C..0x08025FDA. It rejects a user when 080CDBB4 is true; otherwise it accepts when 080CD95C is false or kind is 1, returns 080CD560(user,26) for kind 21, and rejects other kinds.

Fresh canonical native matching with fixed agbcc `-mthumb-interwork -O2` exited 1. Source passed plausibility; the complete candidate and target are both 78 bytes. The target has 34 reachable instructions, candidate 32. Native aligned score: 26/32 instructions and 68/78 bytes. Independent same-offset equality: 53/78 bytes; the aligned score is not a same-offset score.

The target narrows the argument into R5 and copies it into persistent R6 at 08025F92. It compares R5 with 1, but compares R6 with 21, and saves/restores R6. Natural tested C instead uses R5 for both comparisons and saves/restores only R4/R5. Its missing copy shifts the first call and changes literal-load displacement, branch positions and alignment; the target copy/register allocation remains unreproduced. No per-address exception or compiler steering was used.

Bounded natural forms tried:

- A direct two-case switch inside the 080CD95C condition: preserved 78-byte/32-instruction candidate.
- Combined early-return guards with direct comparisons: complete symbol shortened to 76 bytes, so the extent gate refused it before plausibility checking.
- A separate byte guard followed by the remaining one-case switch: same 78-byte residual.
- A naturally inline kind/status helper: 82-byte plausible candidate with extra return normalization/branching, still no persistent R6 copy; removed.
- Byte-sized and promoted unsigned selector locals for the switch: same 78-byte residual; removed as unnecessary.

The simplest complete candidate was restored and freshly checked. This records a bounded fixed-profile code-generation gap, not permanent impossibility. Native output and the source-bound nonmatching report remain in private address scratch. Unmatched active C/report were removed.
