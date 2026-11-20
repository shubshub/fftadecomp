# 0x080447B4 - five-phase menu resolution task: bytes identical, refused (a register cursor over a local array at a loop head) (1500 bytes)

Attempt 2026-11-20, kit 3afe589f4, decomp main 81362adaf07.
`void func_080447B4(void *task, u8 *phase)` is a task of the 0x0804 menu module, dispatched through a five-entry jump
table at 0x080447D8 on `*phase`:

- phase 0 asks `func_0804BB5C` for the value of entry 0 and of every type 2 or 4 entry among entries
  1-6 (`MenuEntry`, the 0x34-byte entry of `src/080445DC.c`), and goes to phase 4 when entry 0 has none;
- phase 1 runs `func_08044E44` on the active entries and then marks with status 0xFF every entry that conflicts with
  an earlier one: the same direction as entry 0 (`func_0804BB10(...) - 1`), the same choice as an earlier entry, or a
  choice equal to an excluded entry's slot (this last loop restarts from the first entry after each mark);
- phase 2 calls `func_08045260` for the remaining entries (discarding its result) and goes on once the status byte
  it sets marks every entry done (0xFF), then sets up the panel: it clears the
  panel's 16 item pointers, asks `func_080D17C4` for the result and its kind through a local byte, records the kind,
  counts the items with `func_080D1C94` when there is no result, and either finishes (phase 4) or arms phase 3 with
  `data_0201F4E8 = 0` and `data_0201F4E9 = 1`;
- phase 3 waits for the panel state to leave 3, counts calls in `data_0201F4E8` and resumes at the phase kept in
  `data_0201F4E9` after the sixth; phase 4 does nothing.

## The index

The index row `080447B4 08044D90 1500 664 return` has the right extent: `push {r4-r7, lr}`, `push {r5-r7}` (r8-r10)
and `sub sp, #0x48` at 0x080447B4-0x080447BE pair with `add sp, #0x48`, `pop {r3-r5}` (restoring r8-r10),
`pop {r4-r7}`, `pop {r0}` and `bx r0` at 0x08044D72-0x08044D80, and the last literal pool (0x08044D84-0x08044D8C) ends
at the indexed end. No index change is needed.

## Byte identity

`080447B4.c` (SHA-256 `39ae59c34f61ef4c9670d10a167db0ce9586d66a96a80486693b8e9a14a0c43c`) was compiled as
`match.py` compiles it (fixed flags, `-mthumb-interwork -O2`) and linked at 0x080447B4 with every callee and data
symbol bound to its ROM address (36 relocations resolved). The 1500 linked bytes equal the ROM span
`[0x080447B4, 0x08044D90)`, SHA-256 `262ece5f029e8b3dec1d315170cb7a7b7b82eaa6523315e75c084ae2be16fca8`.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Two symbols are needed; neither is in `config/data_symbols.json`. Each address was found as an aligned literal word by
scanning the whole ROM, and every such word is inside this function:

| Symbol | Literal words | Object |
|---|---|---|
| `data_0201F4E8` | 0x08044D38, 0x08044D88 | `u8`: the call counter of phase 3 (`strb` at 0x08044D26; `ldrb`/`adds #1`/`strb` at 0x08044D5C-0x08044D60) |
| `data_0201F4E9` | 0x08044D3C, 0x08044D8C | `u8`: the phase phase 3 resumes at (`strb` at 0x08044D2C; `ldrb` at 0x08044D6C) |

Both are accessed only as bytes and only by this function.

## Refusals

Kit 3afe589f4 (every refusal line below was rerun there), `match.py --root . --no-write [selector] 0x080447B4` with this source copied to `src/080447B4.c` and
the symbols above added. None matched.

| Selector | Refusal |
|---|---|
| default | `inconsistent stack aliases at control-flow join; owner-switch data-buffer proof: inconsistent possible pointer offsets at control-flow join` |
| `--switch-data-profile u16-scalars-frame-v1` | `inconsistent stack aliases at control-flow join` |
| `--switch-data-profile u16-scalars-fixed-frame-v1` | the same |
| `--switch-data-profile u16-scalars-v2` | the same |
| `--switch-data-profile u16-scalars-v1` | the same |
| `--owner-runtime-profile conditional-finite-spilled-scalar-loops-v1` | `finite loops exclude local BL and word switches` |
| `--owner-runtime-profile conditional-finite-local-word-loops-v1` | the same |

`inconsistent stack aliases at control-flow join` is raised at one place, `tools/match.py:5417`: at a join, a register
whose stack alias differs between the incoming paths is refused unless it is overwritten before it is used.

## Cause

Phase 2 clears a 16-word local array with a register cursor:

```
08044B56  mov  r4, sp
08044B58  ldr  r0, [r5]            @ loop head
...
08044B64  stm  r4!, {r2}           @ items[k] = 0; r4 += 4
...
08044B6A  ble  0x08044B58
```

At the loop head r4 is sp+0 on entry and sp+4n on the back edge, and the next use of r4 (the `stm`) reads it before
anything overwrites it, so the join check refuses. The same frame also holds the address of the local `kind`
(`add r6, sp, #0x40` at 0x08044B52), which is live across the calls of phase 2, passed in r2 to `func_080D17C4`
(`adds r2, r6, #0` at 0x08044B8A, `bl` at 0x08044B8C) and read back at 0x08044B98 and 0x08044C78, and the incoming
`phase` pointer spilled at sp+0x44 (0x080447C0) and reloaded at 0x0804488C, 0x08044D14, 0x08044D30, 0x08044D56 and
0x08044D6E. The finite-loop selectors exclude the function because of its jump table (a word switch).

## Source notes

1. **`unknown_A9 = kind` in the `kind == 1` arm.** Both arms that record the kind store the byte loaded at 0x08044B98
   (`cmp r3, #1` at 0x08044B9A; `strb r3` at 0x08044BA2 and 0x08044BDC). The literal `unknown_A9 = 1` compiles to
   1504 bytes with an extra register copy. A reviewer should confirm that storing the variable in an arm where it is
   known to be 1 is a plausible original (both arms "record the result kind").
2. **The local `items[16]` is written and never read.** The sixteen stores are in the ROM (the cursor loop above) in a
   0x40-byte frame area nothing else touches; the source comments it. A reviewer should judge whether a write-only
   local array is the likely original or whether another spelling (for example a clear loop over a different object)
   leaves the same stores.
3. **The direction compare goes through a `u8` local `other`.** `direction == (u8)(func_0804BB10(...) - 1)` in the
   condition is also identical; without the narrowing (`direction == func_0804BB10(...) - 1`) the output differs
   (three differences).
4. **The inner conflict loop retests entry `i + 1` instead of `j + 1`** (`ldrb r0, [r0]` from the outer row offset at
   0x08044A00, `cmp r0, #0xff` / `beq` at 0x08044A04). The result is the same either way, because only later entries
   are written in that loop, so it is not a bug case; the source comments it.
5. **`i = 0xFF; break;` restarts the outer loop**: the 0xFF just stored also goes to `i` (`mov r8, r0` at 0x08044AA4)
   and the increment at 0x08044AC6 wraps it to 0.
6. **`u8 i`/`j` against `s32 k`**: the first group is narrowed (`lsls`/`lsrs #24`), the second compared signed
   (`ble` at 0x08044B6A and 0x08044C6A).
7. No volatile, no inline helper, no macro.

No original bug is reproduced.

kit issue: no issue yet for the loop-head cursor over a local array (the join check at `tools/match.py:5417`). The
finite-loop selectors' word-switch exclusion has no issue either.
