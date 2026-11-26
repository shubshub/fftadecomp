# func_081104DC: the last pass of phase 0x102 reads every scale table one entry past its end

**Status: reached on every complete run of this task; nothing of it is
drawn.** The out-of-range reads are shown by executing the ROM's own bytes.
That none of the values read reaches the sprite routines is shown by running
the ROM's object update and draw walk after every pass, under emulation.
Neither has been observed in a running game or in a full-system emulator.

It is the same mistake as in `func_08114910` (`docs/bugs/08114910/`). That
function's table ends at 0x083A39CE, and these tables begin at 0x083A39D8,
after the 10-byte script `data_083A39CE`.

## The bug

`func_081104DC` is a task callback that `func_08110888` starts. Its phase
0x101 creates 11 rotating sprite objects from the 20-byte rows of
`data_083A2FD8` and 14 moving ones from `data_083A30F0`, and starts each of
them on a 60-step motion. Phase 0x102 then moves them for 60 passes. Each
pass steps a counter once. Then, for each rotating object, it steps the
motion, sets the position, turns the object and looks its x and y scale up in
the tables its row names, or uses 0x0100 where the row names none:

```
08110710  mov  r3, r8             ; payload
08110712  ldrh r0, [r3]           ; payload->counter
08110714  adds r0, #1
08110716  strh r0, [r3]           ; counter++, before the lookups
          ; for each of the 11 rotating objects (0x0811071A-0x081107C0):
08110736  bl   func_080E064C      ; step the x motion; 0x0811073E the y motion
0811074E  bl   func_080107D4      ; position
0811075C  strh r0, [r4, #0x1C]    ; angle += the row's spin (0x08110752-0x0811075C)
08110762  ldr  r2, [r5, #8]       ; the row's x table, 0 for none
0811076A  ldrh r0, [r3]           ; the stepped counter
08110770  ldrh r1, [r0]           ; x_table[counter] (0x0811076C-0x0811076E)
08110776  ldr  r3, [r5, #0xC]     ; the row's y table, 0 for none
0811077E  ldrh r0, [r2]           ; the stepped counter
08110784  ldrh r2, [r0]           ; y_table[counter] (0x08110780-0x08110782)
08110792  bl   func_080112CC      ; object: x scale, y scale, angle
08110798  bl   func_080E0690      ; has the x motion ended?
081107A4  bl   func_08011428      ; yes: unlink the object
081107AA  str  r3, [r4]           ; and clear the pointer to it
          ; the same for the 14 moving objects, without tables (0x081107C2-0x0811081E)
08110820  ldr  r1, [sp, #0x10]    ; have all 25 ended?
0811083A  strb r0, [r1]           ; then the status byte = 7 (0x08110834); phase = 0x103
```

The tables are seven arrays of 60 halfwords, back to back at
0x083A39D8-0x083A3D1F, one every 0x78 bytes. The rows of `data_083A2FD8`
name six of them. The seventh, 0x083A3B40, is named only by the rows of
`data_083A3264`, which `func_0811166C` uses (`src/0811166C.c`). Every pointer
to the tables in the ROM is in one of those two row tables. An entry is
256 / size, the 8.8 reciprocal an affine sprite takes: 0x0100 is size 1, and
a negative entry is a mirrored sprite. Each table starts at size 1, and its
size moves in equal steps to the end of its shape:

| table | entries 0 to 59: size | entry 59 |
|---|---|---|
| 0x083A39D8 | 1 to 2 | 0x0080 |
| 0x083A3A50 | 1 to 1/2 | 0x0200 |
| 0x083A3AC8 | 1 to 1/4 | 0x0400 |
| 0x083A3B40 (not used here) | 1 to 1/16 | 0x1000 |
| 0x083A3BB8 | 1 to 1/16 over entries 0-29, then -1/16 to -1 | 0xFF00 |
| 0x083A3C30 | 1 to 1/16 over entries 0-19, then -1/16 to -1 | 0xFF00 |
| 0x083A3CA8 | 1 to 1/16 over entries 0-39, then -1/16 to -1/2 | 0xFE00 |

Of the 420 entries, 414 are 256 / size(k) truncated toward zero. The other 6
are one nearer zero, each at a k where 256 / size(k) is a whole number.
`repro.py` checks all 420 entries of your ROM against that form.

The counter is 0 when the phase starts and is stepped before the lookups, so
the 60 passes read entries 1 to 60. There is no entry 60. The 60th pass, the
one that goes on to unlink the objects, makes 19 lookups: 9 x and 10 y,
because object 5 has no tables and object 1 no x table. Each reads the
halfword after its table:

* For five of the six tables that is the next table's entry 0, 0x0100. For
  0x083A3AC8 the next table is 0x083A3B40, the one this function does not
  use.
* For 0x083A3CA8, object 7's y table, it is 0x000A at 0x083A3D20, the first
  halfword of `data_083A3D20`. The only reference to 0x083A3D20 in the ROM is
  the pool word at 0x081158C8 in `func_0811584C`, which copies the 20 bytes
  there as its effect settings (`src/0811584C.c`).

The other 59 passes read entries 1 to 59. Entry 0, 0x0100, is the scale
phase 0x101 gives every object (see Impact), so each table is otherwise used
in full.

## Trigger and reachability

The trigger is the pass of phase 0x102 that starts with the counter at 59,
which is the 60th. Every complete run of the task makes that pass. No input
and no game state enters:

* The payload is cleared when the task is created. `func_08005954`
  allocates the payload size plus 0x1C bytes (0x08005968-0x08005970) and
  clears all of them through `g_callbacks_0836D4B8[0]`
  (0x0800597C-0x08005984). That is the IWRAM copy of the zero fill
  `func_08A38A2C` (`src/08A38A2C.c`, `docs/cartridge.md`). The function then
  runs phase 0 and sets the stored phase to 0x100 (0x08005A0C-0x08005A10).
* Phases 0, 0x100 and 0x101 do not write the counter. Phase 0 stores the
  status pointer at payload +4 (0x0811051A-0x08110520), and phase 0x101
  writes the objects, the motions and the task pointers. Phase 0x102
  therefore starts at 0.
* Every motion lasts 60 steps. Phase 0x101 starts all 50 of them (x and y of
  25 objects) with `func_080E0608(..., 60)` (`movs r3, #0x3C` at 0x081105EE,
  0x08110600, 0x08110652 and 0x08110662). `func_080E064C` counts a motion's
  remaining steps down, and `func_080E0690` reports when they reach 0
  (`src/080E064C.c`, `src/080E0690.c`). So every object is unlinked on the
  60th pass. The phase ends when all of them have been (0x08110820-0x08110824),
  so it lasts exactly 60 passes, and the last one indexes with 60.
* Between passes the phase is kept by the task runner, which copies the
  task's state into the event before the callback and back after it
  (`src/08005A24.c`). The counter is in the task's own payload.

`repro.py` does not set this state by hand. It fills the task's memory with
0xA5, clears it with the ROM's own zero fill, runs phase 0 as the creator
does, and then calls the ROM bytes once per pass, as the runner does. It
records every write to the counter. Before phase 0x102 the only one is the
zero fill's. In phase 0x102 the only ones are the `strh` at 0x08110716,
storing 1 to 60.

Who starts the task:

* Its address appears once in the ROM, in the pool word 0x08110F38 of
  `func_08110888`. That function creates the task in its phase 0x107 with a
  0x35C-byte payload (0x08110F18-0x08110F20, `src/08110888.c`), and passes its
  status pointer as the descriptor's +4. There is no BL to 0x081104DC.
* `func_08110888` cannot finish before the task does. Its phase 0x109 goes on
  only once `func_080E051C` has removed the task, which it does when the
  task's stored phase is 2 (`src/080E051C.c`, `src/08005BB0.c`). This task
  sets 2 in its phase 0x103, after phase 0x102 has run to its end.
* `func_08110888` is started once. Its address appears only in the pool word
  0x08111230 of `func_08110FE0`, which creates it in its phase 0x104 (bl
  `func_08005B6C` at 0x0811121C). No BL calls it.
* `func_08110FE0` skips the children it creates in phases 0x101 to 0x104,
  `func_08110888` among them, when the halfword at +0x16 of its request is
  set. Phase 0 copies that halfword to its payload's +7
  (0x08111050-0x08111052), and phase 0x100 then goes to 0x105 without
  starting them (0x0811108A-0x081110A6).
* `func_08110FE0` is an effect. It is the callback of the registry entry at
  0x08395170, which is `data_083947D8[0x133]`, effect id 0x134 for
  `func_080D3508` (`src/080D3508.c`). It is also the second callback of
  `data_083A60C8` (0x083A60CC), which `func_0811896C` starts for request
  value 0x34 (`src/0811896C.c`). No BL calls `func_08110FE0` either.

Not established: which animation of the game this effect is, and how often
play asks for it. Whenever it runs with that halfword clear and this task
completes, the reads happen.

## Behaviour against correct behaviour

`func_080112CC(object, x, y, angle)` is three stores, to the object's +0x32,
+0x34 and +0x36 (0x080112CC-0x080112D0). The values below are object 7's
(x table 0x083A3A50, y table 0x083A3CA8, spin 0xFF00). The other ten objects
follow the same pattern with their own tables. "Fixed" is the `-DBUGFIX`
build. The pass numbers in brackets are those of `repro.py`, which counts
phase 0x100 as pass 1.

| pass of phase 0x102 | counter on entry | ROM reads | ROM stores for object 7 (x, y, angle) | fixed |
|---|---|---|---|---|
| 1 (3) | 0 | entry 1 of each table, 19 reads | 0x0102, 0x0106, 0xFF00 | the same |
| 2 (4) | 1 | entry 2 | 0x0104, 0x010C, 0xFE00 | the same |
| ... | | | | |
| 59 (61) | 58 | entry 59 | 0x0200, 0xFE00, 0xC500 | the same |
| 60 (62) | 59 | entry 60 of each table: 19 reads, all outside their table | 0x0100, 0x000A, 0xC400 | no reads, no stores |

On passes 1 to 59 the two builds make the same reads and the same calls.
After each of those passes no byte differs between them in the payload, the
event, the status byte, the object pool or the LCD register image.

On pass 60 both builds set the status byte to 7 and the phase to 0x103,
unlink all 25 objects, clear every object pointer in the payload, and return
0. The unlinked objects have state byte 0, and nothing is drawn after the
pass. The only bytes that differ afterwards are inside the 11 freed rotating
slots: the scales and the high byte of the angle (+0x32 to +0x35 and +0x37;
every spin is a multiple of 0x100). For object 7 they are 0x0100, 0x000A,
0xC400 in the ROM, and 0x0200, 0xFE00, 0xC500 in the fixed build, which are
the values of pass 59.

## Impact

None visible. This comes from the code and from running the ROM's own object
code under emulation, not from watching the game.

A pass, as in `docs/bugs/08114910/`, is what `func_080D36B0` does in its
state 1 (`src/080D36B0.c`). It runs the effect task manager
(`func_08005A24`), the object update (`func_08010DD0`) and the object draw
walk (`func_080D3024`). The draw walk hands each linked object to the sprite
routines `func_080018A0` and `func_08001F34`. For a rotating object like
these it hands `func_080018A0` the object's +0x32, +0x34 and +0x36
(0x080D30B0-0x080D30C4).

**The values from outside the tables are never drawn.**

* `func_080112CC` only stores them.
* The same pass then unlinks each object (0x081107A4) and clears the pointer
  to it (0x081107AA). `func_08011428` takes the object off its list and
  clears its state byte, and the iterator skips objects whose state byte is
  0 (0x0801169C-0x080116A0).
* In the repro, the draw walk hands nothing to the sprite routines after
  that pass, in either build, or after any of the four passes that follow.
* The stale 0x000A does not outlive the slot. The allocator copies a 64-byte
  template, `data_08149828`, over a slot before it hands it out
  (0x080109C0-0x080109C8). In the repro, the ROM's allocator gives the slot
  that held 0x000A out again with x and y scale 0x0100.

Going by the tables' own form, had these values been drawn, the objects
would have jumped back to size 1 (0x0100) for one frame at the end of their
change, and object 7's y size would have been 25.6 (0x000A) straight after
-1/2. That is a reading of the tables. What `func_080018A0` does with the
values was not analysed.

**The 59 lookups before them draw the whole of every table.** Phase 0x101
gives every rotating object x and y scale 0x0100 and angle 0, with
`func_080112CC(object, 0x100, 0x100, 0)` (0x081105D4-0x081105E0), and 0x0100
is entry 0 of every table. The objects are drawn once with those values,
after the pass that creates them and before phase 0x102 begins. The ROM then
stores entries 1 to 59 on the next 59 passes. So what the draw walk hands
`func_080018A0` for each object, pass by pass, is its tables from entry 0 to
entry 59, once each, with the angle advanced by the object's spin on every
pass. For object 7, every fourth entry and the last:

```
x scale  0100 0108 0112 011C 0128 0134 0141 014F 015F 0170 0183 0198 01AF 01C9 01E7 0200
y scale  0100 011B 013C 0167 019F 01ED 025D 030F 0455 076D F000 F989 FBF3 FD0D FDAE FE00
```

The fixed build draws exactly the same. `repro.py` compares every word the
draw walk hands the two sprite routines on all 66 passes it runs, and none
differs. There are 11 scaled and 14 plain draws on each of passes 2 to 61,
and none on the others.

Not established:

* any of this in a running game or in a full-system emulator;
* which animation of the game this effect (id 0x134) is, and how often play
  asks for it;
* that `func_080D36B0` state 1 runs once per displayed frame;
* what `func_080018A0` does with the scale and angle words it is handed;
* the callees of phases 0, 0x101 and 0x103 that set up the screen or start
  and end other tasks. The repro replaces them with stubs (see its
  docstring). None of them is called in phase 0x102, and both builds call
  them identically;
* the copying of the IWRAM routines. The repro copies the same 176 bytes
  the installer copies, from 0x08A38A2C to 0x03005E78
  (`docs/cartridge.md`), and runs the zero fill and the object copy routine
  from there.

## Developer intent

The intent was the animation the ROM draws. Each object grows, shrinks or
flips through the 60 keyframes of its tables, from size 1 to the end of the
table's shape, while it moves and turns, and then disappears.

The likely mistake is an off-by-one bound, the same as in `func_08114910`
(`docs/bugs/08114910/`) and `func_08116514` (`docs/bugs/08116514/`), effect
callbacks of the same module. The phase was given one pass per motion step,
60, and the lookups were written on every pass, including the one that only
unlinks the objects. Counted from the pass that creates them, the objects
are drawn 60 times. Entry 0 comes with the objects and entries 1 to 59 come
from the first 59 lookups. So only 59 lookups have a keyframe to fetch and a
pass on which it is drawn. The 60th has neither.

Evidence:

* Entry 0 is the state the set-up gives. Phase 0x101 sets every rotating
  object's scale to 0x0100 explicitly, and every table starts at 0x0100.
  Stepping the counter before the lookup is what makes the first lookup
  fetch entry 1 and not repeat it.
* The counter is handled like the motions next to it, which are stepped
  first and read afterwards on the same pass (0x08110736-0x0811074E). On
  drawn pass k, the position is step k of the motion and the scale is entry
  k of the table, both counted from the creation values.
* Each table reaches the end of its shape exactly at entry 59: size 2, 1/2,
  1/4, 1/16, -1, -1 and -1/2. The ROM draws that entry on its last drawn
  pass.
* The same excess pass shows in the motions. Their 60th step, the end
  position the row gives, is computed on the pass that unlinks the objects,
  and it is never drawn. That is harmless, because the interpolator has a
  value for step 60. The tables have none for entry 60.

`func_0811166C`, in the same module, uses the same seven tables through its
own rows, `data_083A3264`, and makes the lookups first and the step
afterwards (`src/0811166C.c`, lines 130-135 and 150):

```c
            scale_x = 0x100;
            if (data_083A3264[index].scale_x != 0)
                scale_x = data_083A3264[index].scale_x[payload->counter];
            ...
        payload->counter++;
```

That is weak evidence for what was meant here, for two reasons:

* It shows an order, not a count that comes out even. That phase ends when a
  palette animation ends (`func_080D4774`, line 151), not after a count of
  passes. How many entries it reads depends on that animation, which was not
  measured.
* In this function that order does not give the animation the ROM draws. It
  is the rejected alternative below.

What the developer would have written cannot be proved from the ROM. The fix
below is the smallest change that removes the reads and leaves every drawn
value as it is.

## The fix

```c
            object->rotation += definition->rotation;
#ifdef BUGFIX
            if (payload->counter >= 60)
                goto check_end;
#endif
            x_scale = 0x100;
            if (definition->x_scale != 0)
                x_scale = definition->x_scale[payload->counter];
            y_scale = 0x100;
            if (definition->y_scale != 0)
                y_scale = definition->y_scale[payload->counter];
            rotation = object->rotation;
            func_080112CC(object->object, x_scale, y_scale, rotation);
#ifdef BUGFIX
        check_end:
#endif
            if (func_080E0690(&object->x_motion)) {
```

When the stepped counter is past the end of the tables, the fixed build
skips the lookups and the `func_080112CC` call and goes straight to the test
that unlinks the object. This is the form of `docs/bugs/08116514/`: there is
more than one statement to skip, and the test that unlinks the object has to
stay.
Passes 1 to 59 are untouched. The bound is the table length, which is what
keeps the reads in range. Every motion is 60 steps, so in this ROM the test
picks the same pass as the end of the x motion does. Measured by `repro.py`:

* the fixed build reads entries 1 to 59 and nothing outside the tables;
* on pass 60 it makes no read and no `func_080112CC` call, and it unlinks
  the 25 objects as the ROM does;
* every word handed to the sprite routines is the same as in the ROM, on
  every pass.

The skipped call also carried the angle of pass 60. That store is dropped
with it, and, like the scales, it was never drawn.

The default build is unchanged: `match.py` reports it byte identical
(940/940 bytes), and `repro.py` links it at 0x081104DC and requires it to
equal the ROM's bytes. The `-DBUGFIX` build is 944 bytes. After the angle is
stored it tests the counter (`ldrh`, `cmp r0, #0x3B`, `bhi` to the end
test), and its register allocation differs around that test: the flag that
records whether all objects have ended is kept in a register, not in a stack
slot.

### Rejected alternative: `x_scale[payload->counter - 1]`

Indexing with the counter before the step, which is what the order in
`func_0811166C` amounts to, also keeps every read inside the tables: the 60
passes read entries 0 to 59. It was measured with the same harness, on a
build whose `BUGFIX` arm was that index in both lookups, and it changes what
is drawn:

* The draw walk's output differs from the ROM's on 59 of the 60 passes that
  draw the objects, passes 3 to 61: every keyframe after the first arrives
  one pass late.
* Entry 0 is drawn twice, once from the set-up and once from the tables.
* Entry 59 is stored on the pass that unlinks the objects and is never
  drawn. Each object stops one keyframe short of the end of its shape:
  object 7 last shows 0x01F7 and 0xFDE8 instead of 0x0200 and 0xFE00.

A change that moves 59 drawn frames and drops the last keyframe is not a
repair of reads that draw nothing. To see it, put that index in the `BUGFIX`
arm and run `repro.py`: its comparison of the drawn values fails and lists
passes 3 to 61.

## Reproduction

`repro.py` does the following:

1. Links the default build at 0x081104DC and requires it to equal your
   ROM's 940 bytes.
2. Checks the seven tables of your ROM against their shapes, and the rows
   that name them.
3. Creates the task as `func_08005954` does: it fills the task's memory with
   0xA5, clears it with the ROM's zero fill and runs phase 0. It then runs
   the ROM bytes and the `-DBUGFIX` build pass by pass, each in its own
   machine, for 66 passes: phases 0x100 and 0x101, the 60 passes of phase
   0x102, phase 0x103 and three more. A pass is one call of the function with
   the stored phase, then the ROM's `func_08010DD0` and `func_080D3024`.
4. Records every read from the tables made by this task, every write to the
   counter, every `func_080112CC` call and every unlink it makes, and every
   word the draw walk hands to the sprite routines.
5. Runs single passes of phase 0x102, from counters 29 and 58, in fresh
   machines.

It fails if any of these stops being true: the ROM bytes read entry 60 of
every table they use on the pass that unlinks the objects; the fixed build
reads nothing on it; the drawn values are the same in both builds.

The objects are made by the ROM's own creator and allocator and removed by
the ROM's `func_08011428`. Stubs: the two sprite routines, and the callees of
phases 0, 0x101 and 0x103 that set up the screen or start and end other
tasks (see the docstring). Requires unicorn and the repository toolchain
(see the docstring).

```
$ python3 docs/bugs/081104DC/repro.py baserom.bin
source src/081104DC.c: default build == ROM bytes [081104DC, 08110888)

1. The scale tables: seven of 60 s16, back to back at 0x083A39D8-0x083A3D1F.
  [ok] tables the 11 rows of data_083A2FD8 name (object: x, y; '-' for none): '0:083A3AC8,083A3A50 1:-,083A3A50 2:083A39D8,083A3BB8 3:083A39D8,083A39D8 4:083A3C30,083A3A50 5:-,- 6:083A39D8,083A39D8 7:083A3A50,083A3CA8 8:083A39D8,083A3BB8 9:083A3AC8,083A3A50 10:083A39D8,083A39D8'
  [ok] each named table is one of the seven; the one none of them names: (True, ['083A3B40'])
  [ok] of the 420 entries: equal to 256 / size(k) truncated; one nearer 0 where that is whole: (414, 6)
  [ok] entry 0 of every table; entry 59, the end of its shape: (['0100', '0100', '0100', '0100', '0100', '0100', '0100'], ['0080', '0200', '0400', '1000', 'FF00', 'FF00', 'FE00'])
  [ok] entry 60 of each table this function names: the halfword after it: ['083A39D8:0100', '083A3A50:0100', '083A3AC8:0100', '083A3BB8:0100', '083A3C30:0100', '083A3CA8:000A']
  [ok] that is the next table's entry 0; after 0x083A3CA8 it is 0x083A3D20, past the seventh: ([True, True, True, True, True], '083A3D20')

2. Non-trigger: creation and the two passes before phase 0x102.  Phase 0
   stores the status pointer, 0x100 moves on, 0x101 creates the objects.
  [ok] ROM    (phase, counter) on entry to passes 1, 2, 3: [('0x100', 0), ('0x101', 0), ('0x102', 0)]
  [ok] ROM    writes to payload->counter before phase 0x102: (by, bytes, value): [('zero fill', 4, 0)]
  [ok] ROM    writes to it by the object update and the draw walk, on any pass: []
  [ok] BUGFIX (phase, counter) on entry to passes 1, 2, 3: [('0x100', 0), ('0x101', 0), ('0x102', 0)]
  [ok] BUGFIX writes to payload->counter before phase 0x102: (by, bytes, value): [('zero fill', 4, 0)]
  [ok] BUGFIX writes to it by the object update and the draw walk, on any pass: []
  [ok] table reads in passes 1 and 2; distinct func_080112CC (x, y, angle), and calls: [(0, [], 0), (0, ['0100 0100 0000'], 11)]
  [ok] objects created: rotating, moving; all distinct and nonzero: (11, 14, True)
  [ok] the 11 rotating objects' +0x32, +0x34, +0x36 (x scale, y scale, angle) after pass 2: ['0100 0100 0000']
  [ok] bytes of payload, event, object pool and register image that differ between the builds: []

3. Trigger: pass 62, the 60th of phase 0x102, which unlinks the objects.
  [ok] ROM    (pass, phase, counter) on entry: (62, '0x102', 59)
  [ok] ROM    table reads: 19, by the two lookups, each at index 60 of its own table: (True, True)
  [ok] ROM    reads inside the table they index: 0
   ROM    the 19 reads (object axis: address = value):
     0x:083A3B40=0100  0y:083A3AC8=0100  1y:083A3AC8=0100  2x:083A3A50=0100  2y:083A3C30=0100
     3x:083A3A50=0100  3y:083A3A50=0100  4x:083A3CA8=0100  4y:083A3AC8=0100  6x:083A3A50=0100
     6y:083A3A50=0100  7x:083A3AC8=0100  7y:083A3D20=000A  8x:083A3A50=0100  8y:083A3C30=0100
     9x:083A3B40=0100  9y:083A3AC8=0100  10x:083A3A50=0100  10y:083A3A50=0100
  [ok] ROM    func_080112CC: (x, y, angle) passed to all 11 objects are entry 60 and 60 steps: True
  [ok] ROM    func_080112CC(object 7, x, y, angle): ['0100 000A C400']
  [ok] BUGFIX (pass, phase, counter) on entry: (62, '0x102', 59)
  [ok] BUGFIX table reads; func_080112CC calls: ([], [])
  [ok] ROM    return value; phase after it; the status byte: (0, '0x103', 7)
  [ok] ROM    the 25 objects unlinked in this pass; object pointers left in the payload: (True, [0])
  [ok] ROM    state bytes of the 25 objects; sprites drawn after this pass: ([0], 0)
  [ok] BUGFIX return value; phase after it; the status byte: (0, '0x103', 7)
  [ok] BUGFIX the 25 objects unlinked in this pass; object pointers left in the payload: (True, [0])
  [ok] BUGFIX state bytes of the 25 objects; sprites drawn after this pass: ([0], 0)
  [ok] x scale, y scale and angle left in object 7's freed slot: ROM, BUGFIX: ('0100 000A C400', '0200 FE00 C500')
  [ok] bytes that differ after this pass: offsets in freed rotating slots; anywhere else: (['+0x32', '+0x33', '+0x34', '+0x35', '+0x37'], [])

4. All of phase 0x102.  Passes 1 to 59 are the same in both builds.
  [ok] ROM / BUGFIX passes in phase 0x102: [60, 60]
  [ok] ROM    counter on entry: first pass, last pass, one more on each pass: (0, 59, True)
  [ok] ROM    stores to the counter in phase 0x102: by; values first, last, one more each: (['08110716'], (1, 60, True))
  [ok] ROM    reads on every pass; pass k reads index k, k = 1..60: (True, True)
  [ok] BUGFIX reads on passes 1..59; pass k reads index k; reads on pass 60: (True, True, 0)
  [ok] ROM / BUGFIX every read inside the table it indexes: [False, True]
  [ok] ROM    func_080112CC on pass k, k = 1..60: entry k of each object's tables, k steps of spin: True
  [ok] passes 1..59: same reads, same calls; bytes that differ between the builds: (True, True, 0)

5. What is drawn.  The draw walk runs after every pass.  Compared here is
   every word it hands the two sprite routines, on all passes of the run.
  [ok] passes compared; passes on which the builds differ: (66, [])
  [ok] ROM    (scaled, plain) draws on passes 2..61; on passes 1 and 62..66: ([(11, 14)], [(0, 0), (0, 0), (0, 0), (0, 0), (0, 0), (0, 0)])
  [ok] ROM    pass 2 + k, k = 0..59: the 11 scaled draws are each object's entry k, k steps: True
  [ok] BUGFIX (scaled, plain) draws on passes 2..61; on passes 1 and 62..66: ([(11, 14)], [(0, 0), (0, 0), (0, 0), (0, 0), (0, 0), (0, 0)])
  [ok] BUGFIX pass 2 + k, k = 0..59: the 11 scaled draws are each object's entry k, k steps: True
  [ok] ROM    draws 000A on any pass: False
   object 7 (x 0x083A3A50, y 0x083A3CA8): the entries drawn on passes 2, 6, ..., 58 and 61
     x  0100 0108 0112 011C 0128 0134 0141 014F 015F 0170 0183 0198 01AF 01C9 01E7 0200
     y  0100 011B 013C 0167 019F 01ED 025D 030F 0455 076D F000 F989 FBF3 FD0D FDAE FE00
   The ROM's allocator rebuilds a freed slot from its template (ROM machine):
  [ok] a new object takes the slot that held 000A; its x and y scale: (True, '0100 0100')

6. Non-trigger: phase 0x103, and single passes of phase 0x102 in fresh machines.
  [ok] pass 63, phase 0x103: ROM / BUGFIX (return, phase after, reads, calls): [(0, '0x2', 0, 0), (0, '0x2', 0, 0)]
  [ok] ROM / BUGFIX stubbed callees: all reached, each only in its own phase: [True, True]
  [ok] counter 29: ROM / BUGFIX (return, phase, counter, reads, calls, unlinks): ((0, '0x102', 30, 19, 11, 0), (0, '0x102', 30, 19, 11, 0))
  [ok] counter 29: reads at index 30; same reads, calls, draws; bytes that differ: (True, True, True, True, [])
  [ok] counter 58: ROM / BUGFIX (return, phase, counter, reads, calls, unlinks): ((0, '0x102', 59, 19, 11, 0), (0, '0x102', 59, 19, 11, 0))
  [ok] counter 58: reads at index 59; same reads, calls, draws; bytes that differ: (True, True, True, True, [])

all assertions hold
```
