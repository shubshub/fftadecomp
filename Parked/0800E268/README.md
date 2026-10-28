# 0800E268 — Parked

The complete indexed target is 0x0800E268..0x0800E454: 492 bytes and
239 reachable Thumb instructions. The preserved complete candidate also spans
492 bytes, ending at 0x0800E454, with 236 reachable instructions.

Fresh native matching at fixed agbcc `-mthumb-interwork -O2` exits 1:
`NOT MATCHING - bytes differ`; source plausibility passes. The closed leaf CFG
and complete ELF extent are supported, with no relocations. The native aligned
diff score is 149/236 instructions and 389/492 bytes; these are alignment-based
diff scores, not same-offset byte equality or match credit.

The implementation fills 160 scanline bounds, chooses packed four-byte or
eight-byte animation records, resolves a relative shape offset, applies signed
position offsets and vertical clipping, and advances the animation timer/frame.
It handles loop flag 2, terminal flag 0x8000 and duration sentinel 999.

Remaining differences:

- The target allocates four stack bytes and saves the frame count there. Its
  ordinary/positioned animation bases occupy sb/sl and its signed drawing X
  occupies r8. The candidate has no local stack allocation: the bases occupy
  r8/sb, the frame count occupies sl, drawing X occupies r6, and the shape
  pointer occupies r5 rather than r6.
- The target explicitly guards the drawing loop before entry, loads its signed
  height with `ldrh` and shifts, and retains the shifted scanline value in r5.
  The candidate uses a shared loop test and `ldrsh`, retaining that value in r3.
  These choices also alter the drawing-source/destination temporary registers.
- The target preserves the zero timer value and frame-field address for a
  common frame-reset store. The candidate keeps the duration in another
  temporary and recomputes the frame-field address when resetting it.
- The candidate materializes an extra 0xFFFF literal when narrowing the
  incremented frame. The target instead uses a shift pair. Different literal
  placement and alignment compensate for the instruction-count difference,
  so equal complete extents do not imply a close byte match.

Bounded natural forms tested: separate fill and drawing counters; pointer and
indexed fill traversal; short and word-sized coordinate temporaries; signed
and unsigned scanline induction; structured for/while and guarded do loops;
record-local and function-scope packed frame pointers; direct duration stores
and a shared duration value; structured and shared-label restart paths; and
struct versus raw halfword/word shape-header representations. A short drawing
counter emitted unwanted narrowing, an aligned packed shape added access
instructions, and a word header emitted a word load. The preserved form uses
ordinary halfword shape fields and packed animation records. No flags,
headers, maps, toolkit code, assembly, volatile accesses or steering were used.

Native output and the corresponding generated assembly remain in the private
0800E268 scratch directory. The unmatched active source and generated report
were removed; only this C/README pair is intended for integration.
