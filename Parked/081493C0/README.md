# 081493C0 — Parked

Complete target: 0x081493C0..0x0814941C, 92 bytes and 39 reachable instructions.

`081493C0.c` is the complete best tested natural C candidate. It scans the fixed-size object pool, selects the first entry with its busy bit clear, then sets the busy bit and seven-bit state field. The original exhausted-pool null fallback and subsequent unconditional field writes are preserved.

The default native matcher with agbcc `-mthumb-interwork -O2` returned exit 1: source plausible, compiled extent 92 bytes, 38/39 instructions and 90/92 bytes identical. The remaining difference is instruction scheduling at entry: the compiler loads the pool pointer before initializing the loop index; the target initializes the index before loading that pointer. The loop, literal locations, object stride, bitfield update sequence, and return otherwise match.

Bounded natural alternatives covered a direct search loop, an inline search helper, local versus argument-backed pool/count access, byte versus integer count, and conventional local initialization. None produced the target instruction ordering. No assembly, volatile access, dead code, compiler flags, or shared metadata changes were used.

Raw native comparison evidence remains outside the repository in the private address scratch directory. No active source or match report is retained for this unmatched function, and no exact-match credit is claimed.
