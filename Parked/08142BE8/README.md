# 0x08142BE8 - libgcc dp-bit __pack_d: bytes identical under old_agbcc, refused by the library-unit path (`__lshrdi3` call) (332 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. The function lies in the `libgcc dp-bit` library unit
(`config/library_units.json`, toolchain `old-agbcc-O2-v1`) and is libgcc's `pack_d` as compiled into `dp-bit.o`
(`__pack_d`): it packs an unpacked `fp_number_type` (class, sign, unbiased exponent, 64-bit fraction with eight guard
bits) into an IEEE double. NaN gives exponent 0x7FF with the quiet bit set, infinity 0x7FF with a zero fraction, zero
and a zero fraction exponent 0; an exponent below -1022 is denormalised by a variable 64-bit right shift (the
`__lshrdi3` call at 0x08142C64), one above 1023 becomes infinity, and otherwise the guard bits are rounded to nearest
even. The 52/11/1 bit-field stores follow (0x08142CDC-0x08142D0A), then the two words are swapped
(`FLOAT_WORD_ORDER_MISMATCH`, 0x08142D0C-0x08142D12) and the result is returned in r0:r1. The index row
`08142BE8 08142D34 332 139 return` is right (139 reachable instructions, one `bl`; twelve literal words, the last pool
at 0x08142D20-0x08142D30). The only external symbol is `__lshrdi3`, the index function at 0x08144378
(`08144378 081443AE 54 27`). No data symbol is needed.

## Byte identity

`match.py` stops before its own byte comparison (below), so identity was shown by hand with the unit's toolchain:
`cpp -nostdinc -undef -I include`, `old_agbcc -mthumb-interwork -O2` (pret/agbcc's `-DOLD_COMPILER` build, the binary
`match.py` names for `old-agbcc-O2-v1`, SHA-256 `88ebbb5b6167ab979f1652e599a5fb134eabe9a93f43122ca019da77a32c29f1`),
`arm-none-eabi-as -mthumb-interwork`. `.text` is exactly 332 bytes. Linked at 0x08142BE8 with `__lshrdi3` bound to
0x08144378 (one `R_ARM_THM_CALL`), the 332-byte symbol equals the ROM span `[0x08142BE8, 0x08142D34)`: SHA-256
`38aa6a8e47b81d402a011d733156fc99229f9fdf028aee34f5920b3464a5bb00` for both. `plausible.py --strict` exits 0.

The same source under the default `agbcc -mthumb-interwork -O2` gives a 336-byte symbol that differs from the ROM in
60 of the 332 bytes, from 0x08142CB8 on: agbcc materialises `sp` separately for the exponent and the sign bit-field
stores (`mov r3, sp`, then `mov r2, sp`), where the ROM and `old_agbcc` share one `mov r2, sp` (0x08142CEC).

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08142BE8.c`: the default run, the
`--unit-toolchain old-agbcc-O2-v1` run, and the three selectors below with and without
`--unit-toolchain old-agbcc-O2-v1` (eight runs). None matched.

| Run | Refusal |
|---|---|
| `--unit-toolchain old-agbcc-O2-v1` | `compile failed: lshrdi3 requires the fixed approved toolchain configuration` |
| default (no toolchain option) | `refused: 0x08142BE8 lies in library unit libgcc dp-bit: its default-toolchain object differs from old-agbcc-O2-v1's; verify it with --unit-toolchain old-agbcc-O2-v1` |
| `--owner-runtime-profile private-double-unpack-pack-v1`, `--owner-runtime-profile private-double-scalar-pack-v1`, `--software-double-profile convert-sub-div-target-v1`, each with `--unit-toolchain old-agbcc-O2-v1` (3) | `refused: library unit toolchains are admitted on the ordinary Thumb path only, with the default WSL options` |
| the same three selectors without `--unit-toolchain` (3) | the default-run refusal above |

## Cause

On the ordinary path, a call to `__lshrdi3` selects the kit's pinned shift profile (`match.py:5862-5869`), whose
`fixed_configuration` (`lshrdi3_profile.py:36-40`) requires the compiler and flags to be the default agbcc
`-mthumb-interwork -O2`. `--unit-toolchain old-agbcc-O2-v1` replaces both (`library_units.gate`), so the profile
refuses before the byte comparison. The schemas a unit run may report (`library_units.schemas()`,
`library_units.py:283-288`, enforced at `match.py:6156-6158`) do not include the shift profile's
`elf-symbol-thumb-lshrdi3-target-v1` either, so lifting only the toolchain check would not be enough. The
private-double and software-double selectors cannot be combined with a unit toolchain (`library_units.py:326-330`),
and without `--unit-toolchain` the gate refuses the address because the default toolchain's object differs from the
unit's (`library_units.py:357-359`).

## Source notes

- The source is `pack_d` from gcc 2.95's `config/fp-bit.c`, as shipped in pret/agbcc's `libgcc/fp-bit-base.c`, with
  the two defines pret/agbcc's `libgcc/Makefile` puts in front of it for `dp-bit.c`: `FLOAT_BIT_ORDER_MISMATCH` (the
  packed 52/11/1 bit-field union) and `FLOAT_WORD_ORDER_MISMATCH` (the final word swap). The macros are spelled out in
  the file. It is GPL-2.0-or-later with the libgcc exception, as the header comment says.
- The library text guards the quiet-NaN OR with `if (src->class == CLASS_QNAN || 1)`; the source writes the OR
  unconditionally. With the guard restored the bytes are the same (same SHA-256), so the bytes do not choose.
- pret/agbcc's Makefile compiles `dp-bit.i` with `old_agbcc -O2` and no `-mthumb-interwork`. Without that flag the
  epilogue is `pop {r4, r5, r6, r7, pc}`; the ROM has `pop {r4, r5, r6, r7}; pop {r2}; bx r2` (0x08142D1A-0x08142D1E),
  which is what `old-agbcc-O2-v1`'s `-mthumb-interwork -O2` gives.

## Ruled out

- Stock agbcc `-O2`: 336 bytes, 60 bytes differ (above). In an earlier attempt (2026-11-16, not re-run here) about
  twenty single extra flags were tried with stock agbcc as diagnostics (`-O3`, `-O`, `-fforce-addr`, `-fno-gcse`,
  `-fno-regmove`, `-fno-cse-follow-jumps`, ...); none reproduced the shared `mov r2, sp`.
- The previous revision of this entry (a hand-adapted version with a `Binary64Fields *fields = &result.bits` view for
  the exponent and sign stores) is not byte-identical with either compiler: under stock agbcc 14 bytes differ from
  0x08142CF4 on, and under `old_agbcc` 11 bytes differ from 0x08142CEC on (this attempt's runs). The canonical library
  text above replaces it.

kit issue: shubshub/fftadecomp-kit#214
