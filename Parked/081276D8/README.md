# 081276D8: not matching

Both bounded candidates compile to 228 bytes against the complete indexed 240-byte target. Native match.py exits 1 with `compiled symbol is shorter than the indexed span: 228 < 240`, before writing a comparison report or plausibility verdict. No full MATCH is claimed.

The recovered C updates both 24-byte ramps, copies their values to object halfwords +8 and +0xC, conditionally advances the other state update, derives the object halfword +0xA from signed shifted coordinates, changes the animation byte when needed, always calls both completion predicates, and marks completion only when both are true. Source 08127990.c establishes the u16 result contract and initial payload fields; 08127D0C.c establishes the ramp and completion views. All defining helper C return/argument widths are retained.

The target is one complete function [0x081276D8,0x081277C8), with 105 reachable instructions, code ending at 0x081277C2, two alignment bytes, and literal 0x101 at 0x081277C4. It contains 12 direct calls and returns through bx r1 at 0x081277C0. Complete bounded ROM CFG evidence for the two helpers without C bodies is retained in the owned scratch packet. Both have only the state/ramp pointer as an incoming argument; the state helper returns the observed value in r0.

The diagnostic assemblies for u32 and u8 `changed` locals are identical. The compiler folds the animation-changed flag into a direct branch around the setter call. The target retains five extra instructions: `movs r0,#1`, a branch to the common test, `movs r0,#0`, `cmp r0,#0`, and a branch around the setter. This accounts for ten code bytes, plus the target two-byte alignment difference: 240 versus 228 complete bytes. The diagnostic has 100 instructions versus the target 105. The native size refusal remains unchanged.

Tried forms:

1. Natural explicit compare/store with a u32 change flag.
2. The same operation with a u8 change flag. This is candidate.c.

No helper boundary was introduced solely to prevent boolean folding. No artificial operations, asm, pragmas, volatile, dead operations, changed external signatures, toolkit/profile changes, or shared mapping changes were used. Native failure and current-machine source-bound receipt are retained under state/matching-081276D8-author/ at the handover root.
