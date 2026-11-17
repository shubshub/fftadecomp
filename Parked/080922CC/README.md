# 0x080922CC - motion set-up towards a projected point (ArcTan2): bytes identical, refused (ArcTan2 wrapper in the buffer walk) (194 bytes)

Attempt 2026-11-18, kit 750d2fb7, decomp main 52ef3ba2f9.
`func_080922CC(state, first, second, third, add_x, add_y, value_20, value_14)` projects the point with
`func_0801C918(first, second, third, &out[0], &out[1], &out[2])` (0x080922FC), stores the target `(out + add) << 8`,
reads the current view position with `func_0801E6F0(&view[0], &view[1])` (0x0809232C), stores it as the current
position, keeps the larger of |dx| and |dy| in `unknown_24` and sets `angle` from ArcTan2 (`func_08141860(dx >> 8, dy
>> 8)` at 0x08092376). Callers: three sites in 0x08092784 (0x080935A8, 0x080952D2, 0x0809692C; it has a `Parked/`
entry) and the matched `src/08096F3C.c` (0x08096F6A).

The index row `080922CC 0809238E 194 94 return` is right: 94 reachable instructions, the count the kit's own CFG
refinement gives. `config/functions.json` has the same extent and count.

## Byte identity

`080922CC.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080922CC, with every callee and data symbol bound to its
ROM address (3 `R_ARM_THM_CALL`). The 194-byte symbol equals the ROM span `[0x080922CC, 0x0809238E)`: SHA-256
`193b6fb0d4edcaae26088f18df27b49e776b0bc2b2ba509b0e837ed21781228f` for both. `.text` is 196 bytes: the symbol and the
`c0 46` alignment halfword after it. `match.py` refuses before its own byte comparison (below). `plausible.py
--strict` exits 0.

## Refusals

Kit 750d2fb7, `match.py --root . --no-write` with this source copied to `src/080922CC.c` (no data symbol to add): the
default run, the BIOS buffer selectors, the two addressed BIOS-fill-buffer selectors, `named-data-buffer-v1`, and the
selectors the #192 comment and earlier notes name. None matched.

| Selector | Result |
|---|---|
| default, `bounded-buffer-guarded-bios-division-v1` and `named-data-buffer-v1` (3) | `buffer callee 0x08141860: non-leaf calls and interrupts require linked CFG verification` |
| `bounded-buffer-bios-sqrt-scratch-v1` | `BIOS Sqrt requires exact complete svc #8; bx lr wrapper` |
| `bounded-buffer-bios-fill-source-v1`, `bounded-buffer-bios-fill-local-source-semantics-v1` and `bounded-buffer-bios-fill-overwritten-control-stores-v1` (3) | `BIOS fill requires an actual direct call in its closed owner` |
| `bounded-buffer-bios-fast-fill-source-v1`, `bounded-buffer-bios-mixed-fast-fill-source-v1` and `bounded-buffer-bios-mixed-fast-fill-runtime-summaries-v1` (3) | `CpuFastSet fill requires only its actual direct wrapper calls` |
| `bounded-buffer-bios-bg-affine-set-v1`, `bounded-buffer-bios-bg-affine-set-transparent-leaf-scratch-v1` and `bounded-buffer-bios-bg-affine-set-discarded-scratch-v1` (3) | `BgAffineSet requires an actual direct call in its closed owner` |
| `bounded-buffer-bios-mixed-cpuset-fast-fill-source-v1` | `mixed CpuSet/CpuFastSet fill requires actual calls to both wrappers` |
| `bios-word-switch-local-buffers-v1` | `BIOS buffer requires one exact one-object-word switch without local BL` |
| `--addressed-signed-runtime-profile addressed-native-bios-fill-buffer-v1` and `--addressed-signed-runtime-profile addressed-native-bios-fill-buffer-data-v1` (2) | `addressed runtime ELF requires actual addressed calls and no unresolved symbols` |

## Cause

The default buffer walk follows a local address into the BIOS wrapper `func_08141860` (ArcTan2) and refuses its `svc`
(`non-leaf calls and interrupts require linked CFG verification`). At that call the outgoing words `[sp]` and `[sp,
#4]` still hold the addresses of locals passed to `func_0801C918`, so the walk enters the wrapper. In the #192
comment's prototype the scalar summary alone makes it match.

## Source notes

- The local arrays (`s16 out[3]`, `u16 view[2]`) and the pointer locals `out_y`, `view_x`, `view_y` came from a
  mechanical permutation search. The bytes depend on the pointer locals: with `out[1]`, `view[0]` and `view[1]`
  written directly the code differs (measured; the function is 192 bytes instead of 194 when only `view_x` and
  `view_y` are dropped). Locals that only stand for `&out[1]`, `view` and `view + 1` are spare temporaries under the
  source rules, so this text does not ship as written; the #192 comment's match is the verifier's verdict on these
  bytes, not a ship decision.

kit issue: shubshub/fftadecomp-kit#192 (comment)
