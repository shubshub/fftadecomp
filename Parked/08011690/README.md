# 08011690

Complete recovered linked-list iterator for 08011690..080116DC: 76 bytes,
38 reachable instructions. With the default agbcc -mthumb-interwork -O2,
native match exits 1 after accepting the complete ELF extent and plausible
source; the byte comparison fails.

The best tested candidate has the correct 76-byte extent. Its explicit
availability boolean is initialized before the 0x18 mask calculation; the ROM
initializes it after that calculation. The final 0x20 test uses
`ands r1, r0; cmp r1, #0`, while the ROM uses `ands r0, r1; cmp r0, #0`.
All other control flow and node/iterator accesses agree. Native aligned diff:
35/38 instructions, 72/76 aligned bytes. Direct same-offset equality:
68/76 bytes.

Natural forms tested: a direct compound predicate (66-byte symbol, rejected
at the extent gate); an inline logical predicate with u16 flags (78 bytes,
extra flag load and different boolean lowering); explicit availability with
u16 flags (preserved); a negated conjunction assigned to availability;
an inline early-return predicate with promoted u32 flags; and named category
and blocking-mask locals. The last forms retained different boolean lowering,
register allocation or scheduling. No assembly, volatile, flag changes,
forced inline or artificial operations were used.

This bounded attempt leaves a precise code-generation gap, not a claim that
no natural source can match. Fresh native output and the best generated report
remain in the private address scratch directory. Active unmatched C and report
were removed.
