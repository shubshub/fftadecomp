# 080F3F7C — remaining vertical-offset code generation gap

The complete indexed target is [0x080F3F7C, 0x080F40DA), 350 bytes and 157 reachable instructions. The recovered callback implements initialization, a byte countdown, creation of two objects, interpolation and per-frame positioning, then release of both objects.

The final natural C produces a complete 350-byte ELF symbol with 156 instructions. The fixed native matcher exits 1, accepts the source as plausible, and reports 153/156 aligned instructions identical (344/350 aligned bytes). Direct comparison has 338/350 bytes identical at the same offsets. All differing bytes lie in [0x080F3FC8, 0x080F3FD4); every byte outside that interval is exact, including all calls, the interpolation loop, cleanup, and all literals.

The only remaining behavior-equivalent difference is the initial 16-bit vertical displacement. Target instructions at 0x080F3FC8 load the 0xFFCC offset into r3, copy r3 to r0, load the source y into r1, add r1 to r0, store y, and branch at 0x080F3FD2. The candidate instead loads source y into r0, loads the same offset into r3, adds r3 to r0, stores y, and branches at 0x080F3FD0. Its branch is two bytes earlier, followed by two alignment bytes; the offset literal still starts at 0x080F3FD4. This accounts for the complete remaining 12-byte same-offset mismatch interval and one fewer instruction.

Bounded attempts under unchanged agbcc -mthumb-interwork -O2:

- Direct signed subtraction of 52 produces a 342-byte symbol and fails the early short-symbol extent gate.
- A genuine u16 vertical-offset local initialized to -52 preserves the ROM's 0xFFCC literal and yields the final complete 350-byte result.
- Signed versus unsigned source-coordinate fields produces the same remaining difference.
- A semantic coordinate-offset helper used for both initial displacement and interpolation endpoint fully inlines but produces the same gap; it was removed from the preserved simplest reconstruction.
- The preserved helper-free C was run through the canonical matcher again; native exit 1, complete extent and plausible source were confirmed.

No assembly, volatile, compiler flags, forced inlining, checker changes, or shared-file changes were used. The unmatched active source and report were removed. The final native output and generated report remain in the private address scratch directory.
