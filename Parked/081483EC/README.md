# 0x081483EC: native span refusal

Target extent: [0x081483EC, 0x0814846C), 128 bytes, including the numeric pool and alignment. The exact ROM body and current input pins are retained in the candidate and author receipts.

One natural form was attempted: four u16 inputs, extraction of the three packed five-bit channels, their u32 average divided by constant 3, followed by the same unsigned channel scaling, logical shifts, 0xFFE0 overflow tests and packed u16 return as existing matched 08148384.

The first native command exited 1 during compilation/binding:

```
division caller requires an exact nonoverlapping mapped Thumb span
```

The native tool emitted no report, compiled byte stream, byte comparison or instruction difference. The precise compiled extent and remaining byte differences are therefore unestablished. Static candidate evidence had established the indexed 128-byte ROM partition and the audited unsigned-divider identity; that did not establish this source form's native acceptance.

The task requires stopping on an exact native-model refusal. No second form, alternate profile, synthetic helper declaration, shared-input change or successful-proof replay was attempted. The exact attempted source is preserved here, outside active src, together with the actual native error log. The pre-native source/raw and composite hashes, all nine headers, machine/runtime/compiler/tools, all three maps and complete target bytes were persisted before the command in state/matching-081483EC-author/pre-native-inputs.json. Parent owns reservation release and any later decision.
