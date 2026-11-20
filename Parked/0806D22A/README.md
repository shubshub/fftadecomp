# 0806D22A belongs to the state dispatcher at 0806B6D0

The function index in `symbols/functions.txt` assigns the half-open interval
`[0806B6D0, 0806D2B4)` to one 7,140-byte Thumb function. Its last common
block starts at 0806D22A. The next function starts at 0806D2B4.

The owner reads a state byte and jumps through a 256-word table at 0806B6F8
using `mov pc, r0` at 0806B6F0. Exactly 217 entries contain the even
address 0806D22A, including state 3. The instructions at 0806D220–0806D228
also fall through to it after storing a state byte. A scan for Thumb BL
encodings targeting 0806D22A in the first 0x150000 ROM bytes finds 27, all
inside this owner. Such long branches run the shared tail. It restores
the dispatcher's saved return address and returns directly to its caller.

At 0806B6D0 the owner pushes r4–r7 and LR, saves r8–r10 on the stack,
and allocates 32 local bytes. The epilogue at 0806D27C frees those 32 bytes,
restores both sets of registers, and pops the original return address for
`bx r0` at 0806D28A. Direct entry at 0806D22A would consume a frame it
never created. The 138 remaining bytes of the owner comprise 98 instruction
bytes (43 instructions) followed by 40 literal-pool bytes. The first literal
at 0806D28C is used by 0806D220, before the proposed entry.

No standalone C, match selector, or independent function span applies.
