# 08061E70 — complete recovery, not matching

Full indexed target: `0x08061E70..0x08061F52`, 226 bytes and 92 reachable instructions. The recovered function selects the packed add/remove argument, dispatches its upper-halfword type, updates the 64 four-byte records where required, and invokes the observed item and message helpers.

The fixed native `-mthumb-interwork -O2` command exits 1 with source plausibility `plausible`. The best tested complete candidate occupies 234 bytes, eight bytes longer than the indexed target. Native reports 190/234 matching bytes; its instruction alignment reports 41/86 identical instructions. That alignment denominator is not the target inventory count. No match credit is claimed.

The extra eight bytes occur in the remove-record path: the candidate creates and increments a separate store pointer alongside the read pointer (two additional instructions) and emits all three record-clear stores there instead of branching to the add-path's shared final byte/halfword clear stores (two more instructions). The packed remove word and its low-halfword ID also receive different registers. Loop initialization/increment order and the shifted branch, call and literal displacements consequently differ. The selected helper operations, constants, record offsets, field widths and loop bounds are recovered.

Natural forms tried: explicit advancing record pointers in a for loop; direct array indexing; do/while pointer traversal; pointer initialization before the loop with the increment either in the body or for clause; and an indexed per-entry pointer. Both unsigned 16-bit ID locals and unsigned 32-bit locals holding narrowed IDs were tested. Pointer forms produced 238–254-byte candidates, including peeled first iterations; indexed forms reached 234 bytes. The preserved direct-indexed form gave the best native byte comparison. No flags, shared metadata, assembly, volatile access, or compiler steering were introduced.

Evidence is retained in the batch address directory as `last-native-output.txt` and `native-report.md`. This documents a bounded natural-C attempt under the required fixed flags, not permanent impossibility.
