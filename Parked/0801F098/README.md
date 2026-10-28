# 0801F098 — indexed-copy count lifetime difference

The complete target is 0x0801F098..0x0801F122: 138 bytes and 67 reachable instructions, including the 0x02007CB0 base literal. The preserved natural C compiles to the complete 138-byte symbol under fixed agbcc `-mthumb-interwork -O2`. The final native invocation passed extent and source-plausibility checks, then returned NOT MATCHING, exit 1. Its aligned diff score was 65/67 instructions and 134/138 bytes; that score is not same-offset byte equality.

The remaining difference is confined to the indexed branch's initial count handling:

```text
target:    ldrb r0, [r2]
           adds r2, #1
           movs r4, #0
           cmp r4, r0
           bge finish
           adds r1, r0, #0

compiled:  ldrb r0, [r2]
           adds r2, #1
           adds r1, r0, #0
           movs r4, #0
           cmp r4, r1
           bge finish
```

The copy loop itself, raw little-endian halfword branch, destination-base calculation, terminator check, literal pool, prologue and epilogue match. Both signed loop indices preserve the observed 16-bit increment/sign-extension behavior.

Natural attempts covered direct indexed reads, explicit consume-before-store stream reads, a named destination base, and separate signed byte-count versus unsigned halfword-count declarations. The genuine byte-reader helper fully inlines and only the target is emitted. No artificial scheduling, volatile accesses, asm, forced inline or compiler-profile changes were used.

The unmatched active source/report were removed. This candidate earns no match credit.
