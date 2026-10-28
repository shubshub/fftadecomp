# 0803CEF8 — parked

Target: [0x0803CEF8, 0x0803D034), 316 bytes / 147 reachable instructions.

The retained natural C compiles with fixed agbcc -mthumb-interwork -O2 to a complete 316-byte ELF function symbol and passes native source plausibility. Native matcher exit 1: aligned diff reports 145/147 instructions and 312/316 bytes identical; same-offset byte equality is 300/316. Its native report is preserved in private address scratch/native-report.md.

Only two instruction-order gaps remain. At target 0x0803CFCE..0x0803CFD0, the group record offset is added before the 0xB1 flag-array header; the candidate adds the header before the record offset. At target 0x0803CFDC, zero is placed in r2 before calculating the special-entry address; the candidate places the same zero in r2 after that address calculation. All packed ID byte reads, output stores, loop increments, optional-entry values, function extent and literal words are otherwise reproduced by the aligned diff.

Tested forms include explicit output-pointer iteration versus direct indexed output fields; corrected packed 70-byte item metadata; byte-addressed versus typed group records; packing the group collection versus its records; unsigned versus signed destination indices; and a postincrement on the final special ID store. The best form retains direct indexed outputs and packed group records. Signedness, packing location and the final postincrement did not change the remaining instruction order. The initial unaligned metadata declaration produced a 72-byte stride and was corrected. No compiler settings, mappings, headers, generated assembly or target boundaries were changed.
