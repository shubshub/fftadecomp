# 08144D94

Complete target: [0x08144D94, 0x08144DD8), 68 bytes, 30 reachable
instructions. Fixed agbcc -mthumb-interwork -O2.

One complete natural typed-callback candidate was tested. Native matcher exit 1:
72-byte complete ELF symbol, source plausible, 52/72 bytes and 18/32 instructions
identical across the compiled comparison span. This includes four bytes beyond
the target's 68-byte extent; it is not a complete match.

The implementation follows the observed linked-channel cleanup: when track flag
0x80 is set, traverse channels at +0x20, call the driver's typed stop callback
at +0x2C for nonzero channel types masked with 7, clear active flags and owner,
then clear the track's channel head. The first incoming argument is unused.

Precise remaining gap: natural callback invocation emits the canonical compiler
_call_via_r1 thunk linked at 0x08142248, while the target BL calls the separately
indexed helper at 0x08144D84. Callback setup also differs: the target loads its
callback into r3 and retains the masked argument in r0; this source uses r1 and
a temporary r2 before moving the argument to r0. The target starts with TST
rather than the candidate's AND/CMP, and its inner AND branches directly rather
than retaining a separate comparison. These differences change loop branches
and pool alignment. The source contains no addressed-name callback substitute,
manual runtime alias, artificial narrowing, or register forcing.

The native report is retained in address scratch as last-native-report.md.
Active unmatched source/report removed. No match credit.
