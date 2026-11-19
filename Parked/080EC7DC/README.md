# 0x080EC7DC - column drop window effect: bytes identical, refused (a compiler `memcpy` in the volatile semantic check, then a stack index a callee wrote) (1280 bytes)

Attempt 2026-11-20, kit b141ba59, decomp main 82b7baab5e. First attempt at this address.
`u32 func_080EC7DC(void *task, Descriptor080EC7DC *descriptor, Payload080EC7DC *payload)` is a scene effect that drops
one screen column at a time. Phases 0x100 and 0x101 capture two BG maps and upload them to 0x06005800 and 0x06005000;
case 1 hides BG2, BG3 and window 0; case 0x102 programs the window registers, reads the two layers' BG priorities
through `func_0801E620` and indexes a local `u16 priorities[4]` with them for the two BGxCNT values. Then, per step
of the 11-step table `data_08399160`, phase 0x103 opens window 0 over the step's column (`data_0839914C`) and starts
an interpolated line downward (a per-step flag in `data_0839924C` also starts a `func_080DFD8C` effect), 0x104 follows
the line, and 0x105 and 0x106 shift the column's map rows down by the step's drop in each layer. After phase 0x102,
a shake offset of +3 or -3, toggled every two frames, is added to the vertical offsets of all four layers it sets.

## The index

The index row `080EC7DC 080ECCDC 1280 541 return` is right. The start is word aligned, the last pool word is at
0x080ECCD8, and the epilogue (`add sp, #0x10; pop {r3, r4, r5}` into r8-r10, `pop {r4-r7}`, `pop {r1}; bx r1`) fits
the prologue. The kit's `analyze.refine_function` closes the CFG with 541 reachable instructions.

## Byte identity

`080EC7DC.c` (SHA-256 `d57aef4e3bede3f3bd9ad83cab969932d9247ab2a5551fe3bb43cc683956cf44`) was compiled with the
fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`)
and linked by hand at 0x080EC7DC, with every callee and data symbol bound to its ROM address (40 `R_ARM_THM_CALL`,
13 `R_ARM_ABS32`; the compiler's `memcpy` -> the pinned copy helper 0x081443FC) and the object's `.rodata` placed at
0x08149CE0. The 1280-byte symbol equals the ROM span `[0x080EC7DC, 0x080ECCDC)`: SHA-256
`bad409eb3e1a86b151ff3d26610883f18097b698a0f03901986a390cc4bfe170` for both. `.text` is exactly 1280 bytes. The
8-byte `.rodata` initialiser equals the ROM at 0x08149CE0 (`00 00 01 00 02 00 03 00`). `match.py` refuses before its
own byte comparison (below). `plausible.py --strict` exits 0; the refusal comes from `match.py`'s own volatile
semantic check, which `plausible.py` does not run.

## Data symbols

None of the four is in `config/data_symbols.json`:

| Symbol | Literal words | Loads | Use |
|---|---|---|---|
| `data_0839914C` | 0x080ECAE4, 0x080ECB9C, 0x080ECCB8 | 0x080ECA74 (phase 0x103), 0x080ECB2A (0x105), 0x080ECBA8 (0x106) | 5 column records `{u8 left, u8 right, u8 pad[2]}`, stride 4, indexed by `payload->column`. Bytes `00 30 / 30 50 / 50 90 / 90 b8 / b8 f0`: the 240-pixel screen cut into five columns. `left` goes to WIN0H's high byte (0x3B) and `right` to its low byte (0x3A); both `>> 3` give the tile columns. |
| `data_08399160` | 0x080ECAE0, 0x080ECBA0, 0x080ECCBC | 0x080ECA68 (0x103), 0x080ECB3A (0x105), 0x080ECBB8 (0x106) | 11 step records `{u8 column, u8 drop, u8 duration, u8 unknown}`, stride 4, indexed by `payload->step`. It ends at 0x0839918C, the existing `g_table_0839918C` (sibling 080ECCDC). |
| `data_08399244` | 0x080ECAF0 | 0x080ECAC2 | First argument of `func_080DFD8C(..., 1, 4, 0, task)` at 0x080ECACC. Bytes `00 00 02 00 48 01 00 00`. |
| `data_0839924C` | 0x080ECAEC | 0x080ECAB6, byte read at 0x080ECABC | A `u8` flag per step (`01 01 01 00 01 00 01 01 01 01 00`); a nonzero flag starts the `func_080DFD8C` effect. |

0x08149CE0 needs no symbol: it is the compiler's initialiser for `u16 priorities[4] = {0, 1, 2, 3};`. It sits
directly before the initialiser of the next function (080ED4E8, `data_08149CE8`), which fits one translation unit's
`.rodata`.

## Refusals

Kit b141ba59, `match.py --root . --no-write` with this source copied to `src/080EC7DC.c` and the four data symbols
added.

**Refusal 1, the volatile semantic check (what stops it now).** With an owner selector, for example
`--owner-runtime-profile named-data-buffer-stack-index-v1`:

```
source    IMPLAUSIBLE
verdict NOT VERIFIED - the selector was not run

plausibility findings:
  allowlisted volatile semantic check: real compile of func_080EC7DC: the callee has no prototype with a fixed argument list, so its arguments cannot be compared at `bl	memcpy`
```

`named-data-buffer-stack-index-v2`, `named-data-buffer-rom-table-copy-v1` and `local-rom-halfword-table-v1` give the
same: the check runs before the selector. The default run (no selector) refuses differently, with
`compile failed: unexpected nonempty allocated section` (the `.rodata` initialiser).

The trigger is case 0x102. The local initialiser `u16 priorities[4] = {0, 1, 2, 3};` is lowered by agbcc to
`ldr r1, =.rodata; add r0, sp, #4; movs r2, #8; bl memcpy` (ROM 0x080EC91C-0x080EC922, a call to the pinned copy
helper `func_081443FC`). The same function writes allowlisted volatile members of `g_control_flags_03000940`
(`winin_lo`, `winout_lo`, `win0h_hi`, `win0h_lo`, `win0v_hi`, `win0v_lo`; 0x080EC954-0x080EC98E,
0x080ECA80-0x080ECA8A, 0x080ECC18-0x080ECC22), and those writes make the semantic check run. `memcpy` is undefined in
the source, so the check finds no prototype; its runtime table, `volatile_semantics.RUNTIME_ARITY`, lists only
`__divsi3`, `__udivsi3`, `__modsi3` and `__umodsi3`.

**Refusal 2, the stack index (what stops it next).** As a diagnostic only, a copy of the source with a file-scope
`extern void *memcpy(void *, const void *, u32);` passes the volatile check. The parked source does not carry that
prototype: the source never calls `memcpy`, so the declaration would exist only to satisfy the checker. On that copy:

| Selector | Refusal |
|---|---|
| `--owner-runtime-profile named-data-buffer-stack-index-v1` and `-v2` | `error (Refusal): stack index: index range leaves the allocated local frame ([-44, 468) outside [-48, 0)); index has no defined source (no premise can be stated)` |
| `--owner-runtime-profile named-data-buffer-rom-table-copy-v1` | `unsupported stack-address materialization` |
| `--owner-runtime-profile local-rom-halfword-table-v1` | `unexpected nonempty allocated section` |
| default | `unexpected nonempty allocated section` |

The stack-index trigger is in case 0x102:

1. `func_0801E620(&first, &second)` at 0x080EC9AA receives `add r5, sp, #0xC` (0x080EC99E) and `r8 = sp + 0xD`
   (0x080EC9A0-0x080EC9A4). That callee is `*first = g_state_02007F40[2]; *second = g_state_02007F40[3];`.
2. The owner reloads the bytes: `ldrb r0, [r5]` at 0x080EC9C2 and `ldrb r0, [r1]` (r1 = r8) at 0x080EC9FC.
3. It scales them into the stack table: `lsls r0, #1; add r0, sp, r0; adds r0, #4; ldrh` at
   0x080EC9C4-0x080EC9CA and 0x080ECA00-0x080ECA04.

The array is the initialised `u16[4]` at entry SP-44 .. -36 (sp+4 .. sp+0xC). Under the profile's rules an index
that arrives through a stack slot has no defined source. Once both gaps are closed and the data symbols are added,
the selector is `--owner-runtime-profile named-data-buffer-stack-index-v1`.

### The premise the rule would need

Two rows, one per access site, each with bound 4 (`u16` elements, s = 2):

- site 0x080EC9C6: the byte `func_0801E620` stored at entry SP-36 (sp+0xC), which is `g_state_02007F40[2]`, is
  below 4;
- site 0x080ECA00: the byte it stored at entry SP-35 (sp+0xD), which is `g_state_02007F40[3]`, is below 4.

Those bytes are the two map layers' BG priorities. The matched `0801E204` sets them to 2 and 3
(`first_mode = 2, second_mode = 3`) and names them so; the ROM ORs the table entry into the BGxCNT value passed to
`func_080034B8`, whose low two bits are the priority. The bound is a game-state invariant the ROM does not enforce
(compare kit #320).

## Bug check

No reachable bug. The inner loops of 0x105 and 0x106 are `for (y = 31; y >= drop; y--)` with `u8 y`; they would
never end if `drop` were 0, but `drop = step->drop >> 3` is 1 to 5 for all 11 records (`drop` bytes 0x10 0x10 0x08
0x10 0x08 0x18 0x10 0x08 0x18 0x10 0x28). `y - drop` stays at or above 0. The column tiles run from `left >> 3` up to
`right >> 3`, at most 30, inside the 32-wide map. `payload->column` comes from `step->column` (0-4) and indexes an
11-entry `column_offsets`. The `priorities[first]` index depends on the premise above.

## Source notes

1. **0x105 and 0x106 each declare their own `left, right, drop, x, y` in a case block.** The ROM gives `right` sb in
   0x105 (`mov sb, r0` at 0x080ECB38; compares at 0x080ECB4E and 0x080ECB7E) but r8 in 0x106 (`mov r8, r0` at
   0x080ECBB6; compares at 0x080ECBC6 and 0x080ECBFC). The hoisted `first_map` base is in r8 (0x080ECB4C), and
   0x106's hoisted 0x858 is in sb (0x080ECBCC). One variable cannot hold two hard registers, so these are two
   variables. With function-scope shared locals the single `right` (8 refs) outranks the base, takes r8 in both
   cases, and 0x105 differs in 6 lines. The two bodies are a copy-paste that differs only in the map, the VRAM
   address and 0x106's window reset; case-block locals are the idiom of sibling 080E9BDC
   (`case 0x101: { struct BgAffineDst dst; u32 control; ...}`) and of case 0x102 here. An equal alternative, not
   compiled, is a `do { } while (0)` statement macro used by both cases and declaring its own locals: the ROM repeats
   the block at 0x080ECB2A-0x080ECB80 and 0x080ECBA8-0x080ECBFE, though not with the same registers.
2. **The declaration order of the block locals is not load-bearing.** The reversed order (`x, y, drop, right, left`)
   is still identical; function scope against block scope is what matters (note 1).
3. **Separate `left`, `right` and `drop` locals, with `x = left` as the loop init.** The ROM computes each bound once,
   before the loops: `left` raw at 0x080ECB32, `right >> 3` at 0x080ECB36, `drop >> 3` at 0x080ECB44; it applies
   `left >> 3` only at 0x080ECB46, where the loop starts. The plain form, with the bounds inside the `for`,
   re-evaluates them in the loop (1356 bytes); writing `x = left >> 3` directly puts the shift right after the load.
   Three named bounds before a nested loop is ordinary code, and the names follow the data (column edges and drop
   in pixels).
4. **0x103 uses cached pointers; 0x105 and 0x106 index the tables directly.** In 0x103 the ROM scales the index
   before it loads the table address (0x080ECA64-0x080ECA6A for `step`, 0x080ECA70-0x080ECA76 for `column`), and
   both pointers stay live across the volatile window stores (r2, r1). In 0x105 and 0x106 the table address is loaded
   first (0x080ECB2A, 0x080ECB3A, 0x080ECBA8, 0x080ECBB8). Direct indexing in 0x103 (the first draft) recomputed
   both entries after the volatile stores.
5. **`first_offset` and `second_offset` are `s16`.** After the switch the ROM sign-extends the shake offset once
   (`lsls r4, #16; asrs r4, #16` at 0x080ECC6A) and adds it as `adds r0, r4, r0` (0x080ECC6E, 0x080ECC7C,
   0x080ECC8A, 0x080ECC98). In isolation, `u16` fields gave `adds r0, r0, r4` with no extension (the addition is
   narrowed), and `s16` fields gave the ROM's form. These are BG vertical offsets passed to
   `func_08003558(s16 offset, u8 layer)`.
6. **`s16 offset = payload->shake ? 3 : -3;`.** The ROM loads 0x0000FFFD from the pool (0x080ECC60) and overwrites
   it with 3 when `shake` is set; `s16` follows the parameter type. `payload->shake = !payload->shake;` gives the
   ROM's `movs r2, #0; ... bne; movs r2, #1; strb` (0x080ECC4A-0x080ECC58).
7. **Case 1 is three statements**: `display &= ~func_080035A8(2); display &= ~func_080035A8(3); display &= ~0x2000;`.
   This reproduces the ROM exactly, including the single load and store for the last two (`ldrh; bics; ldr =0xDFFF;
   ands; strh`, 0x080EC8A4-0x080EC8AC). `display = display & ~f(3) & ~0x2000` and `display &= ~0x2000 & ~f(3)` both
   materialise 0xDFFF first and differ. It reads as "hide BG2, hide BG3, disable window 0", the mirror of case
   0x102's `display |= 0x2000`.
8. **The caller's prototype `func_0801E144(s16 x, s16 y, s16, s16)` differs from the definition's `u16 x, u16 y`**
   (the matched 0801E144). The ROM passes the two fields with `ldrsh` (0x080EC928, 0x080EC92C), which needs signed
   parameters; a `u16` prototype gives `ldrh`. `int` would also fit; `s16` matches the descriptor's signed fields.
9. **The local initialiser `u16 priorities[4] = {0, 1, 2, 3};`** is kept rather than the explicit
   `func_081443FC(priorities, data_08149CE0, 8)` that siblings 080035D0, 080DE33C and 080DE9E0 use. The bytes at
   0x08149CE0 sit directly before 080ED4E8's initialiser at 0x08149CE8, which fits one translation unit's
   `.rodata`; local initialisers ship in 0810533C, 081171CC, 08111D50, 080FC800 and 080F5710. The explicit spelling
   would also need a new data symbol, and it would not clear refusal 2.
10. **Case 0 hoists `&payload->first_layer` and `&payload->second_layer` (r5, r1) ahead of the fill loop**
    (0x080EC846-0x080EC848). That comes from the plain source (`for (i = 0; i < 11; i++) column_offsets[i] = 0x50;`,
    then the stores and the call).
11. **Names and types.** The `LineState` layout is copied from siblings 080ED4E8 and 080E0A8C. `TransferRecord` is
    left incomplete, as in 080E0A8C's `RequestNode` usage. Members without evidence are `unknown_*`: `unknown_05`;
    `unknown_06`, which is only written here (a copy of `descriptor->x`); `unknown_2A`; and `unknown_105A`.
    `column_offsets[11]` spans +0x08..+0x1D because of the fill loop's bound (`cmp r2, #10; bls` at 0x080EC85C),
    although only 5 columns exist.
12. **No inline asm, pragmas, volatile beyond the shared control-flag declaration, inline helpers, macros or spare
    temporaries.** The only casts are the four `(void *)` VRAM destinations (0x06005800, 0x06005000) passed to
    `func_08000A98`.

## Attempt record

Each attempt was compiled the way `match.py` compiles and diffed with pools and branch targets masked. The first
draft (function-scope loop locals shared by 0x105/0x106, direct table indexing in 0x103, `u16` offset fields, and
case 1 as `display &= ~func_080035A8(3) & ~0x2000`) was 1308 bytes with 129 differing lines. With `s16` offset
fields, case 1 as three statements, cached `step`/`column` pointers in 0x103 and `left`/`right`/`drop` locals with
`x = left` as the loop init, it was 1280 bytes with 6 differing lines (r8 and sb swapped in 0x105). Declaring
0x105/0x106's locals in case blocks made it identical. On the identical source: the loop bounds evaluated inside the
`for` give 1356 bytes (150 lines); 0x104 written as `if (func_08007880(...)) { ... }` (sibling 080ED4E8) is
identical and is the parked form; the block declarations in reverse order are identical.

## Kit issues

- shubshub/fftadecomp-kit#410: the volatile semantic check refuses a compiler-emitted `memcpy` unless the source
  declares `memcpy`, a declaration it never uses. A trusted `memcpy: 3` arity (destination, source, byte count), or
  modelling the call through the existing pinned-helper summary, would let this function reach its selector.
- shubshub/fftadecomp-kit#411: a stack-table index read back from a local that a callee wrote through an out-pointer
  has no defined source. Unlike #361 (a loop-carried index joined around a back edge) there is no loop and no join,
  and unlike #387 nothing spills: each index has one definition, a callee's store into an owner byte that nothing
  else writes between the call and the load. A rule that carries the callee's stored expression to the owner's
  load (here `u8[data g_state_02007F40 + 2] via func_0801E620`) would then take the premise above.

kit issue: shubshub/fftadecomp-kit#410
kit issue: shubshub/fftadecomp-kit#411
