# 0x080051C4 - near miss (340 bytes): 332 compiled; a second pseudo for the source pointer in the dictionary branch

Retry of Parked/080051C4 on 2026-11-16 (diagnosis only, no new shapes tried), kit fcdf2d45, default flags. The source file here is the parked C
unchanged; match.py: 'compiled symbol is shorter than the indexed span: 332 < 340'; plausible.py exits 0. Not shipped: not byte-identical.
Index [0x080051C4, 0x08005318) correct; data_03002BB0 / data_03002BB8 exist. The matched siblings src/08005318.c and src/080053D4.c declare both
globals u32, and src/08005318.c declares func_080051C4 as returning s32 - not yet adopted here.

Remaining differences: (1) frame 12 vs 8 - the ROM saves the advanced source pointer at [sp,#8] before the dictionary-copy loop (0x080052BA) and
reloads it after (0x080052EE); the pointer is in r5 everywhere else, so the ROM has a second pseudo for it in that branch; the ROM also adds 2 to
the pointer after count - 1 and before the 0xFFFF compare (the parked order is add, then decrement). (2) dictionary-copy loop registers: 0xFFFF
sentinel in r7 (copied from r2), &data_03002BB0 in r5, &data_03002BB8 in r6 then sb; here the pointer stays in r5 and the sentinel is reloaded each
pass. (3) mask = 0xFFFF loaded into r0 and stored to [sp], reloaded into r6 for the shift (0x080051FA-0x08005200) - same RTL here, reload chooses
differently following earlier header-code choices (mov r2, ip vs mov r7, ip; movs r6, #2 vs mov r0, #2). (4) mode-3 length read and literal-copy
loop register swaps.

Ruled out: the older parked README's forms (all 332); scheduling (no sched pass at this level), loop hoisting (hoisted code lands after the
compare), strength reduction (increments not on every pass), gcse/PRE (no matching source + 2 available). Untested next steps: a static inline for
the dictionary branch taking the pointer by value and returning it advanced (possible second pseudo; it could ship only if the same text
reproduces a second function or copies a real ROM function); the siblings' u32 data_03002BB8 and s32 return.
