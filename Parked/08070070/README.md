# 08070070 — Parked

Complete target: 0x08070070..0x08070120, 176 bytes and 88 reachable instructions.

`08070070.c` is the complete best tested natural C implementation of the rectangular halfword copy. It preserves the byte-sized coordinates and dimensions, halfword loop counters and row-offset truncation, source row stride, destination row stride, and destination origin fields.

A fresh default native matcher invocation with agbcc `-mthumb-interwork -O2` returned exit 1: source plausible, full compiled extent 176 bytes, 76/88 instructions and 157/176 bytes identical. The retained candidate caches its two strides before the initial height test; the target loads and saves them after that test. The remaining row-offset differences are register operand choices and local stack-slot allocation. The inner halfword-copy loop otherwise matches.

Bounded natural attempts included direct nested loops with field accesses, a guarded row loop with cached strides, conventional loops with cached strides, and eight-bit dimension-field types. Direct field-access versions compiled to 168 bytes. The guarded version compiled to 180 bytes and hoisted an additional origin field. The retained conventional cached-stride version reaches the exact extent with the best observed byte comparison. No assembly, volatile access, compiler-flag changes, or shared metadata edits were used.

Raw native comparison evidence remains outside the matching root as `native-not-matching.md` and `native-result.txt` in the private address scratch directory. Unmatched active source and report have been removed. No exact-match credit is claimed.
