# 080D4020: unmatched two-field clear

The observed complete Thumb body is `[0x080D4020,0x080D4038)`, 24 bytes:

```
04 48 02 1c 4a 32 11 78 00 21 11 70 4b 30 02 78 01 70 70 47 40 09 00 03
```

The ROM loads the mapped base `g_control_flags_03000940`, reads a byte at
+0x4A, stores zero there, reads a byte at +0x4B, and stores zero there.
The two loaded byte values are overwritten or unused before return. Existing
same-symbol sources establish the mapped block but do not recover these two
fields' original declaration. No original bitfield type is claimed.

Two native candidates tested the hypothesis that ordinary assignments to
byte-wide bitfields explain the read-before-clear pattern. Both preserve the
observed field offsets and perform only the two clear operations:

1. Two `u8` bitfields, each width 8, after an unknown 0x4A-byte prefix.
2. Two `u32` bitfields, each width 8, after the same unknown prefix. This
   standard unsigned-integer bitfield candidate is preserved alongside this
   README.

Each was invoked once with the native defaults:

```
python3 /home/user/Desktop/FFTA-handover-2026-10-30/repos/fftadecomp-kit/tools/match.py --root . 0x080D4020
```

Both processes exited 1 with the captured exact diagnostic:

```
compiled symbol is shorter than the indexed span: 20 < 24
```

The exact established difference is the complete ELF extent: each emitted
symbol is four bytes shorter than the owned ROM span. The gate stops before
printing the emitted byte sequence or issuing a report; no positional byte
comparison, source-plausibility verdict or complete-function match is claimed.
No independent disassembly or equivalence campaign was added.

No explicit discarded reads, volatile accesses, inline assembly, pragmas,
profile changes, shared-header changes, invented addresses or compiler-steering
constructs were introduced. No further type or syntax search was attempted.
The unsuccessful candidate is absent from the active source tree.

Both candidate sources, native outputs and current-machine source-bound
receipts are retained under the handover workspace's
`state/matching-080D4020-author/`. No native match report was emitted.
