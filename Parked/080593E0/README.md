# 080593E0 — Parked

The retained direct-field candidate is the complete 114-byte symbol tested
with fixed `agbcc -mthumb-interwork -O2`. Native matching returned exit 1,
source plausibility `plausible`, and an aligned comparison of 107/114 bytes
and 41/45 instructions. Same-offset byte equality is 103/114. The indexed
target is `[0x080593E0, 0x08059452)`, 114 bytes and 45 reachable instructions.
No match credit is claimed.

All calls, byte narrowing, conditional mode selection, stack arguments,
literal values, frame operations, and return match. Two record-address
calculations differ in evaluation/association order:

* At `0x0805940C..0x08059412`, the target first forms global-base + 0x2E7D,
  then adds the 16-byte record index. The candidate first adds the record
  index to the global base, then adds 0x2E7D.
* At `0x08059416..0x0805941C`, the target first adds the record index to the
  global base, then adds 0x2E78. The candidate adds 0x2E78 to the global base
  before adding the record index; the literal-load order changes as well.

The recovered routine reads two byte properties through 080CCB08 and
080CCB28, then configures the output region at context +0x1BC0 using the
record byte at +0x2E7D + index*16 and mode 1 for a nonzero word at
+0x2E78 + index*16, otherwise mode 2.

Tested natural forms: direct fields of the global record array (retained),
and a local pointer to that record array. The local-pointer form produced
a 94-byte symbol and failed the indexed-span check before plausibility.
The complete native report for the retained candidate is preserved in the
private address scratch as `native-report.md`. The retained C is unchanged
from its tested direct-field form.
