# 0804A4CC

Recovered complete rendering-object initialization and label drawing function.
Target: `[0x0804A4CC, 0x0804A6B0)`, 484 bytes and 199 reachable instructions,
including literal pools.

The retained complete candidate was checked by the default native matcher with
fixed agbcc `-mthumb-interwork -O2`. Native exit status was 1: source plausible,
complete symbol 484 bytes, 168/199 instructions and 441/484 bytes identical.
It is not an exact match and earns no match credit.

The remaining differences are the register used for the mode-2 comparison near
`0x0804A5A4`, followed by address formation, register allocation and constant
materialization in the final object-field initialization and source lookup at
`0x0804A5FE..0x0804A66C`. In particular, the target materializes the halfword
value 0x1AD and its destination before the coordinate stores; the candidate
computes the equivalent offset as x + (y + 1) * 32 after setting x=13 and y=12.
The target and candidate retain different registers for the object base,
coordinate constants, state zero and indexed-record offset. Rendering calls,
all three label call sequences, the fixed 56-byte frame, full symbol extent,
final call arguments and field values are recovered.

Natural forms tested included separate and nested map/text calls, direct
halfword initialization, coordinate-derived offset calculation, separate and
combined coordinate assignment, typed access to byte storage, an explicit
halfword destination pointer, an object-array pointer, and signed/unsigned
coordinate fields. A graphics attribute bitfield interpretation introduced
extra read/modify/write operations and was discarded. The closest retained
form uses separate coordinate stores and computes their corresponding offset.
No custom flags, assembly, volatile RAM accesses or compiler directives were used.
This records a bounded unresolved source-form gap under the fixed flags, not
an impossibility claim.

Source-bound native evidence remains in the private address scratch directory:
`last-native-output.txt` and `last-native-report.md`.
