# 0x080DD5A8: positive selected signed-field predicate

**NOT MATCHING.** The recovered natural C has the correct complete 66-byte Thumb symbol, but its instruction scheduling is not byte-identical. Keep it outside `src/` and do not count it as a match.

## Behavior and layout

The input is a readable object pointer in r0. A halfword of flags is at +0x0C. Bit 7 gates the predicate. When enabled, bit 0 selects signed halfword +0x1E; otherwise bit 1 selects signed halfword +0x20. The function returns 1 exactly when the selected field is greater than zero, or 0 when disabled or neither selector is present. Bit 0 has priority even when both selector bits are set and the first field is nonpositive. Other flag bits are ignored. The object is not modified.

The source's minimum local view is 34 bytes, with explicitly unidentified bytes before the evidenced fields. The signed-byte return reflects low-byte signed normalization at caller 0x080E3B4E; the 0/1 machine return alone does not prove a historical C typedef or wider return declaration.

## Exact unresolved difference

Compiler: `/home/user/agbcc/gcc/agbcc -mthumb-interwork -O2`, preprocessed with `cpp -nostdinc -undef`. Original ROM SHA-1: `4ac05441f4de70a4ec3dd932116346c61b8783d9`.

The final source emits `movs r3, #0` at +0x04. The ROM emits that instruction at +0x0A, after the halfword load, right shift and `movs r4, #1`. Moving that single instruction in the decoded list produces the exact target list; all other 32 instructions, including registers and branch destinations, agree. The complete ELF function is 66 bytes, has no relocations or emitted helper symbols, and passes the leaf CFG check. The `.text` section's following two-byte assembler alignment is not owned by the function. The ROM interval `[0x080DD5A8,0x080DD5EA)` owns no literal pool or alignment bytes.

The retained full author bundle is `/home/user/.codex-work/ffta-ulw/080DD5A8-author-substantial/`. Its `ready/Parked/080DD5A8/match-report.md` retains the canonical **NOT MATCHING** report, and its `exact-diff.txt` retains the instruction-level difference. These are external evidence artifacts, not required adjacent files in a minimal shared `Parked/080DD5A8/` containing only this README and `080DD5A8.c`. The unresolved instruction placement is fully described above. The report's instruction-alignment statistic is 32/33 and 64/66 bytes; that is not a byte-identical match or a same-offset byte count.

Parked source SHA-256: `db58c09cc753aebb986498eab8a8fef3fbe096ecf523f0cada876996846e48d0`.

Documentation-only post-review correction: the parked source now includes the exact 66 target bytes in its existing address comment. Its comment-stripped text is byte-identical to frozen `candidate-4.c`, SHA-256 `67e8e78c2830a69e5ad202d3bd3816a156ed9d5a8e9a62b5310f2816d7b759c7`. The frozen candidates, chronology and function body remain unchanged. All compilation and runtime evidence below applies to that frozen candidate; the retained source-bound report was not regenerated for the comment-annotated copy. No compilation, matching or new candidate iteration occurred after the claim was released.

## Evidence-backed source attempts

1. A direct local bit-7 boolean followed by signed-field selection produced 58 bytes. The compiler collapsed the materialized predicate.
2. One inline helper with conditional early returns produced 68 bytes and a duplicate flags read.
3. A raw-bit getter plus a comparison-return predicate produced 66 bytes with r2/r3 exchanged and different result initialization placement.
4. The same raw getter plus an initially-false helper result, conditionally assigned true, produced the current 66-byte candidate with only the scheduling difference described above.

These helpers are grounded in neighboring ROM bodies: `[0x080DD574,0x080DD57E)` is a raw bit-7 getter, and indexed `[0x080DD580,0x080DD598)` is a normalized comparison against one. The target and adjacent negative predicate contain that normalized gate. The first body's start is missing from the function index; this task does not repair another address. Exact historical helper signatures, original inlining boundaries and local declarations remain hypotheses, although the observed helper operations and target semantics are directly decoded. No alternative flags, volatile access, assembly, pragmas, padding tricks or arbitrary declaration-order search were used.

## Validation and limits

- Strict native GCC with ASan/UBSan: 400 cases pass; static layout checks verify offsets 12/30/32 and size 34. Cases combine all enable/selector states, ignored flag bits, and each pair from `-32768, -1, 0, 1, 32767`. Twelve cases distinguish bit-0 priority from fallback/OR behavior; object bytes remain unchanged.
- Unicorn: 400 executions each of the actual ROM body and final compiled body pass the same oracle. All 33 instructions are covered in each body; selected field reads, no object writes, preserved r4-r11/SP and only the expected stack-save writes are checked.
- Two scout entry-to-call witnesses were freshly checked against ROM instruction edges: caller 0x080E3AC8 at 0x080E3B4E, and caller 0x080E6D54 at 0x080E6D8E. Both supply an object pointer and consume the low byte as a boolean. This proves structural call paths, not full caller execution or exhaustive incoming references.

Six fixed target compiler invocations were made across four frozen source candidates: four canonical matches and direct ELF replays of candidates 1 and 4. One native compilation was performed. A verification-script instruction-index assertion was corrected without changing the source or recompiling it; the corrected verification reused the captured ELF.

No exact match is claimed. Further progress requires evidence about the unresolved original source structure or toolchain scheduling, not inserted work to force byte order.
