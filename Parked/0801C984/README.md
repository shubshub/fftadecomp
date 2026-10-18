# 0x0801C984 - parked, no match

102 bytes (51 instructions) plus one literal at `0x0801C9EC` = `0x02007F40`.
Semantics are certain; the code shape is not reproducible with plausible C.

## What the function does

```c
void func_0801C984(s16 first, s16 second, s16 third,
                   s16 *firstOutput, s16 *secondOutput)
{
    s16 *origin = (s16 *)0x02007F40;      /* +0x20/+0x22/+0x24/+0x26 */
    s16 scaled[3];
    scaled[0] = ((first - third) >> 1) + origin[0x10];
    scaled[1] = ((first + third) >> 2) - (second >> 1) + origin[0x11];
    scaled[2] = first + third;
    *firstOutput  = (s32)scaled[0] - origin[0x12];
    *secondOutput = (s32)scaled[1] - origin[0x13];
}
```

`0x02007F40 + 0x24/0x26` is exactly what matched neighbour `src/0801C960.c`
uses as `origin[0x12]` / `origin[0x13]`. Parameter 5 is the stack word at
`frame(36) + 4*(5-5)` = `[sp,#0x24]`. The `s32` temporaries are load-bearing:
they are what produce `ldrsh` with a zero index instead of `ldrh`, the same
trick as `Parked/0801CA10`.

## How close it got

Closest shape is `probes/0801C984/x3_bias_asym_a.c`: **108 bytes, 33 of 69
slots**, and it reproduces the ROM's prologue *and* epilogue byte-for-byte
(`push {r4,r5,r6,r7,lr}; mov r7,sb; mov r6,r8; push {r6,r7}; sub sp,#8` ...
`mov r6,sp; movs r4,#2; add r4,sp,r4; mov r8,r4; add r7,sp,#4; mov sb,r7` ...
`pop {r3,r4}; mov r8,r3; mov sb,r4`) with the same 51-instruction count. It
loses on two coupled things, both about materialising an address:

1. **The `origin` base.** The ROM's literal is `0x02007F40` with
   `ldrh [r5,#0x20]`, `#0x22`, `#0x24`, `#0x26`. agbcc only folds the load into
   the `plus` insn - dropping one pseudo - when the MEM displacement is **0**,
   i.e. `origin = (s16 *)0x02007F40 + 0x10` with offsets 0,2,4,6. That folded
   form unlocks the good allocation (two high registers instead of three) but
   puts `0x02007F60` in the pool. With the ROM's real base and offsets the load
   becomes its own pseudo (`reg:HI 56`) and `local_alloc` needs a third high
   register (`r8`, `sb`, `sl`), costing 10 bytes: 112 instead of 102.
2. **Read-back order.** The ROM loads `*mid` first (`ldrsh r1,[r4,r2]`, `r4`
   being parameter 1's register) and `*low` second through a re-materialised
   `mov r0,sp`, so `*low` is *not* read through `low`. That wants
   `b = *mid; a = scaled[0];`. With the ROM's real offsets this regresses to
   the 112-byte form above.

## Ruled out

Input form (`s16*`/`u16*`/`u8*`/casts/array/struct member/`s16[3]`/`s16[4]`);
shift form (`>> n`, `/ (1<<n)`, `>>=`, mixed signed division); temp type
(`s32`, `int`, `s16`, `u16`, cast inline); origin spelling (initialised
pointer, pointer plus const bias, four element types, body assignment,
declaration position, reversed declaration order of the three slot pointers);
read-back form (a-first, b-first, `*low`/`low[0]`/`scaled[0]`, symmetric and each
asymmetric direction, `s32 ra = ...` split, `(s32)` cast inline, block-scoped
and initialised declarations); statement-level operand order on all three adds;
extra temporaries for the shift results; and 95 flag sets of
`-O0/-O1/-O2/-O3/-Os` crossed with `fdefer-pop`, `fstrength-reduce`, `fgcse`,
`fcse-follow-jumps`, `fexpensive-optimizations`, `fthread-jumps`, `fpeephole`,
`fomit-frame-pointer`, `fcse` - nothing reaches 102 bytes.

Note what is *not* the blocker here, unlike `0x0801CA10`: agbcc does emit all
three `&scaled[k]` registers, and three explicit `s16 *` locals are required to
get them - plain array indexing folds to `sp+imm` at 92-96 bytes. Declaration
order of the three slot pointers, and of `origin`, has zero effect; the
allocator picks the registers, not the source order.

## Diagnosis

This is a register-allocation wall, not an algorithmic one.
`local_alloc` (in `~/agbcc/gcc/local-alloc.c`) ranks callee-saved candidates by
`QTY_CMP_PRI`, a life-length over reference-count ratio. The `origin[0x10]`
load scores `4/life = 1.0` against `&scaled[0]`'s `12/life = 0.52`, so the load
takes `r4` and pushes `&scaled[0]` out to `r9` instead of letting it take `r6`.
The ROM's ordering needs that quantity to live ~8+ instructions longer, or
`&scaled[0]` to carry four references. No plausible C found here does either
while keeping the `0x02007F40` + `0x20` addressing.

Not recorded as unmatchable: this identifies a *class* of failure with a named
mechanism, not a proof that no source reaches it. The 32 shapes and their
distance-from-ROM are kept in `../../fftadecomp-kit/probes/0801C984/`.

`match.py` would refuse this symbol outright - `sub sp, #8` trips the
"unsupported stack-pointer adjustment" gap - so every byte count above comes
from the raw `cpp -> agbcc -mthumb-interwork -O2 -> as -> objcopy` chain.