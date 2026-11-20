# 0x0800DE70 | Interleave two background-scroll scanline planes

The callback copies 160 rows from two 160-halfword input planes into alternating halfwords in a four-byte output row. The ROM stores each halfword as two little-endian bytes. Each of the four stores is immediately preceded by a read of that same destination byte whose value is discarded.

## Call path

The callback table at 0x0814980C contains 0x0800DE65, 0x0800DE71 and 0x0800D325. The constructor at 0x0800CE08 copies the table, selects by mode at 0x0800CE48 and calls 0x0800C3CC at 0x0800CE5A. Mode 1 selects 640 payload bytes and four bytes per row from the tables at 0x08149818 and 0x08149806. The allocator at 0x0800C3CC reserves the payload plus two scanline buffers. The dispatcher at 0x0800C4B4 invokes the callback with the payload and the back buffer, swaps buffers and schedules DMA to the separately supplied register destination. The matched scroll-wave caller at 0x080D8E00 selects that register from 0x08149AD4, which contains 0x04000010, 12, 14, 16, 18, 1A, 1C and 1E (the eight background scroll registers). The register address and the allocated back buffer are distinct arguments.

## Native results

The retained ordinary packed pair passes strict plausibility. The default native compiler emits a 64-byte symbol for the 78-byte target. For the diagnostic, adding volatile to the two packed halfword members reproduces the complete 78-byte ELF symbol and all 39 instructions. Its SHA-256 is e2580e0e4d24fcb32d30b456b80cb14d9bdbee3df19d3dfca9242dbe53b2897e. The official checker rejected both qualifiers. Its volatile allow list covers the separately named LCD shadow object at 0x03000940. The destination here is the allocated back buffer, for which the gate has no entry. The exact original C declaration remains unknown.

The remaining source-type question is tracked in [toolkit issue #168](https://github.com/shubshub/fftadecomp-kit/issues/168).
