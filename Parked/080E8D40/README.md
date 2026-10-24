# 080E8D40: first natural candidate, NONMATCH

Preservation only. Do not place this source in `src/` or count it as matched.

## Attempt and exact difference

One frozen natural C candidate was compiled once with the default literal
`$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2` and the ordinary canonical matcher.
No source, type, spelling, ordering, flag or register retry followed. The
source is unchanged from the precompile freeze. No native campaign ran.

The canonical main returned 1, SystemExit carried integer 1, and the observed
process exited 1. Typed linking and complete framed structural checks passed.
Canonical source plausibility was reached and said **plausible**, but the
verdict is **NOT MATCHING - bytes differ**. Plausibility is not equivalence.

| Measurement | ROM target | Compiled candidate |
| --- | --- | --- |
| Complete owned extent | 508 bytes, E8D40..E8F3C | 512-byte ELF symbol |
| Reached instructions | 207 | 209 |
| Code / literals / zero alignment | 460 / 44 / 4 bytes | 464 / 44 / 4 bytes |
| Fixed local / saved frame | 16 / 24 bytes | 16 / 24 bytes |
| Direct BL sites / unique targets | 23 / 22 | 23 / 22 |

At the same offsets within the genuine 508-byte target, 405 bytes equal and
103 differ; 152 of the target's 207 reached instructions have identical bytes
at the same address. The compiled symbol exceeds ownership by four bytes.
Its extra tail is `40090003`, the relocated-position shadow-address literal.

The canonical display reads 512 ROM bytes because the complete compiled
symbol is 512 bytes. Its final four ROM bytes `f0b54746` belong to the NEXT
entry, not this target. The report's 484/512 aligned-byte and 181/205 linear
instruction metrics are not same-position or owned-body equivalence measures.
No outside-owned byte earns credit.

Concrete remaining differences include the phase-zero selector choice and
wrapper register/load ordering, and two extra halfword-narrowing instructions
after 035A8 at compiled E8EEA/E8EEC. These shift the following cleanup code and
final literal by four bytes and change affected branch/call encodings.
The u16 local declaration for 035A8 is a compatible hypothesis, not proof of
the original public return type; a zero-extended ROM return alone does not
resolve u16 versus a wider return containing a narrow value. No alternate
declaration or source was tried. No unique original source or general
unmatchability claim is made.

## ELF and source evidence

The complete original 2164-byte ELF and linked 5176-byte ELF are retained as
hex in the author evidence bundle. Both .text sections are exactly 512 bytes,
with one complete target function and no external section-alignment bytes.
All 23 original relocations are real R_ARM_THM_CALL sites bound to the 22
indexed Thumb targets. Linked output has no residual relocations, undefined
symbols, veneers, extra helper, data section or linker-added text. The exact
call-target multiplicities agree with the ROM. Captured assembler text,
full sections/symbols and complete reached disassembly remain in the bundle.

Source SHA256:
`c807f34c78f740f520695d2be0b0077b4fd8be330d8e09d23be58ae10a41e41c`.
Source plus all nine headers fingerprint:
`19bd1eff7655fb4c3ee8f561e50f97c36ae813d2e056ca9c07018eb579642c38`.
Canonical NONMATCH report SHA256:
`57c675ba68bf935d2ecd1454c1e24671bb0f58994d47b6c22baf1b336b72f67e`.
Approved ROM SHA1: `4ac05441f4de70a4ec3dd932116346c61b8783d9`.

Author bundle: `080E8D40-author-next`. `ABI.md`, `freeze.json`,
`elf-capture.json`, `verification.json` and `CAPTURE-DISASSEMBLY.md`
bind provenance, headers/maps/tools, chronology, complete ELFs and exact
owned differences. The passive observer's optional cc/flags local fields are
None because those locals do not exist at compile_object entry. The captured
actual command, canonical log/report and freeze preserve the fixed compiler
and flags independently; the observer was not changed or rerun.

## Recovered behavior and remaining assumptions

This is a fullword-zero callback with task/descriptor/payload pointers and a
52-byte payload view. Entry provenance is the D3508 selector 0x22 table slot
083948E0 with pointer 080E8D41 and size 52, not observed runtime execution.
Selector zero also enters the registrar's low arm; no lower-bound guard was
invented. Types and member names describe offsets, not recovered original names.

Phase 0 stores the selector byte/wrapper and creates the initial child via
E03F8 selector 1. That callee's selected branch does not dereference its NULL
coordinate argument. This external ABI use is not admission of E03F8 source
or proof of its nested callbacks, allocator or lifetimes. Phase 1 calls D38B4.
Phase 0x100 waits for E05DC, then runs the effectful low-byte D8858 gate;
success obtains coordinates, creates children in ROM order, sets timer 150,
and uses low-byte DD580 to choose phase 0x101 or 0x102. Phase increments
reload descriptor state after calls. DD748 forwards its -2 side effect;
its fourth argument is an optional coordinate-output pointer, not a scalar.

Phase 0x101 decrements a u16 timer with wrap and creates optional coordinate
and record children at zero. Phase 0x102 short-circuits sequence, repeatedly
clears the shadow mask when reached, polls effectful D9B64, optionally releases
a child, then polls coordinate and effect children before phase 2. D9B64's
busy path writes a payload byte; no pure-poll substitution was made.

Skipped phases can leave child slots and unknown storage without initialization
by this callback. In particular skipping phase 0x101 leaves the coordinate
slot requiring externally valid storage, while D6134 has no NULL guard.
No guard, zero initialization, allocator success, valid selector, lifetime or
recursive-callee guarantee is added. The record pointer at +0x30 is unpolled
and may be overwritten without cleanup here. Literal operands are evidenced
addresses, not proof of full data extents. No runtime-equivalence test was run.

The already coordinator-approved target metadata was copied unchanged.
No additional metadata change is proposed. Only this C/README pair is the
preservation payload; the diagnostic report is not a matched-source report.
