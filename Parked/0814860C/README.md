# Parked: func_0814860C (32 B)

*(func_08092084, which shared this file, now matches — see src/08092084.c and
docs/match/08092084.md.  Only the 0814860C attempt remains here.)*

## What it does

```
0814860C  push {r4, lr}
0814860E  adds r3, r0, #0
08148610  adds r4, r1, #0
08148612  lsls r2, r2, #0x10
08148614  lsrs r2, r2, #0x10      ; (u16) third argument
08148616  ldrh r0, [r3]           ; read the u16 at +0, returned last
08148618  adds r0, r3, #0
0814861A  adds r0, #0xc           ; block at +0xC
0814861C  movs r1, #0
0814861E  strh r1, [r0, #4]       ; +0x10
08148620  strh r1, [r0, #8]       ; +0x14
08148622  str  r4, [r0, #0xc]     ; +0x18, the u32 argument
08148624  strh r2, [r0, #0xa]     ; +0x16, the u16 argument
08148626  pop  {r4}
08148628  pop  {r0}
0814862A  bx   r0
```

## Where it stops

The stores, the order and the +0xC block all came out right once the block was
anchored at +0xC (not +0x10) and the id read moved into the return statement.
What is left is register assignment: the ROM moves the u32 argument into r4 and
the u16 through r2 up front, while the compiled code keeps the arguments where
they are and offsets from the base directly.

Same class as func_08092084 was: the values are right, the allocation is not.
Two things now known from 08092084 may apply here and have not been tried yet:

* an offset held in a **variable** makes agbcc emit base-first adds
  (`add r4, r0, r1`); inlined into the address expression it comes out
  index-first;
* an **in-place increment** of a pointer is what forces a frame, because it
  keeps the base live across a store.

## Recovered C (compiles, does not match)

```c
u16 func_0814860C(Hdr *h, u32 value, u16 tail) {
    HdrTail *t = &h->tail_block;
    t->cleared_a = 0;
    t->cleared_b = 0;
    t->value = value;
    t->tail = tail;
    return h->id;
}
```
