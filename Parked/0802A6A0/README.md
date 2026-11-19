# 0x0802A6A0 - two-digit number picker: bytes identical, refused (signed quotient and remainder runtimes beside a jump table, named data and a fixed frame) (1196 bytes)

Attempt 2026-11-20, kit b141ba59, decomp main 82b7baab5e.
`u8 func_0802A6A0(Picker0802A6A0 *state)` runs the two-digit number picker whose window the sibling `0x0802A5CC`
opens. Up and down step the value by 1, or by 10 while the tens digit is selected, between 1 and the maximum;
left and right toggle the selected digit. Both digits are redrawn every frame, and a bobbing cursor sprite sits
under the selected one. It dispatches on its phase through a nine-entry jump table.

## The index

The index row `0802A6A0 0802AB4C 1196 524 return` is right. The start is word aligned, the epilogue
(`add sp, #0x24; pop {r3-r5}` back to r8-r10; `pop {r4-r7}; pop {r1}; bx r1`) fits the prologue, and the last pool
word is at 0x0802AB48. The kit's `analyze.refine_function` closes the CFG with 524 reachable instructions.

## Byte identity

`0802A6A0.c` (SHA-256 `304a5da560fd9e7f7a7bed1411c30c95a810e4297b1892bc38642beff1d52ded`) was compiled with the
fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`)
and linked by hand at 0x0802A6A0, with every callee, runtime and data symbol bound to its ROM address
(30 `R_ARM_THM_CALL`, 17 `R_ARM_ABS32`; `__divsi3` -> 0x081426B8, `__modsi3` -> 0x08142950). The 1196-byte symbol
equals the ROM span `[0x0802A6A0, 0x0802AB4C)`: SHA-256 `736021dd3b6a67f4a0a49ed0ef8a12765f13381aec04e44051822f44de29202b`
for both. `.text` is exactly 1196 bytes. The nine jump-table words, the three data words and every `bl` resolve to
the ROM values; the 0xFFFFB000 and 0x00000FFF literals are compiler constants. `match.py` refuses before its own
byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

One is needed: `"data_083916B8": "0x083916B8"`.

- **Three pool words.** The words at 0x0802A998, 0x0802AAA4 and 0x0802AADC hold 0x083916B8.
- **Three loads.** Each is loaded into r0 at 0x0802A95A, 0x0802AA60 and 0x0802AAA8.
- **Used as a source.** Each load is the `source` argument of the sprite drawer `func_08001CF0`, at 0x0802A98E,
  0x0802AA8E and 0x0802AAD4.
- **Neighbours.** The same ROM region already has the named sprite sources `data_083916AA` and `data_083916C0`;
  the latter bounds this object at 8 bytes.
- **Sibling pattern.** `src/0802995C.c` passes `data_0839169C` and `data_083916AA` to `func_08001F34` the same way.

Without it, the default run refuses first with `data target must be an undefined mapped object`.

## Refusals

Kit b141ba59, `match.py --root . --no-write` with this source copied to `src/0802A6A0.c` and the data symbol added.
The default run prints the refusal after `compile failed:`, a selector run as `error (ValueError): <text>`. None
matched.

| Selector | Refusal | Where |
|---|---|---|
| default | `signed quotient excludes other runtime, literal, switch and thunk profiles` | `tools/match.py:1100`: with `__divsi3` bound, the condition refuses `modsi3_bindings and signed_runtime_profile is None` (the mixed `__modsi3`) and any `data_relocations` (the three named data words) |
| `--signed-quotient-profile positive-constant-frame-v1` | `signed quotient excludes other runtime, literal, switch and thunk profiles` | the same check |
| `--addressed-signed-runtime-profile compiler-signed-runtime-data-v1` | `addressed ABS32 requires an aligned unique undefined global with its exact type` | the jump table's nine `R_ARM_ABS32` relocations are against the local `.text` section symbol, not undefined globals |
| `--owner-runtime-profile canonical-integer-private-locals-data-source-v1` | `six-word integer source requires canonical integer calls and zero-addend named objects` | `tools/owner_admission_profile.py:1316`: the switch role is non-empty (raised at line 1319) |
| `--owner-runtime-profile canonical-integer-scalar-data-source-v1` | `six-word integer source requires canonical integer calls and zero-addend named objects` | the same check |
| `--signed-runtime-profile numeric-divmod-v1` | `data target must be an undefined mapped object` | under this profile `switch_relocations` is `None`, so the switch branch at `match.py:841` is skipped and the jump table's `.text` relocation falls through to the data-target check at `match.py:884`-`886` |
| `--owner-runtime-profile numeric-data-switch-source-v1` | `function address requires a canonical addressed function` | the only switch-and-data selector; it does not accept the compiler runtime names `__divsi3` and `__modsi3` |

Not run, because the kit README excludes the shape: `addressed-signed-runtime-v1` and `-data-v1` (they require
explicit `func_081426B8` calls and exclude switches, stack aliases and local buffers), `restoring-owner-acyclic-v1`
(it excludes arithmetic runtimes and switches) and `ordinary-multiple-switch-source-v1` (it needs 2-8 tables and
excludes runtimes).

## Cause

All of these sit in one complete function, and no profile composes them:

1. **Two compiler runtimes.** Compiler-emitted `__divsi3` and `__modsi3`, reached from plain `/ 10` and `% 10` on an
   `s8` field, at six call sites: 0x0802A85A, 0x0802A87E, 0x0802A8B0, 0x0802A8D6, 0x0802A9C8 and 0x0802A9EE.
2. **One jump table.** The guard is `cmp r0, #8; bls` at 0x0802A6B2, the dispatch `lsls #2; ldr =table; adds; ldr;
   mov pc` at 0x0802A6B8-0x0802A6C0. The table at 0x0802A6C8 has nine forward entries; case 8 is the shared exit at
   0x0802AB36.
3. **Three typed data words.** 0x03000000 (`data_03000000`, input state, read at +4), 0x030008B0 (`data_030008B0`,
   tile base at +0x10) and 0x083916B8 (`data_083916B8`, sprite source).
4. **A fixed 0x24-byte frame** (`sub sp, #0x24` at 0x0802A6AA) with
   - seven outgoing stack-argument words at sp+0..sp+0x18, for `func_08001CF0`'s 11 arguments;
   - a local `u16 palette[2]` at sp+0x1C, its address materialized with `add r0, sp, #0x1c` (0x0802A846, 0x0802A8A0,
     0x0802A8F8 and others);
   - one spill slot at sp+0x20 holding `&state->digit` (stored at 0x0802A790 and 0x0802A7C4, reloaded at 0x0802A7D0,
     0x0802A816, 0x0802A834 and 0x0802A95E).
5. Saved r8-r10 (`mov`/`push {r5-r7}`) and ordinary direct calls.

The kit pieces that would compose are kit PR #383's `__divsi3`-beside-a-switch admission (it refuses `__modsi3`,
data and frames beside the switch), `numeric-divmod-v1` (it refuses switches) and the canonical-integer data
selectors (they refuse switches).

## Source notes

Every construct below is ROM-shown, and the plain alternative was compiled. The declaration order of the locals
(`palette`, `tiles`, `buffer`) was not varied; the match does not appear to depend on it.

1. **Plain `/` and `%`, with no cast.** The `lsls r2, #24; asrs r2, #24` after every runtime call (0x0802A860,
   0x0802A884, 0x0802A8B6, 0x0802A8DC, 0x0802A9CE, 0x0802A9F4) comes from the front end itself: `state->value` is
   `s8` and the divisor is a constant, so the quotient and remainder are narrowed back to `s8`.
   - An explicit `(s8)(...)` cast, or an `s8 number` parameter in the callee prototype, compiles identically. The
     plain form is used, with the prototype
     `func_0802979C(void *context, void *tiles, u32 number, u32 digits, u32 style)`, which matches the other
     declared callers (0806E848, 0805843C) and the callee, which does not narrow its third argument.
   - The ROM loads `state->text` into r4 before each division, so the division is evaluated inside the call's
     arguments, not as a statement before the call.
   - Calling `func_081426B8` directly would not produce the `s8` narrowing.
2. **`u8 old = state->value;`.** The ROM reads it with `ldrb r4` at 0x0802A770, while every read of the field itself
   is `ldrsb`; the comparison at 0x0802A7FA is `cmp r4, r0` against an `ldrsb` value. `s8 old` emits a
   sign-extending load and the function grows by 4 bytes. A `u8` local is the codebase's habitual narrow local; see
   the open question.
3. **`if (state->max < state->value) state->value = state->max;`.** The ROM loads `max` first
   (0x0802A7A8-0x0802A7AE) and compares `cmp r1(max), r0(value); bge` at 0x0802A7B4. `state->value > state->max`
   loads `value` first and emits `ble`. The `ldrb r2` of `max` is kept for the store at 0x0802A7B8.
4. **Cursor column `(state->window.x + 3 + (~state->digit & 1)) * 8`.** The ROM (0x0802A962-0x0802A96C, and again
   at 0x0802AA6A and 0x0802AAB2) computes `~digit & 1` (`mvns r2, r2; ands r2, r6(=1)`), adds 3 (`adds r2, #3`),
   adds `x` last (`adds r1, r1(x), r2`) and multiplies by 8 (`lsls #3`): column 3 (tens) when bit 0 of `digit` is
   set, column 4 (ones) when it is clear. Alternatives compiled:
   - `(x + (~digit & 1) + 3) * 8` associates the other way (`x + t` first, then `+ 3`): no match.
   - `(x + 4 - (digit & 1)) * 8` emits `ands; subs #4; subs`: no match.
   - `(x + (digit & 1 ? 3 : 4)) * 8` emits a branch, splitting the block and re-reading `state->timer`: 4 bytes
     shorter.
   - `!(digit & 1)` in the full function changes the register allocation of case 1; in isolation it emits `bic`
     instead of `mvns; ands`.
   - `x + 3 + (~digit & 1)` matches: the front end re-associates it to `x + ((~digit & 1) + 3)`, the ROM order.

   `~flag & 1` for "bit clear" is an ordinary period idiom, written identically at the three sites the ROM repeats.
5. **Palette store order.** Both palette entries hold 11 in every arm. Case 1 with the tens digit selected
   (`digit & 1`) stores `palette[0]` then `palette[1]` (`strh [r0]; strh [r0, #2]` at 0x0802A84C); with the ones digit
   selected it stores `palette[1]` then `palette[0]` (`strh [r0, #2]; strh [r0]` at 0x0802A8A4); case 2 stores [0]
   then [1] (0x0802A9B6). agbcc has no scheduler, so the store order is source order, and the source writes each
   arm's own digit first. A plausible original is that the palette once distinguished the selected digit and the
   style argument (0 against 5) later took that role, leaving both entries at 11. That is speculative; the order
   itself is ROM-shown.
6. **Style arguments 0 and 5, and the zero in `sl`.** In the ones-selected arm the last call's style 0 is passed as
   `mov r0, sl; str r0, [sp]` (0x0802A8E0), where `sl` holds `digit & 1`, known 0 on that path. This is not a source
   construct: the plain literal `0` produces it, the compiler reusing the known-zero register. The same holds for
   `r6 = 0` at 0x0802A848 in the other arm.
7. **`palette` is a local array.** The ROM keeps it on the stack at sp+0x1C and reloads each element for every use
   (`add r0, sp, #0x1c; ldrh`). Two scalar locals would live in registers.
8. **The palette and buffer block is written out twice** (case 1 at 0x0802A8EE, case 2 at 0x0802AA04). The ROM
   repeats it instruction for instruction, with `ldr r5, [r7, #0x38]` placed differently around it: case 1 reloads
   `state->panel.buffer` into r5 after the digit draws, case 2 loads it once before them (0x0802A9AC). The source
   assigns `buffer` after the draws in case 1 and before them in case 2. Case 2's `func_0802AC14` call re-reads
   `state->panel.buffer` (0x0802AA50 `ldr r1, [r7, #0x38]`), so that call uses the field, not the local. No statement
   macro is used: the two copies differ in what precedes them, and duplication is the plain reading.
9. **`case 8: break;`.** The guard is `cmp r0, #8` (0x0802A6B2) and the table has nine entries, the last pointing
   at the exit 0x0802AB36. Without `case 8` the bound would be 7.
10. **Case order 0, 1, 2, 3, 4, 6, 5, 7.** The bodies are laid out at 0x0802A6EC, 0x0802A76C, 0x0802A99C,
    0x0802AAA8, 0x0802AAE0, 0x0802AAF0, 0x0802AB12 and 0x0802AB22. With no scheduler, layout follows source order.
11. **Case 6 stores `phase = 8` before `func_0802A370(0, 0, 0, 0)`.** The store at 0x0802AB02 precedes the call at
    0x0802AB0C.
12. **Case 0 stores `panel.palette = 12` before the two `0xB000` buffer stores** (0x0802A704, 0x0802A716,
    0x0802A728). The first constant is built as `movs #0xB0; lsls #8`; the second is the pool word 0xFFFFB000,
    because the compiler handles `(base_tile + 1) | 0xB000` in 16 bits. Both are plain `| 0xB000`.
13. **`state->value += 10`, `+= 1`, `-= 10`, `-= 1`** are written symmetrically; `++` and `--` give the same code.
14. **Struct layout.** The state begins with a 0x2C-byte window, passed to `func_08017180`, `func_08017508` and
    `func_0802AC14`; its x, y, width and height are at 0x10-0x13, the fields `func_0802AC14`'s matched source reads
    at +0x12. The second 0x2C-byte block at +0x2C is the tile panel passed to `func_0802AB64`; its matched source
    declares `base` at +0x0C and `tag` at +0x1F, which are 0x38 and 0x4B here. The fields at 0x74-0x80 are the text
    context, timer, value, max, digit, base tile and phase; the sibling `src/0802A5CC.c` initialises them as
    `value_74`, `active` (value = 1), `mode` (max), `field_7C`, `value_7E` and `field_80`. Unknown spans are
    `unknown_*`.

## Open question: a possible `s8` wrap on +10

The value field at +0x79 is `s8`, and up adds 10 while the tens digit is selected. The clamp at 0x0802A7B4 compares
`s8` with `s8`. If `max` were 118 or more, `value + 10` could exceed 127 and wrap negative (120 + 10 stores -126);
`max < value` would then be false and the negative value would survive the clamp. The next frame's `old` (`ldrb`,
130) would never equal `value` (`ldrsb`, -126), so the sound at 0x0802A800 would play every frame, and the digits
would be drawn from -12 and -6.

No bug is claimed, because the wrap needs `max >= 118`. `max` is the fifth argument (`[sp]`) of the opener
`func_0802A5CC`, which stores it at +0x7A. Its three ROM callers:

| Call site | Value passed as max | Bounded? |
|---|---|---|
| 0x0806A4A8 | `min(99 - byte, r3)` (`movs r0, #0x63; subs r4, r0, r1; cmp r4, r3; bls` at 0x0806A480-0x0806A488), narrowed to `u8` | capped at 99 |
| 0x0806C536 | `(u8)(byte_a - byte_b)` (0x0806C512-0x0806C51A), a difference of two table bytes | not established |
| 0x0805B604 | a byte loaded from a table (0x0805B5F6 `ldrb r4, [r5]`) | not established |

Only the first caller is shown to cap `max` at 99. If either of the others can pass 118 or more, the wrap is
reachable, and the match needs a bug case (`docs/bugs/0802A6A0/` with an executable repro) before it ships with a
`/* BUG */` comment. These look like item-quantity pickers, where 99 is the usual ceiling, but that is not proved
for the second and third callers.

kit issue: shubshub/fftadecomp-kit#74 (a switch combined with named data; here also two compiler runtimes and a frame)
