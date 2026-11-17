# 0x080A5580 - entry walk with three switches: bytes identical, refused (several jump tables in a function with a loop and local output bytes) (1042 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. `func_080A5580(state)` walks a list of entries and then
calls `func_08141520` with a constant chosen by two more switches. Frame: `push {r4-r7, lr}`, `push {r8-r10}`,
`sub sp, #12`.

- **The loop** runs `r8` from 0 while `r8 < (u8)state[0x2C0]`, over records of 0x2C bytes; header at 0x080A5602,
  test at 0x080A585A, back edge `b 0x080A5602` at 0x080A5866. Each iteration branches on the halfword at
  `state + 0x2E + 0x2C * r8` with compares, not a table.
- **Switch 1**, inside the loop: `subs r0, #1; cmp r0, #17; bhi` at 0x080A573E, dispatch `mov pc, r0` at 0x080A574C,
  pointer word at 0x080A5750, 18 entries at 0x080A5754. The selector is `func_0812EE98(...)` narrowed to `u8`.
- **Switch 2**, after the loop: `subs r0, #1; cmp r0, #18; bhi` at 0x080A58A0, dispatch at 0x080A58AE, pointer word
  at 0x080A58B0, 19 entries at 0x080A58B4. The selector is `func_080CA7A4(item, 3)`.
- **Switch 3**, reached only through entry 15 of switch 2 (target 0x080A5920): `subs r0, #0xCB; cmp r0, #8; bhi` at
  0x080A5922, dispatch at 0x080A5930, pointer word at 0x080A5934, 9 entries at 0x080A5938.
- **The local bytes.** In the loop body, `add r2, sp, #4` and `mov r6, sp; adds r6, #5` pass the addresses of two
  `s8` locals to `func_080A1D84` (`bl` at 0x080A56AA); the caller reads them back at 0x080A56AE and 0x080A56C8, and
  R6 keeps the address across the call to `func_0809A570` at 0x080A56C2.

All table entries are forward and in-function; no named data, function literals, runtimes or thunks; 31 ordinary
calls. No new data symbol is needed.

## The index

The selectors compare the index's instruction counts with the CFG, so three rows are corrected with this entry
(walked independently and with the kit's `analyze.refine_function` at 18dcc516, which agree):

| Function | `symbols/functions.txt` on main | `config/functions.json` on main | reachable |
|---|---|---|---|
| `080A5580` | 521 | 521 | 390 |
| `0809836C` (callee) | 800 | 627 | 627 |
| `0809A570` (callee) | 29 | 27 | 27 |

With the rows as they are on main, `ordinary-multiple-switch-source-v1` stops earlier, with
`multiple-switch dual-index instruction count differs from complete CFG`. Correcting only the `080A5580` row is not
enough: the callee rows are checked too.

## Byte identity

`080A5580.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080A5580, with every callee bound to its ROM address
and the 46 table words and three pointer words to their local targets (31 `R_ARM_THM_CALL`, 49 `R_ARM_ABS32`). The
1,042-byte symbol equals the ROM span `[0x080A5580, 0x080A5992)`: SHA-256
`c7f45a84f7f65c51b3910a89d594df1f51c8ae58fe2b45a6fa3429cb3fd2689b` for both. `.text` is 1,044 bytes: the symbol and
the assembler's `c0 46` alignment halfword. `match.py` refuses before its own byte comparison (below).
`plausible.py --strict` exits 0.

This revision drops the two `(s8)` casts on the arguments of `func_080A1D84` that the earlier copy in this
directory had; both give the same bytes and the same SHA-256.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080A5580.c` and the three index rows
corrected: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, both `--*-quotient-profile` values, every `--function-address-profile` value, every `--switch-data-profile` value except `switch-thunks-v1` and `switch-thunks-frame-v1` (17) | `switch words must describe an adjacent table and forward local cases` |
| `--owner-runtime-profile ordinary-multiple-switch-source-v1` | `multiple-switch prerequisite excludes local CFG cycles` |
| `restoring-owner-switch-cycles-function-words-v1`, `restoring-owner-switch-aligned-v1` | `scalar switch requires one exact zero-interposed-word switch and ordinary calls` |
| `bounded-buffer-root-guarded-switch-v1` | `root buffer requires one exact guarded switch and ordinary calls` |
| `restoring-owner-scalar-switch-v1`, `restoring-owner-runtime-v1` and 30 other restoring-owner, canonical-integer, static-callback and descriptor selectors (32) | `owner requires sole complete Thumb ELF function` |
| `named-data-buffer-v1` and 65 other buffer, scheduler and static-callback selectors (66) | `named-data buffer caller excludes local BL and word switches` |
| `--switch-data-profile switch-thunks-v1`, `switch-thunks-frame-v1` | `switch thunks require a complete local switch, objects and no other runtime` |
| the three `--switch-profile` values | `switch constants require adjacent forward pointer/table words` |

The other 90 selector values stop on requirements this function does not meet (float helpers, runtimes, the
addressed-runtime binding rules, the -O0 toolchain).

## Cause

Each switch selector has one of the three features this function combines, but not the others:

| Selector | Several tables | Loops | Local output addresses |
|---|---|---|---|
| default (`elf-symbol-thumb-switches-v1`) | no, one table | yes | no: a switch excludes a fixed frame here |
| `ordinary-multiple-switch-source-v1` | yes, 2 to 8 | no | no |
| `restoring-owner-switch-cycles-function-words-v1` | no, one table | yes (and it requires typed function words) | no |
| `bounded-buffer-root-guarded-switch-v1` | no, one table | not checked | yes |

The multiple-switch prerequisite takes the tables apart and checks each guard, then requires a topological order of
the whole CFG, which the back edge at 0x080A5866 breaks; its next rule refuses SP as a register operand outside
push, pop and SP adjustments, so `add r2, sp, #4` and `mov r6, sp` would be refused next. The kit README states both
as limits of that selector ("local pointer materialization, local cycles ... are rejected"). The restoring owners
refuse the two-byte alignment tail. Only the root-guarded buffer selector proves local outputs passed to a walked
callee, and it binds exactly one switch.

## Source notes

- `s32 direction` locals: `func_0809D6BC` is called at 0x080A563E and 0x080A570A before the object loads.
- `u16 item = state->item`: the `ldrh r4` at 0x080A588C is reused at 0x080A5920.
- Two case groups that both set `moved = 1` are kept separate, as the ROM has separate blocks (0x080A579C,
  0x080A57A2); merged, the function is 968 bytes.
- The declaration order `played`, `hit`, `moved` follows the ROM's stores at 0x080A558E.
- `s8` locals `left`/`right` (0x080A56B0, 0x080A56C8); `func_080A1D84` takes `s8` arguments, as in the matched
  `src/080A8390.c`.
- Layout and prototypes follow the siblings `080A52D4`, `080A54E0`, `080A5A7C`, `080A1A14` and the callees
  `0812EE98`, `0809A570`, `0809D854`, `080A8390`.

## Ruled out

- Merging the two `moved = 1` case groups: 968 bytes (from the earlier attempt).
- The `(s8)` argument casts of the earlier copy: not needed (same bytes).

kit issue: (to be filed - match.py: no selector admits several jump-table switches in a function with a loop and local output bytes); related: shubshub/fftadecomp-kit#74
