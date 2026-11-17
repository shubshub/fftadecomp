# 0x08007F9C - 16.16 fixed-point natural cubic spline setup: bytes identical, refused (`__divdi3` / `__muldi3` calls have no binding) (848 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. The function fills in the coefficients of a natural cubic
spline through `count` nodes of 80 bytes each (ten `s64` 16.16 fields: position, value, the three segment
coefficients, curvature, and the four tridiagonal-system fields `lower`, `upper`, `right_hand_side`, `diagonal`). For
each interior node it builds one row of the tridiagonal system: `lower = (previous_width << 16) / total_width`,
`upper = 0x10000 - lower`, the right-hand side `(((next_slope - previous_slope) << 16) / total_width) * 6` (each
slope being `((value difference) << 16) / width`), and `diagonal = 0x20000`. The `* 6` is inline shifts and adds
(0x08008074-0x0800808A). It then eliminates forward, solves for the curvatures backward with zero end curvatures, and
derives each segment's `quadratic`, `cubic` and `linear` coefficients. The `s64` arithmetic is 15 runtime calls: `__divdi3` (0x08142280) at 0x08007FFC, 0x0800802E,
0x08008052, 0x08008070, 0x080080DC, 0x080080FA, 0x08008178, 0x08008244 and 0x0800826A, and `__muldi3` (0x08142A20) at
0x08008112, 0x08008134, 0x0800819C, 0x0800827A, 0x08008294 and 0x080082A6. The index row
`08007F9C 080082EC 848 401 return` is right: 401 reachable instructions in 832 bytes of code, then a 16-byte pool
holding the `s64` constants 0x10000 and 0x20000 (0x080082DC-0x080082EB). No data symbol is needed.

## Byte identity

`08007F9C.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08007F9C, with `__divdi3` bound to 0x08142280 and
`__muldi3` to 0x08142A20 (15 `R_ARM_THM_CALL`, no data relocations). The 848-byte symbol equals the ROM span
`[0x08007F9C, 0x080082EC)`: SHA-256 `5420efe130f4c359f16c4d1dc13cd4f1de3002069b1f57f8f2fb2313b9ed85aa` for both.
`.text` is exactly 848 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict`
exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08007F9C.c`: the default run and all 213
selector values. None matched. The outcomes are the same as for `0x080086D0`, except for the instruction quoted by the
switch selectors.

| Selector | Refusal |
|---|---|
| default, both `--*-quotient-profile` values, both `--signed-runtime-profile` values, `--unsigned-runtime-profile unsigned-divmod-ten-v1`, the six `--function-address-profile` values and the ten `--switch-data-profile` values (22) | `call target must be an undefined addressed function` |
| all 42 `--addressed-signed-runtime-profile` values; 113 owner-runtime selectors, among them `named-data-buffer-v1`, `bounded-buffer-runtime-summaries-v1`, `restoring-owner-runtime-v1`, `canonical-integer-scalar-source-v1` and `static-callback-buffer-v1`; `--software-double-profile convert-sub-div-target-v1`; `--control-flow-profile mixed-return-inert-spin-v1` (157) | `function address requires a canonical addressed function` |
| the three `--switch-profile` values | `unsupported compiler assembly statement: 'ldr\tr2, [r4]\t\t@ created by thumb_load_double_from_address'` |

The other 32 selector values stop on requirements this function does not meet: a private float or double helper (15),
an external two-byte alignment pad (12), the -O0 toolchain, a palette bundle, a 96-byte owner, an entry-recursive
owner without a frame, or the software-double remainder profile.

## Cause

This is the same gap as `0x080086D0`. `match.py` resolves each call relocation by its symbol name
(`tools/match.py:842-950` at 18dcc516), and no profile binds `__divdi3` or `__muldi3`. Both names reach the generic
branch, which requires a `func_XXXXXXXX` name and refuses with `call target must be an undefined addressed function`
(`tools/match.py:942-944`); the selectors that resolve calls through `function_address_target`
(`tools/match.py:607-610`) refuse them with `function address requires a canonical addressed function`. Naming the routines as `func_08142A20` cannot pass that branch either: 0x08142A20 lies
inside the identities reserved by the software-double and software-float profiles (`division runtime requires its
canonical compiler alias`, `tools/match.py:948-949`).

## Source notes

- The 16.16 scalings are written `x << 16` on signed `s64` values. Some of those values can be negative, and a left
  shift of a negative signed value is undefined in ISO C. agbcc emits the plain 64-bit shift sequence that the ROM
  has (for example 0x08007FEE-0x08007FF6). The defined spelling `* 65536` compiles to a different body with a
  4-byte-larger frame (below).
- `total_width` is a variable: the ROM forms `previous_width + next_width` once (0x08007FE2-0x08007FE8) and keeps it
  at sp+0x18 (0x08007FEA) before the first shift and division. Writing the sum inline at both uses gives other code
  (below).
- The declaration order of `width`, `previous_width`, `next_width` and `total_width` is load-bearing, because it
  sets their stack slots. Moving `width` after the other three gives other code (below).
- The node field names (`lower`, `upper`, `right_hand_side`, `diagonal`, `curvature`, `linear`, `quadratic`, `cubic`)
  describe the computation. They are not taken from a caller or another source, and no caller was examined.

## Ruled out

- `* 65536` in place of each of the nine `<< 16`, everything else unchanged: 860 bytes. 803 of the overlapping bytes
  differ, the first at 0x08007FA6 (the ROM's `sub sp, #0x48`; the multiply form allocates 76 bytes).
- `width` declared after `previous_width`, `next_width` and `total_width`: 848 bytes, 25 differ, first at
  0x08007FDE.
- No `total_width` variable (the sum written inline at both uses): 860 bytes. 711 of the overlapping bytes differ,
  the first at 0x08007FB2.
- The previously parked copy (`* 65536` with separate block-scope temporaries for the slopes and the eliminated
  values) is 872 bytes. 790 of the overlapping bytes differ, the first at 0x08007FA6, and it overruns the following
  function by 24 bytes.

kit issue: shubshub/fftadecomp-kit#80
