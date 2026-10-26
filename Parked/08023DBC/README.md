# 08023DBC

Target: complete `[0x08023DBC, 0x08023E88)`, 204 bytes / 84 reachable instructions.

The retained tested candidate compiles with fixed agbcc `-mthumb-interwork -O2` to a complete 192-byte ELF symbol, twelve bytes short. Native matcher exit 1: `compiled symbol is shorter than the indexed span: 192 < 204`. This extent rejection occurs before a complete comparison report, so no matching-instruction or matching-byte count is claimed.

The fixed-flag assembly shows a shared completion block: after the cancel sound call, the candidate branches to the confirm path's common `func_08013364` call, status clear, and flag-bit update. The target emits those operations separately in both paths, at `0x08023DDA..0x08023DE6` and `0x08023E02..0x08023E0E`. The zero-return block and literal-pool placement also differ. Both page-count byte reads corresponding to target `0x08023E1C` and `0x08023E26` are present; this is not a missing redundant-load case.

Tested natural forms: separate early-return branches produced 192 bytes; a structured if/else chain with a common success return produced 188 bytes; the retained inlined menu-completion helper produced 192 bytes and still shares the completion code. No flags, assembly, volatile accesses, pragmas, or compiler-steering operations were introduced. The private `candidate.s` records the retained form's fixed-flag output.
