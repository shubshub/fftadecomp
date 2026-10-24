# 080E7D20 — preserved NONMATCH

One natural candidate, frozen before one canonical compile with the literal
default `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`. No source/type/order/flag
retry, manual link, native campaign or match credit. The C here is byte-for-byte
the frozen candidate, including the complete target-byte comment.

## Exact result

| Complete ownership | ROM target | Compiled candidate |
| --- | ---: | ---: |
| Start | 080E7D20 | 080E7D20 |
| Exclusive end | 080E7F4C | 080E7F38 |
| Symbol bytes | 556 | 536 |
| Reached instructions | 227 | 223 |
| Code / literal / alignment bytes | 488 / 60 / 8 | 480 / 52 / 4 |

Within the true 556-byte target, 155 bytes agree at the same offset, 381 differ
and 20 are absent. No excess bytes or external section filler receive ownership
credit. The first difference is offset 2. These are positional comparisons, not
an aligned/LCS score; no canonical comparison report was produced.

Actual process exit was 1. `main` was observed returning `None` while unwinding
the string-valued `SystemExit`: `compiled symbol is shorter than the indexed
span: 536 < 556`. This is not a normal successful `main` return.

The canonical pipeline did reach linking: it compiled the object, resolved its
17 `R_ARM_THM_CALL` sites to 16 indexed Thumb targets, checked the linked code,
then rejected the short symbol after workspace cleanup. Full original (1976 B)
and linked (5004 B) ELF images were passively captured from that invocation.
Both `.text` sections and function symbols are exactly 536 bytes; the linked
ELF has no remaining relocations, undefined symbols or extra allocated payload.
No second linker or compiler invocation was used to produce this evidence.

Observed differences include saving r4-r7/LR rather than also saving r8/r9,
different register/pool placement, folding the record flags to 0x0C/0x14,
different old-resource boolean normalization, and explicit halfword narrowing
of the declared u16 mask result before clearing RAM. These observations are
diagnostics, not authorization to change the frozen types or chase instructions.

## Plausibility and semantic limits

Canonical plausibility was not reached. A separate existing plausibility check
returned 1 with **ten unwaived SUSPECT `rom-address` findings** for numeric ROM
table-base initializers. No automatic plausibility approval, data-symbol
invention or waiver is claimed. Those literal table bases are observed ROM
evidence, but that does not override the source gate.

The candidate preserves the full-word zero callback return, three full-pointer
inputs, observed descriptor/payload offsets, signed coordinates, effectful
DD748 call with null optional third-coordinate output, unchecked selector,
phase/call order, old-resource-nonnull/new-null conditional mask clearing,
resource reload before continuation, ordered short-circuit polls, low-byte
two-slot completion test, and unpolled record child. No initialization or guard
was added. Original nominal types are not uniquely recovered; valid layouts,
selectors, storage, allocation results, phase ordering and retained-pointer
lifetimes remain assumptions. Opaque callee ABI evidence is not recursive
equivalence or a runtime proof. No future-impossibility claim is made.

## Provenance

Frozen source SHA256:
`5498cb87fe761c7e81eebe15c4360028b0f36f996efbbd388d1ff405d025f361`.
Source plus nine-header fingerprint:
`e583bc030f72257268e9ce5b77407ea144f785efeccc3324fb4c4c941e1d7b26`.

Evidence bundle:
`/home/user/.codex-work/ffta-ulw/080E7D20-author-next`.
`ABI.md`, `freeze.json`, `compile-start.json`, `canonical.log`,
`elf-capture.json`, `COMPILED.md`, `verification.json` and `plausibility.log`
retain pre-output decisions, chronology, genuine ELF/assembly, exact differences
and the separate source-gate findings. `SHA256SUMS` binds the complete bundle.
