# 080E0CC4: one natural callback recovery, not matching

The unchanged first C candidate recovers the witnessed scheduler callback's
state transitions and field/call contracts. One canonical agbcc invocation with
`-mthumb-interwork -O2` exits 1:

```text
compiled symbol is shorter than the indexed span: 438 < 468
```

There was no source revision, flag/type/spelling/register retry, native campaign
or compiler workaround. This is a bounded nonmatch, not an impossibility claim.
Only this README and `080E0CC4.c` are intended for shared Parked integration.
The C SHA-256 is
`9f498d2880aba14f853fa89bda9323e92b475b5efc14cf3f2c4d03ad3d08ee8d`.

## Exact ownership and differences

The approved ROM target owns [080E0CC4,080E0E98): 468 bytes comprising
448 code bytes in 209 instructions, 16 literal bytes and four alignment bytes.
Literal words are E0CF8=00000101, E0DF0=03000940, E0E68=03000940 and
E0E6C=00009FFF. The required source comment contains every target byte.

Both original and linked ELF function symbols own 438 bytes, ending E0E7A,
with 197 reached instructions, 424 code bytes, 12 literal bytes and two internal
alignment bytes. Their .text sections contain 440 bytes; the trailing `c046`
is outside the function symbol and earns no ownership or match credit.
The full target-owned positional comparison has 30 equal bytes, 408 unequal
bytes within the compiler symbol, and 30 absent target-tail bytes. These are
same-position counts, not an instruction-aligned edit-distance score.

The first difference is offset 2 (E0CC6): target byte 47 versus compiler 4F.
The compiler saves r8/r9, whereas the target saves r8; register allocation,
branch positions and literal placement also differ. The target contains 13
discarded RAM byte loads, including its long shadow configuration sequence;
the candidate emits none. The natural byte-field writes do not establish an
original bitfield declaration, so no dead reads, volatile, invented masks or
bitfields were added to force them. These observations do not prove that the
size difference is solely due to the omitted loads.

All 15 original relocations are typed Thumb calls to the eight observed callees;
linking succeeds, and the linked ELF has no remaining relocation or undefined
symbol. Static ordinary-CFG checking accepts the actual emitted 438-byte
function, but canonical mapped-span verification rejects it. No canonical match
report was written, and no src payload is offered.

## Recovered contract and limits

The compatible entry is `u32(void *task, void *descriptor, void *payload)`,
returning zero. A reached local E12B6 registration loads callback word 080E0CC5
at E12D8 and requests a 44-byte payload. This does not certify the enclosing
constructor's defective index or recursively prove scheduler allocation.

Descriptor phase is u16 +0; object is +4 and selector is u16 +14. Payload has
u16 countdown +0, low8 selector +2, signed coordinates +4/+6, object +8, two
six-s16 interpolation records +0C/+18 and child pointers +24/+28. The RAM view
uses only observed byte/u16 access widths; unknown gaps are not recovered
semantic fields or a total global allocation claim.

Phase zero obtains coordinates, narrows y minus 40 and initializes countdown
34. Phase 100 decrements modulo 16 bits, then at zero writes shadow state,
initializes two interpolations for durations 36/28, creates children and reloads
phase before incrementing. Phase 101 updates the first child before testing
the countdown; the second starts only on a call whose pre-decrement count is
already zero. Both completion checks use low8 truth and short-circuit. Phase
102 stores each returned child pointer and processes the second only after the
first is null. Other phases return zero without these effects.

The eight direct dependency contracts and matched interpolation types are
grounded in retained local bodies. Valid storage, initialized outputs,
ABI-conforming returns, allocation success and recursive manager/lifetime
effects remain assumptions. Original nominal types beyond compatible widths
are not uniquely known. No runtime or general semantic-equivalence proof was
performed after the nonmatch.

## Retained local evidence

The complete frozen bundle remains at
`/home/user/.codex-work/ffta-ulw/080E0CC4-author-next`:
`HANDOFF.md`, `ABI.md`, `freeze.json`, `canonical.log`, `elf-capture.json`,
`verification.json`, `DISASSEMBLY.md`, `metadata.patch` and `SHA256SUMS`.
Raw original/linked ELF bytes are preserved as text hex in the capture; the
verification file records complete sections/symbols/relocations and every
target-owned positional difference. No standalone binary or ROM copy remains.
The local evidence files are supplemental and are not required members of this
two-file Parked payload.

The separate target-only metadata proposal corrects count 234 to 209 and
legacy symbol length 000016 to 0001D4, keeping the approved 468-byte ROM extent.
It must never be changed to the candidate's 438 bytes to manufacture a match.
The coordinator owns metadata integration, claims and publication.
