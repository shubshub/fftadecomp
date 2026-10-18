# Parked: func_0801CA10 (54 bytes)

**Close, and parked with a precise diagnosis.** 8 of 27 instruction slots
agree (25 of 27 semantically); the whole remainder is how the addresses of a
local array get materialised. The agent removed its source again rather than
leaving a non-match in `src/`, which is the rule.

## What it does

Reads three `s16` at +0/+2/+4 of `source`, scales them by 32/16/32 into a
**local `s16[3]`**, then writes the low byte of each to `destination[0..2]`:

```
movs r3, #0            ; ldrsh r2, [r0, r3]
movs r4, #2            ; ldrsh r3, [r0, r4]
movs r5, #4            ; ldrsh r4, [r0, r5]
mov  r0, sp            ; scaled[0]
mov  r6, sp / adds r6, #2
add  r5, sp, #4        ; scaled[1], scaled[2]
asrs r2, r2, #5        ; >> 5
strh r2, [r0]
asrs r3, r3, #4        ; >> 4
strh r3, [r6]
asrs r4, r4, #5        ; >> 5
strh r4, [r5]
ldrh r0, [r0] / strb r0, [r1]        ; truncate back out of the array
ldrh r0, [r6] / strb r0, [r1, #1]
strb r4, [r1, #2]                   ; the third value never round-trips
```

## Best recovered C (compiles, 52 bytes)

```c
void func_0801CA10(s16 *source, u8 *destination) {
    s32 first, second, third;
    s16 scaled[3];
    first = source[0]; second = source[1]; third = source[2];
    scaled[0] = first >> 5; scaled[1] = second >> 4; scaled[2] = third >> 5;
    destination[0] = scaled[0];
    destination[1] = scaled[1];
    destination[2] = scaled[2];
}
```

**The `s32` temporaries are load-bearing.** They are what makes agbcc emit the
ROM's `ldrsh` + `asrs` pair; with `s16` locals you get
`ldrh; lsls #16; asrs #21` instead. Keep them.

## The exact remaining difference

Only the stack-address materialisation:

```
ROM                                  compiled here
mov  r0, sp                          mov  r0, sp
mov  r6, sp / adds r6, #2             asrs r2, r2, #5
add  r5, sp, #4                      strh r2, [r0]
                                     ...
push {r4, r5, r6, lr}               push {r4, r5, lr}
pop  {r4, r5, r6}                    pop  {r4, r5}
```

The ROM keeps `&scaled[0..2]` in three registers (one reused as an
offset-index register); agbcc folds each into a single `sp` base plus an
immediate. Confirmed from agbcc's `-da` RTL dump: here `local_alloc` gives each
`&scaled[k]` a pseudo whose value is plain `sp`, leaving the offset inside the
`MEM`, and reload folds it. Net +2 instructions in the ROM (54 = 27×2, no pad,
against 52 = 25×2 + a trailing `nop`).

Three separate `s16 *` locals `p0/p1/p2 = &scaled[k]` **do** emit the ROM's exact
address sequence - but at 68 bytes, because agbcc then spills the array base
and re-derives `&scaled[2]` from `&scaled[1]`. So that is not the source, and
it would not be plausible C anyway.

## Ruled out

Input form (`s16*`, `u16*` + cast, `u8*` per access, struct field access,
array parameter, array-of-struct at the wrong stride), shift form (`>> n`,
`/ (1<<n)`, `>>=`, `<< 11 >> 16`), temporary type (`s32`, `int`, `long`, `s16`,
`u16`, `s8`, comma form, `register`), buffer (`s16[3]`, `u16[3]`, `s16[4]`,
`u8[6]` viewed through other pointer types, three scalars — which agbcc
forwards away entirely, making the function frameless), access spelling
(`*(&scaled[k])`, pointer aliases, array in a block), frame layout (a pad
member moves the array off `sp+0`), and every optimisation level plus
`strength-reduce`, `gcse`, `cse-follow-jumps`, `expensive-optimizations`,
`thread-jumps`, `peephole`, `omit-frame-pointer`, `defer-pop`,
`strict-aliasing`, `inline` — all `-O1`..`-Os` produce the identical 52 bytes,
and `-O0` is 160.

## Two leads worth keeping

1. **The tooling gap is real, and this is the case that demonstrates it.**
   `match.py` refuses the symbol outright (`unsupported stack-pointer
   adjustment`), so even a correct source could not have been verified here.
   Two independent agents have now hit it; `0x0801CA10` is the reference case.
2. **Try `0x0801CA48`** (46 bytes, the two-input sibling). Same idiom, two
   `ldrsh` with register-indexed offsets, `&scaled[0..2]` in r0/r4/r5, and a
   literal-zero `strh` into slot 1. The `s32`-temporary trick that unlocked
   `ldrsh` here should transfer, and it is worth a sub-agent.

No shared type is warranted: the input is just `s16 *`.