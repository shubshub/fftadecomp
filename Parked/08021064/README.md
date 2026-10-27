# 08021064

Target: complete 128-byte Thumb function, 64 reachable instructions,
0x08021064 .. 0x080210E4. Fixed agbcc `-mthumb-interwork -O2`.

The preserved complete byte-stream implementation sums sprite tile counts
from six-byte records following a little-endian count. A zero shape uses
size weights 1, 4, 16 and 64; other shapes use 2, 4, 8 and 32.

The last native invocation exited 1 because the compiled ELF symbol is
114 bytes, shorter than the indexed 128-byte span. The extent gate refused
before CFG verification, source plausibility or byte comparison; none of
those later gates is claimed.

Diagnostic assembly identifies the remaining loop difference. The compiler
loads the two count bytes once, keeps the count in r1 and decrements it at
each iteration, saving only LR. The target saves r4/r5/LR, retains the list
base in r4, increments an independent r5 index, and reloads/reassembles the
two count bytes at the loop tail. The preserved source's shape/size shifts
and switch weights express the target operations, but the emitted control
flow and register lifetimes are not exact.

A packed count/bitfield-record form compiled to 120 bytes and also changed
the shape test to a mask. The byte-stream form compiled to 114 bytes with
either a u16 or signed-integer count helper result. Removing pointee const
qualification retained the same 114-byte result. No flags, volatile reads,
forced inlining or artificial side effects were introduced.

No native report was generated because every run stopped at the extent
gate. The unmatched active source was removed and diagnostic compiler
artifacts were cleaned.
