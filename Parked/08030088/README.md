# 0x08030088 - parked, no match

Best attempt: 63 of the ROM's 105 instructions. Recovered C in the agent's
report; the source is summarised below. Four separate differences remain, all
with one root cause.

## First, the index was wrong

`config/functions.json` said 56 bytes / 28 instructions, cutting at a `bne`.
The function actually runs to the interworking epilogue at `0x0803014A`
(`pop {r4,r5}; pop {r0}; bx r0`) with its pool at `0x08030150..0x08030167` -
**224 bytes, 105 instructions**. The 28 indexed instructions were the prologue.
The span has been corrected in the index.

## What was established (each confirmed by compiling)

- **Masks are `~0x20` / `~0x40`, not `~0x21` / `~0x41`.** agbcc expands `~x` as
  `-(x+1)`, so `movs #0x21 / rsbs #0` is `~0x20`. Written as a literal agbcc
  folds it to `movs #0xDF`; it only emits the `movs`/`rsbs` pair when the mask
  goes through a local, hence the two `u32` locals.
- **`(*(State **)0x03002810)`, not `State *s = *(State **)…`** - only the
  pointer-to-pointer form reloads the state after every store.
- The loop is **30 iterations of stride 12, signed countdown**:
  `while (n >= 0) { …; n--; }` with a separate byte `off` gives exactly
  `movs r4,#0x1d / adds r2,#0xc / subs r4,#1 / cmp r4,#0 / bge`.
- Loop offsets are **0xB0..0xB3**, above `strb`'s 0x7C immediate range.
- Store order `0xB1, 0xB0, 0xB3, 0xB2` is source order, the same quirk as the
  matched `func_08030044`.
- `tail = 0x3AA; ptr[tail] = 1; tail++; ptr[tail] = 1;` is the only spelling
  giving one pool word and `adds r2,#1`.

## What is left, and why

42 instructions in four places: the prologue load order, the mask placement,
three `strh` reloads, and the clearing loop. All four are the same problem -
agbcc has to treat the base pointer as **opaque** so that byte stores
invalidate its reloads, but a literal `(u8 *)0x02002C10` is constant-propagated.

An `extern u8 g_02002C10[]` *does* produce the base+offset shape, but agbcc
then proves those stores cannot reach `0x03002810` (an undefined symbol is
address 0 in an unlinked object) and keeps the state in a callee-saved register
instead of reloading - and the symbol form leaves an `R_ARM_ABS32` that
`match.py` refuses regardless.

Ruled out: an extra load level, the base as a parameter, `volatile` (banned),
`u8 *e = base + off`, a base-at-0xB0 local, a struct-typed entry pointer,
`for (i = 0; i < 30; i++)`, a pointer walk `e += 12`, `do..while (n >= 0)`.

## Also found

`func_08043F64` and `func_080D2E60` were missing from the index and are now
added; `match.py` had a hard cap at `0x08150000` that would have rejected
`0x080D2E60` regardless. Both fixed, so a later attempt at this function starts
from a working verifier.