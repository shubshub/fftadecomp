# 08004D68 — bounded compiler mismatch

Target: 08004D68..08004E0E, 166 bytes including literal pools, 63 reachable instructions.

The retained natural candidate recovers the input masks, four control words,
unchanged-input counter, previous-input byte, and alternating control bit.
The fixed native matcher exits 1 before byte comparison or plausibility:

```text
function  0x08004D68   166 bytes (Thumb)
source    src/08004D68.c
compiler  $HOME/agbcc/gcc/agbcc -mthumb-interwork -O2
compiled symbol is shorter than the indexed span: 162 < 166
```

The target begins with a halfword read from 04000134 followed by explicit
byte truncation (`ldrh r0, [r4]; lsl r0, r0, #24; lsr r3, r0, #24`).
The retained source uses a genuine named halfword register and a byte input;
agbcc reduces this to `ldrb r3, [r4]`, removing exactly four bytes.
The remaining emitted instructions and literal sequence follow the target.
No full native byte-equality result is claimed.

Three bounded natural formulations were checked. A control local produced
154 bytes, an explicit port pointer with a wider control local produced
150 bytes, and direct writes in each branch produced the retained 162 bytes.
No volatile qualifier, inline assembly, pragma, compiler flag change, fake
binding, or redundant operation was introduced to force the missing read.
This is an ordinary source/code-generation mismatch, not an unsupported
matcher profile diagnosis. No match report was generated.
