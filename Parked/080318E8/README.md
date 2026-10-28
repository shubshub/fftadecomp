# 080318E8 — unresolved loop-setup scheduling

Complete target: `[0x080318E8, 0x08031978)`, 144 bytes / 58 reachable instructions.

The retained complete C initializes the twelve pointer slots, installs the four VRAM buffer addresses, derives the six pointers from the shared state buffer, and assigns the scratch pointer. Fixed native matching returned exit 1: source plausible; complete ELF symbol 144 bytes; closed leaf CFG with no relocations; 139/144 bytes and 55/58 instructions identical. This is not a match and receives no match credit.

The remaining difference is instruction scheduling before the clear loop. The candidate computes the slot cursor (`r3 = r4 + 8`) before loading the shared-state pointer address and scratch address into r0/r5 and clearing r2. The target loads r0/r5 and clears r2 before computing that cursor. These reordered loads also change their PC-relative literal displacements. The clear loop and subsequent field initialization otherwise match.

An indexed clear loop generated reverse traversal and a longer symbol. A normal memset remained an unsupported undefined runtime call. Aggregate initialization introduced an allocated constant section or an unresolved runtime copy, so neither was retained. External VRAM symbols additionally caused constant-address hoisting and larger register saves; the retained source uses the actual fixed VRAM addresses. No assembly, volatile accesses, pragmas, dead code, compiler-option changes, or verifier changes were used.

Retained native log: `/home/user/.codex-work/ffta-ulw/audio-following-v111-matching/080318E8/match-current.log`.

Native invocation (source must be installed at src/080318E8.c to replay):

```sh
env PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' python /home/user/Documents/Claude_Chats/2026-10-09/fftadecomp-kit/tools/match.py --root /home/user/.codex-work/ffta-ulw/audio-following-v111-matching/matching-root 0x080318E8
```
