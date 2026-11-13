# 080D2AD0: byte-identical; a switch with a signed bias word before its table has no selector

Target: `[0x080D2AD0, 0x080D2BF4)`, 292 bytes. It filters 16-byte packed records (the layout of the matched `080D29D4`) with a `switch` on the 10-bit id over `0x16D..0x175`. It calls `func_080C9540`, appends matches to the output, and returns early when the limit runs out.

`080D2AD0.c` compiles to 292 bytes. Only 14 words differ from the ROM, and all of them are relocations: the table pointer, the 9 jump-table words (equal to ROM minus `0x080D2AD0`) and 4 `bl` sites. The dispatch pool holds the case bias `0xFFFFFE93` ahead of the table pointer. Refusals:

- default: `switch requires one exact adjacent unsigned guard and five-op dispatch`
- `numeric-data-switch-source-v1`: `numeric switch requires ordinary calls, zero-addend data and local table words`
- `restoring-owner-scalar-switch-v1`: `complete-owner text reachable instruction count differs`
- `two-constants-frame-v1`: `switch constants require an exact two-word gap and unsigned guarded dispatch`
- `restoring-owner-switch-aligned-v1`: `aligned owner requires actual external two-byte Thumb alignment`
- `ordinary-multiple-switch-source-v1`: `local relocation words have no unique complete guarded-table partition`

Tracked upstream: https://github.com/shubshub/fftadecomp-kit/issues/136
