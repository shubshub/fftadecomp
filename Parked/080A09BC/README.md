# 080A09BC — unmatched

Target: complete `[0x080A09BC, 0x080A0BB6)`, 506 bytes / 246 reachable instructions.

The complete retained natural C candidate computes signed endpoint differences, absolute planar distance and angle, then processes each signed height. It finds the vertical span, optionally scales speed, writes planar velocity components, and initializes the six observed signed 64-bit fixed-point trajectory fields in each 0x58-byte record.

Fresh final native result: exit 1 before comparison, `compiled symbol is shorter than the indexed span: 468 < 506`. The direct compiler listing contains 229 instructions and 5 BL instructions. No native byte-match count or plausibility verdict was produced; this is not a match.

Main remaining gap: the source explicitly repeats both velocity-component calculations in the vertical-scaling and ordinary branches, but agbcc merges them into one shared cosine/sine pair. The target retains two cosine/sine pairs and has seven static BL instructions, versus five in the candidate. Related lifetimes and register allocation differ: target speed stays in r7, height pointer in r8, absolute X in r9 and planar angle in r10; candidate instead uses r8 for speed, r7 for the height pointer, a stack slot for absolute X and r9 for the angle. The inner maximum selection also has a different conversion/selection sequence.

The observed signed 64-bit shift-and-store sequences and trajectory field offsets 0x78, 0x80, 0x88, 0x90, 0x98, and 0xA0 are represented directly. No runtime helper workaround or alternative compiler flags were introduced.

Bounded natural attempts:

- Initialize both absolute-value temporaries before their sign checks: 468 bytes.
- Initialize absolute Z after the absolute-X sign check, following the target's assignment order: 468 bytes, retained.

No assembly, padding, volatile access, register variables, dead code, or compiler flag changes were used. The unmatched active source and any address report were removed.
