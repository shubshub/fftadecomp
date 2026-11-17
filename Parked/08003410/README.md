# 0x08003410 - VRAM and palette clear: bytes identical, refused (a DMA3 fill whose fixed source is a stack halfword) (68 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `func_08003410()` clears BG VRAM and palette RAM with two
immediate DMA3 fills from a zero halfword on its stack, and resets the OAM affine parameters in between
(`func_08003454`, matched `src/08003454.c`). The first fill stores the halfword's address to DMA3SAD (`mov r0, sp;
movs r5, #0; strh r5, [r0]; ldr r4, =0x040000D4; str r0, [r4]`, 0x08003414-0x0800341C), 0x06000000 to DAD and
0x8100C000 to the control word (enable, immediate, fixed source, 16-bit, 0xC000 units), and reads the control word
back (0x08003428). The second fill (0x0800342E-0x0800343E) targets 0x05000000 with 0x81000200. The matched
`src/08002710.c` calls it.

The index row `08003410 08003454 68 27 return` is right (27 reachable instructions). `data_040000D4` is already in
`config/data_symbols.json`.

## Byte identity

`08003410.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08003410, with every callee and data symbol bound to its
ROM address (1 `R_ARM_THM_CALL`, 1 `R_ARM_ABS32`). The 68-byte symbol equals the ROM span `[0x08003410, 0x08003454)`:
SHA-256 `5096078770373f44c3578272f48dc089139544b4458ab03aace3c0b30362418b` for both. `.text` is exactly 68 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08003410.c` (no data symbol to add): the
default run and the selectors the kit issue and the earlier notes discuss.

| Selector | Result |
|---|---|
| default, `named-data-buffer-v1` | `unsupported stack-alias use or escape` |

## Cause

The default walk refuses the store of the stack address into DMA3SAD (0x0800341C) as an escape. The address goes to a
write-only DMA register; with immediate timing and a fixed source the transfer reads that one halfword and finishes
before the next instruction. No selector models a DMA source register, so `named-data-buffer-v1` refuses at the same
store.

## Source notes

- The register block is the volatile `data_040000D4` view with the same `plausible:` comment as the matched
  `src/08002480.c` and `src/080023EC.c`; the control read-backs at 0x08003428 and 0x0800343E are in the ROM.
- The fill source is written `u16 *source = &zero; *source = 0;`, the fill-source idiom of the matched
  `src/08137B20.c` and `src/0805868C.c`. The plain `zero = 0; dma->source = &zero;` gives 68 bytes with 2 halfwords
  different (0x08003414 and 0x08003416: the order of `mov r0, sp` and `movs r5, #0`), so the pointer local is
  load-bearing; it rests on that precedent.

kit issue: shubshub/fftadecomp-kit#239
