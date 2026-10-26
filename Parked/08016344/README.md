# 0x08016344 — Parked

The complete target is 540 bytes with 259 reachable instructions, ending at 0x08016560. The retained natural C recovers the border, interior, bottom-row, and optional shadow drawing paths.

The default native matcher with the fixed agbcc `-mthumb-interwork -O2` configuration returned exit 1: source plausible, complete 540-byte ELF function, closed leaf CFG, and no relocations. It reported 172/260 instructions and 483/540 bytes identical. This is not a byte-identical implementation.

The remaining differences are ordinary compiler output: the packed tile base occupies a different register, an early copy changes argument handling, address additions use different operand ordering, and register choices propagate into the shadow loop and alignment. Bounded natural variants changed variable lifetimes, row addressing, and tile-value reuse but did not reproduce the target. No unsupported verifier mechanism was encountered.

The native differing report is retained privately at `/home/user/.codex-work/ffta-ulw/audio-following-v73-matching/08016344/native-not-matching.md`; no ROM-derived instruction diff is included here.
