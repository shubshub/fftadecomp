# 0x0801D818 - map view refresh: bytes identical, refused (a stack view that reaches a DMA0 fill from a callee local) (104 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `func_0801D818()` builds the same 0x30-byte view on its
stack from the map state at `g_state_02007F40 + 0x228` (`ldr r4, =0x02008168`): +4 = 0, +6 = 0x800, +8 and +0xA =
0x100, +0 = 1, +1 = 0, the map's x and y at +0x28 and +0x2A and its halfword +8 at +0x1E. It calls
`func_0801B7F8(&view, map->first, map->second, map->buffer, map->buffer + 0x2000, 1)` (0x0801D85C) and then clears bit
1 of the halfword at `g_state_02007F40 + 0x2C` (pool words 0xFFFFFDD8 and 0x0000FFFD). The matched `src/0801AC78.c`
calls it.

The index row `0801D818 0801D880 104 45 return` is right (45 reachable instructions).

## Byte identity

`0801D818.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0801D818, with every callee and data symbol bound to its
ROM address (1 `R_ARM_THM_CALL`, 1 `R_ARM_ABS32`). The 104-byte symbol equals the ROM span `[0x0801D818, 0x0801D880)`:
SHA-256 `3232f38173197a0aeecec833c89c7c60085faf82d9aba15bc146c6e400de9418` for both. `.text` is exactly 104 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0801D818.c` (no data symbol to add): the
default run and the selectors the kit issue and the earlier notes discuss.

| Selector | Result |
|---|---|
| default | `buffer callee 0x0801B7F8: buffer callee 0x0801AF08: unsupported stack-alias use or escape` |

## Cause

`func_0801AF08` (1,740 bytes, unmatched) fills from a local of its own through DMA0: `mov r0, sp; strh r1, [r0]; ldr
r1, =0x040000B0; str r0, [r1]` at 0x0801AFC8-0x0801AFCE. The buffer walk follows this function's descriptor into
`func_0801AF08` through `func_0801B7F8` and refuses that store, the callee-side form of the DMA fixed-source fill. The
kit issue's proposed rule covers the owner's own store only; it lists this case under "Not covered".

kit issue: shubshub/fftadecomp-kit#239 (this function is its "Not covered" case, the same store inside a walked callee)
