# 08006DA0 — parked recovery

This is a natural, behavior-tested recovery, **not a byte match**. No active
source, private header or match report remains for this address.

## Complete symbol and discrepancy

The actual ROM function is `[0x08006DA0,0x08006E26)`: 134 bytes containing
66 reachable instructions. Every byte is code; there are no literal pools,
tables or internal alignment. The zero halfword at `0x08006E26` is external
alignment before the next function at `0x08006E28`, and is excluded.

ROM SHA-256:
`52ccddd712513cc0c943490a0be055ad763ddc048fcd42af45a2e191bbb86384`.

The retained source emits one ELF `STT_FUNC` of 130 bytes / 64 instructions.
Its `.text` is 132 bytes, with an external `c046` alignment halfword after the
function symbol. That halfword is not part of the candidate. Typed linking
resolves the single ordinary call to `08006D38`; no unresolved relocation or
additional emitted function remains. Linked candidate SHA-256:
`b71237da058604cd5ee0ca5e43eb54b5f74179e959261cd9b8af574ecdc0d580`.

There are 33 equal byte positions out of the full 134-byte target: 97
overlapping byte positions differ and four target positions are absent.
Eight instructions have identical bytes at the same address. This is a
positional count, not an instruction-alignment score.

The frozen `2e2a664` verifier rejects the complete symbol:

```text
compiled symbol is shorter than the indexed span: 130 < 134
```

Separate complete-body CFG, typed-link and plausibility checks pass as
diagnostics only; they do not override that rejection. The candidate produces
both decoded pointers directly in their destination registers, omitting the
target's two moves from `r0` after the conditional decodes. Register operands
also differ in the assembled-offset and decrement expressions. Consequently
later branch/call positions differ. The retained compiled body preserves the
observed byte-read/store order in the tested paths.

## Bounded natural forms

1. A generic owner/block interface with local byte views and a cached complete
   next offset produced 122 bytes. It reused the complete offset rather than
   reconstructing it inside the neighbor/head assignments.
2. Consistent byte-pointer formals and assignments from the source encoded
   link field produced the retained 130-byte form. The compiler retains the
   loaded next-link bytes through the conditional assignments.
3. A meaningful ordinary inline decoder taking an already assembled offset
   also produced the same 130-byte body.
4. A decoder taking the encoded byte pair, analogous to the repeated operation
   in neighboring `08006D38`, with native-width decoded arithmetic, produced
   136 bytes. It added a high-byte reload before the neighbor/head stores.
   This form was discarded rather than weakening the ordered-read evidence.

No forced-inline attribute, assembly, volatile operation, packing/alignment
directive, alternate compiler flag, artificial storage or control-flow
scaffolding was used. The simpler direct byte view is retained without a
private header. This bounded result does not establish inherent unmatchability.

## Recovered contract and order

The retained compatible interface is
`void func_08006DA0(u8 *owner, u8 *block)`. The pointers are byte views, not
claims about the unique original nominal types or complete allocator layout.
No incoming `r2`, `r3` or stack argument is consumed. The target saves 16 bytes
without a local frame; saved LR is popped into `r0` on return, so no meaningful
scalar result is established.

All encoded 16-bit fields are accessed as separate bytes, low byte first:

1. Read block bytes `0x08/0x09`, then `0x0A/0x0B`. Zero denotes a null link;
   nonzero denotes `owner + 4 * offset`. Both decoded pointers are captured
   before any link write.
2. Copy the captured next offset to previous-node bytes `0x0A/0x0B`, or to
   owner bytes `0x00/0x01` when no previous node exists.
3. If a next node exists, **reload** block bytes `0x08/0x09` after the preceding
   writes and copy that offset into next-node bytes `0x08/0x09`.
4. Clear block bytes in exact order `0x0A`, `0x0B`, `0x08`, `0x09`.
5. Read owner count bytes `0x04/0x05`, decrement, and store the low/high result
   bytes. The retained `u16` conversion wraps zero to `0xFFFF`; no extra guard
   or clamp is introduced.
6. Call `void func_08006D38(void *owner)` with the original owner pointer.
   This declaration agrees with the independently recovered helper. No
   purity assumption or cached owner metadata crosses the call.

The actual `08006D38` body is `[0x08006D38,0x08006D9E)`, 102 bytes / 51
instructions. It reads the updated head/count, follows the encoded next links
for its bounded decrement loop, then writes the selected owner-relative offset
to owner bytes `0x02/0x03`. A prematurely exhausted chain can cause a null read;
the caller adds no guard that would hide that behavior.

Actual incoming-entry evidence is the independently audited BL at
`0x08006EE6` in `08006EC0`, in addition to the closed prologue/return and
adjacent-function boundaries. No exhaustive caller or ownership proof is made.

## Fresh behavioral evidence

The retained self-cleaning reproducer is
`/home/user/.codex-work/ffta-ulw/08006DA0-08/check_recovery.py`:

```sh
export PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp
export PATH=/home/user/armtc/root/usr/bin:$PATH
python3 /home/user/.codex-work/ffta-ulw/08006DA0-08/check_recovery.py
```

It independently compiles and typed-links the parked source, verifies full
symbol extents and the isolated official rejection, and executes target ROM
versus the fresh candidate. Both execute the **actual ROM `08006D38` body**;
no helper is stubbed or replaced with parked C. A separate semantic oracle
checks each body's complete ordered nonstack reads, writes, helper call,
full synthetic EWRAM and untouched nonstack IWRAM.

All 158 paired cases / 316 executions pass: 157 return pairs and one explicit
null-chain fault pair. The cases include 135 list-removal cases covering every
position in lists of lengths one through nine at three byte-base alignments.
The remaining 23 diagnostic cases cover count wrap/high-byte boundaries,
cyclic or self links, premature null termination, and a byte-overlap case where
the first neighbor write changes the block's previous offset before its reload.
These malformed-metadata cases are not claims of valid allocator invariants.

All 66 target instructions, all 64 candidate instructions and all 51 actual
helper instructions are covered. Every returning case checks the return PC,
restored SP and callee-saved `r4..r11`; incoming unrelated registers vary across
cases. Maximum observed stack depth, including the real helper, is 24 bytes
for both bodies. No nonstack memory access is omitted from the ordered trace.

Valid live byte storage covering the owner, block and every derived link
remains required. Pointer arithmetic is within that storage for ordinary C;
the ROM's address arithmetic does not establish arbitrary arena capacity,
ownership, object lifetime or allocator-wide safety. The null fault is a
machine diagnostic, not defined C behavior. Instruction coverage and these
bounded fixtures are not universal behavioral-equivalence or termination
proofs. Full byte equality remains unresolved.
