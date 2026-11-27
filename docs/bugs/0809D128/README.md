# func_0809D128: a fourteenth movement is started through a NULL slot

**Status: a latent bug. It is reachable through the event-script engine, but
it is not known to happen in the shipped events.**
* The faulty accesses are shown by executing the ROM's own bytes.
* The engine allows up to 17 path movements at once against 13 slots.
* Whether any shipped event script ever runs 14 at once has not been
  established (see "Trigger").

## The bug

`func_0809D128(slots, object, route, count)` starts a path movement in the
first free slot of the movement manager's thirteen 0xB4-byte slots. The free-slot
search (the inlined `find_free_slot`) returns NULL when every slot's object is
set. Nothing tests that result:

```
0809D142..0809D154                ; loop over the 13 slots; a free one branches to 0x0809D260
0809D156  movs r7, #0             ; none free: slot = NULL
0809D158  str  r1, [r7]           ; slot->object = object         -> 0x00000000
0809D15A  ldr  r5, [r7, #4]       ; slot->movement                <- 0x00000004
0809D15E  bne  0x0809D180         ; non-zero: no allocation
0809D188  strb r0, [r6, #4]       ; manager flags |= 1
0809D19C  bl   _call_via_r3       ; g_callbacks_0836D4B8[1](slot->route = 0x08, route, count * 4)
0809D1A6  strb r0, [r4]           ; slot->count = count           -> 0x00000068
0809D1B4  bl   _call_via_r2       ; g_callbacks_0836D4B8[0](&slot->active = 0x6C, 0x48)
0809D1B8  ldrb r4, [r4]           ; slot->count read back         <- 0x00000068
0809D1BC  ldr  r1, [r7, #4]       ; slot->movement again          <- 0x00000004
0809D1C0  ldr  r0, [r7]           ; slot->object                  <- 0x00000000
0809D1C6  str  r0, [r4]           ; start_movement: state->object = ..., through slot->movement
```

The repro records the ROM's accesses to the BIOS page in this order: a write of
0x0, a read of 0x4, a write and a read-back of 0x68, a read of 0x4 and a read
of 0x0. The route copy and the status clear also go to 0x08..0xB3.

## Trigger and how often it happens in play

**The callers.** `func_0809D128` has two callers. Both are path-move tasks
that run it once, in phase 0x100:
* `func_08126FCC`, bl at 0x081270C4;
* `func_08127124`, bl at 0x081271C8.

They are started by event-script commands from the command table
`data_083A7EE4` (6-byte entries `{u16 length; handler}`):

| opcode | handler | starts |
|---|---|---|
| 0x41 | `func_081234FC` | `func_08127AF8` -> `func_08126FCC` |
| 0x42 | `func_0812352C` | `func_08127AF8` -> `func_08126FCC` |
| 0x44 | `func_08123580` | `func_08127B40` -> `func_08127124` |

**A thread holds one movement at a time.** Each of these handlers returns
0x115. The script thread `func_08121FB8` then waits in state 0x115 until its
`ready` byte is set. The task sets that byte (`output->complete = 1`,
`func_08126FCC` phase 0x101) only after `func_0809D96C` finds no slot left for
the object. `func_0809D2F8` frees a slot once its movement has ended. So each
script thread holds at most one slot at a time.

**But up to 17 threads can run.** Scripts fork threads with opcodes 0x00 and
0x01 (`func_08122B14` and `func_08122B50`, through `func_081223C8`).
`func_08122404` registers a fork in a table of 16 entries (`i < 16`, through
`func_08121D0C` and `func_08121D20`). It refuses a fork only when the table is
full or a thread with the same id is already running. Together with the
event's main thread (`func_0812237C`), up to 17 threads can each hold one path
movement. The engine therefore allows more simultaneous movements than the 13
slots.

**Shipped data, not established.** I walked the 233 event scripts of
`g_table_089A5D54` (62 groups) linearly, using the table's command lengths:
* The largest is group 1, script 1 (0x089A636F). It has 28 path-move commands
  and 99 forks.
* The next largest has 11 path-move commands.
* 52 scripts do not walk cleanly with fixed lengths, so this is an estimate.

Whether any event runs 14 path movements at the same time depends on the
scripts' control flow. That has not been determined.

## Behaviour

The table below is for all 13 slots in use. The repro models the BIOS page
the way the hardware presents it to code running from ROM: reads return one
open-bus word (the last BIOS opcode fetched; the repro uses 0xE3A02004) and
writes are dropped.

| | ROM | BUGFIX |
|---|---|---|
| BIOS-space accesses | stores at 0x00, 0x08..0xB3; reads at 0x00, 0x04, 0x68 | none |
| manager flags | bit 0 set | unchanged |
| movement state used | the open-bus word read from 0x00000004 | none |
| after that | `start_movement` stores through it (0x0809D1C6), then calls `func_0809A53C`, `func_0809836C` and `func_0809A570` with an object pointer read back from it (by the code; the repro stops at that store) | returns |

With a free slot (repro cases 2 and 3), both builds fill the first free slot,
allocate its movement state and start the movement identically.

## Impact

Unknown, possibly harmful. From 0x0809D1C6 on, the function writes through
the open-bus word, and it hands the callees an object pointer read back
through that word. What those accesses hit depends on the open-bus value and
on how the GBA decodes such addresses. The repro stops at the first access
outside GBA memory and does not try to model the rest.

If the game survives those accesses, the movement itself is lost. The object
never gets a slot, because the store to 0x00000000 is dropped, so the caller's
`func_0809D96C` wait ends at once and the script continues without the move. The caller's follow-up `func_0809D98C` and `func_0809D9D8` find no
slot and do nothing.

## Developer intent

The same manager's lookups all handle a missing slot:
* `func_0809D96C` returns 0;
* `func_0809D98C` and `func_0809D9D8` end their 13-entry searches with
  `match = 0` and test `if (match)` before using it;
* `func_0809D2F8` skips empty slots.

Only the allocation assumes that a slot is always free. The most likely intent
is that 13 slots are more than any scene needs, so the full case was never
handled. The safe behaviour is to drop the movement, which is what the lookups
already do when a slot is missing.

## The fix

```c
#ifdef BUGFIX
    if (slot == 0)
        return;
#endif
```

The movement is not started, nothing is written outside the manager, and the
script continues exactly as it does in the ROM once the move is lost, but
without the accesses through BIOS space and the open-bus pointer.

## Reproduction

```
python3 docs/bugs/0809D128/repro.py [path/to/baserom.bin]
```

What it checks:
* The default build links to the ROM bytes.
* With all 13 slots in use:
  * the ROM bytes make the BIOS-page stores and reads above, set the manager
    flag, and stop at a store inside the open-bus "state";
  * the BUGFIX build returns, with no BIOS access and the manager and heap
    unchanged.
* With slot 12 free, and with slots 3 and 7 free, the two builds fill the same
  slot identically.

It needs unicorn and the toolchain; see the header of `repro.py`.
