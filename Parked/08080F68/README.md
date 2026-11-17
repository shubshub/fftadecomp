# 0x08080F68 - two-row tile recolour and copy: byte-identical, held by source policy (272 bytes)

Attempt 2026-11-17, rechecked at kit 18dcc516 against decomp main e1149cf7e7. The function picks two rows of a tile
region (`state->unknown_0C + ((unknown_1A + offset) * 2 % (unknown_17 * 2)) * width`, the remainder through
`func_08142950` at 0x08080F9C), recolours up to `count` entries of each row between `start` (2 when bit 1 of
`unknown_10` is set, else 0) and `end` (`width`, less 2 when bit 2 is set) by replacing the palette nibble
(`& 0xFFF | palette << 12`, 0x08081024-0x0808102C; `palette` 0xFF means `unknown_1F`), and copies each row out with
the CpuSet wrapper `func_0814186C` (0x08081044) as a halfword count `(size / 2) & 0x1FFFFF`. It uses the same state
as the matched `src/08081B24.c` and `src/08085558.c` (the offsets match the immediates: `+8`/`+0xC` pointers, `+0x10`
and `+0x1A` halfwords, `+0x15`, `+0x17`, `+0x1E` and `+0x1F` bytes) and the same callees as `src/0801799C.c`. The
index row `08080F68 08081078 272 129 return` is right (129 reachable instructions to 0x0808106E, then a pad halfword
and the pool words 0x00000FFF and 0x001FFFFF). It references no data; no data symbol is needed.

## Byte identity

`08080F68.c` is byte-identical at kit 18dcc516 with default flags: `match.py --root . --no-write 0x08080F68`, with
this source copied to `src/08080F68.c`, prints `verdict MATCH - byte identical`, 129/129 instructions (272/272
bytes), and `plausible.py --strict --addr 0x08080F68` exits 0.

Compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked at 0x08080F68 with `func_08142950` and `func_0814186C` bound to their
ROM addresses (2 `R_ARM_THM_CALL`), the 272-byte symbol equals the ROM span `[0x08080F68, 0x08081078)`: SHA-256
`0535fb6a78344f7c65866722db533c5f6abf67dc10d9e43e86332431b6bc1e57` for both. `.text` is exactly 272 bytes.

## Refusals

No verifier refusal. It is held by the source policy, AGENTS.md "Does not ship": "a cast that changes no value ... or
a type chosen for where the allocator then puts the value". The match needs the field `unknown_15` read into a wider
local and narrowed into a second one:

```c
u32 stride = state->unknown_15;
u8 width = stride;
```

Both hold the same byte for the whole function. `u8 width = stride` changes no value, because `stride` is a
zero-extended byte; removing it changes only register allocation. `s32 stride` matches too, and is the same device.

## Cause

The question is whether the copy of `+0x15` into two registers is shown by the ROM or is allocation. It is
allocation. The ROM loads the byte once (`ldrb r0, [r0, #0x15]` at 0x08080F84) and copies it twice, `mov sl, r0` at
0x08080F86 and `adds r5, r0, #0` at 0x08080F88. `r5` feeds the row multiply (`muls` at 0x08080FA4) and `end`
(`adds r6, r5, #0` at 0x08080FE4, then `subs #2`); `sl` feeds the hoisted `stride * 2` (0x08080FF4-0x08080FF8, kept at
`[sp, #0x14]` and added at 0x08081048, not reloaded from the state after the call).

One `u8` local gives 264 bytes, 126 instructions, with the same loads, multiplies, masks, stores and calls. Every
difference is a register move (`mov`, or `adds rd, rs, #0`) or a register choice:

- the load goes straight to r5, with no `mov sl, r0` and no `adds r5, r0, #0` (0x08080F86/0x08080F88);
- `ldrh [r0, #0x1a]` without the `mov r1, r8` (0x08080F8E);
- the start mask is built in r0, with no `mov r3, sb` / `mov sb, r3` (0x08080FDA/0x08080FDE);
- `lsls r5, r5, #1`, with no `mov r2, sl` (0x08080FF4).

No instruction narrows, tests, stores or computes anything that the one-local source does not, and the ROM has no
narrowing instruction (`ldrb` already zero-extends). Two registers for one value are the allocator's output, so
under AGENTS.md "Evidence first: what is a fake" the copy is a device, not ROM-shown code. Apart from a whole-body
inline wrapper (below), every source tried keeps the byte in two registers only when a narrowing conversion
separates two locals.

The matched siblings give no second variable either. `src/0801799C.c` has two different variables: a `u8 width`
parameter (used for `end`) and a `u8 stride` local (used for the multiply), and its increment reloads
`state->stride`; its caller `src/08017AF4.c` passes `state->field_15` as `width`. In this ROM the multiply and `end`
share one register and the increment uses the other, so 0801799C's split does not map here. `src/08081B24.c`
(`u32 width`) and `src/08085558.c` (`int width`) read `+0x15` into one wide local.

To ship, a source needs ROM evidence for the second variable: a distinct value or role the ROM computes, a reload,
or a ROM-copied helper whose `u8` parameter receives the field. None was found; a ROM-wide scan found no other
function with this shape.

## Source notes

- The halfword count is the matched siblings' idiom: a byte size `s32 size = (end - start) * 2;` before the loop and
  `(size / 2) & 0x1FFFFF` in the call, as `src/0808AA18.c` and `src/0801799C.c` write it. This closes the load-order
  swap of main's previous revision (0x0808103E/0x08081040).
- The remainder is written as a call to `func_08142950` (the `__modsi3` entry), as the matched `src/0801799C.c` and
  `src/08085558.c` write it, with the same declarations. `frame = frame % (state->unknown_17 * 2);` produces the same
  bytes, but `match.py` then refuses: `signed remainder numeric proof requires a frameless caller`.
- The parameter types are read off the entry narrowings: `s8 offset` (`lsls`/`asrs #24` at 0x08080F8A-0x08080F8C),
  `u8 palette` and `u8 count` (0x08080F78-0x08080F80). The callers declare it differently:
  `src/080837AC.c` as `(void *list, s32 row, u32 x, u32 y)` and `src/08082254.c` as
  `(Menu082254 *menu, s32 row, u32 x, u32 y)`.
- Declaration-order dependence (not a ROM computation order): the pair's initialiser runs first wherever it is
  declared, as the ROM's load at 0x08080F84 does, but its position changes pseudo numbering and with it the stack
  slots of the two hoisted invariants `start * 2` and `stride * 2`. Placed after `start`, `end`, `size`, `row` or
  `column` it matches; first, or after `rows`, `destination`, `frame`, `line` or `colored` (last), it gives 125/129
  with `[sp, #0x10]` and `[sp, #0x14]` swapped at 0x08080FF2, 0x08080FF8, 0x08081036 and 0x08081048.

## Ruled out

`match.py` stops every compile whose bytes differ at `signed remainder caller requires exact complete mapped ROM
bytes`, so each result below is from a raw compile (`agbcc -O2`, same recipe) disassembled with capstone: the number
of the ROM's 129 instructions (pad and literal pool excluded) that are identical at the same position, or the size
when it differs.

| variant | result |
|---|---|
| this source: `u32 stride` loaded, `u8 width` copy | MATCH 129/129, 272/272 (held) |
| `s32 stride` loaded, `u8 width` copy | MATCH (the same device) |
| one local, `u8 width`, `rows += width` | 264 bytes, 126 instructions (register moves only, above) |
| `u8 stride; u8 width = stride;`, or `u32` and `u32` | 264 bytes |
| `u8 width` loaded, `u32 stride = width;` (widening) | 268 bytes |
| two reads of the field (`u8` and `u8`) | 264 bytes (merged by CSE) |
| no local, every use reads `state->unknown_15`; the same with a `const State08080F68 *` or a `const u8` member | 260 bytes, 124 instructions |
| `u32 stride; s32 width = (u8)stride;` | 128/129 (`mov r5, sl` for `adds r5, r0, #0` at 0x08080F88) |
| the pair declared first | 125/129 (the stack slot swap, above) |
| copy matrix, loaded local for the increment, copy for the multiply and `end` (5 x 5 types: u8, u16, s16, u32, s32) | MATCH only for u16/u32/s32 -> u8 and u32/s32 -> u16; same-type, sign-only (u32/s32) and widening copies 264 bytes; u16/u32/s32 -> s16 268 bytes; an `s16` loaded local 272-276 bytes, at most 109/129 |
| copy matrix with the roles swapped (loaded local for the multiply and `end`, copy for the increment) | no match; closest u16 -> u8, 127/129, and u16 -> s16, 107/129; the rest 264-276 bytes or far |
| the whole body as a `static inline` with a `u8 width` parameter (first or last), called with `state->unknown_15` | 272 bytes, 117/129 (palette/count slots swapped); no out-of-line ROM function has that shape, and a whole-body wrapper is refused anyway |
| the same with `width` as the third parameter | 268 bytes |
| the same with the increment reading `state->unknown_15` | 260 bytes |
| no `size` local: `(end - start) & 0x1FFFFF` or `(((end - start) * 2) / 2) & 0x1FFFFF` in the call | 119/129 |
| `(size >> 1) & 0x1FFFFF` | 122/129 (stack slots and the mask load order differ) |
| `size = (end - start) * sizeof(u16)`, or `size` computed inside the loop | MATCH (both keep the pair) |
| `end = width; if (unknown_10 & 4) end -= 2;` | 126/129 (`adds r6, r5, #0` two instructions early, before the bit-2 mask at 0x08080FE0) |
| main's previous revision (`size = end - start` in the loop, `size & 0x1FFFFF`) | 127/129 (`ldr r2, =0x1FFFFF` / `ldr r3, [sp, #0xc]` swapped at 0x0808103E/0x08081040) |

From the earlier attempts (2026-11-16, not re-run here): the `src/0801799C.c` text with `count` added and the width
read from the state gives 264 bytes, and adding the pair at 0801799C's declaration position gives 125/129 (the slot
swap above); inline `tile_row`/`span_end` helpers 264 bytes; a per-row line pointer
(`u16 *line = rows + row * width`) 272 bytes and far; 2-D indexing (`rows[row * width + column]`) 288 bytes. Main's
previous revision traced its load swap in agbcc's dumps (the first loop pass substitutes the single-use invariant
`size & 0x1FFFFF` into the r2 set, the rerun pass hoists the mask constant, and reload breaks the tie the other way)
and ruled out `0x1FFFFF & size`, `u32 size`, five other placements of the `size` assignment, `size &= mask`, a fused
`(end - start) & mask`, `(x * 2 / 2)`, increments in the `for` header, 2-D indexing and swapped pointer increments.

kit issue: none (held by source policy, not a verifier gap)
