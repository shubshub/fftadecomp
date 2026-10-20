# 08131F70: selected-value adjustment

## Status

Not matched. The natural recovery emits a 96-byte function instead of the
complete 100-byte ROM function. This is a code-generation mismatch, not an
unsupported proof profile. No successful source or match report is retained.

The ROM extent is `[0x08131F70, 0x08131FD4)`: 43 reachable instructions, with
code ranges `[0x08131F70, 0x08131FC2)` and `[0x08131FCC, 0x08131FD4)`, a zero
alignment halfword at `0x08131FC2`, and literal words `0x02000000` and
`0x00001F64` at `0x08131FC4` and `0x08131FC8`.

The standard compiler is `agbcc -mthumb-interwork -O2`; the reviewed verifier
is `/home/user/.codex-work/ffta-ulw/kit-reviewed-3f840c6/tools/match.py`.

## Recovered behavior and contracts

The function takes one mutable object pointer and returns no value. It exits
when bit `0x10` of the halfword at offset `0x26` is set. Otherwise, byte
`0x28` selects a signed halfword starting at offset `0x20`. The halfword is
promoted before absolute value, so `-32768` correctly becomes `32768`.

The actual backing storage must permit the selected aligned halfword read,
the aligned pointer read at offset `8`, and the halfword read at offset
`0x26`. No selector range or fixed array extent has been established. The
byte-buffer view does not invent a small array bound.

Two distinct calls to the existing `u8 func_08131BB8(void *)` are retained,
with a fresh read of the pointer at offset `8` for each. Each false result
exits. The matched helper tests membership in 24 records beginning at
`0x02000080`, with stride `0x108`, and does not mutate the object. The
repeated test is therefore redundant under that helper contract; its
original source-level layering is not established. No helper mutation is
invented to explain it.

After both tests succeed, the word at `g_state_02000000 + 0x1F64` is reduced
by the magnitude, wrapping modulo 2^32. A positive signed interpretation of
the wrapped result is stored; otherwise zero is stored. Only one global
write occurs. The existing named base binding is sufficient.

The recovery uses unsigned subtraction to avoid signed-overflow undefined
behavior. Its conversion from `u32` to `s32` deliberately relies on the
target compiler's two's-complement interpretation for high-bit-set values;
that conversion is implementation-defined, not a portable ISO C claim.
A fully defined alternative is to clamp an unsigned result above
`0x7FFFFFFF` to zero. Neither interpretation assumes a nonnegative prior
global value. For example, prior bits `0x80000000` and magnitude `1` produce
`0x7FFFFFFF`, not zero.

## Attempts and remaining difference

1. A `void *` argument with a byte-view local and explicit
   `0x20 + selector * 2` addressing emitted 100 bytes, but used different
   object registers and a different selected-halfword access sequence.
2. A direct byte-buffer argument with ordinary halfword indexing emitted
   96 bytes. This minimal representation is retained.
3. A typed prefix containing the known pointer, flags, and selector fields
   also emitted 96 bytes. It did not improve the selected-value access and
   is not retained.

The retained candidate combines `object + 2 * selector`, then uses
`0x20` as the register offset for `ldrsh`. The target retains
`object + 0x28`, subtracts `8`, adds the scaled selector, and performs
`ldrsh` with a zero offset. The candidate has one fewer instruction;
its literal pool also needs no alignment halfword, accounting for the
four-byte difference. Branches, calls, and literal locations move
accordingly.

Both helper calls, the signed-halfword absolute value, the wrapping
subtraction and signed comparison, the final stores, and the separate
base/offset literal shape are otherwise recovered. No invented array
extent, overlapping aggregate, compiler option, or inert operation was
added to force the address sequence.
