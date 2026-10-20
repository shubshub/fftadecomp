# 08123D50 — callback-address relocations unsupported

The recovered function initializes script/view state and installs five
callbacks in the table at `0x03002710`. Bounded Binary Ninja analysis finds
55 reachable Thumb instructions in `[0x08123D50, 0x08123DDA)`, followed by
two alignment bytes and nine referenced literal words. The complete symbol
extent is `[0x08123D50, 0x08123E00)`, 176 bytes.

The first natural candidate compiles with the normal agbcc
`-mthumb-interwork -O2` flags to a 176-byte ELF function. Instruction positions,
literal positions, and all 92 bytes outside relocation words match the ROM.
The remaining 84 bytes contain 14 direct-call relocations, two known-global
relocations, and five `R_ARM_ABS32` function-address relocations. This is not
an official byte-identical match: the callback-address relocations have not
been linked and admitted by the matcher.

At initial verification, `match.py` rejected the mapping because direct-call
targets were absent. A separate read-only call to the official `call_bindings` routine,
supplying just those absent entries in memory, reaches the decisive error:
`data target must be an undefined mapped object`. The current data-linking
profile accepts mapped object literals, not function-address literals. The
unsupported callback symbols are `func_080231E8`, `func_08096E78`,
`func_080D36B0`, `func_080231F4`, and `func_0802326C`. Their symbol names were
retained; raw code addresses were not substituted to bypass the check.

## Recovered contracts

- `g_state_02000000` supplies a mode byte at offset `0x2190`.
  `func_0800397C` takes the byte-sized predicate `mode != 2`.
- `g_state_0200F390` has halfword flags at offset `0x94` and the 40-byte
  view subobject initialized by `func_08024758` at offset `0x1C`.
- `func_08096BA0` and `func_081256BC` do not consume the caller's incidental
  register contents. The former's initial helper chain initializes its own
  inputs; the latter explicitly passes `0xFF` to its helper.
- The return from `func_08096D7C` is passed explicitly to `func_0809AB14`.
  The byte returned by `func_080C95A8(0x35)` goes to `func_080BD11C`.
- Existing `func_08006ADC` stores a `u32` payload and clears its flag.
  Existing `func_080069F4` consumes these payloads as callbacks taking
  `(u8 index, u8 *flag)`, justifying the function-address-to-word casts.
  The registration indices are 4, 2, 5, 6, and 7.

No alternative spelling, compiler flags, fabricated enclosing layout,
incidental-register argument shortcut, or instruction-order steering was
attempted. A supported function-address relocation profile is the next
required step before this source can be reconsidered for `src/`.
