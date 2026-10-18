# Parked: func_0800BC08 (26 bytes)

Writes two s16 into a 40-byte record of the table at 0x02009000, indexed by a
byte-masked index.  A sub-agent swept ~160 spellings; the arithmetic and both
stores come out byte-identical, and the whole gap is one thing:

    the pooled base is materialised *after* the x40 chain instead of before it

which also means the frame (`push {r4,lr}` / `pop {r0}` / `bx r0`) never
appears, because without r4 live the function is a leaf and agbcc tail-calls
it.

## Root cause (from agbcc RTL dumps)

The base is a constant-valued pseudo.  When its only use is inside
`plus(base, index * 40)` - an ordinary expression - `combine` propagates the
constant into the `plus`, reload materialises it at the `add`, and it lands in
r0 because the index is dead by then.

It survives as a pseudo only when its uses are **inside MEM addresses**.
`src/0801CD28.c` (matched) depends on exactly that: its `state` is only ever
used as `mem[plus(p_state, 4)]` / `mem[plus(p_state, 8)]`, so it stays a pseudo
and reload emits `ldr r4, [pc, #..]` right after the argument masks - exactly
the shape 0x0800BC08 needs.  With a *variable* index there is no way to keep
the base out of a `plus`.

## Evidence about the optimisation level

`-O1` gets much closer: 7 of 13 instructions, 25 of 32 bytes, with the right
`push/pop/bx r0`, one pool entry and the right store offsets - but the mask
lands in r3 instead of r0, the x40 accumulator in r0 instead of r3, and the
`ldr r4` comes after the scale instead of before.  40 further `-O1` spellings
did not close it.

This is the first evidence that the ROM may not be `-O2`: the 46 matched
functions are all built from arguments that arrive on the stack, which forces
the frame anyway and makes `-O1`/`-O2` identical for them.  Leaves like this
one are where the levels actually differ.  Worth a systematic sweep.

## Follow-up: that lead is refuted, and this function's blocker is something else

A systematic sweep of every parked function and every source in `src/` at
`-O0/-O1/-O2/-O3/-Os` settled the flag question: **12 of the 43 matched
functions break at `-O1`**, all 43 are byte-identical at `-O2`, `-O3` and `-Os`.
The ROM is `-O2`; `-O1` only *looks* closer here and is not closer in
substance.  See `docs/toolchain.md`.

The premise this note started from was wrong, and it is the kind of error that
survives because it sounds right: *"the 46 matched functions all take stack
arguments, so the levels cannot tell them apart"*.  Only **13 of 43** read `sp`
at all, and 11 of the 12 `-O1` breakages never touch it.  Leaves with register
arguments do discriminate — against `-O1`.

**The real blocker here is not the optimisation level either.**  The ROM ends

```
pop {r4}; pop {r1}; bx r0
```

and per the agbcc return-register table recorded in `Parked/0814862C`,
`pop {r1}` is the path for a **non-void** return (r0 is void, r1 is anything up
to 4 bytes).  The recovered C returns `void`, so *every* level emits `pop {r0}`.
Fixing the return type is the precondition, not the flags.

## Also found

`Rec40` in `include/ffta.h` was declared with 0x18 bytes of padding and named
as if it were 40 bytes - it is 28.  The file only worked because it spells the
stride as a literal 40.  Fixed separately.
