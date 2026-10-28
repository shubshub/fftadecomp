# 08144DD8 — unresolved incoming-register contract

Target: complete indexed Thumb body [0x08144DD8, 0x08144E08), 48 bytes / 24 reachable instructions. Fixed compiler: agbcc -mthumb-interwork -O2.

The target immediately reads a channel pointer from live r4 and a track pointer from live r5. It has no prologue, no moves from ordinary argument registers r0/r1, and returns directly with bx lr. It clobbers r0-r3 while retaining r4/r5. The captured body therefore exposes a custom incoming-register contract that the preserved ordinary C signature does not reproduce. The source is an arithmetic reconstruction, not a claim that the incoming ABI has been recovered.

Channel fields: output bytes at +2/+3, volume byte at +0x12, signed balance byte at +0x14. Track gain bytes are at +0x10/+0x11. The outputs are the unsigned-saturated-to-255 values of ((128 + balance) * volume * leftGain) >> 14 and ((127 - balance) * volume * rightGain) >> 14. Signed 32-bit arithmetic and arithmetic shifts follow the target instructions; the explicit unsigned saturation checks follow its BLS conditions.

One natural typed reconstruction was compiled and natively checked. The compiled complete ELF symbol is 62 bytes / 31 instructions, with a normal r0/r1 pointer signature, a push/pop return frame and different arithmetic temporaries. The matcher accepted the complete closed-leaf CFG and source plausibility, then returned exit 1, NOT MATCHING - bytes differ. Its aligned diff score was 8/31 instructions and 33/62 bytes; this is not same-offset equality with the 48-byte target. Following ROM bytes displayed by the longer comparison are outside the indexed target and provide no match credit.

Further ordinary signature or expression changes do not establish live r4/r5 input values. No register-bound assembly declarations, naked attributes, forced inlining, artificial volatile accesses, dead code, compiler flag changes or shared metadata edits were introduced. Resolving this body requires genuine caller/ABI evidence or broader function-boundary evidence rather than an invented C argument contract. Unmatched active source and report were removed.
