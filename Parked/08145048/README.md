# 08145048: state-byte reset and flag update

The complete indexed ROM body is [0x08145048, 0x08145062): 26 bytes and
13 reachable Thumb instructions. It clears the bytes at offsets 0x16 and
0x1A, then ORs the flags byte at offset 0 with 12 when byte 0x18 is zero,
or with 3 otherwise. The first incoming argument is untouched by the ROM.

The retained natural C recovers these operations. With the fixed agbcc
-mthumb-interwork -O2 toolchain its complete ELF symbol is 28 bytes and
14 instructions. The final native invocation exits 1 with closed leaf CFG,
no relocations, source plausible, and NOT MATCHING - bytes differ. This is
not an exact match and earns no match credit.

Remaining differences: ROM leaves r0 untouched, uses r2 for the clears,
mode load and selected mask, loads the flags byte into r3, and returns via
bx lr without an LR frame. The compiler uses r0 for the clears and mode,
saves/restores LR, and initializes mask 3 before the comparison rather than
emitting the ROM's two-branch mask selection. These register and control-flow
differences account for the nonmatching complete symbol.

A natural return-of-first-argument variant produced 32 bytes and still
saved/restored LR. A naturally inlined byte-mask helper produced 30 bytes,
retained explicit mask branches, but still used r0 scratch and an LR frame.
Neither improved on the retained 28-byte direct form. No assembly, volatile,
compiler-option changes, forced inlining or artificial argument uses were
introduced. Further recovery needs genuine original ABI/type or compiler
context; an unused argument cannot be made live just to retain r0.

Final native log:
/home/user/.codex-work/ffta-ulw/audio-following-v429-matching/08145048/match-current.log.
Active unmatched C and report were removed; only this Parked pair is
proposed for integration.
