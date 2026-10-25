# 080E0240 — preserved nonmatching curve-task callback

**NONMATCH; preservation only, zero compiled-match credit.** One natural source
candidate was frozen before one canonical compilation with the default
`$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`. It remains unchanged. No alternative
source, type, flags, register ordering or spelling was tried; no native campaign
was run after the nonmatch.

## Actual result and complete ownership

The canonical process exited **1** with:

```text
compile failed:
buffer caller requires an exact complete mapped span
```

This is a post-compilation verification failure, not a C/compiler syntax failure.
The original object and linked executable were both captured completely. The
canonical tool stopped before producing a match report or aligned diff; no report
is claimed or supplied for integration.

| Body | Bytes | Reached instructions | Code | Owned literals | Internal alignment |
| --- | ---: | ---: | ---: | ---: | ---: |
| True ROM target [080E0240,080E03F8) | 440 | 210 | 434 | 4 | 2 |
| Complete compiled ELF function symbol | 442 | 209 | 432 | 8 | 2 |

The compiled `.text` section is **444 bytes**, including a separate two-byte
`c046` alignment instruction **outside** the 442-byte function symbol. Those
external bytes are neither target nor function credit. The two-byte symbol
overrun and the two-byte external section alignment are different facts. The
ROM target endpoint is not extended to accommodate either.

The target has one referenced literal, `0x00000103` at 080E0350, and skipped
zero alignment at 080E034E. The compiled body has referenced words `0x00000101`
at 080E0264 and `0x00000103` at 080E0358, with skipped zero alignment at 080E0262.
All body bytes are accounted for independently of the section alignment.

The first positional difference is at function offset 4. The ROM preserves the
payload in r5 and first compares phase 0x100; the compiled body preserves it in
r6 and first compares a literal-loaded 0x101. Dispatch branches, register
allocation, subsequent offsets and some arithmetic lowering differ. A positional
comparison against only the true 440-byte target finds 38 identical byte
positions and 5 identical reached instructions at the same addresses. These are
not an LCS similarity score or a semantic-equivalence claim. The retained JSON
enumerates every differing byte, including the two excess symbol bytes with no
target counterpart; complete separately decoded bodies are retained as text.

Seven `R_ARM_THM_CALL` relocations resolve to exactly four qualified targets:
080E06A4 once and 080E0608/080E064C/080E0690 twice each. The linked ELF has no
residual relocations or undefined symbols and owns one complete Thumb function.
The unchanged stack-argument buffer CFG check accepts both byte arrays under
the same three interpolation-leaf dependencies. Its fingerprint is
`0c20abb736f5b160a811ea42035c8a7d079cd352244391a6de0b18ef445a66b5`.
That structural check does not waive the canonical exact-span condition, which
correctly fails. There was no mapping enlargement, verifier edit or profile bypass.
The narrow source plausibility check reports no findings.

## Recovered contract and limits

The compatible interface is a three-pointer, full-zero-return callback. State
contains phase at +0 and input-record pointer at +4. The 0x4C payload holds eight
halfwords, three output pointers, and two three-element signed64 arrays at +0x1C
and +0x34. Ordinary agbcc/APCS alignment supplies this layout; exact original
nominal typedefs are not established.

Phase zero copies the parameters without advancing phase. Phase 0x100 narrows
the signed endpoint sum before its arithmetic right shift, then narrows the bias
addition. Fixed-point values and coordinates preserve signed64 scaling, including
signed32 `count - 1`: count zero yields a final coordinate of -65536. Phase 0x101
unconditionally samples the middle output, then selects optional linear stages
from freshly reloaded pointers. Linear stages write endpoint zero and perform
at least one step/store/test iteration with a wrapping u16 index. Count one still
writes output index one; duration is signed16 `count - 1`. No guards or repairs
were added to these behaviors.

080E06A4 remains **Parked**, not a matched dependency. Its compatible five-argument
ABI is grounded in ROM and independent inventory, not recursive sampler proof.
Pointer validity, buffer capacity, aliasing/lifetime contracts, upstream scheduling,
signed64 callee behavior and termination for malformed durations remain external
obligations. Counts 0/1/2 do not provide three strictly increasing spline
coordinates. This preserved candidate is plausible recovered source, not proved
behavioral equivalence for all inputs or proof that no natural exact source exists.

## Retained evidence and separate metadata

Only this README and `080E0240.c` are the proposed Parked payload. Detailed local
evidence remains in the author bundle, not in paths relative to an integrated
Parked directory:

- `/home/user/.codex-work/ffta-ulw/080E0240-author-next/HANDOFF.md`
- `/home/user/.codex-work/ffta-ulw/080E0240-author-next/ABI.md`
- `/home/user/.codex-work/ffta-ulw/080E0240-author-next/freeze.json`
- `/home/user/.codex-work/ffta-ulw/080E0240-author-next/compile-start.json`
- `/home/user/.codex-work/ffta-ulw/080E0240-author-next/canonical.log`
- `/home/user/.codex-work/ffta-ulw/080E0240-author-next/elf-capture.json`
- `/home/user/.codex-work/ffta-ulw/080E0240-author-next/verification.json`
- `/home/user/.codex-work/ffta-ulw/080E0240-author-next/DISASSEMBLY.md`

The separate `metadata.patch` corrects only the target's JSON/text instruction
count 220 -> 210 and legacy symbol size 18 -> 440. Its endpoint stays 080E03F8.
These ROM-inventory corrections receive no source-match credit. Other targets,
including DFF8C, are not changed by this author patch. Root owns any integration,
mapping-bound report refresh and lease release.
