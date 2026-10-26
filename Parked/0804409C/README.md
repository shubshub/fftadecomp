# 0804409C — Parked

Complete captured target: `[0x0804409C, 0x0804413C)`, 160 bytes and 69 reachable instructions.

The complete natural C candidate stores the primary selection in both saved-state fields, then visits all five six-byte specifications. Nonzero eligible specifications take the selected slot from their active menu entry while preserving the other packed fields.

Fresh default native matcher result with fixed agbcc `-mthumb-interwork -O2`: exit 1, complete compiled extent 160 bytes, source plausible, 67/69 instructions identical and 156/160 bytes identical.

The remaining difference is the placement of two register-copy instructions before the loop. The target copies the persistent menu-pointer address and packed-field mask before calculating the initial specification address; the candidate calculates that address first. The stores, loop body, pointer stride, iteration count and loop tail otherwise match.

Bounded natural attempts covered explicit descending iteration, compiler-reversed ascending iteration, direct array indexing, byte versus integer loop counts, pointer initialization in the loop initializer, and direct initialization of the specification pointer. The closest complete tested candidate is retained here. No redundant operations or compiler steering were added to force the instruction schedule.

Raw target capture, full native output and differing report remain in private address scratch outside the matching root. Unmatched active source and report have been removed. No exact-match credit is claimed.
