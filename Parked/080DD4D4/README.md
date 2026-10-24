# 080DD4D4: signed sentinel fallback, not matching

The preserved C recovers the observed behavior but emits 48 bytes with fixed
`agbcc -mthumb-interwork -O2`; the complete ROM body owns 56 bytes. Canonical
matching rejects the complete-symbol shortfall. No match or progress credit.

The first and only semantic candidate is frozen unchanged, SHA-256
`b0b433098c55e37b4745f853e4cdfd66beffadbc99d70211efb8cc703d606cc3`.
It starts with signed 0x7FFF, selects field +0x1E if flags bit 0 is set, then
selects +0x20 if the current value is still the sentinel and bit 1 is set.
There is no bit-7 gate. Local fields have independently checked offsets.

## Exact remaining difference

ROM: 25 reachable instructions / 50 code bytes, two internal alignment bytes,
and a four-byte literal at 080DD508, ending at 080DD50C. Candidate: 21 reachable
instructions / 42 code bytes, two alignment bytes and a four-byte literal at
relative +0x2C, complete 48-byte ELF symbol. Both are relocation-free leaf CFGs.

The candidate omits the ROM's pre-comparison sign-extension pair, an extra
result move, and saved-r4 pop. It uses different registers and consequently
different load/branch encodings. Its unsigned ldrh result can compare directly
against 0x7FFF without changing equality, then sign-extend once on return.
Exact bytes, differing common-prefix offsets and hashes are retained in
`/home/user/.codex-work/ffta-ulw/080DD4D4-author-substantial/ownership-evidence.json`;
full object disassembly is in
`/home/user/.codex-work/ffta-ulw/080DD4D4-author-substantial/compile-1.log`.

There is no identified semantic gap. No further source candidates, compiler
flags, instruction-order rearrangements or register/spelling searches were
tried. One canonical compile and one inspection compile used identical source
and fixed flags. The compiler/verifier are capable of inspecting this function;
this result is not a claim that the target cannot be matched naturally.

## Evidence and separate metadata

All 210 bounded behavior checks pass: 42 native, 84 ROM and 84 compiled cases.
They cover sentinel fallback, flag priority/absence, irrelevant bits including
bit 7, signed extrema/-1/0/1, ARM/Thumb return modes, saved registers/SP and
unchanged inputs. Five raw main-region BL sites were observed; F1094 explicitly
sign-extends the low halfword result. These are retained observations, not
additional executed caller tests or a proof of all possible callers.

The original end 080DD506 omits the twice-read literal. A separate
three-file metadata patch proposes end 080DD50C, 56 bytes and sym size 0x38.
It preserves the correct count 25. The initial isolated experiment used 28
halfword slots; the coordinator subsequently confirmed `analyze.py` defines
`instrs` as decoded instruction count, so that proposal was corrected without
another compile. Historical isolated snapshots retain 28 for provenance and
must not replace shared indexes. Old and actual instruction counts are both
25. The extent proposal earns no C match credit.

Only this C file and README are intended for Parked integration; supporting
evidence stays in the retained author bundle. No source remains under that
bundle's src/; no generated binaries remain. See
`/home/user/.codex-work/ffta-ulw/080DD4D4-author-substantial/HANDOFF.md`
for full provenance, limitations and reproduction.
