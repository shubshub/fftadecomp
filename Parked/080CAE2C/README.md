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
0807A4AA and 0807A5C4. The menu-state evidence below traces all four arguments.

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

## Menu slot and copy contracts

The four calls read the same byte. With `menu = *(u8 **)0x03002818`,
`08079E18`, `08079F32`, `0807A4A0` and `0807A5BA` each load
`menu[0xC1F]` into R2. The first two calls belong to `080799C0`, the last
two to `0807A094`. All four also pass the unit pointer from `menu + 0x1D0C`
and the item ID from the current record. Running each argument setup in the
USA ROM for slots 0 through 4 produced the expected R0, R1 and R2 at all
20 call boundaries.

Two kinds of menu updates write that slot. At `0807A870`, `0807ABB2`,
`0807C9BC`, `0807D3CA`, `0807DE40` and `0808D710`, the value comes
from the cursor ordinal at `menu[0x561]`. At `0807C88E` and `0807D2E0`,
it comes from the selected row's value. The menu panel starts at offset
0x45C, so its cursor at panel+0x105 is the same byte at menu+0x561.
[The matched row getter](../../src/08089D64.c) returns
`panel[4 + 8 * cursor]`.

The cursor can represent six positions. For input events 0x40 and 0x80,
the path at `0808E030..0808E0A4` sets it to the halfword at menu+0x966,
plus one, minus the halfword at menu+0x2D1A, clamped to 0 through 5.
The upper branch explicitly writes 5 at `0808E094`. Running this block
in isolation reproduced the clamp in 100 cases covering both events.
The equipment handler `0807A79C` is registered in slot 3 at
`080784F0` from case 4 of the parent dispatch table at `080775D0`.
[The registration routine](../../src/08006ADC.c) initializes its state
byte to zero. In state zero the handler copies the cursor ordinal to
menu+0xC1F at `0807A870` or `0807ABB2`, depending on bit 1 of
`02002FC1`. In the separate handlers `0807C7E8` and `0807D240`, the
dispatch tables at `0807C810` and `0807D264` select the ordinal for states
0 and 1 and the row value for state 3. A bound on the cursor in the
equipment context and on the slot preserved across later calls remains open.

Both ten-byte copies have an identifiable implementation. The BLs at
`080CAE5C` and `080CABD8` call the same `bx r3` trampoline with R3 loaded
from `0836D4BC`. [The boot installer](../../src/08002768.c) places
[the matched copy routine](../../src/08A38A9C.c) at `03005EE8`.
The first call copies from unit+0x2A to its own SP. The second copies from
the equipment array passed in R1 to the nested callee's SP. Running the
installed routine through the trampoline for all 16 source and destination
alignment pairs copied exactly ten bytes in each case. Its only other data
accesses were to the eight bytes it saves and restores below its entry SP.
The public owner verifier still needs to model both calls and the slot bound.
