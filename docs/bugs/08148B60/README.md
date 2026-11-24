# func_08148B60: a full path queue freezes the search

**Status: latent. Not known to be reached in play.** The search's queue has
128 entries and no test for a full queue. When 128 entries are valid, the
next route to a cell that is not queued sends the scan in `requeue()` round
the ring for ever. `repro.py` has a 16x16 grid that does this to the ROM's
function. Whether any battle map gives such a grid was not checked. On an
open grid the queue never holds more than 32 entries, and on the random
terrain tried it held at most 42.

## The bug

`func_08148B60(object, callback, share, arg)` steps a path search over the
16x16 cells of a `PathState` (0x98A bytes, the stride of `func_0814913C`).
Category 3 takes the node at the queue's head (`queue_front`), copies it into
its cell, advances the head (0x08148DC0-0x08148DCE), and tries up to three
directions (four from the start), one or two cells each. For a new route to
a neighbour it calls `requeue()`, which updates the queued entry for that
cell if there is one. If there is none, it pushes a new entry
(0x0814906E-0x081490CA).

`requeue()` scans from the head until it reaches an entry that is not valid:

```
08148FC0  ldr r0, [sp, #0x40] ; ldrb r3, [r0]      ; index = head
08148FD2  ldrb r1, [r2] ; ands #0x80 ; beq 0x0814906E ; empty slot: not queued
08148FF0  compare x (sl), y (r7), then cost and climb ...
0814904C  index = index + 1, 0 after 127
08149062  node = &queue[index]
08149064  ldrb r1, [r2] ; ands #0x80 ; bne 0x08148FF0 ; valid: keep scanning
0814906E  push
```

The node being expanded stays valid until its expansion ends
(0x081490EC-0x081490F4). So once 127 cells are pending behind it, all 128
slots are valid: the tail has come round to the node being expanded. The
scan then ends only if it finds the cell it is looking for. For any other
cell it loops for ever, and the loop writes nothing. No push can happen at
128 entries, because a push follows only a scan that found an empty slot.
The only failure is the freeze.

## Trigger and reachability

The trigger is any search in which 128 entries are valid and a further
route reaches a cell that is not queued. Nothing in the function limits the
number of pending cells. `requeue()` keeps at most one entry per cell, but a
cell that was already expanded is queued again when a later route reaches it
at a lower cost, at the same cost with less climbing, or at the same cost
and climbing in one step where the stored route is a two-cell move
(0x08148F74-0x08148FA6, the tests against the cell's stored route).

`repro.py` section 1 is a constructed trigger: a 16x16 grid of 215 cells
and 41 holes, heights from 6 to 106, 9 flag4 cells and 93 flag5 cells,
start (7, 7), climb 4, drop -4 and no cost limit. When the ROM freezes, 35
of the 128 entries are cells that were expanded before, the node being
expanded among them. The costs of the 128 run from 8 to 14. On the open
flat grid the queue holds two costs, as a breadth-first frontier does.

How the trigger was found: a hill-climbing search mutated walls, heights and
the two flags, ran this ROM function under unicorn on each grid, and kept
the grids with the highest peak count of valid entries. It reached 111
after 30,000 mutations and the freeze after about 190,000 more. Peaks seen
without that search:

| grids | peak valid entries |
|---|---|
| open flat grid, all 256 starts (`repro.py` section 3) | 32 |
| 100 seeded random terrains (`repro.py` section 4) | 38 |
| 300 random terrains with holes, flags and limits | 42 |

In the game, `func_08148914` is the only caller (bl at 0x081489E2). It runs
the object with share 0xFFFF, which arrives as -1 (no step limit; see
`docs/bugs/08148914/`), so the whole search runs inside one call:

* `func_08099EA0` sets the limits through `func_08149230` (bl at 0x08099EF4):
  no cost limit (max_cost 0xFF), the unit's climb and drop limits (34 and -34
  in its states 2 and 3 and mode 5), and the unit's tile as the start.
* `func_0809A5E0` passes `func_08097814` as the callback. It fills each cell
  through `func_081491C0`, which always sets cost mode 1. A step therefore
  costs 1 and a two-cell move costs 2, as in `repro.py`.

The grid comes from the battle map, the units on it and the moving unit's
limits. No battle map was run through `func_08097814` here, so whether one
reaches 128 entries is not known.

## Behaviour against correct behaviour

From `repro.py`:

| state | ROM | BUGFIX |
|---|---|---|
| trigger grid (section 1, 2) | never returns: in the scan at 0x08148FF0-0x0814906E with 128 valid entries, looking for cell (3, 9); state unchanged a million instructions later | returns 0 (category 4); 188 cells have a route, and each walks back to the start through `func_08148A0C` |
| open flat grid, every start (section 3) | returns | the same state, byte for byte |
| 100 random terrains (section 4) | returns | the same state, byte for byte |

## Impact

If a map reached it, the game would freeze while a unit's routes were being
searched (`func_08099EA0` sets the search up for `func_08092784` and
`func_080BD8CC`; what the game does with the routes was not checked). The
search runs to the end inside one call from the per-frame task, so nothing
else would run again. No such report is known, and none was looked for.

## Developer intent

The intent is a ring queue that always has a free slot. The scan's only stop
is an empty slot, and nothing in the function compares the tail with the
head. The
size, 128 entries for 256 cells, fits a breadth-first frontier: a frontier on
a 16x16 grid holds at most about 32 cells (section 3).

The likely misunderstanding is that the queue only ever holds a frontier.
The re-queue rule (same cost, less climbing) sends cells that were already
expanded back into the queue, behind the frontier, so the queue can hold
cells over a wide range of costs. The developer also left the node being
expanded valid until its expansion ends, which takes one more slot.

## The fix

```c
        index = next;
#ifdef BUGFIX
        if (index == state->tail)
            break;
#endif
        node = &state->queue[index];
```

The valid entries are always the run from the head to just before the tail.
When the ring is full, the slot at the tail is the node being expanded, so
the scan stops at the tail instead. On a ring that is not full the slot at
the tail is empty, so the scan stops in the same place as before.

```c
                        if (!requeue(state, nx, ny, climb, newdir, cost, j)) {
#ifdef BUGFIX
                            if (state->queue[state->tail].valid)
                                continue;
#endif
                            queued = queue_push(state);
```

With the scan bounded, a full ring reaches the push, which would overwrite
the node being expanded, so the fix drops that route instead. The cell keeps
the route it had, or none, and a later route can still reach it once slots
are free. So on a grid that fills the queue the result can miss some routes,
but every route it records is real, and the search always ends. Without
routes dropped, the queue would need room for one entry per cell, which the
0x98A-byte record (`func_0814913C`, `func_0814914C`) does not have.

## Running the case

```
python3 docs/bugs/08148B60/repro.py [path/to/baserom.bin]
```

It needs unicorn and the repository toolchain (see the docstring). It first
checks that the default build reproduces the ROM's 1,488 bytes. It exits 0
when every assertion holds.
