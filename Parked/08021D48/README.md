# 0x08021D48 - near miss (78 bytes): 76 compiled; GCSE removes the third flags reload

Retry of Parked/08021D48 on 2026-11-16, kit fcdf2d45, default flags. match.py: 'compiled symbol is shorter than the indexed span: 76 < 78';
plausible.py exits 0. Not shipped: not byte-identical with the project's fixed flags. The source here is the parked C unchanged (three
conditional negations of *first written `*first *= -1`; flags as plain u32 masks, as the matched siblings 08021D14 and 08021DA8).

Remaining difference: the ROM reloads the flags word a third time (ldr r0, [r4] at 0x08021D7C); this build reuses the second load from r1, which
also swaps the registers of the second and third tests.

Cause: GCSE. The same C compiled with -fno-gcse (a diagnostic only) is instruction-for-instruction the target: `match.py --flags
"-mthumb-interwork -O2 -fno-gcse"` prints MATCH - byte identical (39/39), which does not count because the flags are fixed (match.py accepts any
--flags, kit #130). The gcse dump: PRE: redundant insn 60 (expression 2) in bb 4, reaching reg is 48; PRE/HOIST: end of bb 2, insn 82 - PRE
treats the store to *first in the second if-body as not clobbering object->flags and hoists the third load. Not strict aliasing
(-fno-strict-aliasing still removes it). PRE treats the first if-body differently from the second although both compile to the same RTL - next
step: read pre_lcm / compute_transpout in agbcc gcse.c to see what the original source did differently. Ruled out: bitfield flags (ldrb / lsl #26
/ bge, different allocation); only two tests (the second reload survives - the pattern appears only on the third test).
