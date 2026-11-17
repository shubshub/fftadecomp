# 0x0801B5D4 - map layer view request: bytes identical, refused (a stack state that reaches a DMA0 fill from a callee local) (92 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `func_0801B5D4(request)` copies the request's fields into a
0x30-byte state on its stack at sp+8 (in the ROM's store order: bytes +4, halfwords +6, +8 and +0xA, bytes +0 and +1,
halfwords +0x28 and +0x2A, and the halfword at `g_state_02007F40 + 0x1E` to +0x1E; 0x0801B5DA-0x0801B600), gets the
two layer buffers from `func_0801AD1C(0)` and `func_0801AD1C(1)`, and calls `func_0801B7F8(&state, request->first,
request->second, buffer0, buffer1, 1)` (0x0801B61E). `func_0801B7F8` (28 bytes, matched `src/0801B7F8.c`) passes
everything on to `func_0801AF08`. No `bl` or function word in the ROM refers to 0x0801B5D4.

The index row `0801B5D4 0801B630 92 46 return` has the right extent; 46 is half the byte count, and the reachable
count is 40 (the kit's own refinement and an independent CFG walk agree). No refusal below depends on it.

## Byte identity

`0801B5D4.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0801B5D4, with every callee and data symbol bound to its
ROM address (3 `R_ARM_THM_CALL`, 1 `R_ARM_ABS32`). The 92-byte symbol equals the ROM span `[0x0801B5D4, 0x0801B630)`:
SHA-256 `2ca6ebca1fa18f4efe56bce28935959afcd1f06a96aaf547a3841f7f6649aee2` for both. `.text` is exactly 92 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0801B5D4.c` (no data symbol to add): the
default run and the selectors the kit issue and the earlier notes discuss.

| Selector | Result |
|---|---|
| default, `named-data-buffer-v1`, `protected-descriptor-word-v1` | `buffer callee 0x0801B7F8: buffer callee 0x0801AF08: unsupported stack-alias use or escape` |
| `descriptor-output-alias-v1`, `descriptor-single-store-v1` | `buffer callee 0x0801B7F8: buffer callee 0x0801AF08: unknown store can invalidate a live pointer word` |

## Cause

`func_0801AF08` (1,740 bytes, unmatched) fills from a local of its own through DMA0: `mov r0, sp; strh r1, [r0]; ldr
r1, =0x040000B0; str r0, [r1]` at 0x0801AFC8-0x0801AFCE. The buffer walk follows this function's descriptor into
`func_0801AF08` through `func_0801B7F8` and refuses that store, the callee-side form of the DMA fixed-source fill. The
kit issue's proposed rule covers the owner's own store only; it lists this case under "Not covered".

kit issue: shubshub/fftadecomp-kit#239 (this function is its "Not covered" case, the same store inside a walked callee)
