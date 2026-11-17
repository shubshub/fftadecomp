# 0x0801F1A8 - recursive tile-resource loader: bytes identical, refused (a self call outside the plain direct-call path) (324 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. `func_0801F1A8(src)` loads one tile resource into the
buffer `func_0801AD1C(0)` returns, by the resource's first byte:

- 0x10: LZ77-decompress it there (`func_08141890`, `swi 0x11`);
- 1 or 0x11: a 24-bit id in bytes 1-3. For an id other than 0xFFFFFF it recurses into the resource that the 32-bit
  offset of `data_08569104[id]` selects, `func_0801F1A8((const u8 *)data_08569104 + offset)` (self calls at
  0x0801F1FE and 0x0801F264); for 0xFFFFFF it fills the buffer with the 16-bit value of `func_0801E6E4()` through
  CpuFastSet (`func_08141868`, `swi 0x0C`, control 0x01001000) from a stack word. Type 1 then passes `src + 4` to
  `func_0801F124`; type 0x11 first decompresses `src + 4` into `data_02003CB0` and passes that. Both end by
  re-binding `g_state_02007F40.transfer` through `func_0801ED24(..., 0x800)`;
- anything else: CpuFastSet copy of `src + 4` with control 0x1000.

The matched `src/0802046C.c` calls it. All four data symbols are already in `config/data_symbols.json`. The index row
`0801F1A8 0801F2EC 324 162 return` has the right extent; 162 is half the byte count, and the reachable count is 131.
It did not affect any refusal below.

## Byte identity

`0801F1A8.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0801F1A8, with callees and data bound to their ROM
addresses and the two self calls resolved against the object's own symbol (12 `R_ARM_THM_CALL`, 4 `R_ARM_ABS32`).
The 324-byte symbol equals the ROM span `[0x0801F1A8, 0x0801F2EC)`: SHA-256
`0597a38dc15fa65cac0af222e3fd6d4c0c0f8b08abc772e82c3049c24f259fd4` for both. `.text` is exactly 324 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0801F1A8.c`: the default run and all
213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default | `stack aliases cannot cross calls in caller-clobbered registers` |
| `bounded-buffer-bios-mixed-fast-fill-source-v1`, `bounded-buffer-bios-fast-fill-source-v1`, `named-data-buffer-v1` and 110 other owner selectors (113) | `owner requires unique undefined zero-valued global symbols` |
| all 42 `--addressed-signed-runtime-profile` values | `addressed calls require unique undefined zero-valued global functions` |
| all six `--function-address-profile` values | `function-thunk symbols require unique undefined global types` |
| both `--*-quotient-profile` values | `self calls are admitted only on the plain direct-call path` |
| `--control-flow-profile mixed-return-inert-spin-v1`, `--software-double-profile convert-sub-div-target-v1` | `self or intra-function addresses are unsupported` |
| `entry-recursive-ordinary-call-v1` | `refused: entry owner has an undecoded tail` |

The other 47 selector values stop on requirements this function does not meet (float helpers, an alignment pad, a
switch, the -O0 toolchain, the division runtimes).

## Cause

Since #147 the default path admits a `bl` to the function's own entry, but only on the plain direct-call path; the
kit README's "Self calls" section refuses self calls together with buffer, owner, runtime, switch and thunk
selectors. This function needs the buffer walk for its stack `fill` word, which is the CpuFastSet source
(`add r0, sp, #0x10` at 0x0801F21A and 0x0801F282). With a self call the default path cannot fall back to the buffer
proof and stops at the first call that has a local address in a caller-clobbered register. The owner selectors,
which would prove the fill, bind every call relocation to an undefined global, and the self call names the
function's own defined symbol.

What remains when only the self calls are taken away: with both self calls redirected to another indexed function
(`func_0801F124`; the variant's bytes differ from the ROM only in those two `bl` instructions, 2 bytes) and a
scratch copy of the ROM patched with the variant's 324 bytes, so that only the verifier's policy can refuse,
`--owner-runtime-profile bounded-buffer-bios-mixed-fast-fill-source-v1` reports `verdict MATCH - byte identical`
(extent `complete named-data Thumb owner with ordinary bounded-buffer calls and conditional BIOS CpuFastSet
local-word source bounds`). On the default path the same variant stops at
`buffer callee 0x08141868: non-leaf calls and interrupts require linked CFG verification`. So the self call is the
only obstacle on that selector. Neither self call passes a local address: R0 is a ROM pointer into
`data_08569104`.

## Source notes

- The id and the offset are assembled byte by byte (`(b[2] << 8) | b[1]`, then `<< 16`, then `<< 24`), in the ROM's
  order of `ldrb`s and `orrs` (0x0801F1CA-0x0801F1D6, 0x0801F1E8-0x0801F1FA). `data_08569104` entries are 0x58 bytes
  (`movs r0, #0x58; muls` at 0x0801F1DE-0x0801F1E2) with the offset at +4.
- The two recursive arms (types 1 and 0x11) repeat the same id/offset block; the ROM has both copies
  (0x0801F1CA-0x0801F1FE and 0x0801F230-0x0801F264).
- `fill` is a `u32` local whose address is the CpuFastSet source; the ROM stores `(value << 16) | value` to
  `sp + 0x10` before each fill (`str r1, [sp, #0x10]` at 0x0801F216).

## Ruled out

Nothing beyond the source above was needed: it was byte-identical as first written, and no alternative spellings
were compared. The sibling `0x0801F2EC` has the same shape and is not matched.

kit issue: (to be filed - self calls are admitted only on the plain direct-call path: recursive functions that also need an owner, BIOS-fill, runtime or switch selector are refused); shubshub/fftadecomp-kit#192 (comment to be posted): the fill summary at the call site in the root walk would cover this function without the self-call change
