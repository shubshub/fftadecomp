# 08057E98 — parked natural C attempt

Complete indexed target: `[0x08057E98, 0x08058104)`, 620 bytes and 290 reachable instructions.

The complete candidate draws both mode-specific tile layouts and clears each layout's final tile row. The best source was restored and freshly tested with the unchanged native matcher, approved ROM and fixed agbcc `-mthumb-interwork -O2`. Native exit: 1. Source verdict: plausible. Compiled complete symbol: 620 bytes. Native comparison: 289/290 instructions and 618/620 bytes identical. This is not an exact match.

The sole remaining instruction-order difference is materialization of the `g_state_02000000` table address. The target loads it into r1 at 0x08057EE4, before the three instructions multiplying unitId by 264. The candidate emits those three instructions first and then loads the same address into r1; its PC-relative immediate changes accordingly. The resulting unit-record pointer in SL and all subsequent drawing calls, tile accesses, loops and epilogue match.

Natural forms tested included direct arithmetic and explicit row/bank offsets, a shared mutable tile destination and loop counter, and byte-view versus direct typed table access. Separate 32-bit bank-row arithmetic avoids the initial common-factor rewrite that multiplied width by five; narrowing that phase early instead introduced an OR and extra copy. Direct typed accesses without the cached unit pointer increased the frame from 12 to 16 bytes and complete symbol from 620 to 636 bytes, so that form was discarded. No assembly, volatile storage, fixed registers, compiler changes, or scheduling contrivances were used.

Raw source SHA-256: `7e8168737123653840e0f0eef3ecceee012fc9206aaa068a1a97a62591275660`.
Preserved native report: `/home/user/.codex-work/ffta-ulw/audio-following-v100-matching/08057E98/last-native-report.md`.
Report SHA-256: `57dff0feb368a1c85210b67cabd66918b53ad593da5803c6fca633eff5832c45`.
Fresh raw native output remains at `/home/user/.codex-work/ffta-ulw/audio-following-v100-matching/08057E98/native-output.txt`. The complete captured target remains in the same address scratch directory.

Unmatched private src/report files have been removed. Root owns integration and lease release.
