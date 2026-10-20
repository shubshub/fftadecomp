# 0801CC7C: rectangle-bounded map-cell predicate

This is a natural recovery, not a verified match.

## ROM extent and behavior

The complete function occupies `[0x0801CC7C, 0x0801CD06)`: 138 bytes and
66 reachable Thumb instructions. Its interior literal at `0x0801CCF0` is
`0x02007F10`. The two zero bytes at `0x0801CD06` are external alignment before
the next function, `0x0801CD08`, and are not part of this symbol.

Both coordinates are narrowed to unsigned bytes. The already matched
`func_0801CD4C` writes four separate local bytes, recovered as width, height,
left, and top. The predicate rejects coordinates below either origin or at
or above either exclusive upper bound. The sums use promoted integers, not
byte-wrapped arithmetic. Inside the rectangle, it returns whether the first
byte of the two-byte map cell is nonzero.

The global layout is corroborated by neighboring map accessors: the entries
pointer is at `0x02007F10 + 4`, and the map width byte is at offset 8.
Valid map storage is the ordinary input-state precondition. The zero/one
result supports an integer predicate; it does not uniquely recover the
original return typedef.

## Two independent limitations

1. The reviewed `868e87e` matcher rejects `unsupported stack-address
   materialization` before byte comparison. At `0x0801CC94`, `movs r0, #1`
   establishes a constant; bytes `68 44` at `0x0801CC96` decode as
   `add r0, sp, r0`. This forms the local-byte pointer `sp + 1` within a
   four-byte local frame beneath 32 bytes of saved registers. The candidate
   and ROM share this sequence. The missing proof is not permission to
   bypass the verifier.
2. Diagnostic compilation and typed-call linking independently show real
   byte differences. The retained source emits a complete 138-byte symbol
   with 65 reachable instructions, a two-byte alignment gap at
   `0x0801CCEE`, and the same interior literal. The ROM has 66 instructions
   and no corresponding gap. The first two bound checks use different
   registers. The compiled cell calculation factors the index as
   `2 * (row * width + column)` before adding the base, whereas the ROM adds
   the doubled row offset to the base before the doubled column offset.
   The common epilogue and call target match, but the symbol is not
   byte-identical. Repairing the verifier alone cannot establish a match.

## Bounded attempts

The initial combined outside-rectangle guard emitted 136 bytes. Natural
successful-path variants using the established map-accessor calculation
emitted 126, 128, or 132 bytes, with different register lifetimes. Separate
ordinary early returns produced the retained 138-byte candidate; expressing
the final address as chained pointer additions instead emitted 142 bytes.
No assembly, volatile accesses, artificial state, dead code, or compiler
directives were introduced. Further source permutations were stopped.

## Diagnostic evidence

The retained source uses the standard `agbcc -mthumb-interwork -O2`
toolchain. Its only relocation is the typed call at `0x0801CCAA` to
`0x0801CD4C`; there are no data relocations.

- Source SHA-256:
  `5e721b3c1c8a97f486b2589243212217709885226716fac8beeafc2a0f03ce49`
- Emitted full-symbol SHA-256:
  `f8ecfe9a04521c9d71a1e9524a1a83743a4078b80b8fd562bdb4dd654e62ffe7`
- ROM full-span SHA-256:
  `4525b72830d12a86414a578da0d8ddcc256d25ec0a69c08c84d6b70198fc8690`

No successful match report is retained.
