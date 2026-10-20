# 080CEF78 — mode-dependent linked-record search

This is a plausible recovery, not a byte match. No active source, private
header or match report is retained for this address.

## Complete extent and remaining difference

The complete target is `[080CEF78,080CF060)`: 232 bytes and 104 reachable Thumb
instructions. Its code ranges are `[EF78,EF96)`, `[EFA0,EFF6)` and
`[EFFC,F05A)`, with the common `080C` prefix omitted. Four literal words are
at `EF98`, `EF9C`, `EFF8` and `F05C`; they contain the named state base,
offset `0x28C8` and two copies of `-0x150`. Zero halfwords at `EF96`, `EFF6`
and `F05A` are internal alignment. Thus the full span contains 210 code
bytes, 16 literal bytes and six alignment bytes. The next indexed entry at
`080CF060` is excluded. Entry evidence is the indexed prologue and closed
bounded CFG, not a discovered incoming reference.

The retained candidate produces exactly one 228-byte ELF function and a
228-byte `.text` section with agbcc `-mthumb-interwork -O2`. It has 103
reachable instructions, 208 code bytes, the same four literal values and
four alignment bytes. Its code ranges are `[EF78,EF96)`, `[EFA0,EFFA)` and
`[F000,F058)`; its final literal ends at `F05C`. The linked symbol SHA-256 is
`75b1a722e69431d9530f43487f368afecd39f795d68c36fcf2da3ef6823b4817`.
Only 77 of the 228 overlapping byte positions are identical. This is not a
matching prefix or permission to truncate the target.

The frozen `2e2a664` official matcher rejects the candidate before comparison:
`compiled symbol is shorter than the indexed span: 228 < 232`. Separate
plausibility and complete raw linked-CFG checks pass. Both symbols retain
the same 20-byte saved-register set and one direct helper call. Differences
include register selection for identifier reconstruction, a shared suffix
of the backward identifier reconstruction, earlier initialization of the
range Boolean, and branch/literal placement. The observed target's explicit
range Boolean is retained semantically, not removed to hide a difference.

The first ordinary byte-view/direct-range form produced 228 bytes. A grounded
full-record category-bitfield form with direct range expressions produced
212 bytes. The retained form uses meaningful private inline identifier and
range helpers and produces 228 bytes. A preliminary truncated bitfield view
was rejected because agbcc widened its accesses to words. A separate
ten-bit `u16` identifier probe produced a halfword read rather than the
observed pair of byte reads and was not retained. No storage constraints,
assembly, compiler-flag changes, forced inlining or artificial control flow
were used. The inline origin is a plausible recovery, not identified original
source provenance.

## Interface, layout and traversal

The compatible interface returns a node pointer or null and consumes the low
eight bits of mode and low sixteen bits of category. The only helper is
`u32 func_080CEECC(u16 identifier)`: the caller tests the complete return word,
not its low byte. The audited real helper returns zero or one on returning
paths, but that range alone does not establish a narrow declared return type.

The global declaration remains the existing opaque
`extern u8 g_state_02000000[]`. A local typed state view reads the head pointer
at offset `0x28C8`. Nodes have record, previous and next pointers at offsets
0, 4 and 8. Records encode a ten-bit identifier in byte 0 and the low two
bits of byte 1; category occupies bits 2 through 4 of byte 2.

The neighboring independently audited `080CEDC8` establishes the concrete
64-entry, 16-byte record pool at `020021C8`, its 16-byte clear/copy lengths,
and the 12-byte node pool at `020025C8`. The private view's 13 trailing unknown
bytes therefore represent an observed record extent, not an invented gap.
Target-compiler probes confirm record size/alignment 16/4, unknown bytes
beginning at offset 3, node size/alignment 12/4, pointer offsets 0/4/8 and
head offset `0x28C8`. A static initialized field probe checks the byte-local
bitfield representation. Repeated header inclusion compiles. No shared
global or record declaration was changed.

Null head returns null. Mode zero searches forward, checking `node->next`
before processing each node; the next-null terminal node is excluded. It
returns the first category match whose identifier lies outside inclusive
`0x150..0x166`, using the observed wrapped 16-bit subtraction test.

Nonzero modes first follow next pointers to the terminal node, then search
backward while the current node has a previous pointer. The previous-null
node is excluded. For a category match, mode one calls `080CEECC`; only a
full-word zero result proceeds to reload the node's record pointer and
identifier and apply the exclusion test. Mode two performs that test without
calling the helper. Other nonzero modes still traverse and read categories
but never select a node. No early invalid-mode guard is invented.

The caller performs no non-stack writes. Repeated link reads and post-call
record reloads remain observable in the tested compiled recovery. The C
domain requires valid appropriately aligned typed nodes/records and readable
backing state. The concrete pool's alignment does not establish the validity
of every arbitrary pointer. No allocation bound, ownership, purity annotation,
acyclicity or universal termination guarantee is inferred.

## Bounded execution evidence

The reusable diagnostic freshly compiles and links the candidate, independently
models selection results and helper-call arguments, and compares actual target
and candidate execution in 151 paired fixtures, or 302 executions:

- 139 returning synthetic-RAM/table fixtures use actual ROM code for every
  executed helper. Of these, 35 invoke `080CEECC`, making 36 calls on each
  side. All nested `080CE4DC` and `080CB4A4` calls execute their real bodies.
- Ten returning fixtures explicitly model the helper, including returns
  `0`, `1`, `0x100`, `0x10000` and `0xFFFFFFFF`, caller-saved-register clobbers,
  and record-pointer mutation to excluded or accepted identifiers. Those
  mutations and wide values are not attributed to the actual helper.
- Two cyclic-list fixtures reach an execution budget without returning,
  preserving rather than replacing possible nontermination. Finite-budget
  traces are not asserted equal across different instruction counts.

All 149 returning pairs have equal exact ordered non-stack read traces,
helper arguments/order, return pointers and final RAM. Independent expectations
also check result/calls and all initialized RAM, including explicitly modeled
mutations. CPU non-stack writes are absent; returning executions preserve
`r4..r11`, restore SP and return to the supplied address. The fixtures cover
all 104 target and 103 candidate instructions, all 69 instructions of the real
`080CEECC`, 47 selected-path instructions of `080CE4DC` and all 11 instructions
of `080CB4A4`. This is instruction coverage, not every possible branch outcome
or full coverage of the large accessor.

Run from the game root:

```
PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp \
PATH=/home/user/armtc/root/usr/bin:$PATH \
python3 /home/user/.codex-work/ffta-ulw/080CEF78/check_recovery.py \
    Parked/080CEF78/080CEF78.c
```

The diagnostic also reproduces the official matcher rejection in a scoped
isolated root, checks plausibility, and verifies the target-compiler layout.
Generated binaries and temporary roots are removed automatically. No ROM
dump is retained. There is no MATCH or saved-successful-report replay claim.
