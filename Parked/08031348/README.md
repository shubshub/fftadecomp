# 0x08031348 - display layer clear and graphics load: bytes identical, refused (CpuSet fills from stack zeros with counts from bytes) (384 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `func_08031348()` clears the tile maps of four display
records (`data_03000E60`, `data_03000E80`, `data_030008B0`, `data_03000990`; `width * height` halfwords each) and
0x4000 halfwords at the first record's tiles with CpuSet from stack zeros (five `func_0814186C` calls,
0x0803136C-0x080313BA). It decompresses six graphics blocks into `data_02003CB0` with `func_08005318` or
`func_0800543C` and copies each to VRAM with CpuFastSet (`func_08141868`, six calls), clears both halves of
`data_03003860` with word fills from stack zeros (`0x05000080`), and calls `func_080314C8(0)`. Callers: the matched
`src/0803172C.c` and 0x08030200.

The index row `08031348 080314C8 384 131 return` is right (131 reachable instructions).

## Byte identity

`08031348.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08031348, with every callee and data symbol bound to its
ROM address (20 `R_ARM_THM_CALL`, 18 `R_ARM_ABS32`). The 384-byte symbol equals the ROM span `[0x08031348,
0x080314C8)`: SHA-256 `140e2f786775b2f779d93f17ae2e27c92657c64cfcce57dc20e77911f8b5c5e4` for both. `.text` is exactly
384 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08031348.c` and `data_06010100`,
`data_06010E40`, `data_060134C0`, `data_083AA184`, `data_083ADB08`, `data_083AE194` added to
`config/data_symbols.json` (each at the address its name gives): the default run and the selectors the kit issue and
the earlier notes discuss.

| Selector | Result |
|---|---|
| default, `named-data-buffer-v1` | `buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification` |
| `--addressed-signed-runtime-profile addressed-native-bios-fill-saved-scalar-control-numeric-mmio-data-v1`, `bounded-buffer-bios-fill-source-v1`, `--addressed-signed-runtime-profile addressed-native-bios-fill-buffer-data-v1` | `buffer access is unaligned or outside allocated local words` |

## Cause

The default walk enters the CpuSet wrapper `func_0814186C` and refuses its `svc`. The BIOS fill selectors admit a
stack fill source but must prove the control word's unit size; here the four counts are `width * height` of two
zero-extended bytes (`ldrb`, `muls`), which their bit prover does not follow, so bit 26 (32-bit units) is not proved
clear and the source unit is taken as a word past the halfword local (`buffer access is unaligned or outside allocated
local words`).

## Source notes

- The five halfword fills use `sourceN = &fillN; *sourceN = 0;`, the idiom of the matched `src/0804DDCC.c`. The plain
  `fillN = 0; func_0814186C(&fillN, ...)` gives 392 bytes against 384 (29 halfwords differ from 0x08031350), so the
  pointer locals are load-bearing and rest on that precedent.
- Six data symbols (three VRAM destinations and three compressed sources) are not in `config/data_symbols.json`; the
  refusal runs add them (above).

kit issue: shubshub/fftadecomp-kit#236; shubshub/fftadecomp-kit#192 (comment)
