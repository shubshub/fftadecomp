# 08016560 — bounded natural C attempt

Target: `[0x08016560, 0x080165C4)`, 100 bytes, 50 reachable Thumb instructions. The complete recovered behavior fills width halfwords for height-minus-three rows, beginning two stride rows into a tile buffer, only when width exceeds one and height exceeds three. Each halfword is the 16-bit sum of the tile argument and palette shifted left twelve bits. Row stride is the fifth argument; the fourth flags argument is unused. The seven-argument ABI agrees with the existing caller at 08016268.

Final native matcher exit: 1. Actual refusal: `compiled symbol is shorter than the indexed span: 96 < 100`. The preserved candidate emits a complete 96-byte symbol with 48 Thumb instructions. The native gate refuses the extent before source plausibility, so there is no native plausibility or exact-match claim for this candidate and no match credit.

The main residual is register allocation and copies around the nested loops. ROM preserves the incoming buffer in ip, then copies ip back to a low register when forming the row address. The compiler preserves the buffer in r7 and forms the row address directly. ROM keeps the current row count in r1, decrements into r2 before the inner loop, and copies r2 back to r1 afterward; the compiler keeps that counter in r2 directly. Those omitted copies and different assignments of stride, tile, row and column registers leave the candidate four bytes shorter. The bounds checks, seven incoming arguments, row start/stride arithmetic, tile narrowing and complete nested-fill behavior are retained.

Natural forms tested: unsigned post-decrement row condition; an explicit zero-tested row counter; typed versus opaque buffer input; a genuine naturally inline row-fill helper; and halfword versus byte row addressing. The post-decrement form produced 104 bytes and passed source plausibility but retained a -1 loop sentinel and different register allocation. Explicit zero testing produced 96 bytes; the other buffer/helper forms retained that extent. The final helper form is naturally fully inlined, with only the target function emitted. No assembly, artificial volatile access, forced inlining, compiler flag changes or inert code was used.

Compiler: agbcc `-mthumb-interwork -O2`.
Native command, from the private matching root:

```sh
env PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' python /home/user/Documents/Claude_Chats/2026-10-09/fftadecomp-kit/tools/match.py --root . 0x08016560
```

Final native output: `/home/user/.codex-work/ffta-ulw/audio-following-v462-matching/08016560/match-current.log`.
Compiler diagnostic assembly: `/home/user/.codex-work/ffta-ulw/audio-following-v462-matching/08016560/candidate.s`.
Full target: `/home/user/.codex-work/ffta-ulw/audio-following-v462-matching/08016560/target-disassembly.md`.
