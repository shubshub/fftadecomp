# 0x0800F860 - byte-identical, parked on a policy question: the match needs a term that is always zero (218 bytes)

Target: complete `[0x0800F860, 0x0800F93A)`, 218 bytes, 105 instructions. Default flags; `data_02009160` is already in
config/data_symbols.json. Retried 2026-11-16 with kit fcdf2d45.

| file | result |
| --- | --- |
| `0800F860.c` (`height = y - start;` in the `height == 0` arm) | `MATCH - byte identical`, 105/105 instructions, 218/218 bytes (elf-symbol-thumb-frame-data-v1), plausible --strict clean |
| `0800F860-plain.c` (`height = y;`) | NOT MATCHING, 94/105 instructions, 199/218 bytes, plausible --strict clean |

Not shipped: on that path `start` is always 0, so the term does nothing at run time. Inert code waits for the
maintainers' answer to the policy question shared with 0x0800AF8C and 0x0800ADD8.

## What the function does (ROM)
- 0800F86E-0800F880: x, y, radius, height narrowed as u16, clip as u8; spans at [sp+0x34], clip at [sp+0x38].
- 0800F882: radius == 0 returns. 0800F886: `movs r0, #0` - start = 0, before the chain, on every path.
- 0800F888-0800F88E: clip == 0 arm, `adds r1, r5, #0` (y = height). 0800F890-0800F896: height == 0 arm,
  `adds r5, r1, #0` (height = y), a plain register copy with r0 (start) still 0. 0800F898-0800F89C: else arm,
  start = (u16)(y - height).
- 0800F89E-0800F8A8: y << 16 (spilled to [sp+0xc]), x << 16 (r8), radius >> 1 (sl) - GCSE's hoists of the two calls'
  shared argument terms, in that order.
- 0800F8AA-0800F8AC: `cmp r5, #0; beq` loop entry; 0800F8AE-0800F8E6: the loop runs height times and stores
  spans[start + i] when (s16)start is >= 0 (and <= 159 when clip).
- 0800F8E8-0800F926: func_0800ED58((s16)x, (s16)y, radius, radius >> 1, spans + height or spans, clip, 1).

## Why the plain form fails
`height = y;` differs in three places: the hoists come out as x << 16 (r8), y << 16 (sl), radius >> 1 ([sp+0xc]),
which swaps `ldr [sp+0xc]` / `mov sl` in both calls; the loop entry at 0800F8AC is `ble` instead of `beq`; and
`adds r2, r7, r6; mov ip, r2` replaces `adds r0, r7, r6; mov ip, r0` at 0800F8B2.

From the RTL: an int-typed right-hand side is expanded as a 16-bit narrowing (`(v << 16) >> 16`), and on this path cse
reduces it to y. That `y << 16` is the first occurrence of the expression in the function, so GCSE hoists it ahead of
`x << 16`; and the known 16-bit source lets combine turn the signed loop-entry test `height <= 0` into `== 0`. With
the bare `height = y` the pseudo is set from a register set twice, so combine keeps `ble`. A bare cast (`(u16)y`,
`(s32)y`, `y - 0`) is folded to the plain copy, so a second operand is needed, and the only ones that match,
`start` and `height`, are both 0 on that path.

Second witness: the unmatched sibling 0x0800F770 has the identical chain at 0800F79A-0800F7B0 and `cmp r3, #0; beq` at
0800F7B6-0800F7B8. In a source for it, changing `height = y;` to `height = y - start;` turns its `ble` into `beq` and
changes nothing else, so both functions carry the same signature of an int-typed right-hand side.

## Matching spellings (all 218/218, plausible clean) - the ROM cannot choose
`height = y - start;` (in `0800F860.c`), `height = y + start;`, `height = start + y;`, `height = y | start;`,
`height = y - height;`, `height = y + height;`, `height += y;`. All are no-ops on that path.

## Readings in which the term would be real - all refuted
| form | result |
| --- | --- |
| one `height = y - start;` after the chain for all three arms | 190/222 bytes, 77/105 (the subtraction is emitted after the join; the ROM has none) |
| the same shared by the two clip arms only | 190/222 bytes, 77/105 |
| `else { if (height == 0) height = y; start = y - height; }` | 191/218 bytes, 84/103 |
| `else if (height == 0) { height = y; start = y - height; }` | 196/222 bytes, 83/105 |
| `start = 0;` inside each arm, arm 2 `height = y - start;` / `height = y;` | 207/222, 88/103 / 188/222, 78/103 |
| `u16 start = 0;` as an initialiser, plain arm 2 | 196/218 bytes, 93/105 |
| nested `else { if (height == 0) height = y; else start = y - height; }` | 199/218 bytes, 94/105 (same code as plain) |
| arms reordered | 193/218 bytes |
The ROM fixes the arrangement: `movs r0, #0` at 0800F886 dominates the chain, the fall-through arms are clip == 0 then
height == 0, and the height == 0 arm is one copy followed by a jump to the join.

## Ordinary forms without a no-op term - none match
| form | result |
| --- | --- |
| `height = y;`, `y - 0`, `(u16)y`, `(s16)y`, `(s32)y`, `(u32)y`, `(u16)(s32)y`; `!clip` / `!height`; `(s16)height == 0` | 199/218, 94/105 each |
| `height = clip ? y : height` | 199/218 (folded) |
| `s16 start` / `s32 start` with plain arm 2 | 94/105 / 92/105 |
| loop bound `i < (s32)height`; a separate `u16` or `s32` count | 94/105 each |
| `u32 i` or `(u32)i < height` | 183/218, 81/105 |
| `u16 i` / `s16 i` | 170/218, 72/105 / 154/234, 50/110 |
| `i != height` | 185/218, 83/105 |
| pointer walk with `for (i = height; i != 0; i--)` | 138/224, 40/106 |
| `s16 row = start;` / `s32 row = (s16)start;` in the loop, plain arm 2 | 196/218, 90/105 / 199/218, 94/105 |
| old-style (K&R) definition, plain arm 2 | same code as plain |
| `s32 cy = y;` working copy (then `height = cy;` is a real truncation); `u32 cy` | 216/218, 104/105 (y's entry `lsrs` moves after the clip narrowing) |
| `s16 cy` | 214/218, 103/105 |
| `cy = y;` as a statement after `start = 0;` / at the start of the else / in each arm | 212/222, 86/105 / 187/222, 76/103 / 207/226, 84/106 |
| y used in the chain, `cy = y;` after it; in each arm | 190/222, 77/103; 191/226, 76/107 |
| a single-set centre local assigned after the chain, plain `height = y` | `beq`, but 77/103 (extra moves) |

## Rest of the source (holds for both files)
- Callee: func_0800ED58 is unmatched (Parked/0800ED58); its entry narrows x, y and both radii as u16 and the two stack
  bytes as u8. `s16 x, s16 y` is needed for the `asrs #16` at 0800F8EE/0800F8F2 and 0800F912/0800F916 (`u16` gives
  210 bytes; `s32` with explicit `(s16)` casts also matches); src/0800E4DC.c declares the family `s16 x, s16 y`.
  Seven arguments; the stack words spans, clip and 1 at [sp], [sp+4], [sp+8].
- Own prototype: the entry narrowings agree with `(u16 x, u16 y, u16 radius, u16 height, Span *spans, u8 clip)`; the
  callers (src/0800E4DC.c, src/0800FDFC.c, src/0801040C.c, src/08010464.c) use no result.
- Span: `left` at +0, `right` at +2, stride 4, names as src/0800E718.c. Constants 159/160, radius >> 1, direction 1;
  data_02009160 is read with ldrb.
- `radius + x + data_02009160` follows `adds r0, r7, r6` at 0800F8B2 (`x + radius`: 217/218, 104/105).
- No merged function has this arm chain: src/0800E718.c has `if (clip == 0) center_y = y;`, src/0800E878.c
  `center_y = 0; if (side == 0) center_y = radius;`, and Parked/0800ED58 and Parked/0800F6A8 a single clip == 0 arm.

kit issue: shubshub/fftadecomp-kit#201 (policy question)
