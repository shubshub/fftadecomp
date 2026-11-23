# func_08A3915C: the vertical clip takes a piece's bottom edge from its x position

**Status: reachable whenever a drawn object straddles the top or bottom edge
of the screen; the visible effect is rare.** The faulty test is shown by
executing the ROM's own bytes, together with the ROM's screen test that
decides which objects are drawn. Neither has been observed in a running game
or in a full-system emulator.

## The bug

`func_08A3915C` (IWRAM copy at 0x030065A8, reached through the ROM slot
0x0839402C) appends the pieces of an object's piece list to the current OAM
buffer and skips the pieces that are off the 240x160 screen. For each piece
it computes the left edge `px` and the right edge `px + width`
(0x08A3926C..0x08A39278) and tests them, then the top edge `py` and

```
08A3927A  mov  ip, r1          ; ip = px << 16, kept from the horizontal test
  ...
08A392D6  ldrh r1, [r5, #2]    ; height
08A392D8  mov  r0, ip
08A392DA  asrs r0, r0, #16     ; px
08A392DE  adds r0, r0, r1      ; bottom = px + height
```

and tests `py < 0 && bottom < 0` (0x08A392EA..0x08A392F4) and
`py > 159 && bottom > 159` (0x08A392F6..0x08A39302). The bottom edge should be
`py + height`.

## Trigger and reachability

A piece is decided wrongly when its top edge is off the screen (`py < 0` or
`py > 159`) and `px + height` and `py + height` fall on different sides of the
bound:

* above the top with rows still on the screen (`py + height >= 0`) and
  `px + height < 0`: a piece wider than it is tall, at the left edge, is
  dropped although part of it shows;
* wholly above the top (`py + height < 0`) with `px + height >= 0`: kept;
* wholly below the bottom (`py > 159`) with `px + height <= 159`: kept, that
  is any piece below the screen whose x is at most 159 minus its height.

Who reaches it:

* The slot 0x0839402C is read twice in the ROM: by `func_0808F638`
  (pool word 0x0808F674; the call at 0x0808F6C8 passes the object's s16
  position at +0x0C/+0x0E unchanged) and by `func_0808F1F4` (pool word
  0x0808F31C; the position plus the offset of a part, `src/0808F1F4.c`).
  `func_0808F638` walks the objects of the render tree every time
  `func_080231F4` runs (bl at 0x08023210), drawing the list at the object's
  +0x154 itself, or handing objects with a part tree (+0x150) to
  `func_0808F1F4` through `func_08021FB4` (0x0808F720). Neither caller clips
  the position.
* Objects enter the render tree in `func_0808EFCC`. For an object without a
  part tree it first calls the slot 0x08394028, `func_08A38EA0`, with the
  list at +0x158 and the same position (0x0808F0F6), and skips the object
  when that returns 0 (0x0808F0FC). `func_08A38EA0` is the same walk with the
  bottom edge right (see Developer intent). So whole objects off the screen
  are not drawn, and the faulty test decides the off-screen pieces of
  objects that are partly on the screen: objects at the top or bottom edge.
  `func_0808EFCC` compares the words at +0x158 and +0x154
  (0x0808F158..0x0808F15C); when they are equal the tested list is the drawn
  one. The test for objects with
  a part tree (the callback `func_0808F804`) was not analysed.

Not established: which objects of the game these are, how often one stands
at the top or bottom edge in play, and how often its pieces meet the
conditions above.

## Behaviour against correct behaviour

From `repro.py`, the ROM bytes against the `-DBUGFIX` build from the same
state, appending to an empty buffer (entries as the OAM fields hold them:
x 9 bits, y 8 bits):

| piece (position on the screen) | ROM | BUGFIX |
|---|---|---|
| 32x8 at (-20, -4): rows 0..3, columns 0..11 show | no entry | (492, 252) |
| 64x32 at (-40, -16) | no entry | (472, 240) |
| 8x8 at (100, -50): nothing shows (rows 206..213) | (100, 206) | no entry |
| 64x64 at (10, 200): nothing should show | (10, 200) | no entry |

Through the screen test, for two objects whose first piece, 8x8 at
(100, 150), is on the screen: `func_08A38EA0` passes both; the ROM builder
then keeps the second piece, wholly below the screen, as well:

| second piece | ROM | BUGFIX |
|---|---|---|
| 8x8 at (100, 170) | (100, 150), (100, 170) | (100, 150) |
| 64x64 at (10, 200) | (100, 150), (10, 200) | (100, 150) |

Pieces the bug does not touch agree: on the screen; crossing the top edge
away from the left edge; left of the screen; above the screen at the left
edge; below the screen at the right edge.

## Impact

* Kept pieces wholly above or below the screen draw nothing where they
  are (rows 160..255 of the OAM y range are off the screen), but each takes
  one of the buffer's 128 entries. The builder stops at its limit (128
  entries, or fewer when the caller passes a limit: `count >= limit` at
  0x08A39400..0x08A39402), so in a frame with nearly 128 entries an object
  drawn later can lose pieces. Whether any scene comes near 128 entries was
  not established.
* A kept piece below the screen whose rows pass 255 wraps: OAM y is 8 bits,
  so the entry at y = 200 of a 64-row piece covers rows 200..263, and rows
  256..263 are screen rows 0..7. The piece's last rows show at the top of
  the screen. That needs py >= 193 for a 64-row piece (>= 225 for 32 rows,
  >= 241 for 16, >= 249 for 8) while another piece of the same object is on
  the screen.
* A dropped piece at the top-left corner leaves a gap of at most its own
  size in the object while the object is crossing the corner.

## Developer intent

A copy-and-edit of the horizontal test a few lines above it:
`right = px + size->width` became `bottom = px + size->height` with the
member changed and the variable not. The two sibling walks in the same code
image add the height to `py`:

* `func_08A38EA0`, the screen test above: `ldrsh` of the height added to py
  at 0x08A38F8A..0x08A38F8E and 0x08A38F98..0x08A38F9C;
* `func_08A39458`, the out-of-line worker of the other OAM list builder
  `func_08A397D8`: the same at 0x08A3959E..0x08A395A2 and
  0x08A395AE..0x08A395B2.

Unlike those two, this function computes each far edge once into its own
variable before its two tests (0x08A39272..0x08A39278 and
0x08A392DE..0x08A392E4), which is where the wrong variable went in.

## The fix

```c
#ifdef BUGFIX
            bottom = py + size->height;
#else
            bottom = px + size->height;
#endif
```

The vertical test then matches the horizontal one and the two sibling walks.

## Reproduction

`repro.py` copies the code image [0x08A38ADC, 0x08A3991C) to 0x03005F28 as
`func_0808F74C` does, links the default build at 0x08A3915C and requires it
to equal your ROM's 764 bytes, then runs the original at 0x030065A8 and the
`-DBUGFIX` build from a scratch page on the same piece lists, and the ROM's
`func_08A38EA0` at 0x030062EC for the last case. Requires unicorn and the
repository toolchain (see the docstring).

```
$ python3 docs/bugs/08A3915C/repro.py baserom.bin
source src/08A3915C.c: default build == ROM bytes [08A3915C, 08A39458)

1. Dropped although visible: a 32x8 piece at (-20, -4) covers rows 0..3
   and columns 0..11.  The ROM tests px + height = -12 < 0 and drops it.
  [ok] ROM entries: []
  [ok] BUGFIX entries (x, y): [(492, 252)]
  [ok] 64x32 at (-40, -16): ROM entries: []
  [ok] 64x32 at (-40, -16): BUGFIX entries: [(472, 240)]

2. Kept although above the screen: an 8x8 piece at (100, -50).  The ROM
   tests px + height = 108 >= 0 and keeps it; the entry shows nothing
   (rows 206..213) but takes one of the 128 OAM entries.
  [ok] ROM entries (x, y): [(100, 206)]
  [ok] ROM entry rows on screen: []
  [ok] BUGFIX entries: []

3. Kept although below the screen, and wrapped to the top: a 64x64
   piece at (10, 0) of a list placed at y = 200.  The ROM tests
   px + height = 74 <= 159 and keeps it; OAM y wraps at 256, so rows
   0..7 of the screen show the piece's last rows.
  [ok] ROM entries (x, y): [(10, 200)]
  [ok] ROM entry rows on screen: [0, 1, 2, 3, 4, 5, 6, 7]
  [ok] BUGFIX entries: []

4. Non-triggers: both builds agree.
  [ok] on screen, 8x8 at (100, 50): ROM == BUGFIX: ([(100, 50)], [(100, 50)])
  [ok] crossing the top edge at the right, 32x8 at (200, -4): ROM == BUGFIX: ([(200, 252)], [(200, 252)])
  [ok] crossing the top edge, 64x64 at (10, -56): ROM == BUGFIX: ([(10, 200)], [(10, 200)])
  [ok] left of the screen, 8x8 at (-30, 50): ROM == BUGFIX: ([], [])
  [ok] above the screen at the left edge, 32x8 at (-20, -50): ROM == BUGFIX: ([], [])
  [ok] below the screen at the right, 64x64 at (150, 170): ROM == BUGFIX: ([], [])

5. Through the render tree's screen test: objects that straddle the
   bottom edge.  func_08A38EA0 adds the height to py and passes each
   object, because its first piece, 8x8 at (100, 150), is on screen;
   the ROM builder then also keeps the second piece, which is wholly
   below the screen: an 8x8 one at (100, 170) takes an entry and shows
   nothing, a 64x64 one at (10, 200) shows its last rows at the top.
  [ok] 8x8 at (100, 170): func_08A38EA0 (ROM): 1
  [ok] 8x8 at (100, 170): ROM entries (x, y): [(100, 150), (100, 170)]
  [ok] 8x8 at (100, 170): rows of the second entry on screen: []
  [ok] 8x8 at (100, 170): BUGFIX entries: [(100, 150)]
  [ok] 64x64 at (10, 200): func_08A38EA0 (ROM): 1
  [ok] 64x64 at (10, 200): ROM entries (x, y): [(100, 150), (10, 200)]
  [ok] 64x64 at (10, 200): rows of the second entry on screen: [0, 1, 2, 3, 4, 5, 6, 7]
  [ok] 64x64 at (10, 200): BUGFIX entries: [(100, 150)]

all assertions hold
```
