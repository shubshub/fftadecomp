# 08028434

Complete indexed target: 0x08028434..0x0802849E, 106 bytes and 48 reachable
Thumb instructions. The candidate reconstructs the navigation-unit subobject
at state+0x38, cursor at state+0x58 (signed row at cursor+0x11), and motion
subobject at state+0x6C. It forwards the direction to the motion operation,
either sets the cursor row or refreshes the row and moves the unit, then
forwards the signed cursor row with value 0x0B.

Four complete natural candidates were tested using the unchanged native
matcher and fixed agbcc -mthumb-interwork -O2. The preserved final candidate
passes the complete 106-byte ELF-symbol extent and native source plausibility
gates, but returns exit 1, NOT MATCHING. The native report states:

    47/48 instructions identical (104/106 bytes)

The only remaining byte differences are the order of the two independent
argument moves before func_08017FB0:

    address     target                 candidate
    08028466    adds r1, r6, #0         mov r0, sb
    08028468    mov r0, sb              adds r1, r6, #0

The first candidate named only the cursor and unit pointers and also differed
in their saved-register allocation and setup ordering. Naming the actual
motion subobject alongside those two handles recovered every other target
instruction. Narrowing a word-sized incoming row into a local u8 added a
prologue ordering difference without resolving the call setup. Using an
opaque object argument with a typed NavigationState local retained the best
104/106-byte result and is the preserved tested source.

The cursor setter's byte parameter remains consistent with its existing
recovered definition; its prototype was not widened solely to change call
setup. No assembly, volatile, optimization changes, forced inlining, artificial
operations, or manufactured helper were used. A compliant natural source form
for the final argument-move ordering remains unresolved.

The final native report is retained in the address's private scratch directory.
Unmatched active src/08028434.c and docs/match/08028434.md were removed. The
root coordinator owns reservation release and any later integration.
