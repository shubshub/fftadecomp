# 0800AFAC — parked

Target: complete [0x0800AFAC, 0x0800B0AC), 256 bytes / 120 reachable instructions.
Fixed native agbcc `-mthumb-interwork -O2`: complete 256-byte candidate; source plausible; NOT MATCHING (exit 1). Native comparison reports 119/120 instructions and 254/256 bytes identical.

The remaining difference is the order of one register-preservation instruction. The candidate emits `mov sb, r0` at 0x0800AFB4, before narrowing the format, size, and index arguments. The target emits the same instruction at 0x0800AFC4, after those conversions and immediately before preparing the first call. All subsequent instructions, both dimension switches, record stores, allocation calls, literal words, and return sequence match.

Tested natural declarations: pointer-valued first argument and record field; opaque u32 first argument and field; and u32 inputs explicitly narrowed into u16/u16/u8 locals (retained candidate). All three compile to the same instruction sequence with the same single ordering difference. No compiler flags, synthetic operations, assembly, volatile access, or optimization directives were used. Matching stopped after this bounded signature reconstruction attempt.
