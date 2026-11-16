# 0x08000FC8 - byte-identical only with volatile on a RAM table not on the allow list (148 bytes)

Retry of Parked/08000FC8 on 2026-11-16, kit fcdf2d45, default flags. 68/68 instructions identical (148/148 bytes); match.py: bytes identical /
source IMPLAUSIBLE (not on the allow list) / HAND-ASM REQUIRED BUT NOT ALLOWED; 08000FC8.c:11-14: ERROR: volatile (one per member).

Not shipped: volatile is admitted only on an evidence-backed declaration in include/ that is on the plausible.py allow list, and this table is
not on it. Recorded as unmatchable: the evidence requires maintainer review.

The source here searches the current bank's 32 affine-matrix slots for four equal parameters, else claims the first free slot and copies them in.
Slot type `typedef struct { volatile u16 pa : 16; volatile u16 pb : 16; volatile u16 pc : 16; volatile u16 pd : 16; } AffineSlot;`, table
`extern AffineSlot data_030032B0[][32]`, parameter `const AffineSlot *matrix`, entries read as slots[index].pa. Without volatile agbcc merges the
four halfword compares into two word compares and drops the four dead loads before each strh (124 bytes, the older parked result). volatile u16
x : 16 and plain volatile u16 x give identical bytes. The parameter must have the same volatile type as the table (non-volatile parameter: compare
loads swap, 12 bytes differ). Indexing slots[index] fixes the older parked loop setup (it walked an entry pointer). No non-volatile way to get a
dead load before a store was found.

Evidence for a possible allow-list entry (maintainer decision): every store to 0x030032B0 in this function is preceded by a dead load of the same
halfword; it is the only function writing the table field by field (0800105C and 08001194 clear it with the CpuSet-style callback; 080012BC reads it
with plain loads and its OAM stores at 0x07000006 have no dead loads) - one function in one module, weaker than control_flags.h's evidence.

Kit issue: (to be filed) - the allow list (tools/volatile_allow.json) pins one anonymous extern struct, so it cannot express a fixed-address array
of a named volatile type that a parameter also uses.
