# 08125FA8

Complete recovered display/control state routine. One natural bitfield candidate was tested using fixed `agbcc -mthumb-interwork -O2` flags, following the already observed same-family result at 08125DE8.

Target: complete indexed `[0x08125FA8, 0x08126118)`, 368 bytes, 153 reachable instructions. Preserved candidate: complete ELF symbol 364 bytes, 151 compiler assembly instructions. Default native matcher exits 1 at the extent gate: `compiled symbol is shorter than the indexed span: 364 < 368`. Byte comparison and native plausibility are not reached; no match or plausibility verdict is claimed.

The candidate omits two ROM instructions that read the previous destination byte immediately before overwriting it: `08126026` (`ldrb r1, [r4]`) and `081260FA` (`ldrb r2, [r1]`). Both address the control byte at 0x0300098A; their loaded values are unused. The recovered eight-bit control bitfield uses an unsigned-halfword declaration and ordinary compound clear/full restoration assignments. The compiler emits the value read needed for the clear, but omits those two additional old-value reads. The retained assembly otherwise follows the captured state blocks, display-call arguments, stack frame, register choices, cleanup and completion operations, with shifted branches and literal references after the missing instructions. No aligned or same-offset byte score is claimed.

The complete candidate preserves owner and variant capture, the 0x50-byte control snapshot, flags 0xC00, display mask 0x1C, allocation of 0xA04 bytes, both display kinds, polling, byte countdown, cleanup and saved control restoration. Related natural unsigned-byte and unsigned-halfword eight-bit forms were already tried on 08125DE8 and omitted the same old-value reads. No artificial dead expressions, volatile accesses, assembly, flag changes or forced inlining were introduced. This records a bounded remaining source/compiler gap, not permanent impossibility.

Unmatched active source/report are removed. Current compiler assembly and native output are retained in address-private scratch.
