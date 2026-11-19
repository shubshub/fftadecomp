# 0x080461D4 - mission talent panel: bytes identical, refused (a stack text buffer passed to the number-to-text helper func_080142DC) (1664 bytes)

Attempt 2026-11-20, kit b141ba59, decomp main 82b7baab5e.
`void func_080461D4(Item080461D4 *item, u16 flags)` draws a mission's talent panel into the text tiles at
`data_0600AFE0` (window 5):

- the header `data_085668B0[12]`;
- the row's byte `gains[0]` (`g_table_0855AE4C[item->id]` + 0x2A) as 1, 2 or 3 digits, then `data_085668B0[13]` and
  `[40]`;
- the clan slot 0 level (`g_state_02000000` + 0x21B4) as 1 or 2 digits, in palette 11 when `flags & 1` is set and
  palette 12 otherwise, then `data_085668B0[14]`;
- eight talent rows, icons 0x14..0x1B. Each row draws the slot's level (`slots[i][0]`) when `flags & 0x8000` is
  clear, with palette 11 or 12 from `flags & (1 << i)`; when that bit is set, each row draws the slot's experience
  (`slots[i][1]`) in palette 12.

Every number is formatted by `func_080142DC` into a local `u8 text[32]` at sp+8. The callers are `bl` sites at
0x080494A8, 0x08049658 and 0x08049840, inside the oversized index row 08046A4C..08049C20.

## The index

The index row `080461D4 08046854 1664 656 return` is right: the start is word aligned; `push {r4-r7, lr}` plus
`push {r8-r10}` with `sub sp, #0x2c` match `add sp, #0x2c`, `pop {r3-r5}` (restoring r8-r10), `pop {r4-r7}`,
`pop {r0}` and `bx r0` at 0x0804681E-0x0804682C; and the last literal pool (0x08046830-0x08046850) ends at the
indexed end. The kit's `analyze.refine_function` closes the CFG with 656 reachable instructions.

## Byte identity

`080461D4.c` (SHA-256 `c74bf1d0dd2a3a883ea75620382a2bf22565b59e83f576a7894f99508491c096`) was compiled with the
fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`)
and linked by hand at 0x080461D4, with every callee and data symbol bound to its ROM address (72 `R_ARM_THM_CALL`,
29 `R_ARM_ABS32`). The 1664-byte symbol equals the ROM span `[0x080461D4, 0x08046854)`: SHA-256
`f598de92302b115badf75bbf20497d62e2ad4a53911aa0b2ff10032c08dd3f0f` for both. `.text` is exactly 1664 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

None needed: every data symbol the source names is already in `config/data_symbols.json`.

## Refusals

Kit b141ba59, `match.py --root . --no-write` with this source copied to `src/080461D4.c`. None matched.

| Selector | Refusal | Raised at |
|---|---|---|
| default | `buffer callee 0x080142DC: buffer callee 0x08002FB8: signed remainder requires numeric proof or fresh addressed-call provenance` | `tools/match.py:4881` (`modsi3.AddressedRemainderRequired` at the `bl` to `__modsi3` 0x08142950 in 08002FB8), prefixed by the callee walk at `tools/match.py:3934` |
| `--owner-runtime-profile named-data-buffer-v1` | the same as default | the same |
| `--owner-runtime-profile bounded-buffer-runtime-summaries-v1` | `buffer callee 0x080142DC: buffer callee 0x08002FB8: inconsistent possible pointer offsets at control-flow join` | `tools/match.py:3126` (`merge_possible_aliases`, called from the join merge at `tools/match.py:3901`), via `RuntimeSummaryBufferProof` (`tools/runtime_summary_profile.py:287`) -> `NamedDataBufferProof._check_arguments` (`tools/named_data_buffer_profile.py:218`) -> `tools/match.py:3934` |
| `--owner-runtime-profile bounded-buffer-bios-mixed-fast-fill-runtime-summaries-v1` | `CpuFastSet fill requires only its actual direct wrapper calls` | `tools/bios_fast_fill_source_profile.py:40` (the function has no CpuFastSet call) |
| `--owner-runtime-profile conditional-known-query-stack-buffer-v1` | `private stack address or saved value passed to a call` | `tools/known_query_stack_buffer_profile.py:236` |

The runtime-summaries proof is a subclass of `NamedDataBufferProof`. Loop replay is opted into only by the class's own
`__dict__` (`tools/match.py:3480`, `tools/named_data_buffer_profile.py:201`), so the summaries proof keeps the join
refusal. Replay would not decide this loop anyway: the runtime summaries export no quotient value
(`result='unconstrained scalar in r0; no constant, range or alias exported'`), so the loop's exit branch has no known
flags.

## Cause

1. The root passes its 32-byte stack buffer `text` (`add r0, sp, #8`) to `func_080142DC(text, value, digits)` 20
   times. The digits argument is a constant 1, 2 or 3, except at 0x0804634A-0x08046352, where r2 is 1 or 2 from a
   join (`level >= 10 ? 2 : 1`).
2. `080142DC` reserves its own 8-byte frame (`sub sp, #8`). It passes that frame to `func_08002FB8(value, sp)`
   (`mov r1, sp` at 0x080142FC) and then to `strlen` at 0x081444B8, and then writes 2*n+1 bytes to the caller's
   buffer, where n = (digits & 0xFF), or 1 when that is zero.
3. `08002FB8` sets `text += 6` and writes the terminator. Its do-while loop (0x08002FCA-0x08002FF6) writes one digit
   per pass, `__modsi3(half, 5) * 2 + low + '0'`, decrements the pointer and continues while `__divsi3(half, 5)` is
   nonzero. A second loop (0x08003004-0x0800300C) then pads with spaces until a counter that started at 6 reaches -1.
   The pointer moves back a data-dependent number of times, so the walk sees two offsets for 080142DC's private
   buffer at the loop head.

The alias the verifier refuses is 080142DC's private frame buffer, not the root's `text`.

Four Parked or unshipped functions pass a stack buffer to `080142DC` and stop at the same callee: 0x080458A4,
0x0804A3CC and 0x081386BC (Parked on main) and 0x08045DF4 (not yet published).

## Source notes

1. **`u16 icon`, assigned at the start of each of the 16 talent rows.** The ROM's `movs r7, #0x14` .. `#0x1B` sits at
   the start of each row, before the slot byte is loaded and formatted (0x080463DE, 0x0804643A, 0x0804648E,
   0x080464E2, 0x08046536, 0x0804658A, 0x080465DA, 0x0804662E; and 0x08046688, 0x080466C0, 0x080466F2, 0x08046724,
   0x08046756, 0x08046788, 0x080467BA, 0x080467EC), and `r7` is stored as `func_080378C8`'s fifth argument
   (`str r7, [sp]`) two calls later. Literal fifth arguments instead give a different allocation
   (`movs r0, #0x14; str r0, [sp]` at the call, and `r7` takes `data_0600AFE0` in place of `r8`; at least 28 diff
   lines). `icon = 0x14` followed by `icon++` per row matches in the `flags & 0x8000` arm; in the other arm CSE loses
   the constant across the palette diamonds and keeps `adds; lsls; lsrs` (21 diff lines). The type follows
   `func_080378C8`'s `u16 graphic` parameter (`src/080378C8.c`); `u32 icon` is also byte-identical. This is a per-row
   variable the ROM shows, plausibly hand-written; a reviewer should confirm that it is not a spare temporary.
2. **`__attribute__((packed))` on the 0x46-byte table row.** The ROM scales the index with `movs r1, #0x46; muls`
   (0x080461F2). Without `packed`, agbcc pads the struct to a word multiple: stride 0x48 and a shift-add sequence
   (3 diff lines plus a pool pad). Merged siblings declare the same table packed: `src/080CFCD0.c`, `src/080D1E70.c`,
   `src/0803CEF8.c`, `src/08049ED0.c`.
3. **`level >= 10 ? 2 : 1` for the digits.** ROM: `movs r2, #1; ldr r3, [sp, #0x28]; cmp r3, #9; bls; movs r2, #2`
   (0x0804634A-0x08046352). `level < 10 ? 1 : 2` inverts the arms (`movs r2, #2; bhi; movs r2, #1`, 3 diff lines).
   Both are natural spellings; the ROM picks this one.
4. **Three `gain` branches (`< 10`, `< 100`, else) with copied tails.** Each branch formats, draws the number at
   x=10 (x=9 for three digits) and draws `data_085668B0[13]` at x=12. Cross-jumping merges the first two tails (the
   first branch jumps to 0x080462CC); the third keeps its own copy (0x08046318-0x08046320). Copy-paste branch bodies,
   as period code writes them.
5. **The 16 rows are written out, not wrapped in a macro.** Each `flags & 0x8000` arm has eight rows of three calls,
   copied and edited, and the ROM repeats the row instruction for instruction apart from the constants (in the
   `flags & 0x8000` arm, CSE reuses the 2, 12 and `g_state_02000000` registers). A statement macro, for example one
   taking (icon, slot, x, y), would be equally byte-identical; the plain form is kept because no merged sibling
   defines such a macro.
6. **The declaration order of locals is not load-bearing.** Declaring `text` and `icon` before `entry` gives
   identical code.
7. **An `entry` local before `level`.** The ROM computes the row address (`muls`, `adds` at 0x080461F4-0x080461F8)
   before it loads `slots[0][0]` (0x080461FA-0x08046202), and loads `gains[0]` only after that
   (0x08046204-0x08046206). This is `const Entry *entry = &g_table_0855AE4C[item->id]`, as `src/080D1E70.c` writes
   it. `level` is read before any call and spilled to sp+0x28 (`str r0, [sp, #0x28]` at 0x08046202), so it is a local
   read at the top, not an inline read at its use.
8. **Names.** `gains[16]` at +0x2A and `slots[16][2]` at 0x21B4 follow `src/08046854.c`, which adds
   `object->gains[index]` to `slots[index][1]`. Its caller stores `&g_table_0855AE4C[item->id]` to 0x0201F508
   (0x08047882-0x0804788A) and passes that word as the object (0x08049688-0x0804969C, index 1..8, mask 2..0x100):
   the same bits this function tests, so it is the same row type. `Item080461D4` (`u16 id : 10`, packed) follows
   `src/08049ED0.c`. `text_state` at +0xC4C of `*g_state_03002810` follows `src/080378C8.c`.

No original bug is reproduced.

kit issue: shubshub/fftadecomp-kit#192 (comment) (the digit loop of 08002FB8, which moves its text pointer back a data-dependent number of times)
