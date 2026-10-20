# Parked: func_080CD9BC

Status: plausible recovery, not byte-identical under the standard
`agbcc -mthumb-interwork -O2` toolchain.

## Field contract and complete extent

The input points to a valid object containing a readable byte at offset
`0xE9`. The function returns 1 when bit `0x10` is set and 0 otherwise.
The local object layout agrees with the nearby `func_080CD95C` recovery.
There is no null-pointer check in the original.

Bounded Binary Ninja inspection confirms the complete half-open extent
`[0x080CD9BC, 0x080CD9D4)`: 24 bytes, 12 reachable Thumb instructions,
no literal pool, and no alignment bytes within the function.

## Remaining difference

The parked source uses a local flags byte and an early return for the
clear-bit case. Its symbol is also 24 bytes with 12 instructions. The
branch direction, boolean return values, mask register, and epilogue match.
Only the relative order of the mask load and byte load differs:

- ROM: advance to the flags field, load mask `0x10` into `r1`, load flags
  into `r0`, then apply the mask.
- Parked C: advance to the flags field, load flags into `r0`, load mask
  `0x10` into `r1`, then apply the mask.

The official matcher reports `11/12 instructions identical (22/24 bytes)`
for this reordered pair. That is an alignment-based comparison, not a
byte-identical verdict. The source passes the plausibility gate.

## Bounded attempts

- A direct nonzero comparison compiles to a shorter 12-byte symbol.
- An explicit shared result variable compiles to an 18-byte symbol.
- Explicit returns produce 24 bytes but initially reverse the branch order
  and assign the mask and loaded byte to different registers.
- A named flags byte with a clear-bit early return produces the parked
  result.
- Constant-first mask spelling does not recover the register allocation.
- A named `const u8` mask produces the same load-order mismatch.
- The peer-derived non-const mask form produces 24 bytes but loads the mask
  before the field-address addition; the ROM loads it after that addition.

No extra address temporaries, inline assembly, volatile accesses, or
optimization changes were added to force the remaining instruction order.
The source and failed report were removed from the verified trees. This
recovery remains parked rather than counted as a match.
