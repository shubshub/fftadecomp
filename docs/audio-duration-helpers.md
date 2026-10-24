# Audio duration helpers

Two first-candidate natural C recoveries match their complete Thumb bodies:
`080DFE28` is 76 bytes / 30 reached instructions, and `080DFE74` is 68 bytes /
27 instructions. Each owns a middle and a trailing RAM-address literal. The
separate prologue at `080DFEB8` is not part of `080DFE74`; its old end incorrectly
included that adjacent code. The corrected indexes exclude it.

Both helpers take a low-eight-bit channel and unsigned low-sixteen-bit duration.
For nonzero duration they first call `08141500`, test its low byte, and calculate
`duration >> 4`, substituting one for a zero quotient. Channel one selects RAM
state `0200F2E0`; channel two selects `0200F320`; other channels still perform
the status query but do not dispatch a state operation. The getter returns zero
or two, not a normalized one-valued boolean.

The zero-duration paths differ: `080DFE28` calls `0814164C(channel)` without
querying status, whereas `080DFE74` returns without any call. Nonzero dispatch
uses `08145358` and `08145388`, respectively. The latter remains Parked, not
matched; direct-call validation is an ABI summary rather than a recursive
behavioral proof. Opaque state pointers identify genuine RAM bases without
inventing object layouts, allocation sizes or new data-symbol bindings.

Thirteen focused native cases cover `080DFE28` and twelve cover `080DFE74`,
including channel selection, unsigned duration boundaries, gating and call
order. Stubs compare the fixed pointers without dereferencing game RAM.
Separate target compilation proves complete-byte identity; native cases do not
prove downstream audio-engine behavior. Independent review replays each frozen
target candidate once without repeating the native campaigns.

## Preserved curve-sampling wrapper

`Parked/080E06A4/` retains one natural signed64 curve-sampling wrapper. Both
complete bodies have 138 bytes and 65 reached instructions, but one commuted
ADD encoding differs at `080E06C8`: 136 byte positions and 64 instructions
agree. Neither that near-match nor external alignment earns match credit.
The source was not rewritten to chase operand order, and no native campaign
was run for this nonmatch.

The wrapper preserves unsigned-halfword allocation-stride truncation and a
do-while sample loop: a zero sample count still writes one sample. It uses the
Parked `08008480` coefficient routine and signed64 `080086D0` evaluator through
typed call contracts, not recursive arithmetic or termination proofs. The
Parked README records the full discrepancy and numerical/storage preconditions.

## Constructor verification boundary

Nearby task constructors pass local descriptors through `08005B6C` to allocator
`08005954`. Current combined function-address/buffer verification rejects its
runtime thunks. A separate read-only probe with the unchanged base buffer proof
also rejects the descriptor block copy. The later callback receives an
allocator-local descriptor; constructors with embedded local parameter pointers
add another lifetime obligation. Removing only the thunk rejection would not
establish alias-preserving copies, callback identity or non-retention.

These are bounded verifier obligations, not evidence that the project or these
functions are impossible to decompile. No guard was weakened and no constructor
was promoted to a match. The smallest proposed next evidence slice is the
scalar-field constructor `080DFD68`, including allocation/list separation and
the phase-zero effects of its callback.

## Adjacent task predicates

Two independently qualified entries restore previously omitted code. Both
have separate prologues, a single getter call and balanced returns; neither
is reached by fallthrough from its predecessor. `080DFDD8` owns 28 bytes and
11 instructions, including its trailing comparison literal at `080DFDF0`.
The preceding constructor `080DFD8C` therefore ends at `080DFDD8`, with 76
bytes and 35 instructions. `080DFEB8` owns 20 bytes and nine instructions,
without a pool; the already-correct `080DFE74` boundary remains unchanged.

`080DFDD8` matches its first natural candidate and one independent replay.
It forwards an object pointer to `08005BAC` and tests the returned halfword
against `0x0101`. Six sanitizer-backed cases cover the predicate, pointer
forwarding, one-call behavior and absence of writes. Its nominal original
return typedef remains unknown; the recovered `u8` result is canonical 0/1.

`Parked/080DFEB8/` preserves the first candidate for normalization of the
full `08005BB0` result. It emits 16 bytes instead of the complete 20-byte
target and receives no match credit. Its README distinguishes decoded ELF
summaries from unavailable raw images and the inferred short-symbol failure
from an uncaptured diagnostic. No source retry or native campaign followed.

Both getters require a valid readable halfword at object+0x14. The bounded
36 KiB incoming-reference scan found no callers, not global absence. New
index entries establish local ownership, not exhaustive game coverage or
runtime reachability. Constructor proof work remains separate.

## Forwarding wrapper and second normalized predicate

`080DFECC` matches its first natural candidate and independent replay: ten
bytes and four instructions forward the unchanged pointer to `08005B58`.
The wrapper has a void result; restoring the return address through r0 does
not return a task pointer. Its complete symbol excludes the two alignment
bytes before `080DFED8`. Four stub-backed native forwarding cases and four
type/width assertions supplement, rather than replace, the target-byte proof.

`Parked/080E07D8/` preserves a second full-word normalization wrapper around
`08005BB0`. Its single candidate emits 16 bytes and seven instructions instead
of the target's 20 bytes and nine instructions. The compiler omits the explicit
zero assignment and unconditional branch. This attempt retains both raw ELF
images and the actual short-symbol diagnostic with process exit 1; it earns
no match credit. No source revision or native campaign followed the nonmatch.

Both newly indexed entries have independently checked local boundaries.
`080E07EC` begins a separate body and is not padding owned by `080E07D8`.
The bounded incoming-pattern scan is not an exhaustive caller census. These
recoveries do not establish task allocation, lifetime or downstream behavior.

## Conditional task release

`080DFED8` and `080E07F8` each own 44 bytes and 20 instructions, without a
literal pool or local frame. The corrected instruction counts replace the
provisional halfword counts of 22; their existing endpoints are unchanged.

Both return null immediately for a null input. Otherwise they query
`08005BB0`: a false result returns the original pointer, while a true result
calls `08005B58` once and returns null. Their natural inline normalization
helper follows the already matched `080DBAB8` idiom identified before either
candidate was compiled. The original helper identity and nominal types remain
unknown. There is no dereference of the task after the release call.

The first frozen candidates reproduce both complete bodies. Seven native
branch/forwarding/call-order cases and four type/width assertions cover
`080DFED8`; thirteen finite cases cover `080E07F8`. Stub results include values
with a zero low byte but nonzero full word, so the predicate must not narrow
the callee result before normalization. These tests do not establish recursive
destruction, manager validity or hidden callback effects.

## State callback inventory

Two larger neighboring entries are single complete bodies, not collections
of short functions. `080DFF04` owns 136 bytes and 65 instructions, with no
pool or alignment. `080E0824` owns 616 bytes: 566 instruction bytes, 44 owned
literal bytes and six internal alignment bytes, reaching 253 instructions.
Their indexed endpoints remain unchanged; the instruction counts and stale
14-byte/24-byte symbol sizes are corrected. No new entry is inferred.

`Parked/080DFF04/` preserves its sole natural callback candidate, which emits
140 bytes and 67 instructions. An extra state-pointer copy and separate phase
store prevent a match. The canonical comparison displays four bytes beyond
the true target; those following-function bytes are excluded from ownership.
Complete ELF images, the actual exit-1 diagnostic and the exact discrepancy
are retained. There was no source retry or native campaign.

In phase `0x100`, this callback waits while the status byte is nonzero; zero
allows conditional task creation. It reloads and increments the phase after
the calls. Skipped creation leaves the existing task field unchanged. Its
compatible types do not establish original names, registration, initialization
or scheduler lifetime guarantees. Neither callback earns new match credit.

## Curve callback inventory

`080DFF8C` owns 690 bytes and 337 instructions: 684 instruction bytes, one
four-byte literal and two internal alignment bytes. `080E0240` owns 440 bytes
and 210 instructions: 434 instruction bytes, one four-byte literal and two
internal alignment bytes. Their existing endpoints remain unchanged. Corrected
instruction counts and symbol sizes do not introduce entries or match credit.

The sole natural candidates emit 654 and 442 bytes respectively, so both remain
nonmatches. DFF8C stops at the short-symbol gate; E0240 stops at the buffer
profile's exact-span gate. Neither canonical invocation produces a match report.
Each compiled section also has two external alignment bytes, excluded from
its function symbol and from target ownership. Raw ELF evidence and the first
candidates are retained without compiler-output-driven retries or native runs.

Both callbacks stage fixed-point curve values and call the Parked sampler
`080E06A4`; E0240 also uses the matched interpolation helpers for optional
linear channels. DFF8C's compatible `u16(s16, s16)` declaration for `08141860`
is supported by the complete SVC wrapper and an existing matched caller, not
by a proof of interrupt effects. Signed narrowing, count-zero coordinates and
E0240's do-while stores are preserved rather than repaired. Buffer validity,
sampler preconditions and scheduler lifetimes remain external obligations.

## Additional release wrappers

Three existing entries have complete code-only bodies:

| Entry | Bytes | Instructions | Behavior |
| --- | ---: | ---: | --- |
| `080E051C` | 34 | 15 | Return the original pointer, or release it and return null |
| `080E0540` | 48 | 23 | Release each nonnull array element, then clear its slot |
| `080E05DC` | 44 | 20 | Conditional release with explicit predicate normalization |

The conditional wrappers skip calls for null input and test the full-word
`08005BB0` result. E05DC's inline normalization is grounded before compilation
in the neighboring helper pattern; it does not narrow the predicate to a byte.
E0540 uses unsigned16 count and index, unlike the unsigned8 DBA88 analogue.
It clears the selected slot after `08005B58` returns even if that call changes
the slot's contents. Zero count performs no array access.

Each first candidate matches its complete owned body. Focused native evidence
covers null inputs, nonzero full-word predicates, pointer forwarding and call
order, plus mixed array slots, post-call clearing and counts 257 and 65535.
These finite stubbed checks do not prove recursive release effects or scheduler
lifetimes. Index counts are corrected and two missing symbol rows restored;
no new function entry or endpoint is inferred for these three wrappers.

## Aggregate release and constructor ownership

`080E0570` is a 76-byte, 36-instruction array wrapper. It uses unsigned16 count
and index and tests the full-word predicate result. A false predicate records
an aggregate zero and scanning continues. A true predicate causes a fresh
load of the selected slot, release of that current pointer, and then clearing
of the slot. Zero count returns one without accessing the array. Calls can
repopulate earlier slots, so a true result does not prove global emptiness.
The first candidate and independent replay match all 76 bytes. Eleven finite
native cases exercise ordering, slot replacement, full-word truth and count
256; they do not prove recursive release behavior or object lifetimes.

The constructor at `080E03F8` owns 292 bytes through `080E051C`, rather than
the former 278-byte span ending at `080E050E`. Three reached trailing literal
words and their alignment account for the additional 14 bytes. Its complete
partition is 236 instruction bytes, 52 data bytes and four alignment bytes,
with 108 instructions. The seven-case switch has two separately loaded scalar
mask words before its table-pointer literal; the default switch profile does
not recognize that placement. The opt-in `two-constants-v2` profile supports
this layout only within its separately bounded, unframed shapes. The separate
`two-constants-frame-v1` profile also supports fixed scalar frames with direct
SP word accesses, but rejects SP-address materialization and buffer, function
literal and runtime-thunk composition. Neither profile combines the
constructor's buffer, callback and allocator contracts by assumption. Those
remain separate proof obligations. This inventory correction creates no new
entry, C source or match credit for the constructor.

Two further existing entries have independently checked complete ownership:
`080E0A8C` contains 470 instruction bytes, 36 literal bytes and two alignment
bytes in its 508-byte span (208 instructions); `080E0CC4` contains 448
instruction bytes, 16 literal bytes and four alignment bytes in its 468-byte
span (209 instructions). Their endpoints remain unchanged. The former uses a
four-byte scalar outgoing-argument frame; the latter has no local frame and
has a concrete scheduler registration with a 44-byte payload. Their compatible
callee declarations and structural checks permit natural-source attempts, not
match predictions or recursive runtime proofs. Discarded RAM-byte loads do
not establish original bitfield types or justify artificial reads.

Their sole natural candidates are nonmatches: E0A8C emits 510 owned bytes
against 508, while E0CC4 emits 438 against 468. Both retain complete original
and linked ELF evidence, with external section filler excluded. E0A8C's
canonical diagnostic compares a compiler-sized ROM window extending two bytes
past the approved endpoint; that diagnostic does not expand target ownership.
Neither candidate was revised from compiler output or subjected to a native
campaign. Both are preserved in Parked with zero match credit.

## Registered countdown callback

`080E0C88` restores a previously unindexed 60-byte, 30-instruction callback
between `080E0A8C` and `080E0CC4`. Its separate prologue and balanced return
own the complete interval, with no literal pool, relocations or alignment
credit. Table slot `08395290` contains its Thumb pointer `080E0C89` and a
four-byte payload size. Selector `0x158` in `080D3508` selects that registration;
the call at `080D35AC` passes it to `08005954`, whose callback path invokes
the stored pointer through `08142250`. This establishes an entry, not an
observed runtime occurrence or a recursive allocator proof.

Phase zero narrows the descriptor's duration word at offset eight to the
payload's unsigned16 countdown. Phase `0x100` decrements a nonzero countdown
and sets phase two when it is zero afterward, including initially zero.
Phase one and unhandled phases leave the fields unchanged; every return is
full-word zero. Unknown descriptor and payload bytes remain unmodified.

The first frozen candidate and one independent canonical replay match all
60 bytes. Twenty-one finite native checks cover duration truncation, countdown
boundaries, inactive phases and a lifecycle sequence, with layout and field
preservation assertions. They do not prove arbitrary pointer validity or
scheduler lifetimes. The new index entry increases the provisional function
denominator by one; this is not an exhaustive whole-game inventory.

## Registered multi-child callbacks

Three existing entries have independently checked complete ownership and
registration-backed compatible callback contracts:

| Entry | Bytes | Instructions | Registered payload bytes |
| --- | ---: | ---: | ---: |
| `080E28C4` | 256 | 122 | 56 |
| `080E2FA4` | 230 | 96 | 48 |
| `080E3AC8` | 322 | 141 | 48 |

The first two registrations use IDs `0x15B` and `0x160` in `080D3508`, selecting
table rows `083952A8` and `083952D0`. The third is passed to `08005B6C` at
`080E3E0A` within `080E3C0C`. These are real conditional registration paths,
not observations of gameplay execution or proofs of allocator lifetimes.
Each callback receives full task, descriptor and payload pointers and returns
full-word zero. Instruction counts and stale symbol lengths are corrected;
their endpoints remain unchanged, excluding external alignment after E2FA4
and E3AC8. Inventory qualification alone earns no compiled match credit.

E28C4 creates and waits for one child before processing eight object slots.
For each nonnull slot, it applies the negated signed-low16 rank adjustment,
reloads the slot after that call and stores the cleanup helper's result.
Newly completed slots contribute to a byte count. A second pass subtracts
that count from the halfword ranks, stores the wrapped low16 result, then
clears ranks whose wrapped sign bit is set. This is not an unlimited-width
subtraction followed by a clamp. Phase advancement reloads state after calls.

E2FA4 waits for an initial child, obtains signed-halfword coordinates and
creates three more children in a fixed order. The final phase polls its first
child and only then the second; it does not poll the third child stored at
payload offset `0x2C`. E3AC8 similarly creates three children, but polls the
first two in successive phases. Its table lookups use an unchecked byte
selector, and its flags retain the observed byte/halfword widths. Its DD5A8
dependency remains a Parked nonmatch, not a recursively verified helper.

E2FA4 and E3AC8 use 16-byte outgoing-argument frames. Their structural
checks rely on ordinary callee ABI summaries; nested constructor copies,
callback escape and scheduler lifetime contracts are not thereby proved.
Observed table bases do not establish complete object bounds or justify
invented named-data bindings.

The first frozen E2FA4 candidate and one independent canonical replay match
all 230 owned bytes and 96 instructions, including nine typed direct calls.
Its 232-byte compiled text
section ends in an external `c046` halfword where the ROM has `0000`; neither
external halfword belongs to the function or receives match credit. Sixteen
finite native cases check phase dispatch, call order, signed coordinates,
post-call reloads, short-circuit polling and preservation of the unpolled
child. Separate 32-bit layout assertions check field offsets and payload
size. Host stubs do not establish actual callee safety or scheduler lifetimes.

The unchanged first E28C4 and E3AC8 candidates are nonmatches. E28C4 emits
260 bytes and 121 instructions against 256 bytes and 122 instructions;
its compiler-sized aligned diagnostic includes four bytes outside ownership.
E3AC8 emits 314 bytes and 139 instructions against 322 bytes and 141
instructions. Its standalone plausibility check also reports five suspect
numeric ROM pointer initializers; observed table bases do not waive that
finding. Neither candidate receives match credit, source retries or a native
test campaign. Complete original and linked ELF evidence is retained for
both, with external section alignment excluded from the owned comparison.

## Interior continuation ownership

A separate inventory review retires this duplicate owning text-index row:

```text
080E30E0 080E317C 156 78 call
```

The containing callback E308C owns 240 bytes through E317C: 222 code bytes,
16 referenced literal bytes and two alignment bytes, with 102 reached
instructions. Selector `0x161` registers it from table row `083952D8` with a
32-byte payload. E30E0 is its post-call continuation after E30DC calls DE10C.
The reached eleven-instruction suffix uses inherited r5/r6 and restores the
containing callback's 40-byte saved/local stack context. It is not a separate
ordinary-ABI function. Removing the duplicate row changes no matched source
span or JSON function denominator and earns no match credit. E308C's separate
buffer/callee proof obligations remain unresolved.

One raw Thumb BL encoding at `08314AC6` targets E30E0. Its surrounding legacy
function classification conflicts with the generated data layout, and current
bounded decoding does not establish an executable caller or a data consumer.
That witness remains unresolved: this ownership correction does not disprove
a custom inherited-frame entry, computed references or alternate instruction
contexts. The historical row is retained here rather than erased from the
inventory's provenance.

## Following registered effect callbacks

Three further existing envelopes have independently reviewed complete ownership
and reached callback registrations through `08005B6C`:

| Entry | Bytes | Instructions | Registered payload bytes |
| --- | ---: | ---: | ---: |
| `080E4844` | 464 | 192 | 44 |
| `080E5310` | 296 | 114 | 44 |
| `080E5438` | 142 | 65 | 20 |

E4A14 registers E4844 at E4AF4. E54C8 and E5694 register E5310 at E55B4 and
E56A0; E54C8 also registers E5438 at E5646. These are reached local setups,
not whole-constructor admission, observed gameplay or allocator/lifetime
proofs. Each receives full task, descriptor and payload pointers and returns
full-word zero. Counts and stale symbol sizes change without endpoint changes;
the halfword after E5438 at E54C6 remains external alignment.

E4844 creates a selector-dependent effect sequence. Its unsigned16 countdown
decrements before testing, so zero wraps rather than triggering immediately.
The final polling phase remembers whether one child was nonnull before its
poll; only that transition clears the observed halfword RAM-shadow mask.
Subsequent polls short-circuit in order, and the last created child is not
polled. Table bounds and valid selectors remain unproved.

E5310 creates a fixed sequence without advancing its initialization phase
locally. After its first three polls all return null, it clears the RAM-shadow
mask on every reached polling tick, then polls the remaining two children.
The D9B64 busy path has an observed side effect and is not treated as a pure
predicate. Its last created child is also not polled here. Forwarded embedded
addresses do not establish original array types or safe nested storage.

E5438 copies a wrapper pointer and narrowed selector, obtains signed-halfword
coordinates, creates one child with selector-derived flags, then waits for
the nullable cleanup result. Phase advancement reloads state after effects.
Unknown storage, external initialization and scheduler lifetimes remain
unproved; no extra guards, initialization or cleanup are inferred. These
inventory corrections alone earn no compiled match credit.

The first E4844 candidate emits 480 bytes and 203 reached instructions against
464 bytes and 192 instructions. Only 18 owned byte positions agree; its
compiler-sized aligned diagnostic includes 16 bytes belonging to the next
function. Four numeric-ROM initializer findings leave the canonical source
label IMPLAUSIBLE, without a waiver. E5310's first candidate is plausible
but differs at 265 of its 296 byte positions; its reached instruction count
is 117 rather than 114. Equal symbol sizes and an aligned display do not
establish a match. Both unchanged candidates are preserved in Parked after
independent preservation reviews, with complete original/linked ELF evidence,
no source retries or native campaigns, and zero compiled match credit.

E5438's first frozen candidate and one independent canonical replay match
all 142 owned bytes and 65 instructions, including three typed calls.
The final two bytes of its 144-byte compiled text section are external
`c046` alignment and are not credited. Sixteen finite native cases exercise
phase dispatch, selector narrowing, coordinate outputs, flags, post-call
phase reloads and nullable completion; separate 32-bit assertions verify
the observed field layout and 20-byte payload. These checks use host stubs,
not a recursive proof of the scheduler, callees or object lifetimes.

## Coordinate-output and conditional-child callbacks

Three further complete envelopes have independently reviewed ownership and
reached registrations through `08005B6C`. Counts and stale symbol sizes are
corrected without changing endpoints or adding entries:

| Entry | Bytes | Instructions | Registered payload bytes |
| --- | ---: | ---: | ---: |
| `080E6714` | 518 | 208 | 56 |
| `080E7130` | 388 | 170 | 36 |
| `080E75B8` | 234 | 103 | 32 |

E691C registers E6714 at E69FC, E72B4 registers E7130 at E754A, and E76A4
registers E75B8 at E7AB2. These local paths support the three-pointer callback
ABI and full-word zero return, not gameplay occurrence, constructor admission
or descriptor-copy and allocator lifetime guarantees. The ordinary framed
profile accepts the complete ROM bodies; that alone does not admit C sources.
E6714 and E75B8 exclude the two alignment bytes after their owned endpoints.

DD748's fourth argument is an optional signed-halfword coordinate-output
pointer, not a scalar mode. It forwards the arguments to DD760 with a fifth
argument of -2. A nonnull fourth pointer selects DBD5C, which copies three
underlying coordinate halfwords; a null pointer selects DBDC8's transformed
two-coordinate output through 1C984. DD760 subsequently calls DE268 on the
-2 path, so DD748 is not a pure getter. E7130 passes its third coordinate
field; E6714 and E75B8 pass null. Earlier zero-only call sites do not establish
the nonzero argument type, nor does the wrapper check prove null-safe access.

E6714 creates a variant-dependent multi-child sequence. It remembers the prior
nonnull state of one child before polling and performs resource/array cleanup
and RAM-shadow mask clearing only on that child's nonnull-to-null transition.
Later polls short-circuit, phase updates reload after effects, and the record
child is not polled. Observed table entries do not establish a variant bound.

E7130 creates two resource objects and conditionally creates an auxiliary
child. Its low-byte predicate tests, signed-halfword comparison and coordinate
reloads are distinct operations. The false branch does not assign payload+0x18
before its later poll; external initialization is not proved.
The final record child is not polled. E75B8 similarly leaves payload+0x14 and
+0x1C unchanged when its creation predicate is false, but later polls +0x14
through D6134, which has no local null guard. These are retained preconditions,
not permission to add initialization, skip polling or invent lifetime proofs.

An independent E6590 ownership review also corrects its stale endpoint to
E6714: the reached load at E66F4 owns the mask literal at [E6710,E6714).
Its complete 388-byte envelope contains 166 instructions, 24 literal bytes
and four internal alignment bytes. Only its three existing metadata rows
change; the E6714 successor remains separate. No incoming E6590 reference was
found in the bounded survey, which is not a global absence claim or source
readiness evidence. This correction earns no compiled match credit.

The first frozen candidates for all three callbacks are plausible nonmatches:

| Entry | Compiled bytes / instructions | Equal / different owned byte positions | Excess symbol bytes |
| --- | ---: | ---: | ---: |
| `080E6714` | 528 / 215 | 22 / 496 | 10 |
| `080E7130` | 400 / 175 | 28 / 360 | 12 |
| `080E75B8` | 250 / 111 | 13 / 221 | 16 |

These are position-wise comparisons of complete owned target envelopes, not
longest-common-subsequence scores or sampled disassembly counts. External
alignment and diagnostic bytes beyond each target receive no match credit.
Each unchanged C/README pair is preserved in Parked after an independent
preservation review, with complete original and linked ELF evidence retained
locally. No source retries or native campaigns were run. None adds compiled
match credit or establishes exhaustive coverage.

## Selector-driven resource and child polling

Three additional callbacks have independently reviewed complete ownership,
compatible three-pointer ABIs and reached registrations through `08005B6C`:

| Entry | Bytes | Instructions | Registered payload bytes |
| --- | ---: | ---: | ---: |
| `080E7D20` | 556 | 227 | 52 |
| `080E8158` | 556 | 231 | 52 |
| `080E8590` | 560 | 231 | 52 |

Their registration calls are E80F0, E8528 and E89AC respectively. These are
reached local paths, not observed gameplay or admission of the constructors.
Counts and stale symbol sizes are corrected without changing endpoints or
adding entries. All three complete ROM bodies pass the ordinary framed
profile; this is not source admission or compiled match credit.

Phase zero narrows descriptor selector/flags into bytes, obtains transformed
coordinate outputs through DD748 and retains the underlying pointer. It does
not advance the phase or initialize later resource/child slots. The registered
52-byte payload does not prove initialization, selector bounds or lifetimes.
Forwarding an address at payload+0x14 does not establish its original type.

E7D20 short-circuits its polling phase in resource, coordinate child, sequence
and two-slot-helper order. E8158 and E8590 instead poll every stage and
accumulate an all-finished flag, even when an earlier result is nonnull.
RAM-shadow mask clearing requires an old-nonnull/new-null resource transition;
E7D20 reloads the resource after that effect before deciding to continue.
The two-slot helper's low-byte result differs from full-word pointer tests.

E8158 conditionally subtracts eight from its stored signed-halfword y after
testing underlying word+0x30 bit 15. Its creation phase adds a selector-table
halfword, narrows and sign-extends only the y passed to D49FC; D6098 receives
the stored y. E8590 passes constant 41 to D4724, unlike the other callbacks'
selector-table argument. Creation order, fresh selector/flag loads and phase
reloads after effects remain significant. All three later poll wrapper-child
+0x2C and enter phase two on null; record-child+0x30 is not polled here.

An independent E87C0 ownership review extends its stale endpoint from E8A2C
to E8A30. The reached load at E8A0E owns the trailing 00007FFF mask literal;
its complete 624-byte envelope contains 266 instructions, 52 literal bytes
and eight internal alignment bytes. Only its three existing metadata rows
change. E8A30 remains a separately owned successor with its own registration.
The bounded survey found no incoming E87C0 reference, not global absence.
This repair grants neither source readiness nor constructor admission.

All three first frozen candidates remain nonmatches after separate independent
preservation reviews:

| Entry | Compiled bytes / instructions | Equal / different / absent owned bytes | Excess symbol bytes |
| --- | ---: | ---: | ---: |
| `080E7D20` | 536 / 223 | 155 / 381 / 20 | 0 |
| `080E8158` | 566 / 241 | 51 / 505 / 0 | 10 |
| `080E8590` | 558 / 233 | 164 / 394 / 2 | 0 |

These are positional comparisons of complete owned target envelopes, not
aligned diagnostic scores. E7D20 and E8590 complete typed linking and local
structural validation before the short-symbol gate rejects them; canonical
report generation and plausibility are not reached. Separate read-only
plausibility checks report ten unwaived numeric-ROM initializer findings for
E7D20 and none for E8590. E8158 reaches canonical reporting with one unwaived
numeric-ROM initializer finding and an IMPLAUSIBLE classification.

The unchanged C/README pairs are preserved in Parked. Complete original and
linked ELF evidence remains local. External alignment, including E8590's two
bytes after its shorter symbol, receives no credit; matching section lengths
cannot fill missing owned bytes. No source retries or native campaigns were
run, and none adds compiled match credit. No exhaustive inventory or
whole-game completion is claimed.
