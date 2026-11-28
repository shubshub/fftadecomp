# func_0803E3B4: paying a cost in list items takes every copy held

**Status: conditionally reachable.**
* Two shipped rows reach the faulty code: rows 44 and 46. Each costs one
  copy of a list item (0x77 and 0x34).
* The defect shows only when the player holds two or more copies of that
  item.
* The list takes duplicates and the counter counts them. Whether the game
  can give the player a second copy of 0x77 or 0x34 has **not** been
  established.
* With a single copy, the only case known to occur, the ROM and the BUGFIX
  build behave identically.

`repro.py` runs the ROM's own bytes on the two-copy and three-copy states:
* The ROM clears every copy.
* The BUGFIX build clears one.

## The bug

`func_0803E3B4(index)` is one of the menu sub-tasks that `func_08034E88`
dispatches (BL at 0x08034F0A, its only caller). It is a state machine on
`slots[index].state`. State 10 takes the cost of the selected row,
`g_table_08564670[window->selector]`. The table has 27-byte rows: the cost
is `item` (u16 at +7) times `count` (u8 at +9).

The cost kind is chosen by the item id:

| item | kind | count held | removal |
|---|---|---|---|
| 0 | nothing | - | - |
| >= 0x8000 | money, `count * 200` (state 0x17) | - | - |
| 0x4000-0x7FFF | list B: 20 halfwords at `g_state_02000000+0x1F3C`, id = `item & 0x7FFF` | `func_08038704(id)` | `func_080386C8(id, limit)` |
| 0x178-0x3FFF | list A: 64 entries `{u8 id, u8, u16 holder}` at `+0x2B08`, id = `(item & 0x3FFF) - 0x177` | `func_080385E4(id)` | `func_080385A8(id, limit)` |
| below 0x178 | a plain item in the bank `g_state_02001940` | `func_080CB2B4(item)` | `func_080CA9E8(item, row->count)` |

List A's branch, 0x0803EB0C-0x0803EB56:

```
0803EB16  ldr  r2, =0xFE89 ; adds ; lsls/lsrs #16    ; id = (u16)((item & 0x3FFF) - 0x177)
0803EB20  bl   func_080385E4                          ; free copies of id
0803EB24  lsls r0, #24 ; lsrs r1, r0, #24             ; r1 = (u8) number held
0803EB28  ldrb r0, [r4, #9]                           ; row->count
0803EB2A  cmp  r1, r0 ; blo 0x0803EBA8                ; held < cost: "not enough" (state 0x11)
0803EB2E  cmp  r0, #0 ; bne 0x0803EB34
0803EB32  movs r1, #1                                 ; a row costing 0: limit 1
0803EB34  adds r0, r5, #0
0803EB36  bl   func_080385A8                          ; limit = r1 = number held   <- BUG
0803EB4A  ldrb r1, [r4, #9]                           ; the message gets row->count
0803EB56  bl   func_0803E1C0                          ; (id, row->count, data_085668B0[47], 1)
```

List B's branch (0x0803EA54-0x0803EA96) has the same shape:
* `func_08038704` at 0x0803EA60 counts the copies;
* the same guard is at 0x0803EA6E;
* `func_080386C8` at 0x0803EA76 removes them;
* the message gets kind 2.

Both removers work the same way: they walk their list in order and clear
each entry that holds the id, until they have cleared `limit` entries. In
list A an entry is cleared with its holder. Both test only the id. The ROM
passes the number held as `limit`, so:
* **List B:** every copy held is cleared.
* **List A:** the counter `func_080385E4` counts only *free* copies, those
  with holder 0. `func_080385A8` clears as many entries as there are free
  copies, in table order, whether attached or free. When no copy is attached
  (the usual case), that is every copy. With an attached copy early in the
  list, it takes the attached copy and leaves a free one (section 3).

The u16 at +2 of a list-A entry is named `count` in `src/080385A8.c`. It
behaves as a holder: `src/080CF118.c` matches it against a record's id and
clears it when that record lets the entry go.

## Trigger and reachability

**Rows.** The table has rows 0-123. From row 124 (0x08565384) on, the bytes
no longer follow the row layout, and rows 125-127 are zero. `repro.py`
checks:
* Only rows 44 (item 0x1EE: list A id 0x77, one copy) and 46 (item 0x1AB:
  list A id 0x34, one copy) have a list-A cost.
* No row has a list-B cost. The list-B branch is therefore unreachable with
  the shipped table.

**The path to state 10.** State 9 waits for the yes/no window
(`slots[1]`). On choice 0 it sets the next state to 10, which state 2
enters. Which events open this menu on rows 44 and 46 was not traced.

**Two copies.** `func_080384F0` is list A's adder:
* It takes the first empty entry and does not check for the id already
  being there. Its only caller (0x08038A8C) is `func_0803890C`, which
  commits queued rewards of kind 1.
* `func_08038858` queues rewards. It is called from `func_0803A07C`
  (0x0803A604, 0x0803A620), `func_080458A4` (0x080459E0, 0x08045A3A),
  `func_08045DF4` (six sites, 0x08046048-0x080461A2) and this function's
  state 12 (0x0803F0C2).
* In this table, the kind-1 rewards are row 41 (item 0x19C, list A id 0x25)
  and row 45 (0x1A4, id 0x2D). Neither is 0x77 or 0x34.
* The reward data of the other three queuers was not examined.

So two copies are structurally possible, but it is **not known** whether
play can produce them for 0x77 or 0x34. The case is conditional on that.

## Behaviour

`repro.py`, state 10 run once in each build:

| section | state | ROM | BUGFIX |
|---|---|---|---|
| 1 | row 46; two free copies of 0x34 (entries 3, 10), plus 0x77 and 0x12 | both copies of 0x34 cleared | entry 3 cleared, entry 10 kept |
| 2 | row 44; three free copies of 0x77 (entries 1, 2, 9) | all three cleared | entry 1 cleared |
| 3 | row 46; 0x34 attached to record 0x11 (entry 2), free copies at 7 and 12 | entries 2 and 7 cleared, 12 kept | entry 2 cleared (the attached copy) |
| 4 | row 46; one copy | cleared | the same |
| 5 | row 46; no copy | "not enough": next state 0x11, nothing cleared | the same |
| 6 | row 42 (plain item 0x177, one); five held | four left | the same |
| 7 | synthetic row: list B id 0x40B1, one; held twice | both cleared | one cleared |
| 8 | synthetic row as 7; list B holds 0x00B1 | count 0: "not enough" | the same |

In sections 1-4 and 7, both builds otherwise do the same:
* the message call `func_0803E1C0(id, 1, data_085668B0[47], kind)`, which
  reports one copy;
* the next state is 0x14, renderer 5 is enabled, and the same callee
  sequence runs.

Sections 7 and 8 write a row at index 200 into the *emulated* ROM. No
shipped row reaches list B; these sections only exercise the second BUGFIX
site.

## Impact

* **If two copies can be held:** paying row 44 or 46 removes every free
  copy of the item instead of one. The game says that one copy was handed
  over. The other copies are simply lost, with no other side effect.
* **With one copy:** no effect. Neither does it matter whether the player
  holds two copies of other items.

Two notes on what the BUGFIX does not change:
* **Section 3:** `func_080385A8` does not skip attached copies. A removal
  can take a copy that a record still holds, even though the counter
  counted only free ones. Both builds do this. It is a separate quirk of
  the list-A helpers, and the fix does not address it. Whether a copy can
  be attached while this menu runs was not traced.
* **Section 8:** list B's cost id keeps bit 0x4000 (`item & 0x7FFF`), but
  state 12 masks a list-B reward to `id & 0xFFF` (0x0803F056-0x0803F058)
  before `func_08038858` queues it, and `func_08038628` stores it that way. The branch would never find a copy that the game gave.
  This is moot, because no row reaches the branch.

## Developer intent

The intended rule is "remove the row's count of copies", as everywhere else
in this state:
1. **The plain-item branch** of the same state passes the row's count to
   its remover: `ldrb r1, [r4, #9]` at 0x0803EBE4, then
   `func_080CA9E8(item, row->count)` at 0x0803EBE6. Section 6 runs it:
   five held, one taken.
2. **The message** in both list branches reports the row's count
   (`ldrb r1, [r4, #9]` at 0x0803EA8A and 0x0803EB4A).
3. **The removers take a limit, yet each has exactly one call site**:
   0x0803EA76 for `func_080386C8`, 0x0803EB36 for `func_080385A8`. The
   counters `func_08038704` and `func_080385E4` also have one call site
   each, the line just before. If "remove all" were meant, the limit would
   never be needed: called with the number just counted, it cannot stop the
   walk early when every copy is free.
4. **The zero guard** (0x0803EA6E, 0x0803EB2E) tests the *row's* count but
   overwrites the *limit*. It turns "costs nothing" into "remove one". That
   only makes sense if the developer believed the limit already held the
   row's count.

The ROM uses a single value both for the number held (compared with the
row's count) and for the removal limit. In the reconstruction it is the
local `count`. Whatever its original name, the likely slip is passing that
local where the plain-item branch passes `row->count`:
* The plain branch passes `row->item` and `row->count` straight to its
  remover.
* The list branches first convert the item to a list id held in a local.
* In their remover calls, the local that holds the number held took the
  place of `row->count`.

## The fix

In both list branches:

```c
            count = func_080385E4(id);          /* func_08038704(id) for list B */
            if (count >= row->count) {
#ifdef BUGFIX
                count = row->count;
#endif
                if (row->count == 0)
                    count = 1;
                func_080385A8(id, count);       /* func_080386C8(id, count) */
```

Why it is correct:
* After the "enough?" test the limit becomes the row's count, so exactly
  the advertised number of copies goes.
* The zero guard keeps its ROM meaning.
* The message, the next state and every other store are unchanged
  (sections 1-4, 7).
* With one copy, or none, both builds behave identically (sections 4-5).

What the fix does not change: which entries go. They are still the first
ones in table order, attached or not (section 3).

## Reproduction

```
python3 docs/bugs/0803E3B4/repro.py [path/to/baserom.bin]
```

What it does:
* Checks that the default build links to the ROM bytes
  [0x0803E3B4, 0x0803F650), and reads the rows' costs from the ROM.
* Runs these from the ROM: the four list helpers, the bank helpers
  `func_080CB2B4` and `func_080CA9E8`, the row table and the label table.
* Stubs the message (`func_0803E1C0`, recorded) and the sound, window and
  renderer calls (logged). It asserts that no other callee is reached.

It needs unicorn and the toolchain; see the header of `repro.py`.
