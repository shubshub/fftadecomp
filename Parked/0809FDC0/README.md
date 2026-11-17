# 0x0809FDC0 - step towards a projected point (ArcTan2, sine table, division): bytes identical, refused (stack aliases across calls; ArcTan2 under the runtime-summary selector) (302 bytes)

Attempt 2026-11-18, kit 750d2fb7, decomp main 52ef3ba2f9.
`func_0809FDC0(state)` reads the current view position (`func_0801E6F0`), projects the state's point
(`func_0801C918`), adds the offsets, and takes the angle of the difference from ArcTan2 (`func_08141860` at
0x0809FE1E). It scales the larger of |dx| and |dy| by the sine and cosine tables (`func_08007A60`, `func_08007A4C`),
divides each component by `step` (`__divsi3` at 0x0809FE66, 0x0809FE88, 0x0809FE9E and 0x0809FEC0), clamps a zero
quotient to `limit` with the component's sign, moves the view with `func_0801E5E0` and returns 1, or 0 when both
components are zero. Callers: 0x080A1600 (0x080A19AA), the matched `src/080A1A14.c` (0x080A1B40), 0x080A5B98
(0x080A5BC8), and the matched `src/080A83A4.c` (0x080A83CE) and `src/080A83DC.c` (0x080A83E0).

The index row `0809FDC0 0809FEEE 302 151 return` has the right extent; 151 is half the byte count, and the reachable
count is 141 (the kit's own CFG refinement). `config/functions.json` has the same extent and count.

## Byte identity

`0809FDC0.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0809FDC0, with every callee and data symbol bound to its
ROM address (10 `R_ARM_THM_CALL`). The 302-byte symbol equals the ROM span `[0x0809FDC0, 0x0809FEEE)`: SHA-256
`aeaa03e1d80a211fb25b68223ad1fa59e85457c135b50fa74eeae0cc6fce6a87` for both. `.text` is 304 bytes: the symbol and the
`c0 46` alignment halfword after it. `match.py` refuses before its own byte comparison (below). `plausible.py
--strict` exits 0.

## Refusals

Kit 750d2fb7, `match.py --root . --no-write` with this source copied to `src/0809FDC0.c` (no data symbol to add): the
default run and all 215 selector values. None matched.

| Selector | Result |
|---|---|
| default and 4 other selector values (5) | `stack aliases cannot cross calls in caller-clobbered registers` |
| `--addressed-signed-runtime-profile addressed-signed-runtime-v1`, `named-data-buffer-stack-index-v1`, `named-data-buffer-stack-index-v2`, `bounded-buffer-bios-fill-source-v1` and 128 other selector values (132) | `function address requires a canonical addressed function` |
| `canonical-integer-scalar-source-v1` and 2 other selector values (3) | `canonical integer caller dual-index count differs from complete CFG` |
| `bounded-buffer-runtime-summaries-v1` | `buffer callee 0x08141860: non-leaf calls and interrupts require linked CFG verification` |

The other 75 selector values give 15 other results, none of them a match; the most frequent are `owner requires sole
complete Thumb ELF function` (32), `private float requires unique undefined pinned helper symbols` (15), `u16
switch-data requires a mapped local switch without other runtimes; function literals require and are required by a
function-literal selector` (8).

## Cause

The default path refuses the local addresses held across calls (`stack aliases cannot cross calls in caller-clobbered
registers`); the function has no buffer proof on that path. Of the 215 selector values, the one that walks it as a
buffer owner with the division runtime, `bounded-buffer-runtime-summaries-v1`, stops at the ArcTan2 wrapper (`buffer
callee 0x08141860: ...`), which is how the #192 comment lists it among the scalar wrappers met in walked callees. 132
of the 215 give `function address requires a canonical addressed function`.

## Source notes

- `u32 angle` and the declaration order came from a mechanical permutation search; they are a steering doubt for
  review. The type is not what steers: `s32` and `u16` give the same bytes, and only `u8` changes them (measured).

kit issue: shubshub/fftadecomp-kit#192 (comment)
