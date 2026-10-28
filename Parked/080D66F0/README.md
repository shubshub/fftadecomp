# 080D66F0 — Parked

Captured target: 168 bytes / 81 reachable instructions, 080D66F0..080D6798.

The preserved complete natural C reads raw bytes or decodes runs from a byte-aligned little-endian halfword header. Header bits 0..13 give the run length; bit 15 selects incrementing values and bit 14 selects a repeated value, with incrementing taking precedence. Literal runs read successive bytes. Completing a compressed run advances the stream by four bytes for generated/repeated data, or by the even-rounded literal length plus two header bytes, and resets the halfword index.

Fresh native matcher exit 1: compiled symbol is 142 bytes, shorter than the indexed 168-byte span. The extent failure stops the native gate before CFG, plausibility, and byte comparison. No exact byte/instruction match count is claimed.

Diagnostic assembly shows the same broad decoding branches, byte truncation for incrementing output, halfword index wrap, and stream advancement. It omits target register-copy sequences around the length and mode masks, keeps mode in r7 instead of ip, and assigns stream/data/length/output to different registers. Target also separately forms data + 2 before literal indexing and separately copies the rounded length; the candidate folds those operations into shorter address calculations. These allocation and expression differences account for the shorter extent; they were not filled with artificial moves or dead code.

Bounded natural forms tested: manual byte assembly with a halfword header and separate index increment/check emitted 140 bytes; a packed header, named halfword masks, explicit raw-data local, and increment-and-check emitted 142 bytes; a fully inlined masked-header helper produced the same 142-byte extent; promoting the packed header to a word and retaining direct masks also emitted the preserved 142-byte candidate. The final diagnostic used the unchanged compiler flags.

The unmatched active source was removed; no native report was generated because all candidates stopped at the extent gate. Temporary preprocessor and assembly diagnostic files were removed. Fixed native verifier boundaries were unchanged.
