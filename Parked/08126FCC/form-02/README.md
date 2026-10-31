# 08126FCC: observed layout corrected, native mismatch retained

This is the separately authorized correction of the definite member-layout
bug in form 01. The original source, README, error, diagnostic and final
receipt remain unchanged in the parent directory and private form-01 packet.

The saved target is [0x08126FCC,0x08127124), 344 bytes and 148 reached
instructions. It writes signed list-count byte +0x0E and reverse byte +0x0F,
reads them separately, and reads their overlapping halfword at +0x0E.

The original candidate embedded a small union after the pointer/byte prefix;
selected agbcc actually placed that union at +0x10. The corrected source
uses a union of two whole-payload structs with the same genuine pointer
fields at +0, +4 and +8 and byte members at +0x0C and +0x0D. One view then
has the signed list-count byte and reverse byte; the other has the reached
halfword. No attribute, packing directive, unknown padding or invented
object bound was introduced. The authorized unchanged-source diagnostic
confirms actual stores and byte loads at +0x0E/+0x0F and the halfword load
at +0x0E. Signed byte loads also use the corrected +0x0E offset.

Only the type layout and member paths changed. Normalizing those paths
makes the entire function body identical to form 01. Loops, operation order,
conditions, conversions, helper prototypes, callback ABI and settings calls
were not changed.

The one fresh native command used the unchanged fixed toolchain and
`--function-address-profile canonical-thunks-v1`. It exited 1:

```
compile failed:
inert spins require an exact unique nonoverlapping Thumb span
```

It generated no match report or plausibility verdict. The one authorized
unchanged corrected-source compiler-only diagnostic again measured one
complete 320-byte FUNC, versus the indexed 344-byte target. This is an
ordinary 24-byte emitted-extent mismatch, not a selector impossibility.
The emitted body SHA-256 is
`19bcb3a5f365f1766fa2f59ff5867780c072ea02b631b54b6434dc3429072a03`.

The first fixed-offset difference remains the branch at 0x08126FDC:
candidate `beq 0x081270AA`, target `beq 0x081270B8`. Across the maximum
344-byte extent, 308 offsets differ, including 24 missing tail bytes.
Case-block order, loop condition, shared versus duplicated settings call,
conversion instruction sequence and literal placement still differ. The
target's explicit sign extension before a later byte store remains absent
from emitted code; no new conversion/type form was attempted to force it.
No source semantic/equivalence conclusion is inferred from that instruction
sequence difference alone.

Counts for this correction: one layout-only source revision, one fresh
native attempt, one unchanged-source compiler-only diagnostic, zero native
retries and zero MATCH credit. Both versions together have two source forms,
two original native attempts and two separately authorized diagnostics.
All 135 fixed input pins remain unchanged. No shared input or PRIMARY edit,
manual ROM read, broker, Git or publication operation occurred.

Private final supplemental receipt:
`state/matching-08126FCC-author/layout-correction-final-receipt.json`.
