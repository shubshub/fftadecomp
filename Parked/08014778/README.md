# 0x08014778 - pixel width of an encoded text: bytes identical, refused (a self call with a jump table and a local buffer) (582 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. `u16 func_08014778(const u8 *text)` measures the width of
an encoded string. Byte 1 switches to raw mode, in which each byte adds `func_08013A5C(byte - 1)`; otherwise
two-byte glyph codes add `func_08013A5C(code & 0x7FFF)`, and an `@` code dispatches through an 89-entry jump table
(codes 0x21..0x79, `mov pc, r0` at 0x080147D8, table at 0x080147E0): `@s` adds 0x10 or 6 by `g_state_020020D0.mode`,
`@%` expands a field into the local `buffer[0x2C]` with `func_08018CEC` and measures it recursively
(`bl func_08014778` at 0x08014970), `@c`/`@n` return, and the other codes skip their operands or adjust the width.
Seven matched sources call it (among them `src/0801446C.c`, `src/08018624.c`, `src/080199EC.c`).
`g_state_020020D0` is already in `config/data_symbols.json`. The index row `08014778 080149BE 582 101 return` is
right (101 reachable instructions once the table is resolved).

## Byte identity

`08014778.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08014778, with callees and data bound to their ROM
addresses, the 89 table words to their case labels and the self call resolved against the object's own symbol (4
`R_ARM_THM_CALL`, 91 `R_ARM_ABS32`). The 582-byte symbol equals the ROM span `[0x08014778, 0x080149BE)`, jump table
and pool included: SHA-256 `131d000096d5cfdc53134bae6f6acc03e461f9b16eec73c16a2e78298b8298d2` for both. `.text` is
584 bytes: the symbol and the assembler's `c0 46` alignment halfword. `match.py` refuses before its own byte
comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08014778.c`: the default run and all
213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, both `--*-quotient-profile` values, `--switch-data-profile u16-scalars-v1`, `typed-outgoing-six-words-v1` | `self calls are admitted only on the plain direct-call path` |
| `numeric-data-switch-source-v1`, `bounded-buffer-guarded-switch-v1`, `bounded-buffer-root-guarded-switch-v1`, `named-data-buffer-v1` and 89 other owner selectors (93) | `owner requires unique undefined zero-valued global symbols` |
| `restoring-owner-scalar-switch-v1`, `restoring-owner-acyclic-v1`, `static-callback-buffer-v1`, `canonical-integer-scalar-data-source-v1` and 28 other owner selectors (32) | `owner requires sole complete Thumb ELF function` |
| `--switch-data-profile u16-scalars-v2`, `u16-scalars-frame-v1`, `u16-scalars-functions-v2`, `u16-scalars-functions-frame-v2` | `switch words must describe an adjacent table and forward local cases` |
| 29 `--addressed-signed-runtime-profile` values | `addressed ABS32 requires an aligned unique undefined global with its exact type` |
| the other 13 `--addressed-signed-runtime-profile` values | `addressed signed runtimes exclude data and irregular relocations` |
| all six `--function-address-profile` values | `function-thunk symbols require unique undefined global types` |
| `--switch-data-profile switch-thunks-v1`, `switch-thunks-frame-v1` | `switch thunks require canonical _call_via aliases without function words` |
| `--control-flow-profile mixed-return-inert-spin-v1` | `inert-spin data requires one undefined mapped global object` |
| `entry-recursive-ordinary-call-v1` | `refused: entry saved-only owner excludes local frames and stack-address materialization` |

The other 28 selector values stop on requirements this function does not meet (float helpers, the division
runtimes, the -O0 toolchain). The `owner requires sole complete Thumb ELF function` group refuses the alignment
halfword after the 582-byte symbol.

## Cause

As for `0x080144F4`: the default path admits a self call only on the plain direct-call path, and this function has a
jump table; the owner selectors bind every call relocation to an undefined global, which the self call is not. It
also needs the jump table together with a local buffer passed to ordinary callees (kit #74's switch-and-buffer
case), and a buffer rule at the self-call site: the self call receives the local `buffer` (`mov r0, sp` at
0x0801496E after `func_08018CEC(buffer, code)` at 0x0801496A). The nested call's own `buffer` is a new local, so
the tracked buffer is not passed on.

## Source notes

- `func_08013A5C` is declared `s32 (s32)`; the matched `src/08013A5C.c` is `u8 func_08013A5C(u16 index)`, and
  `0x080144F4` declares it `u16 (u16)`. The ROM narrows the argument itself here (`(u16)(text[0] << 8 | text[1])` is
  masked with 0x7FFF at 0x080147A4-0x080147A8) and adds the result to the sign-extended width; the bytes do not show
  the callee's real return type, and the three declarations disagree.
- A byte below 0x80 other than 1 and 0x40, outside raw mode, does not advance `text` (`continue`): the ROM branches
  from 0x080147C4 straight back to the loop test at 0x080149AA without an increment, so such a byte loops forever.
  The source reproduces that rather than guessing an intent.
- `width` is `s16` (sign extension before each add, 0x080147AE-0x080147B0); `raw` is an `s32` flag.

## Ruled out

Nothing beyond the source above is recorded: it was byte-identical as written, and no alternative spellings were
compared.

kit issue: (to be filed - self calls are admitted only on the plain direct-call path: recursive functions that also need an owner, BIOS-fill, runtime or switch selector are refused); the switch-and-buffer part is shubshub/fftadecomp-kit#74
