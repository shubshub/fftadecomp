# 0812AD14 bounded natural-C attempt

Target: `0812AD14..0812ADDC`, 200 bytes / 93 reachable instructions.
Fixed compiler: agbcc `-mthumb-interwork -O2`; native function-address profile: `canonical-thunks-v1`.

The complete recovered function clears one 120-byte text page and a 256-byte scratch buffer, calls `func_08013E9C`, then decodes two-byte cells and the `@n`, `@s`, `@>`, and `@c` commands. The page, scratch-buffer, and input pointers occupy state offsets `0x304`, `0x308`, and `0x30C`. Incoming arguments are the state pointer and an unsigned byte page index; return type is void.

The preserved candidate compiles to one complete 200-byte ELF function containing 92 instructions. The final native invocation exits 1 with `inert-spin complete body differs from ROM`. That check occurs before the ordinary byte-comparison report and plausibility verdict; no match or plausibility credit is claimed.

The first differing instruction is at target address `0812AD34`: the ROM loads the clearing callback slot address into `r6`, while the candidate uses `r5`. The candidate retains the buffer-member address in `r6`, column in `r5`, and row offset in `r4`; the ROM uses `r5`, `r7`, and `r6` respectively. At the loop's first byte read, the ROM copies the loaded `r2` byte into `r4` before comparing against `0x40`; the candidate compares `r2` directly and lacks that instruction. Its same-size middle literal pool follows an alignment gap. The target and candidate extents being equal does not imply same-offset byte equality.

Bounded natural forms tried: direct character conditional; outer switch on a promoted local character; direct switch on the buffer byte; byte, signed-word, and unsigned-word character locals; and literal versus loaded values for the known `@s` pair. These forms did not reproduce the ROM register allocation and character copy. An initial two-byte structure rounded to four bytes under this compiler, so the complete candidate uses an actual two-byte array cell. Initial incorrect member offsets were corrected before the final full-extent attempts. No flags, assembly, volatile accesses, artificial dead expressions, or forced register constraints were used. This records the bounded source gap under the fixed flags, not a permanent impossibility claim.

Native output and diagnostic compiler assembly remain in the address-private scratch directory. The unmatched active source/report were removed.
