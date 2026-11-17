# 0x08132CB8 - random pick of a matching unit slot: bytes identical, refused (variable index into a local u8[8]; the modulo runtime) (204 bytes)

Attempt 2026-11-18, kit 750d2fb7, decomp main 52ef3ba2f9.
`func_08132CB8(state, wanted)` records in a local `u8 found[8]` which of the unit's five slots (`func_080C7EA4(unit,
0x1D + i)`) hold an entry whose `func_080CA7A4(entry, 3)` equals `wanted`, picks one with `func_08002804() % count`
(`__modsi3` at 0x08132D18), stores the entry and applies it (`func_080CAF78`, `func_080CB54C`; `func_080CA9E8` when
`func_08131BB8` holds for the unit, `func_080CA900` when it holds for the state's first word; then `func_080CA2E8`)
and returns 1, or 0 when none matches. Its caller is the matched `src/08132EE8.c` (ten sites,
0x0813303C-0x081330BC).

The index row `08132CB8 08132D84 204 102 return` has the right extent; 102 is half the byte count, and the reachable
count is 90 (the kit's own CFG refinement). `config/functions.json` has the same extent and count.

## Byte identity

`08132CB8.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08132CB8, with every callee and data symbol bound to its
ROM address (12 `R_ARM_THM_CALL`; `__modsi3` at 0x08142950). The 204-byte symbol equals the ROM span `[0x08132CB8,
0x08132D84)`: SHA-256 `cc5244fd9183f20b13698dbe83958fb64f1b472433684edd1125c55b5fa748ac` for both. `.text` is exactly
204 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 750d2fb7, `match.py --root . --no-write` with this source copied to `src/08132CB8.c` (no data symbol to add): the
default run, the two stack-index selectors and the ROM-table-copy selector the #200 comment discusses, and the
known-query stack-buffer and finite-loop selectors earlier notes name. None matched.

| Selector | Result |
|---|---|
| default | `unsupported stack-alias use or escape` |
| `named-data-buffer-stack-index-v1`, `named-data-buffer-stack-index-v2`, `named-data-buffer-rom-table-copy-v1` and 3 other selectors (6) | `function address requires a canonical addressed function` |

The 3 others are `conditional-known-query-stack-buffer-v1`, `conditional-finite-local-word-loops-v1` and
`conditional-finite-spilled-scalar-loops-v1`. Of all 215 selector values, 149 give `function address requires a
canonical addressed function` and none matches.

## Cause

The default path refuses the variable index into the local array (`unsupported stack-alias use or escape`). The
stack-index selectors refuse the compiler's `__modsi3` relocation (`function address requires a canonical addressed
function`), as for 0x08128E40; that is the #200 comment's row for this function.

## Source notes

- The modulo is the `%` operator. An earlier text called the runtime explicitly, `func_08142950(func_08002804(),
  count)`; it gives the same bytes (same SHA-256, measured), so the explicit call is only a spelling, and it is not
  used. That spelling's refusals differ: the default is the same, but the stack-index, ROM-table-copy, known-query
  and finite-loop selectors give `division runtime requires its canonical versioned proof`.

kit issue: shubshub/fftadecomp-kit#200 (comment)
