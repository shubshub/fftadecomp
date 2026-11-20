# func_08114910: the shrink phase reads its scale table one entry past the end

**Status: reached on every complete run of this task; nothing of it is
drawn.** The out-of-range read is shown by executing the ROM's own bytes. That
the value read never reaches the sprite routine is shown by running the ROM's
object update and draw walk after every pass, under emulation. Neither has
been observed in a running game or in a full-system emulator.

## The bug

`func_08114910` is a task callback that `func_08115560` starts. In phase 0x105
it turns and shrinks one sprite object over 20 passes. Each pass steps an
interpolator for the angle, steps a counter, and looks the scale up in the
table `data_083A39A6`:

```
08114CE8  bl   func_080E064C      ; step payload->spin
08114CEC  ldrh r0, [r6]           ; payload->counter
08114CEE  adds r0, #1
08114CF2  strh r0, [r6]           ; counter++, before the lookup
08114CF4  ldr  r0, [r6, #0x14]    ; payload->scaled_object
08114CF6  ldr  r2, =0x083A39A6    ; the table (literal at 0x08114D30)
08114CF8  ldrh r1, [r6]           ; the stepped counter
08114CFA  lsls r1, r1, #1
08114CFC  adds r1, r1, r2
08114D00  ldrsh r2, [r1, r3]      ; table[counter]
08114D02  ldrh r3, [r4]           ; (u16)(spin.current << 8), 0x08114D04-0x08114D06
08114D08  adds r1, r2, #0
08114D0A  bl   func_080112CC      ; object: x scale, y scale, angle
08114D0E  ldrh r0, [r6]
08114D10  cmp  r0, #0x13
08114D12  bls  return             ; stay in the phase while counter <= 19
08114D16  bl   func_08011428      ; unlink payload->object
08114D1E  bl   func_08011428      ; unlink payload->scaled_object
08114D24  counter = 10 ; phase = 0x106
```

The table has 20 halfwords, at 0x083A39A6-0x083A39CD. Entry k is
`256 * 608 / (608 - 31 * k)` rounded down, for k = 0..19: it runs from 0x0100
to 0x2000, which is 256 divided by a size that falls in equal steps from 1 to
exactly 1/32. `repro.py` checks all 20 entries of your ROM against that form.

The counter is 0 when the phase starts and is stepped before the lookup, so
the 20 passes read entries 1 to 20. There is no entry 20. The twentieth pass,
the one that goes on to remove the object, reads address 0x083A39CE. That
holds 0x00BF, the first halfword of the next object in the ROM, the 10-byte
script `data_083A39CE`:

* 0x00BF breaks the rising series, and the closed form gives no size for
  k = 20 (the divisor 608 - 620 is negative).
* The only reference to 0x083A39CE in the ROM is the pool word at 0x08115444
  in `func_081151A0`, which passes it to `func_080D3E9C` as a script
  (`src/081151A0.c`). The only reference to the table is the pool word at
  0x08114D30. The object after the script, at 0x083A39D8, has references of
  its own.

The other 19 reads are entries 1 to 19. Entry 0, 0x0100, is the scale a new
object already has (see Impact), so the table is otherwise used in full.

## Trigger and reachability

The trigger is the pass of phase 0x105 that starts with the counter at 19,
which is the twentieth. Every complete run of the task makes that pass. No
input and no game state enters:

* Phase 0x103 sets the counter to 50 (0x08114C6E-0x08114C70). Phase 0x104
  decrements it on every pass and goes on only when it reaches 0
  (0x08114C80-0x08114C8E). Phase 0x105 therefore starts at 0.
* Phase 0x105 ends only when the stepped counter is above 19
  (0x08114D0E-0x08114D12). That takes 20 passes, and the last one indexes
  with 20.
* Between passes the phase is kept by the task runner, which copies the
  task's state into the event before the callback and back after it
  (`src/08005A24.c`). The counter is in the task's own payload.

`repro.py` does not set this state by hand. It starts the ROM bytes in phase
0x103 and calls them once per pass, as the runner does. The function makes 51
passes in phases 0x103 and 0x104, and then 20 in phase 0x105, with the counter
at 0, 1, ..., 19 on entry.

Who starts the task:

* Its address appears once in the ROM, in the pool word 0x08115738 of
  `func_08115560`. That function creates the task in its phase 0x104 with a
  0x1A0-byte payload (`src/08115560.c`). There is no BL to 0x08114910.
* `func_08115560` skips all its child tasks when the `hidden` halfword of its
  request is set: its phase 0x100 then goes straight to 0x10A.
* `func_08115560` is an effect. It is the callback of the registry entry at
  0x08395188, which is `data_083947D8[0x136]`, effect id 0x137 for
  `func_080D3508` (`src/080D3508.c`). It is also the fifth callback of
  `data_083A60C8`, which `func_0811896C` starts for request value 0x37
  (`src/0811896C.c`). No BL calls `func_08115560` either.

Not established: which animation of the game this effect is, and how often
play asks for it. Whenever it runs unhidden and this child completes, the
read happens.

## Behaviour against correct behaviour

`func_080112CC(object, x, y, angle)` is three stores, to the object's +0x32,
+0x34 and +0x36 (0x080112CC-0x080112D0). The function passes the table value
as both x and y. "Fixed" below is the `-DBUGFIX` build.

| pass | counter on entry | ROM reads | ROM stores (x, y, angle) | fixed |
|---|---|---|---|---|
| 1 | 0 | entry 1, 0x083A39A8 | 0x010D, 0x010D, 0x0600 | the same |
| 2 | 1 | entry 2, 0x083A39AA | 0x011D, 0x011D, 0x0D00 | the same |
| ... | | | | |
| 19 | 18 | entry 19, 0x083A39CC | 0x2000, 0x2000, 0x7A00 | the same |
| 20 | 19 | 0x083A39CE, outside the table | 0x00BF, 0x00BF, 0x8000 | no read, no store |

On passes 1 to 19 the two builds make the same reads and the same calls, and
no byte of the payload, the event or the object pool differs between them.

After pass 20 both builds have the counter at 10 and the phase at 0x106, have
unlinked both objects (state byte 0, nothing left on the draw list), have
cleared `payload->object` and `payload->scaled_object`, and return 0. The only
bytes that differ are the scale and angle left behind in the freed object
slot: 0x00BF, 0x00BF, 0x8000 in the ROM, and 0x2000, 0x2000, 0x7A00, the
values of pass 19, in the fixed build.

## Impact

None visible. This comes from the code and from running the ROM's own object
code under emulation, not from watching the game.

A pass, here, is what `func_080D36B0` does in its state 1 (`src/080D36B0.c`):
it runs the effect task manager `data_0200F430` (bl `func_08005A24` at
0x080D3714), then the object update (`func_08010DD0`, through `func_0800A640`
at 0x080D3718), then the object draw walk `func_080D3024` (bl at 0x080D372E).
Effects are created in that manager (`src/080D3508.c`), and their children are
created in whichever manager is running (`src/08005B6C.c`). The draw walk is
the only caller of the list iterator `func_08011690`, and `func_080D36B0` is
its only caller. For an object like this one it hands the object's +0x32,
+0x34 and +0x36 to the sprite routine `func_080018A0`
(0x080D30B0-0x080D30C4).

**The value from outside the table is never drawn.**

* `func_080112CC` only stores it.
* The same call then unlinks the object (0x08114D1E) and clears the pointer
  to it (0x08114D22). `func_08011428` takes the object off its list and
  clears its state byte, and the iterator skips objects whose state byte is 0
  (0x0801169C-0x080116A0).
* In the repro, the draw walk after pass 20 hands nothing to the sprite
  routines.
* The stale 0x00BF does not outlive the slot. The allocator `func_0801093C`
  copies a 64-byte template, `data_08149828`, over a slot before it hands it
  out (0x080109C0-0x080109C8). In the repro the ROM's allocator gives the
  freed slot out again with scale 0x0100.

Going by the table's own form (entry = 256 / size), 0x00BF drawn as a scale
would have been a size of about 1.34, straight after 1/32. That is a reading
of the table; what `func_080018A0` does with the value was not analysed.

**The 19 lookups before it draw the whole table.** The template gives every
new object x and y scale 0x0100 and angle 0, and 0x0100 is entry 0 of the
table. The object is created on the last pass of phase 0x104
(0x08114CA6-0x08114CD0) and drawn once with those values before phase 0x105
begins. The ROM then stores entries 1 to 19 on the next 19 passes. What the
draw walk hands the sprite routine for this object, pass by pass, is the
table from entry 0 to entry 19, once each:

```
x, y scale  0100 010D 011D 012E 0141 0157 0170 018E 01B0 01D9 020A 0246 0293 02F7 037E 0440 056D 0781 0C28 2000
angle       0000 0600 0D00 1300 1A00 2000 2600 2D00 3300 3A00 4000 4600 4D00 5300 5A00 6000 6600 6D00 7300 7A00
```

The fixed build draws exactly the same. `repro.py` compares every word the
draw walk hands the two sprite routines, on all 74 passes it runs, and none
differs.

Not established:

* any of this in a running game or in a full-system emulator;
* which animation of the game this effect (id 0x137) is, and how often play
  asks for it;
* that `func_080D36B0` state 1 runs once per displayed frame;
* what `func_080018A0` does with the scale and angle words it is handed;
* that no other code runs the effect manager without the draw walk. The
  direct load of the manager's address for `func_08005A24` is only at
  0x080D3710, but `func_08005A24` has other callers; whether any of them runs
  this manager was not checked;
* the object copy routine itself. `data_0836D4BC[0]` runs from IWRAM, where
  the emulated machine has no code, so the repro supplies a byte copy for it.
  The allocator depends on that copy: nothing else marks a slot as used
  (template +0 is 1).

## Developer intent

The intent was the animation the ROM draws: the object shrinks through the 20
keyframes of the table, from full size to exactly 1/32, while it turns
(`func_080E0608(&payload->spin, 0, 128, 20)` at 0x08114CD0, passed on as
`spin.current << 8`).

The likely mistake is an off-by-one bound. The phase was given 20 passes, and
the lookup was written on every one of them, including the pass that only
removes the object. Counted from the pass that creates it, the object is
drawn 20 times. Entry 0 comes with the object and entries 1 to 19 come from
the first 19 lookups, so only 19 lookups have a keyframe to fetch and a pass
on which it is drawn. The twentieth has neither.

Evidence:

* The creation template holds entry 0 (`data_08149828` +0x32 and +0x34 are
  0x0100). Stepping the counter before the lookup is what makes the first
  lookup fetch entry 1 and not repeat it.
* The counter is handled like the interpolator next to it, which is stepped
  first and read afterwards on the same pass (0x08114CE8, 0x08114D02). On
  drawn pass k the angle is step k of the interpolator and the scale is entry
  k of the table, both counted from the creation values 0 and 0x0100.
* The table ends on exactly 0x2000, a size of 1/32. The ROM draws that entry
  on its last drawn pass.
* The same excess pass shows in the angle. Its twentieth step, 0x8000, the
  half turn, is produced on the removing pass and never drawn. That is
  harmless because the interpolator has a value for step 20. The table has
  none for entry 20.

`func_08112CCC`, in the same module, makes the same call with the lookup
first and the step afterwards (`src/08112CCC.c`, lines 74-76 and 85-87):

```c
func_080112CC(payload->first_object, data_083A35C0[payload->index],
             data_083A35C0[payload->index], 0);
payload->index++;
```

That is weak evidence for what was meant here, for two reasons:

* It shows an order, not a count that comes out even. Its table has 60
  entries (`256 * 472 / (472 - 7 * k)`, ending on 0x0800, a size of exactly
  1/8). It makes 59 lookups, 20 in its phase 0x102 and 39 in its phase 0x103,
  starting from index 0 in a cleared payload. Entry 58 is stored on the pass
  that removes its object, and entry 59 is never read. This comes from its
  source and its table, not from running it.
* In this function that order does not give the animation the ROM draws. It
  is the rejected alternative below.

What the developer would have written cannot be proved from the ROM. The fix
below is the smallest change that removes the read and leaves every drawn
value as it is.

## The fix

```c
        func_080E064C(&payload->spin);
        payload->counter++;
#ifdef BUGFIX
        if (payload->counter < 20)
#endif
        func_080112CC(payload->scaled_object, data_083A39A6[payload->counter],
                      data_083A39A6[payload->counter],
                      payload->spin.current << 8);
        if (payload->counter > 19) {
```

The fixed build makes the lookup and the call only while the stepped counter
is inside the table. Passes 1 to 19 are untouched. Pass 20 goes straight to
the removal. Measured by `repro.py`:

* the fixed build reads entries 1 to 19 and nothing else near the table;
* on pass 20 it makes no read and no `func_080112CC` call;
* every word handed to the sprite routines is the same as in the ROM on every
  pass.

The call it skips also carried the angle 0x8000. That store is dropped with
it, and like the scale it was never drawn.

The default build is unchanged: `repro.py` links it at 0x08114910 and requires
it to equal the ROM's 1196 bytes. The `-DBUGFIX` build is 1204 bytes. It has
four more instructions after the counter is stored at 0x08114CF2, which are
`lsls r0, r0, #16`, `lsrs r0, r0, #16`, `cmp r0, #0x13` and a `bhi` to the
removal.

### Rejected alternative: `data_083A39A6[payload->counter - 1]`

Indexing with the counter before the step, which is what the order in
`func_08112CCC` amounts to, also keeps every read inside the table: the 20
passes read entries 0 to 19. It was measured with the same harness, on a build
whose `BUGFIX` arm was that expression (1196 bytes, one added `subs r1, #1` at
0x08114CFA), and it changes what is drawn:

```
ROM          0100 010D 011D 012E 0141 0157 0170 018E 01B0 01D9 020A 0246 0293 02F7 037E 0440 056D 0781 0C28 2000
counter - 1  0100 0100 010D 011D 012E 0141 0157 0170 018E 01B0 01D9 020A 0246 0293 02F7 037E 0440 056D 0781 0C28
```

* The draw walk's output differs from the ROM's on 19 of the 20 passes that
  draw the object: every keyframe after the first arrives one pass late.
* Entry 0 is drawn twice, once from the template and once from the table.
* Entry 19, 0x2000, is stored on the pass that removes the object and is
  never drawn. The shrink ends at 0x0C28, a size of about 1/12, instead of
  1/32.

A change that moves 19 drawn frames and drops the last keyframe is not a
repair of a read that draws nothing. To see it, put that expression in the
`BUGFIX` arm and run `repro.py`: its comparison of the drawn values fails and
prints the second line above.

## Reproduction

`repro.py` does the following:

1. Links the default build at 0x08114910 and requires it to equal your ROM's
   1196 bytes.
2. Checks the 20 table entries of your ROM against the closed form.
3. Runs the ROM bytes and the `-DBUGFIX` build pass by pass from phase 0x103,
   each in its own machine, for 74 passes. A pass is one call of the function
   with the stored phase, then the ROM's `func_08010DD0` and `func_080D3024`.
4. Records every read near the table, every `func_080112CC` call, and every
   word the draw walk hands to the sprite routines.

It fails if any of these stops being true: the ROM bytes read index 20 on the
removing pass; the fixed build does not; the drawn values are the same in
both.

The objects are made by the ROM's own creator and allocator and removed by the
ROM's `func_08011428`. Stubs: the two sprite routines, the IWRAM copy routine,
the child task starter `func_080DFD8C`, and the callees that only other phases
use. In the game, `func_0800A640` also runs `func_0800B568` and `func_0800C4B4`
before `func_08010DD0` (0x0800A642, 0x0800A646); the repro does not run them,
and neither touches the object pool. Requires unicorn and the repository
toolchain (see the docstring).

```
$ python3 docs/bugs/08114910/repro.py baserom.bin
source src/08114910.c: default build == ROM bytes [08114910, 08114DBC)

1. The table data_083A39A6: 20 halfwords, 256 * 608 / (608 - 31 * k).
  [ok] the ROM's 20 entries equal the closed form for k = 0..19: True
  entries 0..19: 0100 010D 011D 012E 0141 0157 0170 018E 01B0 01D9 020A 0246 0293 02F7 037E 0440 056D 0781 0C28 2000
  [ok] the halfword after the table, at 0x083A39CE: '00BF'

2. Non-trigger: the passes before the lookups.  Phase 0x103 creates the
   first object and sets the counter to 50; phase 0x104 counts it down and,
   at 0, creates the object that phase 0x105 scales.
  [ok] ROM / BUGFIX passes in phases 0x103 and 0x104, then (phase, counter): [(51, '0x105', 0), (51, '0x105', 0)]
  [ok] lookups and func_080112CC calls made in those passes: [0, 0]
  [ok] bytes of payload, event and object pool that differ between the builds: []
  [ok] the new object's +0x32, +0x34, +0x36 (x scale, y scale, angle), from the template: '0100 0100 0000'

3. Trigger: the twentieth pass of phase 0x105, which removes the object.
  [ok] ROM    (phase, counter) on entry: ('0x105', 19)
  [ok] ROM    table reads: instruction, address, bytes, inside [083A39A6, 083A39CE): [('08114D00', '083A39CE', 2, False)]
  [ok] ROM    func_080112CC(scaled object, x, y, angle): [(True, '00BF 00BF 8000')]
  [ok] BUGFIX (phase, counter) on entry: ('0x105', 19)
  [ok] BUGFIX table reads; func_080112CC calls: ([], [])
  [ok] ROM    return value; then (phase, counter): (0, '0x106', 10)
  [ok] ROM    payload->object, payload->scaled_object, objects on the draw list: (0, 0, [])
  [ok] ROM    state bytes of the two objects; sprites drawn after this pass: (0, 0, 0)
  [ok] ROM    x scale, y scale, angle left in the freed slot: '00BF 00BF 8000'
  [ok] BUGFIX return value; then (phase, counter): (0, '0x106', 10)
  [ok] BUGFIX payload->object, payload->scaled_object, objects on the draw list: (0, 0, [])
  [ok] BUGFIX state bytes of the two objects; sprites drawn after this pass: (0, 0, 0)
  [ok] BUGFIX x scale, y scale, angle left in the freed slot: '2000 2000 7A00'
  [ok] bytes that differ between the builds after this pass, as offsets in the freed slot: ['+0x32', '+0x33', '+0x34', '+0x35', '+0x37']

4. All of phase 0x105.  Passes 1 to 19 are the same in both builds.
  [ok] ROM / BUGFIX passes in phase 0x105: [20, 20]
  [ok] ROM    counter on entry, first..last pass: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19]
  [ok] ROM    table index read: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]
  [ok] BUGFIX table index read: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19]
  [ok] ROM / BUGFIX every read inside the table: [False, True]
  [ok] ROM    x scale passed: '010D 011D 012E 0141 0157 0170 018E 01B0 01D9 020A 0246 0293 02F7 037E 0440 056D 0781 0C28 2000 00BF'
  [ok] BUGFIX x scale passed: '010D 011D 012E 0141 0157 0170 018E 01B0 01D9 020A 0246 0293 02F7 037E 0440 056D 0781 0C28 2000'
  [ok] y scale == x scale on every call, in both: True
  [ok] passes 1..19: same reads, same calls; bytes that differ between the builds: (True, True, 0)

5. What is drawn.  The draw walk runs after every pass.  Compared here is
   every word it hands the two sprite routines, on all passes of the run.
  [ok] passes compared; passes on which the builds differ: (74, [])
  [ok] ROM    passes with a scaled draw (of 74); each is this object, y scale == x scale: (True, True)
  [ok] ROM    x scales drawn, passes 51..70: '0100 010D 011D 012E 0141 0157 0170 018E 01B0 01D9 020A 0246 0293 02F7 037E 0440 056D 0781 0C28 2000'
  [ok] BUGFIX passes with a scaled draw (of 74); each is this object, y scale == x scale: (True, True)
  [ok] BUGFIX x scales drawn, passes 51..70: '0100 010D 011D 012E 0141 0157 0170 018E 01B0 01D9 020A 0246 0293 02F7 037E 0440 056D 0781 0C28 2000'
  [ok] ROM / BUGFIX draw the 20 table entries once each, in order: [True, True]
  [ok] ROM    draws 00BF on any pass: False
  [ok] ROM    angles drawn (the BUGFIX build's are among the words compared above): '0000 0600 0D00 1300 1A00 2000 2600 2D00 3300 3A00 4000 4600 4D00 5300 5A00 6000 6600 6D00 7300 7A00'
   The ROM's allocator rebuilds a freed slot from its template (ROM machine):
  [ok] two new objects take the two freed slots: True
  [ok] x and y scale in the slot that held 00BF: '0100 0100'

6. Non-trigger: single passes of other phases.
  [ok] phase 0x104, counter 2: ROM / BUGFIX (return, phase, counter, lookups + calls): ((0, '0x104', 1, 0), (0, '0x104', 1, 0))
  [ok] phase 0x104, counter 2: bytes that differ between the builds; other-phase callees reached: ([], [])
  [ok] phase 0x106, counter 3: ROM / BUGFIX (return, phase, counter, lookups + calls): ((0, '0x106', 2, 0), (0, '0x106', 2, 0))
  [ok] phase 0x106, counter 3: bytes that differ between the builds; other-phase callees reached: ([], [])
  [ok] other-phase callees reached in the main runs: []

all assertions hold
```
