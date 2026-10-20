# 0x080CD9A4

Status: recovered, not byte-identical. This remains a matching task.

## Confirmed behavior and extent

The function reads the byte at offset `0xE9` of its non-null input object and
returns one when bit `0x08` is set, otherwise zero. The complete ROM symbol is
`[0x080CD9A4, 0x080CD9BC)`: 24 bytes, 12 reachable Thumb instructions, no
literal pool, and no alignment padding.

## Remaining difference

The retained natural byte-field predicate compiles to a complete 24-byte,
12-instruction symbol with `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`.
The published `c85d11d` matcher accepts its source plausibility and closed leaf
CFG, with no relocations, but reports 22/24 identical bytes and 11/12 aligned
instructions.

After adding `0xE9` to the object pointer, the ROM loads the mask into `r1`
before reading the byte into `r0`. The candidate reads the byte first and
loads the mask second. The AND, comparison, branches, and returns agree.

## Natural forms checked

- A direct boolean comparison produces a shorter 12-byte symbol.
- A positive-condition early return produces 24 bytes but changes operand
  registers and branch ordering; an explicit `else` has the same result.
- Assigning a byte result in both branches produces an 18-byte symbol.
- A clear-bit early return from the direct field expression produces the
  correct branch ordering, but swaps the operand registers.
- Loading a masked-byte local, including with commuted AND operands, leaves
  the register difference. The retained unmasked-byte local is closer.
- A named `u8 mask = 8` before the byte load also produces 22/24 bytes, but
  moves the mask load before the pointer adjustment rather than between the
  adjustment and byte load.

No compiler-flag sweep, assembly, volatile access, pragmas, artificial ordering
statements, or verifier bypass was used. The nonmatching source and report were
removed from the active source/report directories.
