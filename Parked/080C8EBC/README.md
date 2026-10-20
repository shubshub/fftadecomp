# 080C8EBC — natural recovery, not matching

## Extent and verification

The complete target is `[0x080C8EBC, 0x080C9076)`: 442 bytes and 204
reachable Thumb instructions. It has no literal pools, tables, or internal
alignment. The zero halfword at `0x080C9076` is outside the function.
Independent bounded CFG inventory and Binary Ninja agree on this extent.

The retained candidate compiles with agbcc `-mthumb-interwork -O2` to
450 bytes and 208 instructions. The reviewed `3f840c6` matcher accepts its
fixed-frame/direct-call CFG and marks its source plausible, but correctly
reports `NOT MATCHING - bytes differ`.

The saved diagnostic report compares the complete 450-byte candidate with
450 ROM bytes starting at the target. Its last eight ROM bytes are outside
the actual 442-byte target; they are not an enlarged function boundary.
The report's 390/450 comparison score is not an exact-symbol match. Direct
same-offset comparison agrees on 225 of the actual target's 442 bytes.
The first difference is the branch displacement at `0x080C8F0C`.

## Recovered behavior

The function receives an object byte pointer and an output byte pointer and
returns the written length in the low byte. It has no output-capacity
argument or check, does not append a terminator, and does not establish an
allocation bound. Output may alias object storage; later object-count and
entry-byte reads must remain observable.

The first path is selected by the short-circuit calls to `080C8240`,
`080C8260`, and `080C8194` with category arguments `0x0A`, `9`, and `0x5E`.
It snapshots accessor selector 3, conditionally appends 1 after repeated
predicate calls, and scans ascending entries from 1 while below the
reloaded object byte at `0x34`. For nonzero bytes at `0x40 + index`, it
uses `080C94D0` followed by `080C8570` selector `0x0C`. It appends only
nonzero values absent from the current output prefix.

The other path selects inclusive bit ranges: default 5–15, category 2
uses 16–22, category 3 uses 23–30, category 4 uses 31–38, and category 5
uses 39–46. It conditionally appends 1 using `080C8228`. Each set bit
reported by `080C9540` produces a low-byte `080C8570` result using record
index `bit - 3`. This path neither filters zero nor removes duplicates.

Helper contracts are ordinary ABI assumptions, not a proof of the entire
call tree's termination or validity. In particular, this recovery does not
invent a termination guard for `080C8570` link chains.

## Bounded attempts and remaining differences

1. A straightforward raw-byte view with a local output-prefix length
   compiled to 438 bytes / 202 instructions. The full-symbol matcher
   rejected the shorter extent.
2. A maintained prefix length and explicit paired bit/record indices
   reached 442 bytes but retained different register allocation,
   address calculations, and loop strength reduction.
3. The retained natural form uses a direct prefix-length condition in the
   duplicate scan and a byte-array view at offset `0x40`. It compiles to
   450 bytes / 208 instructions. The first-path outer index, entry address
   calculation, and second-path record-index induction still differ.
   The target maintains an unscaled record index; the candidate compiler
   maintains a shifted value before extracting its low byte.

A genuine flexible-array object declaration was also rejected by this
old compiler as an incomplete field type. It was removed rather than
replaced with an invented fixed array bound.

No asm, volatile accesses, register constraints, optimization changes,
artificial guards, padding, or altered helper contracts were used. This
candidate is retained only under `Parked`; there is no active source or
matching report for the address.
