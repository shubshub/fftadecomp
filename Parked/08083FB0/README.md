# 0x08083FB0 - menu record phase handler: bytes identical, refused (owner guarded-switch selectors do not accept a two-word interposed pool) (1540 bytes)

Attempt 2026-11-20, kit b141ba59, decomp main 82b7baab5e.
`u8 func_08083FB0(s32 index)` runs one phase of the menu record `data_03002818->records[index]`: a guarded word
switch on the record's phase byte (13 entries). Cases 0 and 4 copy the record's configured values
(`inlined_08085450`); case 2 opens the record's window (`inlined_080853A0`); case 4 also clears the list window
(a CpuSet fill through `func_0814186C` from a stack halfword) and redraws its rows; cases 8 and 9 close the window
and set the phase to 0xFF; the other cases update the list and step the phase.

## The index

The index row is `08083FB0 080845B4 1540 756 return`. The extent is right: the start is word aligned and the epilogue
(`add sp, #0x2c`, pop r8-sl, pop r4-r7, `pop {r1}; bx r1`) fits the prologue. The instruction column is not the
reachable count: the kit's `analyze.refine_function` closes the CFG with 593 reachable instructions, and only with
its `two_constant_word_switch` opt-in. Not corrected here: no draft needs it.

## Byte identity

`08083FB0.c` (SHA-256 `0827e86c1e177887fe302622b4cade0d5101d726f024a4339ab9aac2f4c4a169`) was compiled with the
fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`)
and linked by hand at 0x08083FB0, with every callee and data symbol bound to its ROM address (24 `R_ARM_THM_CALL`,
29 `R_ARM_ABS32`, including the table pointer and the 13 table words). The 1540-byte symbol equals the ROM span
`[0x08083FB0, 0x080845B4)`: SHA-256 `93c15f27d5abc84fa268cd8c207d28d75c7d3294511b0e6067b7f1f67096cbf1` for both.
`.text` is exactly 1540 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict`
exits 0.

## Data symbols

None needed: every literal resolves to an existing name (`data_03002818`, `data_030009E0`, `data_03000000`,
`data_02003CB0`, `data_03000990`, `data_03000E80`).

## Refusals

Kit b141ba59, `match.py --root . --no-write` with this source copied to `src/08083FB0.c`. None matched.

| Selector | Refusal | Raised at |
| --- | --- | --- |
| default | `switch requires one exact adjacent unsigned guard and five-op dispatch` | `match.py:2528`. `switch_layout` uses the fixed pool, `pool_words = interposed_words + object_words_before_table` (`match.py:2452`); the u16 scalar breaks the run of object words before the pointer. |
| `--switch-data-profile u16-scalars-frame-v1` | `stack aliases cannot cross calls in caller-clobbered registers` | `match.py:5006`. This route accepts the dispatch-identified pool, but its frame proof has no buffer proof and admits no stack address in a register, for example r0 = sp+0x20 at the CpuSet call 0x080841EC. |
| `--owner-runtime-profile bounded-buffer-guarded-switch-v1` | `structural inventory is not closed` | `owner_graph_profile.py:26`, via `owner_admission_profile.py:492/497`. `owner_admission_profile.refine` (`:450-453`) calls `analyze.refine_function` without `two_constant_word_switch=True`, so the refinement reports `unresolved jump at 0x08083FE2`. |
| `--owner-runtime-profile bounded-buffer-root-guarded-switch-v1` | `structural inventory is not closed` | The same place. Behind it, `RootGuardedSwitchBufferProof.bind_root` (`named_data_buffer_profile.py:333`) refines again with `owner.refine` (`:339`) and lays the switch out with the fixed-pool `match.switch_layout` (`:344`), and `verify_leaf_instructions` is called without `switch_interposed_pool` (`owner_admission_profile.py:709-713`). |
| `--owner-runtime-profile bios-word-switch-local-buffers-v1` | `structural inventory is not closed` | The same place. `bios_word_switch_buffer_profile.refine` (`:23-27`) passes only `one_object_word_switch=True`, and `owner_graph_profile.py:57` accepts exactly one interposed object word. |
| `--switch-profile two-constants-frame-v1` | `unsupported compiler assembly statement: '.word\tdata_03002818'` | `switch_placement.py:73`. The two-constant profiles exclude object words and stack-address materialization by design. |

Cross-check: `analyze.refine_function` on these bytes closes the CFG (`cfg_closed: True`, one switch with
`interposed_words: 2`) only with `two_constant_word_switch=True`; every other opt-in leaves `unresolved jump at
0x08083FE2`. `GuardedSwitchBufferProof.inspect` (`named_data_buffer_profile.py:758-790`) already passes that flag, but
only for a switch inside a walked callee. The kit needs to accept the two-word pool at owner level; the source should
not be steered around it.

## Cause

- A guarded word switch on the record's phase byte (`cmp r0, #0xC; bls; b default` at 0x08083FD4..0x08083FD8). The
  five-op dispatch is at 0x08083FDA..0x08083FE2, followed by a 13-entry table at 0x08083FF0.
- Two words sit between the dispatch and the table-pointer literal at 0x08083FEC: 0x08083FE4 `data_03002818`, a typed
  object word, and 0x08083FE8 `0x00002CBA`, a u16 scalar.
- A fixed restoring frame: push r4-r7/lr and r8-sl, then `sub sp, #0x2c`. Outgoing arguments 5-12 of
  `func_08017424` go to sp+0..sp+0x1C.
- Stack addresses in registers: a 12-byte descriptor copied to sp+0x20 with `add r1, sp, #0x20; ldm r0!, {r3, r4, r7};
  stm r1!, {r3, r4, r7}` (0x080840C6..0x080840CC), then read back through `add r0, sp, #0x20` with `ldrb`/`ldrh`
  (0x080840EC..0x0808412C); and the halfword fill source at sp+0x20, held in r8 (0x080841D2) and passed in r0
  (`add r0, sp, #0x20`, 0x080841E4) to the CpuSet wrapper `func_0814186C` with control `0x01000000 | width` (bit 24
  fill, halfword units) at 0x080841EC.

## Source notes

- **`RECORD_CURSOR(index)->row`** is the macro of the merged `src/08081DEC.c`, with the same comment. The ROM forms
  the cursor's address (record + 0x98, literal `0x2D20`) at each of its three row reads and loads the row from it at
  +0x11 (0x08084224, 0x0808427C, 0x080842C8). The plain `menu.cursor.row` folds the +0x11 into the literal (0x2D31):
  3 `ldrb` differ, 2 `adds` swap operands and case 3 swaps registers (10 lines differ). It stands on the precedent.
- **Inline helpers.** `inlined_080853A0`, `inlined_0808537C` and `inlined_08085450` are the verbatim text of the
  merged ROM functions `src/080853A0.c`, `src/0808537C.c` and `src/08085450.c`, each with an "An inlined copy of"
  comment.
  - Case 2 calls `inlined_080853A0` with `x = 0xFF`, so its `if (x != 0xFF)` folds away. Its `enabled = 1` is the
    constant the ROM holds in ip from 0x080840D8 (`movs r3, #1; mov ip, r3`).
  - Cases 4, 6 and 7 call `inlined_0808537C` with `enabled = 1`, so its test folds away.
  - Cases 0 and 4 call `inlined_08085450`. Its copy loop keeps `entries` and `values` in registers while it reloads
    `count` every pass, exactly as in the ROM function.
  - `fill16` and `clear_window` are the static-inline text of the merged `src/080817F8.c`. The same loop is in its
    ROM at 0x08081818..0x08081850 and here at 0x080841C4..0x080841FE, register for register (r4 window, r5 row, r6
    buffer, r7 halved size, r8 fill address, sb 0x01000000).
  - The not-yet-published 0x08081FB0 candidate uses the same helper set.
- **Deferred-inline placement (period evidence).** The out-of-line copies of these helpers sit at 0x0808537C,
  0x080853A0 and 0x08085450, after 0x08084DA0, the last large function of the module, among its small trailing
  functions (0x08085484, 0x08085518, 0x08085558). Inside this module they are inlined, here and in 08081FB0. Other
  modules call the out-of-line copies with `bl`: `func_0808537C` at 0x080423A4, 0x080411F6, 0x080425CC and
  0x08040600; `func_08085450` at 0x0804222E, 0x08040FCA, 0x0804245E and 0x0804040E. In gcc 2.95's
  `rest_of_compilation`, only a `static inline` function whose address is not taken is deferred, and it is written at
  the end of the unit only if something still references it; a public `inline` function is written where it is
  defined; a GNU `extern inline` body is used for inlining only and never written. Since other modules call these
  copies, they are public, so the layout fits two arrangements and the ROM alone does not decide between them: a
  header `extern inline` body that this module inlines, with one public definition at the end of the module's file;
  or a separate helper unit that follows this module. Both share the point that matters here: the helpers were inline
  bodies visible to this module in the original, which is why their text is inlined here and kept as shared text with
  the merged sources, rather than invented to fit.
- **The `values` / `configuration` locals before `inlined_08085450` (cases 0 and 4) change the bytes.** In the ROM
  both addresses are formed first (`0x2D4C`, then `0x2CD0`), then the configuration is loaded, then the values pointer
  (0x08084038..0x08084046, 0x0808417A..0x08084188). Passing the two fields directly as arguments gives 53 differing
  lines: the registers of both copy loops are reassigned. The 08081FB0 candidate needs the same two locals in the same
  order for its own copy of this block (0x0808201C..0x0808202E). Naming arguments before a call is an ordinary idiom,
  but a reviewer should confirm it.
- **Case order 0, 2, 4, 3, 6, 7, 8, 9, 10, 11, 12.** Case 4's body (0x08084168) comes before case 3's (0x080842A4) in
  the ROM, and agbcc lays out case bodies in source order. Commented in the source. Case 4 ends in the shared tail of
  case 7 (0x080843A2: two `func_080812E8` calls, then phase 6), which the compiler produced by cross-jumping.
- **`case 12: break;`.** The guard compares with `#0xC` (0x08083FD4), so the table has 13 entries. Entry 12
  (0x08084020) goes straight to the return at 0x08084570, as do entries 1 and 5. Commented in the source.
- **Case 8 falls through into case 9.** The `strb` of phase 9 at 0x0808443E runs on into case 9 at 0x08084440.
  Commented.
- **`func_0808389C` returns `s32` here.** Its own source (`src/0808389C.c`) returns `u16`, but the ROM tests the result
  as a full word (`cmp r0, #0` right after the `bl` at 0x080842AC). Declaring it `u16` adds `lsls r0, r0, #0x10`, and
  the function grows to 1544 bytes. Commented at the declaration. The original was most likely called through a
  different declaration in this file, or with none.
- **The `object` local in case 3** is loaded before the `func_08017B68` call (0x080842FE `ldr r4, [r0]`), as in the
  merged `src/08085518.c`.
- **Types** follow the ROM: `u16 count` (narrowed after `func_08017B50`, 0x0808423A) and `s32 row` (signed
  `cmp`/`blt`), as in `src/0808389C.c`; a `u8` return; `s32 index`.
- **Names.** Struct members with no evidence are `unknown_*`. Used fields with no known meaning are `field_XX`:
  `field_42A`, `field_438`, `field_43A`, `field_43B`, `field_95D`, `field_C0C`, `field_1D04` and
  `Object08083FB0.entries[].field_10`. `delay` (0x42B) and `selection` (0x36) follow `src/080846B0.c`.
- **The declaration order of locals:** nothing depends on it.
- No original bug is reproduced.

## Attempt record

1. The first draft, without `RECORD_CURSOR`: 10 lines differ (the cursor-row reads and the case 3 registers).
2. With `RECORD_CURSOR`: identical apart from relocations; the parked source.
3. Plain arguments instead of the `values` / `configuration` locals: 53 lines differ.
4. `func_0808389C` declared `u16`: one extra `lsls`, 1544 bytes.

kit issue to be filed: owner guarded-switch selectors and interposed pool words
kit issue: shubshub/fftadecomp-kit#349 (an owner with its own guarded jump table passing a local buffer to a callee; here the pool also has two interposed words)
kit issue: shubshub/fftadecomp-kit#74 (switches combined with named data or local buffers)
