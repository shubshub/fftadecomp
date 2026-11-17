# 0x08021D48 - flag-negated offset pair read: near miss, compiles to 76 of 78 bytes (78 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. The function copies two `s16` values at +0x18 and +0x1A
of an object to `*first` and `*second`, then negates `*first` once for each of the flag bits 0x20, 0x200 and
0x400 that is set in the object's `u32` flags word at +0. Each test reloads the flags word (`ldr r0, [r4, #0]`
at 0x08021D56, 0x08021D68 and 0x08021D7C). The matched caller `src/0808F1F4.c` passes the addresses of two
local offsets. The index row `08021D48 08021D96 78 39 return` is right: 39 reachable instructions, no calls,
no literal pool. No data symbol is needed.

## Byte identity

`08021D48.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked at 0x08021D48 (no relocations). The symbol and `.text` are 76
bytes, 2 short of the span: 38 instructions against the ROM's 39. ROM span SHA-256
`ff76d1f9c056cb31d48ba7857723d72d47258d1447dbe5fd1a38913f43ce7d25`, linked 76-byte symbol SHA-256
`f3a4784e182569989ec5a89ae88ab76b296c4cd4227e3370a984914cdac28d60`.

`match.py --root . --no-write 0x08021D48` stops before its byte comparison with `compiled symbol is shorter than
the indexed span: 76 < 78`. `plausible.py --strict` exits 0.

The first 16 instructions (0x08021D48-0x08021D66: both copies and the whole 0x20 test) are identical. Then:

- 0x08021D68-0x08021D6C: the ROM reloads the flags into r0 and builds the 0x200 mask in r1. This build loads
  the flags into r1 and the mask into r0, because it keeps the flags for the third test.
- 0x08021D74-0x08021D76: the zero index of the `ldrsh` for the second negation is r1 in the ROM and r2 here.
- 0x08021D7C: the ROM's third `ldr r0, [r4, #0]` is missing. This build tests the second load again
  (`ands r1, r0; cmp r1, #0` against the ROM's `ands r0, r1; cmp r0, #0`).
- The third negation and the epilogue are the same instructions, 2 bytes earlier.

In instruction order, 28 of the ROM's 39 instructions appear unchanged in this build.

## Cause

GCSE removes the third flags load. The earlier attempt's gcse dump shows partial redundancy elimination
treating the store through `first` in the second if-body as not clobbering `object->flags`, so it reuses the
value loaded for the second test instead of reloading. It does not do the same across the first if-body,
although that body compiles to the same store. The evidence measured in this attempt with this source:

- With `-fno-gcse` added (a diagnostic only; the flags are fixed), the bytes are identical (linked SHA-256
  equal to the ROM span). `match.py --flags "-mthumb-interwork -O2 -fno-gcse"` now reports `verdict NOT
  VERIFIED - bytes equal under a non-default toolchain, which is admitted only as a library unit's toolchain
  inside that unit` with `39/39 instructions identical (78/78 bytes)`.
- `-O1` instead of `-O2` also gives identical bytes.
- `-fno-strict-aliasing` does not change the result (76 bytes, the same SHA-256 as above), so type-based
  aliasing alone does not explain it. This attempt's reading of agbcc's alias handling is that the `s16`
  store through `first` is never seen to conflict with the `u32` load from the object. That reading was not
  re-derived for this entry.
- With only two tests, the second reload survives (58-byte symbol, two loads of the flags word). The removal
  happens only on the third test.
- `volatile u32 flags` gives identical bytes. `volatile` is refused by AGENTS.md ("Do not fake a match"), and
  the flags word is ordinary RAM, so that is not a source.

## Source notes

- `flags` is a plain `u32` tested with masks, as in the matched neighbours `src/08021D14.c` and
  `src/08021DA8.c`, which also test a `u32` flags word at +0 of their object.
- The negation is written `*first *= -1`, which gives the ROM's `ldrsh; negs; strh` for each test.
  `*first = -*first` loads with `ldrh` instead (below).
- `FlaggedPair` names only +0, +0x18 and +0x1A. The caller declares the object as `const void *`.

## Ruled out

All measured in this attempt with this source and the fixed flags (symbol size, differing byte positions of
78):

- `*first = -*first` instead of `*first *= -1`: 70 bytes, 54 (`ldrh` instead of `ldrsh`, and the third
  load is still removed).
- The negations done in an `s16` local and stored once: 68 bytes, 70.
- `const FlaggedPair *object`: 76 bytes, the same SHA-256 as this source.

From this attempt's search, not re-measured for this entry: a union over the flags word, helper functions,
and `const void *` and `s32` spellings. None of them kept the third load. From the earlier attempt (kit
fcdf2d45): bitfield flags give `ldrb`, `lsl #26` and `bge` with a different allocation. This source is the
previous parked copy with only a comment added.

kit issue: none (not byte-identical)
