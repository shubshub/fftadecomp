# 0x0804C044 - animated record and menu cursor task: bytes identical, refused (signed and unsigned remainder runtimes beside a jump table and a local buffer) (1168 bytes)

Attempt 2026-11-20, kit b141ba59, decomp main 82b7baab5e.
`void func_0804C044(void *task, u8 *state)` is the per-frame task callback that `func_08035174` installs
(`func_08006AF8(&data_03002720, 3, func_0804C044, 1)`). It has three parts:

1. A loop over the `u16 count` 28-byte records at `data_03000E30.entries` (the records written by `func_0804C524`,
   `func_0804C5F8`, `func_0804C668`, `func_0804C6A0`, `func_0804C6E4` and `func_0804C740`). Each active record (+0x0D)
   is drawn by a 7-way switch on +0x0C through `func_08001CF0` or `func_08001F34`, and animated records step their
   frame and timer. Case 2 builds a one-sprite OAM descriptor `{1, 0, 0, tile}` in a local `u16[4]` at sp+0x1C and
   passes its address.
2. On `*state == 0`: two `func_0804C788` placements, a +2/-2 slide of the s8 at `g_state_03002810->gauge->+0x19`
   between 0 and 24 depending on bit 0x40, and two fixed sprites at y `data_030009E0[3].y * 8 + 1`.
3. The menu cursor: if `flags(+0xF21) & 1` and not `& 0x10`, draw `data_083919C6` (bobbing by
   `data_08393CA2[state]`, flipped by bit 8) or, with bit 0x80, `data_083919CE` (bobbing by `data_08393D02[state]`);
   with bit 2 the phase advances modulo 48 or 40, otherwise it resets.

## The index

The index row `0804C044 0804C4D4 1168 488 return` is right. The start is word aligned, the prologue
(`push {r4-r7, lr}; mov r7, sb; mov r6, r8; push {r6, r7}; sub sp, #0x24`) and the epilogue
(`add sp, #0x24; pop {r3, r4}; mov r8, r3; mov sb, r4; pop {r4-r7}; pop {r0}; bx r0`) balance, and the final pool
word is at 0x0804C4D0. The kit's `analyze.refine_function` closes the CFG with 488 reachable instructions.

## Byte identity

`0804C044.c` (SHA-256 `b52819095388e02431f313a592dbeb47b189a8b7a5fda93eb006cb5fc8694ae0`) was compiled with the
fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`)
and linked by hand at 0x0804C044, with every callee, runtime and data symbol bound to its ROM address
(15 `R_ARM_THM_CALL`, 21 `R_ARM_ABS32`). The 1168-byte symbol equals the ROM span `[0x0804C044, 0x0804C4D4)`:
SHA-256 `4d9d52a6f5c81182105d92356ba90055dc0454574b9e3ad171660a4eab44747a` for both. `.text` is exactly 1168 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

The object's undefined symbols are exactly 14: the callees `func_08001CF0`, `func_08001F34` and `func_0804C788`, the
runtimes `__modsi3` (0x08142950) and `__umodsi3` (0x08142B28), and nine data objects. The linked call order equals
the ROM's 15 `bl`s: CF0, F34, `__modsi3`, F34, F34, CF0, F34, F34, 0804C788, 0804C788, CF0, CF0, CF0, F34,
`__umodsi3`. `__modsi3` is the compiler's choice for `(e->frame + 1) % e->count` (an int dividend, a loaded-byte
divisor), and `__umodsi3` for `state %= 48` / `state %= 40` on the u8 phase; neither is called explicitly.

Two details make a naive hand link look wrong: the callee symbols must be Thumb-typed (`.thumb_set`), because plain
linker-script assignments make `ld` insert `__func_*_from_thumb` interworking stubs and retarget every `bl`; and the
output section needs the explicit address (`.text 0x0804C044 : { ... }`), because with `. = 0x0804C044;` the
section's 8-byte alignment moves it to 0x0804C048.

## Data symbols

Three of the nine objects are not in `config/data_symbols.json`:

| Name | Evidence |
|---|---|
| `data_083919B0` | Literal at 0x0804C348, loaded at 0x0804C29A as the first argument of `func_08001CF0`. ROM halfwords `0002 4000 8000 405E 0000 4020 4066`: an OAM descriptor, count 2, then 2 x (attr0, attr1, attr2), 14 bytes, ending exactly at the next descriptor `data_083919BE`. |
| `data_083919BE` | Literal at 0x0804C354, loaded at 0x0804C2C2 for the second fixed sprite. ROM `0001 0000 4000 406E`: count 1, 8 bytes, ending at the existing `data_083919C6`. |
| `data_08393CA2` | Pool words at 0x0804C364 and 0x0804C3F8, loaded at 0x0804C328 and 0x0804C37C and indexed by the menu phase (`state % 48`). ROM, 48 s8 values: `0` x11, `2, 4, 5, 6, 7`, `8` x16, `7, 7, 7, 6, 6, 6, 5, 5, 5, 5, 5, 4, 3, 2, 2, 1`, the horizontal bob for the cursor. Its sibling table `data_08393D02` (40 phases, vertical bob) is already named and declared `const s8` in `src/080812E8.c`. |

The other six are already mapped: `data_03000E30`, `g_state_03002810`, `data_030009E0`, `data_083919C6`,
`data_083919CE`, `data_08393D02`. `data_083919C6` and `data_083919CE` are declared `const u8 []` in
`src/08038028.c`, which draws the same two cursor descriptors with the same 0x80/0x08 flag logic; the new ones
follow that spelling. Without the three symbols the default run refuses first with
`data target must be an undefined mapped object`.

## Refusals

Kit b141ba59, `match.py --root . --no-write` with this source copied to `src/0804C044.c` and the three data symbols
added. None matched.

| Selector | Refusal |
|---|---|
| default | `unsigned remainder excludes other runtime, switch, function and thunk profiles` (`tools/match.py:1083`: a `__umodsi3` binding refuses beside any `__modsi3` binding, and beside switch relocations unless an umod-r1 or unsigned-thunk profile is selected) |
| `--owner-runtime-profile canonical-integer-scalar-data-source-v1` | `six-word integer source requires canonical integer calls and zero-addend named objects` |
| `--owner-runtime-profile numeric-data-switch-source-v1` | `function address requires a canonical addressed function` |
| `--owner-runtime-profile bounded-buffer-runtime-summaries-v1` | `named-data buffer caller excludes local BL and word switches` |
| `--owner-runtime-profile bounded-buffer-guarded-switch-v1` | `function address requires a canonical addressed function` |

The source was not respelled to dodge any of these. Rewriting `%` as explicit `func_08142950` / `func_08142B28`
calls would be steering: the ROM's runtime choice falls out of plain `%` on these types.

## Cause

All of the following sit in one function:

- a guarded 7-entry local jump table (guard `cmp r0, #6; bls` at 0x0804C066, table word at 0x0804C078, table
  0x0804C07C..0x0804C097) with forward cases only;
- compiler `__modsi3` at 0x0804C11E with a variable divisor (a loaded byte, `ldrb r1, [r5, #0xe]`, not proven
  nonzero) and an int dividend `frame + 1`;
- compiler `__umodsi3` at 0x0804C49A with constant divisors 48 and 40 that join at that one call site
  (`movs r1, #0x30` at 0x0804C3EC and `movs r1, #0x28` at 0x0804C498);
- a fixed frame `sub sp, #0x24` with seven outgoing stack words per call and r8/sb saved;
- a local `u16[4]` at sp+0x1C, stored through `add r1, sp, #0x1c` (0x0804C132) and passed by `add r0, sp, #0x1c`
  (0x0804C15C) to `func_08001F34`;
- nine named data objects (six mapped, three proposed above).

The newest composition, kit PR #383's division-and-switch profile, admits only `__divsi3` with a positive constant
divisor beside one table, with no data and no other runtime. The `__modsi3` s16 profile needs a signed-16 dividend
and a nonzero divisor and excludes frames, switches and unsigned mixing.

## Source notes

Every load-bearing choice below was also compiled in its plain form; the byte counts are of the plain form linked as
above, and "diff lines" counts mismatching instructions after masking branch targets and pool offsets.

1. **`*(u32 *)(e->base + (e->frames[e->frame].cell << 2))`** (case 0/1 at 0x0804C098..0x0804C0AA, case 6 at
   0x0804C1A8..0x0804C1BA). The ROM scales the cell first (`lsls r0, r0, #2` at 0x0804C0A2), then loads the base
   (`ldr r1, [r5, #0x18]` at 0x0804C0A4), then adds base first (`adds r0, r1, r0` at 0x0804C0A6). In each of these
   six spellings the base load comes before the shift, followed by `adds r0, r0, r1` (2 instructions out of order
   per site, both sites): `((u32 *)e->base)[cell]`, `*(u32 *)(e->base + cell * 4)`, `cell * sizeof(u32)`,
   `*(u32 *)(cell * 4 + e->base)`, `u32 *base` with `(u8 *)e->base + e->base[cell]`, and an integer `u32 base`
   field. In `EXPAND_SUM`, agbcc defers a `* 4` (and puts the MULT first) but emits a shift at once. A shifted byte
   offset into an offset table is an ordinary idiom. The only `<< 2` byte-offset sibling, `0804BEE8`
   (`pixels + ((column & 0xF8) << 2)`), is itself a reconstruction, so it is not original evidence.
2. **One function-scope `u8 *gfx` shared by cases 0/1 and 6.** The ROM keeps gfx in r4 in both (`adds r4, r1, r0` at
   0x0804C0AA and 0x0804C1BA, `adds r0, r4, #0` before each call), and in case 6 the zero for the stack words is r3,
   reused as the mode argument. With a local per case the result is 1164 bytes: case 6 computes gfx straight into
   r0, and case 3's `movs r3, #0; bl func_08001F34` cross-jumps into case 6's call, so 0x0804C17E..0x0804C182 go
   missing. One graphics pointer per function is natural.
3. **One `s32 x, y` pair shared by both cursor branches.** The ROM keeps x in r7 and y in r6 in both branches
   (`adds r7, r0, r1` at 0x0804C33A, `subs r7, r2, r0` at 0x0804C38E, `ldrb r6` at 0x0804C3A2; `ldrb r7` at
   0x0804C43E, `ldrb r6` at 0x0804C444), which uses six callee-saved registers and saves sb. Declaring x and y
   inside each branch gives 1152 bytes: only r8 is saved, the push and pop lose sb, and the whole tail is
   reallocated. Declaring them before the branches is how a developer would write "compute x and y, then draw". The
   types are free (`u8 y` and `s32 y` are identical); `s32 x, y` was chosen because x is a signed sum and both are
   passed as `s32`.
4. **`x = pos.x + data_08393CA2[state]`** (flag-8 arm). The ROM forms `&positions[sel].x` first
   (0x0804C31A..0x0804C326), then the table address and its s8 load (0x0804C328..0x0804C336), then `ldrb r1, [r1]`
   (0x0804C338) and `adds r7, r0, r1`. The order `data_08393CA2[state] + pos.x` computes the table address first
   (18 diff lines in 0x0804C31A..0x0804C33A). Either operand order of a commutative add is natural.
5. **`x = pos.x + 8 - data_08393CA2[state]`** (other arm). The ROM loads pos.x (`ldrb r2, [r0]` at 0x0804C37A), then
   the table, `subs r0, #8` (0x0804C38C) and `subs r7, r2, r0` (0x0804C38E): `pos.x - (tbl - 8)` after fold
   re-associates the source. Spelled literally as `pos.x - (tbl[state] - 8)` it folds to `(pos.x + 8) - tbl` with
   `adds r1, #8` (6 diff lines); `pos.x - tbl[state] + 8` gives `subs` then `adds r7, #8` (7 diff lines). Of the
   three spellings only `pos.x + 8 - tbl[state]` matches.
6. **Identical arms: `else if (flags & 8) state = 24; else state = 24;`** (0x0804C3D2..0x0804C428). The ROM keeps the
   flag-8 test. After the `func_08001CF0` call the flags byte is reloaded into r4 (`mov r0, r8; ldr r1, [r0];
   adds r4, r1, r4; ldrb r4, [r4]` at 0x0804C3CA..0x0804C3D0), and the bit-2 test (`movs r0, #2; ands r0, r4;
   cmp r0, #0; beq 0x0804C40C` at 0x0804C3D2..0x0804C3D8) falls to:
   - 0x0804C40C `movs r0, #8`, 0x0804C40E `ands r0, r4`, 0x0804C410 `cmp r0, #0`, 0x0804C412 `beq 0x0804C420`: the
     flag-8 test, whose outcome nothing depends on;
   - the then-arm: 0x0804C414 `ldr r2, =0xF1D` (pool word 0x0804C41C), 0x0804C416 `adds r1, r1, r2`, 0x0804C418
     `b 0x0804C424`, padding at 0x0804C41A;
   - the else-arm: 0x0804C420 `ldr r3, =0xF1D` (pool word 0x0804C42C), 0x0804C422 `adds r1, r1, r3`;
   - the shared tail (cross-jumped): 0x0804C424 `movs r0, #0x18`, 0x0804C426 `strb r0, [r1]`, 0x0804C428
     `b 0x0804C4C2`.

   Both arms store 24 to +0xF1D. The plain form `else state = 24;` gives 1148 bytes: the test, the second arm, its
   branch and its pool word all disappear. Byte differences start at 0x0804C2F8 (shorter long-branch offsets), and
   register choice differs from 0x0804C3CC on (the flags byte lands in r1 instead of r4). No compiler pass could
   have introduced this test: the ROM physically contains it. The source carries an address comment at the
   construct. It is still the open kit #201 shape (identical single-statement arms). `plausible.py` does not flag
   it, because the arms sit in an `else if` chain with braces; the braces were not added for the gate. A likely
   original is two separately named restart phases that both happen to be 24. In `data_08393CA2`, phase 24 is the
   maximum offset 8, so the flipped cursor rests at pos.x + 8 and the unflipped one at pos.x. Nothing shows a
   misbehaviour, so no bug is claimed.
7. **Case order 0, 1, 2, 3, 4, 6, 5.** The case bodies are laid out in that order (0/1 at 0x0804C098, 2 at
   0x0804C132, 3 at 0x0804C164, 4 at 0x0804C186, 6 at 0x0804C1A8, 5 at 0x0804C1DC; table at 0x0804C07C). agbcc emits
   case bodies in source order, so this is evidence of the original order; case 6 sits next to case 0/1, which it
   resembles.
8. **`(g->flags & 1) && !(g->flags & 0x10)`.** The u8 narrowing after the 0x10 mask (`ands; lsls r0, #24;
   lsrs r3, r0, #24; cmp r3, #0` at 0x0804C2FA..0x0804C302) comes out of this plain condition by itself, as does the
   0x02 mask in the 0x80 branch (0x0804C47A..0x0804C482), whose zero is then stored by `strb r1, [r0]` at
   0x0804C4C0. Using r3 as the known zero for the stack words at 0x0804C448..0x0804C466 also falls out. No
   temporaries were written.
9. **`!(g_state_03002810->flags & 8)` as the seventh argument** (`lsrs r2, r2, #3; movs r1, #1; bics r1, r2` at
   0x0804C3B2..0x0804C3B6) is agbcc's store-flag expansion of a single-bit equality test, from the plain spelling.
10. **Free choices** (byte-identical either way; the natural one was kept): `e->frame++` against
    `e->frame = e->frame + 1`; `if (!e->active) continue;` against wrapping the switch in `if (e->active)`; `u8 y`
    against `s32 y`. Declaration order is not load-bearing: swapping `e` and `gfx` is identical.
11. **The local OAM descriptor in case 2** is filled by four element assignments. A brace initializer
    (`u16 sprite[4] = {1, 0, 0, e->frame}`, or `{1, 0, 0, 0}` plus a store) makes agbcc call `memset`/`memcpy`,
    which the ROM does not contain.
12. **The loop** is a pointer walk `for (i = 0; i < data_03000E30.count; i++, e++)` with `e = data_03000E30.entries`
    loaded once before the loop (0x0804C052). The ROM increments i before e (0x0804C228..0x0804C22E) and re-reads the
    count each iteration (0x0804C230..0x0804C232). This matched first time.

## Types and names

- The 28-byte record is a local `AnimEntry`. `ffta.h`'s `Entry` has the same offsets, but spells +0x00 as `u32` and
  +0x04 as `unknown_04[4]`, so using it would need casts. Each sibling of this module (0804C668, 0804C6E4, 0804C740,
  0804C7EC) declares its own local view of the record. +0x14 is read as a byte (`ldrb r3, [r5, #0x14]` at
  0x0804C148), unlike the `u16 field_14` view in 0804C740.
- `data_03000E30` is `{u16 count; u16 unknown_02; void *entries;}`, as `DispatchList` in `src/08035174.c`.
  `void *entries` lets the same pointer go both to the record walk and to `func_0804C788(u8 *, ...)` (`ffta.h`).
- The menu state's +0xF1C..+0xF21 names (`count`, `state`, `unknown_F1E`, `selection`, `previous_selection`, `flags`)
  follow `src/0804ADC8.c` and `src/0804AD44.c`. The position array at +0xEDC (stride 4, x at +0, y at +1) follows
  0804AD44's `field_edc` / `field_edd`.
- `data_030009E0` uses the 0x4C-byte record with `s8 x, y` at +0x34/+0x35 from `src/08038028.c` (`ldrsb` at
  0x0804C2A4 and 0x0804C2C6 confirms signed).
- The callee prototypes follow `src/08001CF0.c` and `src/08001F34.c`, except that the last `func_08001F34`
  parameter is `u32`, as several matched callers declare it; a byte record field is passed there.
- The gauge fields +0x18 (u8) and +0x19 (s8, from `ldrsb` at 0x0804C266 and 0x0804C27C) are `field_18` and
  `field_19`. Their only proven role is the y passed to `func_0804C788` for records 2 and 1.

kit issue: shubshub/fftadecomp-kit#74 (a switch combined with a local buffer; here also two compiler runtimes and named data)
kit issue: shubshub/fftadecomp-kit#349 (the buffer selector's `named-data buffer caller excludes local BL and word switches`)
