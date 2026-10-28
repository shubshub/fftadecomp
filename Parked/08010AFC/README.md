# 08010AFC — parked

Target: complete [0x08010AFC, 0x08010D2C), 560 bytes / 269 reachable instructions.
The retained candidate has a complete 576-byte ELF symbol, source plausible, native NOT MATCHING (exit 1), using fixed agbcc `-mthumb-interwork -O2`.

Recovered behavior includes blink timing, inactive-state checks, signed forward/reverse frame selection, both duration encodings, tick advancement, repeat handling, restart/stop state, and return flags. The blink logic and initial stack layout match. Remaining differences include register assignment around signed frame conversions and inline duration lookup, address-expression ordering in the compact and packed layouts, and merging of the end-of-animation stop branches. These change the complete extent and branch/pool locations; there is no isolated unused-load mismatch.

Natural forms tested: explicit signed frame/sequence locals with a duration reader (546 bytes); raw halfword inputs with signed casts at indexing sites (564 bytes); an inline reader handling the -1 current-sequence/current-frame defaults (568 bytes); and the retained signed-frame/u16-duration refinement (576 bytes). No flags or artificial operations were used. No further candidates were tried after the bounded reconstruction.

The last native diff reports 178/274 instructions and 473/576 bytes identical. Those denominators cover the 576-byte comparison window and include 16 ROM bytes beyond the true 560-byte target; they are not a complete-target match claim. The failed native report is retained in the private address directory as `native-not-matching.md`.
