# 08131E90: recovered, not byte-identical

The complete ROM function is `[0x08131E90, 0x08131EC0)`: 48 bytes and
23 instructions, with no literal pool or local stack allocation.

The retained natural C compiles to 48 bytes and 23 instructions with the
reviewed `3f840c6` matcher and `agbcc -mthumb-interwork -O2`. It passes
plausibility and direct-call CFG verification but differs in 13 bytes:
35/48 bytes and 11/23 instructions match. `match.md` records the final
comparison made before moving the source out of `src/`.

## Recovered behavior

- Call `s32 func_080C7EA4(const void *, u32)` with the pointer at offset
  zero and selector `0x26`. This selector returns the zero-extended
  halfword at the pointed object's offset `0xD6`.
- After the call, read the index byte at offset `0x28` and add the signed
  halfword at `0x20 + 2 * index`. The index is unchecked; no four-element
  array bound is established by this function.
- The sum is signed and lies within `[-32768, 98302]` for this helper
  selector. Cap values above 10, without applying a lower clamp.
- Reload the pointer at offset zero and store the result's low halfword
  at its offset `0xD6`. Negative results retain their low 16 bits.

The caller requires valid storage for the selected signed halfword and
valid helper/final-store objects. No null checks, nonalias assumptions,
or cached pre-call fields were introduced.

## Remaining mismatch

The ROM preserves the helper result in `r0`, reads the index through
`object + 0x28`, subtracts eight from that address to reuse it as the
halfword-table base, and produces the sum in `r2`. The retained source
instead moves the helper result to `r1`, forms `object + 2 * index`,
uses a register offset of `0x20` for the signed load, and keeps the sum
in `r1`. This also changes the comparison and store operand registers.
The prologue, helper call, signed upper-cap branch target, final pointer
reload, and return sequence otherwise agree.

A named table-pointer temporary produced 52 bytes. Explicit base-value,
index, and table-pointer locals produced 50 bytes. The clean inline
indexed view retained here produces the correct 48-byte extent but is
not a match. No compiler-steering constructs or fabricated array bounds
were used.
