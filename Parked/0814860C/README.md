# Parked: func_0814860C (32 bytes)

**Cannot be reproduced from plausible C.**  Same cluster and same cause as
`Parked/0814862C` — see "The dead-load mechanism" below, which now explains
three functions at once.

## What the ROM does

```
push {r4, lr}
adds r3, r0, #0        r3 = h
adds r4, r1, #0        r4 = value
lsls/lsrs r2, #0x10    r2 = (u16) tail
ldrh r0, [r3]          <-- DEAD: overwritten two instructions later
adds r0, r3, #0
adds r0, #0xC          r0 = h + 0xC
movs r1, #0
strh r1, [r0, #4]      +0x10 = 0
strh r1, [r0, #8]      +0x14 = 0
str  r4, [r0, #0xC]    +0x18 = value
strh r2, [r0, #0xA]    +0x16 = tail
pop  {r4}
pop  {r0}              <-- void return
bx   r0
```

## Corrections to the previous attempt

The parked note claimed the stores were already right.  They were not:

* `include/ffta.h`'s `HdrTail` puts the fields at +4/+6/+0xC/+8.  The ROM needs
  **+4, +8, +0xC, +0xA** — a `u32` at +0 of the block, `cleared_a` +4, an
  unknown at +6, `cleared_b` +8, `tail` +0xA, `value` +0xC.
* the struct in the header was never actually compiled, so the claim rested on a
  stale report.

With the corrected layout the store instructions and their order are exact.

## The dead-load mechanism (the useful part)

The dead `ldrh r0, [r3]` is the *cause* of everything else, not a detail:

| | with the dead load | without it |
|---|---|---|
| where `h` lives | r3 | r0 |
| `+0xC` | materialised: `adds r0,r3,#0; adds r0,#0xC` | folded into the addressing mode |
| `value` | r4 (callee-saved) | r1 |
| frame | `push {r4, lr}` … `pop {r4}; pop {r0}` | none, `bx lr` |

In ~20 variants, **every** compile containing a load from `h` puts `h` in r3 and
**every** compile without one keeps it in r0.  agbcc's `simplify_gen_binary`
always flattens `plus(plus(h,12),4)` into `plus(h,16)`, so the block pointer only
survives as a separate addend when the destination register differs from the
base's — which is exactly what the dead load causes.

This also explains why these functions keep a frame while similar-looking ones
do not: **the frame comes from register pressure created by a load that later
dies.**  agbcc deletes an unused load, so no plausible C reproduces it.

Ruled out as a source of a dead `ldrh` (all compile to nothing): `u16 id =
h->id;`, bare `h->id;`, `return h->id;` in a void function, `return
(void)h->id;`, comma expressions, `while (h->id) break;`,
`switch (h->id){default: …}`, a dead store overwritten by `= 0`, `u16*`/`u32*`
indexing forms, `p += 12` with a separate local, and variable offsets.

The only route to the bytes is

```c
if (h->id) { b->value = v; b->tail = t; } else { b->value = v; b->tail = t; }
```

— inert control flow, which `plausible.py` rejects and which is the same trick
already refused for `0x0814862C`.  Even with it, only 22 of 32 bytes came out.

## Best honest source (compiles, 24 bytes, no frame)

```c
void func_0814860C(Hdr *h, u32 value, u16 tail) {
    HdrTail *t = &h->tail_block;
    t->cleared_a = 0;
    t->cleared_b = 0;
    t->value = value;
    t->tail = tail;
}
```