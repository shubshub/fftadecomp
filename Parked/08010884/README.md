# 08010884 — remaining entry-instruction order difference

The complete indexed target is 0x08010884..0x0801093A: 182 bytes and 78 reachable instructions. The preserved natural C compiled to a complete 182-byte symbol with the fixed agbcc `-mthumb-interwork -O2` profile. Native extent verification and source plausibility passed; the native verdict was NOT MATCHING, exit 1.

Only the order of the two independent instructions immediately after `push {lr}` differs:

```text
target:    lsls r1, r1, #0x18
           adds r2, r0, #0
compiled:  adds r2, r0, #0
           lsls r1, r1, #0x18
```

The rest of the instructions, branches, literal pools and complete extent match. The native aligned diff score was 77/78 instructions and 180/182 bytes; this score is not same-offset byte equality.

The initial logical-expression visibility predicate and early list-head initialization compiled to 172 bytes. Separate early returns in the genuine, fully inlined visibility predicate plus list-head initialization immediately before selection produced the preserved 182-byte candidate. A word-sized input with an explicit low-byte conversion produced the same entry-order difference; the preserved interface uses the original byte-sized flag. No scheduling devices, extra compiler flags or forced inlining were introduced.

The unmatched active source/report were removed. This candidate earns no match credit.
