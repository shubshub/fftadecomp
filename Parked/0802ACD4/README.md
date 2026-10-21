# 0x0802ACD4 - non-matching: 115 of 128 bytes, 60 of 64 instructions

Plausible C, **not** a byte match.  There is no `src/0802ACD4.c` and no
verified match report for this address.

## The target

`[0x0802ACD4, 0x0802AD54)` - 128 bytes, 64 instructions, plus the literal
word `0x00000fff` at `0x0802AD50`.  The next function's prologue is at
`0x0802AD54` (`func_0802AD54`), so the whole span belongs to this function.

```
0802ACD4  f0b5       push     {r4, r5, r6, r7, lr}
0802ACD6  4f46       mov      r7, sb
0802ACD8  4646       mov      r6, r8
0802ACDA  c0b4       push     {r6, r7}
0802ACDC  8046       mov      r8, r0
0802ACDE  0798       ldr      r0, [sp, #0x1c]     ; stack argument (count)
0802ACE0  1206       lsls     r2, r2, #0x18
0802ACE2  120e       lsrs     r2, r2, #0x18
0802ACE4  9146       mov      sb, r2              ; tag -> r9
0802ACE6  1b06       lsls     r3, r3, #0x18
0802ACE8  0006       lsls     r0, r0, #0x18
0802ACEA  000e       lsrs     r0, r0, #0x18
0802ACEC  8446       mov      ip, r0              ; count -> ip
0802ACEE  0906       lsls     r1, r1, #0x18
0802ACF0  c911       asrs     r1, r1, #7
0802ACF2  090c       lsrs     r1, r1, #0x10        ; (u16)((s8)a * 2) -> r1
0802ACF4  db0d       lsrs     r3, r3, #0x17        ; (u8)c * 2
0802ACF6  4046       mov      r0, r8
0802ACF8  c268       ldr      r2, [r0, #0xc]       ; state->base
0802ACFA  d218       adds     r2, r2, r3
0802ACFC  407d       ldrb     r0, [r0, #0x15]      ; state->field_15
0802ACFE  4843       muls     r0, r1, r0
0802AD00  4000       lsls     r0, r0, #1
0802AD02  1518       adds     r5, r2, r0           ; p
0802AD04  4946       mov      r1, sb
0802AD06  ff29       cmp      r1, #0xff
0802AD08  02d1       bne      0x0802AD10
0802AD0A  4346       mov      r3, r8
0802AD0C  db7f       ldrb     r3, [r3, #0x1f]      ; state->tag
0802AD0E  9946       mov      sb, r3
0802AD10  0020       movs     r0, #0
0802AD12  461c       adds     r6, r0, #1
0802AD14  6046       mov      r0, ip
0802AD16  0028       cmp      r0, #0
0802AD18  0dd0       beq      0x0802AD36
0802AD1A  0d4f       ldr      r7, [pc, #0x34]      ; 0xFFF
0802AD1C  4946       mov      r1, sb
0802AD1E  0c03       lsls     r4, r1, #0xc         ; tag << 12
0802AD20  2b1c       adds     r3, r5, #0           ; w = p
0802AD22  6246       mov      r2, ip              ; j = count
0802AD24  1988       ldrh     r1, [r3]
0802AD26  381c       adds     r0, r7, #0
0802AD28  0840       ands     r0, r1
0802AD2A  2043       orrs     r0, r4
0802AD2C  1880       strh     r0, [r3]
0802AD2E  0233       adds     r3, #2
0802AD30  013a       subs     r2, #1
0802AD32  002a       cmp      r2, #0
0802AD34  f6d1       bne      0x0802AD24
0802AD36  4346       mov      r3, r8
0802AD38  587d       ldrb     r0, [r3, #0x15]      ; state->field_15 (reloaded)
0802AD3A  4000       lsls     r0, r0, #1
0802AD3C  2d18       adds     r5, r5, r0           ; p += field_15
0802AD3E  301c       adds     r0, r6, #0
0802AD40  0128       cmp      r0, #1
0802AD42  e6dd       ble      0x0802AD12
0802AD44  18bc       pop      {r3, r4}
0802AD46  9846       mov      r8, r3
0802AD48  a146       mov      sb, r4
0802AD4A  f0bc       pop      {r4, r5, r6, r7}
0802AD4C  01bc       pop      {r0}
0802AD4E  0047       bx       r0
0802AD50  ff0f 0000  .word    0x00000fff
```

## Interface

`void func_0802ACD4(State *state, s8 a, u8 b, u8 c, u8 count)`

The state block is the one of `func_0802AB64` (the sibling in the same
module): a `u16 *base` at `+0x0C`, a `u8` at `+0x15` (the row stride in u16
entries) and a `u8 tag` at `+0x1F`.  `+0x15` is reloaded after the inner
loop, because the store through `w` may alias the state block.

* `a` - signed byte, used as `(u16)(a * 2)` (the narrowing is
  `lsls #24 / asrs #7 / lsrs #16`), multiplied by the row stride.
* `b` - the tag.  `0xFF` means "use `state->tag`"; the parameter itself is
  overwritten with the resolved tag (that is why it lives in r9/sb).
* `c` - a u8 column offset, used as `(u8)c * 2`.
* `count` - the number of entries to tag per row (on the stack: `[sp, #0x1c]`
  after the 28-byte frame, i.e. the first stack word - Thumb `bl` does not
  push the return address).

Callers confirm the types: `0x0806E5EC` passes `r1 = (s8)r5` (a signed
byte), `r2 = 0xFF` (default tag) or `0x0B`, `r3 = 2` and
`[sp] = (u8)(state->field_15 - 2)` (the row length minus two).

## What the function does

For two rows, tag `count` consecutive u16 entries of `state->base` with a
4-bit tag in the high nibble, keeping the low twelve bits:

```
p = state->base + c + (u16)((s8)a * 2) * state->field_15;
for (i = 0; i < 2; i++) {
    for (j = 0; j < count; j++) {
        *p = (*p & 0xFFF) | (tag << 12);
        p++;
    }
    p += state->field_15;
}
```

The outer loop runs exactly twice, the inner loop is a countdown with an
`if (count != 0)` guard, and the row pointer advances by the stride only
(the walking pointer is a separate copy).

## The difference

115 of 128 bytes are identical; 13 bytes differ, in four instructions:

| offset | address | ROM | this source |
|---|---|---|---|
| 0x3E | 0x0802AD12 | `adds r6, r0, #1` | `adds r7, r0, #1` |
| 0x46-0x4F | 0x0802AD1A-0x0802AD23 | `ldr r7, [pc, #0x34]` first, then the tag shift and the two IV inits | the tag shift and the two IV inits first, the literal load last |
| 0x52 | 0x0802AD26 | `adds r0, r7, #0` | `adds r0, r6, #0` |
| 0x6A | 0x0802AD3E | `adds r0, r6, #0` | `adds r0, r7, #0` |

In words: the ROM loads the `0xFFF` literal **first** in the inner loop's
pre-header (before `tag << 12` and the two induction-variable
initialisations), while this source loads it **last**; that shifts the mask
between r6 and r7 and therefore also swaps the register the outer loop's
counter gets.

The literal load is hoisted out of the inner loop by agbcc's invariant
motion, which places it immediately before the loop, i.e. *after* the
source-level statements of the pre-header.  To get it first, the `tag << 12`
must itself be hoisted out of the inner loop (i.e. written inline in the
expression, so that it is created after the mask in the RTL and both are
moved together) - but then agbcc hoists `tag << 12` one level further, out of
the outer loop, which the ROM does not do.

## What was ruled out

* **Parameter types.**  `a` is `s8` (the callers pass `(s8)x`, and the
  narrowing is `lsls #24 / asrs #7 / lsrs #16` = `(u16)((s8)x * 2)`); `b` and
  `c` are `u8`; the stack argument is a `u8`.  `u16`/`s16` for `a` produce
  `lsls #17 / lsrs #16` instead.
* **The tag as a local instead of the modified parameter.**  That moves the
  tag into ip and the count into r8 (48 of 64 instructions) - the ROM has
  the tag in r9/sb and the count in ip, which only the modified-parameter
  form produces.
* **The pointer.**  One pointer (`p = base + c; p += row * field_15`) merges
  the two additions into one register; the ROM keeps the intermediate in r2
  and the final pointer in r5, which needs two pointer variables
  (`q = base + c; p = q + row * field_15`).  With one pointer the row
  offset is applied in place (40 of 64 instructions).
* **The row value.**  It has to be a `u16` local (`u16 row = a * 2;`); inlining
  `(u16)(a * 2)` loses the `lsrs #16` truncation (45 of 64).
* **The outer loop.**  `for (i = 0; i < 2; i++)` with a signed counter is
  what produces the rotated `i + 1` / `i <= 1` shape; an unsigned counter
  gives `bls` instead of `ble`, and `while (i < 2) { i++; ... }` gives a
  countdown.  A `do/while` and `i != 2` were also tried.
* **The inner loop.**  It has to be a countdown (`while (j != 0) { ...; j--; }`)
  with the `if (count != 0)` guard written explicitly in the source - that is
  what rotates the *outer* loop into the ROM's shape.  Without the explicit
  guard the outer loop keeps the increment at the bottom (40 of 64); with a
  `for (j = 0; j < count; j++)` or a `do/while` the counter direction or the
  extra guard is wrong.
* **The `tag << 12` value.**  It has to be a `u32` local in the `if` block.
  Inline, agbcc hoists it out of the outer loop (43 of 64); as a `u16` it
  gains a truncation; as an explicit mask local (`u16 m = 0xFFF;`) the
  constant is propagated and the whole shape changes (27 of 64).
* **The count.**  A local copy of the count (`u32 n = count;`) changes the
  register allocation, and using it for the loop counter makes agbcc add a
  second guard, because it can no longer prove the counter is non-zero
  (39 of 64).  The parameter must be used directly.
* **Statement order.**  All permutations of the declarations
  (`tag`, `row`, `q`/`p`, the tag fix-up) and of the statements inside the
  `if (count != 0)` block were tried; none changes the position of the
  literal load.
* **Other forms.**  `*w &= 0xFFF; *w |= t;`, `(u16)(...)`, `0xFFF & *w`,
  `t | (*w & 0xFFF)`, an index-based inner loop (`p[j]`), a `for` inner loop,
  a `do/while` inner loop, `--j` in the condition, and a `u8`/`u16`/`u32`
  count copy were all tried; none produced the ROM's pre-header order.

The recovered source is plausible C and compiles to 128 bytes, but it is not
byte identical, so it stays here rather than in `src/`.
