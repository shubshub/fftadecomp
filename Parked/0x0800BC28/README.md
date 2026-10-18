# Parked: func_0800BC28 (30 B)

Four bytes out, and they are one register-allocation decision: the table base
lives in **r4** and is a callee-saved register in the ROM, but agbcc puts a
*literal* base in **r0** and then has no callee-saved register at all.

## The ROM

```
0800BC28  push {r4, lr}
0800BC2A  lsls  r0, r0, #0x18      ; index &= 0xff
0800BC2C  lsrs  r0, r0, #0x18
0800BC2E  ldr   r4, [pc, #0x18]    ; pool @ 0x0800BC48 = 0x02009000
0800BC30  lsls  r3, r0, #2
0800BC32  adds  r3, r3, r0        ; *5
0800BC34  lsls  r3, r3, #3         ; *8  -> *40
0800BC36  adds  r3, r3, r4         ; record = base + index*40
0800BC38  ldrh  r0, [r3, #0x18]
0800BC3A  strh  r0, [r1, #0]
0800BC3C  ldrh  r0, [r3, #0x1a]
0800BC3E  strh  r0, [r2, #0]
0800BC40  pop   {r4}
0800BC42  pop   {r0}
0800BC44  bx    r0
```

## Where it stops

```
compiled (28 B)                       ROM (30 B)
                                      push {r4, lr}
lsls r0, r0, #24                      lsls r0, r0, #24
lsrs r0, r0, #24                      lsrs r0, r0, #24
                                      ldr  r4, [pc, #24]
lsls r3, r0, #2                       lsls r3, r0, #2
adds r3, r3, r0                       adds r3, r3, r0
lsls r3, r3, #3                       lsls r3, r3, #3
ldr  r0, [pc, #12]   ; 0x02009000      adds r3, r3, r4
adds r3, r3, r0                       ldrh r0, [r3, #24]
ldrh r0, [r3, #24]                    strh r0, [r1, #0]
strh r0, [r1, #0]                     ldrh r0, [r3, #26]
ldrh r0, [r3, #26]                    strh r0, [r2, #0]
strh r0, [r2, #0]                     pop  {r4}
bx    lr                              pop  {r0}
                                      bx   r0
```

Every body instruction matches, including the `*40` as `(x<<2)+x)<<3` and both
MEM displacements. Only the base register differs, and that costs the whole
prologue/epilogue pair: a callee-saved register has to be pushed to get a
return, and once the frame exists agbcc closes with the interworking
`pop {r0}; bx r0`.

## Why r0 and not r4

A literal address in C reaches agbcc as `CONST_INT` inside the address
expression. `expand_binop`/`expand_plus` commute the add so that the multiply
comes first, so the RTL is

```
r3 = r0 << 2 ; r3 += r0 ; r3 <<= 3 ; (P = 0x02009000) ; r3 = r3 + P
```

`P` is a reload pseudo that is *born at its point of use*, i.e. after the
scaling, where r0 - the masked index - is already dead (`REG_DEAD r0` on
`adds r3, r3, r0`). `REG_ALLOC_ORDER` on ARM is {r3, r2, r1, r0, ip, lr, r4,
...}, so `P` takes r0; no callee-saved register is used, no frame is created.

For the ROM, `P` has to be born *before* the scaling so that it conflicts with
r0 (index), r1, r2 (the two out-pointers) and r3 (the scaled index) and is
pushed out to r4. agbcc only does that when the first operand of the plus is
already a register when the plus is expanded - which is what `force_reg` on a
**symbol address** does, and it is why the base load sits *above* the multiply.

## Evidence: a symbol reproduces all 30 bytes

Declaring the table as a real array instead of spelling the address out:

```c
static Rec40a g_tbl[2];              /* 40-byte record type, x/y at +0x18/+0x1A */
void func_0800BC28(u32 index, s16 *a, s16 *b) {
    u8 i = (u8)index;
    *a = g_tbl[i].x;
    *b = g_tbl[i].y;
}
```

compiles to **exactly** the 30 target bytes - `push {r4, lr}`, the mask, the
`ldr r4, [pc, #24]` before the multiply, `adds r3, r3, r4`, both
`ldrh [r3, #24]`/`[r3, #26]`, `pop {r4}; pop {r0}; bx r0`, the 2-byte pad at
+0x1E and the pool at +0x20. The only difference is the pool word: the object
contains `.word g_tbl` (an R_ARM_ABS32 relocation, value 0 in .bss) where the
ROM has `0x02009000`, i.e. the original source addressed the table through a
link-time symbol that the game placed at 0x02009000.

`match.py` cannot verify that: it rejects any object with a non-.text section
("unexpected nonempty allocated section") or with a relocation ("unresolved
relocations"), so the symbol form cannot be checked byte-for-byte, and the
literal form cannot be made to reproduce the register allocation.

## Ruled out

Tried and checked with agbcc -mthumb-interwork -O2 (all produce 28 B, base in
r0, `bx lr`):

* `(u8 *)0x02009000 + (u8)index * 40` with the struct pointer, and the same
  via `sizeof` - `sizeof` gives the `(x<<3)-x)<<2` = 28 stride, not 40;
* `((Rec40 *)0x02009000)[i]`, `&tbl[i]`, `tbl[i].x`/`tbl[i].y`, a local
  `u8 i = (u8)index` first or last, `void *base`, `(u64)`/`(void *)` cast
  round-trips on the literal, a `static Rec40 *const` pointer (folded to the
  literal), the pool-valued literal with `(u8 *)`/`s16 *`/`u32 *` typed bases;
* two separately spelled address expressions (`*(s16 *)(t + i*40 + 0x18)` and
  `... + 0x1a`): that *does* put the base in r4 and emit `push {r4, lr}` /
  `pop {r4}` / `pop {r0}` / `bx r0`, but GCC folds the 0x18/0x1A into the two
  literals (0x02009018/0x0200901A) and needs a second `ldr` and a second
  `adds` - 44 bytes, not 30;
* `-O0/-O1/-O3/-Os` - all four emit the same 28 bytes.

What does work is a literal base used *only* at `+ constant` addresses
(`u8 *t = (u8 *)0x02009000; *(s16 *)(t + 0x18); *(s16 *)(t + 0x1a);` gives
`ldr r3, [pc, #8]` + `ldrh [r3, #24]`/`[r3, #26]`): there the base pseudo
survives and the displacements stay in the MEMs. Adding the index to that same
base is what loses it. That is the shape the ROM has, but agbcc will not build
it from a literal, and forcing it (a redundant base use, an inline symbol, a
pragma) is exactly the kind of contrivance `plausible.py` rejects.

## Recovered C (compiles, 28 of 30 bytes)

```c
void func_0800BC28(u32 index, s16 *a, s16 *b) {
    Rec40 *r = (Rec40 *)((u8 *)0x02009000 + (u8)index * 40);
    *a = r->x;
    *b = r->y;
}
```