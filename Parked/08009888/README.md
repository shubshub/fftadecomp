# Parked: func_08009888 (40 bytes)

**Source is plausible; the bytes still cannot be produced in isolation.**  Same
wall as `0x0800BC08` and `0x0800BC28` — this is the third function blocked on
the linked build.

## What it does

Five literal pools:

| pool | address | value |
|---|---|---|
| A | `0x080098B0` | `0x03000ED0` |
| B | `0x080098B4` | `0x02000000` |
| C | `0x080098B8` | `0x00002FBE` |
| D | `0x080098BC` | `0x00002FBF` |
| E | `0x080098C0` | `0x00002FBC` |

r0 is a **base pointer** (`0x02000000`, the first word of EWRAM) and each of the
three accesses adds a **separate field offset from its own pool entry**.  So:

```
[0x03000ED5] = 1        ; A + 5
[0x03000ED4] = 0        ; A + 4
[0x02002FBF] = 0        ; B + C
half [0x02002FBC] = 0   ; B + E
[0x02002FBE] = 0        ; B + D
```

The three simultaneously live values are what forces the frame, and `pop {r0}`
confirms a void return.

## Why it will not match

agbcc emits *base + separate pool offsets* only when the base is a **symbol it
cannot see through**.  Every relocation-free spelling folds the offsets into
the address:

* literal `u8 *block = (u8 *)0x02000000` + offsets → one pool entry plus
  `sub #3` / `add #2`; 36-byte symbol, **no frame**, `bx lr`
* offsets in `u32` locals → folded identically
* wide offsets (0x1F1C / 0x2190 / 0x2191) → each address folded into its own
  absolute constant, with `add r0,r0,#1` for the adjacent pair
* four separate literal pointers → right frame, five pool loads, but three full
  addresses instead of one base + three offsets, and the store order differs

The symbol form gets the family right — instructions 2-5 are identical to the
ROM — but its pool holds `.word g_02000000`, an `R_ARM_ABS32` data relocation,
and `match.py` rejects those.  Six field/store orderings were tried; the best
was 2 of 20 target halfwords, because gcc merges the offsets
(`add #1`, `sub #2`, `sub #3`) instead of giving each its own pool, and never
needs r4 so the frame never appears.

## Corroboration worth keeping

`0x02000000` is used as a literal-pool base in roughly 40 places in the code
region.  `func_080099C4` (offsets 0x1F1C / 0x2190 / 0x2191, plus a ROM table
pointer at `0x085516D0`) and `func_0802DA00` (0x2FC4) use the identical
base-plus-separate-offsets shape.

So there is one EWRAM object at `0x02000000` of at least 0x2FC0 bytes with
members scattered across 0x1F1C-0x2FC4, and one IWRAM object at `0x03000ED0`
(also referenced at `0x080021AA`).  That is a genuine piece of reverse
engineering, recovered incidentally from the match attempt.
