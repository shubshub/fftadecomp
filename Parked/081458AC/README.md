# 081458AC — Parked

Target: complete ROM function [0x081458AC, 0x08145990), 228 bytes / 109 instructions.

The preserved natural C reconstructs music-player song startup: signature and priority checks, player timing resets, track stop/start initialization, remaining-track shutdown, optional reverb, and signature restoration. Track stride is 0x50; song parts begin at +8.

Fresh native matcher result with unchanged agbcc -mthumb-interwork -O2: exit 1, complete ELF extent 228 bytes, source plausible, NOT MATCHING because bytes differ. Native comparison: 91/109 instructions identical and 205/228 same-offset bytes. Full invocation output remains in the sibling address scratch native-output.txt.

Remaining differences:

- Priority checking: ROM loads check_priority before the initial song priority, then reloads song priority into r0 and copies it to r2 on the active-player path. The candidate loads song priority first, caches it in r3, and later copies r3 to r2. The byte-flag test also uses a different pointer register/load order.
- The two track loops have the same control flow, calls, field offsets, and stores, but several temporary count and zero values use r0 rather than r1. The candidate loads reverb before forming the 0x80 mask; ROM forms the mask first.
- The status word and low-halfword checks, initialization constants, song pointers, track stride, and both called addresses agree.

Bounded natural reconstructions tried: direct low-halfword/signed status tests, a status union, explicit status masks, priority snapshot/refresh, conditional priority assignment, and assigning priority after the rejection guard. The explicit-mask snapshot/refresh reconstruction retained here had the best tested byte comparison. The union variant was 224 bytes; conditional branch assignment was 232 bytes. No assembly, volatile, compiler changes, forced inlining, artificial reads, or scheduling-only code was introduced.

Only byte equality remains unresolved. The unmatched active source/report have been removed; this pair receives no match credit.
