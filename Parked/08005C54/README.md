# 08005C54 — natural conversion recovery, not matching

## Verdict and complete extent

This is an honest nonmatching recovery, not an active match or an assertion
that the function is inherently unmatchable. The frozen 4847c93 matcher rejects
the retained candidate before comparison: `compiled symbol is shorter than the
indexed span: 494 < 550`. No active source or match report is retained.

The complete ROM function is `[0x08005C54,0x08005E7A)`: 550 bytes and 272
reachable CFG instructions, comprising 546 code bytes and the four-byte literal
at 0x08005D70 containing 0x0836D490. There is no internal alignment or switch
table. The zero halfword at 0x08005E7A is external and excluded.

The candidate has exactly one emitted function of 494 bytes and 244
instructions. Its `.text` is 496 bytes; the final `C046` halfword is outside
the function symbol and is not counted. Its 490 code bytes and four-byte
literal are both included. The literal occurs at 0x08005D58 and the typed
call to 0x08000ADC at 0x08005E16. No relocations remain after typed linking.
The independent diagnostic CFG and separate source plausibility check pass;
these do not override the official complete-span rejection.

SHA256:

- ROM body: `31a747d5b87d24da832d609ee4acd5f0d9f816e347b6d0b4e5e50f446e7b21ab`
- Linked candidate: `eaee774b485688f66088140c4c5606596c3f084390a9a7eb2e4afe1af45b2abf`
- Retained C: `3e79a8741f9f648e59437d73a9f83e289013524d462657978a4e9accf8f2c3e5`

Only 28 of the 550 target byte positions and five of the 272 target
instruction positions coincide. The candidate is 56 bytes and 28 instructions
shorter. It has different register allocation, no four-byte scalar frame,
different guard/load scheduling and extra progress reloads, with correspondingly
different branch, literal and call positions. This is not merely a relocation
problem or a candidate-prefix match. The target keeps the destination in a
four-byte stack local; the candidate keeps it in a saved register.

## Bounded natural forms

Both forms use one ordinary switch and typed state/progress/queue-record views.
No compiler flags were varied and no forced registers, storage, alignment,
inline functions, assembly, volatile accesses, pragmas or dummy work were used.

1. Direct bytewise descriptor expressions and repeated nibble source-index
   expressions compiled to 496 bytes and 245 instructions.
2. The retained form makes the unsigned descriptor-length representation
   explicit and computes the nibble source index once before selecting its
   high or low nibble. It compiles to 494 bytes and 244 instructions.

The second form expresses the observed unsigned comparisons and shared source
byte selection naturally. Further instruction-spelling searches were not
attempted. The first form was superseded rather than retained as another
candidate artifact.

## Interface, layouts and ordered effects

The compatible interface is `u32 func_08005C54(void *object, const void *input)`.
Only the full incoming r0/r1 are consumed; there are no incoming stack
arguments. The full result is normalized to zero or one. The original nominal
return type and original struct names are not uniquely established.

`ConversionState` is an observed local view, not an original allocation claim:
capacity is a halfword at +0x04, output pointer at +0x08, progress halfword at
+0x0C, output offset word at +0x10, cursor word at +0x14 and embedded queued
record at +0x18. Its target size is 0x34 and alignment four. The grouped
`ConversionProgress` subobject is 12 bytes. `TransferRecord` uses the same tag,
member names, order and types as the recovered 08000ADC definition; it is
0x1C bytes with source/destination/control words at +4/+8/+0x0C and next pointer
at +0x18. Sixteen target-compiler assertions check these sizes and offsets.

The input descriptor is read bytewise, with no invented aligned-word load.
The destination LE32 at bytes 4..7 plus the entry output offset is cached
before the source LE32 at bytes 0..3 is assembled. Bytes 8/9 form the live
unsigned input length. Byte 0x0A's high nibble selects:

- 0x00: copy input bytes, incrementing the u16 produced and input-progress
  counters after each output store.
- 0x10: clear an output byte, then write its first nibble from the next
  MSB-first input bit; consume another bit and conditionally OR the second
  nibble. The first-bit false path still performs its second zero store.
- 0x20: select the low or high input nibble according to cursor parity and
  combine it with descriptor byte 0x0B shifted left four.

Packed-mode cursor increments are full unsigned words. Progress receives the
low16 of cursor shifted right three or one, respectively. Produced is u16.
The mask-table constant refers only to the eight actually indexed bytes at
0x0836D490; no original table allocation size is asserted.

Every mode, including unknown modes and initially empty work, calls the real
queue helper once. Its canonical declaration is
`void func_08000ADC(struct TransferRecord *, const void *, void *, u16)`.
Arguments are the embedded record, freshly loaded output pointer, cached
entry destination, and `produced >> 2`, truncating rather than rounding.
The output-offset word is reloaded after the call before adding produced
modulo 2^32. The final length and progress are read again for the result.

ADC writes the queued descriptor and appends it to the chain at 0x03002BCC.
It retains the record/source/destination addresses; it does not perform a
copy or otherwise read the source/destination buffers. Its complete actual
68-byte/31-instruction body is executed in the checks, not replaced with a
model or stub.

## Behavior evidence and read-order limitation

The self-cleaning reproducer is
`/home/user/.codex-work/ffta-ulw/08005C54-author/check.py`. Run with:

```sh
env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp \
  PATH=/home/user/armtc/root/usr/bin:$PATH \
  python3 /home/user/.codex-work/ffta-ulw/08005C54-author/check.py
```

It recompiles the retained C in a disk-backed isolated root with all current
headers/maps and the original ROM symlink, reproduces the official rejection,
then links the whole candidate with the canonical ADC target. It also checks
source plausibility, complete CFGs, relocation closure and target layouts.
Temporary object/ELF/ROM-link artifacts are removed automatically.

The author suite executes 101 target/candidate pairs, 202 executions, with the
actual ROM mask bytes and actual ADC body, without helper stubs. An independent
ordered-operation oracle checks the result, call arguments, ordered writes,
entire EWRAM, non-stack IWRAM, callee-saved registers, restored SP and return
control. It also checks every target nonliteral read/write against the oracle.
There are 94 ordinary synthetic-memory fixtures and seven explicitly
machine-only overlap diagnostics. The latter include a queue next field that
overlaps the live output offset, distinguishing post-call reload from reuse of
the cached entry offset.

Cases cover all 16 mode high nibbles, low-nibble irrelevance, zero/partial/full
work, produced counts below and across the four-byte queue truncation boundary,
all eight bit positions, both nibble parities, true/false bit branches,
zero/nonzero output nibbles, unsigned output-offset wrap, progress narrowing
across 0xFFFF, unaligned input descriptors and empty/one/multiple-node queues.

Coverage is 268/272 target and 240/244 candidate instructions, plus all31
ADC instructions on both sides. The four unexecuted instructions on each side
are the switch's less-than-0x10/nonzero default arm, which is unreachable for
the actual `byte & 0xF0` selector. Maximum stack depth is 48 bytes for the target
and 44 for the candidate, including ADC.

**Read traces are not identical.** All101 pairs differ both with and without
literal reads. For example, at a guard the ROM reads input length bytes before
the progress halfword, while the candidate reads progress first. The candidate
also reloads progress in loop guards where the ROM uses its just-computed
narrowed value. Ordered writes, results, calls and final memory agree in the
tested fixtures; this is not an exact ordered-read recovery, byte match or
all-input equivalence proof.

Ordinary C use requires suitable aligned state/queue objects, readable input
and source storage, writable output storage for the actual accesses, valid
target pointer representations and a finite append queue. The explicit
byte-to-address conversions rely on the target ABI. The tests do not establish
original allocation sizes, arbitrary aliasing or object lifetimes, queue
consumer behavior, hardware transfer semantics, cycle termination, or safe
reuse of an already queued record. Overlap diagnostics do not expand that C
domain. Entry evidence is indexed/structural; no incoming-reference provenance
was proved for 08005C54.
