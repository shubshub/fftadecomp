# func_0804E358: removing a list's last entry underflows its saved cursor row

**Status: reachable in play.** The faulty store is shown by executing the ROM's
own bytes. The on-screen effect comes from reading the code and running the
ROM's consumer functions under emulation. It has not been observed in the
running game.

## The bug

`func_0804E358(group)` clamps the saved position of list `group` after the
list's entry count has changed. The position is the record
`{u16 top; u16 selected}` at `data_0201F548 + 0x53C + 4 * group`.

```
0804E38E  ldrh r1, [r5]          ; top
0804E390  adds r0, r1, #6
0804E392  cmp  r0, r2            ; r2 = count
0804E394  ble  0x0804E3B4        ; top + 6 <= count: nothing to do
0804E396  ldrh r3, [r5, #2]      ; selected
0804E398  adds r0, r3, r1        ; (u8)(selected + top), 0x0804E39A-0x0804E39C
0804E39E  cmp  r0, r2
0804E3A0  blo  0x0804E3AA        ; before the end: keep the cursor
0804E3A2  cmp  r2, r4            ; r4 = 6 rows
0804E3A4  bhs  0x0804E3AA
0804E3A6  subs r0, r3, #1        ; selected - 1, with no test for 0
0804E3A8  strh r0, [r5, #2]
0804E3AA  ldrh r0, [r5]
0804E3AC  cmp  r0, #0            ; top - 1 only if top != 0
0804E3AE  beq  0x0804E3B4
```

When the count is 0, all three conditions hold: `top + 6 > 0`, `selected + top
>= 0` and `0 < 6`. A `selected` of 0 therefore becomes `0xFFFF`. The top row
has a guard (0x0804E3AC) but the selected row does not.

## Trigger and how often it happens in play

The function has two callers, both BLs and both states of the menu state
machine `func_0804CBB4`:

| caller | bl | what it does first |
|---|---|---|
| `func_0804D7E8` | 0x0804D80A | Zeroes the chosen list-4 entry (a pointer into `g_state_02002B08`, obtained through `func_0804E9D0`), re-sorts list 4 (`func_080CB24C`), then clamps group 4. |
| `func_0804D840` | 0x0804D862 | Removes the chosen list-5 value from the 20-slot table at `0x02001F3C` (`func_08038694`), compacts and sorts the table (`func_080CB27C`), then clamps group 5. |

Both are the "Yes" branch of a confirmation prompt that follows picking an
entry. `func_08013380` returns 0 for "Yes":

* State 0xB (0x0804CF2C) picks a list-4 entry. State 0xC (0x0804D070) is the
  yes/no prompt, and state 0xE (0x0804D154) calls `func_0804D7E8`. Entries
  whose halfword at +2 is non-zero get a message instead (state 0xD), so they
  cannot be removed.
* State 0x10 (0x0804D232) picks a list-5 entry. State 0x11 (0x0804D330) is the
  prompt, and state 0x12 (0x0804D36C) calls `func_0804D840`.

Picking an entry first saves `{top, cursor}` into the record:
`func_0804E408` case 0x103 writes `records[slot] = {state->value,
state->kind}`, which are the menu's +0x1A top row and the list's +0x11 cursor
row. When the list had exactly one entry, the record is `{0, 0}` and the
count after removal is 0, which is the trigger.

The game expected the list to empty. After the removal, state 0x13
(0x0804D3F8, list 5) and state 0xF (0x0804D1DE, list 4) test whether anything
is left (`func_08050E84`, `func_0804D814`). If nothing is, they return to the
category menu instead of re-opening the list.

The category menu still offers the empty list:

* `func_08050C38` builds its six entries from the table at `0x083937B2`
  (`0x3B 0x3C 0x3D 0x3E 0x4F 0x3F`).
* It drops only `0x4F` (list 5), and only while event flag `0x207` is clear
  (`func_080C9540`).
* It never tests a count.
* `func_0804D6B0` cases 4 and 5 open lists 4 and 5 unconditionally.

When the player opens the list again, the list task
(`func_0804E408` -> `func_0804EF68` -> `func_0804F948`) restores the record
without a check:

* `strh` of top into menu +0x1A at 0x0804FA1A;
* the low byte of `selected`, read as s8 (`ldrsb` at 0x0804FA46), to
  `func_08017AF4` (bl at 0x0804FA4C);
* the same byte read as u8 (`ldrb` at 0x0804FA9C) to `func_08017FB0` (bl at
  0x0804FAA0).

The record lasts as long as the menu does. `func_0804E05C` allocates the menu
data and clears it with the `(pointer, size)` callback that allocation sites
call on new blocks (`g_callbacks_0836D4B8[0]`). It frees the data on exit, so
the bad row persists until the menu is closed. It also persists until the
player picks an entry again, which rewrites the record, and the list has to be
refilled for that.

So the trigger is: in this menu, remove the only entry of list 4 (always
available), or of list 5 (once flag 0x207 is set), and then open that category
again before leaving the menu.

## Behaviour against correct behaviour

| state | ROM | correct |
|---|---|---|
| group 4 or 5, `{0, 0}`, count 0 | `{0, 0xFFFF}` | `{0, 0}` |
| group 5, `{0, 2}`, count 2 | `{0, 1}` | `{0, 1}` |
| group 4, `{2, 3}`, count 7 | `{1, 3}` | `{1, 3}` |
| group 5, `{0, 5}`, count 9 | `{0, 5}` | `{0, 5}` |

When the empty list is shown again, the ROM consumers receive row -1 / 0xFF:

* `func_08017AF4` passes -1 to `func_0801799C`. That function draws the
  highlight row: `copy = destination + (row << 1) * field_1E`. The palette-11
  highlight is therefore copied into the **two map rows above the list**
  (rows -2 and -1) instead of rows 0 and 1. The source is ring row
  `((top + row) * 2) mod (rows * 2)`, taken through `__modsi3`
  (`func_08142950`) of the u16 value 0xFFFE.
* `func_08017FB0` stores 0xFF in the list's +0x11 (its cursor row) and 0xFF0
  in +0x0E (`row << 4`).

With the fix, an empty list is shown as it is when the menu has never visited
it: highlight copies to map rows 0 and 1, and cursor row 0.

## Impact

What the code shows: when the emptied category is re-opened, the highlight
copies overwrite two tile rows of the BG map directly above the list. These
are probably the window's frame or title. The copied content is a palette-11
copy of a list row, which is blank because the list is empty. The cursor
record also holds row 255.

Not established:

* how the frame looks after the overwrite;
* whether the cursor sprite at row 255 is visible. Its drawing code was not
  traced.

Any corruption is cosmetic and temporary as far as traced. It lasts until the
menu is closed. Also not traced: what the list's input handler
(`func_0804F14C`) does with cursor row 0xFF on an empty list. There are no
entries for it to select, so no data is read through the bad row in the paths
examined here.

## Developer intent

The intent was to keep the saved cursor inside the shrunken list. The
developer guarded the top-row decrement (`if (top) top--`) but not the cursor
decrement. The likely reasoning was "the cursor is past the end, so there is a
row before it". That holds for every count from 1 up. The clamp runs after one
entry is removed, so `count < 6` means the list had at most 6 entries before
the removal: it fit on one page, `top` is 0, and `selected >= count >= 1`. It
fails only for a count of 0. In short, this is a missing empty-list case.

Evidence that the empty case was anticipated in the caller but not here:

* Both removal paths test for an empty list afterwards (0x0804D3F8,
  0x0804D1DE) and avoid re-opening it. The author knew that removing an entry
  can empty a list.
* The same expression has a guard one line later (`if ((saved)->top)`). The
  missing guard is an omission rather than a different convention.

## The fix

```c
#ifdef BUGFIX
    /* An empty list has no row to step back to: leave the cursor on row 0,
       where a list that was never opened has it. */
    if (count == 0) {
        saved->top = 0;
        saved->selected = 0;
    } else
#endif
    CLAMP_SELECTION(saved, count, rows);
```

`{0, 0}` is the record a fresh menu has, because the menu data is cleared at
allocation. It is also what the clamp would produce if it guarded the cursor
the way it guards the top row. For counts of 1 and up, the fixed build runs
the unchanged clamp. The default build is unchanged: the source still MATCHes
98/98, `plausible.py --strict` exits 0, and the preprocessed default token
stream is identical to the parked source.

## Reproduction

`repro.py` does the following:

1. Links the default build at 0x0804E358 and requires it to equal your ROM's
   98 bytes.
2. Runs the ROM bytes and the `-DBUGFIX` build on the same records.
3. Stubs `func_08050E74` / `func_08050E84` (the counts) and records BIOS
   CpuSet.
4. Runs the ROM's `func_08017AF4` -> `func_0801799C` and `func_08017FB0` with
   each result.

Requires unicorn and the repository toolchain (see the docstring).

```
$ python3 docs/bugs/0804E358/repro.py baserom.bin
source src/0804E358.c: default build == ROM bytes [0804E358, 0804E3BA)

1. Trigger: func_0804D840 removed the only entry of list 5.  The record
   holds the row the player picked it from, {top 0, selected 0}; the count
   is now 0.
  [ok] ROM    {top, selected}: ('0x0', '0xffff')
  [ok] BUGFIX {top, selected}: ('0x0', '0x0')

   The same through func_0804D7E8, which removes the only entry of list 4:
  [ok] ROM    {top, selected}: ('0x0', '0xffff')
  [ok] BUGFIX {top, selected}: ('0x0', '0x0')

2. Non-trigger: the last of three entries removed, cursor on it
   ({0, 2} with count 2): both step back to row 1.
  [ok] ROM   : (0, 1)
  [ok] BUGFIX: (0, 1)

3. Non-trigger: list 4 scrolled ({2, 3}) after its count fell to 7:
   both pull the page up one row and keep the cursor row.
  [ok] ROM   : (1, 3)
  [ok] BUGFIX: (1, 3)

4. Non-trigger: the list still fills the page ({0, 5} with count 9):
   neither changes the record.
  [ok] ROM   : (0, 5)
  [ok] BUGFIX: (0, 5)

5. Impact: the empty list is shown again from the category menu and
   func_0804F948 restores the saved row into the ROM consumers.
   (window: 6-row ring, 12 tiles wide, map stride 32 tiles)
   The highlight's CpuSet copies go to map rows (row << 1) and (row << 1) + 1,
   counted from the list's first map row; the ring size does not enter.
  [ok] ROM    map rows written: [-2, -1]
  [ok] ROM    list +0x11 / +0x0E (row, row << 4): (255, '0xff0')
  [ok] BUGFIX map rows written: [0, 1]
  [ok] BUGFIX list +0x11 / +0x0E (row, row << 4): (0, '0x0')

all assertions hold
```
