# 0800FA0C: bounded unmatched attempt

Target span: [0800FA0C,0800FAA8), 156 bytes, 68 instructions. Accepted lease sol-FA0C, claim 6524556666. Three native matcher attempts all exited 1. No MATCH or native plausibility result is claimed, and the matcher emitted no report.

The recovered operation allocates 0x298 bytes using callback 0800F93C and the named window destination, initializes coordinates/type/radius, obtains the state again, fills its ranges, renders them and returns the task. Source/type evidence is retained in state/resumed-matching-batch29-20261030/candidate-named.json.

Forms tried:

1. Signed coordinate fields and the inline render helper used by matched 0801010C. Native refusal: function-address caller differs from the ROM. The complete linked candidate is 156 bytes; exactly nine bytes differ, all register selections in nine instructions.
2. Direct rendering statements reusing the state variable. Native refusal: function-address caller requires an exact mapped Thumb span. Linked function size is 152 bytes, versus the target 156.
3. Unsigned coordinate storage with explicit signed coordinate conversion in the same inline helper. Native refusal: function-address caller differs from the ROM. Its complete linked bytes equal attempt 1. The exact third source is preserved here.

Remaining differences, compiled versus target:

- 0800FA52: movs r1,#0xA2 versus movs r3,#0xA2.
- 0800FA54: lsls r1,r1,#2 versus lsls r3,r3,#2.
- 0800FA56: adds r0,r0,r1 versus adds r0,r0,r3.
- 0800FA58: mov r2,r8 versus mov r1,r8.
- 0800FA5A: strh r2,[r0] versus strh r1,[r0].
- 0800FA74: movs r3,#0 versus movs r2,#0.
- 0800FA76: ldrsh r0,[r4,r3] versus ldrsh r0,[r4,r2].
- 0800FA78: movs r2,#2 versus movs r3,#2.
- 0800FA7A: ldrsh r1,[r4,r2] versus ldrsh r1,[r4,r3].

Every call relocation and both referenced literals agree in the 156-byte forms. Native refusal remains authoritative. No gate, tool, shared header or mapping was edited. The canonical-thunks profile was not selected because this target contains no indirect thunk call. No successful proof was replayed.

Exact sources, logs, retained assembly, diagnostic linked bytes/differences, run records and current-machine receipt: state/matching-0800FA0C-author/. Diagnostic typed linking did not admit a match. Each failed source also received one diagnostic C compilation to expose its assembly. The first retained-assembly diagnostic had one input-type API error before linking; that error and correction are recorded separately. No report was fabricated.
