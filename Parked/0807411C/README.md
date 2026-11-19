# 0x0807411C - unit status panel task: bytes identical, refused (a switch pool with one interposed object word beside local and non-local CpuSet calls) (1648 bytes)

Attempt 2026-11-20, kit b141ba59, decomp main 82b7baab5e.
`void func_0807411C(u8 index, u8 *phase)` is a task callback that `func_08070414` registers in slot 4 of the task table at
`data_03002730`. It drives the unit status panel in window 2 (`data_030009E0[2]`). Phase 0 initialises the panel and
moves to phase 1. In phase 1 a nine-state machine on `data_03002818->mode` (+0x450) runs:

- states 2, 3 and 6 slide the window: its `x` moves by +2, -1 or +4 per frame, `offset_x = x * 8`, and both palette
  buffers are copied to `data_03003860` each step;
- states 0 and 1 detect a change of the selected unit;
- state 7 starts the slide out;
- state 5 redraws the unit's name and seven numbers, places the panel at the top or bottom of the screen from the
  unit's on-screen y, loads the unit portrait graphics and palette, and enters state 6.

A shared tail then syncs two flag pairs at +0x98B and, for window 4, redraws a 30-tile header row from one of two ROM
tile rows.

## The index

The index row is `0807411C 0807478C 1648 824 return`. The extent is right: the start is word aligned, and the
epilogue (`add sp, #8; pop {r3}; mov r8, r3; pop {r4-r7}; pop {r0}; bx r0`) fits the prologue
(`push {r4-r7, lr}; mov r7, r8; push {r7}; sub sp, #8`). The instruction column is the halfword count (bytes/2): the
kit's `analyze.refine_function` closes the CFG with 641 reachable instructions, and only with its
`one_object_word_switch` opt-in. Not corrected here: no draft needs it.

## Byte identity

`0807411C.c` (SHA-256 `3ce18579a43b094d0743c7ecdb8c1ad771c0effaa15ceed90d4523a3db7a0df4`) was compiled with the
fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`)
and linked by hand at 0x0807411C, with every callee and data symbol bound to its ROM address (37 `R_ARM_THM_CALL`,
41 `R_ARM_ABS32`, including the nine-word jump table at 0x08074180). The 1648-byte symbol equals the ROM span
`[0x0807411C, 0x0807478C)`: SHA-256 `be39ceb438652750769a91d84d87d2a03cf676469db5ec1e09e7b9a846d89c14` for both.
`.text` is exactly 1648 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict`
exits 0.

## Data symbols

Two are needed; neither is in `config/data_symbols.json`.

| Symbol | Evidence |
|---|---|
| `data_0894FF88` | A `const u16[30]` ROM tile row of palette-7 entries (`700B 700C ... 7019 701A 741A`). Pool references at 0x08074758 (this function: the source of `func_08035578(src, window4->second_plane, 30, 0x15B)` when flag bit 5 is set) and 0x080748D8 (a neighbouring function). |
| `data_0894FFC4` | The next `const u16[30]` row, directly after the first (0x0894FF88 + 0x3C). It differs only in its last two entries (`741B 701B`). Pool references at 0x08074788 (this function, the else arm) and 0x080748FC. |

Precedent: `data_0894FF54`, the 26-halfword row just before these, is already named and is passed to `func_08035578`
the same way in `src/080870A8.c`. Without the two symbols the default run refuses first with
`data target must be an undefined mapped object`.

## Refusals

Kit b141ba59, `match.py --root . --no-write` with this source copied to `src/0807411C.c` and the two data symbols
added. None matched.

| Selector | Refusal |
|---|---|
| default | `stack aliases cannot cross calls in caller-clobbered registers` (the frame walk with no buffer proof, at the CpuSet call 0x0807440A with the local fill source in r0) |
| `--owner-runtime-profile bios-word-switch-local-buffers-v1` | `every CpuSet site requires an actual checked local fill source` (`bios_word_switch_buffer_profile.root_manifest`); the switch, frame, alias walk and data bindings get that far |
| `--owner-runtime-profile bounded-buffer-guarded-switch-v1` | `structural inventory is not closed` (`owner_graph_profile.graph`) |
| `--owner-runtime-profile bounded-buffer-root-guarded-switch-v1` | `structural inventory is not closed` |
| `--switch-data-profile u16-scalars-frame-v1` | `stack aliases cannot cross calls in caller-clobbered registers`, at the same CpuSet call 0x0807440A: the frame path has no buffer proof, so the stack address formed by `add r1, sp, #4` at 0x080743FC cannot reach the call in r0 |
| `--addressed-signed-runtime-profile addressed-native-bios-fill-buffer-data-v1` | `addressed ABS32 requires an aligned unique undefined global with its exact type`; the jump-table words relocate against `.text`, not against an undefined global |

## Cause

- **A jump table with one interposed object word.** The guard `cmp r0, #8; bls; b default` is at 0x08074168 and the
  dispatch (`lsls; ldr; adds; ldr; mov pc, r0`) at 0x0807416E-0x08074176. Between the dispatch and the table-pointer
  literal (0x0807417C) sits one reached object word at 0x08074178, `data_03002818`; the nine-word table at
  0x08074180 follows. `analyze.refine_function` closes this CFG only with `one_object_word_switch=True` (641 reached
  instructions, one switch with `interposed_words: 1`). The owner-admission refinement that the guarded-switch
  selectors use passes no switch-layout opt-in, so their inventory is not closed.
- **A fixed frame** `sub sp, #8` with the fifth outgoing argument of `func_08015110` at `[sp]` (`str r1, [sp]` at
  0x08074416).
- **One local CpuSet fill.** A `u16` at sp+4 is zeroed and passed in r0 to `func_0814186C` with control 0x01000180
  (bit 24 fill, halfword units, count 0x180), at 0x080743FC-0x0807440A.
- **Seven CpuSet calls with no local pointer:** six palette copies with control 0x04000080 (bit 26 word units, count
  0x80) at 0x080741C0, 0x080741D6, 0x0807426E, 0x08074284, 0x08074328 and 0x0807433E, and one graphics copy at
  0x080745DA (`data_02003CB0` to `data_06014300`).
- **Named data:** `data_03002818`, `data_030009E0`, `g_state_02000000`, `data_02003CB0`, `data_03003860`,
  `data_0600AEE0`, `data_06014300`, `data_0894FF88` and `data_0894FFC4`.

The closest selector is `bios-word-switch-local-buffers-v1`, which already gets through the switch, the frame and the
alias walk. The same interposed-pool family of gaps stops 0x08083FB0, published alongside (two interposed words).

### Diagnostic relaxations: evidence, not fixes

Measured on a throwaway copy of the kit's `tools/` (not re-run for this entry; nothing in the kit was changed). With
both changes, `--owner-runtime-profile bios-word-switch-local-buffers-v1` printed `verdict MATCH - byte identical`.
They show where the refusals sit; they are not proposed as the fix.

1. **CpuSet site-set equality.** `bios_word_switch_buffer_profile.root_manifest` requires the set of sites with a
   checked local fill observation to equal the set of every CpuSet call site in the owner. Here one site has a local
   fill source, and seven carry no local pointer at all. The diagnostic changed `!=` to "not a subset". The plain
   buffer walk's BIOS summary already treats a wrapper call with no live local pointer as an ordinary ABI call; a
   real fix would more likely require equality over the sites that carry a local pointer in R0-R3 and keep the
   others as ordinary returning calls.
2. **Numeric hardware words.** After change 1, `owner_admission_profile.verify` refused with
   `owner address literals require exact typed object/function coverage`. The uncovered words are the three pool
   words 0x04000080 at 0x080741F0, 0x080742A8 and 0x08074358: CpuSet copy controls (bit 26 plus count 0x80, no bit
   24) that fall in the hardware address window. `bios-word-switch-local-buffers-v1` is not in
   `NUMERIC_HARDWARE_SELECTORS`, so these words are never classified as numbers; the diagnostic added the selector to
   that tuple. Sibling `0807478C` ships the same 0x04000080 words under `elf-symbol-thumb-data-v1`.

## Source notes

1. **Case order 2, 3, 0, 1, 6, 7, 5 in the inner switch.** The ROM lays the case bodies out in that order:
   0x080741A4 (2), 0x08074228 (3), 0x080742AC (0), 0x080742DC (1), 0x08074308 (6), 0x08074398 (7), 0x080743E0 (5).
   agbcc emits case bodies in source order, so the source lists them in that order; the comment above the switch
   cites the range.
2. **`case 8: break;` in the inner switch**: see "For the reviewer".
3. **`case 0xFF: break;` in the outer switch**: see "For the reviewer".
4. **`u16 clear; u16 *fill = &clear; *fill = 0; func_0814186C(fill, data_0600AEE0, 0x01000180);`** The ROM forms the
   address first (`add r1, sp, #4` at 0x080743FC), then `movs r0, #0; strh r0, [r1]`, and passes the same register
   to the call (`adds r0, r1, #0` at 0x08074406). Plain `clear = 0; func_0814186C(&clear, ...)` and
   `u16 clear = 0;` both compile to `movs r1, #0; add r0, sp, #4; strh r1, [r0]` with no copy, so two instructions
   differ and one is missing. Declaring the pointer with its initialiser or assigning it as a statement gives the
   same bytes. The parked form is the text of the merged sibling `src/08035A68.c`
   (`u16 clear; u16 *fill = &clear; ... *fill = 0; func_0814186C(fill, dst, ...)`); the reviewer should confirm
   whether that sibling's idiom is enough to ship the pointer.
5. **One `u32 value` local** for the seven numbers drawn and for the graphics size returned by `func_080CB808`. In
   the ROM, r5 holds every drawn value (loaded at 0x08074430, 0x08074456, 0x08074476, 0x0807449A, 0x080744B8,
   0x080744DC and 0x080744F8) and the size (0x080745C4); the size feeds `lsls r2, r5, #0xa; lsrs r2, r2, #0xb`
   directly at 0x080745D4. With a separate `u32 size` local, the unit-record base moves from r4 to r5 and the drawn
   values from r5 to r4 (about 20 lines differ). One local reused for unrelated values is a period idiom.
   `func_080CB808` is declared here as returning `u32`: it returns `func_0800588C(...)`, which reads a big-endian u32
   header (`src/0800588C.c` returns `u32`); `src/0807478C.c` declares it `const u8 *` and spells the control
   `((u32)resource << 10) >> 11`. The CpuSet count is written `(value / 2) & 0x1FFFFF`, the SDK CpuCopy16 form; with
   an unsigned `value` it compiles to the same `lsls #10; lsrs #11`, with a signed one it would not.
6. **`g_state_02000000.units[shown].field` written at each use**, with no unit pointer. The ROM keeps the base
   0x02000000 + shown * 0x108 in r4 (0x0807442A) and adds 0x98, 0x9A, 0x9C, 0x9E, 0x156, 0x89 and 0x8A: the +0x80 of
   `units[]` is folded into each field offset. A `Unit *unit = &g_state_02000000.units[shown]` pointer loads
   0x02000080 and uses `ldrh r4, [r5, #0x18]`. This follows `src/08071DC8.c` and `src/080725B8.c`
   (`unknown_00[0x80]` then `units[24]`), whose field names are kept (`level` at 0x09, `first` at 0x1A, `second` at
   0x1E, `value` at 0xD6). The fields at 0x18 and 0x1C are drawn beside them with a grey palette when zero, so they
   are named `current_first` and `current_second`.
7. **`if (data_03002818->flag_2)`** as a plain bit-field test gives the ROM's `movs r0, #4; ands r0, r1;
   lsls r0, r0, #0x18; lsrs r0, r0, #0x18; cmp r0, #0` at 0x080746DE; a `u8 lower = data_03002818->flag_2;` local
   gives `lsls #0x1d; lsrs #0x1f` instead.
8. **Window `x` (+0x34) and `top` (+0x31) are `s8`.** `x` is read with `ldrsb` at 0x080741AC, 0x08074230,
   0x08074292, 0x08074310 and 0x080743B4; `top` with `ldrb; lsls #0x18; asrs #0x18` at 0x0807461C-0x08074620. The
   rectangle at +0x30..+0x33 is `s8` in `src/0808A830.c`. `bottom` (+0x33) and `y` (+0x35) are only stored and are
   declared `s8` with them.
9. **The palette-copy pair is written inline three times**, in cases 2, 3 and 6, with the same
   `(u8 *)data_03002818 + 0x28` / `+ 0x228` text as `src/0807478C.c`. The ROM repeats the pair at 0x080741B2,
   0x08074260 and 0x0807431A, and once more in 0807478C. A statement macro would also be byte-identical; it is not
   used, to keep the merged sibling's text.
10. **The name fetch comes before the fill.** `const u8 *name = (const u8 *)func_080C7EA4(data_03002818->unit_1D0C,
    0);` is a local because the ROM calls `func_080C7EA4` (0x080743F6) before the fill and keeps the result in r5
    until `func_08015110`. The cast follows `src/08128968.c` and `src/0802C8C4.c`.
11. **The screen-position test is `target_y - camera_position + 44 > 94`.** The ROM computes `subs; adds #0x2c;
    cmp #0x5e; ble` at 0x08074522-0x08074528 with signed halfword loads, which this spelling gives.

No original bug is reproduced.

## For the reviewer: the two empty case labels

A case label ships when the ROM shows the table word or compare it creates. Each label below is accounted for by
specific ROM words and compares.

### `case 8: break;` (inner switch on `mode`)

- The guard at 0x08074168 is `cmp r0, #8; bls`, and the table at 0x08074180 has nine words (indices 0-8). agbcc sizes
  the guard and the table from the smallest and largest case values, so the largest case value is 8. With no
  `case 8` the largest value is 7: the guard becomes `cmp r0, #7` and the table has eight words (compiled: the first
  draft gave exactly that).
- Table word 8 (0x080741A0) holds 0x08074634, the shared tail after the switch: the address an empty
  `case 8: break;` jumps to, and also the default.
- Table word 4 (0x08074190) also holds 0x08074634. agbcc fills every index that has no case label with the default
  label, which is the same tail, and a `case 4: break;` would produce exactly the same word. The ROM therefore cannot
  tell whether case 4 was written, and it is left out: no ROM word or compare requires it.

### `case 0xFF: break;` (outer switch on `*phase`)

- The outer dispatch at 0x08074126-0x08074136 is
  `ldrb r2, [r3]; cmp r2, #1; beq case1; cmp r2, #1; ble L; b end; L: cmp r2, #0; beq case0; b end`.
- That is agbcc's balanced decision tree with root value 1, a left subtree {0}, and a right branch (values > 1) to
  `end`. The `ble L; b end` pair is the inverted long form of `bgt end`; `end` (0x0807477A) is beyond Thumb's
  conditional branch range.
- agbcc's `balance_case_nodes` splits a list only when it has three or more nodes; with exactly two case values (0
  and 1) it emits a linear chain (compiled: the first draft gave `cmp r2, #0; beq; cmp r2, #1; beq; b end`).
- The shape is accounted for by a third case value greater than 1 whose body is the shared exit. Jump optimisation
  then merges that case's test (`cmp r2, #X; beq end; b end`) into the single `b end` of the right branch.
- Any value greater than 1 gives identical bytes, so the ROM does not fix the value. 0xFF follows the empty
  `case 0xFF: break;` in the merged task-phase callbacks `src/0803D820.c` and `src/0803DC1C.c`.

## Attempt record

1. The first draft differed in 74 lines: the outer switch was a linear chain; the table had eight words (no case 8);
   the unit base was taken through a pointer (pool 0x02000080); the fill's constant and address order was swapped;
   and a separate `resource` local swapped registers at the size.
2. Adding `case 0xFF`, `case 8`, `units[shown]` at each use and one `value` local reused for the size left only the
   fill order (3 instructions).
3. The `fill` pointer made it identical apart from the unrelocated table words; linked, all 1648 bytes are identical.

Rejected variants: `u16 clear = 0;` and plain `clear = 0` for the fill; a separate `u32 size` local; a u8 local
holding the bit-field. Variants that keep identical bytes: `fill` assigned as a statement instead of initialised; the
bit-field test written directly instead of through a byte mask.

kit issue to be filed: owner guarded-switch selectors and interposed pool words
