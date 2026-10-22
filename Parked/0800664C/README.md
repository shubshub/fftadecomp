# 0800664C — two-channel transition callback, not byte-matched

This is an honest **Parked recovery only**. The first natural switch compiles
to one 208-byte function, shorter than the complete 212-byte target. Frozen
`4847c93` verification rejects it with
`compiled symbol is shorter than the indexed span: 208 < 212`.
There is no active source or match report, and no MATCH or cached-replay claim.

## Complete body and remaining difference

The complete target is `[0x0800664C,0x08006720)`: **212 bytes / 97 instructions**.
Code occupies `[0x0800664C,0x0800671A)`, followed by internal zero alignment
`[0x0800671A,0x0800671C)` and the required word `0x03000940` at `0x0800671C`.
The next independent prologue starts at `0x08006720`; none of it is included.

The retained candidate has exactly one **208-byte FUNC and .text**, containing
96 instructions, no unresolved relocation, and a literal at `0x0800666C`.
Its code occupies `[0x0800664C,0x0800666C)` and
`[0x08006670,0x0800671C)` with no internal alignment gap. Separate diagnostic
typed linking resolves all six ordinary BLs to the three audited helper
entries; the raw local CFG and individual-source plausibility checks pass.
Those diagnostics do not override the official full-symbol rejection.

The proper positional comparison is **16/212 equal bytes and 3/97 equal
same-address instructions**, not a match percentage or a candidate-prefix
comparison. Important differences are:

- The candidate hoists the output-base literal into r8 before dispatch,
  adds an r8 save/restore, and places its pool inside the dispatch sequence.
  The target loads the shared trailing literal only on output-writing paths.
- The target performs four old-output byte reads at `0x08006696`,
  `0x0800669E`, `0x080066EC`, and `0x080066F4` whose results are discarded.
  The natural assignments omit them. These are real read-footprint differences.
- The target sign-extends the duration halfword before each stacked fifth
  argument. The compatible u16 helper declaration causes the candidate to
  zero-extend it instead. Both pass the same consumed low16 pattern, but the
  complete stacked word and instruction sequences differ for negative duration.
- Registers, branch displacements, BL displacements and epilogue placement
  consequently differ throughout the body.

One natural switch form was retained. Its local coordinate fields were made
u16 to agree with the completed `TransitionState` recovery in
`Parked/08007620`; this did not repair the 208-byte result. No incompatible
signed helper prototype, volatile access, unused read, synthetic bitfield,
register constraint, lifetime manipulation, artificial branch or compiler
flag sweep was used to reproduce the missing instructions. No claim is made
that every possible natural source has been exhausted.

## Compatible interface and observed layout

The compatible callback interface is
`u32(void *task, TransitionEvent *event, TransitionPayload *payload)`.
Incoming r0 is unused, but its callback position is retained; r1/r2 supply
the event and payload. There are no incoming stack arguments. Every normal
return produces full-word zero. This does not uniquely establish the original
nominal callback types, and the inventory established structural entry rather
than a particular inbound reference.

Fourteen target-agbcc assertions establish the retained local views:

- TransitionState: 24 bytes, alignment four, eleven halfwords at
  `0x00..0x14`; the final remaining-count field is at `0x14`.
- TransitionEvent: 28 bytes; state at zero, initial/target packed halfwords
  at `0x14`/`0x16`, signed duration at `0x18`.
- TransitionPayload: 56 bytes; four endpoint bytes at zero through three,
  duration at four, embedded states at `0x08` and `0x20`.
- TransitionOutput: 80-byte observed view, with bytes at `0x4C`/`0x4D`;
  its fixed base `0x03000940` comes directly from the ROM literal.

These are compatible views of observed offsets and natural compiler layout,
not recovered allocation bounds or proof of the original typedefs. Source
use requires appropriate live, aligned typed backing. The public helper
interfaces are `void(void*,u16,u16,u16,u16)`, `void(void*)`, and
`u32(const void*)` for 07620, 076F4 and 07894 respectively. Existing helpers
have different private views behind void pointers; this recovery does not
claim a source-wide portable effective-type proof across every helper.

## Ordered behavior

State zero copies the high then low byte of each event endpoint halfword into
the payload, preserving the separate live halfword reads, then copies duration.
State one and unhandled states return zero without these effects.

State `0x100` writes both initial bytes to `0x0300098C`/`0x0300098D`, initializes
each embedded state with its initial byte, zero, target byte and low16 duration,
reloads/increments the event state, then falls through to the update work.
State `0x101` begins directly at that work: advance both objects in order,
publish their live low first-coordinate bytes, and short-circuit the two
full-word completion predicates. Both nonzero predicates store event state two.
Calls are ordinary mutating boundaries; payload/event reloads are not replaced
by purity assumptions. No null or positive-duration guard is added.

The actual initialization helper wraps endpoint differences to signed16 before
its sign decision. Its zero-second-delta path immediately selects the target
first coordinate. The actual advancement helper uses signed remaining/error
tests and may loop forever on malformed positive-count, zero-delta state.
Target-specific signed-halfword conversion and arithmetic right shift remain
explicit domain assumptions, not portable all-compiler claims.

## Fresh bounded evidence

The self-cleaning reproducer builds the retained source in an isolated root
with current headers/maps and a ROM symlink, checks complete ELF/link/CFG/layout
facts, and executes **24 returning pairs / 48 executions plus one deliberately
bounded nonreturning pair / two executions**. All three actual ROM helper
bodies execute, without stubs or modeled callbacks. A separately expressed
operation oracle predicts the ordered calls, data reads/writes and final state.

The returning fixtures cover all callback states, positive/negative/zero and
signed-boundary durations, ascending/descending/equal endpoints, completion
short-circuit outcomes, multiple error-loop iterations and half-delta correction.
They cover 96/97 target and 95/96 candidate caller instructions. The only
unexecuted instructions are the target branch at `0x08006662` and its candidate
counterpart `0x0800666A`: reaching either would require the zero-extended event
state to be less than one but neither zero nor one. No impossible input was
fabricated to claim coverage. The real helpers cover all **58/68/10** instructions.
There are 69 real helper entries per returning side, plus the first step entry
on each nonreturning diagnostic side. Peak stack use is 52 target versus
56 candidate bytes because of the extra candidate save.

Every returning execution agrees with its own exact ordered data/call oracle,
and paired executions agree on writes, consumed low16 call arguments, final
mapped nonstack RAM, r4-r11, SP and return control. **15/24 returning pairs have
different nonstack read traces**: four omitted old-output reads on `0x100`,
two on `0x101`. Two pairs have different raw fifth-argument words. All 24 have
different literal/stack-inclusive read traces. These differences are measured,
not erased into a general trace-equivalence claim.

The malformed zero-delta fixture runs a 1,500-instruction prefix on each side
and remains inside the real helper's subtraction loop, with no later helper
call or return. It is a machine-only diagnostic, not a valid-state termination
guarantee. The other fixtures use synthetic, aligned, separately backed event,
payload and output storage; arbitrary overlap, effective types, object lifetime,
concurrent mutation and all-domain termination are not proved.

```sh
env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp \
  PATH=/home/user/armtc/root/usr/bin:$PATH python3 \
  /home/user/.codex-work/ffta-ulw/0800664C-author/check.py
```

Only the small script and text log remain in that owned scratch directory;
temporary compiler objects and binaries self-clean. Root owns release and
independent review.

- Source SHA256: `1dcfa6b61a105f2985a00c124b61118097bc3046832b80b351e99df1850cba6d`
- Target SHA256: `18022186202b4e95605547d9e486002bbff5eca0a7202cad74799bb973997a79`
- Candidate SHA256: `bb9140071377e060a4c3a01b09135fce9a3529dc57363d0abe4ccf6b8da891e2`
