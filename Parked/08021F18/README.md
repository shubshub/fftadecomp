# 08021F18 tree rendering traversal

The canonical Thumb agbcc `-mthumb-interwork -O2` object gives the full
154-byte symbol at [08021F18, 08021FB2). All 154 linked bytes match the USA
ROM. Its SHA-256 is `1b28f97604da37d593eeabed05ed8b969343ae6fca07f0cb290ca7ac428c6325`.
The closed graph has 73 instructions, two internal alignment bytes and one
callback literal. The symbol is followed by two external alignment bytes.
The original ELF has R_ARM_ABS32 at +0x60 for func_080216F8 and R_ARM_THM_CALL
at +0x6E for _call_via_r7. The immutable callback pointer is 080216F9, and
the thunk at 08142260 executes BX R7. Payload and node are passed in R1 and
R0 respectively. Child and parent links are reloaded along the traversal.

The root saves 32 register bytes and allocates 12 local bytes. It stores
the narrowed x/y coordinates at offsets 0 and 2 and bytes at 4 and 6..10.
It skips offset 5 and the incoming argument at entry SP+0. The fixed
callback has 172 reachable instructions. It reads offset 5 at 080217E6
and passes that byte in its first outgoing stack word to 08001F34 at
08021840. The renderer loads that argument at 08001F46 and sets flags
bit 0x1000 at 08001F7E..08001F86 when the low byte is nonzero. The C
preserves the omitted assignment. Giving it a zero or the caller's
fifth argument would change the observed machine behavior. The two draw
paths call 080018A0 and 08001F34. Arbitrary input trees and termination
remain conditional.

On toolkit f1b81350, `--function-address-profile canonical-thunks-v1`
rejects the stack alias join, and
`--owner-runtime-profile bounded-buffer-conditional-thunks-v1` rejects the
local argument pointer at the indirect call. The two-word tree closure
does not cover this 12-byte root and callback. Saved MATCH credit requires
a native callback and loop proof that preserves the observable unwritten
byte, normal-return ABI, live local bounds, and callback effects. No
accepted report exists for this candidate.
