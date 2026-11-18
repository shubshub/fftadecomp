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

## Original Thumb frame traces

On toolkit `66dfa4e6`, the native C again matches all 92 bytes. The ordinary verifier still stops inside `0801B7F8 → 0801AF08`. Original control-flow refinement counts 40 instructions, 86 code bytes, one literal word and two alignment bytes.

A second obstacle lies beyond the DMA writes. The caller gives the renderer a 48-byte local view at its SP+8. It initializes view fields +0, +1, +4, +6, +8, +10, +30, +40 and +42. At 0801B5B6 the renderer retrieves that original pointer. Its common tail at 0801B5B8 reads the halfword at +44, clears bit 0, and stores it back at 0801B5BE. The caller never initialized the halfword. The original read value also survives in the caller-saved R1 through the renderer, forwarding wrapper and outer return.

Six runs executed the original Thumb owner and its real callees in Unicorn, with the DMA0 control-read hook performing the selected immediate transfer and clearing the enable bit. Each run used an entry SP of 03006000, a request width of 16, a height of 8, and one of two initial halfwords at 03005FF0 (view+44). The two layer-enable predicates read the original map-state bytes at 02007F40 and 02007F41.

| Layer bytes | Request x | Seed / returned R1 | Final view+44 | DMA0 |
| --- | ---: | --- | --- | --- |
| 80 / 80 | 0 | 1235 / 1235 | 1234 | No transfers |
| 80 / 80 | 0 | A55B / A55B | A55A | No transfers |
| 00 / 00 | −8 | 1235 / 1235 | 1234 | Both fills and the layer copies |
| 00 / 00 | −8 | A55B / A55B | A55A | Both fills and the layer copies |
| 80 / 80 | −32 | 1235 / 00200000 | 1235, never read | Fully clipped, no transfers |
| 80 / 80 | −32 | A55B / 00200000 | A55B, never read | Fully clipped, no transfers |

In the two enabled cases the DMA0 polls at 0801AFDE and 0801B03E observed control 81000004. Each transfer repeated the initialized halfword at 03005F5C four times into a distinct external layer buffer. Later polls at 0801B322, 0801B3B4, 0801B4CC and 0801B55A observed ordinary incrementing-source copies. The disabled, unclipped executions establish the uninitialized read independently of the modeled DMA behavior. The parked callers 0801B630 and 0801D818 also leave +44 unwritten in their local views. Admitting a shared renderer summary would need to preserve both the DMA lifetime requirements and the observed dependence on incoming stack bytes.
