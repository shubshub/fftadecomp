# 08013A5C: bounded natural reconstruction

Target: [0x08013A5C, 0x08013A86), 42 bytes / 16 reachable instructions.
Fixed compiler: agbcc -mthumb-interwork -O2.

The function returns 0x10 when the byte at g_state_020020D0 + 0x13
is nonzero. Otherwise it returns the byte at data_084966B0 plus the input
converted from u16 to s16.

Fresh native match of the preserved candidate exited 1: NOT MATCHING.
The complete 42-byte ELF-symbol extent, closed leaf CFG, typed data linking,
no-relocation check and source plausibility all passed. The byte comparison
reported 38/42 identical bytes and 13/16 identical instructions. No match
credit is claimed.

Remaining difference:
- ROM keeps the narrowed input in r2; candidate keeps it in r1.
- ROM loads the table base into r1 before sign-extending the input into r0.
  Candidate sign-extends its r1 input into r0 first, then loads the table
  base into r1. This changes the literal-load displacement as well.
- The signed address addition, byte load, branches, middle literal pool,
  alignment, constants, return value and return sequence otherwise agree.

Bounded forms tested: opposite early-return conditions; direct array indexing;
a named table pointer initialized before the condition and in the lookup
scope; equivalent offset-plus-pointer dereference. The reversed condition
restored the correct extent and branch/literal layout. A pointer initialized
before the condition hoisted the table load and reversed pool order. Array
indexing and lookup-local pointers retained a different register allocation.
The preserved offset-plus-pointer form was the closest complete candidate
and was rerun with the unchanged native matcher immediately before parking.

The last native report is retained in the private address scratch directory.
No active unmatched source or report remains in this matching root.
