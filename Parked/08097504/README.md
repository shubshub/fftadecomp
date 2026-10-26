# 08097504

Complete natural position/range eligibility implementation for [0x08097504, 0x080975DA): 214 target bytes and 103 reachable instructions. No match credit.

Fresh default native match exited 1. The fixed agbcc flags were `-mthumb-interwork -O2`. The complete compiled symbol is 214 bytes; ordinary direct Thumb call proof and source plausibility are accepted. Comparison reports 101/103 instructions identical and 212/214 bytes identical.

The only differing instructions are the lower movement bound. The target emits `cmp r0, #2` followed by `blt` to the false-return block; the retained source emits `cmp r0, #1` followed by `ble` to the same block. The conditions are equivalent for the signed integer local. All other bytes, including helper calls, coordinate narrowing, terrain checks, range comparison, frame and branches, match.

A combined range condition folds into a subtraction and unsigned bound check, producing 212 bytes for an integer local or 216 bytes for a byte local. Separate byte/direct-field guards produce unsigned branches. Separate signed integer guards recover the target upper comparison and complete 214-byte layout but canonicalize the lower comparison as described. A signed halfword local, reversed comparison operands and a Boolean predicate local did not resolve that last difference. The retained source is the best complete native-tested candidate; compiler flags and metadata were unchanged. This is an unresolved compiler-shape gap, not a claim of unmatchability.

Native command:

```sh
env PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' python /home/user/Documents/Claude_Chats/2026-10-09/fftadecomp-kit/tools/match.py --root /home/user/.codex-work/ffta-ulw/audio-following-v177-matching/matching-root 0x08097504
```

The invocation used src/08097504.c; the unchanged source is retained here after clearing the unmatched source/report. Relative to the private matching root, the native log is ../08097504/match-current.log and the complete target is ../08097504/target-disassembly.md.
