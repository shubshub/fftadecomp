# 0804BB5C map path reconstruction

Canonical Thumb agbcc -O2 produces the complete 100-byte symbol at
[0804BB5C, 0804BBC0). All 49 native instructions match after the original
R_ARM_THM_CALL at +0x14 binds func_0804BBC0. The linked SHA-256 is
`e66b5056cef906b28342f3ff199298b1a320af55ca52d25faa19b630e0b1ef24`.
The source uses a single index for predecessor traversal and then output
copying. The 32-byte local array first holds distances and then the path
in reverse. Both inputs are compared at register width. The wrapper
narrows only the start node at the call to 0804BBC0. Existing caller
080445DC uses an octet prototype; its actual arguments are both LDRB.

The only raw original Thumb BL to the 396-byte worker is 0804BB70. The
five original direct calls to this wrapper are 08039674, 0804471A,
08044800, 08044864 and 08044EFE. The full ROM has no literal Thumb
pointer to either function. The ordinary and named-data-buffer-v1
verifiers reject a worker stack alias on toolkit f1b81350.

The valid 30-node map and its predecessor relation establish bounds for
the algorithm when both nodes lie in 0..29, the two arrays are writable
for 32 bytes and do not overlap. Entry to this wrapper needs independent
evidence for that domain. 08044800 reads start and destination directly
from mutable menu offsets 0x7BB and 0x7BD and passes 0x7C1 as path storage.
08039674 tests that its destination byte is nonzero and that the decremented
value differs from its source; these tests do not establish the range.
08043F90 writes the saved five-bit selection minus one to 0x7BB.
080445DC can populate an entry's resource byte using 08045424. Across
the 256 resource inputs in the original ROM, 252 table cases select the
explicit 0xFF return, three require RAM selectors 3, 5 or 6, and one
returns zero. Which of those entries can reach the route query depends on
game state. A proof needs the active-entry and save-state invariants
across all five call sites. No saved MATCH report is claimed.
