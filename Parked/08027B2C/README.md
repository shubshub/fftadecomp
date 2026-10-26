# 08027B2C — parked

Target: [0x08027B2C, 0x08027D10), 484 bytes / 209 reachable instructions.

The retained natural C candidate compiles to the complete 484-byte ELF function symbol with fixed agbcc -mthumb-interwork -O2. Native matcher exit 1: source plausible, 432/484 bytes identical (161/201 decoded candidate instructions identical). Its saved native report is in the private address scratch directory.

Remaining differences are register allocation and value lifetime: target changes the entries-field address from r6 to r8 at the second availability branch, freeing r6 for the selection-record pointer and final availability result. The candidate retains the entries-field address in r6 and uses r8 for those values. The target also retains the final count in r1 for positioning; the candidate reloads it after storing visible_count. These differences affect literal-pool placement and branch offsets.

Tested forms: direct structure-field accesses (retained, 484 bytes); a local u16 final-count snapshot (480 bytes); an explicit entries-field address plus signed count snapshot (476 bytes); and an inline u16 visible-count helper (480 bytes). The three shorter forms were rejected by the native complete-span check. No compiler settings, mappings, headers, or target boundaries were changed.
