# 0800620C — natural recovery, not a verified match

## Complete target and retained candidate

The target owns `[0x0800620C,0x0800664A)`: **1,086 bytes / 522 reachable
instructions**, comprising 1,060 code bytes, six literal words and two internal
zero bytes. The zero halfword at `0x0800664A` is external alignment, not part
of this function. The next function starts at `0x0800664C`.

Target SHA-256:
`58a903fe68a78b1d8541362fe720839cbc5784a99f486e44e71e4a889ecb6d75`.

One ordinary natural C form was retained. Under the reviewed `4847c93` toolkit,
agbcc `-mthumb-interwork -O2` emits one **1,140-byte / 542-instruction FUNC**,
with `.text` also 1,140 bytes: 1,100 code bytes, nine literal words and four
internal zero bytes. Its diagnostic linked SHA-256 is
`04c2d48418ade9c7449b6387bf2eb306ef0fd15f7eaf2ba1b11a1050ffcd8d49`.
Only **75 of the 1,086 target-position bytes** and **15 of 522 same-address
instructions** agree. The candidate has 54 additional bytes; neighboring ROM
bytes are not counted as part of the comparison.

Both save r4-r10 and LR, but the target has 28 local bytes and the candidate
32, including an additional payload-pointer spill. Local depth before callees
is respectively 60 and 64 bytes. Register allocation, descriptor construction,
branch sharing, reload scheduling and literal placement differ throughout.
No register, storage, alignment or control-flow forcing was attempted.

## Admission limits and reproducible diagnostic

There is no active source or match report for this address. The official
isolated `match.py --no-write` invocation rejects the candidate with:

```text
buffer callee 0x08005FC4: buffer callee 0x0814187C: non-leaf calls and interrupts require linked CFG verification
```

The complete ROM's separate raw local verifier also rejects with
`inconsistent stack aliases at control-flow join`; the candidate rejects with
`unsupported stack-alias use or escape`. These are distinct proof limitations,
not permission to count diagnostic byte comparisons as an accepted match.
Even a future proof extension would still leave the substantial byte mismatch.

The diagnostic uses an isolated full-header root and adds exactly one local
data binding, `g_table_0836D498 = 0x0836D498`, to its copied data-symbol map.
No production mapping is changed. Three reachable target literals hold that
address, and the observed table operations establish four-byte rows containing
width byte, height byte and size halfword. The source deliberately declares an
unsized external array; no allocation length is invented. A direct typed ROM
literal triggered the existing plausibility check, so the retained version
uses the grounded named object. That binding needs independent production
approval before any future promotion.

Unmodified typed linking accounts for all eight BL relocations and three data
relocations, leaves no residual relocation or linker stub, and preserves the
whole emitted symbol. This is relocation evidence only. The source passes
plausibility; 19 target-compiler assertions verify the event/payload prefixes,
four-byte table row and eight-byte local descriptor layouts.

Retained local reproducer and logs:
`/home/user/.codex-work/ffta-ulw/0800620C-author/{check.py,check.log,official.log}`.

```sh
env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp \
  PATH=/home/user/armtc/root/usr/bin:$PATH \
  python3 /home/user/.codex-work/ffta-ulw/0800620C-author/check.py
```

The script builds inside its own disk-backed temporary directory and cleans
generated binaries. It reads the existing ROM rather than retaining a copy.

## Recovered interface and ordered behavior

The compatible callback is `u32(void *task, void *event, void *payload)`.
The first position is unused directly, not deleted; each normal return is
full-word zero. No unique original nominal type or registration provenance is
claimed. Entry evidence is the indexed prologue, closed local CFG and adjacent
boundaries, not a newly established incoming reference.

- Event zero captures the source-record pointer, copies the event count and
  ordered 16-byte records, rechecking live payload count with a u16 loop index,
  then initializes transparent/fill halfwords to `0x03FF`.
- Event one conditionally frees the buffer and clears its pointer. Event
  `0x100` checks cursor/count, selects a record and shape, stores changed size
  before free/allocation, and uses a fresh size for allocation. No allocation
  failure guard is invented.
- Byte and halfword modes first fill from the live payload fill field. Direct
  fill records then perform a second fill from the record; other records build
  two complete local descriptors and call `08005FC4`. Pointer/flag fields in
  the input records remain byte-decoded. The local descriptors are initialized
  native eight-byte views which the callee reads through its serialized byte
  interface. A u16 do-while fill count of zero wraps through 65,536 stores;
  it is not an empty operation.
- The actual installed clear callback receives `(payload+0x10,4)`, then event
  state becomes `0x101`. The common tail reloads state, cursor and record.
  Byte mode caps wrapped-u16 remaining size at `0x800`, queues half as many
  units, then reloads progress and size. Halfword mode increments progress
  before queueing the selected chunk.
- **Kind 3 does not mark completion at progress 3.** Instructions
  `0x08006574..0x08006596` select buffer+`0x1040` and destination+`0x1800`,
  then go directly to progress increment and queueing without setting r10.
  At progress 4 it queues zero source/destination and still does not complete.
  Only kind 0 and the final kind-1/kind-2 branches set halfword-mode completion.
  This corrects the earlier inventory prose claiming four-chunk completion.

The existing helper declarations are retained: pointer-return copy/allocation,
void free, six-position descriptor operation, seven-position BAC, and
four-position A98. BAC's opaque `ExtendedRequestNode` and A98's opaque
`TransferRecord` declarations agree with their active definitions. The embedded
request at payload+`0x14` is passed as allocated storage, not given a fabricated
common nominal struct. The observed records start at payload+`0x30`; the source
does not claim its 20-byte header prefix is the entire allocation.

## Focused execution evidence and limitations

The retained script runs **36 paired fixtures / 72 executions** of actual ROM
and the freshly compiled candidate. An independently expressed operation
oracle checks normalized helper calls (including both descriptor byte images),
ordered executed nonstack writes, complete synthetic EWRAM, queue head, zero
result, restored SP and r4-r11. Actual helpers executed are `081443FC`,
`08005FC4`, `08000BAC`, `08000A98`, the previously audited copied-clear body
and BX-r2 thunk. No BIOS service is reached; it is an explicit failure if one
is reached. Allocation/free are explicitly modeled boundaries, with caller
register clobbers and selected event/size/cursor mutations. Their model writes
are checked in final memory, not misrepresented as executed allocator code.

One fixture uses pristine ROM shape rows; the other 35 use explicitly synthetic
shape data, with the real clear pointer retained at its overlapping slot.
All RAM is synthetic. Mode-`0x20`/`0x30` probes are raw machine-selection
diagnostics, not evidence that the original shape table has 16 valid objects.
Cases cover initialization/free, exhausted cursor, both fill modes, descriptor
operation, allocation replacement and mutation, every halfword chunk branch,
kind-3 noncompletion, byte chunks, zero remaining and wrapped remaining.

Coverage is **518/522 target** and **535/542 candidate** instructions. The four
unexecuted target branches follow impossible negative/otherwise cases after
u16 or low-two-bit narrowing; all missing addresses for both bodies are listed
in the log. The test does not claim complete candidate branch coverage.

**RAM read traces differ in 17/36 fixtures.** Byte-mode fill/reload scheduling
and chunk paths differ; neither identical read footprints nor universal
behavioral equivalence is claimed. The read comparison excludes ROM literals,
ROM table fetches and local-stack accesses. Calls normalize descriptor stack
addresses to their eight initialized bytes. Local stack remnants are not part
of the full-EWRAM equality claim.

Ordinary execution requires valid aligned event/header storage, adequate live
record and buffer backing, initialized serialized pointer representations,
finite valid queues, and compatible effective types. Queued records and buffer
addresses can outlive the callback; consumer lifetime and allocation success
are separate obligations. Mixed nominal queue-node types, arbitrary aliases,
invalid pointers, zero-fill wrapping allocations, BIOS behavior, concurrency
and engine termination are not certified. Integer/pointer conversions use the
32-bit target representation. The recovery remains **Parked only**.
