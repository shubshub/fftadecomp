# 0x0801A320 - map palette load: bytes identical, refused (a CpuSet fill from a stack zero beside a named callback word) (268 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `func_0801A320()` loads the palette of the current map entry
`data_02007F10` into `data_03003860`. For entry 0xFF it gets the first index and count from `func_0801E6D4(&first,
&count)` and clears `count * 16` halfwords with CpuSet from a stack zero (`func_0814186C(&zero, data_03003860,
0x01000000 | (count << 4))`, 0x0801A34C). Otherwise it keeps colour 0, gets the range the same way, and by the mode
`func_0801AE9C()` returns either decompresses the entry's palette from `data_08569104` (`func_08141890`, LZ77) or
copies it through `data_0836D4BC[0]` (`_call_via_r3` at 0x0801A3D2), or for modes 1 and 2 expands it from
`data_08427A04` or `data_0842CC80` with `func_0800543C`; then it restores colour 0. Its caller is 0x0801A15C.

The index row `0801A320 0801A42C 268 134 return` has the right extent; 134 is half the byte count, and the reachable
count is 106 (the kit's own refinement and an independent CFG walk agree). The bogus index row inside `data_08569104`
that an earlier note mentions (`08568C6E`) is no longer in the index.

## Byte identity

`0801A320.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0801A320, with every callee and data symbol bound to its
ROM address (8 `R_ARM_THM_CALL`, 9 `R_ARM_ABS32`). The 268-byte symbol equals the ROM span `[0x0801A320, 0x0801A42C)`:
SHA-256 `019f2624ea2301a59317debf41667fc7408d76346b7316378e8b2be3b39f09e7` for both. `.text` is exactly 268 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0801A320.c` (no data symbol to add): the
default run and the selectors the kit issue and the earlier notes discuss.

| Selector | Result |
|---|---|
| default | `buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification` |
| `named-data-buffer-v1`, `bounded-buffer-bios-fill-source-v1` | `acyclic owner excludes arithmetic runtimes and indirect thunks` |
| `--addressed-signed-runtime-profile addressed-native-bios-fill-saved-scalar-control-numeric-mmio-data-v1`, `--addressed-signed-runtime-profile addressed-native-bios-fill-buffer-data-v1` | `function address requires a canonical addressed function` |

## Cause

The stack zero is the CpuSet fill source, so the default buffer walk enters the wrapper `func_0814186C` and refuses
its `svc` (`non-leaf calls and interrupts require linked CFG verification`). The BIOS fill selectors would admit the
fill but not the `_call_via_r3` call through the named word `data_0836D4BC` (`function address requires a canonical
addressed function`), and `named-data-buffer-v1` refuses that thunk outright.

kit issue: (to be filed - match.py: named data and the generic buffer proof never compose, on the plain path (`buffer-call evidence does not support data relocations`) or on the function-literal path (no buffer fallback with data)); shubshub/fftadecomp-kit#192 (comment to be posted)
