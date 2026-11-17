# 0x08017734 - tile-row copy over a region record: near miss, 258/280 bytes (280 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. The function copies `func_08017B50(region) * 2` tile
rows of a region record (the layout of the matched `src/08017618.c` and `src/0801799C.c`) to its destination. The
row count is formed once (`lsls #17; lsrs #16` after the call at 0x0801774E) and counted down in r9. Each source
row is `start + n` wrapped by `rows * 2` through the signed remainder at 0x08142950 (`bl` at 0x08017778). If the
callback at +0 is set, it is called through `_call_via_r3` (0x080177A2) with the context at +4 and
`index++ >> 1`. Its `u8` result goes into the palette nibble of the first two tiles, and the rest of the row is
copied from the third tile with `func_0814186C`, the CpuSet wrapper (0x080177CA). Without the callback the whole
row is copied (0x080177E2). With `flags & 4` the last two tiles get palette 0xD (0x080177E6-0x08017818). The
index row `08017734 0801784C 280 140 return` has the right extent (128 reachable instructions, 5 `bl`, code to
0x08017846, literal words at 0x080177D0, 0x080177D4 and 0x08017848). Its count column is the halfword count of
the span, not the instruction count. The function uses no named data.

## Byte identity

`08017734.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08017734, with `func_08017B50`, `func_08142950`,
`func_0814186C` and `_call_via_r3` bound to their ROM addresses (5 `R_ARM_THM_CALL`). `.text` is exactly 280
bytes, but the result is not the ROM: 106/128 reachable instructions identical (258/280 bytes). ROM span SHA-256
`9448833ac2c7a9e87c923bd6104b515d957572f71e2095aabf65ba604688931e`, linked symbol SHA-256
`8b93e69e63148f8e194cff851f12418add666e4010c917fecb5a059a92a404b7`.

All 22 differing instructions come from one register swap. The ROM keeps `region` in r5 and the row source
pointer in r6, and this build swaps them. The constant temporaries that share those registers swap too: the
0xFFF mask (`ldr r6, =0xFFF; mov sl, r6` at 0x08017766-0x08017768) and 0xD000 (`movs r6, #0xD0; lsls r6, #8;
adds r2, r6, #0` at 0x08017802-0x08017806). Each differing instruction differs only in a register field (one
byte each). The differing instructions are at 0x08017740, 0x0801774C, 0x08017754, 0x08017758, 0x0801775C,
0x08017766, 0x08017768, 0x08017772, 0x0801778A, 0x0801778C, 0x0801778E, 0x08017794, 0x080177A8, 0x080177B4,
0x080177BE, 0x080177DA, 0x080177E6, 0x080177F8, 0x08017802, 0x08017804, 0x08017806 and 0x0801781A. Instruction
order, the frame, the literal pools and every other instruction are identical.

`match.py --root . --no-write 0x08017734` stops before its own byte comparison with `compile failed: signed
remainder excludes mixed aliases, addressed calls with data, and other profiles`. With `--addressed-signed-runtime-profile
addressed-signed-runtime-r3-callback-data-v1` it stops with `addressed runtime ELF requires actual addressed
calls and no unresolved symbols`. `plausible.py --strict` exits 0.

## Cause

The bytes differ only in the allocation of `region` and the source pointer. The only change found that removes the
swap is a return type for `func_08017B50` (see Source notes).

Even with exact bytes this function cannot be verified at kit 18dcc516. It combines the addressed signed
remainder (`func_08142950`) with a `_call_via_r3` callback. The default path refuses any signed-remainder ELF
that also calls a `_call_via_rN` helper (`tools/match.py:1047-1054`; the helpers are `RUNTIME_HELPERS`,
`tools/match.py:129`). The r3-callback addressed-runtime selector is a data selector: it requires at least
one named-data relocation (`tools/addressed_signed_runtime_profile.py:866` and `940-943`), and this function
references no named data.

## Source notes

- **Return type of `func_08017B50` (open policy question).** Declared as `u32 func_08017B50(TileRegion
  *region);`, the source links to all 280 bytes (linked SHA-256
  `9448833ac2c7a9e87c923bd6104b515d957572f71e2095aabf65ba604688931e`, equal to the ROM span). The merged
  callers `src/08040280.c`, `src/08040E30.c`, `src/08042030.c`, `src/08042148.c`, `src/08042EC4.c` and
  `src/08042FDC.c` declare it that way. This entry does not publish that form. The callee `src/08017B50.c`
  returns `u16`, so `u32` here may be "a type chosen for where the allocator then puts the value", which
  AGENTS.md lists under "Does not ship". Other callers disagree: `src/08017E28.c` needs `u16` (with `u32` it
  differs in 50 bytes), and `src/0804F948.c` declares `s32` (it is also identical with `u32`, but 191 bytes
  differ with `u16`). The `u32` variant is refused by `match.py` with the same two strings as above. The ROM
  does not show which type the original declaration had: both forms produce the same `lsls #17; lsrs #16`
  after the call.
- The palette is held as `u8` (the ROM's `lsls #24` at 0x080177A6, then `lsrs #12` to put it in the top
  nibble).
- The byte size of the copy is formed as `(width - 2) * 2` before the loop (0x0801776A-0x08017770) and halved
  with `asrs #1` at the call (0x080177C4), as `src/0801799C.c` halves its byte size for the same CpuSet call.
  In the other branch the halving folds, and `width` is loaded from its stack slot straight into r2 (0x080177D8).
- `TileRegion` names only the members this function reads. The others are `unknown_*`.

## Ruled out

- The previous parked copy (main) had a `while (count != 0)` loop with an early return, a `u32` palette
  pre-shifted by 12, and the size computed once before the loop. It measures 93/128 instructions (226/280
  bytes): the same r5/r6 swap, plus the `(width - 2) << 1` store and the `lsrs r0, r0, #16` of the count
  scheduled differently (0x08017754-0x08017772), and the palette shift and the else-branch argument order out
  of place (0x080177A8-0x080177AE, 0x080177D8-0x080177DC). This source fixes those with a `for (i = count; i !=
  0; i--, row++)` counter, a `u8` palette and the per-branch size locals.
- From the earlier attempt: with the shift written inside the loop as `<< 1` and `>> 1`, combine folds the
  pair to `width - 2`, and computing the size before the loop puts it after the 0xFFF load. This source keeps
  the ROM's `asrs #1` by halving a signed byte size with `size / 2`, the spelling `src/0801799C.c` uses.
- The `u32` return type for `func_08017B50` makes the bytes identical (above). It is held as a policy question
  and is not published.

kit issue: shubshub/fftadecomp-kit#134 (the byte-identical `u32` variant is refused by it; the published source is not byte-identical)
