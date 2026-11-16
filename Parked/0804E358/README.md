# 0x0804E358 - near miss (98 bytes): byte-identical only with a do { } while (0) once-loop

Retry of Parked/0804E358 (96 bytes) on 2026-11-16, kit fcdf2d45, default flags.

The source in this directory compiles to the target's 98 bytes (MATCH - byte identical, 41/41 instructions, report elf-symbol-thumb-data-v1,
plausible.py clean) but only with the clamp body wrapped in a `do { } while (0)` statement macro, CLAMP_SELECTION(saved, count, rows), used once.
The wrapper's only effect is that the loop notes double the reference weights inside it, so the global allocator ranks the `top` pseudo above
`count`. Without it the same statements give a 7-instruction register swap (34/41, 91/98 bytes: count in r1, top in r2; the ROM has them the other
way round) and nothing else.

Not shipped: a once-loop that only changes loop-depth weighting steers the compiler (policy question: kit #191), and a statement macro ships only
with shared text (the same text reproduces a second function) or as a verbatim copy of a real ROM function; this one is used once and has neither.

Legitimate part (keep): `rows = 6` assigned in each arm of the `group == 4` test next to the count call. With two reaching definitions the
constant folds into `adds r0, r1, #6` but not into `cmp r2, r4`, as in the ROM (a single assignment folds to cmp #6 and 96 bytes). Callers pass
only 4 and 5 (func_0804D7E8, func_0804D840): two list kinds each with its own row count. `u16 top; u16 selected;` from ldrh without sign
extension (src/08050AF4.c declares `top` s16 for the same table at 0x53C).

Ruled out (each keeps the register swap or changes the code): switch instead of if/else; reversed comparison operands; nested ifs; early return;
u16 count or rows; s32 rows (bhs becomes bge); one `rows = 6` after the join (96 bytes); `rows = 6` before the count call in each arm (moves
movs r4, #6); keeping the first call's result as the initial count; for (i = 0; i < 1; i++) (loop survives, 108 bytes); while (cond) { ...; break; }
(different registers). Declaration order of count/rows does not matter.

Open idea: the two arms may be two inlined list-kind helpers (each returning its count and row limit), or the clamp may be an inlined function
shared with another list screen - look for the same clamp sequence in unmatched neighbours; either would supply the shared text the macro lacks.
