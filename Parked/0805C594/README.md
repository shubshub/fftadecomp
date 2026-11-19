# 0x0805C594 - two-member pick and draw phase handler: bytes identical, refused (a signed remainder runtime with call thunks and a variably indexed stack buffer) (1256 bytes)

Attempt 2026-11-20, kit b141ba59, decomp main 82b7baab5e.
`void func_0805C594(u8 index, u8 *phase)` is runner handler 1: the merged `src/0805873C.c` installs it with
`func_08006ADC(&data_0200F428->runner, 1, (u32)func_0805C594)`. It switches on `*phase`:

- `0`: allocates a 0x2038-byte state into `data_0200F42C` and clears it through `g_callbacks_0836D4B8[0]`. It sets
  the count to `rand % 2 + 1`. When no roster record is named (`func_080CCB94() == 0`) it picks members from the ROM
  table `data_0839383C`; otherwise it collects the indices of the named records among the first 20 into a local
  `u8[20]`, clamps the count to that number (at most 2) and draws distinct random members. It then fills two
  per-member bytes through `func_080CCB08` and `func_080CCB28` and sets `*phase = 1`.
- `1`: places each member from `data_0839387C` through `func_0805CF3C` and picks a random `% 4` value. It builds the
  heap and owner (`func_080070C8`, `func_08021A3C`), clears the item words, creates the objects (`func_08021B1C`,
  `func_08021BD4`, `func_08021618`, `func_08021DF8`) and sets `*phase = 2`.
- `2`: runs `func_08021E7C(owner)`. For each member the roster case refreshes `field_201A`; then it calls
  `func_0805CA7C(i)` and draws through `func_08021F18` and `func_08001F34(data_08393880, ...)`.
- `0xFF`: frees the state and calls `func_08006B8C(&data_0200F428->runner, index)`.

## The index

The index row `0805C594 0805CA7C 1256 520 return` is right. The start is word aligned and the epilogue
(`add sp, #0x38; pop {r3, r4, r5}; mov r8/sb/sl; pop {r4-r7}; pop {r0}; bx r0`) fits the prologue
(`push {r4-r7, lr}; push {r8, sb, sl}; sub sp, #0x38`). The kit's `analyze.refine_function` closes the CFG with 520
reachable instructions.

## Byte identity

`0805C594.c` (SHA-256 `05e9abf26772d692f1e50100b10cbd9273f1cca9fadedee872f5a6dedd772834`) was compiled with the
fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`)
and linked by hand at 0x0805C594, with every callee, runtime and data symbol bound to its ROM address
(27 `R_ARM_THM_CALL`, 13 `R_ARM_ABS32`; `__modsi3` -> 0x08142950, `_call_via_r2` -> 0x0814224C). The 1256-byte
symbol equals the ROM span `[0x0805C594, 0x0805CA7C)`: SHA-256
`420445faff47fc5ab508eba852421387b097307449f54da6e9ece49dbedb03ac` for both. `.text` is exactly 1256 bytes. The
padding halfwords at 0x0805C90E and 0x0805CA1A are in the same places, and the pool words carry the ROM's addends:
`g_state_02000000` + 0x2E78 is split into two literals, `g_state_02000000` + 0x2E7F is one literal. `match.py`
refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Four are needed; none is in `config/data_symbols.json`.

| Symbol | Evidence |
|---|---|
| `data_0200F42C` | Pool word 0x0200F42C, loaded at 0x0805C5C6, 0x0805C604, 0x0805C68C, 0x0805C6D2, 0x0805C72C, 0x0805C7A6, 0x0805C844, 0x0805C852, 0x0805C868, 0x0805C888, 0x0805C93C and 0x0805CA40. Case 0 stores `func_08022840(0x2038)` into it (0x0805C5D0); case 0xFF tests, frees and zeroes it (0x0805CA42-0x0805CA4E). It is the pointer to this handler's state, next to the existing `data_0200F428`. |
| `data_0839383C` | Pool word at 0x0805C680, loaded at 0x0805C620. The function reads `[base + i*8]` as a byte count (0x0805C648-0x0805C64A) and `[base + i*8 + 4]` as a pointer (0x0805C63E-0x0805C642, 0x0805C650). ROM: `07 00 00 00 30 38 39 08 04 00 00 00 37 38 39 08`, that is `{7, 0x08393830}, {4, 0x08393837}`; each pointer addresses the byte list just before the table (7 bytes, then 4). |
| `data_0839387C` | Pool word at 0x0805C91C, loaded at 0x0805C7BA. Read as `[base + i*2]` (0x0805C7CA-0x0805C7D0) and `[base + 1 + i*2]` (sl = base + 1, 0x0805C7BE-0x0805C7C2 and 0x0805C7DC-0x0805C7E0). ROM: `05 0b 00 06`, a `u8[2][2]` = `{5, 11}, {0, 6}`. |
| `data_08393880` | Pool word at 0x0805CA3C, loaded at 0x0805C9FE as the first argument of `func_08001F34`, the graphic drawn under each member. It starts directly after the 4-byte `data_0839387C` (ROM `02 00 fc 40 ...`). |

Existing symbols used: `g_state_02000000`, `data_0200F428`, `g_callbacks_0836D4B8`.

## Refusals

Kit b141ba59, `match.py --root . --no-write` with this source copied to `src/0805C594.c` and the four data symbols
added. None matched.

| Selector | Refusal |
|---|---|
| default | `signed remainder excludes mixed aliases, addressed calls with data, and other profiles; compiler signed runtime thunks: unsupported stack-alias use or escape` |
| `--addressed-signed-runtime-profile compiler-signed-runtime-thunks-data-v1` | `unsupported stack-alias use or escape` |
| `--owner-runtime-profile bounded-buffer-conditional-thunks-v1` | `function address requires a canonical addressed function` |
| `--owner-runtime-profile bounded-buffer-runtime-summaries-v1` | `runtime summary owner requires exact canonical division entries and no thunks` |
| `--owner-runtime-profile named-data-buffer-stack-index-v2` | `function address requires a canonical addressed function` |

The default run re-verifies the function under `compiler-signed-runtime-thunks-data-v1`, as the kit README
documents. The inner refusal is raised at `tools/match.py:5238` in `verify_leaf_instructions`
(`if (set(read) & aliases.keys()) - allowed_aliases and not deferred_derivation and not (bounded_index ...): raise
ValueError("unsupported stack-alias use or escape")`), called from `addressed_signed_runtime_profile.py:974`
(`verify`), `:1305` (`build`) and `:1434` (`issue`).

## Cause

The stack buffer is `u8 candidates[20]` at sp+0x1C..sp+0x2F, indexed by a variable:

- the write `candidates[found] = i`: 0x0805C6AC `mov r0, sp`; 0x0805C6AE `adds r0, r0, r7`; 0x0805C6B0
  `adds r0, #0x1c`; 0x0805C6B2 `strb r6, [r0]`;
- the read and write of `candidates[pick]`: 0x0805C6FC `mov r2, sp`; 0x0805C6FE `adds r2, r2, r0`; 0x0805C700
  `adds r2, #0x1c`; 0x0805C702 `ldrb r1, [r2]`; 0x0805C716 `strb r0, [r2]` (stores 0xFF). The index `pick` is the
  u8-narrowed `__modsi3` result (0x0805C6F4 `bl`, 0x0805C6F8-0x0805C6FA `lsls/lsrs #24`).

The refusal fires at the first `adds rX, rX, rIndex` on the SP-derived alias (0x0805C6AE). The thunks-data route
admits no SP materialization at all ("No SP materialization is admitted", kit README).

All of the following sit in one complete Thumb owner:

- compiler-emitted `__modsi3` at three sites (0x0805C64C, 0x0805C6DC, 0x0805C6F4), with s16 dividends from
  `(s16)func_08002804()` and divisors that are table bytes, `min(found, 2)` and `found`;
- compiler-emitted `_call_via_r2` at two sites (0x0805C5D8, 0x0805C876), each target loaded by a full-word `ldr`
  from `g_callbacks_0836D4B8`;
- typed named data: RAM, ROM, and a symbol plus addend (`g_state_02000000` + 0x2E7F);
- a fixed 0x38-byte frame holding seven outgoing stack-argument words (sp+0x00..0x18); the local `u8[20]` at
  sp+0x1C, indexed by a loop-bounded index (`found`) and by a runtime-result index (`pick`); the spilled `phase`
  pointer at sp+0x30 (stored at 0x0805C5A0, reloaded for `*phase = 1` at 0x0805C77E `ldr r7, [sp, #0x30]` and for
  `*phase = 2` at 0x0805C908 `ldr r2, [sp, #0x30]`); and a scalar spill at sp+0x34 (0x0805C9B8 / 0x0805C9D2);
- a compiler switch lowered as a compare tree (0, 1, 2, 0xFF).

Each selector covers part of this. `compiler-signed-runtime-thunks-data-v1` covers the runtime, the thunks and the
data, but no stack aliases. `bounded-buffer-runtime-summaries-v1` covers the runtime and the buffer, but refuses
thunks. `bounded-buffer-conditional-thunks-v1` and `named-data-buffer-stack-index-v2` cover thunks or stack indexing,
but refuse the runtime call target. Admitting this function needs a bounded-buffer (variable stack index) proof
composed with the signed-runtime and thunk route. The buffer is ROM-shown, so the source should not be reshaped to
avoid it.

## Source notes

Every alternative below was compiled with the rest of the source unchanged; "diff lines" counts instruction-level
differences against the ROM.

1. **`i = found > 2 ? 2 : found;`: the loop counter `i` holds the clamped count.** ROM, 0x0805C6C4-0x0805C6CC:
   `adds r0, r7, #0; cmp r7, #2; bls; movs r0, #2; adds r6, r0, #0`. The ternary result is built in r0 and copied
   into r6, which is `i`'s register in every case of the function. It crosses `bl func_08002804` (0x0805C6CE) and is
   passed as the divisor at 0x0805C6DA (`adds r1, r6, #0`) to `__modsi3` at 0x0805C6DC; `i = 0` follows at
   0x0805C6E8. Alternatives:
   - a separate `u8 limit` with the same ternary: 160 diff lines, whether declared first, between `i` and `found`,
     after `candidates` or in its own block; `i` moves to r7 and `found` to r8;
   - an `s32 limit` with the ternary: 29 diff lines;
   - `limit = found; if (limit > 2) limit = 2;`: 28 diff lines; `i` and `found` get the right registers, but the r0
     temporary and the copy into r6 disappear (`adds r6, r7, #0 ... movs r6, #2`);
   - the ternary written inline in the `%`: 140 diff lines; the call is expanded first, so the clamp lands after
     `bl func_08002804`, against the ROM order.

   This is the period idiom of one narrow u8 local reused for an unrelated value. The source comments the r6 range
   0x0805C6CC-0x0805C6DC.
2. **`for (i = 0, found = 0; i < 20; i++)`.** ROM: 0x0805C698 `movs r6, #0` (i), then 0x0805C69A `movs r7, #0`
   (found); no entry test (0 < 20 is folded); the bottom test is 0x0805C6C0 `cmp r6, #0x13; bls`.
   `found = 0; for (i = 0; i < 20; i++)` gives the two moves in the other order (2 diff lines). agbcc has no
   scheduler, so the ROM order is the source order. A comma in a `for` initialiser that sets two loop variables is
   a standard C idiom, not a comma expression that places a store.
3. **The roster record is `__attribute__((packed))`**, copied from the merged `src/080CC510.c` (`struct Record`) and
   `src/080593E0.c` / `src/08058C48.c` (`UnitTemplate`). ROM: `g_state_02000000.records[i].name != 0` uses two
   literals, 0x02000000 (0x0805C69C) and 0x2E78 (0x0805C69E), added separately (0x0805C6A2, 0x0805C6A4) before
   `ldr r0, [r0]`; `g_state_02000000.records[m].identifier` uses one literal, 0x02002E7F (0x0805C982), then
   `ldrb r0, [r0]` at 0x0805C986. When the containing object's alignment is 1 byte, `expand_expr` folds the constant
   field offset into the symbol before the variable index is added, and only for a byte field; the u32 `name` cannot
   fold that way, so it splits. Alternatives:
   - the same struct unpacked: `.identifier` also splits into two literals (`ldr =0x2000000 ... adds ... ldr
     =0x2E7F`) where the ROM has one literal 0x02002E7F;
   - `data_02002E78[m].identifier` with an unpacked record: one literal 0x02002E78 plus `ldrb [r0, #7]` (2 diff
     lines);
   - the byte-pointer form of `src/080CCB94.c` (`&g_state_02000000_bytes[i * 16]` then `+ 0x2E78`) also gives the
     split literals for the loop, but it is not needed once the record is packed; the struct access is the plain
     form.
4. **`candidates[found] = i; found++;`.** ROM: 0x0805C6AC-0x0805C6B2 computes `sp + found + 0x1C` and stores `i`;
   only then does 0x0805C6B4-0x0805C6B8 compute `found + 1`. `candidates[found++] = i;` gives 12 diff lines, because
   the increment is computed before `add r0, sp, r0`. Both spellings are ordinary; the ROM picks the two-statement
   one.
5. **`do { ... } while (data_0200F42C->count != i);`** for the distinct-pick loop. ROM: 0x0805C6E8 `movs r6, #0`
   falls straight into the body at 0x0805C6EA with no entry test; the bottom is 0x0805C71E-0x0805C728
   (`ldr; ldr =0x2018; adds; ldrb r0; cmp r0, r6; bne`), the loaded count being the first `cmp` operand and the
   test `!=`. A `for` or `while` would get an entry test that agbcc cannot fold (the count is unknown). `count >= 1`
   and `count <= found` always hold here, so a do-while is the natural form.
6. **`if (candidates[pick] != 0xFF) { members[i] = candidates[pick]; candidates[pick] = 0xFF; i++; }`.** ROM:
   0x0805C702 `ldrb r1, [r2]`; 0x0805C704 `adds r0, r1, #0`; 0x0805C706 `cmp r0, #0xff`; 0x0805C712 `strb r1`
   (member); 0x0805C714-0x0805C716 `movs r0, #0xff; strb r0, [r2]`. This is the plain form, compiled first.
7. **`(s16)func_08002804() % n`** at all five random sites: 0x0805C5DC/0x0805C5E2-0x0805C5EE (inline `% 2`),
   0x0805C630/0x0805C644-0x0805C646, 0x0805C6CE/0x0805C6D6-0x0805C6D8, 0x0805C6EA/0x0805C6EE-0x0805C6F0 and
   0x0805C806/0x0805C812-0x0805C822 (inline `% 4`). Each shows `lsls #16; asrs #16`. The same spelling is in 34
   merged sources (for example `080D2114`, `080CF7F4`, `0812D660`). `func_08002804` returns
   `(seed >> 16) & 0x7FFF` (`src/08002804.c`).
8. **`func_08021A3C(data_0200F42C->heap, 736, 799, 0, 0)`.** ROM: 0x0805C858-0x0805C860 `movs r1, #0xb8; lsls r1,
   #2` (0x2E0), `ldr r2, =0x31F`, `movs r3, #0`, `str r3, [sp]`. `r0` is still `func_080070C8`'s return: with the
   plain struct reads, CSE removes the reload of `data_0200F42C->heap` because a struct store cannot alias the
   scalar global. Decimal arguments follow `src/0802995C.c` (`704, 725`). The prototypes for `func_08021A3C`,
   `func_08021B1C`, `func_08021BD4`, `func_08021618`, `func_08021DF8`, `func_08021E7C`, `func_08021F18` and
   `func_08001F34` are copied from `0802995C`.
9. **`if (items[i] != 0) func_08021BD4(objects[i], items[i])` passes the just-stored object from r2** (0x0805C892
   `adds r2, r0, #0`, 0x0805C8AA `adds r0, r2, #0`): the same CSE reuse as `0802995C`, from the plain form.
10. **`field_2026[i] + 4` is passed as a u32** (0x0805C8CA `ldrb r1`, 0x0805C8CC `adds r1, #4`, no narrowing),
    following `0802995C`'s u32 parameters for `func_08021618`.
11. **Case order 0, 1, 2, 0xFF** follows the code layout: case 0 at 0x0805C5C6, case 1 at 0x0805C7A4, case 2 at
    0x0805C93C, case 0xFF at 0x0805CA40. The compare tree at 0x0805C5A6-0x0805C5C4 is agbcc's own.
12. **The declaration order of locals is not load-bearing.** `found, i` and `candidates, i, found` both compile
    byte-identical.
13. **The struct layout comes from the immediate offsets.** The state has `heap` +0, `owner` +4, `items[2]` +8,
    `objects[2]` +0x10, `buffer[0x2000]` +0x18 (size from 0x0805C84A-0x0805C84C, `movs r1, #0x80; lsls r1, #6`);
    `count` +0x2018, `from_roster` +0x2019, `field_201A[2]`, `unknown_201C[2]`, `members[2]` +0x201E; `field_2020`
    through `field_202A` (u8[2] each), `unknown_202C[4]`; `x[2]` +0x2030 and `y[2]` +0x2034, both s16 (`ldrsh` at
    0x0805C9AA and 0x0805C9B6). `sizeof` = 0x2038 matches the allocation (0x0805C5C8). `MemberChoices` is
    `{u8 count; const u8 *members;}` with stride 8. The `runner` at `data_0200F428`+0xCD8 is the `Table` from
    `ffta.h`, as `0805873C` uses it.

## Bug check

None is reproduced. `func_08002804` returns 0..0x7FFF, so every `(s16)` dividend is non-negative and `count` is 1
or 2. On the roster path `func_080CCB94()` scanned the same 20 records, so `found >= 1`; the clamp is at least 1 and
no `__modsi3` call gets a zero divisor. `count <= found`, so the distinct-pick do-while terminates
(probabilistically). The default path indexes only `data_0839383C[0..1]`, which has 2 entries.

## Attempt record

The first draft had the right size and control flow, but `i` was in r7 and `found` in r8, the else-loop literal
was folded, and the record field reads were unpacked. The byte-pointer test, `candidates[found] = i; found++;` and a
separate ternary `limit` split the else-loop literals, with `i` and `found` still misallocated. Reusing `i` for the
clamp put `i` and `found` in r6 and r7 (80 diff lines left: case 2's split 0x2E7F literal and reload choices).
`data_02002E78[m].identifier` left 4 diff lines (`+7` folded into `ldrb`, the two zero moves swapped); the packed
record left 2 (the `movs` order); `for (i = 0, found = 0; ...)` left none.

kit issue: none filed for this combination. Related: shubshub/fftadecomp-kit#396 (the same compiler-signed-runtime-thunks route refuses a native stack buffer by its no-stack-alias rule)
