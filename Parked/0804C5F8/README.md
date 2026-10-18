# Parked: func_0804C5F8 (110 B, 55 instructions)

Ten arguments, builds one 28-byte table entry.  Two of the findings from the
easier batches carry over and both had to be got right for this to get close:

- the scale is `index * 28`, spelled shift/subtract/shift, and it only comes out
  that way when the offset is computed before the base is folded in;
- the argument order in the signature is not the store order, and `u16`/`u8`
  parameters are visible in the mask instructions.

## Where it stops

agbcc folds the selector's u16 mask into the shift:

```
rom                      compiled
lsls r2, r2, #16         lsls r2, r2, #16
                         lsrs r2, r2, #30        <- one shift, mask folded in
lsrs r2, r2, #14
```

`(u16)(kind >> 2)`, `(u16)kind >> 14` and a named `u16 sel` were all folded to
the same `lsrs #30`.  All four optimisation levels (`-O1 -O2 -O3 -Os`) produce
identical code, so this is not the open `-O1 vs -O2` question - agbcc simply
always folds a mask that has no other use.

For the ROM to keep the pair, the masked value must have had a second use, or
the shift was applied to a different quantity than the one that was masked.
That is a lead about the original source, not something to fake with contrived
expressions.

Secondary, smaller: the ROM computes the table address into r0 and loads the
u16 from there; the compiled code uses r1.  Same values, different allocation.

## Recovered C (compiles, does not match)

```c
void func_0804C5F8(Entry *base, u16 index, u32 kind, u8 a4,
                   u8 a5, u8 a6, u8 a7, u32 a8, u8 *row, u16 a10) {
    u8 *r = row + (u16)(kind >> 2);
    u32 head = *(u32 *)r;
    Entry *e = (Entry *)((u8 *)base + index * 28);
    e->field_0e = *(u16 *)(row + head);
    e->field_00 = (u32)(row + (head + 2));
    e->field_0f = 0;
    e->field_08 = 0;
    e->field_0d = 1;
    e->field_0a = a6;
    e->field_10 = a4;
    e->field_11 = a5;
    e->field_0c = 6;
    e->field_13 = a7;
    e->field_18 = a8;
    e->field_16 = a10;
}
```

## Next step

func_0804C524 (116 B) is the same function with one more argument and two
different fields - once the mask question is answered, it falls out.
