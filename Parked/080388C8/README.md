# 080388C8: bounded natural reconstruction

Target: complete [0x080388C8, 0x0803890A), 66 bytes / 28 reachable instructions.
The function scans 361 four-byte records at state offset 0x1940. It compares
an unsigned halfword key at record offset 0 and returns the byte at offset 2
for the first match, or zero after exhausting the table.

Fixed native command used the approved ROM with agbcc -mthumb-interwork -O2.
The preserved candidate reaches complete ELF-symbol ownership and closed leaf
CFG verification and is plausible. Native exit 1 is the byte-equality gate:
60/66 same-offset bytes and 23/28 instructions are identical. The candidate
has exactly the target's 66-byte extent, literal values/positions, alignment,
loop, loads, comparisons, branches, index narrowing and epilogue.

Remaining difference: target loads key offset 0x1940 into r6, initializes the
360 bound in r4, then loads value offset 0x1942 into r5. The candidate uses
r5 for the key offset and loads the value offset into r6 before initializing
the bound. The key/value address additions consequently use the opposite
r5/r6 operands. These are the five differing instructions (six bytes).

Tried a typed state containing a 361-element record array, initializing the
index before the state pointer, and byte-addressed accesses with the recovered
record stride. The latter fixes the target's index-plus-base operand order.
Both <=360 and <361 bounds produce the same remaining allocation difference.
Separating search from value retrieval with an explicit break grows the ELF
symbol to 76 bytes and duplicates the initial key comparison. The preserved
candidate is the best tested 66-byte form, restored and freshly matched again.
No assembly, volatile, compiler changes, artificial dead expressions or
register-steering constructs were used.

Fresh native report retained in the private address scratch as
last-native-report.md. Active unmatched source and report were removed.
