# 0809FD88

Parked after one actual native check with agbcc `-mthumb-interwork -O2`.
The native command exited 1 with this exact refusal:

```
signed quotient requires a CFG-proven positive signed32 constant in r1
```

No native byte verdict, source-plausibility verdict, or match report was
produced. `native-failure.log` preserves the complete native output.

The recovered source uses the two signed halfwords at offsets 0 and 2 of
each point. It calculates absolute x/y differences, selects their maximum,
and divides by the third signed argument using ordinary C division. The
nearby 0809FBF4 source independently uses this signed-halfword point layout.
The target calls the canonical signed quotient runtime at 081426B8, forwarding
its incoming third argument from r2 to divisor r1.

The default native signed-quotient profile accepts only CFG-proven positive
signed32 constant divisors. The dynamic incoming divisor supplies no such
fact. No source-only change can supply that fact while preserving the
observed input contract. No positive/nonzero assumption, addressed runtime
alias, replacement arithmetic, assembly, volatile, pragma, dead code,
artificial steering, toolkit change, or unsupported profile was introduced.
No further spelling attempts were run after this decisive admission refusal.

The exact complete 56-byte target/decode and source-bound current-machine
receipt are retained under `state/matching-0809FD88-author/` in the handover
root. The receipt records the single failed native execution and its log hash.
There is no claimed byte-exact match or arithmetic-runtime admission.
