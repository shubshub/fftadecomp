# 0x08006D38: plausible recovery, not a byte match

## Complete extent and verdict

The actual ROM function occupies `[0x08006D38, 0x08006D9E)`: 102 bytes and
51 instructions, all code, with no literal pool, table or internal padding.
The following zero halfword is external and excluded. Its SHA-256 is
`ebb75817e6e49a104d4d7562559c89ddc557fad028fc27e7b58bb62aa017566b`.

The retained candidate emits exactly one function symbol, also 102 bytes /
51 instructions, with no relocations. Its SHA-256 is
`6c31fdfaeaa44caa6392d3de8ece17dda6cd8bae2595d0268f5fd1b4b6cf7df5`.
The ELF `.text` section is 104 bytes because of two external `C046` alignment
bytes; these are not part of the function symbol or the comparison.

The frozen `kit-reviewed-2e2a664` matcher checked the complete symbol while
the candidate was active and reported **NOT MATCHING — bytes differ**,
with plausible source, 32/51 identical instructions and 83/102 equal bytes.
A separate positional byte comparison also gives 83/102. The complete
leaf CFG passes. This is a real code-generation mismatch, not a verifier
limitation or a prefix-only comparison. No active source, private include,
or match report remains for this recovery.

## Natural representation and bounded attempts

All attempts use the standard `agbcc -mthumb-interwork -O2` configuration.

1. Direct byte accesses with a reused `u16 offset` local emit 100 bytes /
   50 instructions. The count expression uses arithmetic rather than logical
   right shift, with equivalent results for its nonnegative byte-decoded range.
2. Separate unsigned head, count and next-offset values with a signed traversal
   counter emit 98 bytes / 49 instructions. The pointer-join copies disappear,
   and register choices differ from the target.
3. The retained private ordinary inline helper expresses the repeated operation
   of decoding two little-endian bytes as a nullable owner-relative word
   offset. It is used for both the head and next link. This restores the full
   102-byte / 51-instruction shape, but not its bytes.

The final candidate uses r3 for the current node and r1 for the countdown;
the target uses r2 and r3 respectively. The decoded words are ORed into
different registers, with corresponding compare, shift and traversal operand
differences. Branch positions, byte-access order and the final output-store
tail agree. The helper has a meaningful shared decoding role and emits no
standalone symbol. Historical use of an identical inline helper is an
inference, not established provenance.

No register binding, forced inline attribute, compiler pragma, volatile,
manufactured control flow, padding or optimization-flag sweep was used.
This bounded attempt does not establish that the function is inherently
unmatchable.

## ABI, behavior and valid storage

The compatible interface is `void func_08006D38(void *owner)`. It directly
consumes only r0, makes no calls, saves eight bytes, has no local frame or
incoming-stack arguments, and returns through saved LR in r0 rather than
producing a meaningful scalar result.

All encoded fields are accessed as separate bytes, low byte first:

- Decode owner bytes 0x00/0x01 as an unsigned word offset. Zero is null;
  otherwise the node is `owner + 4 * offset`.
- A null head immediately writes zero to owner bytes 0x02 and 0x03 without
  reading the count.
- Otherwise capture the unsigned count from bytes 0x04/0x05, halve it, then
  decrement the signed counter before each positive test. The number of
  followed links is `max((count >> 1) - 1, 0)`, at most 32766.
- Each traversal decodes node bytes 0x0A/0x0B using the same representation.
  A final null node selects zero. A nonnull node produces the low 16 bits of
  its owner-relative word offset.
- Write the selected offset to owner bytes 0x02 and 0x03. No other nonstack
  memory is written. Count metadata is not reloaded during traversal.

There is deliberately no null-node guard inside the traversal. A null link
on the last traversal is accepted; one reached earlier can cause a later
read at address 0x0000000A. Such raw machine faults are not valid C executions.
Real C pointer arithmetic and subtraction require live byte storage covering
the owner-relative nodes, not merely numerically mapped addresses. No arena
capacity, allocation ownership or metadata-consistency guarantee is inferred.
Finite cycles can be traversed because the count bounds the loop, provided
all accesses remain valid; this is not an allocator-wide termination claim.

## Reproducible bounded evidence

Run from the game repository with the standard environment:

```sh
PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH python3 /home/user/.codex-work/ffta-ulw/6d38-author-98/check.py
```

The small reproducer freshly compiles the retained source, verifies one full
function symbol and the leaf CFG, and compares actual ROM with candidate
execution against an independently specified offset-traversal operation model.
It self-cleans generated build artifacts.

All 201 paired cases / 402 executions pass, covering all 51 target and all
51 candidate instructions. Of these, 183 pairs return normally and 18 pairs
are explicitly machine-only malformed-link faults. Fixtures include empty
heads, counts from zero through 65535, last-traversal null links, earlier null
faults, high offsets through 0xFFFF, byte-unaligned owner bases, and finite
self/multiple-node cycles. All data are synthetic RAM; no helper stubs or
callee models are involved because this function is a leaf.

The independent model, target and candidate agree on exact ordered byte reads
and writes, full final RAM and fault location. Returning cases also preserve
r4-r11, SP and the return destination, with eight-byte stack depth. Data traces
exclude instruction fetches and stack accesses. Faulting cases do not claim
successful ABI restoration or portable C behavior.

Only the source, private header, this diagnosis and small disk-backed
reproducer/build scripts are retained. Root owns reservation release,
metadata, independent review and any eventual promotion.
