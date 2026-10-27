# 0800BF04 — bounded nonmatch

Accepted claim: 6454124194 (batch v647). No match credit claimed.
Target: 0x0800BF04..0x0800BF50, complete 76 bytes / 32 instructions.
The candidate updates bits 14 and 15 of the object's attribute halfword according to two incoming byte flags.

Final native matcher exit: 1, NOT MATCHING — bytes differ. The complete 76-byte ELF-symbol extent and closed leaf CFG passed; there are no relocations. Source plausibility passed. The fixed compiler was agbcc -mthumb-interwork -O2 with the approved USA/Australia ROM; no runtime profile was selected.

The aligned matcher comparison is 74/76 bytes and 31/32 instructions. There are six positional byte differences (70/76 positional bytes identical). The sole instruction scheduling residual is that compiled `adds r3,r0,#0` occurs at 0x0800BF06, before the three argument truncation instructions; the ROM places that pointer copy at 0x0800BF0C, after them. Positional differences occur at 0x0800BF06, 0x0800BF07, 0x0800BF08, 0x0800BF0B, 0x0800BF0C and 0x0800BF0D. Every byte from 0x0800BF0E onward agrees, including branches, stores, returns, literals and alignment.

Bounded natural attempts:

- Direct typed u8 flags and a struct halfword field: complete 76 bytes, plausible, scheduling residual above. This is the preserved best candidate.
- Wider u32 arguments normalized through local u8 flags: the same native output and residual.
- A genuine naturally inlined semantic flag helper with u16 masks: compiled to 60 bytes and failed the complete-extent gate; plausibility was not reached for that attempt.
- Restored the direct typed candidate and reran the native matcher: exit 1 with the exact residual above.

Evidence is in sibling batch scratch `0800BF04/native-attempt-1.log`, `native-attempt-2.log`, `native-attempt-3.log`, `native-final.log` and `last-native-report.md`. No assembly, pragmas, volatile, dead code, forced inlining, artificial padding or register steering was used. The unmatched active source and report were removed after preserving this pair.
