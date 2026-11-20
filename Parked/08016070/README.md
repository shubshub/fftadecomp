# Window text icon drawing at 08016070

The owned Thumb function spans [0x08016070, 0x080161A0), including a graphics-state literal at 0x080160F8 and a tile buffer literal at 0x0801619C. Two direct calls at 0x080127F8 (in 0x080120F0) and 0x08015792 (in 0x080154D8) supply eight arguments and discard the result.

The routine locates a text icon in a tilemap using the text cursor, row width and window flags. The icon lookup writes a missing flag to a local byte. On success the routine writes four consecutive tile numbers with the returned palette in a 2×2 square and copies 64 halfwords from the shared tile buffer. It advances the cursor by 16 on both paths.

## Native result

The original agbcc with `-mthumb-interwork -O2` emits 304 bytes, with 241 matching bytes at their original offsets and 63 differing. Both named data relocations, all three direct BL instructions, both literal-pool positions, the epilogue and the 2×2 store sequence match. The compiler spills the window pointer early, where the ROM keeps it in R9 and spills the horizontal origin. The different register assignments propagate through the width-reduction loop and tilemap address calculation. The original also reads the cursor through R4 immediately before the BIOS copy, where the compiled candidate uses R0. Reordering declarations, using a working tile index, factoring address calculation and varying ordinary loop and coordinate expressions did not close this difference.

Every differing byte offset, in hexadecimal relative to 0x08016070 (inclusive ranges), is listed below.

`00E–017, 019–01D, 01F–021, 023–02D, 02F–030, 032, 03A–03D, 040, 042, 044, 046, 048, 04A, 04C, 054, 058, 064, 06E, 072, 07A, 084, 08D, 09A, 09E, 0A0, 0AE, 0B0, 0B6–0B8, 0C0–0C1, 108, 10A`

Linked C SHA-256 `b17c09ffba3bde425e5aab5cc3a445f73b9f3d3f8eb2a95a33a372a16e5e12e4`. ROM extent SHA-256 `949937aa5c21919f60e9cc002eb906c7e84a4890996825e1bd8e7b63fcd99609`.

## Verification boundary

The default native matcher stops while inspecting the local output byte passed to 0x08015DAC, via 0x080CEBF8 and 0x080CE4DC, at an unresolved program-counter write. Running the public structural selectors separately on the original ROM isolates a second boundary. The guarded-switch selector refuses an observed discarded return register in 0x08015DAC. The guarded-callee-alias selector retains that alias and reaches the root return at 0x0801619A with R2 pointing to the missing flag at entry SP minus 40. The public root-return-scratch selector stops earlier at the nested switch.

A Thumb emulator checked the ROM and linked C separately against the expected tilemap writes, helper arguments, return address, restored stack pointer and callee-saved registers in 360 cases each. The checks covered the special icon code boundaries, window flag combinations, row wrapping, tile-number wraparound and both missing-flag outcomes. The three helpers were stubbed at their call boundaries. The 63 differing bytes keep the function out of the matched count.
