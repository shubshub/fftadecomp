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
the phase-zero effects of its callback. Adjacent-entry proposals
remain separate inventory work and receive no compiled-byte credit here.
