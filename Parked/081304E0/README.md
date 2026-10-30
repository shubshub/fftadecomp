# 081304E0 native gate refusal

Accepted reservation: sol-04E0, claim6528047788. One natural source form and one default native invocation were attempted. The source preserves the existing caller declaration s32(void*) and defining CD480(u8,u8) pointer-return helper contract.

The native invocation exited1 with the exact diagnostic:

```
compile failed:
switch caller differs from the ROM
```

The guard at tools/match.py:1952 compares the complete linked switch caller with the indexed ROM bytes before switch binding verification. It emitted no compiled-byte listing or offset comparison and created no native Markdown report. The exact differing bytes are therefore unavailable from this retained native output. This is an unmatched source, not a successful proof or a claim that the ROM shape is unsupported.

The source and native failure log are retained here. The full106-byte target, source raw and composite hashes, all9header contents, all3map pins, runtime/compiler/tool pins, exact native command, and run log are frozen in state/matching-081304E0-author/. The first precise gate refusal ends this lane; no retry, profile change, diagnostic compilation, or toolkit edit was performed. Active src/081304E0.c and docs/match/081304E0.md are absent.
