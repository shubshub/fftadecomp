# 0x0809D464 - near miss (294 bytes): byte-identical only with a contrivance

Retry of Parked/0809D464 (284 bytes) on 2026-11-16, kit fcdf2d45, default flags.

The source in this directory compiles to the target's 294 bytes (MATCH - byte identical, 141/141 instructions, report
elf-symbol-thumb-frame-calls-v1, plausible.py clean), but only with `RoutePoint *point = (RoutePoint *)state;` - the route cursor initialised
from the state parameter with a value that is never read through it. Not shipped: the initialiser exists only to steer register allocation
(AGENTS.md: nothing that exists only to steer the compiler), so this is not a match. Without the initialiser (`RoutePoint *point;`) the source
compiles to 286 bytes (286 < 294; the older parked source is 284): `state` sits in r4 alone, there is no `mov sl, r0` / `mov r4, sl`, and the
store after func_08148A98 is `strh r0, [r4, #24]`.

What the ROM shows: one register (r4) holds the first-half state pointer and then the loop cursor; the entry copy of the first argument (sl) is used
only for the `length` store after func_08148A98. Reproduced only when a single variable is set from `state` at the top, reassigned from `route`
after func_08148A98 returns but before its result is stored, and incremented after `count - 1` is computed.

Legitimate fixes over the older parked source (keep them): phase constants and `state->state = 0` written as static inline copies of the sibling
bodies func_0809D620 / func_0809D638 (fixes the movs r0,#2; movs r1,#3; movs r2,#4 preload); `s8 x` / `s8 z` locals loaded before the
func_0809B014 call (two independent adds #0xFE / #0xFF address computations); a separate `last = count - 1` ahead of `point++`. To ship, the two
inlines would have to be verbatim copies of src/0809D620.c / src/0809D638.c (named inlined_0809D620 / inlined_0809D638); here they use this
file's struct and member names.

Ruled out (each compiled): an explicit MovementState * alias with the tail store through the parameter (the block after the frame-- label switches
to the parameter's register); first half as a static inline start(state, ...) (single register, 284 bytes); func_0809B014 result held in the cursor
variable (visible adds r4, r0, #0; cmp r4, #0); `point = route` before the func_08148A98 call (call argument switches to r4, separate
adds r4, r6, #0); `point = route` after `state->length = func_08148A98(...)` (store becomes strh r0, [r4, #24], second register disappears);
`count--` instead of `last` (decrement in place in r5). Declaration order does not matter.

Open idea: a source where the first half and the walk are two inlined functions sharing one formal, or where the state parameter itself is
reused as the cursor (e.g. a void * / union-typed parameter walked after the first half).
