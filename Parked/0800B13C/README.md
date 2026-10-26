# 0800B13C — unmatched complete candidate

Target: complete [0x0800B13C, 0x0800B2A4), 360 bytes / 175 reachable instructions. Captured target: `/home/user/.codex-work/ffta-ulw/audio-following-v102-matching/0800B13C/target-disassembly.md`.

The retained C implements all four flag-selected table layouts, optional first index, inclusive signed last index, signed 16-bit accumulation, and the 999 terminator for the two signed-value layouts. The packed signed-field view represents the observed unaligned little-endian reads without volatile access.

Latest native result: exit 1, `compiled symbol is shorter than the indexed span: 352 < 360`. The candidate is complete; no match credit is claimed. Fixed compiler flags remain `-mthumb-interwork -O2`.

Remaining gap: the compiler retains different induction-value and pointer-base representations in the byte-layout loops and different register allocation around the signed-value loops. The target keeps the byte-loop counter as a narrowed raw halfword, sign-extends it on each iteration, and forms the data-plus-three base after the initial bounds check. The current source optimizes these operations differently. Earlier explicit byte assembly also reused signed-value reads that the target performs separately; the packed field view restores those reads, but does not resolve the complete code-generation gap. Recovering the original serialized record and counter declarations is the next concrete source-level step.

Native command:

```sh
env PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' python /home/user/Documents/Claude_Chats/2026-10-09/fftadecomp-kit/tools/match.py --root /home/user/.codex-work/ffta-ulw/audio-following-v102-matching/matching-root 0x0800B13C
```

Retained final invocation output: `/home/user/.codex-work/ffta-ulw/audio-following-v102-matching/0800B13C/match-current.log`. The unmatched source and generated report were removed from `src/` and `docs/match/`; only this Parked pair remains for integration.
