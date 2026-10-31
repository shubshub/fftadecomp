# 080182CC unmatched after authorized identifier build fix

The complete target is 368 bytes at [0x080182CC, 0x0801843C), with 139 reached instructions. Accepted claim 6537804797 belongs to sol-82CC; parent owns release and integration.

Two source forms and two original default native executions occurred. Form 1 exited 1 during compilation because the local Record typedef collided with include/ffta.h:168. Parent then authorized only the two identifier-token replacements Record -> Record080182CC. Layout, fields, prototypes, operations, ordering and control flow remained identical. The inverse replacement recovers the exact original source. This was a build-error correction, not a semantic or byte-shape iteration.

Form 2 exited 1 after 0.270109 seconds with:

```
compile failed:
switch caller differs from the ROM
```

No native report or full emitted body was retained by that failure. Exactly one authorized unchanged-form-2 compiler-only diagnostic then used the actual default host cpp, agbcc -mthumb-interwork -O2, assembler and typed linking mechanism. All nine diagnostic commands exited 0. The linked ELF function symbol and complete .text are each 368 bytes, matching the target extent. There are 357 equal byte positions and 11 differing byte positions. All differences are within 0x0801834C..0x0801836B: the target loads the state base into r0 and its record pointer into r2; the candidate keeps the state base in r6 and loads the record pointer into r0, with corresponding register differences in the packed-ID and fallback setup. The surrounding bytes, switch table, direct-call encodings, literal values, remainder of the body and final return bytes compare equal positionally. This finite comparison is not a C semantic-equivalence theorem or native acceptance.

No third source form, second compiler diagnostic, proof/API replay, native retry, register-steering correction or source claim of impossibility was made. There are zero MATCH results.

Current parked source raw SHA-256: d86c7e0b7fd966850ee75aa15e887d61117f5617bce7301df610a28abae58f2c
Source plus all nine headers SHA-256: 38760a555a6366cc37c999e040b96691a9289416ed5b1904dfdfe165f33911a2
Complete diagnostic linked-body SHA-256: e374c5bc9aa7d21e15e60bf99f9a4f55e05119c24a6f1dffa4f3bad81688d68d

Original form-1 source remains immutable at state/matching-080182CC-author/attempt1-source.c, its original parked README at attempt1-parked-README.md, and its original final-unmatched.json receipt and compiler error logs are unchanged. The final form-2 source remains separately frozen at attempt2-source.c. Exact identifier delta, both native commands/exits/stdout/stderr, all compiler-only diagnostic commands/ELF/body/disassembly/differences, and the superseding final-form2-unmatched.json receipt are preserved in that same owned state directory. No native report was generated for either form. The original final-unmatched.json describes the earlier form-1 parking checkpoint; this README and final-form2-unmatched.json supersede its active parked-pair status without rewriting it.

Both actual current map sets are JSON426649b8/text8cf6d4a4/data84f2215c. All 115 tool sources, nine headers, six native binaries, two libraries and six maps were freshly captured and unchanged across the corrected run and diagnostic. Runtime captures are current-machine evidence. No ROM read, helper read, shared map/header/tool edit or successful replay occurred. Only the owned failed active source was removed; no active native report existed.
