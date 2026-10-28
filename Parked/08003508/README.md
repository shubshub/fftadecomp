# 08003508 — bounded natural-source attempt

Target: 0x08003508..0x08003558, complete 80-byte symbol, 30 reachable instructions.
Preserved candidate: complete 72-byte symbol, 26 instructions, with the four indexed data literals and the same branch structure. It replaces one of four halfword fields at offsets 0x0A, 0x0E, 0x12, or 0x16 according to the byte selector.

Fixed compiler: agbcc -mthumb-interwork -O2. The native matcher exits 1 at the complete-symbol extent gate: `compiled symbol is shorter than the indexed span: 72 < 80`. Linking, byte comparison and native source plausibility were not reached; no match or plausibility acceptance is claimed.

The target loads the previous halfword into r1 immediately before each complete halfword replacement. The preserved natural `u16 value : 16` field assignment compiles to the matching branch/register/store sequence but omits those four loads: target sites 0x0800351C, 0x0800352E, 0x0800353E and 0x0800354A. Their eight bytes account for the entire extent difference. A 32-bit channel representation using adjacent `u32 : 16` bitfields also compiled to 72 bytes and failed the same native extent gate.

The simpler tested halfword layout is preserved. Artificial unused reads, volatile accesses and compiler steering were not introduced. Active unmatched source/report were removed.
