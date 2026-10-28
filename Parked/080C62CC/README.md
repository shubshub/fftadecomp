# 080C62CC — remaining control-field load mismatch

Target: complete Thumb span 0x080C62CC..0x080C6480, 436 bytes and
199 reachable instructions. This candidate initializes the 0xB4-byte state,
copies the input words, builds the mode-dependent history, copies a palette,
requests animation 1, and saves and updates the display-control fields.

The fixed agbcc `-mthumb-interwork -O2` native matcher exits 1 at the complete
ELF extent check: `compiled symbol is shorter than the indexed span: 432 < 436`.
The final restored candidate was tested with the ordinary native command;
it contains no canonical callback aliases. Byte comparison and native
plausibility were not reached, so neither gate is claimed to pass.

Fixed-compiler assembly inspection isolates the remaining difference to the
final byte-field update at display-control offset 0x4A. The ROM reads the byte,
clears bit 4, reads that byte again, then stores the masked value. The candidate
omits the second read; its shorter instruction stream also changes trailing
alignment and literal placement. The earlier state-history, word-copy,
callback and animation sequences were recovered with ordinary C and genuine
helpers that the fixed compiler naturally inlines.

Bounded attempts covered a single-bit field, unsigned byte-width bitfields
with byte and word base types, and a packed register-union view. These did not
recover the extra read. No discarded-value expression, artificial volatile,
assembly, compiler-flag change or forced-inline attribute was added.

Only this C file and README are retained in Parked. Native diagnostic output
remains in the private address scratch directory; unmatched active source and
report are removed. No match credit is claimed.
