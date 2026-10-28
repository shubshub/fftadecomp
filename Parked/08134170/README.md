# 08134170: bounded native mismatch

Target: complete [0x08134170, 0x081341BA), 74 bytes / 37 reachable instructions.
Compiler: unchanged agbcc -mthumb-interwork -O2.
Latest native match.py exited 1: complete 74-byte ELF extent and plausibility passed,
but bytes differ. The candidate has 37 instructions; 8/37 instructions and 31/74
same-offset bytes are identical. Native output is retained in address scratch at
../08134170/native-output.txt relative to the matching root.

Recovered behavior: object byte 0xE7 holds current and previous four-bit references;
other object byte 0x104 supplies an identity. Equal object pointers or an already
current identity leave the pair unchanged. A previous identity swaps forward;
a new identity shifts the current reference into the previous slot.

The preserved complete candidate uses flat unsigned-byte bitfields at the proven
0xE7 offset and a byte identity at 0x104. Its low-nibble extraction uses left/right
shifts rather than the ROM's mask. In the swap branch it retains additional masks
and old-byte merge operations instead of the ROM's direct previous | current << 4.
Its insert branch reuses the earlier shifted low nibble and lacks the ROM's explicit
0xF0 mask and ip temporary. Register allocation and branch displacements consequently
also differ. These are genuine native code-generation differences, not a gate refusal.

Bounded natural attempts tested byte, promoted signed/unsigned word, and halfword
locals, plus flat byte/word bitfield storage. Promoted locals gave 66-byte symbols;
flat word fields with narrowed locals gave 68-byte symbols, rejected by the extent
gate before plausibility. An initial nested pair had incorrect compiler-imposed
alignment and was corrected to flat fields. No assembly, artificial reads, volatile,
forced inline, compiler changes, or steering were introduced.

Active unmatched source and generated report were removed. No exact match credit.
