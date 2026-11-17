# 0x0803D034 - unit group list build: bytes identical, refused (a local count passed to a callee that keeps it in its frame); not shippable as written (96 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `func_0803D034(list, result)` initialises the list from
`data_083918C4` with CpuSet (`func_0814186C(src, list, 14)`, 14 halfwords, 0x0803D044), points `list->entries` at its
storage, and for a non-zero group `g_state_03002810->data->group` fills the list with `func_0803CDAC(&count, group,
entries)` (groups 2 to 6 only) and sets `*result = func_0803CEF8(&count, group, entries, 1)`; `count` is a stack word.
Its caller is 0x0803AE80.

The index row `0803D034 0803D094 96 48 return` has the right extent; 48 is half the byte count, and the reachable
count is 40 (the kit's own refinement and an independent CFG walk agree). No refusal below depends on it.

## Byte identity

`0803D034.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0803D034, with every callee and data symbol bound to its
ROM address (3 `R_ARM_THM_CALL`, 2 `R_ARM_ABS32`). The 96-byte symbol equals the ROM span `[0x0803D034, 0x0803D094)`:
SHA-256 `1f1efed0cb557bc9cb3562940c5afd42fbb5dbfc69f4a61de49216e819588da8` for both. `.text` is exactly 96 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0803D034.c` and `data_083918C4` added to
`config/data_symbols.json` (each at the address its name gives): the default run and the selectors the kit issue and
the earlier notes discuss.

| Selector | Result |
|---|---|
| default, `named-data-buffer-stack-index-v1` | `buffer callee 0x0803CEF8: unsupported buffer pointer use or escape` |
| `named-data-buffer-stack-index-v2` | `buffer callee 0x0803CEF8: forwarded buffer pointer slot needs a callee with only immediate SP uses` |

## Cause

The walk follows `&count` into `func_0803CEF8` (matched `src/0803CEF8.c`), which keeps the pointer in its own frame
(`str r0, [sp]` and `str r0, [sp, #0xc]`, 0x0803CF04-0x0803CF12) and also passes its own frame address on (`mov r2,
sp` at 0x0803CF5E). The default walk refuses the spill; `named-data-buffer-stack-index-v2`, which admits a forwarded
pointer slot, refuses on the callee's SP uses (`forwarded buffer pointer slot needs a callee with only immediate SP
uses`).

## Why it does not ship as written

`s32 group = 0;` is a dead initialiser (`group` is assigned before any read) and `const u8 *src = data_083918C4;` a
spare temporary. Both move bytes: without the initialiser 11 halfwords differ (from 0x0803D03E), without `src` 2
(0x0803D03C-0x0803D03E). The earlier notes record that both exist only for instruction order. The entry is parked for
the verifier evidence; the source needs a natural spelling before it could ship.

## Source notes

- `data_083918C4` is not in `config/data_symbols.json`; the refusal runs add it (above).

kit issue: shubshub/fftadecomp-kit#238
