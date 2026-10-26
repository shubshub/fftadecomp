# 0x0800F860 — Parked

Complete target: `[0x0800F860, 0x0800F93A)`, 218 bytes / 105 instructions.

The fixed native matcher exits 1: plausible C, complete 218-byte ELF symbol, 199/218 bytes and 94/105 instructions identical. The 20-byte stack frame, six incoming arguments, seven-argument direct calls to `0x0800ED58`, and named data linking are supported.

The recovered function fills a contiguous sequence of scanline spans, then calls the curved-span routine. It preserves the target's invariant clipping test: the tested initial row does not advance while the span pointer advances.

The remaining differences are saved-coordinate allocation and two equivalent arithmetic operands. At target `0x0800F89E..0x0800F8AA`, the shifted centerY is spilled at stack +0x0C, shifted centerX is retained in r8, and radius/2 is retained in sl. The candidate computes shifted centerX first into r8, retains shifted centerY in sl and spills radius/2 at stack +0x0C. This changes the corresponding coordinate and radius loads in both calls. The right endpoint uses r2 before moving to ip instead of r0, and the span-address add has the two source registers reversed. The remaining loop and call setup instructions match.

Seven native runs covered direct casts versus signed coordinate locals, signed word endpoint/row temporaries versus narrowed locals, a saved half-radius versus direct expressions, explicit scanline and global-byte pointer views, and natural caller argument widths. The final run restored the best complete-size candidate. Other forms produced 214- or 222-byte functions or an additional stack spill. No asm, volatile, pragmas, fixed registers, or artificial steering was used.

The nonmatching active source and report were removed. Source-bound native evidence remains privately at `/home/user/.codex-work/ffta-ulw/audio-following-v71-matching/0800F860/last-native-report.md`. No exact-match claim is made.
