# 08004E10 recovered C

The full indexed target is `0x08004E10..0x08004EC8`: 184 bytes and 71 reachable instructions. The complete recovered function checks serial state and hardware status, updates the interrupt shadow and enable register, acknowledges interrupt flags, initializes timer 3, starts serial activity when appropriate, invokes the two transfer helpers, increments the state counter, and returns the result byte.

The retained natural plain-C source compiles and assembles with fixed `agbcc -mthumb-interwork -O2`. `arm-none-eabi-nm -S` reports `func_08004E10` size `0xBC` (188 bytes), four bytes beyond the indexed target. The fresh default native matcher exits 1 with `compile failed: recursive or intra-function calls are unsupported`: the oversized candidate covers the adjacent indexed helper at `0x08004EC8`, which it calls. No native byte-comparison report or exact-match count was produced. This is a candidate extent failure, not evidence that the genuine target calls itself.

Compared with the captured target, the retained compilation saves an additional r8 register and holds the serial register address, original control byte, state pointer, and constant 8 in different registers. Its byte read-modify-write uses immediate `0xBF` where the target forms `~0x40` with a negate; the target also keeps constant 8 in ip and moves it back for the mode store. The recovered RAM offsets and hardware addresses/operations agree, including the combined timer word at `0x0400010C`.

Bounded forms tried were a local serial-register pointer and direct MMIO expressions, with byte or promoted-word snapshots of the two control reads. The retained local-pointer/promoted-word form is the compact 188-byte candidate. No custom compiler flags, assembly, dead code, or volatile accesses were introduced.

These are actual MMIO registers in `0x0400xxxx`; volatile qualification is the usual C contract for preserving hardware accesses. The current native plausibility contract rejects volatile, and the coordinator explicitly required keeping that contract unchanged. No volatile version was compiled or tested, so this attempt does not claim that qualification alone would recover the target bytes or that matching at the fixed flags is permanently impossible.

The last native command diagnostic is preserved privately in `08004E10/last-native-output.txt` in this matching batch. The unmatched source has been removed from `src`, and no generated report remains in `docs/match`.
