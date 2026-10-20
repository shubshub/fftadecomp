# 080D0B48: record activation and list reorder, not a match

## Disposition and complete-symbol evidence

This is a natural-C recovery, parked rather than byte-identical. There is no
active source or successful match report. Equal symbol length is not a MATCH,
and no inherent unmatchability or unique original-source reconstruction is
claimed.

- Complete target: `[0x080D0B48,0x080D0ED2)`, 906 bytes / 418 reachable
  Thumb instructions, with one return at `0x080D0ED0`.
- Target SHA-256:
  `2333a76ec3bc94a7eb315a43cb08355883e93c452cf95bb5dab16d3ecbea25a7`.
- Target code occupies 848 bytes. Its 13 literal words occupy
  `[0x080D0CC4,0x080D0CDC)`, `[0x080D0DA8,0x080D0DAC)`,
  `[0x080D0DF0,0x080D0DF4)`, `[0x080D0E54,0x080D0E60)`,
  `[0x080D0E78,0x080D0E7C)` and `[0x080D0EAC,0x080D0EB0)`.
  Zero halfwords at `0x080D0DEE`, `0x080D0E52` and `0x080D0E76` are internal
  alignment. The zero halfword at `0x080D0ED2` is external; a separate genuine
  entry begins at `0x080D0ED4`.
- Retained candidate: the same 906-byte function extent, but 414 instructions,
  840 code bytes, 15 literal words and six internal alignment bytes.
  There is exactly one code-defined `STT_FUNC`. The ELF `.text` is 908 bytes;
  its final `c046` NOP is outside the function symbol.
- Linked candidate SHA-256:
  `b1618ba81c222d193e86b8b25382d55b626feb8044f322041c05b21b57f3ed98`.
- Same-address comparison finds 125 equal bytes and 781 differing bytes;
  30 instructions have equal bytes at their original addresses. No target
  bytes are omitted by the retained symbol, but most do not match.

Both functions save 32 bytes of registers without a local frame. Differences
include register allocation, cached byte reads, helper-result narrowing,
constant-mask materialization, conditional assignment shape, global-base
reuse and literal-pool placement. The final list updates and epilogue partly
align, but this is not a partial-match promotion.

## Bounded attempts and official verification

Three ordinary representations were checked with unchanged
`agbcc -mthumb-interwork -O2`:

1. A direct byte-offset view of the list-head pointer emitted 876 bytes / 408
   instructions and failed the official complete-symbol length check.
2. The retained structured state view, grounded by the observed head at
   offset `0x28C8` and the neighboring recovery, emits 906 bytes / 414.
3. Directly masking helper results in field assignments, with a full-word
   intermediate for the cached flag calculation, emitted 898 bytes / 414.
   The explicit helper-result form was retained for its clearer call/read
   sequencing. No further compiler search was performed.

The frozen `kit-reviewed-2e2a664` matcher accepts the retained complete ELF
extent, ordinary typed BL bindings, named-data relocations and strict source
plausibility, then reports `NOT MATCHING - bytes differ` with exit 1. Raw CFG
verification accepts all 414 candidate instructions and all 418 target
instructions. There is no local long-BL, switch, outgoing stack argument,
unsupported arithmetic runtime or unresolved transfer in this caller.
No verifier change, runtime-binding bypass, assembly, volatile access,
forced register, artificial storage, private inline helper or altered
optimization option was used. No saved successful-report replay is claimed.

For reproduction, preprocess this source at its canonical source location in
an isolated game tree with the current headers/configuration, use the normal
frozen matcher, and inspect the full ELF symbol rather than truncating it.
The same ordinary `match.link_calls` path was used for the diagnostic binary;
no custom callee or data binding was substituted.

## Interface, layouts and ordered effects

The compatible interface is `void(u8 *record, void *object, u16 first,
u16 second)`. Both trailing registers are explicitly narrowed to 16 bits;
only their low bytes are stored at record offsets `+0x04` and `+0x05`.
The epilogue restores the return address into `r0`, so residual `r0` does not
establish a scalar return. Original nominal parameter types are not unique.

`ObjectState` records only observed halfwords at `+0x16` and `+0x28`.
When non-null, the object receives the record's ten-bit identifier and mask
`0x04` is ORed into its flags. The local linked-node view has data/previous/next
pointers at `+0x00/+0x04/+0x08`. The global backing declaration remains the
existing `extern u8 g_state_02000000[]`; a local state view locates its head at
`+0x28C8`. This is a physical observation, not a universal allocation or
strict-aliasing guarantee. The canonical `ScriptEntry` header is reused, as
are compatible six-byte row, 70-byte definition and 27-byte definition-table
declarations. The new four-byte threshold-row stride is directly observed;
no table allocation bound is inferred.

The record's bits `0x1C` at `+0x02` are cleared and its 70-byte definition is
selected by the ten-bit identifier. Packed definition fields set byte
`+0x03`, substituting `0xFF` for zero, and fields split across record bytes
`+0x01/+0x02`. The originally cleared byte is retained for the second update.

For definition kind 1, the function finds the first empty low-three-bit tag
among five six-byte rows at `0x02002E34`. If all are occupied, it retains the
fifth row while the loop index becomes 5; no new capacity guard is added.
The actual copied clear callback clears six bytes before packed fields are
written. The definition can cause a `08036330` call whose result is stored
and then overwritten by the raw encoded definition field. That call and the
intermediate store are preserved. The category byte is reloaded before its
later lookup. After another getter call and `08036440(value,0)`, a matching
other occupied row may cause bit `0x80` to be set in selected byte `+0x01`.

For kind 0, `080CF310(record,object,1)` returns a full unsigned word. Its
audited range is 0 through 5. A nonzero result selects a four-byte row at
`0x08527E4A`; RNG is called before reading that row's threshold byte. The
natural signed-sixteen-bit RNG conversion and `% 256` are retained. The
comparison may replace the result with zero, then its low 16 bits are stored
as two separate bytes at record `+0x06/+0x07`. The actual RNG returns
0 through 32767, so its signed narrowing is lossless on those executions.

Finally, two traversals locate the selected node and the tail. A node's data
is compared only while its next pointer is non-null; an absent record falls
through to the tail. A selected non-tail node is detached and appended using
the observed reload/store order. No empty-head or cycle guard is invented.

The initial null-object check does not establish null safety for kind 0:
the audited `080CF310` implementation reads object fields and has its own
valid-pointer/divisor requirements. This caller uses its compatible ordinary
ABI summary, not a recursive callee-safety proof. Likewise, list traversal
requires a readable non-null finite list and writable nodes for updates.
Valid record/table storage and compatible object lifetimes remain caller
contracts; these tests do not prove arbitrary allocation or alias validity.

## Bounded behavioral evidence and read-trace limitation

370 paired fixtures / 740 executions ran the actual ROM caller and the
freshly linked candidate against an independent memory/result/call model.
The fixtures use explicitly synthetic RAM objects, lists, party rows and
table records at their observed addresses. Actual instructions execute for
RNG `08002804`, getter `08036330`, predicate `08036440`, thunk `0814224C`, and
the 50-byte clear body copied from ROM `08A38A2C..08A38A5E` to RAM
`03005E78..03005EAA`.

Only `080CF310` is explicitly modeled: its return is chosen within audited
range 0..5, with no modeled memory changes and caller-clobbered registers
invalidated. Its real body and divisor/domain behavior are not tested here.
Thus the kind-0 fixtures are caller tests under that summary, not a proof
that every synthetic object can safely execute the real helper.

The cases cover null/non-null initial objects on non-kind-0 paths; kinds
0/1/2/3/5/7; all five empty-slot positions and all-full rows; encoded fields
with and without bit `0x80`; getter zero and selected-row-adjacent reads;
party membership and duplicate-row checks; identifiers including `0x3FF`
with explicitly supplied synthetic definitions; first/second argument upper
bits; RNG threshold edges for all result buckets; and singleton, head,
middle, tail and absent-record list cases.

All 370 pairs agree with the independent model on full EWRAM, RNG and
non-stack IWRAM, compatible call arguments/order, return control, balanced
SP and preserved `r4-r11`. Memory outside the actual caller/helper stack
save area is unchanged except modeled data writes. Ordered non-stack write
traces agree between target and candidate in every pair. Per side the suite
executes 110 real clears, 158 real getter calls, 110 real party predicates,
150 real RNG calls and 180 modeled `080CF310` calls.

**Ordered reads do not match.** Every pair has a different complete data
trace. A concrete first difference is the ROM reloading record byte `+0x01`
before the packed update while the compiler reuses its earlier value. Other
cached/reordered reads are not claimed equivalent under concurrent mutation,
MMIO or arbitrary overlapping storage. Final-memory and ordered-write
agreement on these fixtures is not instruction or complete trace equality.

Coverage reaches 417/418 target and 413/414 candidate instructions. The
unexecuted instruction in each is the negative signed-remainder correction
(`0x080D0E24` target, `0x080D0E20` candidate), unreachable with the actual
nonnegative RNG range. Real helper coverage is clear 25/25, getter 12/12,
party predicate 44/53, RNG 10/10 and thunk 1/1; unused party modes are not
claimed covered. Generated ELF/binary/fixture artifacts are not retained.
