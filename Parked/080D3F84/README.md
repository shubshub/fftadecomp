# 080D3F84 — unresolved control-field type

Target: `[0x080D3F84, 0x080D3FC8)`, 68 bytes, 31 reachable instructions.
The retained complete C candidate emits 60 bytes under fixed agbcc
`-mthumb-interwork -O2`. The final native invocation exited 1 with:

```
compiled symbol is shorter than the indexed span: 60 < 68
```

The extent gate stopped before byte comparison and native plausibility checks.
No native plausibility or exact-match credit is claimed.

The incoming task pointer is passed unchanged to 0x08005BFC, whose established
implementation returns the task payload at offset 0x18. Each byte argument
updates payload field 6 or 7 unless it is the 0xFF sentinel. The function then
writes `(payload[5] << 6) | payload[6]` to the control byte at offset 0x4A of
0x03000940, and payload byte 7 to its next byte. The function returns void.

The target reads the old destination byte before each full-byte store:
0x080D3FB0 reads offset 0x4A and 0x080D3FBA reads offset 0x4B. Their read
values are unused. Around the first read, the target also preserves the
address through ip and r4. The current candidate omits those two reads and
two address-preservation moves, yielding four fewer instructions and eight
fewer bytes. The retained byte-based bitfields are an attempted type model,
not a confirmed reconstruction of the original declaration.

Natural unsigned halfword-, word-, and byte-based eight-bit fields were
tested; a packed word-based layout was also tested. All emitted 60 bytes
and removed the old-byte reads. No volatile qualifier, artificial discarded
expression, assembly, extra helper, compiler-option change, or dead code was
introduced to reproduce them. Further progress requires evidence for a
legitimate declaration or access form that explains the retained reads.
This is an unresolved type-recovery boundary, not proof of unmatchability.

The full target, retained heuristic observation, and final native output
remain in the captured inventory and sibling address scratch directory.
The last matcher output is `match-current.log`. The unmatched active source
and report were removed. No shared metadata, headers, toolkit, main-game
files, or other addresses were changed.
