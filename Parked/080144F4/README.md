# 0x080144F4 - widest line of an encoded text: bytes identical, refused (self calls with a jump table and local buffers) (644 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. `u16 func_080144F4(const u8 *string, u8 align)` measures
the widest line of an encoded string. Two-byte glyph codes add `func_08013A5C(code & 0x7FFF)`; an `@` code
dispatches through an 89-entry jump table (codes 0x21..0x79, `mov pc, r0` at 0x0801452E): `@s` adds 0x10 or 6 by
`g_state_020020D0.mode`, `@c`/`@n` end the line, `@%` expands a name into the local `name[0x2C]` with
`func_08018CEC` and `@r` a label into `label[0x2C]` with `func_0801624C`, and each is measured recursively
(`bl func_080144F4` at 0x080146C6 and 0x080146E0, with `align` 0), `@S` lets `func_0801446C(text, &width)` advance
the text and update the width through a pointer to the local `width`, and the other codes skip their operands or
adjust the width. With `align` set the result is `func_08013BC0(widest, 8)`. The matched `src/08018624.c` calls
it. `g_state_020020D0` is already in `config/data_symbols.json`; the index
row `080144F4 08014778 644 131 return` is right (131 instructions, then the table and pool).

## Byte identity

`080144F4.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080144F4, with callees and data bound to their ROM
addresses, the 89 table words to their case labels and the two self calls resolved against the object's own symbol
(7 `R_ARM_THM_CALL`, 91 `R_ARM_ABS32`). The 644-byte symbol equals the ROM span `[0x080144F4, 0x08014778)`, jump
table included: SHA-256 `04286a826f8a01c5e9faaed1e7fbe6010084d9e67ce1466936fa8cfa14e80af6` for both. `.text` is
exactly 644 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080144F4.c`: the default run and all
213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, both `--*-quotient-profile` values, `--switch-data-profile u16-scalars-v1`, `u16-scalars-v2`, `u16-scalars-frame-v1`, `typed-outgoing-six-words-v1` | `self calls are admitted only on the plain direct-call path` |
| `numeric-data-switch-source-v1`, `restoring-owner-scalar-switch-v1`, `bounded-buffer-guarded-switch-v1`, `bounded-buffer-root-guarded-switch-v1`, `named-data-buffer-v1` and 108 other owner selectors (113) | `owner requires unique undefined zero-valued global symbols` |
| 29 `--addressed-signed-runtime-profile` values | `addressed ABS32 requires an aligned unique undefined global with its exact type` |
| the other 13 `--addressed-signed-runtime-profile` values | `addressed signed runtimes exclude data and irregular relocations` |
| all six `--function-address-profile` values | `function-thunk symbols require unique undefined global types` |
| `--switch-data-profile switch-thunks-v1`, `switch-thunks-frame-v1` | `switch thunks require canonical _call_via aliases without function words` |
| `--control-flow-profile mixed-return-inert-spin-v1` | `inert-spin data requires one undefined mapped global object` |
| `entry-recursive-ordinary-call-v1` | `refused: entry saved-only owner excludes local frames and stack-address materialization` |

The other 42 selector values stop on requirements this function does not meet (float helpers, an alignment pad,
the division runtimes, the -O0 toolchain).

## Cause

Since #147 the default path admits a `bl` to the function's own entry only on the plain direct-call path: `main()`
refuses a self call together with switch relocations, and this function has an 89-word jump table. The switch-data
selectors refuse the self call the same way. The owner selectors, including the switch and buffer owners, bind every
call relocation to an undefined global, and the self call names the function's own defined symbol.

Beyond the self-call binding it needs more than one composition: the jump table together with local buffers passed
to ordinary callees (`name` and `label` to `func_08018CEC` and `func_0801624C`, `&width` to `func_0801446C`, at
`sp`, `sp + 0x2C` and `sp + 0x58`), which is kit #74's switch-and-buffer case, and a buffer rule at the self-call
sites, because each self call receives one of the local buffers (`mov r0, sp` at 0x080146C2; `add r4, sp, #0x2c`
at 0x080146D2). In the nested call that buffer is the callee's incoming `string`, not its own local, so the nested
self call receives the callee's own `name` or `label`, never the tracked buffer.

## Source notes

- `func_08013A5C` is declared `u16 (u16)`; the matched `src/08013A5C.c` is `u8 func_08013A5C(u16 index)`. The ROM
  adds its result to the halfword width without re-narrowing it, so the bytes do not settle the return type.
- `text` is a copy of `string`, the parameter itself is not advanced.
- `@S` is written `text -= 2; text += func_0801446C(text, &width);`: the callee gets the address of the `@`.
- The cases that only consume the code (0x61, 0x62, 0x6B, 0x70, 0x75, 0x77, 0x78, 0x79) are listed with an empty
  `break`, like the default.
- `done` is an `int` flag tested after the switch (`if (done == 1) break;`).

## Ruled out

Nothing beyond the source above is recorded: it was byte-identical as written, and no alternative spellings were
compared.

kit issue: (to be filed - self calls are admitted only on the plain direct-call path: recursive functions that also need an owner, BIOS-fill, runtime or switch selector are refused); the switch-and-buffer part is shubshub/fftadecomp-kit#74
