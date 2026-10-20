# 0x080D0590 — nonmatching multi-pass selection recovery

This is a plausible behavioral recovery, **not a byte match**. There is no
active source or verified match report for this address.

## Complete target

The target is `[0x080D0590, 0x080D0AB0)`: **1,312 bytes and 592 reachable
instructions**. Its SHA-256 is
`0e5682384c089f8e6b01e9cf354759d2b31e93b0215a0ee2409c4494480fa8ef`.
The next function's prologue at `0x080D0AB0` is excluded.

There are 1,202 code bytes in these ranges:

- `[0x080D0590, 0x080D05C4)`
- `[0x080D05D0, 0x080D0642)`
- `[0x080D0654, 0x080D072C)`
- `[0x080D0738, 0x080D0830)`
- `[0x080D0844, 0x080D08A4)`
- `[0x080D08A8, 0x080D09B6)`
- `[0x080D09D8, 0x080D0A76)`
- `[0x080D0A80, 0x080D0AB0)`

The 26 literal words occupy `[0x080D05C4, 0x080D05D0)`,
`[0x080D0644, 0x080D0654)`, `[0x080D072C, 0x080D0738)`,
`[0x080D0830, 0x080D0844)`, `[0x080D08A4, 0x080D08A8)`,
`[0x080D09B8, 0x080D09D8)`, and `[0x080D0A78, 0x080D0A80)`.
The three internal zero halfwords at `0x080D0642`, `0x080D09B6`, and
`0x080D0A76` belong to the complete symbol. There is no jump table.

The target saves 32 bytes and allocates 16 local bytes. All nine `BL`
instructions call external entries; none is a local long branch. Independent
bounded Binary Ninja analysis and the frozen verifier agree on the exact set
of 592 instruction addresses, with 126 Binary Ninja basic blocks.

## Interface and behavior

The compatible interface is
`u32 func_080D0590(SelectionRecord **output, u32 capacity, u32 filter)`.
The three incoming words are used without narrowing; no incoming `r3` or
stack argument is consumed. The original nominal parameter types and
signedness are not uniquely established by these operations.

The initial callback clears `capacity * 4` bytes before the list-head test.
The current ROM callback slot `0x0836D4B8` contains `0x03005E79`; the actual
copied clear routine takes `(void *destination, s32 byte_count)` through
`_call_via_r2`. Its signed count conversion is target-specific for large
unsigned products. No guard was added for zero or overflowing capacities.

The list head is at `0x020028C8`. Each node has its data pointer at offset
`0x00`, previous pointer at `0x04`, and next pointer at `0x08`. The 16-byte
record view and three category bits at byte `0x02` agree with this family's
previously recovered storage. Identifiers combine byte `0x00` and the low
two bits of byte `0x01`. Definition rows are 70 bytes at `0x0855AE4C`.
The canonical `script_entry.h` declaration is used for the separate 12-byte
rows at `0x08563A70`; the permission argument is their byte `0x00`, not their
named identifier at byte `0x01`.

The recovered phases preserve these distinctions:

1. Count unused slots among five six-byte records at `0x02002E34`.
2. Reserve capacity for category-zero records outside IDs `0x150..0x166`,
   without appending them, and remember whether a reserved definition has
   group two. Reaching zero capacity here returns zero selected records.
3. Select definition kinds three/five or ID `0x0F`, with permission,
   category, filter, `0x0400` flag, deduplication, and unused-slot checks.
4. If no group-two reservation was seen, select at most one group-two
   record. This phase does not apply the preceding `0x0400` flag check.
5. Alternate group one and group zero, restarting at the head after a
   selection. Stop after both groups fail consecutively. ID `0x17F` also
   requires the five global flags `0x258..0x25C` to be clear, checked in
   short-circuit order.
6. On normal exhaustion, change unselected category-one records to category
   two. Capacity exhaustion returns immediately, skipping this cleanup.

Every append writes the pointer, increments the full-word return count,
conditionally normalizes the live record category to one, then decrements
capacity. Definition kind one consumes an unused slot. Output scans use the
zeros supplied by the initial clear; there is no appended terminator write.
Definition pointers are computed before permission calls, while the final
alternating phase reconstructs the record identifier again afterward.

The real permission helper `u8 func_08036330(u8)` reads
`0x02002CC3 + 12 * ((u8)selector - 1)`. Its zero-selector pre-base read is not
guarded away. The real `u8 func_080C9540(u16)` supplies the five flag tests.
Neither dependency is replaced or simplified in the recovery.

The private header contains ordinary meaningful inline identifier, range,
membership, little-endian flag, and filter operations. Their original inline
provenance is unknown. There are no forced-inline attributes, register
constraints, storage tricks, optimization pragmas, or forced read retention.

## Attempt and exact mismatch

One natural source form was compiled with the standard agbcc
`-mthumb-interwork -O2` settings using frozen toolkit `2e2a664`. The alternating
search uses ordinary separate preferred-group and previous-miss variables,
not an artificial packed local chosen to reproduce a register allocation.
No compiler-flag sweep or register-steering variants were attempted.

The official result was:

```text
compiled symbol is shorter than the indexed span: 1296 < 1312
```

The candidate is exactly one 1,296-byte `STT_FUNC` and a 1,296-byte `.text`,
with **594 reachable instructions**. It has 1,206 code bytes, 21 literal words
(84 bytes), and six alignment bytes. It saves the same 32 bytes but allocates
24 local bytes instead of 16. Registers, spill placement, branch destinations,
pool placement, and head-pointer reloads differ. At identical offsets, only
92 of the 1,296 overlapping byte positions agree; 1,204 differ, and the target
has another 16 bytes. No comparison includes the next function.

The linked candidate SHA-256 is
`7f2f63fc32ef5050d12e026eff95399adaa23afdda3dfbb86a55dbe515cdd3ae`.
Typed direct-call/data linking, complete candidate CFG verification, literal
ownership checks, and the separate plausibility check pass. The official
whole-symbol size gate still rejects it; there is no MATCH or saved-report
replay claim. A compiler layout probe confirms record size 16, node size 12,
canonical script-entry size 12, and the intended byte category layout.

## Bounded behavioral evidence and limits

Author tests execute both actual target and freshly linked candidate in
238 paired fixtures, or 476 body executions. All helpers execute their real
ROM instructions; the clear routine is copied from ROM `0x08A38A2C` to RAM
`0x03005E78`. Tables, list records, state bytes, and output storage are
explicitly synthetic. A separate operation model checks selection order,
return count, and record categories; it does not replace any executed helper.

Of these, 232 pairs use ordinary bounded storage, four returning pairs are
explicit machine-only zero-capacity or wrapped-clear-size fixtures, and two
pairs exhaust an instruction budget on a cyclic list. The 236 returning
pairs agree on return value, ordered nonstack writes, helper arguments,
results and order, complete final EWRAM, preserved `r4..r11`, SP, and return
destination. They include repeated nodes pointing to the same record,
capacity exits, ID boundaries, all category values, quota exhaustion, both
filter high-word cases and low filters, permission misses and zero selectors,
special-ID flag short circuits, alternating priorities, and cleanup.

**Read footprints are not identical.** There are 234 returning pairs with
different ordered data-read traces. In these fixtures the differences are
head-pointer reads at `0x020028C8` hoisted or reused by the candidate. The
remaining ordered reads agree after explicitly excluding those head reads.
For the one-record fixture, the target performs 81 tracked reads and the
candidate 79. Tracked reads include EWRAM and referenced ROM data, but not
stack accesses, instruction fetches, or differing literal-pool fetches.
This is not a blanket ordered-read equivalence claim.

The returning fixtures execute 236 clear calls, 1,196 permission calls, and
70 flag calls per body. Coverage reaches 587/592 target and 587/594 candidate
instructions, all 12 permission-helper instructions, all 22 bit-lookup
instructions, and 19 clear-routine instructions. The clear's unaligned byte
loop is not exercised by aligned pointer arrays and four-byte lengths.
The unvisited caller instructions concern a nonempty output scan during the
initial reservation pass and head-null branches after earlier nonnull checks;
the corresponding storage is cleared or stable in the ordinary fixtures.
No claim of universal path or alias coverage follows from these tests.

Ordinary source use requires appropriately typed, aligned output storage,
valid nodes and 16-byte records, all accessed definition/script rows and
state bytes, and sufficient capacity for the actual accesses. No table extent,
original allocation, inbound-call provenance, acyclicity, or universal
termination is established here. Cyclic budget limits are observations, not a
termination proof. Zero/large capacities and overlapping output/list storage
are not promoted to safe API contracts; incompatible aggregate overlap,
concurrent changes, and memory-mapped read side effects are outside the tested
ordinary C domain. There is no `restrict` or invented guard in the source.
