# Parked: func_0814862C

16 bytes, 8 instructions, Thumb. Not matched yet.

## What it does

```
08014862C  push {lr}
08014862E  adds  r2, r0, #0
080148630  lsls  r1, r1, #24
080148632  lsrs  r1, r1, #24
080148634  ldrh  r0, [r2]
080148636  strb  r1, [r2, #0x1c]
080148638  pop   {r0}
08014863A  bx    r0
```

Sets a byte at +0x1c and returns the u16 at +0. The obvious C:

```c
u16 func_0814862C(Ent *p, u8 v) {
    u16 id = p->unknown_0;
    p->flag = v;
    return id;
}
```

## Why it does not match

Two differences from what `agbcc -mthumb-interwork -O2` produces:

1. **The frame.** agbcc compiles this to a sibling/tail call (`bx lr`), while
   the ROM saves lr and returns through it (`push {lr}` ... `pop {r0}; bx r0`).
   A frame is only forced when the function reads an incoming stack argument -
   and an *unused* extra parameter does not do it (verified: a third `u16`
   parameter compiles to the identical body, frame and all absent).
   `-fdefer-pop`, `-fno-defer-pop`, `-O0..-Os` change nothing, and
   `-fno-optimize-sibling-calls` does not exist in this compiler
   (gcc 2.9 predates it), so it cannot be disabled from the command line.
2. **The u8 mask.** The ROM masks r1 with `lsl/lsr #24` before storing, which a
   `u8` parameter does not need (the ABI already passes the low byte). A wider
   parameter with an explicit `(u8)` cast would emit it - but on its own that
   still does not produce the frame.

So the original source had something that made the compiler treat this as
non-leaf while keeping a `u8`-narrowed value. Not yet identified.

## Retrying it

Worth another attempt with a different reconstruction of the struct or
signature - the neighbouring matched functions (`0x08011040`, `0x080DBD5C`)
show the same argument-order pattern and *do* have stack arguments.
