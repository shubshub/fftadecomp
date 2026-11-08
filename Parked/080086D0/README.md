# 080086D0

Complete indexed target [0x080086D0, 0x08008818), 328 bytes.

`s64 func_080086D0(s64 x, s32 count, s64 *knots, s64 *values, s64 *slopes)`
is a 64-bit fixed-point spline interpolation. It binary-searches `knots`,
then interpolates with 16.16 multiplies and divides (`a*b >> 16` and
`(a << 16) / h`). The arithmetic is written with plain `s64` `*` and `/`.
`values` and `slopes` are read from sp+0x3C and sp+0x40. The h/dx
stack-slot order needs `s64 dx, h, ...` declared in that order.

## Bytes: identical except the six unrelocated runtime `bl`s

`080086D0.c` was compiled with the fixed `agbcc -mthumb-interwork -O2`,
assembled, and its `.text` extracted: 328 bytes. The only differing bytes are
the six runtime `bl` sites. Their relocations come in the target's order:
`__muldi3` (0x08142A20) and `__divdi3` (0x08142280).

## Why it is not in src/

* Plain operators: "call target must be an undefined addressed function"; no
  canonical binding exists for `__muldi3` or `__divdi3`.
* Plain operators with `canonical-integer-scalar-source-v1`,
  `addressed-integer-runtime-v1` or `addressed-signed-runtime-v1`: "function
  address requires a canonical addressed function".
* Explicit `func_08142A20` calls: "division runtime requires its canonical
  compiler alias". The software-double profile reserves 0x08142A20.

No tooling was changed.

Tracked upstream: https://github.com/shubshub/fftadecomp-kit/issues/80
