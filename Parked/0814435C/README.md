# 0814435C: signed 64-bit comparison

The complete ROM body is [0x0814435C, 0x08144378): 28 bytes and 14 reachable
Thumb instructions. Incoming r0:r1 and r2:r3 hold two signed 64-bit operands.
The high words are compared as signed integers, then equal-high operands
are ordered by unsigned low words. The result is 0 for less, 1 for equal,
and 2 for greater.

The retained natural C uses a local union to expose the low and high words
without a helper call or a change to that two-operand ABI. The fixed agbcc
-mthumb-interwork -O2 compilation emits a 32-byte, 16-instruction complete
ELF symbol. Native matching exits 1: closed leaf CFG, no relocations, source
plausible, NOT MATCHING - bytes differ.

The precise residual is the interworking LR frame. The compiler inserts
push {lr} before the comparison body and uses pop {r1}; bx r1 at its end.
ROM starts directly with the comparison and returns with bx lr. The 13
comparison/result instruction encodings, occupying 26 bytes, are otherwise
identical, displaced by the compiler's two-byte prologue. The reported
aligned diff is 7/16 instructions and 27/32 bytes; that score is not
same-offset equality or complete-symbol matching. The comparison includes
bytes beyond the 28-byte indexed ROM owner when the candidate is 32 bytes;
those adjacent bytes are not part of this function.

No original-runtime ABI attribute or compiler context is established that
would justify changing the function to suppress this frame. No assembly,
flag changes, forced inlining, artificial volatile or inert control flow
was used. The recovered body is preserved without match credit.

Final native log:
/home/user/.codex-work/ffta-ulw/audio-following-v432-matching/0814435C/match-current.log.
Active unmatched source and report were removed.
