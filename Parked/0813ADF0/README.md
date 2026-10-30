# 0813ADF0: bounded ordinary native mismatch

Accepted lease: sol-ADF0, request 6529256413. The target is exactly 64 bytes at
[0x0813ADF0, 0x0813AE30), with 28 reached Thumb instructions and 8 literal bytes.
No native MATCH was obtained. All three candidates passed source plausibility
and native linking/CFG admission, then differed in bytes or compiled extent.

The C preserves the observed const byte input, unsigned 32-bit length and CRC
state, unsigned 16-bit loop counter, initial/final complement, low 8-bit table
index and the actual 256-word CRC table. The counter wraps; length >= 65536 has
no terminating guard in the ROM, and no guard was added. No gameplay contract
is inferred.

1. Combined high-part-first XOR expression: 64-byte compiled symbol, ordinary
   byte mismatch. At the same target offsets, 17 bytes agree and 47 differ.
   Native aligned comparison reports 10/28 instructions and 44/64 bytes.
2. Meaningful byte table-index local followed by direct accumulator updates:
   68-byte symbol versus the 64-byte target. Native aligned comparison reports
   12/28 instructions and 46/68 bytes. Its ROM comparison includes 4 bytes of
   the next indexed function; that expansion is not matching evidence.
3. In-place parameter CRC state with explicit complements and table-first
   low 8-bit mask update: 72-byte symbol versus the 64-byte target. Native aligned
   comparison reports 11/30 instructions and 42/72 bytes. Its ROM comparison
   includes 8 bytes of the next function, which are not part of this target.
   The mask introduces an 0xFF register and an IP table base; length is saved
   in R4. At the same original target offsets, 3 bytes agree and 61 differ.

All original sources, pre-run captures of all nine headers, runtime, compiler,
tools, maps and complete body, native commands/logs/run receipts, reports and
exact offset differences are retained in state/matching-0813ADF0-author. This
directory contains the exact final source and native report moved out of active
source/report paths. No compiler-only diagnostic, profile/toolkit change, ABI
invention, successful proof replay or fourth candidate was used. The parent
owns release and any future work.
