# 08111A5C — not matching

Complete target: `[0x08111A5C, 0x08111C7C)`, 544 bytes and 242 reachable instructions.

The full recovered function initializes an actor interpolation, waits through the first delay, creates its child task, then updates and spawns 28 independently timed sprites. The two interpolation arrays, sprite array, actor and child fields are represented at their observed offsets. The final transition waits for the central object, the final spawn interval and all 28 sprites to finish.

A fresh default native match after restoring the retained candidate exited 1. The complete compiled symbol is 544 bytes, the source is plausible, and the native aligned comparison reports 241/242 instructions identical (542/544 bytes).

The only remaining difference is the order of the definition-table base load at the second loop head. The target loads that base before copying and scaling the 8-bit index; the candidate copies/scales the index before loading the same base. The load's PC-relative displacement consequently differs. The same entry pointer, field loads, calls, loop updates, completion checks and literal data otherwise match. This is an instruction-order gap, not an unsupported native profile or missing binding.

Bounded natural attempts included the original local entry pointer, a shared table pointer for the loop and completion check, a base-plus-element pointer, a function-scope entry pointer, direct repeated array accesses, and a do/while loop. The original, function-scope entry pointer and do/while forms retained the same best gap; the other forms worsened the result. The original complete source is retained and was freshly rechecked. Compiler flags remained fixed at `-mthumb-interwork -O2`; no steering constructs were added.

Native command: `python /home/user/Documents/Claude_Chats/2026-10-09/fftadecomp-kit/tools/match.py --root /home/user/.codex-work/ffta-ulw/audio-following-v100-matching/matching-root 0x08111A5C`, with the approved ROM, ARM toolchain PATH and disk-backed TMPDIR. Full native output and the differing generated report remain only in the private address scratch directory. No match credit is claimed.
