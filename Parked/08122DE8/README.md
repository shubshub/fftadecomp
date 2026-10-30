# 08122DE8: unmatched encoded-byte branch

The complete owned Thumb target is `[0x08122DE8,0x08122E1C)`, 52 bytes:

```
00 b5 03 1c 4a 78 01 20 08 56 00 28 07 da 80 32
12 06 12 0e 18 1c 01 21 03 f0 ec fa 04 e0 4a 78
18 1c 02 21 03 f0 e6 fa 01 48 02 bc 08 47 00 00
15 01 00 00
```

It reads record byte 1 unsigned, tests a signed interpretation of that byte,
and calls 0x081263DC. The negative arm adds 0x80, narrows to u8, and passes
mode 1. The nonnegative arm reloads byte 1 and passes mode 2. It returns
0x115. No field meaning beyond these observed operations is recovered.

No defining C or existing declaration for 0x081263DC was present. Its complete
48-byte ROM definition was inspected and retained in each attempt receipt.
It explicitly narrows r1 and r2 to bytes, writes through r0 at +6, and loads
object+8. Its `pop {r0}; bx r0` epilogue overwrites the return register with
the saved return address. The local declaration therefore uses an opaque
object pointer, two u8 arguments, and void result. Direct-call semantics
would remain conditional on the ordinary ABI summary; no native match or
callee-behavior proof is claimed.

Three natural source forms were run once each with the canonical command:

```
python3 /home/user/Desktop/FFTA-handover-2026-10-30/repos/fftadecomp-kit/tools/match.py --root . 0x08122DE8
```

1. An s8 record field, copied to a u8 temporary before the signed test.
2. A u8 record field, copied to a u8 temporary and tested through an s8 cast.
3. An encoded-byte union with signed and unsigned views, otherwise retaining
   the same operations. This final candidate is preserved alongside this file.

Every native process exited 1 with the exact captured diagnostic:

```
compiled symbol is shorter than the indexed span: 48 < 52
```

A single diagnostic compilation of failed candidate 2 used the native
compile helper and unchanged default flags. Its retained assembly shows the
unsigned and signed initial byte loads, both helper calls, narrowing, and
constant return. It reuses the initial unsigned byte in the nonnegative arm,
omitting the target's `ldrb r2, [r1, #1]` at 0x08122E06. That removes two code
bytes and the two alignment bytes preceding the final literal. Its raw
relocatable text contains unresolved BL relocations, so it is not presented
as a linked ROM-byte comparison. No diagnostic recompilation of candidate 3
was performed; its established native difference is the same 48-versus-52
complete-symbol extent.

The short-symbol gate emitted no reports and no source-plausibility verdicts.
No volatile accesses, explicit discarded reads, assembly, pragmas, altered
profiles, shared headers, mappings, or toolkit changes were introduced.
No byte-exact match is claimed. The unsuccessful active source was moved to
this directory; no report exists under docs/match/ for this address.

All three candidate sources, native outputs, source-bound current-machine
receipts, the helper ROM evidence, and the bounded candidate-2 diagnostic are
retained under the handover workspace's `state/matching-08122DE8-author/`.
