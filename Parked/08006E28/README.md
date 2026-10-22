# 08006E28: natural recovery, not a byte match

The retained insertion caller is plausible and passes the existing official
stack-buffer proof, but eight emitted bytes differ. It remains Parked with
no active source or matching report. Helpers are executed from the actual
ROM; their different Parked C implementations are neither linked nor altered.

## Complete extent and exact discrepancy

- Target: `[08006E28,08006EBE)`, 150 bytes / 73 instructions, all code.
- Target SHA-256: `d7d37063b367add1fa0a31c1c1f7f89482d89a4168b56c001ac521d53dba530b`.
- Candidate: one complete ELF function, also 150 bytes / 73 instructions.
- Candidate body SHA-256: `f12295c204a3a1d951b675c75b29420c8f4d95a6a513422fa03ab0fbe8e56d46`.
- Source SHA-256: `ca33f1b32d0723c752cae76af4601327b58082066cab1ab6db1381f3bb813478`.
- Exactly 142/150 same-position bytes and 65/73 same-address instructions agree.

Both direct Thumb calls bind to the actual indexed 08006C88 and 08006D38
targets. The two relocations in the original object's single relocation
section resolve without remaining relocations, veneers or emitted local
helper functions. Candidate `.text` is 152 bytes; final `c046` is external
section alignment. ROM's `0000` at 08006EBE is also external. Neither is
included in the complete 150-byte function comparison. There are no pools
or internal alignment bytes.

Every differing byte is listed here; all other function bytes agree:

| Byte address | Target | Candidate |
|---|---|---|
| 08006E30 | A8 | A9 |
| 08006E32 | E9 | E8 |
| 08006E34 | 09 | 00 |
| 08006EA6 | 08 | 01 |
| 08006EA9 | 30 | 31 |
| 08006EAA | 20 | 21 |
| 08006EAC | 00 | 09 |
| 08006EAE | 60 | 61 |

The first three substitutions exchange r0/r1 during the low/high size-byte
decode. The remaining five use r1 instead of r0 as the count-update result.
The changed byte at 08006EA9 belongs to the instruction starting at 08006EA8.
Branch positions, call targets, memory-address order and the rest of the
complete instruction sequence agree.

## Official proof and bounded attempts

Frozen toolkit `kit-reviewed-4847c93` reports:
`NOT MATCHING - bytes differ`, 142/150 bytes, plausible source, with profile
`elf-symbol-thumb-frame-buffer-calls-v2`. Its legacy buffer mode rejects a
join in 6C88, but the matcher's existing supported stack-buffer fallback
succeeds. The dependency is the full actual 174-byte 6C88 body, SHA-256
`7753b4551e4d959c458be6fb052231a28bdd00592aa2a47c75f066aeb2de5dd5`.
There is no remaining official proof blocker and no verifier or map change.
The bytes themselves fail. Strict replay rejects both the nonmatch report
and an in-memory forged MATCH verdict with the same differing body.

Three grounded forms used only fixed agbcc `-mthumb-interwork -O2`:

1. Direct byte assignments with nullable offset expressions and two natural
   output-pointer locals emitted 156 bytes / 76 instructions. It reloaded
   escaped output locals between byte stores. The official matcher rejected
   the nonexact mapped extent, even though diagnostic fallback CFG proof passed.
2. Ordinary inline helpers for little-endian field reads/writes and repeated
   nullable pointer-offset conversion emitted 152 bytes / 74 instructions.
   A materialized count-field address added an instruction. The full mapped
   extent check again rejected it; no prefix comparison was accepted.
3. The retained form sequences the little-endian read explicitly and uses
   a normal local count read/modify/write. It emits the exact full size, with
   only the eight register-choice bytes above remaining different.

The repeated write and pointer-offset helpers represent ordinary operations;
their original inline provenance is unknown. No register binding, assembly,
volatile, pragma, forced inline attribute, storage trick, artificial control
flow, flag sweep or acceptance change was used. These attempts do not prove
that every possible natural representation is unmatchable.

## Interface and ordered behavior

Compatible interface: `void func_08006E28(u8 *owner, u8 *block)`.
Only incoming r0/r1 are consumed. There are no incoming stack arguments or
scalar return. The caller saves r4/r5/LR and allocates two pointer locals:
12 saved bytes plus eight local bytes, 20 own bytes total.

1. Read block size from bytes +6 then +7. Call actual 6C88 with owner, this
   unsigned 16-bit size, `&before` at caller SP and `&selected` at SP+4.
2. Encode block as the low 16 bits of its owner-relative word offset. Store
   its low/high bytes in before+10/+11, or owner+0/+1 when before is null.
3. If selected is nonnull, store block's offset in selected+8/+9.
4. Reload before and selected from their local pointer objects after neighbor
   writes. Store their nullable offsets to block+8/+9 and block+10/+11.
5. Read owner count bytes +4/+5, increment modulo 65536, and write low/high.
6. Call actual 6D38(owner) to recompute owner+2/+3, then restore the frame.

Zero encoded links mean null; nonzero links decode to owner plus four times
the unsigned 16-bit offset. The block is already dereferenced before the
later null-to-offset conditional, so that conditional supplies no null-input
safety. Pointer subtraction requires the owner and nodes to lie within the
same valid byte-array storage, rather than merely having convenient numeric
addresses.

Actual 6C88 initializes selected-null then before-null, searches the finite
size-sorted links, and on nonempty completion writes before then selected.
The stack output-pointer objects are live throughout the call and are
distinct from the byte-arena metadata in the tested domain. The supported
proof checks this buffer dependency; ordinary call summaries alone do not
establish every callee's runtime contract.

Actual 6D38 is a separate 102-byte leaf, SHA-256
`ebb75817e6e49a104d4d7562559c89ddc557fad028fc27e7b58bb62aa017566b`.
It follows the count-derived number of next links from the head and writes
the selected owner-relative offset. It is also executed in every runtime
pair below, not replaced by a model. Maximum nested stack depth is 40 bytes
through 6C88; the 6D38 call uses 28 bytes including the caller.

## Fresh finite runtime and ABI evidence

The self-cleaning reproducer is:

```sh
env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp \
  PATH=/home/user/armtc/root/usr/bin:$PATH python3 \
  /home/user/.codex-work/ffta-ulw/08006E28-author/check.py
```

It copies the retained source into an owned isolated build root, preserves
the exact current map bytes, invokes the official matcher, inspects the
complete linked ELF, and runs target and candidate callers with both full
actual ROM helpers. Seven target-compiler assertions check byte/scalar and
pointer sizes, pointer alignment and pointer-difference width. No invented
packed structure or inferred original nominal typedef is required.

Seven pairs / 14 executions pass:

| Case | Existing sizes | Search start | Inserted size |
|---|---|---:|---:|
| Empty | none | null | 0 |
| Head, backward search | 8,20,40 | last | 1 |
| Interior, forward search | 5,10,15,30,50 | first | 22 |
| Tail, forward search | 2,4,8 | first | 99 |
| Equal-size backward search | 7,7,7,16 | third | 7 |
| Wide fields | 0,0100,8000,FFFF | last | 0101 |
| Count-byte carry | 255 nodes sized 0,4,...,1016 | index127 | 510 |

Fixtures include byte-unaligned owner bases, nonzero high offset bytes and
the count transition 255 to 256. Every fixture has consistent finite sorted
links, representable owner-relative offsets, live byte-arena backing and a
new block disjoint from the existing nodes and local pointer objects.

A separately computed sorted-list insertion position checks helper outputs.
An independent byte-operation oracle checks every ordered read/write,
including the actual helper's repeated size reads, local-output stores,
neighbor updates, count accesses, second-helper traversal and complete stack
save/restore traffic. All 256 KiB EWRAM and 32 KiB IWRAM bytes match the
expected final state. Both callers preserve r4-r11, restore SP and return to
the Thumb sentinel, with the observed maximum 40-byte stack depth. These
finite tests do not convert the byte-different source into a match.

Coverage is 72/73 caller instructions, all 87/87 6C88 instructions, and
45/51 6D38 instructions. Caller 08006E4E is the null-block arm after prior
block dereference and is not a valid input case. Missing helper instructions
08006D4E, 08006D56, 08006D58, 08006D5A, 08006D7A and 08006D90 are null-head
or null-node paths outside these consistent post-insertion lists. They are
not claimed dynamically covered.

Three runtime negative controls reject a wrong neighbor-field store, wrong
count increment and wrong shift in the actual selection helper. Two report
negative checks reject the real nonmatch and a forged matching verdict.
`check.log`, `official.log`, `not-match-report.md`, `freeze.json` and the
three small attempt logs remain under the author scratch directory. All
generated objects, linked executables and layout intermediates are removed.

## Limits and disposition

There is no arbitrary output/metadata overlay, malformed-link, cyclic-list,
null-block, concurrent-mutation, MMIO, allocator-capacity, ownership or
universal-termination proof. Count-byte carry is tested, not a full 65535
node list or count-wrap fixture. The typed byte-arena lifetime and pointer
arithmetic assumptions remain explicit. No nominal original types or broad
equivalence claim is inferred from the bounded cases.

This recovery stays Parked and contributes no active matched-byte credit.
No helper source, production map, shared header, Git state or lease was
modified by the author. Root owns independent review and reservation release.
