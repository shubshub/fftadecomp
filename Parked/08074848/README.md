# 08074848 — bounded natural-C near match

The recovered function clears twelve region pointers, initializes the two VRAM
tile-storage planes, and assigns three halfword-buffer regions. The complete
target is [0x08074848, 0x080748A8): 96 bytes and 35 reachable instructions.

The preserved candidate compiles with the fixed agbcc -mthumb-interwork -O2
flags under immutable kit 5707d46c64da4313a2a6c09784e4cfc564053c82.
The native matcher accepts its source as plausible and its complete 96-byte
ELF symbol as a closed leaf, but exits 1 because the bytes differ. No C match
credit is claimed.

The remaining difference is the order of the context-slot address load and
zero initialization relative to forming the clearing pointer before the loop.
The resulting literal-load displacement also differs. Every byte from offset
0x0C through the end of the complete symbol agrees with the target. The native
aligned diff reports 33/35 identical instructions and 92/96 aligned bytes; this
is distinct from the same-offset byte count recorded in result.json.

Grounded forms tested included indexed clearing, forward pointer clearing,
forward and descending counters, a post-tested loop, and loop-local pointer
initialization. An ordinary memset expression remained an unresolved external
call rather than the target's inline clear. Named VRAM-array addresses caused
address hoisting and extra saved registers; direct pointers to the actual GBA
VRAM regions avoided that difference. A local pointer to the table recovered
the complete size and all subsequent operations. No register annotations,
artificial volatile accesses, inline assembly, padding or flag changes were
used. Further setup permutations solely to order instructions were not pursued.

The unmodified compiler relocatable ELF, final native log and unmatched native
report are retained in the sibling 08074848 artifact directory outside
matching-root. Active unmatched source and report have been removed.
