# 0x080823B0 - near miss (1212 bytes): one register swap, 479/487 instructions

Retry of Parked/080823B0 on 2026-11-16, kit fcdf2d45, default flags.

The source here is structurally complete: the compiled symbol is exactly 1212 bytes, every instruction shape, operand order and pool word
matches, and the older parked README's 56-byte shortfall and extra pushed register are gone. match.py: NOT MATCHING - bytes differ, 479/487
instructions identical (1203/1212 bytes); not a refusal. plausible.py: no findings. Index row 080823B0 0808286C 1212 487 correct; no data symbols
needed. Not shipped: not byte-identical.

Remaining difference: one register swap inside the held-0x200 page-down block - in the ROM `visible` (list +0x16) is in r3 and `scroll`
(list +0x1A) in r5; here they are the other way round. That is all 8 differing instructions. In this build the global allocator ranks scroll
above visible (5000 vs 4347).

Helpers: RECORD_CURSOR is the macro of the matched src/08081DEC.c (shared text). cursor_row, a one-line static inline accessor used twice, has no
shared text; without it the function is 1208 < 1212, so a shipped source would also need evidence for it.

Sibling evidence: matched src/08042774.c contains the same page-down code and its ROM uses the target's registers (r3 visible, r5 top). Its source
declares `u16 visible`, a `u16 span = visible * 2;` local and an if/else clamp. Copying that here (u16 visible, u16 span, ?: clamp) flips the
pair but pushes scroll to r4, the record base to r5 and the input pointer to r6 (58 differing lines); the sibling's if/else clamp shrinks this
function to 1184 bytes.

Ruled out (hundreds of compiles): every u8/u16/s32 combination for visible, scroll, count, position and u8/u16/s16/u32/s32 span; declaration
order, uninitialised declarations, every subset of locals moved to function scope (24 to 168 lines worse); reading fields directly; += vs =,
four else-store forms, visible + visible, swapped commutative operands, inverted inner if, else wrapper, min-then-subtract clamp; reloading
visible or count in the clamp, an inline clamp helper; a last = count - 1 local, (s8)next casts instead of the row local, u8 old, cursor_row
spellings, an s32 index parameter.

Open idea: something elsewhere in the function that raises the record base pointer's or lowers scroll's allocation priority while emitting the
same instructions (e.g. how the list pointer is obtained, or the page-down block being an inlined copy of a helper shared with 08042774).
