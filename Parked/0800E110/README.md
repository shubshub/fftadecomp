# 0x0800E110 - near miss (144 bytes): 140 compiled; two dead ldrb that only volatile reproduces

Retry of Parked/0800E110 on 2026-11-16, kit fcdf2d45, default flags. match.py: 'compiled symbol is shorter than the indexed span: 140 < 144'.
plausible.py exits 0 on the source here. Index row 0800E110 0800E1A0 144 68 correct; no data symbols.

Every compiled instruction matches the target; missing are two dead loads at 0x0800E134 / 0x0800E136 (ldrb r0, [r1, #2]; ldrb r0, [r1, #3]) - a
read of header->frame_count, in the same order the sibling src/0800E1A0.c reads it, never used. Both land in r0 with nothing using them, so they
had no live range at allocation. Non-volatile dead loads are deleted by flow; a use that combine folds in the same block is removed by its
dead-insn cleanup (distribute_notes) - tested with frame_count & 0xFFFF0000; a folded use in a later block keeps the loads live in separate
registers (r4/r3, r8/r7). A diagnostic `frame_count = ((const volatile FrameHeader *)data)->frame_count;` placed before the width read and left
unused is byte-identical (68/68, 144/144; match.py: source IMPLAUSIBLE, ERROR: volatile, HAND-ASM REQUIRED BUT NOT ALLOWED); after the width read
the two loads land after it (66/68). Not used: volatile is admitted only on evidence-backed declarations in include/ on the plausible.py allow list,
and this is ROM data reached through a pointer. A whole-ROM scan finds no other back-to-back same-register load pair, so there is no matched
precedent.

Possible evidence for the maintainers: src/0800E1A0.c still compiles to identical bytes with its header reads made volatile, which would fit an
original header type that was volatile-qualified. The allow list only covers an extern RAM struct; a ROM data pointer would need a policy decision
(compare kit #168 for pointer-reached RAM buffers; no issue covers ROM data).

Ruled out: a static inline draw helper returning frame_count with the caller ignoring it (deleted); same-block folded uses (& 0xFFFF0000, >> 16,
> 0xFFFF, > 0x7FFF, < -0x8000, unsigned < 0) (deleted or the compare stays); folded uses after the if/else (distinct registers); a step-by-step
read (fc = data[3]; fc <<= 8; fc |= lo) (deleted); a packed u32 header narrowed to u16 (two bytes loaded). The older parked README's combine
theory does not hold.
