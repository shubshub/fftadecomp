# 0801539C

Complete indexed target: 0x0801539C..0x080153FC, 96 bytes and 44 reachable
Thumb instructions. The recovered function resets the text state, measures the
string as a u16 pixel width, centers it within an unsigned-byte width measured
in eight-pixel cells, moves the cursor by the resulting signed halfword offset,
and draws the string with the supplied byte style and a zero mode argument.
The return value is the draw operation's unsigned halfword result.

Five bounded native attempts used unchanged agbcc -mthumb-interwork -O2 and
the canonical matcher. The preserved candidate passes the complete 96-byte
ELF-symbol and source plausibility gates, but exits 1, NOT MATCHING:

    39/44 instructions identical (91/96 bytes)

Only the buffer/text saved-register allocation differs. The target keeps the
buffer in r8 and the text in sb; the candidate uses sb and r8 respectively.
This changes the following five instructions' register operands:

    address     target             candidate
    080153A8    mov r8, r1         mov sb, r1
    080153AA    mov sb, r2         mov r8, r2
    080153BC    mov r0, sb         mov r0, r8
    080153E0    mov r1, r8         mov r1, sb
    080153E2    mov r2, sb         mov r2, r8

All remaining instructions, including signed division toward zero, the
halfword offset narrowing, stack argument, direct call targets and return
narrowing, match the target bytes.

The first direct expression additionally scheduled the cell-width shift
before the measured-width zero extension (89/96 matching bytes). Assigning
the measured u16 width before calculating the offset recovered the target
arithmetic ordering (91/96). Ordinary destination/text locals retained that
result. A semantic centered-text-offset helper with plain static storage
emitted extra text and was refused by the native single-function gate. The
preserved standard static inline helper is fully inlined by fixed O2: the
native complete-symbol gate accepts it without extra functions or local
helper calls, but its saved-register allocation remains different.

No assembly, volatile, forced-inline attributes, compiler flag changes,
manufactured helper arguments, or artificial operations were used. A natural
form that recovers the target's buffer/text register allocation remains
unresolved. The final source-bound native report is retained in the private
address scratch directory. Unmatched active source/report were removed; the
root coordinator owns reservation release and integration.
