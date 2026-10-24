# 08145388: preserved natural candidate, not matching

One frozen candidate was compiled once with fixed `agbcc -mthumb-interwork -O2`.
Canonical plausibility passes, but the complete symbol is **44 bytes / 18
instructions**, compared with the genuine ROM body's **40 bytes / 16
instructions**. This source is not eligible for `src/` or match credit.

The recovered side effects are a signature guard at +34, copying the unsigned
16-bit argument into +26 then +24, setting +28 to 2, and clearing bit 31 of the
word at +04. Unknown byte arrays describe unmodeled object storage at measured
offsets. The void result is an ignored-result model, not proof of the original
return type. No caller was found in the retained bounded inventory scan.

## Exact difference

- agbcc emits `push {lr}` and ends with `pop {r0}; bx r0`; ROM uses no stack
  frame and returns directly with `bx lr`.
- The compiled normalized halfword value is in r3 and the signature in r1;
  ROM uses r1 and r3 respectively. Stores and comparison operands differ
  accordingly, without changing the recovered field operations.
- Extra return machinery shifts code from 32 to 36 bytes and the identical
  two-word literal pool from +0x20/+0x24 to +0x24/+0x28. Branch and literal offsets
  also shift. The complete compiled symbol has no relocations or external
  `.text` padding.
- At identical offsets within the true 40-byte target, 2 bytes agree; 38
  differ, and the compiled body has 4 additional bytes. Retained JSON lists
  every differing or extra byte. The matcher's displayed 32/44 alignment
  score is not raw equality or ownership credit: its 44-byte ROM diagnostic
  extends four bytes into the following function at 081453B0.

The struct offsets, halfword narrowing, guard, store values and mask are
supported by the instructions. No semantic correction was identified to
justify a new candidate. No return-type, spelling, cast, register-order,
compiler-option or source-order search was attempted. Native behavior tests
were not run because the single canonical attempt did not match.

## Retained evidence

Only this C file and README are proposed for Parked preservation. All other
evidence stays in `/home/user/.codex-work/ffta-ulw/08145388-author-next/`:

- `first-match.log`: canonical NOT MATCHING result and aligned disassembly.
- `comparison.json`: true 40-byte target, complete 44-byte candidate and exact
  raw byte differences, with following-function bytes explicitly excluded.
- `elf.txt`, `results.json`: complete ELF ownership and source/header bindings.
- `EVIDENCE.md`, `freeze.json`, `CHRONOLOGY.md`, `HANDOFF.md`: rationale,
  pre-compilation freeze and bounded attempt history.

These names refer to that explicit retained bundle, not paths relative to an
integrated Parked directory. The private corrected target span includes both
owned literal words; shared metadata integration remains coordinator-owned.
