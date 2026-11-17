# 0x0800D3BC - affine wave line generator (BgAffineSet per scanline): bytes identical, refused (BgAffineSet in the buffer walk; volatile output record) (606 bytes)

Attempt 2026-11-18, kit 750d2fb7, decomp main 52ef3ba2f9.
`func_0800D3BC(wave, out)` fills 160 eight-halfword affine line records at `out` (pa, pb, pc, pd and the x and y
offsets as halves). It computes the base transform once with BgAffineSet (`func_08141864(&wave->src, &base, 1)` at
0x0800D42A); for each line inside the wave's band (modes 1 to 3, `unknown_34` or `unknown_36` lines around
`unknown_04`) it recomputes the transform from a local source with that line's `sx` from `unknown_178[i]`
(`func_08141864(&src, &row, 1)` at 0x0800D54C) and adds the line offset from `unknown_38[i]`; lines outside the band
get the base transform. No `bl` reaches it: it is the task callback that 0x0800CF08, 0x0800CFC8, 0x0800D090 and
0x0800D168 pass to `func_0800C3CC` (literal words at 0x0800CFC0, 0x0800D08C, 0x0800D164, 0x0800D238).

The index row `0800D3BC 0800D61A 606 303 return` has the right extent; 303 is half the byte count, and the reachable
count is 301 (the kit's own CFG refinement). `config/functions.json` has the same extent and count.

## Byte identity

`0800D3BC.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0800D3BC, with every callee and data symbol bound to its
ROM address (2 `R_ARM_THM_CALL`). The 606-byte symbol equals the ROM span `[0x0800D3BC, 0x0800D61A)`: SHA-256
`d86e7f5b4e4f12dbbb07249dd0658ba2911afb6ecdd7181c4260ee6de848e679` for both. `.text` is 608 bytes: the symbol and the
`c0 46` alignment halfword after it. `match.py` refuses before its own byte comparison (below). `plausible.py
--strict` exits 1 (see Source notes).

## Refusals

Kit 750d2fb7, `match.py --root . --no-write` with this source copied to `src/0800D3BC.c` (no data symbol to add): the
default run, the BIOS buffer selectors, the two addressed BIOS-fill-buffer selectors, `named-data-buffer-v1`, and the
selectors the #192 comment and earlier notes name. None matched.

| Selector | Result |
|---|---|
| default, `bounded-buffer-guarded-bios-division-v1` and `named-data-buffer-v1` (3) | `buffer callee 0x08141864: non-leaf calls and interrupts require linked CFG verification` |
| `bounded-buffer-bios-sqrt-scratch-v1` | `BIOS Sqrt requires exact complete svc #8; bx lr wrapper` |
| `bounded-buffer-bios-fill-source-v1`, `bounded-buffer-bios-fill-local-source-semantics-v1` and `bounded-buffer-bios-fill-overwritten-control-stores-v1` (3) | `BIOS fill requires an actual direct call in its closed owner` |
| `bounded-buffer-bios-fast-fill-source-v1`, `bounded-buffer-bios-mixed-fast-fill-source-v1` and `bounded-buffer-bios-mixed-fast-fill-runtime-summaries-v1` (3) | `CpuFastSet fill requires only its actual direct wrapper calls` |
| `bounded-buffer-bios-bg-affine-set-v1`, `bounded-buffer-bios-bg-affine-set-transparent-leaf-scratch-v1` and `bounded-buffer-bios-bg-affine-set-discarded-scratch-v1` (3) | `BgAffineSet requires exactly a local source and a local destination` |
| `bounded-buffer-bios-mixed-cpuset-fast-fill-source-v1` | `mixed CpuSet/CpuFastSet fill requires actual calls to both wrappers` |
| `bios-word-switch-local-buffers-v1` | `BIOS buffer requires one exact one-object-word switch without local BL` |
| `--addressed-signed-runtime-profile addressed-native-bios-fill-buffer-v1` and `--addressed-signed-runtime-profile addressed-native-bios-fill-buffer-data-v1` (2) | `addressed runtime ELF requires actual addressed calls and no unresolved symbols` |

## Cause

The default buffer walk follows a local address into the BIOS wrapper `func_08141864` (BgAffineSet) and refuses its
`svc` (`non-leaf calls and interrupts require linked CFG verification`). The BgAffineSet selectors need a local source
and a local destination at every call, and the first call's source is `&wave->src`, a field of the caller's object
(`BgAffineSet requires exactly a local source and a local destination`). The #192 comment lists this function among
those that get past the wrapper with a BIOS summary and are then refused by plausibility for `volatile` in the source
(below).

## Source notes

- The output record is declared with `volatile u16 : 16` bit-fields, and `plausible.py --strict` exits 1 with 8
  `volatile` errors (lines 24-31). The ROM reads each byte of the record before it stores it (for example `ldrb r0,
  [r7, #1]; strb r2, [r7, #1]` at 0x0800D4A0-0x0800D4A2), and the qualifier is what reproduces those dead loads. The
  record is a line buffer in RAM, not a hardware register, so under the volatile rule this source does not ship; it is
  published as the measured byte-identical text.

kit issue: shubshub/fftadecomp-kit#192 (comment)
