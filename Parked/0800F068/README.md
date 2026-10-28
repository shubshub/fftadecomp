# 0800F068 — not matching

Complete target: `[0x0800F068, 0x0800F308)`, 672 bytes and 317 reachable instructions.

The recovered C implements the radius-zero return, the upper-span call, and both lower ellipse branches. Each lower loop caches the horizontal division when its radius coordinate changes, computes the other scaled coordinate, clips and stores two spans, and updates the midpoint error and 16-bit coordinates. The unclipped branch offsets the span base by the radius. The shared static inline helper is completely inlined by the fixed compiler.

The final fresh default native invocation exited 1 with:

`compiled symbol is shorter than the indexed span: 624 < 672`

This is a 48-byte extent gap. Byte comparison, native control-flow validation and source plausibility were not reached; no exact or plausibility credit is claimed. The captured target uses a 72-byte local frame; the retained candidate uses 56 bytes. The remaining source gap concerns coordinate conversion lifetimes, register/spill allocation and the 16-bit error/coordinate update expressions. The target retains additional signed-coordinate conversions and saved coordinate values around the division calls.

Bounded natural attempts covered unsigned and signed 16-bit loop variables, explicitly narrowed wider counters, signed/unsigned helper coordinate types, pre/post-decrement error updates, loop-local signed origins, and a shared upper/lower helper representation. Compiled sizes were 576–624 bytes, all below the complete target. The 624-byte signed-counter candidate is retained and was freshly rechecked after restoration. No compiler flags were changed and no steering constructs were added.

Command: `python /home/user/Documents/Claude_Chats/2026-10-09/fftadecomp-kit/tools/match.py --root /home/user/.codex-work/ffta-ulw/audio-following-v98-matching/matching-root 0x0800F068`, with the approved ROM, ARM toolchain PATH, disk-backed TMPDIR and fixed `-mthumb-interwork -O2` environment. The concise native output is retained privately in the address scratch directory. ROM-derived disassembly and compiler diagnostics are not included in this Parked pair.
