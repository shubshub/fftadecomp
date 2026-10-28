# 080BCA54 — release nested allocation and object

Complete target: `0x080BCA54..0x080BCA74`, 32 bytes / 14 reachable instructions. The complete natural C releases the nested allocation at offset 0x3C when non-null, clears that field, and releases the owning object.

One natural reconstruction was tested with the approved ROM and fixed agbcc `-mthumb-interwork -O2`. Native matcher exit 1 at the complete-extent gate: compiled ELF function is 30 bytes, shorter than the indexed 32-byte target. No plausibility, linked CFG, or byte-comparison verdict was reached, and no native match report was generated.

Compiler assembly inspection identifies the remaining gap precisely. The target starts with `push {r4,r5,lr}; mov r4,r0; mov r5,r4`, keeps the field-access pointer in r4, and uses r5 for the final release. The candidate coalesces its original void pointer and typed state pointer into r4 and uses `push {r4,lr}`, omitting the redundant two-byte pointer copy. Both release calls, null branch, field clear, and final return are present. The candidate already uses a natural void callback parameter and a separate typed local state view; introducing further aliases solely to retain the copy would be compiler steering. No assembly, volatile memory, padding, dead code, or flag changes were tried. The original complete candidate is preserved, with unmatched active source/report absent.
