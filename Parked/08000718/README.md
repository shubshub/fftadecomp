# 0x08000718 - DmaSet + DmaWait at -O0: bytes identical, refused by plausible.py and the O0 profile (112 bytes)

Retry 2026-11-16, kit fcdf2d45. The function is the AGB-SDK / pret `DmaSet` + `DmaWait` pair built at -O0: a `volatile u32 *`
pointer to 0x040000B0, `dmaRegs[0..2]` = source, 0x04000008, 0x80000027, a bare `dmaRegs[2];` read-back, a second
block that reloads the pointer and waits `while (dmaRegs[2] & 0x80000000);`, then `*(u16 *)0x03002BBC =
*(u16 *)0x03000940;`. With `--flags "-mthumb-interwork -O0"` the bytes are identical (112/112) but plausible.py
reports 4x `volatile` on the two `volatile u32 *dmaRegs = (volatile u32 *)0x040000B0;` lines (verdict HAND-ASM
REQUIRED BUT NOT ALLOWED). plausible.py accepts volatile only as `*(volatile T *)0x04...` or `volatile T *p = &sym;`
used as `p->`/`*p`; it refuses `p[` - the pret DmaSet idiom.
Why these forms: the read-back at 0x08000744 (`ldr r0, [r1]`, discarded) needs a volatile read of DMA0CNT; the ROM
indexes from the [r7, #4] slot (`adds r0, r1, #4` at 0x0800072E; `adds r0, r1, #0; adds r0, #8` at 0x08000736), so
member access (folds to `str r1, [r0, #4]`) is wrong; the second block re-stores 0x040000B0 to [r7, #4]
(0x08000746-0x08000748). `src` is a variable in the ROM ([r7] at 0x08000720, reloaded at 0x08000728) and must be
declared before the blocks.
With `--owner-runtime-profile compiler-orphan-address-constants-O0-v1`: `acyclic path states reject reachable CFG
cycles` (the wait loop) with named data, `orphan prerequisite excludes foreign sections` all-numeric. Via
include/control_flags.h: `path exceeds 20000 instructions`.
Needs: plausible.py to recognise an indexed volatile MMIO pointer local (pret DmaSet), and an O0 replay that admits a
bounded wait loop (same as 0x08003A08). No index or data-symbol change needed.
