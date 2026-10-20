# 080CFAD4: record countdown recovery, not a match

## Disposition and full-symbol evidence

This natural-C recovery is parked, not byte-identical. There is no active
source or successful match report. No inherent unmatchability or original
source reconstruction is claimed.

- Complete ROM function: `[0x080CFAD4,0x080CFCD0)`, 508 bytes / 228
  instructions. Its 486 code bytes occupy `[0x080CFAD4,0x080CFBBA)`,
  `[0x080CFBC8,0x080CFC04)` and `[0x080CFC0C,0x080CFCD0)`.
- The zero halfword at `0x080CFBBA` is internal alignment. Three literal
  words follow at `0x080CFBBC` through `0x080CFBC7`; two more are at
  `0x080CFC04` and `0x080CFC08`. All five words are part of the function.
- ROM SHA-256:
  `c740520dff1c7e0a1638d5990b6e25091e77b2ca6120b232aa5ac292c9a7f4e8`.
- Retained compiler-only linked function: `[0x080CFAD4,0x080CFCB2)`,
  478 bytes / 213 instructions, with exactly one code-defined `STT_FUNC`.
  The ELF `.text` is 480 bytes; its final `c046` NOP lies outside the symbol.
- Linked candidate SHA-256:
  `023e4b96530ef73b2b941eaf4eb043a10fbfc5a5cab3b80c116155278240252d`.
- There are 52 equal same-position bytes, 426 differing overlapping bytes
  and 30 target bytes absent from the candidate. Fourteen instructions are
  equal at their original addresses. These are diagnostic counts, not a
  normalized or partial MATCH.

Both bodies save 32 bytes of registers; the retained candidate allocates eight
additional stack bytes instead of the ROM's twelve. Other differences include
register allocation, loop/update temporaries, byte-decrement materialization,
pool placement and local scalar preservation around calls. The candidate has
456 code bytes, five literal words and one internal zero halfword.

## Bounded attempts and verifier limitation

Two ordinary source representations were tried with unchanged
`agbcc -mthumb-interwork -O2`. The first used an indexed initial count scan,
a `u16` counter-index local and a nonzero-counter-first branch. It emitted
478 bytes / 213 instructions with a twelve-byte local frame. The retained
form reuses a record cursor, keeps index arithmetic full-word until the typed
helper-call boundary and puts the zero-counter branch first; it also emits
478 bytes / 213 instructions. No optimizer flags, dummy operations, forced
registers, artificial storage, inline helpers, assembly or volatile accesses
were introduced.

The frozen `kit-reviewed-2e2a664` official matcher rejects a compiler-generated
signed-runtime relocation with `call target must be an undefined addressed
function`. This source uses natural `/` and `%`, not named runtime calls to
evade that restriction. Both `__divsi3` and `__modsi3` are generated. No toolkit
extension was requested because the actual bytes already differ.

For diagnostic comparison only, the preprocessed source was compiled and
assembled normally, then scratch-only typed linker definitions bound
`__divsi3` to audited Thumb entry `0x081426B8`, `__modsi3` to `0x08142950`,
the ordinary addressed helpers to their actual entries, `_call_via_r2` to
`0x0814224C`, and named data to the current mappings. Linking used the usual
fixed-address script, no relaxation, no undefined symbols and no permitted
linker veneers. Raw fixed-frame CFG checking accepted all 213 candidate
instructions and 15 direct BL sites. Strict scoped plausibility passed.
Neither scratch binding nor raw CFG acceptance is official relocation proof,
byte equality or saved-report replay.

## Recovered interface and effects

The compatible interface is `u8(u8 *output, u8 clear_count)`. The first action
calls the actual copied clear callback with the low byte of `clear_count`.
This argument is a clear length, not output capacity. Up to 24 later bytes
may be appended even when the clear length is zero or one. Required writable
storage must cover both actual operations; no allocation or null-safety
guarantee is inferred.

The local `FlagRecord` exactly preserves the existing `080CECF4` declaration:
one unknown byte, byte flags, and ten more unknown bytes, for stride 12.
The observed status byte at offset `+0x02` is accessed as `unknown_02[0]`,
without introducing an incompatible global type or a shared-header change.

After clearing the output, the function snapshots the count of records with
both flag bits 1 and 2 among 30 entries at `0x02002CC0`. The count is a byte;
the observed cap at 30 is retained despite being unreachable in this scan.
Only indices 6 through 29 are subsequently processed, using 38-byte
definitions at `0x08565416 + 38 * index` and counter index `index + 0x15`.

For a record with flag bit 1:

- Flag `0x08` has priority over flag `0x02`. A zero counter or a counter
  decrementing to zero skips the counter setter, reloads and clears flag
  bits `0x0A`, clears global bit `0x59F`, sets bit `0x581 + index`, writes
  status zero, then appends the low byte of `index + 1`.
- A remaining nonzero counter is stored first. The two definition bytes
  `+0x02` and `+0x03` are then read to form the denominator of the signed
  expression `15 - (14 * remaining) / denominator`; its low byte is stored
  as status. There is no additional clamp.
- With flag `0x02` but not `0x08`, a nonzero first getter result causes a
  second genuine getter call, followed by a byte-wrapped decrement setter.
- With a zero counter, a signed-16 RNG result modulo 100 is narrowed again
  to signed 16 bits, then compared strictly below
  `100 - definition[7 + snapshot_count]`. The table read follows the RNG
  and remainder calls. Success reloads flags and ORs `0x08`, stores status
  one, sets the counter from definition byte `+0x02` only, then appends the
  low byte of `index - 0x7F`.
- Failure reads definition byte `+0x01` before the second RNG call. Its
  signed remainder modulo half that byte is added to the saved base and
  narrowed to a byte. A resulting zero becomes one before the counter setter.

The returned append count is narrowed to a byte and cannot exceed 24 in the
observed loop. Output writes may affect later processing when storage overlaps;
there is no new `restrict` qualifier, cached flags across mutating calls,
capacity guard or reordered clearing operation.

## Helper and arithmetic domain

The existing interfaces are preserved: `u32 08002804(void)`,
`u8 080C95A8(u16)`, `void 080C95C0(u16,u32)` and
`void 080C9574(u16,u16)`. The two counter helpers access byte
`0x02000000 + 0x2030 + low16(index)`. The bit setter performs its actual
unconditional clear/store and conditional set/store at the global bit bank.

The full signed quotient routine `[0x081426B8,0x0814274A)` and signed remainder
routine `[0x08142950,0x08142A1E)` were executed, along with their real no-op
zero handler at `0x0814274C`. The real RNG returns `[0,32767]`, so the caller's
signed-16 conversions are lossless for this dependency. The numerator
`14 * remaining` is at most 3556; all other integer operations are similarly
within signed-32 range before the explicit byte conversions.

The actual bounded definitions for indices 6 through 29 have nonzero
denominators (30, 40 or 255) and base bytes 25, 35, 40 or 255. Thus their
halved-base remainder divisors are also positive. The natural C requires
nonzero divisors on reached paths; it does not promise the ROM runtime's
zero-divisor result as portable C behavior. No original table allocation,
global storage extent, nominal typedef uniqueness or blanket alias-safety
claim follows from these observations.

The clear callback is loaded from `0x0836D4B8` and invoked through the real
`0814224C` thunk. Its actual code at `[0x03005E78,0x03005EAA)` is the 50-byte /
25-instruction copy from ROM `[0x08A38A2C,0x08A38A5E)`. It was not modeled or
replaced during execution tests.

## Behavioral evidence and limits

388 paired fixtures produced 776 actual target/candidate executions. Every
helper, both arithmetic runtimes, the zero handler, thunk and copied clear
routine executed real instructions; no helper stubs were used. RAM was
explicitly synthetic. Definition records were real ROM data except for named
synthetic divisor/base/probability edge cases.

385 pairs had nonzero arithmetic divisors. Three additional pairs deliberately
tested zero duration or base 0/1 and agreed at the compiled-machine level only;
they are outside the natural C arithmetic domain, not semantic C validation.
Separate overlapping-output fixtures exercised clearing and appending into
record bytes, counter bytes and the global bit bank. Those finite machine
tests do not establish arbitrary object allocation or a general alias proof.

Cases covered all clear alignments, clear lengths 0 through selected boundary
values up to 255, unrelated upper argument bits, every flag-priority category,
counter values 0/1/2/15/127/255, first/middle/last processed records, snapshot
counts including 30, actual RNG boundary values, strict probability boundaries,
two-byte denominators, base-byte wrapping and the zero-to-one fallback.
Entire-loop cases returned 24 appended bytes even with clear length one.

Both bodies agreed with a separate mutation/call model and each other on whole
synthetic RAM, RNG state, return value, exact ordered non-stack data reads and
writes, helper arguments/order, R4-R11 preservation, SP restoration and return
control. Instruction literals and stack save areas were excluded from the
cross-binary data trace. All 388 complete ordered data traces agreed.
Per body there were 388 clear calls, 1943 counter reads, 1285 counter writes,
1142 bit-setter calls, 1926 RNG and remainder calls, 209 quotient calls and
three zero-handler calls.

Coverage was 226/228 ROM instructions and 211/213 candidate instructions.
The only uncovered target instructions are the unreachable cap assignment
at `0x080CFB38` and `0x080CFB3A`; a count of 30 single increments cannot
exceed 30. Actual helper coverage was RNG 10/10, counter getter 8/8, counter
setter 8/8, bit setter 23/23, signed quotient 66/72, signed remainder 96/102,
zero handler 1/1, thunk 1/1 and clear 25/25. This evidence supports a bounded
recovery, not a MATCH or full proof over arbitrary inputs and allocations.

Generated compiler, linker and emulator scratch was removed after verification.
