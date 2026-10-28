# 0814195C — unresolved countdown reload

Target: complete indexed Thumb body [0x0814195C, 0x08141984), 40 bytes / 16 reachable instructions, including two literal words. Fixed compiler: agbcc -mthumb-interwork -O2.

The preserved, natively tested source decrements the nonzero 16-bit countdown at data_03005E42 and sets the byte at data_0200F360 when the countdown becomes zero. Native verification reached the complete-symbol closed-leaf CFG and plausibility checks; both passed. The final verdict was NOT MATCHING - bytes differ, exit 1.

The compiled symbol is also 40 bytes but contains 15 reachable instructions: 30 instruction bytes, two alignment bytes and eight literal bytes. The target has 32 instruction bytes and eight literal bytes. After the initial countdown load and zero check, the target performs a second LDRH r0,[r1] at 0x08141966 before subtracting one. The compiler reuses the initially loaded value and omits that reload. Its returns and conditional branch destinations are consequently two bytes earlier; alignment padding follows the return instead. Both data relocations link to the approved named bindings.

Tested the preserved direct update and an ordinary static inline decrement_countdown helper returning the new u16 value. Both compile to the same 40-byte symbol with the same missing reload and pass source plausibility. The native aligned diff score was 12/15 instructions and 37/40 bytes; this score is not same-offset byte equality. The initial load is used by the zero guard, so this is a reload-elimination gap, not an unused load before a whole-byte store.

No evidence established a volatile or other special declaration for this RAM counter. No artificial volatile access, dead expression, assembly, forced inline, flag change or shared metadata change was introduced. The simpler tested direct form is preserved. Unmatched active source and report were removed.
