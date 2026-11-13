# 0813DE38: byte-identical; signed division with four incoming stack words and numeric MMIO has no selector

Target: `[0x0813DE38, 0x0813DF5C)`, 292 bytes. This builds a per-scanline BLDALPHA table:
- rows `[0, start)` get the "from" value;
- rows `[start, end)` interpolate in 8.8 fixed point, with the step computed by a signed `/`;
- rows `[end, 160)` get the "to" value.

It finishes with `func_08000D48(channel, buffer, (void *)0x04000052, 0x20400001)`, the same shape as the matched `0813EDA0` and `08057B90`. Four of its eight arguments arrive on the stack, at `[sp,#0x38..0x44]`.

`0813DE38.c` compiles to all 292 bytes, apart from the three unlinked `bl` sites. `plausible.py --strict` reports nothing. Refusals:

- `addressed-signed-runtime-v1` (explicit `func_081426B8`): `addressed signed runtimes exclude address literals and data bindings`
- `compiler-signed-runtime-numeric-mmio-data-v1`: `local branch access leaves its established frame` (no incoming-word policy)
- `canonical-integer-scalar-source-v1`: `local branch access leaves its established frame`
- `canonical-integer-scalar-data-source-v1`, `canonical-integer-six-words-data-source-v1`: `six-word integer source requires canonical integer calls and zero-addend named objects`

Tracked upstream: https://github.com/shubshub/fftadecomp-kit/issues/75
