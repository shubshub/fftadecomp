# 080CD544: indexed byte flag setter

## Recovered behavior

The complete target is `[080CD544,080CD55E)`: 26 bytes and 13 reachable
Thumb instructions, with no literals or calls. The following zero halfword
is external alignment.

A compatible interface is `void(void *object, u8 index)`. A null object
causes no data access. Otherwise the function sets bit `0x80` in the byte
at `object + 0x40 + (u8)index`, preserving the other bits. The nonnull
object must provide the selected readable and writable byte; its allocation
length is not established. Only the first two argument registers are used,
and the saved return address is popped into `r0`, not a scalar result.

## Remaining mismatch

The retained natural byte-region view compiles to the correct complete
26-byte extent and passes the closed-leaf CFG and plausibility checks,
but matches only 24 of 26 bytes and 11 of 13 instructions:

| Address | Target | Candidate |
| --- | --- | --- |
| `080CD552` | `ldrb r2, [r0]` | `ldrb r1, [r0]` |
| `080CD554` | `movs r1, #0x80` | `movs r2, #0x80` |

The following `orrs r1, r2` and every other instruction are identical.
This is a code-generation mismatch, not a verifier limitation or a match.

## Natural forms checked

- `record[0x40 + index] |= 0x80` produces 28 bytes and a different address
  computation and register allocation.
- A byte-region pointer `flags = record + 0x40`, followed by
  `flags[index] |= 0x80`, produces the retained 26-byte candidate.
- `flags[index] = 0x80 | flags[index]` produces the same 26-byte mismatch.
- An ordinary struct containing seven low bits and one enabled bit does not
  model the observed byte array under this compiler: agbcc gives the struct
  a four-byte stride and emits an index shift. That representation was
  discarded rather than forcing its layout.

All attempts used the reviewed `3f840c6` matcher and the standard agbcc
`-mthumb-interwork -O2` configuration. No assembly, optimization attributes,
volatile accesses, fabricated array lengths, or register-steering work was
added. No failed source or match report remains in the production paths.
