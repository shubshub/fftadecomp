# 080BCC70 bounded matching attempt

Target: 080BCC70..080BCDF8, 392 bytes including the internal scalar pools,
182 reachable instructions. Fixed compiler: agbcc -mthumb-interwork -O2.
The preserved complete candidate emits one 390-byte ELF function containing
181 instruction mnemonics; the semantic helpers are fully inlined.

The fresh default native matcher exits 1 with:
`signed remainder caller requires exact complete mapped ROM bytes`.
This is the caller-byte prerequisite for the signed runtime proof. The
plausibility gate was not reached; no match or plausibility credit is claimed.
The C uses genuine signed remainder expressions with signed 16-bit random
operands and nonzero constant divisors 241 and 129.

The remaining generated-assembly difference is in retaining the list-head
field address during insertion. At target 080BCD54..080BCD5C, the code forms
system+0x1C0 in r0, loads the head into r2, then copies that address into r5.
The candidate forms system+0x1C0 directly in r5 and loads the head from r5,
omitting the final copy. This removes two bytes and shifts the subsequent
branches and calls. The preserved source keeps the target's movement, field
widths, signed narrowing, inactive-node search and observed insertion stores.

Natural forms tried: a returned-head insertion helper assigned directly to
the system member (396-byte initial candidate, with repeated member-address
calculation); a named list-head pointer plus the returned-head helper
(preserved 390-byte candidate); and a void pointer-to-pointer insertion
helper, which distributed the head stores across the insertion branches
instead of producing the target's shared store. Separate traversal and spawn
variables recovered the target's r3/r4 roles in the update loop. None of these
bounded forms produced complete byte equality at the fixed flags. This is a
bounded unresolved source-form gap, not a claim of permanent impossibility.

The captured target, final compiler assembly and fresh native output remain
in the address-specific private scratch directory. Unmatched active source
and report have been removed.
