# 0804393C recovered state machine

The complete ROM symbol is [0x0804393C, 0x08043DF4): 1208 bytes and
487 reachable instructions. The preserved C recovers its initialization,
input/selection handling, animation wait and terminal states, with the
0xCC-byte menu-record stride and separate closed/active arrays.

The final ordinary native command used agbcc -mthumb-interwork -O2 and exited 1:
`compiled symbol is shorter than the indexed span: 1204 < 1208`.
The complete-symbol extent gate stopped this candidate before byte comparison
and source plausibility evaluation; it has no match credit or final plausibility
verdict. The missing four bytes do not represent an omitted source branch:
all captured control-flow cases are present. Register allocation, address reuse
and literal-pool layout still differ from the ROM.

Bounded natural forms tried: a partial menu-record view rooted at +0x984;
named x/y/width/height initialization values reused by the render calls; and
the complete menu-record view rooted at +0x954, which is preserved here.
The corrected partial and full views both produce 1204-byte symbols. Naming
the layout values also produces 1204 bytes and changes register allocation.
No assembly, volatile, forced inlining, flag changes or artificial dead
expressions were used. This is a bounded source/profile gap, not a claim that
no natural C can match these bytes.

The last native output and full target capture remain in the address-private
scratch directory. Active unmatched source and report have been removed.
