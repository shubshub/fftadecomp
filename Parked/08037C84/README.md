# 0x08037C84 - transfer slot setup: bytes identical, refused (a store into the function's own incoming argument word) (364 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. `func_08037C84(slot, resource, renderer, column, row,
mode, kind, enabled)` fills transfer slot `slot` of `g_state_03002810` (slots at +0x954, 0xCC bytes each): two plane
copies sized from renderer `data_030009E0[renderer]` with destination `data_06008000` and sources at
`plane + width * row + column`, the renderer index, two cleared halfwords, `mode` and `resource`, then
`resource->kind = kind` and the one-bit `resource->enabled = enabled`. It is a sibling of the matched
`src/0808136C.c`. The index row on main, `08037C84 08037DF0 364 159 call`, is the corrected one (159 instructions,
then alignment and eleven pool words). The three pool symbols, `g_state_03002810`, `data_030009E0` and
`data_06008000`, are already in `config/data_symbols.json`.

## Byte identity

`08037C84.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08037C84, with the three pool words bound to their
mapped addresses (3 `R_ARM_ABS32`; the function makes no calls). The 364-byte symbol equals the ROM span
`[0x08037C84, 0x08037DF0)`: SHA-256 `3d7ebe32defca4f56d0e535fdc40a15937072f37c2fd1299057bc1b567793622` for both.
`.text` is exactly 364 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict`
exits 0. This revision differs from the earlier copy only in the header comment, which now gives the target bytes.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08037C84.c`: the default run and all
213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, both `--*-quotient-profile` values | `stack-frame write is outside the tracked frame` |
| `named-data-buffer-v1`, `restoring-owner-acyclic-v1`, `bounded-buffer-runtime-summaries-v1` and 36 other owner selectors, `--control-flow-profile mixed-return-inert-spin-v1` (40) | `stack alias arithmetic leaves the tracked frame` |
| 29 addressed-runtime selectors that admit data | `addressed runtime ELF requires actual addressed calls and no unresolved symbols` (they need runtime calls, and this function makes none) |
| the other 13 addressed-runtime selectors | `addressed signed runtimes exclude data and irregular relocations` |

The other 129 selector values stop on their own shape requirements (a runtime, a switch, a BIOS wrapper, a
scheduler call, an alignment pad, the float profiles, the -O0 toolchain).

## Cause

The frame is 0x38 bytes (five low registers, three high registers, `sub sp, #0x18`), so `[sp, #0x40]` and
`[sp, #0x44]` are the incoming words of `kind` and `enabled`. Since #205 the default path admits the narrow read
`add r0, sp, #0x40; ldrb r0, [r0]` of `kind` at 0x08037D8E-0x08037D90; that pair was the previous refusal here. The
default path now stops at the next instruction #205 names under "What stays refused", the store of the masked
`enabled` back into its own incoming slot:

```
08037D9C  movs r0, #1
08037D9E  ldr  r1, [sp, #0x44]     @ enabled (incoming word)
08037DA0  ands r1, r0
08037DA2  str  r1, [sp, #0x44]     @ enabled & 1 written back to its own slot
08037DA4  ldrb r1, [r2, #9]
08037DA6  movs r0, #2
08037DA8  negs r0, r0
08037DAA  ands r0, r1
08037DAC  ldr  r3, [sp, #0x44]     @ read back once, as a scalar
08037DAE  orrs r0, r3
08037DB0  strb r0, [r2, #9]        @ resource->enabled (1-bit field)
08037DB2  add  sp, #0x18           @ epilogue; the word is not read again
```

The source line is `...->resource->enabled = enabled;` with `enabled` a `u32` parameter and the member
`u8 enabled : 1`: agbcc keeps the parameter in its incoming slot, writes the masked value back there and reloads it.
No call, branch or other access to the word comes between the store and the reload, and no local address is ever
stored there. The owner selectors refuse earlier, at the narrow read, because #205 enabled the pair on the plain
path only.

## Source notes

- `kind` and `enabled` are `u32` parameters: with a `u8` `kind` or `enabled` the prologue changes.
- Every store spells `g_state_03002810->slots[slot]` again; the ROM reloads the state pointer for each one (for
  example `ldr r0, [r7]` at 0x08037D94).

## Ruled out

Carried from the earlier attempt: `u8` types for `kind` or `enabled` (prologue differs). No other spelling was
needed.

kit issue: shubshub/fftadecomp-kit#75 (the store into an incoming argument word that #205 left out)
