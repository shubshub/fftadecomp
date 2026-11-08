# 0804FFB8

Complete indexed target [0x0804FFB8, 0x0805005C), 164 bytes.

This is a number drawing routine. It calls the unsigned division runtimes
`func_08142AB0` and `func_08142B28` explicitly, and draws through
`func_080161A0`. It takes five arguments, the u8 flag being the fifth, read
from `[sp,#0x14]`.

## Bytes: identical

`0804FFB8.c` was compiled with the fixed `agbcc -mthumb-interwork -O2`,
assembled, and its `.text` extracted. All 164 bytes equal the ROM except the
five unrelocated `bl` sites. The pool holds only numeric constants
(0x601E, 0xD01E). `plausible.py` reports no findings.

## Why it is not in src/

* `addressed-unsigned-runtime-v1` and
  `addressed-unsigned-runtime-native-buffer-v1`: "local branch access leaves
  its established frame". This is the read of the incoming stack argument.
* `--unsigned-runtime-profile unsigned-divmod-ten-v1` with plain `/` and `%`:
  "unsigned divmod requires one actual canonical quotient and remainder call".
  This function makes two of each.
* `bounded-buffer-three-halfword-output-v1` and
  `bounded-buffer-three-output-dynamic-division-v1`: "division runtime
  requires its canonical versioned proof", or "function address requires a
  canonical addressed function" with plain operators.
* Default: "division runtime requires its canonical compiler alias".

Verifying this needs an addressed unsigned-runtime frame proof that admits
incoming stack-argument reads. No tooling was changed.

Tracked upstream: https://github.com/shubshub/fftadecomp-kit/issues/75
