# 0x0802C8C4 - object tile block rebuild: bytes identical, refused (CpuSet fills from stack zeros beside named _call_via_r3 copies) (304 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `func_0802C8C4(object)` rebuilds the object's tile block and
queues it for VRAM. With bit 1 of `object->flags` set it clears the block with CpuSet from a stack zero
(`func_0814186C(fill_source, tiles, 0x01000180)`, 0x0802C8E8), copies four tile groups from `data_0200F440 + 0x8FC`,
`+ 0xA3C` (only when `field_16 < 0`), `+ 0xF5C` and `+ 0xA1C` through `data_0836D4BC[0]` (`_call_via_r3`, four sites
from 0x0802C8FE), and draws two numbers with `func_0802C830`. Otherwise it clears a 0x300-byte allocation from
`func_08022840` the same way (0x0802C99C), draws text into it with `func_08015110`, converts it into the block with
`func_0802BAF8` and frees it. Both paths end with `func_08000ADC(func_0802BA08(), object->tiles, 0x060097C0, 0xC0)`.
The matched `src/0802CABC.c` calls it.

The index row `0802C8C4 0802C9F4 304 117 return` is right (117 reachable instructions).

## Byte identity

`0802C8C4.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0802C8C4, with every callee and data symbol bound to its
ROM address (15 `R_ARM_THM_CALL`, 3 `R_ARM_ABS32`). The 304-byte symbol equals the ROM span `[0x0802C8C4,
0x0802C9F4)`: SHA-256 `7d0d0c679e3287b7d44228af766a4a93fad11f5f1bc8bf0a6dacad1f60dae32d` for both. `.text` is exactly
304 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0802C8C4.c` (no data symbol to add): the
default run and the selectors the kit issue and the earlier notes discuss.

| Selector | Result |
|---|---|
| default | `buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification` |
| `named-data-buffer-v1`, `bounded-buffer-bios-fill-source-v1` | `acyclic owner excludes arithmetic runtimes and indirect thunks` |
| `--addressed-signed-runtime-profile addressed-native-bios-fill-saved-scalar-control-numeric-mmio-data-v1`, `--addressed-signed-runtime-profile addressed-native-bios-fill-buffer-data-v1` | `function address requires a canonical addressed function` |

## Cause

The stack zeros are CpuSet fill sources, so the default walk enters `func_0814186C` and refuses its `svc`. The fill
selectors would admit the fills but not the `_call_via_r3` calls through the named word `data_0836D4BC` (`function
address requires a canonical addressed function`), and `named-data-buffer-v1` refuses those thunks outright.

## Source notes

- The first arm writes the fill source as `u16 *fill_source = &fill; *fill_source = 0;`, the second as `u16 clear = 0;
  ... &clear`. The plain form in the first arm gives 304 bytes with 71 halfwords different from 0x0802C8DC on, so the
  pointer local is load-bearing. It is the fill-source idiom of the matched `src/08137B20.c` and `src/0805868C.c` and
  rests on that precedent.

kit issue: shubshub/fftadecomp-kit#236; shubshub/fftadecomp-kit#192 (comment)
