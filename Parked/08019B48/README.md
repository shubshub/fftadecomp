# 08019B48 — parked natural C attempt

Complete indexed target: `[0x08019B48, 0x08019C74)`, 300 bytes and 135 reachable instructions.

The complete implementation computes the primary viewport displacement, applies enabled horizontal/vertical offsets, updates the configured background pair, conditionally updates backgrounds 2 and 3 from the secondary layer, and clears flag 0x200.

The best tested complete source was restored and freshly compiled with the unchanged native matcher, approved ROM, and fixed agbcc `-mthumb-interwork -O2`. Native exit: 1. Compiled symbol: 288 bytes, twelve bytes shorter than the indexed 300-byte target. The native matcher stops at its short-symbol gate, so no byte/instruction similarity count, generated report, or native plausibility verdict exists. This is not an exact match.

Manual diagnostic assembly identified missing signed extensions in the optional primary-coordinate additions. The target sign-extends x before adding offsetX and sign-extends y before adding offsetY; agbcc's natural short-coordinate form eliminates those extensions because the result is narrowed back to sixteen bits. The candidate also reuses nearby field offsets with short immediate additions where the target rematerializes constants, and allocates the secondary-layer base to r2 rather than r1. Both forms reach the same recovered fields and implement all captured branches and calls.

Bounded natural forms tested: signed short coordinates with compound additions; full assignment additions with secondary position-plus-offset expressions; unsigned short working coordinates with signed interpretation; and word-sized coordinates with explicit sixteen-bit wrapping. The latter forms compiled to 284 bytes and did not recover the target's signed-extension sequence. The smallest extent gap remains the preserved 288-byte signed-short form. No assembly, volatile storage, fixed registers, compiler changes, dead code, or scheduling contrivances were used.

Raw source SHA-256: `a59e4bfe45d7f69df521e18be485c3bc2d06b5d520f7c53c4321e0ceb8d5fbc9`.
Native output: `/home/user/.codex-work/ffta-ulw/audio-following-v103-matching/08019B48/native-output.txt`.
Native output SHA-256: `6c20aa50d1ab70585d7c885a48960c45da9da946a541e6f460c0b5e4c134ecd4`.
The full captured target remains in the same scratch directory.

Unmatched private src/report files have been removed. Root owns integration and lease release.
