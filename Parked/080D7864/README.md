# 080D7864 — Parked

Captured target: 184 bytes / 88 reachable instructions, 080D7864..080D791C.

The complete natural C submits the descriptor list for a kind-2 command. Other commands queue a transfer bounded by a mode-dependent limit, optionally add a selected destination offset for kind 3, advance source/destination pointers and reduce the remaining byte count, and return a byte completion flag.

Fresh native matcher exit 1: plausible C, complete 184-byte ELF symbol, direct Thumb BL with ordinary ARM ABI call summaries, no relocations. 182/184 bytes and 86/88 instructions are identical. The fixed four-byte outgoing argument area and fifth descriptor-call argument are accepted by the native gate.

Exact remaining differences are at 080D7876 and 080D78D8. Target uses `adds r1, r0, r2` (bytes 81 18); compiled C uses the equivalent `adds r1, r2, r0` (bytes 11 18). At each site r0 is the twelve-byte command index offset and r2 is the commands base. All other bytes, control flow, calls, stack operations, argument widths, transfer counts, and state updates match.

Bounded natural forms tested: direct compound command indexing with an early offset initializer gave a plausible complete 184-byte candidate with 175/184 bytes identical; an inline current-command accessor with named index/base locals and delayed offset initialization improved to 178/184 bytes; commuting its typed pointer addition did not change code; direct named index/base locals in the owning function reached the preserved 182/184-byte result. No integer-address reinterpretation or register forcing was added to alter the remaining commutative instruction operands.

The unmatched active source/report were removed. Last native report is retained in the private address scratch as last-native-report.md. Fixed compiler flags and verifier boundaries were unchanged.
