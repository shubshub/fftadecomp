# 081462F8 — bounded natural-C nonmatch

The candidate recovers the music-player signature guard, temporary signature
increment, selected-track mask traversal, active-track flag check, LFO-speed
byte update and zero-speed reset call. Track stride is 0x50; the LFO-speed byte
is at offset 0x19. The signature is restored after the loop.

The approved fixed compiler and default native matcher reach complete-symbol
comparison and source plausibility. The original ET_REL symbol is 116 bytes,
including its literal pool, with 54 verified reachable instructions. Native
matching exits 1. Exactly 114 of 116 bytes agree at the same offsets; the
instruction comparison is 52 of 54. This is not a matched function and earns
zero C credit.

The sole remaining difference is the temporary register used for the stored
LFO-speed zero check: the compiler uses r0 where the ROM uses r1. This changes
bytes at offsets 0x46 and 0x49 (ROM addresses 0x0814633E and 0x08146341).
The flag-mask setup, byte load, call relocation, branches, frame, return and
literal pool agree. No owner, compiler, mapping or plausibility gate was changed.

Comparing the original input argument produces a shorter 108-byte function.
Comparing the stored plain byte recovers the complete 116-byte frame and
high-register lifetimes. A byte-wide bitfield produces no improvement and was
removed. Separate and combined track conditions, direct bit tests, a named
active mask and promoted loaded flags were tested. A promoted local speed
again collapses the body to 108 bytes. Assignment-as-condition agrees with the
best separate-store/read form and does not resolve the register difference.
No artificial register lifetime, volatile qualifier, helper, assembly or
compiler-option change was used.

The original unmodified compiler ET_REL and final native output are retained
in the batch's sibling 081462F8 artifact directory. The failed active source
and report were removed; this source is preserved for future recovery.
