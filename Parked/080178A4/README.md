# 0x080178A4 - two-row tile copy with a palette callback: bytes identical, refused (signed remainder combined with a `_call_via_r3` callback) (248 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. The function copies two tile rows of a scrolling region
into a destination map; its record is the one the matched `0x0801799C` (`src/0801799C.c`) recolours. The source row
is `(field_1A + row) << 1` wrapped by `rows << 1` through `func_08142950` (`__modsi3`, `bl` at 0x080178C6), scaled by
`stride` and added to the tile pointer at +0xC (0x080178CA-0x080178D6). The destination row is `(row << 1) *
field_1E` halfwords past the pointer at +8 (0x080178D8-0x080178E2). Each row is copied by a 16-bit CpuSet
(`func_0814186C`, `svc 0xB`, called at 0x08017900) of `stride` halfwords. If the callback at +0 is set (`ldr r3,
[r6]` at 0x08017904), it is called through `_call_via_r3` (0x08142250, `bl` at 0x08017918) with the context at +4 and
`line >> 1`. Its byte becomes the palette (bits 12-15) of the row's first two entries. `flags & 4` (+0x10) gives the
last two entries palette 0xD (0x08017934-0x08017966). The `u16` loop counter lives in a 4-byte frame (`str` at
0x080178E8 and 0x0801797C). The index row `080178A4 0801799C 248 116 return` is right: 116 reachable instructions,
then a zero alignment halfword at 0x08017992 and the two pool words 0x00000FFF and 0x001FFFFF. No data symbol is
needed.

## Byte identity

`080178A4.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080178A4. `func_08142950`, `func_0814186C` and
`_call_via_r3` were bound to their ROM addresses 0x08142950, 0x0814186C and 0x08142250 (3 `R_ARM_THM_CALL`, no data
relocations). The 248-byte symbol equals the ROM span `[0x080178A4, 0x0801799C)`: SHA-256
`ed96371b279b9735fa31fe27bde93d880949e83cde581cf0dd3e17c81157acb6` for both. `.text` is exactly 248 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080178A4.c`: the default run and all 213
selector values. None matched.

| Selector | Refusal |
|---|---|
| default, `--signed-quotient-profile positive-constant-frame-v1`, `--unsigned-quotient-profile positive-constant-frame-v1`, the eight `--switch-data-profile u16-scalars-*` / `typed-outgoing-six-words-v1` values and both `--switch-data-profile switch-thunks*` values (13) | `signed remainder excludes mixed aliases, addressed calls with data, and other profiles` |
| `--addressed-signed-runtime-profile addressed-signed-runtime-r3-callback-data-v1` | `addressed runtime ELF requires actual addressed calls and no unresolved symbols` |
| `--function-address-profile canonical-thunks-v1` and the other five `--function-address-profile` values, `--unsigned-runtime-profile unsigned-divmod-ten-v1` (7) | `signed remainder requires its isolated binding profile` |
| `bounded-buffer-runtime-summaries-v1`, `bounded-buffer-bios-mixed-fast-fill-runtime-summaries-v1` | `runtime summary owner requires exact canonical division entries and no thunks` |
| `--signed-runtime-profile numeric-divmod-v1`, `--signed-runtime-profile numeric-divmod-lsr-v1` | `signed divmod requires both canonical original runtime relocations` |
| `--addressed-signed-runtime-profile compiler-signed-runtime-data-v1` and its two `numeric-mmio` variants (3) | `compiler runtime identifiers cannot occur in preprocessed C` |
| `static-callback-buffer-v1`, `static-callback-restoring-r6-target-v1`, `restoring-owner-runtime-v1`, `named-data-buffer-v1`, `bounded-buffer-root-return-scratch-v1`, `canonical-integer-scalar-source-v1` and 105 other owner-runtime selectors; the five `addressed-unsigned-runtime-*` values, `--software-double-profile convert-sub-div-target-v1`, the three `--switch-profile` values, `--control-flow-profile mixed-return-inert-spin-v1` (121) | `division runtime requires its canonical versioned proof` |
| `--addressed-signed-runtime-profile addressed-signed-runtime-v1`, `addressed-signed-runtime-data-v1`, `addressed-signed-runtime-r2-callback-data-v1` and the other 30 addressed signed, integer and native-BIOS values (33) | `function address requires a canonical addressed function` |

The other 32 selector values stop on requirements this function does not meet: a private float or double helper (15),
an external two-byte alignment pad (12), the -O0 toolchain, a palette bundle, a 96-byte owner, an entry-recursive
owner without a frame, or the software-double remainder profile.

## Cause

`match.py` has a binding for an explicit signed remainder. A call named `func_08142950` (`modsi3_profile.ADDRESSED_NAME`,
`tools/modsi3_profile.py:10`) is accepted, and that is how the sibling `src/0801799C.c` matched
(`elf-symbol-thumb-frame-calls-v1`). The signed-remainder gate at `tools/match.py:1047-1054` refuses a compile in which
any other call target is one of the `_call_via_rN` helpers (`RUNTIME_HELPERS`, `tools/match.py:129`). This function
reaches its callback through `_call_via_r3`; the pointer is read from the record's first word at run time
(0x08017904). The plain `%` spelling (below) emits `__modsi3` and stops at the same gate.

The only selector that accepts an addressed signed runtime together with a `_call_via_r3` callback is
`addressed-signed-runtime-r3-callback-data-v1`. It is a data variant: it links typed data relocations and refuses an
object that has none (`tools/addressed_signed_runtime_profile.py:940-943`), and this function references no named
data. No data-free r3-callback variant exists (`tools/addressed_signed_runtime_profile.py:44-47, 104`). The
owner-runtime selectors, the static-callback ones among them, stop earlier: `function_address_target` refuses
0x08142950 as a reserved runtime address (`tools/match.py:607-613`).

## Source notes

- `u16 line = first;` is a second copy of the remainder. The ROM keeps the remainder twice: R0 scales the source row
  (0x080178CA-0x080178D0), and SL, set at 0x080178E4, is the callback's line counter. SL is advanced
  (0x0801790E-0x08017914) only on the path where the callback is present. Incrementing `first` itself does not give
  these bytes (below). The bytes do not show whether the original had two variables or some other spelling that
  yields the second register.
- The remainder is written as an explicit call to `func_08142950`, as in `src/0801799C.c`. Plain `%` on the same
  operands is also byte-identical (below).
- The CpuSet count is spelled `((stride * sizeof(u16)) >> 1) & 0x1FFFFF`. The ROM doubles `stride` once
  (0x080178EC), keeps the doubled value in R8 for the last-two-entries offsets (0x0801793E-0x08017944), and halves it
  again for the CpuSet count (0x080178F6).
- The callback is declared `u8 (*)(void *context, u16 line)`. The result is narrowed with `lsls #24` (0x0801791C) and
  the argument is `line >> 1` of a `u16` (0x08017916). The callback's own type is not otherwise known.
- `field_1A` (the scroll row, `ldrh` at 0x080178BA) and `field_1E` (the destination row pitch, `ldrb` at 0x080178DA and
  0x0801796E) keep the names they have in `src/0801799C.c`. Their meaning beyond these uses is not recovered.

## Ruled out

- Incrementing `first` in the callback call and dropping `line`: 248 bytes, 186 differ, first at 0x080178CE.
- Plain `%` instead of `func_08142950(...)`: byte-identical (the relocation becomes `__modsi3`). `match.py` refuses it
  by default with the same `signed remainder excludes mixed aliases, addressed calls with data, and other profiles`.
  With `canonical-integer-scalar-source-v1` the refusal is `canonical integer source requires call-only compiler
  integer identities`. With `--function-address-profile canonical-thunks-v1` it is `signed remainder requires its
  isolated binding profile`. With `--addressed-signed-runtime-profile addressed-signed-runtime-r3-callback-data-v1`
  it is `function address requires a canonical addressed function`.
- The previously parked copy (other member names, an `int row` temporary, `* 2` instead of `<< 1`) is also
  byte-identical. The published copy drops the temporary and takes the member names and `<< 1` from
  `src/0801799C.c`.

kit issue: shubshub/fftadecomp-kit#134
