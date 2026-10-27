# 08003A08: fixed-compiler extent refusal

Target: [0x08003A08, 0x08003A3E), 54 bytes / 25 reachable instructions.
Fixed compiler: agbcc -mthumb-interwork -O2.

Recovered behavior: select a DMA channel register block through the ROM
pointer table at 0x0836D480, then poll bit 31 of its control word at +8 until
clear. A bounded read of the approved ROM table produced these four words:
0x040000B0, 0x040000BC, 0x040000C8, 0x040000D4. These are the genuine DMA0..3
MMIO register blocks. Volatile qualifies only those actual hardware accesses;
ordinary RAM and locals are not volatile.

One complete natural C reconstruction was compiled with the unchanged native
matcher. It exited 1 at the ELF extent gate:

compiled symbol is shorter than the indexed span: 32 < 54

The target uses an r7 frame, eight stack bytes, stack-resident copies of the
input channel and DMA pointer, repeated pointer reloads, and separate shifts
to isolate/test control bit 31. The fixed optimized reconstruction has a
32-byte symbol rather than that complete 54-byte body. No instruction/byte
match count, CFG acceptance or plausibility verdict was issued: extent
validation refused first. No match credit is claimed.

No optimization changes, frame-forcing constructs, assembly, artificial
volatile or inert expressions were attempted. The hardware-correct candidate
is preserved here. Active unmatched source/report are absent from this root.
