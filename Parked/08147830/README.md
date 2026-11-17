# 0x08147830 - RGB555 two-colour blend: byte-identical, held by source policy (172 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. `u16 func_08147830(u16 color, u16 reference, u8 amount,
u8 mode)` splits both colours into their three 5-bit channels, scales the reference channels by `amount / 16` and
the colour channels by `mode / 16` (each `muls` then `lsrs #4`, 0x08147880-0x081478A2), adds them per channel,
clamps each sum to 31 (`bls` at 0x081478AC, 0x081478B4, 0x081478BC) and packs `red | green << 5 | blue << 10`. The
parameter types come from the entry narrowings (0x0814783A-0x08147848) and agree with the callers' declarations in
`src/08147D94.c`, `src/08147E28.c` and `src/08148274.c`. The index row `08147830 081478DC 172 86 return` is right
(86 reachable instructions, no literal pool). It references no data; no data symbol is needed.

## Byte identity

`08147830.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`); it has no relocations. The 172-byte symbol equals the ROM span
`[0x08147830, 0x081478DC)`: SHA-256 `79870cb187c40f152b9902a3f01d906d66a49dfe2dbd3de698f0cae9618a0b18` for both.
`.text` is exactly 172 bytes. `match.py` with default flags reports `MATCH - byte identical`, 86/86 instructions
(172/172 bytes). `plausible.py --strict` exits 0.

## Refusals

No verifier refusal: kit 18dcc516, `match.py --root . --no-write 0x08147830` with this source copied to
`src/08147830.c` prints `verdict MATCH - byte identical`.

It is held by the source policy, AGENTS.md "Evidence first: what is a fake": source that exists because it moved the
bytes does not ship. The match needs the green and blue extractions written as two statements,

```c
reference_green = reference & 0x3E0;
reference_green >>= 5;
```

where the one-expression spelling `(reference & 0x3E0) >> 5` emits the same `ands` then `lsrs` instructions
(0x0814785A-0x0814787C). The split leaves nothing in the ROM; it only sets each channel's pseudo twice, which changes
register allocation.

## Cause

The one-expression form (u32 channels, `u16` scaled reference values) compiles to 164 bytes: it saves r8/r9/r10 and
reserves 8 stack bytes, where the ROM saves r8/r9 and reserves 4 (0x08147830-0x08147838). The split is chosen by its
effect on that allocation, not by any coding style the ROM fixes: splitting only `reference_blue` matches, and so
does splitting only `reference_green` and `color_green`, while splitting only the two colour channels gives 170
bytes. Every merged sibling writes the extraction as one expression: `src/0814774C.c`, `src/081477DC.c`,
`src/081478DC.c`, `src/08147958.c`, `src/081474BC.c`, `src/081473E4.c`, `src/0814731C.c`, `src/081481AC.c`,
`src/08148384.c` and `src/081475A4.c`.

## Source notes

- The channels are unsigned 32-bit: each scale is `muls` then a plain `lsrs #4` (0x08147880-0x081478A2) and the
  clamps are unsigned (`bls`). The siblings type their channels `u16`/`s16`; here `u16` channels give 186 bytes (the colour
  channels scaled in place and the three sums are truncated to 16 bits, `lsls #12; lsrs #16` and
  `lsls #16; lsrs #16`, which the ROM does not do) and `u16` channels with `>> 4` give 170 bytes.
- The `u16 scaled_reference_*` locals are sibling style. With the one-expression extraction `u16` and `u32` scaled
  locals give the same 164 bytes, so that type is not what moves the allocation.
- Order shown by the ROM: the reference channels are extracted before the colour channels, the reference is scaled
  by `amount` before the colour by `mode`, then the three sums in place, the clamps and the pack. 0x3E0 and 0x7C00
  are built once and kept in sb and r8.
- The ROM's `sub sp, #4` (0x08147838) has no stack access; the split source reproduces it, the one-expression form
  makes it 8.

## Ruled out

Compiled on this attempt (sizes are the complete symbol; `match.py` stops shorter compiles at
`compiled symbol is shorter than the indexed span`):

| variant | result |
|---|---|
| this source: all four green/blue extractions split, u32 channels, u16 scaled | MATCH 86/86, 172/172 (held) |
| only `reference_blue` split | MATCH (the same device) |
| only `reference_green` and `color_green` split | MATCH (the same device) |
| only `color_green` and `color_blue` split | 170 bytes |
| one-expression extraction throughout (siblings' text), u32 channels, u16 scaled | 164 bytes; r8/r9/r10 saved, 8-byte frame |
| one-expression, `u16` channels, `/ 16` | 186 bytes, `NOT MATCHING - bytes differ`, 21/93 instructions |
| one-expression, `u16` channels, `>> 4` | 170 bytes |
| one-expression, sums into new `red`/`green`/`blue` locals (u32 or declared first) | 170 bytes; `u16` sums 164 bytes |

From an earlier pass of this attempt (not re-run here), all with one-expression extraction: u32, s16, s32, int and
unsigned scaled locals 164 bytes; s32 channels 164-196 bytes; the reference scaled in place 168 bytes; per-channel
`color = color * mode / 16 + reference * amount / 16` 164 or 168 bytes; scale, add and clamp per channel (blocks
like `src/08148384.c`) 172 bytes but a different allocation; compound `x *= m; x >>= 4;` 152 bytes; shift-then-mask
`(c >> 5) & 0x1F` 144 bytes; `c >> 10` without a mask 152-156 bytes; the shift folded into the scale 152 bytes;
sibling-style initialised declarations 164 bytes; 144 combinations of clamp spelling, multiply operand order, sum
target, extraction order, scaled type and in-place or new-local scaling, 164-180 bytes, none matching (the closest
reported was sums into new locals with the colour scaled in place, 172 bytes with the ROM's prologue and
extraction; the spelling rebuilt on this attempt gives 170 bytes, so that result is not confirmed); 192
declaration-order permutations, of which only the split forms with `u16` scaled locals match, whatever the order. A channel array (the ROM never touches the stack),
a bit-field colour view (it would need memory or emit `lsls`/`lsrs` pairs, not `ands 0x3E0`) and shifting the
parameter in place (shift-then-mask instructions) do not fit the instructions.

From the earlier attempt (main's previous revision of this entry, with the then `first`/`second` naming): in-place
32-bit channels 166 bytes; separate scaled contributions 164 bytes; 16-bit channels 170 bytes; separate output
channels 156 bytes.

kit issue: none (held by source policy, not a verifier gap)
