# 080C7858: bounded matching attempt

Complete indexed target: `[0x080C7858, 0x080C7906)`, 174 bytes and 87 reachable instructions. The retained natural C removes a tree node, promotes one child when removing the root, reinserts the remaining subtrees using signed keys, and clears the removed node's links.

The fixed native matcher accepted the complete 174-byte compiled symbol, closed leaf CFG, absence of relocations, and source plausibility. Its final result was exit 1, `NOT MATCHING - bytes differ`.

The remaining difference is instruction order in each inlined subtree insertion. At target offsets `0x4E` and `0x7C`, the target loads the context root into `r2` before copying the subtree pointer from `r0` to `r3`. The compiled candidate copies the subtree pointer first, then loads the root. All other instructions, register assignments, and branch destinations agree. Exactly 166 of 174 bytes agree at the same offsets. The matcher's aligned comparison reports 85/87 instructions and 170/174 bytes; that score is not positional byte equality and earns no match credit.

Natural variants with explicit insertion loops and a root-pointer helper retained a context/key register swap. A helper that clears a supplied branch pointer grew to 182 bytes. The retained context-based helper is the closest tested complete candidate. This is a bounded compiler-ordering gap, not a claim of unmatchability.

Final native log: `/home/user/.codex-work/ffta-ulw/audio-following-v247-matching/080C7858/match-current.log`.

Command, from the v247 private matching root:

```sh
env PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' python /home/user/Documents/Claude_Chats/2026-10-09/fftadecomp-kit/tools/match.py --root . 0x080C7858
```

The tested source is retained as `080C7858.c` beside this file. Unmatched active source/report files were removed after this result; no shared files were changed.
