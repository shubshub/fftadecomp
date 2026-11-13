# 080178A4: byte-identical; `__modsi3` with an object-field `_call_via_r3` callback has no selector

Target: `[0x080178A4, 0x0801799C)`, 248 bytes. It copies two tile rows of a scrolling window, using the same record as the matched `08085558` and `08017B9C`: a callback at +0 and its context at +4. The row comes from an explicit `func_08142950` (`__modsi3`). The copy goes through the CpuSet wrapper `func_0814186C`. The palette byte comes from the record's callback, which the compiler calls through `_call_via_r3`. A 4-byte frame holds a spilled `u16` loop counter.

Compiled by hand, all 248 bytes match. The three `bl` relocations are `func_08142950`, `func_0814186C` and `_call_via_r3`, which are the ROM's targets. `plausible.py` reports nothing. Refusals:

- default: `signed remainder excludes mixed aliases, addressed calls with data, and other profiles`;
- `canonical-thunks-v1`: `signed remainder requires its isolated binding profile`;
- `addressed-signed-runtime-r3-callback-data-v1`: `addressed runtime ELF requires actual addressed calls and no unresolved symbols` (no named data, and the callback comes from an object field, not a table literal);
- `addressed-native-bios-ordinary-v1`, `addressed-signed-runtime-v1`: `function address requires a canonical addressed function`;
- `restoring-owner-runtime-v1`: `division runtime requires its canonical versioned proof`;
- plain `%` with `canonical-integer-scalar-source-v1`: `canonical integer source requires call-only compiler integer identities`.

Tracked upstream: https://github.com/shubshub/fftadecomp-kit/issues/134
