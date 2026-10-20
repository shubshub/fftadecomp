# 0x080CD92C

Status: recovered, not byte-identical. This is a remaining matching task, not
an inherently unmatchable function.

## Confirmed behavior and extent

The function reads the byte at offset `0xE8` of its non-null input object and
returns one when bit `0x40` is set, otherwise zero. The complete ROM symbol is
`[0x080CD92C, 0x080CD944)`: 24 bytes, 12 Thumb instructions, and no literal pool.

## Remaining difference

The retained natural byte-field recovery compiles to a 24-byte complete
symbol with `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`. The official matcher
accepts its source plausibility and closed leaf CFG, with no relocations, but
reports only 10/12 identical instructions and 21/24 identical bytes.

At `0x080CD930`, the ROM loads the mask into `r1`, then reads the object byte
into `r0`. The compiler instead reads the byte into `r1`, then loads the mask
into `r0`. The subsequent AND, comparison, branches, returns, and all other
instructions match.

## Natural forms checked

- A positive-condition early return also emits 24 bytes, but reverses the
  conditional branch and return-block ordering.
- The retained clear-bit early return reproduces that control flow, leaving
  only the mask/load register allocation and ordering difference.
- A direct boolean comparison emits a shorter 12-byte symbol.
- An explicit `u8` result assigned in both branches emits an 18-byte symbol.
- Reversing the AND operands or introducing a named masked-byte local leaves
  the same two-instruction difference.
- Representing the flag as bit 6 in a byte-sized bitfield also leaves the
  same difference.
- A peer-supported form with `u8 mask = 0x40; u8 flags = object->flags;`
  followed by the clear-bit early return emits 24 bytes with 11/12 identical
  instructions and 22/24 identical bytes. It assigns the expected registers,
  but loads the mask before adding `0xE8` to the object pointer; the ROM
  performs those operations in the opposite order. This single additional
  form was tested after the initial parking, without further variants.

All attempts used the normal `-mthumb-interwork -O2` compiler flags and
published toolkit `c85d11d`. No inline assembly, volatile access, compiler
pragmas, artificial code, or verifier bypass was used. The unmatched source
and generated report were removed from the active source/report directories.
