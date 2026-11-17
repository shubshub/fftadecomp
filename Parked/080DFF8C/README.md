# 0x080DFF8C - staged three-knot curve sampler callback: near miss, 686/690 bytes (690 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. This is the task callback that the matched constructor
`src/080E0730.c` installs through `func_08005B6C` with a 0x60-byte payload. It takes `(task, descriptor,
payload)`, switches on the descriptor's `u16` phase and returns 0. Phase 0 copies the request (four `s16`
coordinates, the `u16` magnitude, the direction byte, the `u16` sample count and the two output pointers)
into the payload and leaves the phase unchanged. Phase 0x100 picks a perpendicular direction for the chord.
It uses defaults per direction byte, with special cases when the start and end share x or y. It turns that
direction into an angle with `func_08141860` (the `svc 0x0A` ArcTan2 wrapper, 0x080E00E6) and offsets the
chord midpoint by `magnitude` along the angle through the matched readers of the `s16` table
`g_table_08149568`, `func_08007A60` (entry `index + 64`) and `func_08007A4C` (entry `index`) (0x080E011E,
0x080E0146). It then stores three 16.16 knots for x (+0x18),
y (+0x30) and the sample coordinate (+0x48), and advances the phase. Phases 0x101 and 0x102 sample x and y
into the two outputs with the matched `func_080E06A4` (0x080E0204, 0x080E0222). Phase 0x102 then sets the phase
to 2. The index row `080DFF8C 080E023E 690 337 return` is right: 337 reachable instructions (5 `bl`), code to
0x080E023E, one literal word (0x101) at 0x080DFFC4 behind a 2-byte pad at 0x080DFFC2. No data symbol is
needed.

## Byte identity

`080DFF8C.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080DFF8C, with `func_08141860`, `func_08007A60`,
`func_08007A4C` and `func_080E06A4` (twice) bound to their ROM addresses (5 `R_ARM_THM_CALL`). The symbol is
690 bytes. `.text` is 692 bytes, and the last two (`c046`) are assembler filler after the symbol. ROM span
SHA-256 `bf51c9cb9aef84b159f7a8f383240e95293f7bcffd8be8f783720697926f1765`, linked symbol SHA-256
`d7bc51a785e7f230f96a77c6778d9b16903eb61e818bdf16eba569ac62f08598`: 4 bytes differ.

`match.py --root . --no-write 0x080DFF8C` runs its byte comparison and reports `verdict NOT MATCHING - bytes
differ` and `333/337 instructions identical (686/690 bytes)`. `plausible.py --strict` exits 0.

The four differing instructions are the two loads of `payload->magnitude` and the multiplies that use them:

| Address | ROM | This build |
|---|---|---|
| 0x080E0126 | `ldrh r2, [r7, #8]` | `ldrh r1, [r7, #8]` |
| 0x080E0128 | `muls r0, r2` | `muls r0, r1` |
| 0x080E014E | `ldrh r2, [r7, #8]` | `ldrh r1, [r7, #8]` |
| 0x080E0150 | `muls r0, r2` | `muls r0, r1` |

Everything else is identical: the 28-byte frame, the switch, every direction arm, the knot stores and both
sampler calls.

## Cause

The difference is one register choice for a short-lived temporary. After each table call the ROM puts the
magnitude in r2, multiplies, and then copies the midpoint into r1 (`mov r1, sl` / `mov r1, sb`, then `lsls r2,
r1, #16`). This build puts the magnitude in r1, which the midpoint copy overwrites straight after. Both
registers are dead at that point. None of the variants listed under Ruled out moved the magnitude to r2.

## Source notes

These choices are not pinned by the bytes or are open doubts:

- The defaults are stored at the top of each direction block (0x4000 and 0 at 0x080E0000-0x080E0008; 0xC000
  and 0 at 0x080E006E), before any coordinate test.
- Each equal-y arm stores `x = 0` itself (0x080E0044, 0x080E0050; 0x080E00B2, 0x080E00BE). It is not hoisted
  above the inner test.
- `x` and `y` (sl and sb) hold the direction for `func_08141860`, and are then reused for the chord midpoint
  (0x080E0102, 0x080E0118). Two variables carry both meanings.
- The negated difference is kept in an `s16` local (`dx` in direction 0, `dy` in direction 1) before it is
  negated into a `u16`.
- The angle is a `u16` shifted right by 8 to give the `u8` table index (`lsls #16` after the call, `lsrs
  #24` at 0x080E011A).
- The midpoint offset is written product first, `((table * magnitude) >> 8) + (s16)midpoint`.
- The direction and midpoint values are `u16` with `(s16)` casts at their uses, which matches the
  `lsls #16; asrs #16` pairs. The parameters are typed, and the coordinates are loaded once into locals.
- `func_08007A4C` is declared returning `s32` and `func_08007A60` returning `s16`, as their matched sources
  declare them. The sine result is cast to `s16` at its use, because the ROM narrows it (`lsls #16; asrs #16`
  after 0x080E0146).
- `CurveDescriptor.unknown_02` and the layout past +0x18 come from the offsets used here and the 0x60
  payload size in `src/080E0730.c`.

## Ruled out

- The previous parked copy (main) compiles to a 654-byte symbol, 36 bytes short of the span. `match.py` stops
  with `compiled symbol is shorter than the indexed span: 654 < 690`, and 644 of the 690 span bytes differ
  when it is linked by hand. That copy used `s16` working values with ternaries, separate midpoint locals, a
  `u8` index taken from the ArcTan2 result, a midpoint-first addition and `* 65536`. This source changes those
  to `u16` working values with defaults at the top of each block, `x`/`y` reused for the midpoints, a `u16`
  angle, a product-first addition and `<< 16`, and reaches 686/690.
- Variants of this source, each measured by linking at 0x080DFF8C (symbol size, differing bytes of 690):
  - `(s32)payload->magnitude` in both products: 690, 4 (the same bytes as this source).
  - Table result in an `s16` local before the product: 690, 4 (the same bytes as this source).
  - Operands swapped, `payload->magnitude * table`: 690, 12 (from 0x080E0122).
  - Midpoint-first addition, `(s16)x + ((table * magnitude) >> 8)`: 690, 48 (from 0x080E0122).
  - `u8` angle, `angle = func_08141860(x, y) >> 8`: 690, 47 (from 0x080E00EE).
  - Separate `s16` midpoint locals instead of reusing `x`/`y`: 664, 555.
  - Magnitude cached in a `u16` local after the ArcTan2 call: 698, 351.
  - `* 65536` instead of `<< 16` for the two midpoint knots: 672, 559.

kit issue: none (not byte-identical)
