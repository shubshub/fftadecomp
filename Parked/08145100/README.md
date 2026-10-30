# 08145100: bounded ordinary mismatch

The genuine 28-byte Thumb function checks the MusicPlayer signature at offset
0x34 and, when equal to 0x68736D53, clears bit 31 of the word at offset 4.
The local layout follows existing defining sources 08145990 and 081461FC.
There are no calls or evidenced return-value contract in this body.

Two natural void-function forms were checked using the native default profile:
a positive equality guard and an early return on inequality. Both were plausible
and compiled to the same 32-byte complete ELF symbol, rather than the indexed
28-byte body. Each native invocation exited 1 with NOT MATCHING - bytes differ.
The compiler added push {lr}, selected r1 for the signature comparison instead
of r3, and returned through pop {r0}; bx r0 instead of bx lr. The associated
PC-relative offsets and branch target differ. Both literal values and the
status load, AND and store operations agree.

Exact target (28 bytes):
021c536b0348834203d150680249084050607047536d7368ffffff7f

Exact compiled body from both attempts (32 bytes):
00b5021c516b0448814203d1506803490840506001bc0047536d7368ffffff7f

The native report compares 32 ROM bytes because the compiled symbol is 32 bytes;
its final four ROM bytes, 021c0904, belong to the next indexed function at
0814511C. They are not part of this 28-byte target. No complete match is claimed.
No native-model refusal occurred. No fabricated return contract, additional
formal parameter, assembly, pragma, volatile operation or compiler steering was
introduced. Two bounded natural forms exhausted the justified source alternatives
for this lane; no third spelling-only or register-steering attempt was run.

The exact attempted forms, pre-run source/header/runtime/tool/map pins, native
commands, exit receipts, outputs and reports are retained under the handover
state/matching-08145100-author directory. Reservation release is owned by the
parent coordinator.
