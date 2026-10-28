# 081448FC — unresolved flag-test instruction

Target: complete indexed Thumb body [0x081448FC, 0x0814492A), 46 bytes / 22 reachable instructions. Fixed compiler: agbcc -mthumb-interwork -O2.

The function ignores its first argument and traverses the list in its second argument. The head pointer is at list+0x20. For each node, it tests flags at offset zero against 0xC7, sets bit 0x40 when any tested bit is present, calls indexed func_081448DC, then advances through node+0x34. It clears the list's status byte after traversal.

The preserved source was tested with the native matcher: complete compiled symbol 48 bytes / 23 instructions, direct-Thumb-call CFG and typed linking accepted, source plausible, verdict NOT MATCHING - bytes differ, exit 1. The target uses TST r0,r1 after loading mask 0xC7 into r0. The compiler instead emits ANDS r0,r1 followed by CMP r0,#0. That extra instruction accounts for the two-byte gap and shifts forward branches and the relocated direct call. Other operations and register choices agree. The native aligned diff score for this candidate was 17/21 instructions and 42/48 bytes; those are diff scores, not the actual reachable instruction count or same-offset byte equality. Comparison bytes beyond the target's indexed 46-byte body provide no match credit.

Tested a promoted u32 flags local and the preserved u8 local; both generated the same 48-byte body. A named u8 mask in mask-first order generated a 50-byte body, saving r6 and retaining ANDS plus CMP, so it was not preserved. No assembly, artificial volatile access, dead code, forced inlining, compiler flag change or shared metadata edit was used. Unmatched active source and report were removed.
