# 0814274C

Target: complete [0x0814274C, 0x0814274E), 2 bytes, one reachable
instruction: mov pc, lr (f746).

One canonical empty void C body was tested with fixed agbcc
-mthumb-interwork -O2. Native matcher exited 1. The complete compiled symbol
is 2 bytes and passes the closed leaf CFG gate, but emits bx lr (7047):
0/2 bytes and 0/1 instructions identical. The empty-body finding is not
eligible for the canonical exact-bx-lr exception, so the source is also
IMPLAUSIBLE; no plausibility or match credit is claimed.

The supplied return-only body does not establish argument or return-value
types. This candidate tests only the no-op interpretation and is not a verified
signature reconstruction. The fixed interworking return encoding differs from
the target's same-mode return. No alternate flags, inline assembly, artificial
control flow, or return-type workaround was attempted.

Native report retained in address scratch as last-native-report.md.
Active unmatched source/report removed.
