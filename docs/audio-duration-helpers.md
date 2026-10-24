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
