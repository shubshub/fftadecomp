# 080CE8A8 — semantic recovery, not a byte match

## Complete target and contract

The complete Thumb function is `[080CE8A8,080CE93C)`: 148 bytes and 59
reachable instructions. Code occupies `[080CE8A8,080CE8F0)` and
`[080CE904,080CE936)`. Five literal words occupy `[080CE8F0,080CE904)`;
the zero halfword at `080CE936` is internal alignment for the required
literal at `080CE938`. The next function starts at `080CE93C`.

The recovered interface is `u16 func_080CE8A8(void)`. It consumes no incoming
register or stack arguments, saves R4–R6/LR, and has no data writes. The
following caller captures the low 16 bits of its result; this supports the
chosen return type without uniquely establishing an original declaration.

- Read successive halfwords from `g_table_08529EE4` until `0xFFFF`.
- For each entry, call `u8 func_080C9540(u16)` with the low 16 bits of
  `entry + 0x2FF`, counting nonzero results in a word accumulator.
- Call the same predicate with `0x36`. A true result adds one and skips the
  linked-list access entirely.
- Otherwise read the list head at `g_state_02000000 + 0x28C8`. Each node has
  a data pointer at offset zero and a next pointer at offset eight. Read
  data byte zero, then byte one, and compare the ten-bit value
  `data[0] | ((data[1] & 3) << 8)` with `0x17F`.
- The first matching node adds one and stops traversal; null terminates a
  failed search. Return the low 16 bits of the accumulated count.

The private inline helper is an ordinary category-membership operation.
Its inlining is a plausible recovery, not a claim of unique original source
provenance. Unknown members record observed offsets, not a recovered full
allocation. The existing byte-array declaration of `g_state_02000000` is
retained; `CategoryState` is a local view of the observed head field.

## Exact remaining mismatch

With agbcc `-mthumb-interwork -O2` and the reviewed `2e2a664` toolkit,
the retained source emits exactly one function symbol, of size **144 bytes**
and **58 reachable instructions**. The official matcher rejects it with:

```text
compiled symbol is shorter than the indexed span: 144 < 148
```

There is no MATCH report or replay claim. This is not an unsupported-profile
failure: independent use of the same typed linker, closed-CFG verifier, and
named-data-literal checker succeeds for the complete candidate.

The two call sites remain at `080CE8C2` and `080CE8D8`, both bound to the
actual `080C9540` entry. The candidate has one 24-byte literal pool at
`[080CE908,080CE920)` and no alignment gap; its final return ends at
`080CE938`. The target instead splits its literals around the list-search
code and includes the internal alignment halfword described above.

At corresponding byte offsets, 68 bytes agree, 76 common-span bytes differ,
and the final four target bytes are absent. Exactly 25 target instructions
have identical instruction bytes at the same addresses in the candidate.
These are positional counts, not an alignment-based diff percentage.
The first differing byte is at `080CE8AC`, a literal-load displacement.

The table loop has the intended single read per entry. Remaining differences
include the list-head and category registers, loading the category literal
before the null-head test, list-search branch arrangement, an extra register
copy in the byte-mask expression, and the different literal-pool placement.
They are not merely relocatable call operands or trailing external padding.

Linked candidate SHA-256:
`ed1e49d5bbb00b796389e531f9b5a9eea7b1f2074a19f080023eefbd6fd0084e`.
Complete target SHA-256:
`8db70812d3668574a739909266f6860e1d42beefc31534435c01d8e4915543c3`.

## Bounded forms investigated

1. A pointer-based sentinel loop and a membership helper that obtains the
   global head itself produced a 136-byte function.
2. A head-pointer helper with an observed-field state view and a ten-bit
   bitfield also produced 136 bytes. The bitfield was discarded because it
   widened the two observed byte reads into one word read.
3. An indexed sentinel loop and the direct two-byte expression produced a
   148-byte function, but only 57 reachable instructions and different code.
   It redundantly reloaded the table entry before the call, so it was not
   retained as an exact ordered-access recovery.
4. The retained version captures the entry tested by the loop and passes
   that same value to the predicate. This corrects the duplicate-read issue
   and produces the 144-byte candidate documented above.

No register-binding, lifetime, forced-inlining, optimization-level, assembly,
volatile, or artificial-control-flow variants were used. The nonmatch is a
bounded recovery result, not evidence that a natural byte match is impossible.

## Behavioral verification

680 independently constructed paired cases executed both the actual target
ROM and the linked candidate: 1,360 executions and 5,832 pairs of real-helper
calls. The actual 50-byte `080C9540` body executed without stubs. Coverage
included all 59 target instructions, all 58 candidate instructions, and all
22 helper instructions.

Fixtures combined six sentinel tables, seven list shapes, four flag-byte
patterns, both values of flag `0x36`, and two unrelated-register patterns.
Eight additional cases used an invalid head pointer with flag `0x36` set,
confirming that traversal was skipped. Tables included empty, duplicate,
multi-entry, and 33-entry cases plus values whose offset addition wraps at
16 bits. Lists covered null, immediate and later matches, misses, ignored
upper category bits, and a matching node with an invalid next pointer.

Every case checked the normalized helper queries, final low-16 result,
exact ordered table/flag/head/node/data-byte reads, absence of data writes,
R4–R12 preservation, restored SP, and return address. Stack accesses were
confined to the caller's 16 saved bytes plus the helper's four saved bytes.
Code-literal reads and stack traffic were classified separately from data
accesses; literal-read order is not claimed identical between nonmatching
binaries. The frozen plausibility checker also accepts both source files.

These tables, RAM flags, nodes, and byte records are explicitly synthetic
fixtures. No actual table terminator or allocation bound has been recovered.
The C requires readable sentinel-terminated table storage, valid traversed
node/data pointers, and the selected flag storage. No claim is made that an
arbitrary list is acyclic, that every possible input terminates, or that a
bounded execution proves unrestricted memory safety. Large-count truncation
is present in the source and instructions, not exercised by these fixtures.

The parked source and private header can be preprocessed with `-I include`
from the game root and assembled with the normal toolchain. Linking must use
the current named table/state mappings and the typed `080C9540` function
binding; raw unresolved object bytes are not the comparison evidence.
