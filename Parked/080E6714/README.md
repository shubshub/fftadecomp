# 080E6714 — preserved first candidate, NONMATCH

This is an unchanged natural C recovery attempt, not a matched implementation.
One frozen candidate was compiled once with the canonical agbcc toolchain,
literal compiler spelling `$HOME/agbcc/gcc/agbcc`, flags
`-mthumb-interwork -O2`, and no profile override. The canonical main return,
SystemExit value and observed process exit were all 1. Source plausibility
passed without findings or waivers. No source revisions, alternate flags,
second target compilation or native campaign followed the result.

## Complete extent and exact differences

The qualified ROM body is [080E6714,080E691A), 518 bytes:
208 reached instructions / 458 code bytes, 56 referenced literal bytes and
four internal zero-alignment bytes. The two bytes at 691A..691C are external
alignment and are not owned by this function.

The genuine complete compiled ELF symbol is 528 bytes:
215 reached instructions / 472 code bytes, 48 referenced literal bytes and
eight internal zero-alignment bytes. Its entire .text is exactly 528 bytes;
there is no external compiled section alignment to subtract. The ten-byte
symbol overrun is therefore real, not padding credit.

At identical offsets within the owned 518-byte ROM body, 22 bytes agree and
496 differ; only one reached instruction is byte-identical at the same
address. All differences and the ten overrun bytes are retained in
`/home/user/.codex-work/ffta-ulw/080E6714-author-next/verification.json`.
The large positional difference reflects shifted code and pools, not a
measured semantic error rate.

Observed structural differences include an extra r8 save/restore, an early
RAM-shadow pointer load kept in r8 across calls, changed pool placement and
table-address reuse, different registers, and branch-based old-pointer
Boolean normalization instead of the ROM's negate/OR/shift sequence.
The compiled frame has 16 local bytes and 24 saved-register bytes; ROM has
16 local and 20 saved. These observations do not justify source steering.

The canonical report expands its ROM comparison window to 528 bytes because
that is the compiled symbol size. Its last ten ROM bytes are external
alignment plus the beginning of the next function. Its 438/528 byte metric is
an LCS diagnostic, not positional equality; 134/194 instruction text matches
use ROM decoding sampled at compiled instruction offsets, not the true
208-instruction ROM CFG. The original report is retained unchanged, but the
complete owned-body counts above are authoritative for this preservation.

## Recovery model and limits

The callback has a compatible u32(void*,void*,void*) ABI and returns zero.
Local views express observed descriptor fields and the registered 0x38-byte
payload; unknown storage remains unknown. It narrows descriptor halfwords,
preserves ordered child creation and post-call reloads, performs cleanup only
when the sequence changes from nonnull to null, short-circuits live-child
polling, and does not poll the child stored at payload+34.

DD748's fourth argument is an optional s16* output, NULL here. Its nested
-2 path invokes DE268; it is not a pure getter or an integer-mode contract.
Variant-derived table accesses remain unguarded as in ROM. No bounds,
allocation success, scheduler copying, object validity, initialization or
asynchronous lifetime guarantee is invented.

Both captured original and linked ELF files are retained losslessly as hex.
The original has 21 genuine R_ARM_THM_CALL relocations naming 17 indexed
targets; the linked image has no residual relocations or undefined symbols.
Default ordinary framed/direct-call CFG validation passes, and the call-target
multiplicities agree with ROM. This uses the profile's external ARM ABI
assumptions, not recursive callee validation or proof of semantic equivalence.
No original nominal typedef or all-input safety claim is made.

## Retained evidence and integration scope

Integrate only this C file and README into `Parked/080E6714/`.
The failed report is diagnostic evidence, not a ready match report. No shared
source, header, status, toolkit or metadata changes are part of this payload.
Root had already applied the independently approved metadata before the
private snapshot; this lane copied it unchanged and proposes no new repair.

Retained author bundle:
`/home/user/.codex-work/ffta-ulw/080E6714-author-next/`.
Its `ABI.md`, `freeze.json`, `compile-start.json`, `compile-1.log`,
`process-exit.txt`, `elf-capture.json`, `CAPTURE-DISASSEMBLY.md`,
`verification.json`, `HANDOFF.md` and `SHA256SUMS` preserve the rationale,
precompile chronology, full raw objects, complete reached-body evidence,
input bindings and seals. The canonical failed report remains at
`/home/user/.codex-work/ffta-ulw/080E6714-author-next/isolatedroot/docs/match/080E6714.md`.

One attempt demonstrates this candidate's nonmatch, not impossibility of a
future honest recovery. The parent owns independent review and claim release.
