# 08010DD0 — bounded natural C attempt

Target: `[0x08010DD0, 0x08010E62)`, 146 bytes, 59 reachable Thumb instructions. The recovered function walks the counted contiguous node array, removes active nodes whose update returns zero from one of four doubly linked lists, and performs the secondary update when flag bits 1 and 2 are clear. The original do/while traversal and incoming/return ABI are preserved.

The final native matcher invocation exited 1: `NOT MATCHING - bytes differ`. The complete compiled ELF symbol is 146 bytes; native ordinary-call/extent validation passed, and source plausibility was reported `plausible`. This is not an exact match and receives no match credit.

The target preserves the current node with `adds r3, r4, #0` at 0x08010DE8 and uses r3 for the previous/next loads and state clear during unlinking. The compiler omits that copy and uses r4 directly. This also changes the nearby switch branch/literal placement while retaining the complete 146-byte symbol. The native aligned diff reports 54/58 instructions and 137/146 bytes identical; those are aligned diff figures, not same-offset byte equality.

Three natural helper arrangements were tested: one unlink helper containing head selection, separate head-selection and unlink helpers, and explicit head selection passed into unlinking. All retained the same machine-code gap. The preserved C is the final tested complete candidate; no artificial pointer uses, assembly, volatile RAM, compiler flag changes or forced inlining were introduced.

Compiler: agbcc `-mthumb-interwork -O2`.
Native command, from the private matching root:

```sh
env PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' python /home/user/Documents/Claude_Chats/2026-10-09/fftadecomp-kit/tools/match.py --root . 0x08010DD0
```

Final native output: `/home/user/.codex-work/ffta-ulw/audio-following-v455-matching/08010DD0/match-current.log`.
Full target: `/home/user/.codex-work/ffta-ulw/audio-following-v455-matching/08010DD0/target-disassembly.md`.
