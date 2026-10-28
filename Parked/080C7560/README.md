# 080C7560: recovered, not byte matching

Complete target: `0x080C7560..0x080C75F2`, 146 bytes including literal pools and 66 reachable Thumb instructions.

The preserved complete natural C candidate passes native source plausibility and compiles to the complete 146-byte ELF symbol with fixed agbcc `-mthumb-interwork -O2`. Native matching exits 1: bytes differ. Aligned diff score is 54/66 instructions and 134/146 bytes. Actual same-offset equality is 134/146 bytes.

The remaining gap is a consistent r1/r2 allocation swap in twelve instructions: the candidate keeps the input-gate base in r2 and flags/menu base in r1, whereas the target keeps the input-gate base in r1 and flags/menu base in r2. Calls, control flow, field offsets, constants, pools, result normalization, and return paths match. The menu fields are correctly at +0x120 and +0x122.

The complete source recovers the input/menu blocking predicate, including the 0x40/0x80 path and external state check, the 0x20/count path, menu busy/type/count checks, final flag check, return code 2 when blocked, and delegated byte result otherwise.

Bounded natural forms tried: a global-state helper and an explicit input-state helper; byte and word boolean returns; an explicit second menu-state helper argument; and a local snapshot of the initially read flags. Word boolean return shortened the function to 144 bytes. Explicit menu input moved its literal load and changed allocation; a flag snapshot added operand-allocation differences. The preserved byte-return helper with explicit input state had the best correct full-extent result. No asm, volatile, pragmas, dead code, or compiler steering was used. These attempts do not establish permanent impossibility at the fixed flags.

Source-bound native evidence remains privately as `080C7560/best-report.md` and `best-native-output.txt`, alongside the full target capture. Unmatched active source/report were removed. No match credit is claimed.
