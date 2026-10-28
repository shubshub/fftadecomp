# 0803578C — Parked

Complete target: [0x0803578C, 0x08035844), 184 bytes, 79 reachable Thumb instructions.

The complete natural reconstruction copies two three-bit display modes from menu-state offsets 0xF28 and 0xF2C, then copies the three word-valued panel flags at 0xF30, 0xF34 and 0xF24. The recovered display fields are byte-sized packed bitfields at offsets 0x9A and 0xE6. The panel bitfields agree with existing matched neighboring functions.

Fixed native agbcc -mthumb-interwork -O2 accepted the source as plausible and verified its complete 184-byte, single-function ELF extent and closed leaf CFG. Native byte comparison exited 1: 162/184 bytes and 60/80 compared instructions are identical. The compiler emits an additional mode-mask register copy and uses different allocation/scheduling through the first panel update; the final two panel updates and literal values agree. The target has 79 reachable instructions plus two-byte alignment before its pool; the candidate has 80 instructions with no alignment word there. No match credit is claimed.

Bounded alternatives checked byte-mode and word-mode representations. Word/bitfield mode variants produced shorter 168- or 180-byte symbols and failed the complete-extent gate. A genuine repeated-mode helper was rejected because fixed -O2 retained an extra emitted helper; that version was discarded. The retained C uses direct natural bitfield assignments, without helper bodies or code-generation controls.

Fresh report_matches returned false, as required for this nonmatch. The final native report, log, unmodified original compiler relocatable ELF and absolute-path SHA256 result manifest are retained in the sibling batch scratch directory 0803578C. Unmatched active source/report were removed.
