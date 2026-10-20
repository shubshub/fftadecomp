# 080CE4DC: natural recovery, not a match

## Complete target

The actual ROM function is `[0x080CE4DC, 0x080CE8A6)`: 970 bytes and
349 instructions. It contains 700 code bytes, the required two zero alignment
bytes at `0x080CE4FE`, the object word `0x0855AE4C` at `0x080CE500`, the local
table pointer at `0x080CE504`, and 65 four-byte destinations beginning at
`0x080CE508`. Selectors 19 and 20 share a destination. The zero halfword after
`0x080CE8A6` is outside the function.

The compatible recovered interface is `u32 func_080CE4DC(u16 index, u8 selector)`.
Both arguments are normalized at entry. The record stride is 70 bytes; no outer
table length is established. Selectors 0 through 64 return byte/bit-field values,
little-endian halfwords, scaled values, or record-interior pointer bits. Other
low-byte selectors return zero. Pointer-to-word conversion is specific to the
32-bit target ABI, not a portable host-pointer representation.

Selectors **42, 44, and 53** share the one physical call to
`u32 func_080CB4A4(u8 value)`, reading record offsets `0x36`, `0x37`, and `0x3D`
respectively. The caller explicitly narrows the returned value to `u16`.
The real helper returns zero for zero input and otherwise input plus `0x177`.
Selector 49 reads the field in byte `0x3A`; it is not the helper case.

## Retained source and measured gap

The retained source uses an unsized table of 70-byte rows, ordinary masks and
shifts for the observed bit fields, and a private inline little-endian `u16`
reader. The reader is a natural description of repeated adjacent-byte accesses,
not proof of the original source's helper organization. No packed structure,
packing attribute, forced register, volatile access, assembly, artificial
control flow, or added bounds/null guard is used.

With `agbcc -mthumb-interwork -O2`, the retained candidate has exactly one emitted
function symbol, **950 bytes / 339 instructions**, versus **970 / 349** in the
ROM. Its `.text` has two additional external alignment bytes, which are not part
of the 950-byte symbol. The object word, local pointer, 65-entry table, and
required internal alignment retain their original offsets. Case destinations,
some operations, and the final extent differ.

The frozen reviewed toolkit `2e2a664` rejects this candidate with:

```
compile failed:
switch caller requires an exact mapped Thumb span
```

This rejection occurs before the official byte-comparison/report stage. No
byte-match percentage or successful match/report replay is claimed. The exact
970-byte ROM mapping remains correct; it was not shortened for the candidate.

Concrete differences include selector/record allocation in `r3`/`r2` instead of
`r2`/`r3`, ordinary mask operations instead of some target shift pairs, and
different adjacent-byte load/address sequences. For selector 5, the compiler
eliminates the high-byte read because the result only uses bit zero. The ROM
reads offsets `0x41` then `0x42`, combines them, and masks the result. Other flag
cases similarly use target pointer increments and operand allocation that the
candidate does not reproduce. These are not repaired with fake storage views or
artificial shifts.

Bounded natural forms tried under the same standard flags:

| Form | Complete symbol bytes |
| --- | ---: |
| Direct byte-array expressions throughout | 1006 |
| Shared inline reader returning `bytes[0] \| (bytes[1] << 8)` | 950 |
| Reader using a `u16` accumulator and advancing byte pointer | 1010 |

No optimization-flag sweep or compiler/profile change was attempted. This is a
local code-generation mismatch, not evidence that the function is inherently
unmatchable.

## Bounded semantic evidence

A separate diagnostic link and Unicorn execution compared the retained
candidate and actual ROM against an independent selector model. This diagnostic
link is not the official matching gate and does not bypass its rejection.

There were 9,216 executions: both bodies, all 256 low-byte selectors, 14 explicitly
synthetic 70-byte rows, and four bounded ROM byte slices at row indices 0, 1, 7,
and 23. Synthetic rows used index 255. Upper argument bits and unrelated register
contents varied. These fixtures establish no allocation bound or universal
record-validity domain.

Every execution used the real 26-byte helper, not a helper stub. Checks covered
the returned value, the exact helper-call argument and call count, no writes
outside the stack, unchanged record bytes, restored SP and `r4` through `r11`,
and return to the sentinel address. The ROM's ordered record-byte reads were
checked per selector. All 349 ROM instructions, all 339 candidate instructions,
and all 11 helper instructions were executed. Candidate read traces are not
claimed identical: the selector-5 difference is explicit above.

The source and private header pass the frozen plausibility checker with no
findings. No active source/header or normal match report remains for this
address. The reproducible diagnostic script is retained outside the repository
under the address-scoped task directory; generated binary artifacts are removed.
