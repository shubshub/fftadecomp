# 080CAE2C equipment-change checks

The readable C compiles to all 330 bytes of the original function at
080CAE2C..080CAF76 under native agbcc `-mthumb-interwork -O2`. A typed GNU
ARM link resolves the five Thumb calls and both named data relocations.
The linked symbol and the complete ROM slice share SHA-256
`05d816bdcf8b132510706f627ca4e72de72ac658fa731f25cecbc193578d2a1f`.
Recursive decoding gives 155 instructions, two four-byte literals at
080CAE74 and 080CAF04, and a two-byte internal alignment gap at 080CAF02.
Both map entries already agree. The source passes plausibility with zero
findings. The public kit declined verification, so the recovery is Parked.

The routine copies the unit's five equipment IDs from offset 0x2A into a
ten-byte local array. To model replacing an occupied item, it temporarily
clears that slot in the live unit and tests which selected abilities the
item supplied. It restores the original slot, writes the proposed item
only into the local copy, and passes the copy and flags to 080CABA8.

The original indexed ROM contains two direct callers. Recursive control
flow verifies BL 080CB576 in 080CB54C, where a five-slot loop passes mode 1,
and BL 080CB498 in 080CB48C, where the wrapper passes its incoming byte slot
and mode 0. The second wrapper does not itself establish slot < 5. For
example, its caller 08027800 selects zero or a loop index from 0 through 4
at site 080278C0. Other wrapper call sites occur at 08079E20, 08079F3C,
0807A4AA and 0807A5C4. A full slot-range proof for those paths is open.

With this file in a scratch root's `src/080CAE2C.c`, toolkit revision `20b9d53`
`match.py --root <scratch> 080CAE2C --no-write` exits 1 with
`buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification`.
The conditional thunk profile `bounded-buffer-conditional-thunks-v1` returns
`conditional indirect call excludes local argument aliases and pointer words`.
The finite-small-copy profile returns `one actual canonical small-copy call required`.
The existing unit-equipment-attribute profile rejects the owner at its
reviewed types/local-array check.

The actual callback slot at 0836D4BC contains 03005EE9. The BL at 080CAE5C
passes this pointer to the real r3 thunk, with SP as destination, unit+0x2A
as source and length ten. The other calls resolve to 080CA7A4, 080CD480,
080CD1FC and 080CABA8. The last receives the local equipment array and itself
performs another ten-byte indirect copy at 080CABD8. Public admission still
needs both the bounded slot index and the caller-stack contracts for those
genuine calls. No verifier change was made.
