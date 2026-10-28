# 080DCAD4 — unresolved native match

Complete target: [0x080DCAD4, 0x080DCBBC), 232 bytes and 110 reachable instructions. The retained C reconstructs initialization, delay/countdown states, object dispatch, audio flag dispatch and interval scheduling.

The final default native matcher invocation exited 1: `compiled symbol is shorter than the indexed span: 230 < 232`. The candidate emits 109 instructions. Completeness rejection occurs before native source-plausibility or byte-comparison results, so this is not a verified match or a native plausibility pass.

The target loads the interval byte at 0x080DCB94 to test it, then loads it again at 0x080DCB9A before storing the timer. The candidate reuses the first loaded value and omits that second two-byte load. The target also holds the inner kind-switch selector in r1; the candidate uses r0. The reconstructed state/call sequence otherwise follows the complete captured target. No aligned-score or same-offset equality claim is made.

Natural field representations (ordinary fields and byte/halfword bitfields) retained the 230-byte extent. A scheduling helper either emitted an extra function and was rejected, or naturally inlined to the same 230-byte target body. The retained source uses ordinary fields and no helper. The remaining problem is source/type recovery; these attempts do not establish unmatchability.

Native replay from this batch's matching-root after temporarily restoring this candidate to src/080DCAD4.c:

```sh
env PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' python /home/user/Documents/Claude_Chats/2026-10-09/fftadecomp-kit/tools/match.py --root . 0x080DCAD4
```

Final native output: ../080DCAD4/match-current.log. Full target: ../080DCAD4/target-disassembly.md. Unmatched active source and report have been cleared.
