# 0x08128FC4 - event effect on a unit: bytes identical, refused (signed quotient and remainder runtimes beside a jump table and call thunks, with a stack buffer passed to a callback) (1240 bytes)

Attempt 2026-11-20, kit b141ba59, decomp main 82b7baab5e.
`u16 func_08128FC4(State08128FC4 *state)` applies one event effect to the unit `state->unit` (+8), chosen by the
4-bit kind in `state->key` byte 1 bits 4-7, with a 3-bit tier in key byte 2 bits 0-2. It writes the message at
`state->line` (+0x3A8) and returns 0, an item id tagged 0x1000 (the caller, 0812949C, draws the item's icon) or
0x2000 (the gil icon). The kinds are:

1. stat drain (`func_08128C3C`);
2. a template name (`func_08128EE0`);
3. receive a random item from one of three lists;
4. `func_08128E40` with a per-tier count;
5. lose AP in a random ability;
6. lose a random piece of equipment, or all of it at tier 3;
7. raise story counter 12;
8. lose gil.

## The index

The index row `08128FC4 0812949C 1240 486 return` is right: the epilogue fits the prologue, the last pool word is at
0x08129498, and 0x0812949C starts the next function. The kit's `analyze.refine_function` closes the CFG with 486
reachable instructions.

## Byte identity

`08128FC4.c` (SHA-256 `2df4d82542962849f8d1d9516eccc6cbcdb5380d0d0b3baf2aeac26e96cfa12a`) was compiled with the
fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`)
and linked by hand at 0x08128FC4, with every callee, runtime and data symbol bound to its ROM address
(46 `R_ARM_THM_CALL`, 31 `R_ARM_ABS32`; `__modsi3` -> 0x08142950, `__divsi3` -> 0x081426B8, `_call_via_r2` ->
0x0814224C). The 1240-byte symbol equals the ROM span `[0x08128FC4, 0x0812949C)`: SHA-256
`b0ade7291376e4139b6ee6e11c6b93d7a7785fb4ce6b07c4ea34c574e18b2bf1` for both. `.text` is exactly 1240 bytes, and the
object defines one symbol, `func_08128FC4` (size 0x4D8): the two helpers are fully inlined and leave no out-of-line
copy. A second check applied each relocation of the unlinked object by hand (ABS32 against `.text`: base + addend;
against a data name: its address; THM_CALL: the `bl` re-encoded to its target) and found 0 differing halfwords.
`match.py` refuses at its link and binding stage, before its own byte comparison (below). `plausible.py --strict`
exits 0.

## Data symbols

Four are needed; none exists yet. All four are contiguous with the existing `data_083A8260` (`u8[4]` divisors
{10, 5, 2, 1}, read at 0x08129430) and end at the existing `data_083A8284`. ROM bytes 0x083A8260-0x083A8283:
`0a 05 02 01 | 03 05 0a 14 | 6a 01 6f 01 70 01 71 01 72 01 75 01 | 6b 01 6d 01 76 01 73 01 74 01 | 6c 01 6e 01 77 01`.

| Symbol | Type and contents | Pool word / load | Use |
|---|---|---|---|
| `data_083A8264` | `const u8[4]` = {3, 5, 10, 20} | 0x08129174 / `ldr` 0x0812915C, `add r0, sb; ldrb` 0x0812915E-0x08129160 | the tier's count, passed to `func_08128E40` at 0x08129162 (kind 4) |
| `data_083A8268` | `const u16[6]` = {0x16A, 0x16F, 0x170, 0x171, 0x172, 0x175} | 0x081290FC / 0x081290C4, count `movs r1, #6` 0x081290C6 | item list, tiers 0, 1 and 4-7 (kind 3) |
| `data_083A8274` | `const u16[5]` = {0x16B, 0x16D, 0x176, 0x173, 0x174} | 0x081290B0 / 0x081290AC, count `movs r1, #5` 0x081290AA | item list, tier 2 (kind 3) |
| `data_083A827E` | `const u16[3]` = {0x16C, 0x16E, 0x177} | 0x081290C0 / 0x081290BA, count `movs r1, #3` 0x081290BC | item list, tier 3 (kind 3) |

Each list entry is read with `ldrh r0, [r4]` (0x081290D4, 0x081290E0), tested by `func_080CB2B4` and copied to the
stack list; the drawn id goes to `func_080CA7A4` (name) and `func_080CA9E8(id, 99)`. The three item lists are
addressed by three separate zero-addend pool words, so they are three objects.

Existing symbols used: `g_table_085567F0` (text pointers), `g_table_08526680` (item names), `g_callbacks_0836D4B8`
(the clear routine, called through `_call_via_r2`), `g_state_02000000` (u32 gil at +0x1F64: pool 0x08129490 plus the
offset word 0x08129494) and `data_083A8260`.

Without the four symbols the default run refuses earlier:
`data target must be an undefined mapped object; compiler signed runtime thunks: addressed ABS32 requires an aligned unique undefined global with its exact type`.

## Refusals

Kit b141ba59, `match.py --root . --no-write` with this source copied to `src/08128FC4.c` and the four data symbols
added. None matched.

| Selector | Refusal |
|---|---|
| default (re-routed to `compiler-signed-runtime-thunks-data-v1`) | `signed quotient excludes other runtime, literal, switch and thunk profiles; compiler signed runtime thunks: addressed ABS32 requires an aligned unique undefined global with its exact type` |
| `--addressed-signed-runtime-profile compiler-signed-runtime-thunks-data-v1` | `addressed ABS32 requires an aligned unique undefined global with its exact type` |
| `--owner-runtime-profile canonical-integer-scalar-data-source-v1` | `six-word integer source requires canonical integer calls and zero-addend named objects` |
| `--switch-data-profile switch-thunks-frame-v1` | `signed quotient excludes other runtime, literal, switch and thunk profiles` |
| `--owner-runtime-profile bounded-buffer-conditional-thunks-v1` | `function address requires a canonical addressed function` |

The first ABS32 relocation in the object is the jump-table pointer at offset 0x40 (0x08129004). It is relocated
against the `.text` section symbol, so the re-routed selector's "undefined global" check fails there first; that
selector's README section also lists switches and local buffers passed to callbacks as excluded.

## Cause

All of these sit in one framed function:

- compiler `__modsi3` at 0x08129032 (kind 1, `% 7`), 0x08129112 (kind 3), 0x081291D4 (kind 5) and 0x08129302
  (kind 6), all `(s16)func_08002804() % n`;
- compiler `__divsi3` at 0x08129438 (kind 8, `20000 / data_083A8260[tier]`);
- one guarded word jump table: `subs r0, #1; cmp r0, #7; bls` at 0x08128FF0-0x08128FF4, the default `b` at
  0x08128FF6, the dispatch at 0x08128FF8-0x08129000, the pointer word at 0x08129004, eight entries at
  0x08129008-0x08129027;
- two `_call_via_r2` callback calls, each target loaded with `ldr r2, [r0]` from `g_callbacks_0836D4B8`: 0x08129194
  (kind 5) is passed the heap buffer returned by `func_08121B64`; 0x081292A2 (kind 6) is passed a **stack buffer**
  (`mov r0, sp` at 0x0812929E, size 10);
- variable indices into a stack list taken from the `__modsi3` result: `lsls r0, #1; add r0, sp, r0; ldrh` at
  0x08129116-0x0812911A and 0x08129306-0x0812930A;
- typed data: the four new symbols plus the five existing ones above;
- a 0x18-byte frame: sp+0..0xB is the shared u16 list (u16[6] in kind 3, u16[5] in kind 6), sp+0xC the spilled
  return value, sp+0x10 the spilled kind-5 draw, sp+0x14 a caller-save slot (`str` 0x08129312, `ldr` 0x08129324).

A profile would have to compose signed division and remainder, the guarded switch, thunk target loads, a stack
address passed to a callback, a runtime-bounded stack index and typed data in a framed owner.

## Bug check

No original bug is reproduced, so no `docs/bugs` case is needed.

- **Negative stack index:** `func_08002804` returns `(seed >> 16) & 0x7FFF` (`src/08002804.c`), so its `(s16)` is
  non-negative and every `% n` is in `[0, n)`. Each draw is guarded by `n != 0`: kind 3 tests n at 0x081290F0,
  kind 5 at 0x081291C6, kind 6 at 0x081292E0. Kind 6 at tier 3 sets n = 1 but draws nothing.
- **Not-found slot:** the kind-6 search leaves -1 (slot 0xFF) only if the item is not equipped. The item was drawn
  from the equipment list itself, and tier 3 passes 0, so this cannot happen.
- **Kind-5 buffer bounds:** the list is `count` bytes, and indices 1..count-1 write at most count-1 entries; with
  count 0 the loop does not run.
- **Kind-3 list bounds:** each list has at most 6 entries, and the stack list holds 6.
- **Kind 8:** every divisor value is nonzero, and the subtraction is clamped to the current gil.
- **Tiers 4-7:** the tier is 3 bits, but `data_083A8260` and `data_083A8264` have 4 entries each, so tiers 4-7 would
  read the following table. The merged sibling 08128C3C reads `data_083A8260[index]` the same way; its report lists
  the 8 values {10, 5, 2, 1, 3, 5, 10, 20}. Nothing shows that tiers above 3 occur, so no bug is claimed.

## Source notes

1. **Two `static inline` helpers, `pick_ability_with_ap` (kind 5) and `take_equipment` (kind 6).** Both perform
   domain operations the ROM shows:
   - `pick_ability_with_ap`: allocate a byte list (`func_08121B64`) the size of the unit's ability count
     (unit+0x34), clear it through `g_callbacks_0836D4B8[0]`, collect abilities 1..count-1 whose AP
     (`progress & 0x7F`) is nonzero, draw one, and free the list (`func_08121B78`);
   - `take_equipment`: find the item's slot, unequip it (`func_080CAF78(unit, 0, slot)`), add it to the inventory
     (`func_080CA9E8(item, 1)`) and recalculate (`func_080CB54C(unit, 1)`); with item 0 it does this for every
     equipped slot. It then calls `func_080CA2E8(unit)`.

   No out-of-line copy of either exists: a scan of every `bl` in the ROM for the sequence 080CAF78 / 080CA9E8 /
   080CB54C finds only 0x08129366 and 0x0812938C, both in this function. Two spellings are byte-identical; see
   "Both byte-identical spellings" below. The plain form (one variable per value, written inline in the cases)
   allocates differently throughout: unit in r7, tier in r8, line in r9 and text in r6 where the ROM has unit r8,
   tier sb, line sl and text r7; the kind-5 draw in sl instead of a stack slot; a 0x14-byte frame; a normalised
   instruction-sequence ratio of 0.48. Splitting the two values (by either spelling) raised it to 0.93 and put
   unit, tier, line and text in the ROM's registers.
2. **`take_equipment` reuses its parameter `item` as the loop value in the take-all branch**
   (`item = unit->equipment[slot]`). The ROM holds the argument and the loaded piece in the same register: r5 at
   0x08129330 and `ldrh r5, [r6]` at 0x0812937E. With a separate `u16 piece` local the `unit + 0x2A` pointer was
   spilled to the stack and 255 halfwords differed.
3. **Comma `for` initialisers.** Kind 5: `for (i = 1, n = 0; ...)`; the ROM sets i (`movs r2, #1`, 0x0812919C) before
   n (`movs r4, #0`, 0x0812919E). Kind 6 search: `for (slot = 0, found = -1; ...)`; the ROM sets slot (`movs r4, #0`,
   0x08129336) before found (`movs r2, #1; rsbs`, 0x08129338-0x0812933A). The plain forms `n = 0; for (i = 1; ...)`
   and `found = -1; for (slot = 0; ...)` emit the two in the opposite order. Matched sources use the same idiom, for
   example 0805459C (`for (i = 0, count = 0; ...)`) and 08061C9C (`for (i = 0, minimum_age = 0xFF; ...)`). The
   kind-3 and kind-6 gathering loops are written the same way for consistency; their counters are eliminated, so
   they compile to the same bytes either way.
4. **Kind 3, first branch only, assigns `count = 5` before `items = data_083A8274`.** The ROM has `movs r1, #5` at
   0x081290AA before `ldr r0, =0x083A8274` at 0x081290AC; the other two branches load the table first (0x081290BA
   then 0x081290BC; 0x081290C4 then 0x081290C6). A uniform order leaves 2 halfwords different (0x081290AA,
   0x081290AC). This is statement order inside an if/else chain; a `switch` on the tier would place the dispatch
   before the bodies, which the ROM does not.
5. **`AbilityState08128FC4 *abilities = &unit->abilities;` in the kind-5 helper.** The ROM keeps unit+0x34 in r5
   (0x08129180-0x08129182) and rereads the count through it inside the loop (`ldrb r1, [r5]` at 0x081291C0).
   Spelling `unit->ability_count` at each use gave a second loop-invariant copy of the address (r3) and swapped the
   registers of n and the pointer. `abilities->progress[i]` and `unit->abilities.progress[i]` both match; the helper
   uses the former. Siblings use the same pointer idiom: 080CB0D8 `abilities = &unit->abilities` and 080CAF78
   `actions = &data->actions`.
6. **Kind 6 uses separate loop variables for gathering (`i`) and for the slot walks (`slot`).** The gathering counter
   is r3 (`movs r3, #4` at 0x081292B0, `subs r3, #1` at 0x081292C0); the slot walks use r4. Reusing `i` for both put
   the gathering counter in r4, leaving 3 halfwords different (0x081292B0, 0x081292C0, 0x081292C2). In the helper
   spelling this separation is simply the helper's own scope.
7. **Kind 7 clamps with `if (level <= 1) level = 1;` and `if (level <= 2) level = 2;`.** The ROM has
   `cmp r4, #1; bhi` at 0x081293C0 and `cmp r4, #2; bhi` at 0x081293CE; `level < 1` would compile to `cmp #0`.
8. **Kind 8 clamps with `if (gil <= amount) amount = gil;`.** The ROM has `cmp r2, r1; bhi` at
   0x08129448-0x0812944A; `gil < amount` would give `bhs`.
9. **Kind 5 halving:** `level < info->required_points / 2`, then `if (level & 1) level++; level /= 2;`, else
   `level = required_points / 2`. The u8 `level` and the u8 `/ 2` give the unsigned compare `bhs` at 0x08129238 and
   the `lsrs` at 0x08129232 and 0x08129244; the whole byte is stored back with `strb` at 0x08129266. Sibling 080CB0D8
   reads `progress & 0x7F` into a u8 the same way.
10. **Prototypes.** `func_080CCA80` is declared returning `u8`: its definition returns `u32`, but the call site
    narrows it (`lsls r0, #24` at 0x08129148), as 08061DD0 and 0802F400 declare it. `func_08128EE0` is declared
    returning `const u8 *`: its matched definition says `u32`, but the value is a `g_table_085567F0` text pointer
    passed straight to `func_08018C24`.

## Both byte-identical spellings for notes 1 and 6

Both compile to the same 1240 bytes. They differ only in how the two copies and the second loop variable are
written.

**A. Inline helpers (the parked `08128FC4.c`).**
- `u8 ability = pick_ability_with_ap(unit);`. The helper's `selected` is the spilled slot sp+0x10 (stores at
  0x0812919A and 0x081291DC); 0x081291E4 `ldr r5, [sp, #0x10]` is the return value moving into the caller's
  `ability`.
- `if (n != 0) take_equipment(unit, picked);`. 0x08129330 `adds r5, r2, #0` binds the argument `picked` (r2,
  caller-saved around `func_080CA7A4` at sp+0x14, 0x08129312/0x08129324) to the parameter `item`.
- The helper's `slot` (r4, 0x08129336, 0x0812937C) is a different variable from the caller's gathering counter (r3,
  0x081292B0) because it lives in another function.

**B. Explicit copies, everything inline in the switch.**
- Kind 5 declares `u8 selected; u8 ability;`, writes the selection loop inline and adds `ability = selected;` after
  `func_08121B78(learned);`; 0x081291E4 is that assignment.
- Kind 6 declares `u16 picked; u16 item; s32 slot; s32 found;` and writes
  `if (n != 0) { item = picked; if (item != 0) { ... } else { for (slot = 0; ...) { item = unit->equipment[slot]; ... } } func_080CA2E8(unit); }`;
  0x08129330 is `item = picked;`.
- The search and take-all loops use `slot` and gathering uses `i`, which accounts for r4 against r3 at the addresses
  above.
- The rest of the source is the same as A.

Neither spelling corresponds to an out-of-line ROM function or to text shared with a merged sibling.

## For the reviewer

Which spelling ships for notes 1 and 6 is unresolved. Both reproduce the ROM byte for byte, and the addresses each
one explains are listed above; choose between them. Separately, the function cannot be admitted until the kit
composes the shape described under "Cause".

## Attempt record

| Attempt | Change | Result |
|---|---|---|
| r0 | plain form: one variable per value, statements in natural order | ratio 0.48; allocation differs throughout; frame 0x14 |
| r1 | explicit copies (`ability = selected`, `item = picked`) | ratio 0.93; unit, tier, line and text in the ROM's registers |
| r2 | comma initialisers in kind 5 and the kind-6 search | initialisation orders fixed |
| r3 | `abilities` pointer local | ratio 0.985; 5 halfwords left (kind-3 order, kind-6 counter) |
| r4 | kind-3 first-branch order; separate kind-6 loop variable | byte identical (spelling B) |
| r5 | inline helpers instead of the copies | byte identical (spelling A) |
| r6 | helpers plus a separate `piece` local in the take-all loop | 255 halfwords differ; reverted (note 2) |
| r7 | helpers plus comma initialisers in every loop, `abilities->progress[i]` | byte identical; the parked source |

The final version only renamed one local and folded `u8 ability` into its initialiser; it re-checked byte identical
and plausible-clean.

kit issue: shubshub/fftadecomp-kit#74 (a switch combined with `_call_via_rN` thunks and a local buffer; here also two compiler runtimes)
