# 08049E10 — unmatched natural C

Target: `0x08049E10..0x08049ECE`, complete 190-byte symbol and 88 reachable instructions. The retained candidate also emits a complete 190-byte symbol with 88 instructions, the three four-byte literals, and two alignment bytes. Fixed `agbcc -mthumb-interwork -O2`; no truncation, additional helper, or compiler steering.

The final native matcher exited 1: `bytes DIFFER`, `source plausible`, `NOT MATCHING - bytes differ`. Its aligned diff score is 85/88 instructions and 185/190 bytes; this is the native alignment metric, not a same-offset byte-equality claim. The complete ELF symbol has a closed leaf CFG and no relocations.

The function places twenty-byte menu rows at object offset 0x230, scans sixteen resource pointers, and appends rows for nonzero packed ten-bit IDs and nonnull pointers. It preserves the target's ID test before its pointer test, fills the resource-name pointer and row fields, and sets the remaining menu fields and height before returning the row count.

Remaining difference is confined to three setup instructions. Target loads the name table through r0 (`ldr r0, [pc, #0x5c]`), moves that address to r8, then copies the existing row base from r1 to r3. The candidate first copies r1 to r3, then loads the same table through r1 (`ldr r1, [pc, #0x58]`) and moves it to r8. The scan, packed reads, row stores, loop branches, dimension calculation, final field stores, return, and complete function extent match.

Bounded natural forms covered direct and cached table references, delayed counter initialization, direct storage versus published row-pointer access, and row initialization before the loop, in its initializer, or before publishing it. A named name-table pointer exchanged the zero and table registers. Initializing the working pointer before publishing it shortened the compiled symbol to 186 bytes and failed the full-span gate. The retained full-length form was restored and freshly checked.

Source SHA-256: `a3b51e174d282d9d8da8a2345982504f24039a1171761906b2bdd9a0a6c0f863`.
Final native report SHA-256 before removing the unmatched active report: `7fa5507fec65202e05b75ad77aea8a24fe0f7df2d0ee56759bfaa15bf1483256`.

Only this private Parked pair is retained for integration. Active private source/report are removed; no main files were edited and no exact-match credit is claimed.
