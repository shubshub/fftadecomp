# func_08116514: the last pass of phase 0x101 reads every curve one entry past its end

**Status: reached on every complete run of this task; nothing of it is
drawn.** The out-of-range reads are shown by executing the ROM's own bytes.
That none of the values read reaches the screen is shown by running the ROM's
object update and draw walk after every pass, and the effect's own BG2 and
blend code, under emulation. Neither has been observed in a running game or
in a full-system emulator.

The sister task `func_08117B9C` has the same code on its own copy of the data;
its case is `docs/bugs/08117B9C/`.

## The bug

`func_08116514` is a task callback that `func_081168B4` starts. Its phase 0
creates 24 sprite pieces from the 16-byte rows of `data_083A4AE4`. Phase 0x101
then moves them for 150 passes: on each pass it steps a timer and uses it to
index a set of 150-entry curves:

```
08116780  ldrh r0, [r4]           ; payload->timer
08116782  adds r0, #1
08116784  strh r0, [r4]           ; timer++, before the lookups
08116788  ldr  r2, =0x083A4344    ; data_083A4344, the BG2 curve
0811678E  ldrb r3, [r1]           ; curve[timer] -> func_080D7468 (BG2 offsets), bl at 0x08116794
          ; for each of the 24 pieces (0x081167B4-0x08116860):
081167DA  ldrb r3, [r2]           ; payload->offsets[j][timer] -> y of func_080107D4, bl at 0x081167E6
08116822  ldrh r0, [r0]           ; data_083A4314[scale_x[j]][timer] } -> func_080112CC, bl at 0x08116854,
08116842  ldrh r0, [r0]           ; data_083A4314[scale_y[j]][timer] }    for the scaled pieces
08116864  ldrh r0, [r4]
08116866  cmp  r0, #0x95
08116868  bls  return             ; stay in the phase while timer <= 149
0811686E  bl   func_080D5F74      ; remove the 24 pieces
08116872  display &= 0x7FFF ; phase = 0x102
```

The curves, all from the ROM:

* thirteen byte curves of 150 entries, back to back from `data_083A4344`
  (0x083A4344-0x083A4AE1). Each piece row points at the start of one; the BG2
  call always uses the first. Two zero bytes of pad follow at 0x083A4AE2, then
  the piece table `data_083A4AE4`;
* four s16 scale curves of 150 entries, back to back at 0x083A3E64-0x083A4313,
  followed by `data_083A4314`, a table of 12 pointers to them (or 0) that the
  pieces' scale indexes select. The pieces select 0x083A3E64, 0x083A3F90 and
  0x083A40BC; nothing selects the fourth, 0x083A41E8.

The timer is 0 when phase 0x101 starts and is stepped before the lookups, so
the 150 passes read entries 1 to 150. There is no entry 150. The 150th pass,
the one that goes on to remove the pieces, reads one past the end of every
curve it uses: the first entry of the next curve, or the pad after the last
byte curve. On that pass the ROM makes 34 such reads (1 for BG2, 24 piece
offsets, 9 scale values) and passes what they hold on:

| curve | entry 149 | read as entry 150 |
|---|---|---|
| byte curves (BG2 and piece offsets) | 5, 10, 15, 20, 25, 30, 40, 45, 50, 60, 70, 80, 100 | 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0 |
| scale curve 0x083A3E64 | 0x0155 | 0x0100 (0x083A3F90) |
| scale curve 0x083A3F90 | 0x0200 | 0xFF00 (0x083A40BC) |
| scale curve 0x083A40BC | 0xFEAB | 0xFF00 (0x083A41E8) |

Entry 0 is not read in phase 0x101 at all. It is the state the pieces already
have (see Developer intent).

## Trigger and reachability

The trigger is the pass of phase 0x101 that starts with the timer at 149, the
150th. Every complete run of the task makes it. No input and no game state
enters:

* Phase 0 sets the timer to 10 (0x08116758). Phase 0x100 decrements it on
  every pass and goes on when it reaches 0, so phase 0x101 starts at 0.
* Phase 0x101 ends only when the stepped timer is above 149
  (0x08116864-0x08116868). That takes 150 passes, and the last one indexes
  with 150.
* The curve pointers come from the ROM tables `data_083A4AE4` and
  `data_083A4314`; phase 0 copies them into the payload.

Who starts the task:

* Its address appears once in the ROM, in the pool word 0x081169F0 of
  `func_081168B4`, which creates it in its phase 0x101 (bl `func_08005B6C` at
  0x081169E4, payload 0x16C bytes) once a 60-pass delay has run out
  (0x081169B2). There is no BL to 0x08116514.
* `func_081168B4` is an effect. It is the callback of the registry entry at
  0x083951A0, `data_083947D8[0x139]`, effect id 0x13A for `func_080D3508`
  (`src/080D3508.c`). Its address appears nowhere else in the ROM, and no BL
  calls it.

Not established: which animation of the game effect 0x13A is, and how often
play asks for it. Whenever it runs and this child completes, the reads
happen.

## Behaviour against correct behaviour

"Fixed" is the `-DBUGFIX` build. Pass numbers are those of `repro.py`, which
counts from the parent's phase 0x100; this task's phase 0x101 is passes 71 to
220.

| pass of phase 0x101 | timer on entry | ROM reads | ROM writes | fixed |
|---|---|---|---|---|
| 1 | 0 | entry 1 of each curve | BG2 offset, 24 positions, 8 scales from entry 1 | the same |
| ... | | | | |
| 149 | 148 | entry 149 | from entry 149; BG2 vertical offset 0xFFFB (-5) | the same |
| 150 | 149 | entry 150 of each curve: 34 reads, all outside their curve | BG2 vertical offset 0; 24 positions at the pieces' creation y + 0 or 1; scales 0x0100 or 0xFF00 | no reads, no positions, no scales; BG2 offset stays 0xFFFB |

On passes 1 to 149 the two builds make the same reads and the same calls, and
no byte of the payloads, the object pool or the LCD register image differs
between them.

On pass 150 both builds then remove the 24 pieces (`func_080D5F74`, which
unlinks each with `func_08011428`), clear the payload's object pointers, clear
DISPCNT bit 15 and go to phase 0x102. Afterwards the only bytes that differ
are inside the freed object slots (the positions and scales the ROM wrote just
before the removal) and BG2's vertical offset in the register image: 0 in the
ROM, 0xFFFB in the fixed build.

## Impact

None visible. This comes from the code and from running the ROM's own code
under emulation, not from watching the game.

A pass, as in `docs/bugs/08114910/`, is what `func_080D36B0` does in its state
1: the effect task manager (`func_08005A24`), the object update
(`func_08010DD0`) and the object draw walk (`func_080D3024`), which hands each
linked object to the sprite routines `func_080018A0` and `func_08001F34`.

**The pieces.** The positions and scales computed from entry 150 are stored
into the 24 objects, and the same call then removes them. `func_08011428`
takes each off its list and clears its state byte, so the draw walk after that
pass hands nothing to the sprite routines, in either build. On every one of
the 225 passes the repro runs, every word the draw walk hands the sprite
routines is the same in the two builds. The 24 pieces are drawn on passes 61
to 219, and on no pass after.

**BG2.** The one value from outside a curve that outlives the pass is BG2's
vertical offset, which `func_080D7468` writes into the LCD register image
`g_control_flags_03000940` (+0x14). By then BG2 is off:

* the parent turned BG2 on and set its offset to 0 on pass 1, through
  `func_080D7220(data_088F63D8, 0, 2, 0, 0, 0)` (bl at 0x0811698A);
* on the same pass it started the blend sequence `data_0894DCE4` (bl
  `func_080D3E9C` at 0x08116992): three steps of 30, 20 and 160 passes. Run
  from the ROM, it ends on pass 211;
* in its phase 0x102 the parent checks that sequence first
  (`func_080D3F08`, bl at 0x081169F6) and, as soon as it has ended, clears
  BG2's DISPCNT bit (`func_080035A8(2)`, 0x08116A00-0x08116A0C). That happens
  on pass 212, and BG2 stays off for the rest of the run;
* the ROM writes the offset from outside the curve on pass 220, 8 passes
  later.

The register images of the two builds differ only in that halfword, and only
after pass 220, when BG2 is off in both. The 0 the ROM leaves behind is the
offset BG2 was given when the effect set it up on pass 1, not a new value.

The 8-pass margin rests on when each task starts relative to the others. The
repro models the runner as `src/08005954.c`, `src/08005B6C.c` and
`src/08005A24.c` have it: a child created during a pass runs its phase 0 at
creation and its first phase 0x100 pass later in the same pass, after its
parent. If that model were a pass or two out, the margin would still not
close.

Not established:

* any of this in a running game or in a full-system emulator;
* which animation of the game effect 0x13A is, and how often play asks for it;
* that `func_080D36B0` state 1 runs once per displayed frame;
* the other two children of the parent. The repro does not run the palette
  animation (`func_080D4704`, callback `func_080D449C`) or the sound sequence
  (`func_080DFD8C`, callback `func_080DFB0C`); from their sources, neither
  writes the LCD register image;
* whether any later code turns BG2 back on without setting its offset first.
  If some did, the ROM's leftover offset is 0, and the fixed build's would be
  0xFFFB;
* the object copy routine: `data_0836D4BC[0]` runs from IWRAM, where the
  emulated machine has no code, so the repro supplies a byte copy for it.

## Developer intent

The intent was the animation the ROM draws: each piece and BG2 follow their
curves from entry 0 to entry 149, once each, and then the pieces disappear.

The likely mistake is an off-by-one bound, the same as in `func_08114910`
(`docs/bugs/08114910/`), another effect callback of this module. The phase was
given one pass per curve entry, 150, and the lookups were written on every
pass, including the one that only removes the pieces. But entry 0 is already
on screen when the phase starts, so only 149 lookups have an entry to fetch
and a pass on which it is drawn.

Evidence:

* Entry 0 is the state the set-up gives:
  * phase 0 reads entry 0 of the scale curves itself, as each scaled piece's
    first scale (`ldrh` at 0x081166B6 and 0x081166D6; every scale curve
    starts at 0x0100 or 0xFF00);
  * BG2 starts at offset 0, which is entry 0 of the BG2 curve;
  * phase 0 places each piece at its row's position with no offset, and 11 of
    the 13 byte curves start at 0. The two others start at 1, so pieces 1 and
    8 are drawn one pixel above their entry 0 before phase 0x101 starts; that
    is in the ROM either way and does not depend on this bound.
  Stepping before the lookup is what makes the first pass fetch entry 1 rather
  than repeat entry 0.
* The repro checks that, on passes 1 to 149, the y the ROM passes for every
  piece is its creation y plus entry t of its curve, where t is the pass.
* The curves end on plateaus (the last entries of each byte curve are equal:
  5, 10, ... 100), and the ROM draws entry 149 on the last pass before the
  removal.
* `func_08117B9C` is the same code on a copy of the same curves and makes the
  same extra pass.

What the developer would have written cannot be proved from the ROM. The fix
below is the smallest change that removes the reads and leaves every drawn
value as it is.

## The fix

```c
        payload->timer++;
#ifdef BUGFIX
        if (payload->timer > 0x95)
            goto finish;
#endif
        func_080D7468(data_088F63D8, 2, 0, data_083A4344[payload->timer]);
        for (j = 0; j < 24; j++) {
            ...
        }
#ifdef BUGFIX
    finish:
#endif
        if (payload->timer > 0x95) {
            func_080D5F74(payload->objects, 24);
```

On the pass whose stepped timer is past the curves, the fixed build goes
straight to the removal. Passes 1 to 149 are untouched. Measured by
`repro.py`:

* the fixed build reads entries 1 to 149 and nothing outside the curves;
* on pass 150 it makes no read, no `func_080D7468`, `func_080107D4` or
  `func_080112CC` call, and removes the pieces as the ROM does;
* every word handed to the sprite routines is the same as in the ROM on every
  pass, and so is the LCD register image while BG2 is on.

The default build is unchanged: `match.py` reports it byte identical (928/928
bytes), and `repro.py` links it at 0x08116514 and requires it to equal the
ROM's bytes. The `-DBUGFIX` build is 936 bytes.

### Rejected alternative: step the timer after the loop

Moving `payload->timer++` after the loop also keeps every read inside the
curves: the 150 passes read entries 0 to 149. It was measured with the same
harness, on a build whose `BUGFIX` arm was that change, and it changes what is
drawn:

* the sprite draws differ from the ROM's on all 149 passes 71 to 219, the
  passes that draw the moving pieces: every entry arrives one pass late;
* entry 0 is drawn again on the first pass, and entry 149 is computed on the
  removing pass and never drawn;
* BG2's offset differs from the ROM's on passes where BG2 is on, the first
  being pass 84.

A change that moves 149 drawn frames is not a repair of reads that draw
nothing.

## Reproduction

`repro.py` does the following:

1. Links the default build at 0x08116514 and requires it to equal your ROM's
   928 bytes.
2. Checks the curve layout in your ROM.
3. Runs the effect pass by pass from the parent's phase 0x100, once with the
   ROM bytes and once with the `-DBUGFIX` build, each in its own machine, for
   225 passes. The parent `func_081168B4` and the blend sequence run from the
   ROM; a pass ends with the ROM's `func_08010DD0` and `func_080D3024`.
4. Records every read from the curves made by this task, every
   `func_080107D4` and `func_080112CC` call it makes, every object it
   unlinks, every word the draw walk hands the sprite routines, and the LCD
   register image after each pass.

It fails if any of these stops being true: the ROM bytes read entry 150 of
every curve on the removing pass; the fixed build reads nothing on it; BG2 is
off when the ROM writes the offset from outside the curve; the drawn values,
and the register image while BG2 is on, are the same in both builds.

The objects are made by the ROM's own creator and allocator and removed by the
ROM's `func_080D5F74` and `func_08011428`. Stubs: the two sprite routines, the
IWRAM copy routine, and the task starts and removals that the Python runner
does itself (see the docstring). Requires unicorn and the repository
toolchain (see the docstring).

```
$ python3 docs/bugs/08116514/repro.py baserom.bin
source src/08116514.c: default build == ROM bytes [08116514, 081168B4)

1. The curves.  Thirteen byte curves and four s16 scale curves, 150
   entries each, back to back; the byte after the last byte curve is pad.
  [ok] byte curves end at the pad: True
  [ok] scale curves (data_083A4314's non-null words) are 300 bytes apart and end at the table: ['083A3E64', '083A3F90', '083A40BC', '083A41E8', True]
  [ok] every piece row of data_083A4AE4 points at the start of a byte curve: True
  byte curves, entries 149 and 150 (150 = the next curve's entry 0, or the pad):
    5|0  10|0  15|0  20|0  25|0  30|0  40|0  45|0  50|0  60|0  70|1  80|1  100|0
  scale curves, entries 0, 149 and 150:
    0100 0155 0100  0100 0200 FF00  FF00 FEAB FF00  FF00 FE00 0000
  [ok] entry 0 of every scale curve is +-0x100, the scale of an unscaled sprite: [256, 256, 256, 256]

2. The effect, pass by pass (pass 1 = the parent's phase 0x100).
  [ok] parent passes in phase 0x101 before it starts this task (state->delay = 60, 0x081169B2): 60
  [ok] ROM    pass that starts this task (phase 0, then its first phase 0x100 pass); timer after it: ([61], 9)
  [ok] ROM    passes it starts in phases 0x100, 0x101, 0x102 (first..last): [(62, 70), (71, 220), (221, 221)]
  [ok] BUGFIX pass that starts this task (phase 0, then its first phase 0x100 pass); timer after it: ([61], 9)
  [ok] BUGFIX passes it starts in phases 0x100, 0x101, 0x102 (first..last): [(62, 70), (71, 220), (221, 221)]
  [ok] ROM / BUGFIX the pass on which the blend sequence ends (its phase becomes 2): [[211], [211]]
  [ok] ROM / BUGFIX the pass on which the parent removes it: [[212], [212]]
  [ok] ROM / BUGFIX passes after which BG2 is on (DISPCNT bit 10 in the register image): [(1, 211), (1, 211)]

3. Trigger: pass 220, this task's 150th pass of phase 0x101, which removes
   the pieces.
  [ok] ROM / BUGFIX timer on entry: (149, 149)
  [ok] ROM    index every lookup uses (the stepped timer): 150
  [ok] ROM    lookups; each lands at or past the end of its own curve: (34, True)
  [ok] ROM    the BG2 curve's lookup: address, value (the next curve's entry 0): ('083A43DA', 0)
  [ok] ROM    scale lookups (address, value): [('083A3F90', '0100'), ('083A40BC', 'FF00'), ('083A41E8', 'FF00')]
  [ok] ROM    BG2 vertical offset before / after this pass: 'FFFB 0000'
  [ok] ROM    calls made with the values read: func_080107D4, func_080112CC (scaled pieces): [24, 8]
  [ok] BUGFIX lookups; func_080107D4 and func_080112CC calls: ([], [])
  [ok] BUGFIX BG2 vertical offset after this pass (unchanged): 'FFFB'
  [ok] ROM    objects unlinked in this pass (func_080D5F74 -> func_08011428): 24
  [ok] BUGFIX objects unlinked in this pass (func_080D5F74 -> func_08011428): 24
  [ok] ROM    payload->objects after it; state bytes of the 24 objects: (True, True)
  [ok] BUGFIX payload->objects after it; state bytes of the 24 objects: (True, True)
  [ok] ROM / BUGFIX sprites drawn after this pass and after the next five: [0, 0]
  The parent turns BG2 off on pass 212; the ROM writes the offset from
  outside the curve on pass 220, 8 passes later.
  [ok] BG2 on after this pass, in either build: False

4. All of phase 0x101.  Passes 1 to 149 are the same in both builds.
  [ok] ROM    timer on entry: first pass, last pass, one more on each pass: (0, 149, True)
  BG2 vertical offset after passes 70, 71, 211 (the last with BG2 on) and 219: 0000 0000 FFFB FFFB
  [ok] ROM    lookup index: first pass, last pass, one more on each pass: (1, 150, True)
  [ok] BUGFIX lookup index: first pass, 149th pass, one more on each pass; 150th pass: ((1, 149, True), None)
  [ok] ROM    y passed to func_080107D4 on pass t = phase 0's y + entry t of the piece's curve, t = 1..149: True
  [ok] ROM / BUGFIX every lookup inside its curve: [False, True]
  [ok] passes 1..149: same lookups, same calls; bytes that differ between the builds: (True, True, 0)

5. What reaches the screen: every word handed to the sprite routines and
   the LCD register image, after every pass of the run.
  [ok] passes compared; passes whose sprite draws differ: (225, [])
  [ok] ROM    passes with the 24 pieces drawn (first, last); passes with some other count: (61, 219, [])
  [ok] BUGFIX passes with the 24 pieces drawn (first, last); passes with some other count: (61, 219, [])
  [ok] passes whose register images differ, and where: (220, 225, ['+0x14', '+0x15'])
  [ok] BG2 on, on any of those passes: False
  [ok] bytes that differ between the builds after the trigger pass: in freed objects, BG2VOFS, other: (True, ['03000954', '03000955'], [])

6. Non-trigger: one pass of phase 0x101 from timer 74, in fresh machines.
  [ok] ROM / BUGFIX lookup index: [75, 75]
  [ok] same lookups, calls and draws; bytes that differ between the builds: (True, True, True, [])

all assertions hold
```
