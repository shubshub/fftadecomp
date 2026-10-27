# 0804FB38 — Parked

Target: 0x0804FB38..0x0804FB84, 76 bytes / 31 reachable instructions.

The recovered function selects an entry pointer at state +0x424 using its
word-sized index argument. It returns zero for a null entry. Otherwise the
entry's first byte indexes 16-byte definitions at g_table_08521214. The
resource byte at definition +2 becomes zero when absent or 0x18A plus that
byte when present. The result is passed to func_080CB99C, whose byte-valued
return is promoted and increased by 13 for the final word-valued result.

Fresh native matching of the retained candidate with fixed agbcc
-mthumb-interwork -O2 exits 1: complete compiled symbol 72 bytes, indexed
target 76 bytes. The extent gate stops before byte comparison and native
plausibility; neither later gate is claimed to have passed.

The compiler reuses the byte already loaded for the zero test. The target
loads the resource byte again after forming 0x18A, and also copies the
constant into the result register before the addition. These two extra
instructions account for the four-byte extent difference; branch and
literal-pool displacements consequently differ. Null handling, pointer
stride, table stride, lookup call, byte-return narrowing, and final addition
are otherwise recovered.

Bounded natural alternatives used an 8-bit resource bitfield, and a
halfword resource identifier formed by assigning the base then adding the
resource byte. Both still produced 72-byte symbols and stopped at the
extent gate. The simplest byte-field candidate was restored and freshly
native checked before parking. No artificial reload, volatile qualifier,
assembly, forced inlining, compiler flags, or conditions were introduced.

The native extent refusal is retained privately as native-result.txt in
the address scratch. Active unmatched source and report were removed.
