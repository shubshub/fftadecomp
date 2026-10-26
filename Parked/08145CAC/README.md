# 08145CAC — four-channel Game Boy sound update

Target: complete indexed `[0x08145CAC, 0x081460F6)`, 1098 bytes and 501 reachable Thumb instructions. The upper-crossing end is retained; no shorter subspan was attempted.

The recovered C selects each channel's hardware registers, initializes instrument and wave state, advances attack/decay/sustain/release/echo envelopes, applies frequency and pan changes, writes volume/trigger registers, and clears modification flags.

Four native matching attempts used the fixed `agbcc -mthumb-interwork -O2` toolchain. Their complete ELF symbol sizes were 1066, 1078, 1078 and 1078 bytes. Every native invocation exited 1 at the short-symbol gate. The retained candidate occupies `[0x08145CAC, 0x081460E2)`, 1078 bytes, with 494 reachable instructions. These counts include the complete generated symbol and its middle literal pools; they are not a byte-equality score. The native gate did not reach byte comparison or a plausibility verdict.

Remaining differences observed in generated instructions:

- The target duplicates the channel-1/channel-3 register setup tails; the candidate shares a tail and consequently places the early pools and following code differently.
- The target copies the first three wave words with separate `str` and pointer `adds` instructions. The candidate combines each pair into a single-register `stmia`. Pointer and integer byte-cursor formulations both retained this combination.
- The target keeps the next channel number in r10 and next channel pointer in r9, spilling the nr0 register pointer at SP+8. The candidate keeps nr0 in r9, the next pointer in r10, and spills the next number at SP+20, shifting other pointer slots.
- The signed decay-envelope comparison uses shifted byte values in the target; the retained natural signed-byte comparison uses sign extension and a signed-byte load. Flag/read/write temporaries also produce different register choices and instruction ordering.

Natural iterations restored assignment-expression byte-counter tests, explicit control-register branches, source-pointer reload after the wave-enable write, the shared echo transition's position, a signed hardware-bias local, and the control-register assignment expression. Shared stage/flag locals and alternate wave-cursor types did not resolve the remaining differences. No compiler flags were changed, and no assembly, volatile access, optimization pragma, padding or dead computation was introduced. The observed wave-store difference is recorded without claiming that volatile access was the proven original cause.

The unmatched source/report were removed from their active locations. Root owns reservation release. Full target disassembly and the current private candidate remain in the assigned disk-backed private directory.
