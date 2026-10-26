# 0802192C — unmatched complete candidate

Target: complete [0x0802192C, 0x08021A3C), 272 bytes / 131 reachable instructions. Captured target: `/home/user/.codex-work/ffta-ulw/audio-following-v104-matching/0802192C/target-disassembly.md`.

The retained candidate covers the initial readiness scan, exhaustion check, zero-cost boundary retries, backward propagation of an unsigned halfword offset, flag updates, and ordinary cursor advancement. Its retry label implements the observed transition back to the same step without consuming a requested step. All observed halfword fields and pointer slots are represented explicitly.

Latest native result: exit 1, `compiled symbol is shorter than the indexed span: 256 < 272`. No match credit is claimed. The compiler flags remain `-mthumb-interwork -O2`; no verifier, metadata, headers, or toolkit files were changed.

Remaining gap: counter and comparison-value allocation differ. The target holds the shared scan/step index in ip, the step limit in r8, and a loop-invariant flag bit in r9; it also preserves separate promoted comparison values and uses different operand ordering in the update blocks. The retained natural C allocates fewer registers and emits a shorter complete function. Structured retry-loop forms were tested as well, but introduced repeated condition loads and larger code. The original counter/field declarations and source-level transition form remain unresolved; recovering those declarations is the next source-level step. No dummy uses, forced loads, assembly, or register constraints were added.

Native command:

```sh
env PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' python /home/user/Documents/Claude_Chats/2026-10-09/fftadecomp-kit/tools/match.py --root /home/user/.codex-work/ffta-ulw/audio-following-v104-matching/matching-root 0x0802192C
```

Final output: `/home/user/.codex-work/ffta-ulw/audio-following-v104-matching/0802192C/match-current.log`. Unmatched `src/0802192C.c` and `docs/match/0802192C.md` have been cleared; this Parked pair is the retained integration artifact.
