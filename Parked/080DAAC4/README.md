# 0x080DAAC4 - rotated square outline: bytes identical, refused (stack array into a callee; Div remainder wrapper under the stack-index walk) (192 bytes)

Attempt 2026-11-18, kit 750d2fb7, decomp main 52ef3ba2f9.
`func_080DAAC4(task, x, y, radius, angle)` gets a drawing context from `func_0800C614(func_08005BFC(task)->object)`,
builds the four corners of a square of the given radius rotated by `angle` with the sine and cosine tables
(`func_08007A60`, `func_08007A4C`), offsets them by (x, y) in a local `u16[4][2]` array and passes it to
`func_080DA77C(points, 4, context)` (0x080DAB74), which draws the outline. Callers: two sites in 0x0811F28C
(0x0811F598, 0x0811F5AE).

The index row `080DAAC4 080DAB84 192 96 return` has the right extent; 96 is half the byte count, and the reachable
count is 91 (the kit's own CFG refinement). `config/functions.json` has the same extent and count.

## Byte identity

`080DAAC4.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080DAAC4, with every callee and data symbol bound to its
ROM address (5 `R_ARM_THM_CALL`). The 192-byte symbol equals the ROM span `[0x080DAAC4, 0x080DAB84)`: SHA-256
`3ad354e69344c73ef996aa25016cfcf50405cdf786f1c8586d50a80838e99585` for both. `.text` is exactly 192 bytes. `match.py`
refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 750d2fb7, `match.py --root . --no-write` with this source copied to `src/080DAAC4.c` (no data symbol to add): the
default run and all 215 selector values. None matched.

| Selector | Result |
|---|---|
| default, `bounded-buffer-runtime-summaries-v1`, `bounded-buffer-datafree-caller-v1`, `named-data-buffer-rom-table-copy-v1` and 31 other selector values (35) | `unsupported stack-alias use or escape` |
| `named-data-buffer-stack-index-v1` | `buffer callee 0x080DA77C: buffer callee 0x080DA2D4: unsupported buffer pointer use or escape` |
| `named-data-buffer-stack-index-v2` | `buffer callee 0x080DA77C: buffer callee 0x080DA2D4: buffer callee 0x08141874: non-leaf calls and interrupts require linked CFG verification` |
| `bounded-buffer-bios-fill-source-v1` and 2 other selector values (3) | `BIOS fill requires an actual direct call in its closed owner` |

The other 176 selector values give 62 other results, none of them a match; the most frequent are `addressed runtime
ELF requires actual addressed calls and no unresolved symbols` (44), `private float requires unique undefined pinned
helper symbols` (15), `aligned owner requires actual external two-byte Thumb alignment` (12).

## Cause

The default path refuses the local array passed to `func_080DA77C` (`unsupported stack-alias use or escape`). The
stack-index selectors walk it into `func_080DA77C` and its callee `func_080DA2D4`: `named-data-buffer-stack-index-v2`
stops at the BIOS Div-remainder wrapper `func_08141874`, which is the row the #200 comment quotes and the "Div
remainder, under `named-data-buffer-stack-index-v2`" of the #192 comment; `-v1` stops one step earlier in
`func_080DA2D4` (`unsupported buffer pointer use or escape`), which the #200 comment gives beside the `-v2` row.

## Source notes

- The coordinate offset is written through a `static inline offset_coordinate(s16 origin, u16 value)` helper. Without
  it (`points[i].x = (s16)x + points[i].x;` or `x + points[i].x`) the function is 18 bytes shorter, 174 instead of 192
  (measured). No function in the ROM corresponds to the helper, and it is a bare add, so under the inline-helper rule
  this source does not ship until a natural spelling is found.

kit issue: shubshub/fftadecomp-kit#192 (comment), shubshub/fftadecomp-kit#200 (comment)
