# 080DFEB8: current-machine unmatched wrapper

The existing parent-directory parked source and README are preserved unchanged.
This session recovered the observed forwarding call to
`u32 func_08005BB0(const void *)` and zero/nonzero normalization. The wrapper's
original public return type is not uniquely recovered; these attempts use
`u8` for the observed zero-or-one result. No semantic match proof is claimed.

All three native invocations used:

```
python3 /home/user/Desktop/FFTA-handover-2026-10-30/repos/fftadecomp-kit/tools/match.py --root . 0x080DFEB8
```

The source alongside this file is the closest candidate, attempt 1. Native
plausibility and the direct-Thumb-call profile with ordinary ARM ABI call
summaries pass. Its complete 20-byte ELF body differs at three byte offsets:

```
target: 00 b5 25 f7 79 fe 00 28 01 d1 00 20 00 e0 01 20 02 bc 08 47
got:    00 b5 25 f7 79 fe 00 28 01 d0 01 20 00 e0 00 20 02 bc 08 47
```

The target uses `bne` at 0x080DFEC0 and loads 0 then 1 in the two arms.
The candidate uses `beq` and loads 1 then 0. Bytes at offsets 9, 10 and 14
therefore differ; all other bytes agree (17/20).

Attempts with the same `u8` return type and `const void *` parameter:

1. `if (func_08005BB0(object) == 0) return 0; return 1;` produced the parked
   20-byte body and the captured NOT MATCHING report.
2. `return func_08005BB0(object) != 0;` was rejected with the exact native
   diagnostic `compiled symbol is shorter than the indexed span: 16 < 20`.
3. `return func_08005BB0(object) == 0 ? 0 : 1;` received the same extent
   rejection. These early rejections emitted no replacement reports.

All used default `-mthumb-interwork -O2` flags. No toolkit/profile, shared
header, mapping, inline assembly, pragma, volatile access or steering construct
was introduced. No byte-exact match is claimed.

All candidate sources, native logs and current-machine source-bound receipts
are retained under the handover workspace's
`state/matching-080DFEB8-author/`. The report alongside this file belongs to
attempt 1. The unsuccessful active source and report have been moved out of
`src/` and `docs/match/`.
