# func_08117B9C: the last pass of phase 0x102 reads every curve one entry past its end

**Status: reached on every complete run of this task; nothing of it is
drawn.** The out-of-range reads are shown by executing the ROM's own bytes.
That none of the values read reaches the screen is shown by running the ROM's
object update and draw walk after every pass, under emulation. Neither has
been observed in a running game or in a full-system emulator.

This is the sister of `func_08116514`: the same piece animation and the same
code, on its own copy of the data. The developer-intent argument is
the same, and is given in full in `docs/bugs/08116514/`. This case differs in
one point: this task has no BG2 curve, so the only values read from outside
the curves go to the pieces.

## The bug

Phase 0x100 of `func_08117B9C` creates 24 sprite pieces from the 16-byte rows
of `data_083A5E6C` on its eleventh pass. Phase 0x102 then moves them for 150
passes: on each pass it steps a timer and uses it to index 150-entry curves:

```
08117E9C  ldrh r0, [r7]           ; payload->timer
08117E9E  adds r0, #1
08117EA0  strh r0, [r7]           ; timer++, before the lookups
          ; for each of the 24 pieces (0x08117EC0-0x08117F6C):
08117EE6  ldrb r3, [r2]           ; payload->offsets[j][timer] -> y of func_080107D4, bl at 0x08117EF2
08117F2E  ldrh r0, [r0]           ; data_083A569C[scale_x[j]][timer] } -> func_080112CC,
08117F4E  ldrh r0, [r0]           ; data_083A569C[scale_y[j]][timer] }    for the scaled pieces
08117F70  ldrh r0, [r4]
08117F72  cmp  r0, #0x95
08117F74  bls  return             ; stay in the phase while timer <= 149
08117F7A  bl   func_080D5F74      ; remove the 24 pieces
08117F7E  display &= 0x7FFF ; display &= ~func_080035A8(2) (0x08117F8A) ; phase = 0x103
```

The curves, all from the ROM, are a copy of `func_08116514`'s, byte for byte:

* thirteen byte curves of 150 entries, back to back at 0x083A56CC-0x083A5E69,
  then two zero bytes of pad at 0x083A5E6A and the piece table
  `data_083A5E6C`, whose rows point at the starts of the curves;
* four s16 scale curves of 150 entries, back to back at 0x083A51EC-0x083A569B,
  followed by `data_083A569C`, 12 pointers to them (or 0). The pieces select
  0x083A51EC, 0x083A5318 and 0x083A5444; nothing selects 0x083A5570.

The timer is 0 when phase 0x102 starts and is stepped before the lookups, so
the 150 passes read entries 1 to 150. The 150th pass, the one that removes the
pieces, reads one past the end of every curve it uses: 33 reads (24 piece
offsets, 9 scale values), each the first entry of the next curve or the pad.
The values are those of `func_08116514`'s table: byte curves ending 5, 10, ...
100 read 0, 0, ... 0, 1, 1, 0; the scale curves ending 0x0155, 0x0200 and
0xFEAB read 0x0100, 0xFF00 and 0xFF00.

## Trigger and reachability

The trigger is the pass of phase 0x102 that starts with the timer at 149, the
150th. Every complete run of the task makes it, and no input or game state
enters:

* phase 0 sets the timer to 11 (0x08117C28); phase 0x100 counts it down and,
  at 0, creates the pieces and sets it to 10 (0x08117E6A); phase 0x101 counts
  that down; phase 0x102 starts at 0;
* phase 0x102 ends only when the stepped timer is above 149
  (0x08117F70-0x08117F74): 150 passes, the last indexing with 150.

Who starts the task:

* Its address appears once in the ROM, in the pool word 0x08118268 of
  `func_0811802C`, which creates it with a 0x174-byte payload (bl
  `func_08005B6C` at 0x08118256). There is no BL to 0x08117B9C.
* `func_0811802C` is the callback of the registry entry at 0x083951E0,
  `data_083947D8[0x141]`, effect id 0x142 for `func_080D3508`
  (`src/080D3508.c`). Its address appears nowhere else in the ROM, and no BL
  calls it.

Not established: which animation of the game effect 0x142 is, and how often
play asks for it.

## Behaviour against correct behaviour

"Fixed" is the `-DBUGFIX` build. In `repro.py`, pass 1 is the first pass after
phase 0, and phase 0x102 is passes 22 to 171.

| pass of phase 0x102 | timer on entry | ROM reads | ROM writes | fixed |
|---|---|---|---|---|
| 1 | 0 | entry 1 of each curve | 24 positions, 8 scales from entry 1 | the same |
| ... | | | | |
| 149 | 148 | entry 149 | from entry 149 | the same |
| 150 | 149 | entry 150 of each curve: 33 reads, all outside their curve | 24 positions at the pieces' creation y + 0 or 1; scales 0x0100 or 0xFF00 | no reads, no positions, no scales |

On passes 1 to 149 the two builds make the same reads and the same calls, and
no byte of the payload, the object pool or the LCD register image differs.
On pass 150 both then remove the 24 pieces, clear DISPCNT bit 15 and BG2's bit,
and go to phase 0x103. Afterwards the only bytes that differ are inside the
freed object slots.

## Impact

None visible, from the code and from running the ROM's object code under
emulation (a pass is `func_080D36B0` state 1, as in `docs/bugs/08114910/`).
The positions and scales computed from entry 150 are stored into the 24
objects, and the same call removes them; the draw walk after that pass hands
nothing to the sprite routines, in either build. On all 176 passes the repro
runs, every word the draw walk hands the sprite routines, and the whole LCD
register image, are the same in the two builds. The pieces are drawn on passes
11 to 170 and on no pass after.

Not established:

* any of this in a running game or in a full-system emulator;
* which animation of the game effect 0x142 is, and how often play asks for it;
* that `func_080D36B0` state 1 runs once per displayed frame;
* the blend sequence and the palette animation this task starts in phase 0
  (`func_080D3E9C`, `func_080D4704`): the repro gives them tasks that do not
  end and does not run their callbacks. Neither touches the pieces;
* the object copy routine: `data_0836D4BC[0]` runs from IWRAM, so the repro
  supplies a byte copy for it.

## Developer intent

As for `func_08116514`: the pieces follow their curves from entry 0 to entry
149, once each, and then disappear. Entry 0 is the state the creation gives
(the creation pass reads entry 0 of the scale curves, `ldrh` at 0x08117DAE and
0x08117DCE), and the stepped timer fetches entries 1 to 149 on the next 149
passes. The bound gives the phase one pass per entry, 150, so the extra pass,
which is also the one that removes the pieces, has no entry to fetch. The repro
checks that on passes 1 to 149 the y passed for every piece is its creation y
plus entry t of its curve. The same off-by-one is in `func_08114910`
(`docs/bugs/08114910/`).

## The fix

```c
        payload->timer++;
#ifdef BUGFIX
        if (payload->timer > 0x95)
            goto finish;
#endif
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
straight to the removal. Measured by `repro.py`: it reads entries 1 to 149
and nothing outside the curves, makes no lookup and no call on pass 150, and
draws exactly what the ROM draws on every pass.

The default build is unchanged: `match.py` reports it byte identical
(1168/1168 bytes), and `repro.py` links it at 0x08117B9C and requires it to
equal the ROM's bytes. The `-DBUGFIX` build is 1176 bytes.

Stepping the timer after the loop instead was rejected for the reason given in
`docs/bugs/08116514/`: it keeps the reads in range but draws every entry one
pass late.

## Reproduction

`repro.py` starts the task (phase 0), then runs it pass by pass, once with the
ROM bytes and once with the `-DBUGFIX` build, each in its own machine, for 176
passes, each followed by the ROM's `func_08010DD0` and `func_080D3024`. It
records every read from the curves, every `func_080107D4` and `func_080112CC`
call, every object unlinked, every word handed to the sprite routines, and
the LCD register image after each pass.

It fails if any of these stops being true: the ROM bytes read entry 150 of
every curve on the removing pass; the fixed build reads nothing on it; the
drawn values and the register image are the same in both builds.

The objects are made by the ROM's own creator and allocator and removed by the
ROM's `func_080D5F74` and `func_08011428`. Stubs: the two sprite routines, the
IWRAM copy routine, and the two child tasks phase 0 starts. Requires unicorn
and the repository toolchain (see the docstring).

```
$ python3 docs/bugs/08117B9C/repro.py baserom.bin
source src/08117B9C.c: default build == ROM bytes [08117B9C, 0811802C)

1. The curves.  Thirteen byte curves and four s16 scale curves, 150
   entries each, back to back; the byte after the last byte curve is pad.
  [ok] byte curves end at the pad: True
  [ok] scale curves (data_083A569C's non-null words) are 300 bytes apart and end at the table: ['083A51EC', '083A5318', '083A5444', '083A5570', True]
  [ok] every piece row of data_083A5E6C points at the start of a byte curve: True
  [ok] the curves are func_08116514's, byte for byte: scale curves, byte curves: (True, True)
  byte curves, entries 149 and 150 (150 = the next curve's entry 0, or the pad):
    5|0  10|0  15|0  20|0  25|0  30|0  40|0  45|0  50|0  60|0  70|1  80|1  100|0
  scale curves, entries 0, 149 and 150:
    0100 0155 0100  0100 0200 FF00  FF00 FEAB FF00  FF00 FE00 0000
  [ok] entry 0 of every scale curve is +-0x100, the scale of an unscaled sprite: [256, 256, 256, 256]

2. The task, pass by pass (pass 1 = the first after phase 0).
  [ok] ROM    passes in phases 0x100, 0x101, 0x102, 0x103 (first..last): [(1, 11), (12, 21), (22, 171), (172, 176)]
  [ok] BUGFIX passes in phases 0x100, 0x101, 0x102, 0x103 (first..last): [(1, 11), (12, 21), (22, 171), (172, 176)]
  [ok] pass that creates the pieces (the eleventh of phase 0x100): scale lookups it makes: [('083A51EC', '0100'), ('083A5318', '0100'), ('083A5444', 'FF00')]

3. Trigger: pass 171, the 150th pass of phase 0x102, which removes the pieces.
  [ok] ROM / BUGFIX timer on entry: (149, 149)
  [ok] ROM    index every lookup uses (the stepped timer): 150
  [ok] ROM    lookups; each lands at or past the end of its own curve: (33, True)
  [ok] ROM    scale lookups (address, value): [('083A5318', '0100'), ('083A5444', 'FF00'), ('083A5570', 'FF00')]
  [ok] ROM    calls made with the values read: func_080107D4, func_080112CC (scaled pieces): [24, 8]
  [ok] BUGFIX lookups; func_080107D4 and func_080112CC calls: ([], [])
  [ok] ROM    objects unlinked in this pass (func_080D5F74 -> func_08011428): 24
  [ok] BUGFIX objects unlinked in this pass (func_080D5F74 -> func_08011428): 24
  [ok] ROM    payload->objects after it; state bytes of the 24 objects: (True, True)
  [ok] BUGFIX payload->objects after it; state bytes of the 24 objects: (True, True)
  [ok] ROM / BUGFIX sprites drawn after this pass and after the next five: [0, 0]

4. All of phase 0x102.  Passes 1 to 149 are the same in both builds.
  [ok] ROM    timer on entry: first pass, last pass, one more on each pass: (0, 149, True)
  [ok] ROM    lookup index: first pass, last pass, one more on each pass: (1, 150, True)
  [ok] BUGFIX lookup index: first pass, 149th pass, one more on each pass; 150th pass: ((1, 149, True), None)
  [ok] ROM    y passed to func_080107D4 on pass t = the creation y + entry t of the piece's curve, t = 1..149: True
  [ok] ROM / BUGFIX every lookup inside its curve: [False, True]
  [ok] passes 1..149: same lookups, same calls; bytes that differ between the builds: (True, True, 0)

5. What reaches the screen: every word handed to the sprite routines and
   the LCD register image, after every pass of the run.
  [ok] passes compared; passes whose sprite draws differ: (176, [])
  [ok] ROM    passes with the 24 pieces drawn (first, last); passes with some other count: (11, 170, [])
  [ok] BUGFIX passes with the 24 pieces drawn (first, last); passes with some other count: (11, 170, [])
  [ok] passes whose register images differ: []
  [ok] bytes that differ between the builds after the trigger pass: in freed objects, other: (True, [])

6. Non-trigger: one pass of phase 0x102 from timer 74, in fresh machines.
  [ok] ROM / BUGFIX lookup index: [75, 75]
  [ok] same lookups, calls and draws; bytes that differ between the builds: (True, True, True, [])

all assertions hold
```
