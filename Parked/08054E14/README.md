# 0x08054E14 - unit-list payment menu task: bytes identical, refused (same-function long BL jumps in a switch function) (3620 bytes)

Attempt 2026-11-20, kit b141ba59, decomp main 82b7baab5e.
`void func_08054E14(u8 index, u8 *state)` is a task callback: `func_08054664` registers it at 0x08054CCC with
`func_08006ADC(ctx + 0x1478, 0, func_08054E14)`, where `ctx` is `data_0200F428`. The first argument is unused (r0 is
never read). It runs a unit-list menu: pick a unit from `entries[]` (filled by `func_0805451C`), quote its cost with
`func_080CCC6C`, confirm through the message box at ctx+0xCD4, compare the cost with the money word at 0x02001F64 and
subtract it, and apply `func_080CC65C` to the unit.

It switches on `*state` through a 256-entry jump table at 0x08054E38 (guard `cmp r0, #0xff; bls`). There are 27
distinct targets, states 0, 1, 2, 20, 21, 22, 40, 41, 100-105, 120-122, 160, 161, 180, 181, 200, 201, 220-222 and
255; the other 229 entries go to the exit at 0x08055C10. Every path ends with `func_0802995C(ctx + 0x1C58)`.

The switch uses the fixed pool layout: the dispatch is at 0x08054E28..0x08054E31, a zero alignment halfword sits at
0x08054E32, and the table pointer is at 0x08054E34, directly followed by the table. No word is interposed, so the
matching selector family is `-frame-v1`, not `-frame-v2`. The frame holds only outgoing stack arguments: three words
for `func_0802A1FC`, two for `func_080581AC`, one for `func_0802B2E8` and one for `func_08029F18`. The named data,
all already mapped, are `data_0200F428`, `data_03000000`, `data_030008B0`, `data_03000990`, `data_030027F4`,
`g_control_flags_03000940`, `g_state_0200F390` and `g_state_02000000` (addends 0 and +0x80). The function literals,
all indexed entries outside the caller, are `func_0805463C` (pool word 0x080553D0), `func_08055DC4` (0x08055648) and
`func_08054664` (0x080556D0).

## The index

The index row is `08054E14 08055C38 3620 1806 return`. The extent is right: the start is word aligned, and the
prologue `push {r4-r7, lr}; mov r7, r8; push {r7}; sub sp, #0xc` pairs with the epilogue at 0x08055C1C
(`add sp, #0xc; pop {r3}; mov r8, r3; pop {r4-r7}; pop {r0}; bx r0`). The instruction column is not the reachable
count: the kit's `analyze.refine_function` closes the CFG with 910 reachable instructions, and only with its
same-owner long-branch opt-in. Not corrected here: no draft needs it.

## Byte identity

`08054E14.c` (SHA-256 `37639bc613a6ff6b9b4b0ded7a4fb1019ca9b5a4e1590c27acb6790411797dcc`) was compiled with the
fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`)
and linked by hand at 0x08054E14, with every callee, function literal and data symbol bound to its ROM address
(86 `R_ARM_THM_CALL`, 309 `R_ARM_ABS32`, including the table pointer and the 256 case words). The 3620-byte symbol
equals the ROM span `[0x08054E14, 0x08055C38)`: SHA-256
`940d82a7703f9cc839cfb1e05eda1f3fa9f16eab73cc9d8a930c6a161ada20fc` for both. `.text` is exactly 3620 bytes. The 11
same-function long BL jumps below are resolved by the assembler without a relocation. `match.py` refuses before its
own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

None needed.

## Refusals

Kit b141ba59, `match.py --root . --no-write` with this source copied to `src/08054E14.c`. None matched.

| Selector | Refusal | Raised at |
|---|---|---|
| default | `switch evidence excludes object, callback and runtime-thunk bindings` | `match.py:1148` |
| `--switch-data-profile u16-scalars-functions-frame-v1` | `call is not a validated external direct Thumb BL` | `match.py:4828`, `verify_leaf_instructions`, at `0x08054E24 bl #0x8055c10` (the guard's default jump) |
| `--owner-runtime-profile restoring-owner-runtime-v1` | `owner profile requires actual compiler UDIV and indirect thunk calls` | `owner_admission_profile.py:1362` |

The fitting selector is `u16-scalars-functions-frame-v1`: a fixed pool layout, every other reached literal a typed
object, a function word or a u16 scalar, and a fixed frame of write-only outgoing words. It refuses only because of
the long BLs.

Not run, and why:

- `u16-scalars-functions-frame-v2` requires a dispatch-identified pool with at least one interposed word; this
  function has the fixed layout.
- `switch-thunks-frame-v1` requires `_call_via_rN` thunks; there are none.
- `numeric-data-switch-source-v1` refuses any local BL.
- `ordinary-multiple-switch-source-v1` needs two to eight tables; this function has one.
- The other `restoring-owner-switch-*` selectors exclude named data, function literals, or both.
- The addressed-runtime thunk selectors admit same-owner long BL, but exclude switches and function literals.

## Cause: 11 same-function long BL jumps

agbcc emits a `bl` (marked `@far jump` in its assembly) for an unconditional jump that a narrow `b` cannot reach. Two
targets are involved: 0x08055C0E is the cross-jumped `strb r0, [r7]` (`*state = value`), after which execution
falls into the exit; 0x08055C10 is the switch exit, `func_0802995C(ctx + 0x1C58)` and then the epilogue.

| Site | Target | Source path |
|---|---|---|
| 0x08054E24 | 0x08055C10 | switch guard default |
| 0x0805525E | 0x08055C0E | state 0, `*state = 1` (no units) |
| 0x08055286 | 0x08055C0E | state 0, `*state = 20` |
| 0x080552B6 | 0x08055C10 | state 1, end of case |
| 0x080552DC | 0x08055C10 | state 2, message state is not 5 |
| 0x080552EC | 0x08055C10 | state 2, A not pressed |
| 0x080552F2 | 0x08055C0E | state 2, `*state = 255` |
| 0x08055316 | 0x08055C10 | state 20, message still busy |
| 0x0805534A | 0x08055C0E | state 20, `*state = 21` |
| 0x08055372 | 0x08055C10 | state 21, window not ready |
| 0x080553BC | 0x08055C10 | state 21, end of case |

All other `bl`s in the span are ordinary external calls. Cases placed after 0x080553E0 reach the two targets with a
narrow `b`. This is the gap 0x0804CBB4 (published alongside) describes in full, with a possible fix and a minimal
reproducer: the switch-data selectors grant no call permission to same-owner long BL edges, which only the thunk
selectors admit today.

## Source notes

The case order in the source follows the ROM layout: 0, 1, 2, 20, 21, 22, 40, 41, 255, 100..105, 120..122, 160, 161,
180, 181, 200, 201, 220..222.

1. **`if ((s16)(list.position - 3) < 0) list.position = 0; else list.position -= 3;`** and the down-path
   counterpart `if ((s16)(list.position + 3) > count - 3) list.position = count - 3; else list.position += 3;`. Up
   path in the ROM (0x08055470..0x0805547C): `subs r2, #3; lsls r0, r2, #16; cmp r0, #0; bge`, then `strh r5, [r1]`
   (0) or `strh r2, [r1]` (the raw difference). Down path (0x08055558..0x08055568): `ldrh r0, [r4]; adds r1, r0, #3;
   lsls r0, r1, #16; asrs r0, r0, #16; cmp r0, r3; ble`, then `strh r3, [r4]` or `strh r1, [r4]`. So the comparison
   is made on a 16-bit value and the store writes the unextended sum. The cast changes the value (it truncates an int
   to s16). The tests are under "For the reviewer".
2. **`Controls cursors[2]` in the window struct, with each row read as `window.cursors->value`.** The ROM always
   forms the cursor base 0x14DC first and then reads `[base, #0x11]`; the base is formed at 0x0805544A, 0x0805548A,
   0x080554A6, 0x080554F8, 0x08055530, 0x08055576, 0x08055590 and 0x080555EC, and no flat 0x14ED offset appears.
   There are two adjacent 0x14-byte cursor records at 0x14DC and 0x14F0: `func_080583FC` is called with
   (ctx+0x14F0, ctx+0x14DC), and the merged `src/08055C38.c` lays the same window out as
   `List list; Controls controls; u8 cursor[0x14];`. In the source, `func_080583FC(&window.cursors[1],
   window.cursors)` and `func_0805872C(window.cursors, n)` pass the same records. The tests are under "For the
   reviewer".
3. **A `u8 row` local, loaded before each `func_0805871C` call**: `row = window.cursors->value; selected =
   func_0805871C(&window.list, row);`. The ROM loads the row before it forms the list address (row loads at
   0x080554A6..0x080554A8, 0x08055590..0x08055592 and 0x080555EC..0x080555EE; list addresses at
   0x080554AA..0x080554AC, 0x08055594..0x08055596 and 0x080555F0..0x080555F2). Passing the row inline as the argument
   forms the list address first. Merged siblings use the same idiom: `u8 row = cursor->row;` in `src/08055DC4.c`,
   `src/080531F0.c` and `src/08057298.c`.
4. **`selection = &g_state_02000000.selection; selection->cost = data_0200F428->cost;` in state 101.** In the ROM
   (0x08055732..0x08055746) r4 is loaded with 0x02000080 for the unit address; `ldr r1, =0x2050; adds r4, r4, r1` then
   gives 0x020020D0, and `str r0, [r4, #8]` writes the word. The flat member store
   `g_state_02000000.selection.cost = ...` compiles to `str r0, [r4]` with a 0x2058 offset: one instruction differs,
   at 0x08055746. Merged `src/0805451C.c` and `src/0805459C.c` use the same pointer local
   (`Selection *selection = &g_state_02000000.selection;`). The base relation also shows that the source names one
   object (`g_state_02000000`) for the units, the money word (0x1F64) and this block; a separate `g_state_020020D0`
   symbol would be loaded from its own pool word.
5. **The `u8 moved` flag** in the up and down paths is ROM-shown: it is cleared at 0x08055434 and 0x080554E4, set at
   0x08055498 and 0x08055584, and tested at 0x0805549A and 0x08055586. In the two branches that call
   `func_0805872C` the ROM has no `movs r5, #1`; their jumps at 0x08055460 and 0x08055546 go straight to the update
   block (0x080554A0 and 0x0805558A), past the test. There is a comment at the switch.
6. **`extern u8 g_control_flags_03000940[];`** for the two 0x50-byte copies (states 220 and 221). Including
   `control_flags.h` and passing `&g_control_flags_03000940` fails `plausible.py`'s allowlisted-volatile rule
   (`g_control_flags_03000940 may only be used as g_control_flags_03000940.member`). The array declaration follows
   the merged `src/0806094C.c` and `src/08070414.c`, which copy the same block the same way.
7. **The L+Up and L+Down tests are written as `(held & 0x200) && (repeated & 0x40)` and
   `(held & 0x200) && (repeated & 0x80)`.** The ROM tests `held` once (0x0805541C); the Down test at 0x080554DC reuses
   `repeated` from r1 without reloading it. The `&&` form matched on the first compile; a nested `if (held & 0x200)`
   form was not tried.
8. **`func_08013380()` is called up to three times in state 102**, at 0x0805578C, 0x0805583C and 0x08055856; each call
   is in the ROM.
9. **The state 220/221/222 block** follows the merged `src/0806094C.c` (cases 0x10C..0x10E): the same calls, sizes and
   order.
10. **The declaration order of the locals** (`moved`, `row`, `selected`, `selection`) does not matter: reversed, the
    output is still identical.
11. **Names.** `MenuContext`, `entries`, `count`, `selected` and `next` follow `src/08055C38.c`, `src/0805451C.c` and
    `src/08054DA8.c`; `Action` and `Update` follow `src/080581AC.c` and `src/0805463C.c`; `Input` follows
    `src/080581AC.c`. `cost` and `money` are named from use: the cost is compared with the money word and subtracted
    from it. Unknown members are `unknown_*`.
12. **`func_08054664` is declared `(u8 index, u8 *state)`**, the task-callback shape of this function. It is
    unmatched, and the declaration only takes its address; `(u32)func_08054664` converts it to the `u32 value`
    parameter of `func_08006ADC` in `ffta.h`.
13. **No original-game bug is reproduced**, so no bug case is needed.

## For the reviewer

### The cast in the condition (note 1)

These spellings of the up-path clamp were compiled as small test functions with the same struct offsets, followed by
a use of the position:

| Spelling | Result |
|---|---|
| `if ((s16)(pos - 3) < 0) pos = 0; else pos -= 3;` (s16 field) | `subs r3, r0, #3; lsls r0, r3, #16; cmp r0, #0; bge; ...; strh r3`: the ROM shape |
| `u16 p = pos - 3; if ((s16)p < 0) pos = 0; else pos = p;` | an extra `lsrs r3, r0, #16` before the stores |
| `s16 p = pos - 3; if (p < 0) pos = 0; else pos = p;` (s16 field) | an extra `lsrs` |
| the same with a u16 field | an extra `lsrs` |
| `if ((p = pos - 3) < 0) pos = 0; else pos = p;` | an extra `lsrs` |
| `s16 p = pos; p -= 3; if (p < 0) p = 0; pos = p;` | `ldrsh`, `lsrs`, a single store |
| `pos -= 3; if (pos < 0) pos = 0;` | two stores on the negative path |

In the full function, the first draft used an s16 local in both paths; it had the extra `lsrs` at the up clamp
(0x08055470) and at the down clamp (0x0805555A). Without the s16 truncation, an int comparison (`pos - 3 < 0`) does
not produce the `lsls #16` test at all. The question for review: is `(s16)(position - 3) < 0` a plausible original
spelling of "the new top row would go negative"? The position field is 16-bit and is read signed elsewhere (`ldrsh`
at 0x08055442 and 0x08055520).

### The `cursors[2]` array read (note 2)

A member-access chain on `data_0200F428->...` is folded into one constant offset (0x14ED). The ROM's `[base, #0x11]`
form appears only when the cursor address is a pointer value that the front end does not fold back into the chain: a
pointer variable, a cast, or array-to-pointer decay.

| Spelling | Result |
|---|---|
| `data_0200F428->window.controls.value` (flat member) | loads the flat 0x14ED offset (the first draft); every row read differs |
| `Controls *controls = &data_0200F428->window.controls;` before each use (the merged-sibling idiom) | `[base, #0x11]` reads, but at the `func_08055C38` calls the base is formed before the position load, where the ROM loads the position first (`ldrb` at 0x08055486, then the base at 0x08055488..0x0805548A) |
| `(controls = &...)->value` inside the argument | the ROM order, but an assignment inside a call argument |
| `((Controls *)&data_0200F428->window.controls)->value` (same-type cast) | the ROM order; identical code to the array form |
| `Controls cursors[2]` with `window.cursors->value` (the parked source) | the ROM order everywhere, with note 3's `row` local |
| `window.cursors[0].value` | folded to the flat offset again |

For the parked form: the two-record layout is evidenced (`func_080583FC(0x14F0, 0x14DC)` and the two 0x14-byte records
in `src/08055C38.c`), and the form needs no cast and no extra local. Against it: `cursors->value` for element 0 is a
less common spelling than `cursors[0].value`, which does not match, and the merged siblings in this module write a
pointer local for this record instead, a form that cannot reproduce the `func_08055C38` call order here. The cast form
gives the same bytes; it is a value-neutral cast, so it was not used.

kit issue to be filed: same-function long BL in switch selectors
