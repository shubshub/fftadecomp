# 08141E30 — recovered, unmatched

The target is the complete indexed Thumb body [0x08141E30, 0x08141EB8):
136 bytes and 55 reachable instructions. The preserved C recovers the byte
phase/address/expected arguments, callback polling, timeout flag, conditional
manufacturer-0xC2 flash reset write, 0xC000|phase error, cleanup and u16 return.

The last default native invocation with canonical-thunks-v1 exited 1:
`compile failed: inert-spin complete body differs from ROM`.
The fixed agbcc -mthumb-interwork -O2 output has exactly one FUNC symbol,
func_08141E30, of 136 bytes; complete-body equality fails before plausibility.
No match or plausibility approval is claimed.

The preserved candidate precomputes the u16 timeout error. Its first differing
instruction position is target address 0x08141E4C: the ROM loads the callback
slot address into r7 there, while the candidate begins constructing 0xC000
with `mov r1,#192`. The candidate keeps the timeout value in r7 and callback
slot address in r4, while the ROM keeps those roles in r4 and r7 respectively.
Its timeout/manufacturer block and literal pools also occupy different places.
This is a register-allocation and control-flow-layout residual, not a claim
that the native verifier prohibits flash polling generally.

Bounded natural forms tried: precomputed timeout error (preserved, 136-byte
symbol); computing the error only in the failure branch; explicit polling
with early success breaks, including a flattened timeout branch; and a
semantic static inline polling helper. None passed complete native equality.
Flags and native gates were unchanged. No volatile, assembly, artificial
accesses or function-pointer data aliases were introduced.

Native output: ../../../08141E30/last-native-output.txt. Target capture and
candidate assembly are retained in that sibling batch address directory. No active unmatched src/report is
retained. This bounded outcome is not a permanent impossibility claim.
