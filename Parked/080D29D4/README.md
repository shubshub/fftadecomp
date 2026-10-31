# 080D29D4

Parked unchanged first natural C form. No MATCH credit.

The complete saved target is `[0x080D29D4, 0x080D2AD0)`, 252 bytes and 114 reached instructions. The source preserves the actual `u32(void *)` caller contract, the 0x46-byte metadata stride, packed record fields, two-argument typed slot-zero callback, full-width actual helper contracts, explicit signed-16 conversion, and canonical addressed runtime call. No numeric remainder theorem or callback effects are asserted.

One original native invocation used the fixed published toolkit and `--addressed-signed-runtime-profile addressed-signed-runtime-r2-callback-data-v1`, with `agbcc -mthumb-interwork -O2`. It exited 1 after 0.384049 seconds:

```
ValueError: inert-spin complete body differs from ROM
```

No native MATCH/NOT-MATCH report or plausibility verdict was produced. This is an ordinary complete-body compiler byte mismatch, not an unsupported-selector finding.

The one authorized unchanged-source compiler-only diagnostic used the selected native cpp/agbcc/as/link pipeline. The complete ELF function is exactly 252 bytes. Exactly 247 of 252 bytes equal the target at the same offsets; five bytes differ. The discrepancy is confined to `[0x080D2A80, 0x080D2A88)`:

```
ROM:       movs r1, #255; cmp r0, #0; beq 080D2A88; adds r1, r0, #0
candidate: adds r1, r0, #0; cmp r0, #0; bne 080D2A88; movs r1, #255
```

The retained source selects `field ? field : 0xFF`; no definite semantic layout bug was identified. No second source form, source correction, compiler-flag variation, native retry or proof replay was performed. Compiler byte equality alone would not establish native acceptance.

Original source, exact command/output/error, original object ELF, linked ELF, raw assembly, full target and compiled bytes, fixed-offset differences, source/header composites and input/runtime receipts are preserved under `state/matching-080D29D4-author/` in the handover workspace. The parent owns lease release and publication. The callback remains a conditional returning ARM ABI boundary; destination capacity, physical readability, initialization, memory safety, nonescape and universal termination are not established.
