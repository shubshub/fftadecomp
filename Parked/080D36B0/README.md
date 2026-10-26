# 080D36B0

Parked complete natural-C attempt; no match credit.

- Target: `[0x080D36B0, 0x080D376C)`, 188 bytes and 66 reachable instructions.
- Final native matcher: exit 1, `compiled symbol is shorter than the indexed span: 184 < 188`.
- Fixed compiler: agbcc `-mthumb-interwork -O2`.
- Native completeness rejection occurs before byte comparison and plausibility acceptance; neither is claimed.

The remaining discrepancy is in case 0 initialization. The target computes the 0x6000 split offset in r2, computes and stores the workspace pointer in r1, then copies r2 to r1 for func_0800A5F8. The candidate keeps 0x6000 in r1 and computes/stores the workspace pointer in r2, so the final argument copy is absent. This removes one two-byte instruction and two bytes of alignment before the first literal pool. The diagnostic assembly otherwise has the captured switch, update, and cleanup instruction structure; this is not a native equality claim.

Named allocation/workspace slot pointers and a storage-size local retain the allocation-slot load before the allocator call. Integer-address addition still produced 184 bytes; direct RAM lvalues produced 180 bytes. The retained source uses typed external pointer slots and ordinary pointer arithmetic. No assembly, volatile access, altered compiler flags, or forced code generation is present.

The final native log is `../../../080D36B0/match-current.log` relative to this directory. Active unmatched source/report were removed. Root retains integration and reservation ownership.
