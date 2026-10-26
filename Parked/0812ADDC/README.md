# 0812ADDC — bounded natural C attempt

Target: complete indexed [0x0812ADDC, 0x0812AE8C), 176 bytes and 75 reachable instructions. Compiler: agbcc -mthumb-interwork -O2, unchanged native matcher and approved ROM.

The complete C draws nine name positions using data_083A8306, signed 16-bit coordinates and an unsigned 16-bit cumulative advance. Encoded byte pairs occupy state offsets 0x312 through 0x323. Pair 0x40/0x73 advances by six; other pairs form a big-endian glyph identifier masked by 0x7FFF and advance by the return from 08013A5C. Each draw uses a tile offset of four times the position.

The final fresh native invocation exits 1: complete compiled extent 176 bytes, source plausible, bytes DIFFER, verdict NOT MATCHING. The comparison reports 57/74 instructions identical and 147/176 bytes identical. No exact-match claim is made.

The target retains the state in r8, the precomputed name pointer in r7 and shifted y in r9. The candidate retains the state in r7, name pointer in r9 and shifted y in r8, adding a pointer-copy instruction near entry. In the two-byte special-case test, the target recalculates name + 2*i + 1, while the candidate reuses the first byte address and loads its second byte at offset one. The target preserves 2*i in r1 through the tests and then adds the state; the candidate copies the index to r3 and later adds the state into r1. These allocation and common-address differences also shift some call, branch and literal-load offsets. Glyph decoding after that state addition, advance update, loop narrowing and epilogue otherwise align.

Bounded attempts tested a named byte-array record, a precomputed name pointer, direct state-byte decoding, direct name-subrange expressions, ordinary local-initialization ordering, and a packed two-byte glyph record with high/low fields. The simple byte-array form compiled to 160 bytes; named-pointer and direct-subrange forms also produced 172-byte short symbols. The best complete 176-byte version is preserved here. The packed-record form passed plausibility at full extent but compared worse. No flag changes, asm, pragmas, volatile, dead operations or steering were used.

The full native output and generated report remain in the private address scratch directory. Unmatched source and report were removed from the private root's src and docs/match directories.
