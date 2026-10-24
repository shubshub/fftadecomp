# 0x080DC414 — PARKED, not byte-identical

Recovered C: `080DC414.c`, SHA-256 `cfd948553768ae3e68a4d79ead1ed631b82a9d7745abb9b6f017d98b4cfa14c1`.

Only `080DC414.c` and this `README.md` are intended for integration under `Parked/080DC414/`. Supporting evidence remains in the retained author bundle, not beside the integrated files.

The two-byte output aggregate candidate is plausible and compiles with fixed agbcc `-mthumb-interwork -O2` to a complete 132-byte Thumb symbol, but **is not a match**. The retained report at `/home/user/.codex-work/ffta-ulw/080DC414-author-substantial/Parked/080DC414/match-report.md` records NOT MATCHING with the tool's similarity metric 104/132; a direct same-offset comparison finds only **27 equal byte positions and 105 differing positions**. The similarity metric must not be interpreted as positional equality.

## Precise difference

The ROM saves `r4-r6,lr`, keeps source/destination/selector in `r4/r5/r6`, passes two adjacent local output bytes, and recomputes the second byte's stack address when reading it. The compiler saves `r4-r7,lr`, retains the aggregate base in `r5`, keeps destination/selector in `r6/r7`, and later reads `[r5,#1]`. This changes register operands and call displacements. Its return is two bytes earlier, followed by two zero alignment bytes before the shared literal at `0x080DC494`.

- Target: 53 instructions, 128 code bytes + 4-byte owned literal, total 132.
- Candidate: 52 instructions, 126 code bytes + 2 internal alignment bytes + 4-byte literal, total 132.
- Both preserve the four-byte local frame, eleven direct call occurrences, their order, the optional palette branch, signed/unsigned conversions, and `0x03003A60` literal. There are no unresolved linked relocations or external alignment bytes credited.

## Attempts and limits

1. Initial independent scalar-byte locals, frozen before compilation: plausible, NOT MATCHING, tool similarity 101/132. It retains the second local's address across calls.
2. One justified structural revision to a two-byte aggregate after independently reading the second caller `080DC34C`, which passes adjacent bytes at `SP+0x18/+0x19` to the same getter and later consumes them through the same setters. The full rationale remains at `/home/user/.codex-work/ffta-ulw/080DC414-author-substantial/REVISION.md`. This did not resolve the mismatch.

There were three agbcc invocations: one per candidate and one unchanged candidate-2 ELF audit. No flag search, declaration reordering, register tricks, volatile, inline assembly, attributes, warning suppression, or extra array/struct spelling campaign. No further semantic defect was found to justify another revision.

The default verifier's stack-alias rejection is **not** a blocker: the canonical stack-buffer fallback passes both ROM and compiled C. Dependencies are `0801133C`, `08021DA8`, and `08099C04`. Their proof fingerprint is `eacfe957e11c074c4549959ac6ea8aced37e54c501fe2af72a58fef276c26ed7`.

The original public return type of `08099BF4` remains unresolved between `u16` and `u32`. Its ROM zero-extends the low sixteen bits before returning; that proves the returned value width, not the original C declaration. This candidate locally declares `u16`, an inference rather than a recovered public signature. The caller then sign-extends those low sixteen bits for `08011150`; no type or source change was made during review.

## Actual preconditions

Source `+0x44` points to a nested object. Its flags must contain `0x40`: actual `08021DA8` otherwise returns zero without writing either output byte, while this caller unconditionally reads both locals. No default initialization was invented. Native tests exercise valid cases and separately demonstrate the callee's no-write path; they do not call this routine with uninitialized outputs.

The nearby bounded scout found no incoming use of `080DC414`; reachability and satisfaction of the flags precondition by real callers remain unproven. Entry, extent, body, and local ABI evidence are strong, but no caller claim is invented. CpuSet is treated as a BIOS ABI call; its implementation and live hardware effects are not emulated.

This source must remain under `Parked/`, never under the shared game's `src/` or counted as matched. The separate ROM-derived size proposal remains at `/home/user/.codex-work/ffta-ulw/080DC414-author-substantial/metadata.patch`; it is not part of the C-plus-README integration payload or a match claim.
