# 080E5310 — preserved first natural candidate, NONMATCH

One canonical compile with the unchanged default compiler spelling
`$HOME/agbcc/gcc/agbcc` and fixed `-mthumb-interwork -O2` returned **1**:
`NOT MATCHING - bytes differ`. Source plausibility passed. The sole candidate
is preserved without any postcompile source/type/flag/order revisions; no native
campaign or second target compile ran. It is not eligible for `src/` or credit.

## Exact owned difference

The ROM owns `[080E5310,080E5438)`: **296 bytes / 114 reached instructions**,
partitioned into 256 code, 36 referenced literal and 4 internal alignment bytes.
The sole original and linked ELF function symbols are also **296 bytes**, with
`.text` exactly 296 bytes and no external filler. The candidate has **117 reached
instructions**, 262 code bytes, 32 literal bytes and 2 alignment bytes. Neither
comparison includes the next function or claims equal sizes imply a match.

At identical owned byte positions, **31 bytes agree and 265 differ**; no target
byte is missing and no compiler tail extends outside ownership. The first
difference is E5310: target `70b5` saves r4-r6/LR, candidate `f0b5` saves r4-r7/LR.
Both allocate sixteen local bytes; saved state is sixteen versus twenty bytes.

The candidate holds the RAM-shadow address in r6 across the switch and uses r7
for the descriptor; the target uses r6 for the descriptor and loads the shadow
address separately on the two reached paths. The candidate has one 03000940
literal at E5330 instead of the target's E53C0/E5434 pair. It explicitly narrows
the selected u16 mask result with two shifts after each 035A8 call; those shifts
are absent in the target. These differences change branch/call displacements,
register operands, pool placement and alignment. They are observations of the
frozen output, not a proposal to switch types or rearrange source to seek a match.

The canonical report's `241/296 bytes` is its sequence-aligned byte comparison,
not equal-position identity. Its `69/106 instructions` display decodes ROM at
candidate instruction coordinates and can decode target pool bytes as code.
The complete CFG-aware counts above and retained DISASSEMBLY.md supersede those
display counts for ownership analysis; the raw canonical report is unmodified.

Fourteen original `R_ARM_THM_CALL` (type 10) relocations bind to thirteen genuine
indexed targets. The complete linked ELF has no residual relocations, undefined
symbols, extra function bodies or other nonempty allocated sections. Ordinary
framed verification passes for both complete bodies. That is structural ABI
evidence, not byte identity or recursive callee/runtime equivalence.

## Recovered behavior and limits

The compatible callback takes full task, descriptor and payload pointers and
returns u32 zero. The unsigned descriptor phase controls phase 0 creation and
phase 100 polling; phase 1 and other values do nothing locally. Phase 0 preserves
the creation/store order and does not advance phase. Polling stores each result
and short-circuits after D3F08, D4774 and D4D2C. Every tick that gets past those
three clears the halfword RAM shadow mask before D6134 and D9B64 polling. Both
later null results set phase 2. The +28 record child is created but not polled.
D9B64 remains effectful on its busy path; D6134 is not given invented null safety.

The 2C-byte payload layout keeps its first 14 hexadecimal bytes opaque, and its
six pointers at +14..+28. Passing payload+4 does not establish an original array
type or nested buffer safety. Actual ROM record addresses remain opaque numeric
const pointers; no named-data mappings, object sizes or selector bounds are
invented. Original nominal scalar signedness/typedefs remain nonunique where
only widths or low bits are observed. Scheduler initialization, allocation,
copying, lifetime and all ordinary external-call assumptions remain explicit
limits; no omitted initialization or guard is supplied.

## Provenance

Only this C and README are the proposed integration payload. Full retained
evidence is under `/home/user/.codex-work/ffta-ulw/080E5310-author-next/`:
`ABI.md`, `freeze.json`, `compile-start.json`, `canonical.log`, `elf-capture.json`,
`DISASSEMBLY.md`, `verification.json`, and `isolatedroot/docs/match/080E5310.md`.
These are absolute retained-bundle references, not adjacent integration files.

- Frozen C SHA256: `18fed0663c03c2864c460012317927cf74ace7cf16f5105f1e5745054ff5488b`.
- Source plus nine-header fingerprint: `b5662c80aa48f3bb14786a41cce4170881554f7f08d2f8a28d8a22118f302d68`.
- Freeze at `2026-10-24T12:39:38.575324+00:00`; explicit compile start at `2026-10-24T12:39:46.665285+00:00`.
- Complete raw original ELF: 1524 bytes, SHA256 `8485255c186350fdd7d6b917d1849cfe8ba16fda2df19ce72c8c1187a2955bf1`.
- Complete raw linked ELF: 2000 bytes, SHA256 `343a5ef2fc0000cd59f089850542fd2f06e800b40d1c1cdf5c7386dd018ef077`.
- Canonical diagnostic report SHA256: `58683a373ad6e041caf8e268ecbd8882dbad5634e0a0c7b9a47c1c49a571291d`.

Both raw ELF images, all section data, symbols and relocations are retained as
text in elf-capture.json. Passive observation does not replace tool functions;
canonical main, SystemExit, observer and shell process all report 1. Generated
binary artifacts were removed by the canonical temporary-workspace cleanup and
their absence was checked. Root owns independent review, metadata, release and
publication. This attempt earns zero matched-source credit.
