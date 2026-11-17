# 0x08132064 - eight-byte random shuffle: bytes identical, refused (signed remainder with a _call_via_r3 copy callback on a local table) (132 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. Unless bit 4 of `object->flags` is set, the function copies
eight bytes from `data_083A8C0C` (`00 00 00 01 04 04 02 03`) into a local `u8 table[8]` through the copy callback
`data_0836D4BC[0]` (`_call_via_r3`), then moves them in random order into `object->unit->order[1..8]`: each step
takes `index = (s16)func_08002804() % count` (`func_08142950`, the signed remainder), stores `table[index]` and
closes the gap with an overlapping copy through the same callback, `data_0836D4BC[0](&table[index],
&table[index + 1], count - index - 1)`. The index row `08132064 081320E8 132 66 return` has the right extent; 66 is
half the byte count, and the reachable count is 57 (the kit's own refinement agrees).

One data symbol is not in `config/data_symbols.json` on main: `data_083A8C0C`, the eight source bytes, the only
aligned ROM word with that value (the literal at 0x081320E4, loaded at 0x0813207A as the copy's source). It is not
added by this entry; the refusals below were run with it added in a scratch copy of the map.

## Byte identity

`08132064.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08132064, with callees and data at their ROM
addresses, `func_08142950` (`__modsi3`) at 0x08142950 and `_call_via_r3` at 0x08142250 (4 `R_ARM_THM_CALL`, 2
`R_ARM_ABS32`). The 132-byte symbol equals the ROM span `[0x08132064, 0x081320E8)`: SHA-256
`e66bb4460ca6af5cce72063102c7355a22fd51d7932ae17fda7c4553446972d6` for both. `.text` is exactly 132 bytes. `match.py`
refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

This revision calls the remainder by name, `func_08142950((s16)func_08002804(), count)`, and indexes the callback
table (`data_0836D4BC[0](...)`). The earlier copy in this directory wrote `(s16)func_08002804() % count`, which agbcc
compiles to a call to `__modsi3`, and declared the callback as a single pointer; it gives the same bytes and the same
SHA-256.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08132064.c` and `data_083A8C0C`
added: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, both `--*-quotient-profile` values, all ten `--switch-data-profile` values (13) | `signed remainder excludes mixed aliases, addressed calls with data, and other profiles` |
| `--addressed-signed-runtime-profile addressed-signed-runtime-r3-callback-data-v1` | `stack aliases cannot cross calls in caller-clobbered registers` |
| `bounded-buffer-runtime-summaries-v1`, `bounded-buffer-bios-mixed-fast-fill-runtime-summaries-v1` | `runtime summary owner requires exact canonical division entries and no thunks` |
| `named-data-buffer-v1`, `restoring-owner-acyclic-v1` and 109 other owner selectors (111) | `division runtime requires its canonical versioned proof` |
| `--control-flow-profile mixed-return-inert-spin-v1` and 39 addressed-runtime selectors (40) | `function address requires a canonical addressed function` |
| `--addressed-signed-runtime-profile compiler-signed-runtime-data-v1` and its two MMIO variants | `compiler runtime identifiers cannot occur in preprocessed C` |
| every `--function-address-profile` value, `--unsigned-runtime-profile unsigned-divmod-ten-v1` (7) | `signed remainder requires its isolated binding profile` |

The other 37 selector values stop on requirements this function does not meet (float helpers, an alignment pad, a
switch, the -O0 toolchain).

With the earlier `%` spelling the default refusal is the same, and `addressed-signed-runtime-r3-callback-data-v1`
stops one step earlier, at the compiler's `__modsi3` name: `function address requires a canonical addressed
function`.

## Cause

The function combines a signed remainder, a `_call_via_r3` callback read from a ROM table (`data_0836D4BC`), and a
local buffer passed to that callback. The default path refuses a signed remainder together with the callback and the
data words. The one selector that binds an explicit `func_08142950` together with an r3 callback,
`addressed-signed-runtime-r3-callback-data-v1`, gets past the binding and refuses the local `table` passed to the
copier: the first copy uses it as the destination of an 8-byte copy from ROM, the second as both destination and
source of an overlapping copy whose address and size vary with `index` and `count`. That last part is the local
buffer passed to a `_call_via_rN` callback of kit #190.

## Source notes

- Both loop exits are in the ROM: `cmp r6, #8; bgt` at 0x081320CA and `cmp r5, #0; bne` at 0x081320CE, so the
  loop is written `for (i = 1; i <= 8 && count != 0; i++, count--)`.
- `count` is a `u8`; `rest` is computed after the store, as the ROM orders it.
- `Unit` names only `order[9]` at +0xC (elements 1..8 are written).

## Ruled out

- `(s16)func_08002804() % count` (the earlier copy): same bytes; refused one step earlier by the r3-callback selector.

kit issue: shubshub/fftadecomp-kit#134 (signed remainder with a _call_via_r3 callback); the local table passed to the callback is the case of shubshub/fftadecomp-kit#190
