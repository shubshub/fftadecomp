# 0x0809D464 - movement route setup: near miss, 269/294 bytes; byte-identical only with a dead initialiser (294 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. `func_0809D464(MovementState *state, SceneObject *object,
RoutePoint *route, s32 count)` initialises a movement state: it stores the object, the route and its length, clears
the counters, sets the phases 2, 3, 4, 2 and the state byte 0 (the bodies of `func_0809D620` and `func_0809D638`, here
as inline copies of `src/0809D620.c` and `src/0809D638.c`), sets bit 2 of the object's flags, stores
`func_0809A53C(object)` less one (when nonzero) and the object's direction, and calls `func_0809836C(object, 11,
direction, 0)` and `func_0809A570(object, 0, 2)`. When the object's data has movement type 2 and a mode other than 5
and `func_0809B014(object, route, count, x, z)` succeeds, it sets the status counter to 1, stores
`func_08148A98(route, count)` as the length, raises the height of every interior route point whose tile
`func_08099644(owner, x, z)` reports occupied, and sets bit 1 of the state flags. The index row
`0809D464 0809D58A 294 141 return` is right (141 reachable instructions, no literal pool). It references no data; no
data symbol is needed.

## Byte identity

Not byte-identical. `0809D464.c` (the honest form) compiles with the fixed recipe (`cpp -nostdinc -undef -I include`,
`agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) to a 286-byte symbol; `match.py` with default
flags stops at `compiled symbol is shorter than the indexed span: 286 < 294`. Linked by hand at 0x0809D464 (6
`R_ARM_THM_CALL`) and aligned against the ROM it gives 123/141 instructions (269/294 bytes). The ROM span
`[0x0809D464, 0x0809D58A)` has SHA-256 `738913b014747d8bb5dd37a137c141455f2722bd65a75d3390fec1c9077d0226`.
`plausible.py --strict` exits 0.

The differences follow from one register copy the source lacks. The ROM keeps the state pointer in two: `sl`, set at 0x0809D470 and
read only by the length store after `func_08148A98` (`mov r1, sl; strh r0, [r1, #0x18]` at 0x0809D53C-0x0809D53E),
and `r4`, copied from it at 0x0809D478 (`mov r4, sl`), which serves every other state access and becomes the route
cursor at 0x0809D542 (`adds r4, r6, #4`). This source keeps the state in r4 alone (`adds r4, r0, #0`), so the
prologue saves r8/r9 instead of r8/r9/sl (`push {r6, r7}` for `push {r5, r6, r7}` at 0x0809D46A-0x0809D46C), the
length store is `strh r0, [r4, #0x18]`, the cursor is set before `count - 1` is computed instead of after it
(0x0809D540-0x0809D542), the epilogue restores one register fewer (0x0809D57C-0x0809D582), and the branches in
between move up by the eight bytes.

## Refusals

The honest form has no verifier refusal; it does not compile to the ROM's bytes. A variant does: with the three
changes below, `match.py --root . --no-write 0x0809D464` prints `verdict MATCH - byte identical`, 141/141
instructions (294/294 bytes), and `plausible.py --strict` exits 0. It is held by the source policy, AGENTS.md
"Does not ship": "a spare temporary ... a dead initialiser".

```c
RoutePoint *point = (RoutePoint *)state;   /* in place of RoutePoint *point; */
s32 length;
s32 last;
...
            length = func_08148A98(route, count);
            point = route;
            state->length = length;
            last = count - 1;
            point++;
            for (i = 1; i < last; i++, point++) {
```

The initialiser gives `point` a value it never reads through it; `length` and `last` each hold one value used once.
All three are needed: the initialiser alone gives the honest form's 286 bytes, and so do the two temporaries without
it; initialiser and `length` without `last` give 294 bytes, 140/141 (the cursor set before `count - 1`). main's
previous revision of this entry holds the same three constructs (with its own inline helpers in place of the sibling
copies) and also gives `MATCH - byte identical`.

## Cause

With the initialiser `point` and `state` are the same value at entry, so the compiler gives the first half's state
accesses `point`'s register (r4) and keeps the parameter in `sl` for the one store that follows the reassignment
`point = route`. The two temporaries order that reassignment between the call and the store, and the cursor
increment after `count - 1`, as the ROM has them (0x0809D538-0x0809D542).

Open question, not decided here: the ROM does hold two copies of the state pointer (`mov sl, r0` at 0x0809D470,
`mov r4, sl` at 0x0809D478), so a second variable that starts as `state` and later walks the route is visible in the
instructions. Whether that register copy is evidence enough for a cursor initialised from `state` (and for the two
temporaries that order it), or whether the initialiser is a dead initialiser that only moves the allocation, is a
policy question for the maintainer. The inlined copy of this function in `func_0809D128` shows the same two-location
pattern: the state pointer is kept at `[sp, #4]` and in r4 (0x0809D1BE-0x0809D1C4), the length store reloads
`[sp, #4]` (0x0809D2A2-0x0809D2A4) and r4 then becomes the cursor (0x0809D2AA-0x0809D2AC). That suggests the
original was a `static` or inline function whose shape produced the copy, but no source reproducing it without the
initialiser has been found.

## Source notes

- The two helpers are verbatim copies of the matched `src/0809D620.c` and `src/0809D638.c`, named
  `inlined_0809D620` / `inlined_0809D638` with their own types (`Rec5`, `ByteState`); in the earlier
  attempt they fixed the `movs r0, #2; movs r1, #3; movs r2, #4` preload order the ROM has.
- `s8 x` / `s8 z` are loaded before the `func_0809B014` call: the ROM computes the two addresses independently
  (`adds #0xFE` / `#0xFF`).
- `ObjectData`, `SceneObject` and `MovementState` are offset views; only the members this function touches are named.

## Ruled out

Compiled on this attempt (hand-linked and aligned against the ROM's 141 instructions; every non-identical compile is
286 bytes except where shown):

| variant | result |
|---|---|
| this source | 286 bytes, 123/141 |
| + initialiser only | 286 bytes, 123/141 |
| + `length` only | 286 bytes, 123/141 |
| + `last` only, or `length` and `last` | 286 bytes, 124/141 |
| + initialiser and `last` | 286 bytes, 124/141 |
| + initialiser and `length` | 294 bytes, 140/141 (`adds r4, r6, #4` one instruction early, 0x0809D540) |
| + initialiser, `length` and `last` | MATCH 141/141, 294/294 (held) |
| main's previous revision | MATCH 141/141, 294/294 (the same three constructs) |

From the earlier attempt (2026-11-16, not re-run here), each with the initialiser in place: an explicit
`MovementState *` alias with the tail store through the parameter (the block after the mode decrement switches to
the parameter's register); the first half as a `static inline start(state, ...)` (single register, 284 bytes);
the `func_0809B014` result held in the cursor variable (a visible `adds r4, r0, #0; cmp r4, #0`); `point = route`
before the `func_08148A98` call (the call argument moves to r4, with a separate `adds r4, r6, #0`); `point = route`
after `state->length = func_08148A98(...)` (the store becomes `strh r0, [r4, #24]` and the second register
disappears); `count--` instead of `last` (decrement in place in r5). Declaration order did not matter there. Not yet
tried: a source where the first half and the walk are two inlined functions sharing one formal, or where the state
parameter itself is reused as the cursor (a `void *` or union-typed parameter walked after the first half).

kit issue: none (not byte-identical)
