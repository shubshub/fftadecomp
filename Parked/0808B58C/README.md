# 0808B58C

Complete natural rectangle-fill implementation for [0x0808B58C, 0x0808B66C): 224 target bytes and 108 reachable instructions. No match credit.

Fresh default native match exited 1. The fixed agbcc flags were `-mthumb-interwork -O2`. The complete compiled symbol is 228 bytes; native closed-leaf CFG, fixed-frame/data proof and source plausibility are accepted. Comparison reports 83/108 instructions identical and 199/228 bytes identical.

The remaining difference is localized to packed-dimension decoding. The target retains the record offset in r1, loads the packed byte into r2, performs a distinct signed-byte load using r0, and reloads positive width from the record. The candidate retains the offset in r0, uses r3 for the packed byte, emits an unsigned load followed by two sign-extension shifts, and reuses that byte for positive width. It merges the height assignment through r3 before moving to ip. This adds one instruction and shifts alignment/literal placement, producing 228 rather than 224 bytes. The row/column loops, tile calculation and panel accesses otherwise match, apart from the resulting branch and literal offsets.

Natural signed/unsigned field and scalar types, a local record pointer, split destination arithmetic, and direct height initialization were tried. The retained version is the best complete native-tested candidate; no verifier limits, flags or metadata were changed. This is a compiler-shape gap, not a claim of unmatchability.

Native command:

```sh
env PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' python /home/user/Documents/Claude_Chats/2026-10-09/fftadecomp-kit/tools/match.py --root /home/user/.codex-work/ffta-ulw/audio-following-v165-matching/matching-root 0x0808B58C
```

The tested invocation used src/0808B58C.c; the unchanged source is retained here after clearing the unmatched source/report. Native log: ../0808B58C/match-current.log relative to the private matching root. Complete target: ../0808B58C/target-disassembly.md relative to the private matching root.
