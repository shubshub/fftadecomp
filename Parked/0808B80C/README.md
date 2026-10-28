# 0808B80C — Parked

Target: 0x0808B80C..0x0808B858, full 76 bytes / 36 reachable Thumb instructions, including a four-byte mapped data literal. Candidate has the same complete extent and instruction count.

The candidate fills two horizontal tile rows. The first receives successive u16 tile IDs ORed with the incoming flags; the second is one surface stride below and receives tile IDs offset by the original width. The tile ID wraps as u16 after every column. Surface records have stride 0x4C and a byte row-stride member at offset 0x28 in mapped data_030009E0. Width and flags are u16; flags arrive as the fifth argument.

Fresh default native match with fixed agbcc `-mthumb-interwork -O2` exits 1: source plausible, complete symbol 76 bytes, bytes differ. The sole instruction-order difference is at 0x0808B82E..0x0808B832: target emits `lsl r7,r1,1` followed by `mov r2,r6`; candidate emits those two independent setup operations in reverse order. Every other instruction, register, literal and byte offset agrees. The native alignment score is 35/36 instructions and 74/76 bytes, not same-offset byte equality; the four swapped instruction bytes differ at the same offsets (72/76 bytes equal).

Tested natural forms included a plain countdown while loop (counter copied before the width guard), an ascending counted for loop (ascending induction retained), an explicitly guarded countdown do loop (preserved best), and a guarded countdown for loop (decrement scheduled later). Using a byte or word stride local gave the same best ordering. An explicit byte-distance representation placed the two setup operations in the target order but changed the stride-load register and pointer-add operand order. No assembly, artificial operations, volatile access, altered flags or shared edits were introduced.

The complete tested source is preserved here. Unmatched active source and generated report were removed. Final native output remains in the address scratch directory. No match credit is claimed.
