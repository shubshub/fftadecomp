# Parked: func_0801CAE0 (58 B)

One instruction from matching, and it is a register-allocation detail.

## What it does

```
0801CAE0  push {r4, lr}      0801CAE2  ldr  r1, [pc, #0x38]   ; base = 0x02007F40
0801CAE4  mov  ip, r1        0801CAE6  adds r1, #0x2e
0801CAE8  ldrb r4, [r1]      0801CEA  lsls r4, r4, #3
0801CAEC  strh r4, [r0]      0801CEE  mov  r1, ip
0801CAF0  adds r1, #0x2f     0801CAF2  ldrb r3, [r1]
0801CAF4  lsls r3, r3, #3    0801CAF6  strh r3, [r0, #2]
0801CAF8  adds r1, #1        ... then +0x30 and +0x31 by increment
0801CAFE  adds r2, #8        0801CB0C  subs r2, r2, r4
0801CB0E  strh r2, [r0, #8]  0801CB10  subs r1, r1, r3
0801CB12  strh r1, [r0, #a]
```

Four table bytes scaled by 8 (the last two plus 8), written as six s16; the
last two are the differences of the pairs.

## Where it stops

Compiled and the ROM agree on everything except the address of the *second*
table byte:

```
compiled                          rom
adds r1, #1                       mov  r1, ip
                                  adds r1, #0x2f
```

The ROM re-materialises the base out of `ip` for the second access and then
increments for the third and fourth; agbcc strength-reduces all three to
increments when they share one expression. That also moves the literal pool 4
bytes earlier, which is the pool-offset difference visible at the top.

## Recovered C (compiles, does not match)

```c
void func_0801CAE0(s16 *out) {
    u8 *t = (u8 *)0x02007F40;
    out[0] = t[0x2e] << 3;
    out[1] = t[0x2f] << 3;
    out[2] = (t[0x30] << 3) + 8;
    out[3] = (t[0x31] << 3) + 8;
    out[4] = out[2] - out[0];
    out[5] = out[3] - out[1];
}
```

Matching it needs a source where the 0x2F access is spelled independently of
the 0x2E one, so the compiler cannot share the increment. Writing a deliberately
broken-up expression to force that is the same contrivance the plausibility
rule rejects, so it stays parked.
