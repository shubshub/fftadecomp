# 080258C4: bounded natural reconstruction

Target: [0x080258C4, 0x080258F8), 52 bytes / 25 reachable instructions.
Fixed compiler: agbcc -mthumb-interwork -O2.

The function queries the unit category. For category 10, it increments an
odd u16 value with u16 wraparound, then halves it. For category 4, it doubles
the value with u16 truncation. Other categories leave the value unchanged.

The preserved candidate was freshly rerun with the native matcher: exit 1,
NOT MATCHING, source plausible. Complete 52-byte ELF-symbol extent, direct
Thumb call/ordinary ABI validation, and no-relocation checks passed. Byte
comparison reported 50/52 identical bytes and 23/25 identical instructions.

Only the two input-narrowing instructions differ:

ROM 0x080258C6: lsls r4, r1, #16
ROM 0x080258C8: lsrs r4, r4, #16
C   0x080258C6: lsls r1, r1, #16
C   0x080258C8: lsrs r4, r1, #16

Every subsequent instruction is identical, including the linked call,
category checks, odd-value increment and narrowing, shifts, branches and
return sequence. The actual remaining gate is byte equality.

Bounded forms tested: u16 input with direct if/else category dispatch;
a u32 input narrowed into a u16 working local (same two-instruction gap);
and switch dispatch (same input gap plus a different category-check order).
The original direct if/else form is preserved as the best tested candidate.
No compiler flags, helpers, artificial operations or checker changes were used.

The last native report remains in private address scratch. Active unmatched
source and report were removed from this matching root. No match credit.
