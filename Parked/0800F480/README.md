# 0x0800F480 - polygon edge scan conversion: bytes identical, refused (a local passed to a callee that keeps it in its frame) (550 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `func_0800F480(vertices, count, x_offset, y_offset, ranges,
mode, scale)` walks a polygon's edges from the vertex `func_0800DECC(vertices, count, &first)` picks (0x0800F4B2;
`first` is a stack halfword, the result is the winding direction). Each vertex is offset and scaled about a centre (a
`static inline` helper on stack locals), and each edge is rasterised into `ranges` with `func_0800DFB0` or
`func_0800E05C` by direction and slope; the next index is `func_08141874(first + i, count)`, the BIOS remainder
wrapper. Callers: the matched `src/0800E1A0.c` and 0x0800E110. The matched `src/0800F308.c` is a smaller sibling
without the scaling.

The index row `0800F480 0800F6A6 550 275 return` has the right extent; 275 is half the byte count, and the reachable
count is 266 (the kit's own refinement and an independent CFG walk agree). No refusal below depends on it.

## Byte identity

`0800F480.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0800F480, with every callee and data symbol bound to its
ROM address (9 `R_ARM_THM_CALL`, no data relocations). The 550-byte symbol equals the ROM span `[0x0800F480,
0x0800F6A6)`: SHA-256 `a9941c6349ed69f42117d50ab1bde133ee2894a65198a01956dd84e0224417fd` for both. `.text` is 552
bytes: the symbol and the assembler's `c0 46` alignment halfword. `match.py` refuses before its own byte comparison
(below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0800F480.c` (no data symbol to add): the
default run and the selectors the kit issue and the earlier notes discuss.

| Selector | Result |
|---|---|
| default, `named-data-buffer-stack-index-v1` | `buffer callee 0x0800DECC: unsupported buffer pointer use or escape` |
| `named-data-buffer-stack-index-v2` | `buffer callee 0x0800DECC: buffer callee 0x08141874: non-leaf calls and interrupts require linked CFG verification` |
| `ordinary-formal-output-spill-v1`, `ordinary-formal-output-spill-bios-remainder-v1` | `owner requires sole complete Thumb ELF function` |

## Cause

The walk follows `&first` into `func_0800DECC` (matched `src/0800DECC.c`), which keeps the pointer in its own frame
(`str r2, [sp]` at 0x0800DEDA, reloaded at 0x0800DF28); the default walk refuses that (`unsupported buffer pointer use
or escape`). `named-data-buffer-stack-index-v2`, which admits a forwarded pointer slot, gets past it and stops at the
BIOS remainder wrapper `func_08141874` that `func_0800DECC` calls. The two formal-output selectors refuse with `owner
requires sole complete Thumb ELF function`, which the earlier notes trace to the 2-byte alignment halfword after the
symbol.

## Source notes

- `scale_point` is a `static inline` helper used twice (the first vertex and the loop); it scales a point about the
  centre, a real operation. Its two-step `delta` (assign, then multiply) was flagged as a question in the attempt.

kit issue: shubshub/fftadecomp-kit#238; related: shubshub/fftadecomp-kit#192 (the BIOS remainder wrapper behind the forwarder)
