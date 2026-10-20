# 080CEDC8 — recycle a record and list node (not matching)

This is a plausible recovery, not a matching function. The retained ordinary
C candidate compiles with agbcc `-mthumb-interwork -O2` to one 276-byte
function, while the complete target is 260 bytes. The frozen
`kit-reviewed-2e2a664` matcher accepts its existing callback/data verification
profile and source plausibility, but reports `NOT MATCHING - bytes differ`.
There is no toolkit capability blocker here.

## Complete extents and differences

The target is `[0x080CEDC8, 0x080CEECC)`, with 109 reachable Thumb instructions,
224 code bytes, eight literal words, and two zero alignment halfwords.
Its code ranges are `[0x080CEDC8, 0x080CEDD6)`,
`[0x080CEDE0, 0x080CEEA2)`, and `[0x080CEEBC, 0x080CEECC)`.
The alignment halfwords are at `0x080CEDD6` and `0x080CEEA2`; the pools are
`[0x080CEDD8, 0x080CEDE0)` and `[0x080CEEA4, 0x080CEEBC)`.
The next entry at `0x080CEECC` is excluded. Entry evidence is the indexed
prologue, closed bounded CFG and following entry, not an inbound-reference
claim.

The candidate's single function and `.text` are both 276 bytes. It has 116
reachable instructions, 238 code bytes, the same eight literal values, and
six alignment bytes. Its pools/alignment occupy
`[0x080CEDD6, 0x080CEDE0)`, `[0x080CEE82, 0x080CEE94)`, and
`[0x080CEEC2, 0x080CEECC)`. There are no linker veneers or unresolved
relocations. Its linked symbol SHA-256 is
`f80eaef9b09403ea26c4f5471cd1c6e2dd4f5b4b7b8bf6c0a0e480d2a8300bcf`.

The remaining differences include loop unrolling, register allocation,
literal placement, alignment and caching of the final list-head value. Only
50 of the target's 260 byte positions agree; the candidate also extends 16
bytes beyond that complete target. The saved tool diagnostic reports
164/276 matching bytes using its sequence comparison, and its 276-byte ROM
window includes 16 bytes of the next function. That diagnostic is not a
claim that the target owns those extra bytes or that a prefix matches.

Two normal source forms were tested: an initial function-lifetime state
view and the retained form that scopes the insertion state view to that
operation. Both emit 276 bytes. The latter removes an unnecessary high
register save from the first form but still differs overall. No alternate
compiler flags, artificial reloads, storage constraints, assembly or forced
control flow were tried. The source and diagnostic were removed from active
`src/` and `docs/match/`; `match.md` is only the original nonmatching
diagnostic, whose source path names the former active location.

## Grounded state and operation

The compatible interface is `u32 func_080CEDC8(void *source)`. It consumes
only the incoming source pointer, has no incoming stack arguments, saves
20 bytes, and returns normalized full-word zero or one.

The observed state consists of 64 records of 16 bytes at `0x020021C8`,
64 nodes of 12 bytes at `0x020025C8`, and the head word at `0x020028C8`.
A node contains record, previous and next pointers at offsets 0, 4 and 8.
A record's first ten identifier bits are byte 0 plus the low two bits of
byte 1; eligibility tests bits `0x1C` of byte 2. The local views preserve
those observed offsets without adding a conflicting named-global type:
the existing global declaration remains `extern u8 g_state_02000000[]`.

The function follows next pointers to the tail without checking the initial
head for null. It then walks backward, checking for a previous node before
reading each record. The head itself is not selected. If no eligible
non-head node exists, it returns zero without callback or data writes.

For a selected node it updates the previous node's next link, reloads the
selected node's next link, and, when nonnull, updates that next node's
previous link. It then calls the initializer from `0x0836D4B8` separately
for the old record (16 bytes) and old node (12 bytes), reloading the callback
slot for the second call. It finds the first zero identifier among all 64
records and calls the copier from `0x0836D4BC` with that record, the incoming
source and length 16. It finds the first null record pointer among all 64
nodes and inserts it at the current head.

No guard was invented for pool exhaustion: an exhausted search yields null
and the target proceeds to the copy or insertion. Those paths are not valid
C memory-operation domains. With a nonempty final head, insertion stores
record, null previous, next, old-head previous, then global head. With an
empty final head it stores global head first, then record, null next and
null previous. The ordinary typed candidate caches the nonempty head during
these stores: a representative successful case reads the head word twice
overall, whereas the target reads it four times. Exact read-footprint
equivalence is therefore explicitly not claimed.

## Callback provenance and domain

The actual ROM slots contain `0x03005E79` and `0x03005EE9`. Their copied code
comes from ROM `[0x08A38A2C, 0x08A38ADC)` into RAM
`[0x03005E78, 0x03005F28)`, whose 176-byte SHA-256 is
`ce26dd719323641c1c4cbfa501368306ce6e31e193dabce7e84c7067f7590130`.
The ROM thunks at `0x0814224C` and `0x08142250` are the actual `bx r2` and
`bx r3` helpers, respectively.

The first callback clears the requested bytes. Its machine count guard is
signed; the caller's positive constants 12 and 16 agree with the existing
`void (*)(void *, u32)` callback convention. The second callback has the
existing `void (*)(void *, void *, s32)` convention. It copies forward using
word reads/writes only when both pointers are four-byte aligned, then a byte
tail; otherwise it copies bytewise. It is not overlap-safe `memmove`.
Neither copied routine consumes hidden arguments, makes external calls or
retains the passed pointers beyond its writes. This describes the audited
copied bytes, not arbitrary replacements of the callback slots. The
official matching profile itself uses ordinary ABI summaries and does not
prove callback purity or the runtime identity of RAM code.

The meaningful C domain requires valid typed nodes and records, a nonnull
acyclic initial list, accessible source storage, and available destination
record/node storage when success is reached. Source aliases to the selected
record, another record or the eventual destination are not prohibited. The
selected record is cleared before the source is copied, so such aliases can
change what is copied. No `restrict`, arbitrary allocation bound, fabricated
exhaustion behavior or universal alias/termination guarantee is introduced.
In particular, overlapping incompatible aggregate views or unmapped/null
objects are not claimed as defined C inputs.

## Bounded direct-ROM evidence

The local diagnostic freshly compiles the candidate and compares it against
the actual 260 target bytes. All 38 paired fixtures (76 executions) agree
with a separate memory-operation model on returned values or expected
faults, exact ordered nonstack writes, callback arguments/order and final
RAM. All 109 target and 116 candidate instructions execute. Every callback
executes the actual copied initializer or copier through the actual ROM
thunk and slot; no helper is stubbed or modeled in the emulator.

- 32 ordinary-layout synthetic RAM cases cover a head-only list, no eligible
  node, tail/interior selection, early free slots, scans reaching released
  last slots, and source aliases to the selected, other or destination record.
- Three explicitly machine-only overlap fixtures cover forward overlapping
  copies and a record view overlapping the head word. They do not extend the
  C effective-type/subobject domain.
- Three explicitly out-of-domain machine fixtures cover null initial head,
  record exhaustion and node exhaustion. The target and candidate fault at
  the same unmapped address after identical earlier writes/calls; no safe C
  behavior is inferred for these inputs.

There are 16 zero returns, 19 one returns and three expected faults. Read
traces differ in 21 fixtures; write/call/final-state agreement is not
presented as exact ordered-read agreement. All successful returns preserve
callee-saved registers and SP; copied code and callback slots remain
unchanged. The combined executed initializer/copier coverage is 56
instructions. The fixtures are synthetic RAM, while caller, callback slots,
thunks and copied callback instructions come from the actual ROM.

The reusable local diagnostic is:

```
PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp \
PATH=/home/user/armtc/root/usr/bin:$PATH \
python3 /home/user/.codex-work/ffta-ulw/080CEDC8/check_recovery.py \
    Parked/080CEDC8/080CEDC8.c
```

Run from the game root. The neighboring typed binding and linker scripts
are diagnostic-only. Generated builds use task-scoped disk storage and are
removed automatically; no binary or raw ROM dump is retained.
