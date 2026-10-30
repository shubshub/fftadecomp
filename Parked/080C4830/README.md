# 080C4830 — bounded nonmatch

The complete target occupies 60 bytes and has 26 reachable instructions. The
preserved C copies the first word of each 0x328-byte record at object offset
0x2968 into consecutive output words. The halfword at object offset 0x5270
controls the copy count and is read again as signed for the return value.

The final native check exited 1 with `NOT MATCHING - bytes differ`. Both complete
symbols occupy 60 bytes, and the candidate passed plausibility. The comparison
reported 46/60 bytes and 14/26 instructions identical. The literal values, access
widths, countdown loop and signed return access agree. The target preserves the
object base in r1, the record stride in r4 and the output cursor in r5. This
candidate preserves the object base in r4, keeps the stride in r1 and uses r5
for the output cursor. These choices change the initial object/offset setup,
record-address calculation, loop pointer update and final count reload.

Examined natural forms included indexed copying with a cached count, direct
field count bounds, a record pointer walk with a countdown, an explicitly
guarded countdown, signed/unsigned promoted counts, signed and unsigned field
views, a precomputed record-array pointer, and indexed output instead of a
postincremented output pointer. None produced complete byte equality. The
unsigned-index form grew to 64 bytes; the retained form has the target extent
and the clearest direct recovered behavior. No compiler flags, assembly,
qualifiers, artificial control flow or register declarations were introduced.

The original unmodified ET_REL compiler object is retained in the address
delivery directory as `original.o`, with its raw hash in `result.json`. This is
a byte-mismatch result, not an extent or ownership refusal. Fresh successful
report replay is not claimed. Active unmatched source and report were removed;
this function receives zero match credit.
