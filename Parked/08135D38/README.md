# Parked: func_08135D38 (38 bytes)

**Cannot be reproduced from plausible C**, for two independent reasons — either
alone is enough.  Same dead-load mechanism as `Parked/0814862C` and
`Parked/0814860C`; read that note first.

## Literal pools

| pool | instruction | address | value |
|---|---|---|---|
| A | `ldr r0,[pc,#0x24]` @ `0x08135D3A` | `0x08135D60` | `0x02000000` |
| B | `ldr r1,[pc,#0x24]` @ `0x08135D3C` | `0x08135D64` | `0x00002FC2` |
| C | `ldr r1,[pc,#0x20]` @ `0x08135D46` | `0x08135D68` | `0x03000940` |

(`0x08135D5E–5F` is alignment padding.)  So the function writes `7` at
`0x0300098C` and `0xC` at `0x0300098D`, and reads bytes at
`0x02000000 + 0x2FC2`, `0x0300098C` and `0x0300098D`.

## Blocker 1 — three dead computations need a branch condition

```
ldrb r1, [r0]; movs r0, #3; ands r0, r1     <- result dead
ldrb r0, [r2]; movs r0, #7; strb r0, [r2]   <- the load is dead
ldrb r0, [r1]; movs r0, #0xc; strb r0, [r1] <- the load is dead
```

agbcc at `-O2` deletes dead register `SET`s at the tree level (`cse.c` drops a
dead local's assignment; `delete_trivially_dead_insns` after `cse_main` has no
exemption for a non-volatile `MEM`).  Verified: a dead load survives **only**
when the `MEM` is `volatile` — and even then the dead `and` goes, so only the
byte read survives, not the mask.

So the loads have to be **branch conditions that outlive reload**, which in C
means identical `if`/`else` arms — the construct `plausible.py` rejects as
`inert-control-flow`, and which the repo rules forbid as steering.  It also
supplies `push {lr}` / `pop {r0}`: a straight-line leaf never gets a frame,
re-confirmed here with three volatile pointers and six volatile accesses
(still `bx lr`, no push).

## Blocker 2 — the EWRAM address needs a named symbol

`ldr r0,[pc]` = `0x02000000`, `ldr r1,[pc]` = `0x2FC2`, `adds r0,r0,r1` — the
address is deliberately **not folded**.  agbcc folds `base + constant` into a
single literal in every form tried: literal base + literal offset, pointer local
plus a `u32` local, `u16` offsets, a pointer walk, a reused variable.  The only
ways to get the two-entry form are a **symbol reference**
(`extern u8 g_ewram[0x20000]; g_ewram[0x2FC2]` gives the exact shape) — which
leaves an `R_ARM_ABS32` relocation `match.py` refuses — or a memory write
between the definition and the use, which adds instructions the ROM does not
have.

`0x02000000 + <offset>` appears as an **adjacent pool pair 24 times** in the
ROM, so this is a ROM-wide idiom, not a one-off.

## What does compile correctly

`u8 *t = (u8 *)0x03000940; t[0x4C] = 7; t[0x4D] = 0xC;` produces the IWRAM
block byte for byte — 12 of the 13 body instructions; only the two dead loads
are missing.

## Ruled out

`-O0/-O1/-O2/-O3/-Os` (identical for this shape); `volatile` (banned, and it
still loses the dead `and`); dead locals, comma expressions, `(void)` casts;
global-pointer indirection; `u16`/`u32`/`long` offsets; `sizeof`/enum offsets;
`static` arrays; `goto`, `while…break`, `do…while(0)`, `for`, `switch`;
`if (c) X; X;` (the branch survives as `beq`); and every call/inline variant
for `push {lr}` (any call emits a `bl`; an empty `static inline` emits nothing).

## Corroboration

`0x02000000 + 0x2FC2` sits in the same EWRAM object that `Parked/08009888`
found (members at `0x2FBE`, `0x2FBF`, `0x2FBC` there).  One object at
`0x02000000` of at least 0x2FC4 bytes, referenced from many places.