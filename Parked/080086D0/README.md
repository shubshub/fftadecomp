# 0x080086D0 - 16.16 fixed-point spline evaluation: bytes identical, refused (`__muldi3` / `__divdi3` calls have no binding) (328 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. The function is the `s64` 16.16 fixed-point twin of the
matched `func_0800749C` (`src/0800749C.c`, the `double` version). It binary-searches the 8-byte `knots` for the
interval holding `position` (0x080086DA-0x08008700: the high words are compared signed, the low words unsigned), steps
back one interval when the result is above zero (0x08008702-0x08008706), and evaluates the cubic Hermite form with
16.16 products `a * b >> 16` and quotients `(a << 16) / b`. `values` and `coefficients` are the incoming stack words
at sp+0x3C and sp+0x40 (0x0800873C, 0x0800872C). There are six runtime calls: `__muldi3` (0x08142A20) at 0x08008758,
0x08008794, 0x080087DC and 0x080087FA, and `__divdi3` (0x08142280) at 0x08008774 and 0x080087C0. The index row
`080086D0 08008818 328 164 return` has the right extent (no literal pool, no padding; the last instruction is `bx r2`
at 0x08008816) but the wrong instruction count: there are 158 reachable instructions, and 164 is the number of
halfwords, with each of the six `bl` pairs counted twice. The comment at the top of the published source repeats the
index's 164. No data symbol is needed.

## Byte identity

`080086D0.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080086D0, with `__muldi3` bound to 0x08142A20 and
`__divdi3` to 0x08142280 (6 `R_ARM_THM_CALL`, no data relocations). The 328-byte symbol equals the ROM span
`[0x080086D0, 0x08008818)`: SHA-256 `934f8fb11562dfab77b1e78b8d92b218257ecf727bb246a82af276474ee2092a` for both.
`.text` is exactly 328 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict`
exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080086D0.c`: the default run and all 213
selector values. None matched.

| Selector | Refusal |
|---|---|
| default, both `--*-quotient-profile` values, both `--signed-runtime-profile` values, `--unsigned-runtime-profile unsigned-divmod-ten-v1`, the six `--function-address-profile` values and the ten `--switch-data-profile` values (22) | `call target must be an undefined addressed function` |
| all 42 `--addressed-signed-runtime-profile` values; 113 owner-runtime selectors, among them `named-data-buffer-v1`, `bounded-buffer-runtime-summaries-v1`, `restoring-owner-runtime-v1`, `canonical-integer-scalar-source-v1` and `static-callback-buffer-v1`; `--software-double-profile convert-sub-div-target-v1`; `--control-flow-profile mixed-return-inert-spin-v1` (157) | `function address requires a canonical addressed function` |
| the three `--switch-profile` values | `unsupported compiler assembly statement: 'ldr\tr0, [r3, #8]\t\t@ created by thumb_load_double_from_address'` |

The other 32 selector values stop on requirements this function does not meet: a private float or double helper (15),
an external two-byte alignment pad (12), the -O0 toolchain, a palette bundle, a 96-byte owner, an entry-recursive
owner without a frame, or the software-double remainder profile.

## Cause

`match.py` resolves each call relocation by its symbol name (`tools/match.py:842-950` at 18dcc516): a
`func_XXXXXXXX` name, a `_call_via_rN` helper, or one of the compiler runtime names that a selected profile binds
(`__modsi3`, `__divsi3`, `__udivsi3`, `__umodsi3`, `__ashldi3`, `__lshrdi3`, and the software-double and software-float
operations). No profile binds `__muldi3` or `__divdi3`. They therefore reach the generic branch, which requires a
`func_XXXXXXXX` name and refuses with `call target must be an undefined addressed function` (`tools/match.py:942-944`).
The selectors that resolve calls through `function_address_target` (`tools/match.py:607-610`) apply the same
requirement and refuse with `function address requires a canonical addressed function`.
Spelling the calls as `func_08142A20` / `func_08142280` does not help. 0x08142A20 lies inside the identities that
the software-double and software-float profiles reserve, so the same branch refuses it with `division runtime
requires its canonical compiler alias` (`tools/match.py:948-949`). It would also mean naming the runtime routine in
place of the `*` the compiler emits.

## Source notes

- The declaration order of the block locals is load-bearing. `offset` is declared before `width` even though `width`
  is computed first: the ROM keeps `offset` at sp+0 (0x08008728) and `width` at sp+8 (0x08008720). With the two
  declarations swapped, the slots swap (below).
- `coefficient + coefficient + coefficient` is spelled as a sum because the ROM forms `2 * coefficient` once with
  `adds`/`adcs` (0x0800877C-0x0800877E), keeps it at sp+0x20, adds `coefficient` and the quotient to it
  (0x08008784-0x0800878A), and later adds `next_coefficient` to the same doubled value (0x080087C8-0x080087D2).
  `3 * coefficient` does not give these bytes (below).
- The `>> 16` after each product is an arithmetic 64-bit shift (`asrs r1, r1, #0x10` with the low word rebuilt, as at
  0x0800875C-0x08008764), so the operands are signed `s64`. The `(... >> 16) << 16` before the first division
  (0x08008766-0x0800876E) is kept as written. It clears the low 16 bits of the scaled product, and the ROM does
  both shifts.
- The prototype follows `src/0800749C.c`: `(s64 position, s32 count, const s64 *knots, const s64 *values,
  const s64 *coefficients)`. No caller was used to check the parameter types.

## Ruled out

- `width` declared before `offset`: 328 bytes, 20 differ, first at 0x08008710 (the two stack slots swap).
- `3 * coefficient` in place of the sum: 352 bytes; 223 of the overlapping bytes differ, first at 0x08008730.
- Explicit `func_08142A20(a, b)` / `func_08142280(a, b)` calls in place of `*` and `/`: 328 bytes, 66 differ, first
  at 0x0800879C. `match.py` refuses it with `division runtime requires its canonical compiler alias`.
- The previously parked copy (one flat block of locals, the same arithmetic split over named temporaries) is also
  byte-identical when linked the same way. The published copy uses the shape and names of `src/0800749C.c`.

kit issue: shubshub/fftadecomp-kit#80
