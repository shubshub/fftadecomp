# 0x08057578 - sliding counter panel runner: bytes identical, refused (a whole control-block save and restore beside volatile member writes) (1560 bytes)

Attempt 2026-11-20, kit b141ba59, decomp main 82b7baab5e.
`void func_08057578(u8 index, u8 *state)` is a runner callback: a `switch (*state)` over 11 phases (0, 1, 20, 21,
100, 101, 120, 140, 200, 220, 255). It saves the LCD shadow block, opens a window and blend effect, slides a 10x2
tile panel in from column 31 to column 20, counts down a unit record field once every 30 frames, slides the panel
back out, restores the shadow block, and waits for a button press. When the counter reaches 0 at a tick, phase 120
goes straight to phase 140 (the panel slides out). The reference to it is at 0x08056F6C, inside `func_08055F10`,
which phase 255 installs again.

## The index

The index row `08057578 08057B90 1560 599 return` is right: the start is word aligned, the
`push {r4-r7, lr}` / `push {r8-r10}` / `sub sp, #0x20` prologue fits the epilogue at 0x08057B74, and the last pool
word (0x08057B8C, `func_08055F10`) ends at the indexed end. The kit's `analyze.refine_function` closes the CFG with
599 reachable instructions.

## Byte identity

`08057578.c` (SHA-256 `31698e470151d3e79a682f3aa3e138a07972baf4df4c57cb3bb8270ad757fa87`) was compiled with the
fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`;
agbcc prints no warnings) and linked by hand at 0x08057578, with every callee, thunk, function literal and data
symbol bound to its ROM address (30 `R_ARM_THM_CALL`, 38 `R_ARM_ABS32`; the two `_call_via_r3` calls at 0x0805769E
and 0x08057AC4 -> the libgcc thunk 0x08142250). The 1560-byte symbol equals the ROM span `[0x08057578, 0x08057B90)`:
SHA-256 `390a833b0186c765e6b4f6c7be1613ff6fc68974761ada12f90e20a47392a68e` for both. `.text` is exactly 1560 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` refuses the source with six
volatile-allowlist findings; those findings are the refusal.

## Data symbols

One is needed: `data_0839380E` = `0x0839380E`, declared `extern const u8 data_0839380E[];`.

- The ROM loads it from three pool words, 0x08057864, 0x08057924 and 0x08057A24, as r0 (`source`) of
  `func_08001F34` at 0x08057820, 0x080578E8 and 0x080579D2.
- The bytes at 0x0839380E are `04 00 00 40 00 40 e0 02 08 40 00 40 e4 02 00 40 20 00 e8 02 08 40 20 00 ea 02 ...`:
  a count of 4 followed by OAM attribute triples, the sprite descriptor `func_08001F34` takes as its
  `const void *source` (`src/08001F34.c`). Its neighbours `data_083937F8` and `data_08393828` are already named.
- It is the only symbol missing (without it the default run refuses with
  `data target must be an undefined mapped object`). Every other pool word is an existing name (`data_0200F428`,
  `g_state_02000000`, `data_030008B0`, `data_03000990`, `data_03000000`, `data_0836D4BC`,
  `g_control_flags_03000940`), the function literal `func_08055F10`, the VRAM address `0x06009CE0` (written as a
  number, as `src/0802C72C.c` writes `0x06009440`), or a plain offset.

## Refusals

Kit b141ba59, `match.py --root . --no-write` with this source copied to `src/08057578.c` and the data symbol added.

1. Default:
   ```
   compile failed:
   function-address evidence does not support runtime call thunks
   ```
   Expected: the function has the `func_08055F10` literal and two `_call_via_r3` calls, so it needs the thunk
   selector.
2. The fitting selector, `--function-address-profile canonical-thunks-v1`:
   ```
   extent    1560 bytes (complete ELF symbol; typed function literals and canonical thunks; conditional returning indirect ARM ABI; no relocations)
   function-thunk source replay failed: function-thunk captured source changed or is implausible
   ```
3. The cause, `plausible.py src/08057578.c include`:
   ```
   6 finding(s): the code does not look like something a developer would have written
   A byte-identical compile is not a match if the source is implausible.
   src/08057578.c:
     08057578.c:111: ERROR: volatile-allowlist
         allowlisted volatile g_control_flags_03000940 may only be used as `symbol.member`: its address or whole object would carry the qualifier to other memory
     08057578.c:111: ERROR: volatile-allowlist
         no `&` may precede g_control_flags_03000940 (write `g_control_flags_03000940.x & a`): a member's address could reach a volatile member without its qualifier
     08057578.c:112: ERROR: volatile-allowlist
         allowlisted volatile g_control_flags_03000940 may only be used as `symbol.member`: its address or whole object would carry the qualifier to other memory
     08057578.c:193: ERROR: volatile-allowlist
         allowlisted volatile g_control_flags_03000940 may only be used as `symbol.member`: its address or whole object would carry the qualifier to other memory
     08057578.c:193: ERROR: volatile-allowlist
         no `&` may precede g_control_flags_03000940 (write `g_control_flags_03000940.x & a`): a member's address could reach a volatile member without its qualifier
     08057578.c:194: ERROR: volatile-allowlist
         allowlisted volatile g_control_flags_03000940 may only be used as `symbol.member`: its address or whole object would carry the qualifier to other memory
   ```

As a diagnostic only, replacing the two `&g_control_flags_03000940` with `(void *)0` and the two `sizeof` with `0x50`
in a throwaway copy leaves `plausible.py` with nothing to report, so these six findings are the only objection. That
copy's bytes differ, so it says nothing about whether `canonical-thunks-v1` would accept the rest (a fixed 0x20 frame
with `state` spilled to sp+0x1C, one function literal and two `_call_via_r3` calls). That part is untested, because
the gate refuses first.

## Cause

Lines 111-112, phase 1 (the save):

```c
data_0836D4BC[0](data_0200F428->saved_control, &g_control_flags_03000940,
                 sizeof(g_control_flags_03000940));
```

ROM 0x08057690-0x0805769E: `ldr r2, =data_0836D4BC` (pool 0x080576B8), `ldr r0, [r5]`, `ldr r1, =0x2DB4`,
`adds r0, r0, r1`, `ldr r1, =0x03000940` (pool 0x080576C0), `ldr r3, [r2]`, `movs r2, #0x50`, `bl 0x08142250`
(`_call_via_r3`). The count 0x50 is `sizeof` of the pinned declaration.

Lines 193-194, phase 200 (the restore, copied into the symbol):

```c
data_0836D4BC[0](&g_control_flags_03000940, data_0200F428->saved_control,
                 sizeof(g_control_flags_03000940));
```

ROM 0x08057AB8-0x08057AC4: `ldr r0, =data_0836D4BC` (pool 0x08057B1C), `ldr r2, =0x2DB4`, `adds r1, r1, r2`,
`ldr r3, [r0]`, `adds r0, r7, #0` (destination = the block), `movs r2, #0x50`, `bl 0x08142250`.

The volatile member writes that need `control_flags.h` in the same function, each `strb` preceded by a dead `ldrb`
of the same member:

- phase 20, pool 0x08057734: dead loads at 0x080576D8 (`winin_hi`), 0x080576E0 (`winin_lo`), 0x080576E8
  (`winout_lo`), 0x080576F0 (`bldcnt_lo`), 0x08057710 (`bldy_lo`), 0x08057716 (`win1h_hi`), 0x0805771C
  (`win1h_lo`), 0x08057724 (`win1v_hi`), 0x0805772A (`win1v_lo`); `display |= 0x6000` at 0x080576C6-0x080576D2 has a
  plain `ldrh`/`strh`, as the header models it;
- phase 21, `bldy_lo++`: a dead `ldrb r2, [r1]` at 0x08057748, then a re-read for the compare at 0x0805774C;
- phase 200, `bldy_lo--`: a dead `ldrb r1, [r2]` at 0x08057A3A, then a re-read at 0x08057A3E.

Every non-volatile spelling of these byte members loses the dead loads (the kit #90 / #99 evidence), so the header
cannot be dropped.

### Why no other spelling exists: one pool word through r7

Phase 200 loads `0x03000940` once, `ldr r7, [pc, #0xcc]` at 0x08057A30 from pool word 0x08057B00, and the same r7
serves both uses: as the base of the volatile member `bldy_lo` (`adds r2, r7, #0; adds r2, #0x4e` at
0x08057A32-0x08057A34, then `ldrb`/`subs`/dead `ldrb`/`strb`/`ldrb` at 0x08057A36-0x08057A3E), and as the copy
destination (`adds r0, r7, #0` at 0x08057AC0). The pool at 0x08057B00-0x08057B2C holds 0x03000940 exactly once.
agbcc shares a pool word, and CSE shares a register, only for the same `symbol_ref`. A second name for the block
(for example a plain `u8 data_03000940[0x50]`) or a numeric `(void *)0x03000940` for the copy would add a second
pool word and a second load. So the copy must name `g_control_flags_03000940` itself, and the allowlist forbids
exactly that; `&g_control_flags_03000940.display` is refused by the same `no & may precede` rule. Phase 1 (pool
0x080576C0) has only the copy use, but the developer would have spelled both copies the same way.

## Source notes

- **The indirect copier call** (phases 1 and 200; ROM 0x08057690 and 0x08057AB8). The explicit-thunk form, as
  `src/0809185C.c` and `src/0813F604.c` write it (`func_08142250(dst, src, 0x50, data_0836D4BC[0])`), was compiled
  first. It has the same size but is not instruction-identical: phases 1 and 200 load `data_0836D4BC` after the
  destination address, not before; phases 200, 220 and 255 get different reload registers (the `[sp, #0x1c]` reload
  is r1 instead of r3 in phase 200 and r3 instead of r2 in phase 220; the pool constant is r2 instead of r1 in phase
  220 and r1 instead of r3 in phase 255); and as a result jump2's cross-jumping picks different tails (phase 21's
  `*state = 100` keeps its own `ldr r2, [sp, #0x1c]; strb` where the ROM jumps to the shared tail at 0x08057B52, and
  phase 120's `*state = 140` is merged away where the ROM keeps its own copy at 0x080578AA-0x080578AE). The indirect
  call `data_0836D4BC[0](dst, src, sizeof(...))`, which agbcc emits through `_call_via_r3`, is identical: agbcc's
  `expand_call` expands the function address before the arguments, exactly the ROM's `ldr r2, =data_0836D4BC` ahead
  of the destination, and the register and cross-jump differences disappear with it. Many merged siblings write
  `data_0836D4BC[0](...)` this way (`src/0802C72C.c`, `src/080C62CC.c`, `src/08012014.c` and others). A
  `copy = data_0836D4BC;` local (the 0813F604 style) was not tried, because the plain indirect call already matches.
- **Three identical `func_08001F34(data_0839380E, panel_x * 8, 136, 0, 0, 0, 0, 0, (coarse - 1) * 12, 0, 0)` calls**
  in phases 101, 120 and 140. Each phase sets up its own arguments in the ROM, with a different zero register (r6 at
  0x0805782A, r4 at 0x080578F6, sl at 0x080579DE); only the last two instructions and the `bl`
  (0x08057A00-0x08057A04) are shared, by cross-jumping. A copy-pasted draw call is the natural reading; nothing else
  is shared, so no macro is needed.
- **`(s8)panel_x` passed to `func_0802B4A8`** in phases 101 and 140. The same plain cast gives `ldrb; lsls #24;
  asrs #24` in phase 101 (0x080577D4-0x080577D8, 0x080577F4-0x080577F8) and `movs r1, #0; ldrsb` in phase 140
  (0x0805798E-0x08057990, 0x080579AC-0x080579AE) by itself; nothing was steered. The cast exists because
  `func_0802B4A8` reads its x as `(s8)x`, as its merged callers 0806F33C and 0806F050 pass signed panel coordinates;
  the u8 type of `panel_x` follows its unsigned compares (`cmp #0x14; bhi` at 0x0805780E, `cmp #0x1f; bls` at
  0x080579C8).
- **`*state = 140; break;` nested inside phase 120's timer branch** (0x080578AA-0x080578B0, a direct jump to the
  epilogue that skips the draw) is the plain control flow the ROM shows.
- **The loop in phase 0**: `u8 i`, `for (i = 0; i < 24; i++)` with `field_04 == 2 || field_04 == 15` and a `break`;
  the ROM has `lsls #24; lsrs #24; cmp #0x17; bls` at 0x08057650-0x08057658 and one load compared twice.
- **Declaration order** does not matter: the only local is `u8 i`.
- **Types and names.** The struct offsets come from the instructions.
  - `MenuUnitRecord` and `MenuUnitTable` (24 records of 0x108 bytes at `g_state_02000000 + 0x80`; `coarse` and
    `fine` at 0x2FBA/0x2FBB) follow `src/08057E98.c` and `src/08057C88.c`, including the names `field_F0`,
    `field_102` and `field_103`. `field_04` (a byte compared with 2 and 15 at 0x08057630-0x08057634) and `field_28`
    (u16; `&= ~0x10` and `&= ~0x08` with the masks 0xFFEF and 0xFFF7 from the pool, 0x08057A9C-0x08057AA2 and
    0x08057AB0-0x08057AB6) are added in the same `field_XX` style.
  - `text_state` at 0x19C8 follows `src/08057388.c`.
  - `InputState` (`held`, `pressed`, `repeated`) follows `src/08057298.c`; the ROM tests `pressed & 1` at 0x08057B46.
  - `TileGrid` is the layout `func_0802B4A8` and `func_0802B2E8` define; `func_0802B4A8`'s prototype copies its
    definition (`const u16 *source`) with the callers' `s32 x, s32 y`.
  - The array types follow their fillers' definitions: `back_tiles` (0x2D5E) is `u16[20]` because
    `func_080586E0(u16 *)` fills it, and `front_tiles` (0x2D86) is `s16[20]` because `func_0805868C(s16 *, u16)`
    fills it. So one of the two `func_0802B4A8` calls passes an `s16 *` to `const u16 *`, a signedness mismatch agbcc
    does not warn about; making both arrays u16 compiles the same.
  - `window` (0xCD4, the object `func_0802B548` / `53C` / `554` read and write at +0x797 / +0x79A), `runner`
    (`Table` at 0x1478), `panel_x` (0x2DAE), `saved_control` (0x2DB4, 0x50 bytes), `unit_index` (u16 at 0x2E04),
    `timer` (0x2E06) and `blend_lines` (`u16[160]` at 0x2E60, which `func_08057B90` fills and DMAs to 0x04000050)
    are new names, each for the one role the ROM shows.
  - `0x06009CE0` is a VRAM tile address written as a number, as merged sources write VRAM.
  - The `func_08055F10` literal is passed as `(u32)func_08055F10`, the `Table` prototype's type in `ffta.h`, as
    `src/0805873C.c` does.
- **No original bug** is reproduced: the loop leaves `unit_index` unchanged when no record qualifies (the context is
  cleared on allocation), and the `field_F0` decrement is guarded.

## Attempt record

The explicit-thunk form was compiled first and differs as described above; the indirect call is identical; renames
only (member and type names, `InputState`) stay identical and give the parked source.

## Kit issue

The kit #375 comment reports this function as a further example of the class: unlike #224 and the 0x08125A5C example
there, the restore is a whole-block copy into the symbol (the symbol is the copy's destination, so the copy writes
every member, volatile ones included, without naming them), and both copies go through the copier table
`data_0836D4BC` called through `_call_via_r3`, not through `memcpy` / `func_081443FC`. For the typed-copy proposal
this means the copy rule needs the symbol-as-destination direction too (the permutation check has to treat the copy
as a store to each member at its own offset), and the copy helper has to be admitted as an indirect call through a
table of function pointers bound by the thunk profile, not only as a direct `memcpy` / `func_081443FC` call.

kit issue: shubshub/fftadecomp-kit#375 (comment)
