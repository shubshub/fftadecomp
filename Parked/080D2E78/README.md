# 080D2E78

Complete recovered natural C; not a byte match. Target extent is
0x080D2E78..0x080D2EB2: 58 bytes and 27 reachable instructions.

The function decodes the descriptor's 10-bit ID, selects a 0x46-byte record
from g_table_0855AE4C, reads the little-endian flags at offsets 0x41/0x42,
and returns whether bit 2 is set.

The preserved candidate was tested with the ordinary native matcher and fixed
agbcc -mthumb-interwork -O2. Native exit 1: compiled symbol 50 bytes, shorter
than the indexed 58-byte span. The extent rejection occurs before a byte-diff
report or plausibility verdict; no aligned score or byte-equality count is
claimed. Native output is retained in the address-private scratch directory.

Remaining gap: the target copies the record pointer, loads both flag bytes,
shifts the high byte by 8 and ORs the bytes before masking with 4. The compiler
reduces this to adding 0x41 to the pointer and loading only the low byte. Those
seven target instructions become two candidate instructions. The candidate
has 22 reachable instructions plus its four-byte literal and two alignment
bytes, totaling 50 bytes. Its boolean return order and middle-pool placement
also differ: it branches to the zero result, with the one result before the
pool; the target branches to the one result, with zero before the pool.

Bounded natural forms tried:

- Direct little-endian assembly using OR: 50 bytes.
- Ordinary inline u16 little-endian reader: 50 bytes.
- Signed int promotion of the byte values and combined flags: 50 bytes.
- Packed 0x46-byte record with a u16 field at offset 0x41: 50 bytes.
- Ordinary inline flag-test helpers: 40 bytes, with branchless normalization
  and the same eliminated high-byte read.
- Direct little-endian assembly using addition, preserved here: 50 bytes.

All forms preserve the recovered return value. No volatile, assembly,
compiler flags, forced inlining or inert operations were introduced to retain
the redundant high-byte read. This records the bounded fixed-toolchain gap,
not a permanent impossibility claim. Active unmatched source/report removed.
