# 081448DC — unresolved native byte mismatch

Target: complete indexed Thumb body [0x081448DC, 0x081448FC), 32 bytes / 16 reachable instructions.
Compiler: fixed agbcc -mthumb-interwork -O2.
Latest native matcher: exit 1, NOT MATCHING - bytes differ. The complete compiled symbol is 38 bytes / 19 instructions; closed-leaf CFG verification and source plausibility passed. This is not an exact match.

The function removes a node from its owner's doubly linked list. The owner pointer is at node+0x2C, previous at +0x30, next at +0x34, and the owner's head pointer at +0x20. It repairs adjacent links and clears the owner pointer.

Three natural forms were tested: a void function with a guarded body (38 bytes), a node-returning function (40 bytes), and the preserved void early-return form (38 bytes). Both void forms retain an LR save/restore and move the incoming node from r0 to r2. The target keeps the node in r0 and returns directly with bx lr. Those extra push/move/pop instructions account for the six-byte length gap in the preserved form. Its next/previous registers are r0/r1 rather than the target's r1/r2, and its previous load precedes its next load; the first guarded form loaded next first but retained the same register/frame mismatch. The pointer-returning form added a return-value move and did not remove the frame.

The native aligned diff score was 2/19 instructions and 21/38 bytes for the preserved form; that score is not same-offset equality against the 32-byte target. The matcher displayed following ROM bytes when comparing the longer compiled body; they are outside the target's indexed extent and provide no match credit.

No compiler flags, assembly, artificial volatile accesses, forced inlining, or shared metadata were changed. Unmatched active source and report were removed.
