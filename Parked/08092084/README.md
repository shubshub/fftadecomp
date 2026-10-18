# Parked: func_08092084 (22 B) and func_0814860C (32 B)

Both have the right arithmetic; only the *addressing shape* differs, and in
agbcc that comes down to which expression the compiler is allowed to share.

## 0x08092084

```
08092084  push {r4, lr}      08092086  lsls r1, r1, #0x10
08092088  asrs r1, r1, #0xf  0809208A  adds r4, r0, r1
0809208C  strb r2, [r4]       0809208E  adds r0, #1
08092090  adds r0, r0, r1     08092092  strb r3, [r0]
```

The scale is right - `index * 2` from a *signed* 16-bit index, spelled
(index << 16) >> 15 with an arithmetic shift (a u16 gives the logical shift,
which was the first thing tried). What differs is that the ROM recomputes the
second address as `(base + 1) + index * 2` from a fresh `base + 1`, while every
C shape tried lets the compiler share one computed pointer and store to
[ptr] and [ptr, #1].

Recovered C (compiles, does not match):

```c
void func_08092084(u8 *base, s16 index, u8 lo, u8 hi) {
    base[index * 2] = lo;
    base[index * 2 + 1] = hi;
}
```

To match, the source must express the second store so that sharing is not
available - two independent expressions over two independent base pointers.
Not guessed here: inventing `(u8 *)(base + 1 + index * 2)` to coax the
allocation would be exactly the kind of contrivance the plausibility rule
exists to reject.

## 0x0814860C

The rewrite block is right (+0x10 and +0x14 cleared, u32 at +0x18, tail at
+0x16, id read last at +0). What is left is register assignment: the ROM moves
the u32 argument into r4 and the u16 through r2 up front, then computes
`base + 0xC` into r0 and stores at r0+4/+8/+0xC/+0xA; the compiled code keeps
the arguments in place and offsets from the base directly.

Same class of problem as 0x08092084 - a register-allocation detail that needs
the original statement order or a different decomposition to reproduce, not a
different algorithm.
