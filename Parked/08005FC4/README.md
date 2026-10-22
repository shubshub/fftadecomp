# 08005FC4 — descriptor-driven tile transfer

**Parked, not a match.** The retained natural recovery compiles to a complete
556-byte function, shorter than the 584-byte ROM function. No active source
or match report is retained.

## Complete symbols and attempts

The target owns `[0x08005FC4,0x0800620C)`: 584 bytes / 288 reachable
instructions. Code occupies `[0x08005FC4,0x08006148)` and
`[0x0800614C,0x0800620C)`; the intervening four bytes are the scalar literal
`0x000003FF`. There is no internal or external alignment. The following
function begins at `0x0800620C` and is excluded.

Only two ordinary forms were tried with agbcc `-mthumb-interwork -O2`:

| Form | Complete FUNC | Instructions | `.text` |
| --- | ---: | ---: | ---: |
| Direct repeated serialized flag expressions | 542 bytes | 267 | 544 bytes |
| Retained semantic `u16` flag-reader inline helper | 556 bytes | 274 | 556 bytes |

The retained source emits exactly one function. Its ordinary inline helper
does not survive as another ELF function. Typed diagnostic linking resolves
both calls to `0x0814187C`, without a veneer or residual relocation. The
candidate owns `[0x08005FC4,0x080061F0)` and contains its `0x000003FF` pool
at `[0x0800613C,0x08006140)`; its remaining 552 bytes are code. It saves
32 bytes and allocates 20 local bytes, versus the target's 32 plus 24.

Frozen toolkit `4847c93` rejects the retained source with
`compiled symbol is shorter than the indexed span: 556 < 584` before any
match claim. The diagnostic local CFG accepts all 274 candidate instructions
under ordinary direct-call summaries. This is a real code-generation mismatch,
not an unsupported-profile claim. Differences include register allocation,
local-frame size, arithmetic scheduling, eliminated irrelevant flag-byte
loads, and pool/branch placement. Only 54 byte positions agree over the
556-byte common length; the remaining 28 target bytes are absent. This is
not a prefix-match or LCS match percentage.

## Recovered interface and ordering

The compatible interface is `void(const void *, u8, u16, u16, u16,
const void *)`: source descriptor, palette, tile offset, transparent value,
fill value, and destination descriptor. The final two values arrive in the
first two incoming stack words. The ordinary void interface follows the
saved-LR return sequence, not a uniquely recovered original typedef.

Each descriptor is a readable eight-byte serialized representation: data
pointer bytes 0..3, width at 4, height at 5, and flag bytes 6..7, all
little-endian. Pointer reconstruction uses the target's 32-bit integer/pointer
representation; it is not a portable address conversion or an allocation
bound. Halfword element accesses require aligned, legitimately typed storage;
byte element accesses use unsigned characters. Descriptor alignment itself
is not imposed by the byte view.

The recovery captures the initial horizontal/vertical flip bits, iterates
destination rows and columns, and uses live descriptor fields for repetition,
source selection, destination stores and flip alternation. Source flags
`0x0008`/`0x0004` select row/column wrapping. Out-of-range coordinates select
the fill value. Source `0x8000` selects byte elements; otherwise halfwords
use the low-ten-bit transparent comparison, narrowed tile/palette additions
and flip-bit XORs. Destination `0x8000` independently selects byte stores.
Source `0x0010` toggles horizontal flip after each store, and `0x0020`
toggles vertical flip after each row, including zero-width rows. Horizontal
flip is not reset at a row boundary.

The source has no `restrict`, fabricated bounds, null guard or zero-dimension
guard. `const` describes these access paths; it does not promise that an
output byte cannot mutate a writable descriptor or input data. Tested aliases
are ordinary byte descriptor overlays and same-element-type data overlaps,
not arbitrary incompatible-object or misaligned machine overlaps. No universal
memory-safety or termination claim is made.

## BIOS service boundary

The only helper is the actual six-byte wrapper at
`[0x0814187C,0x08141882)`: service 7, copy post-service r1 to r0, return.
The declaration `s32 func_0814187C(s32 denominator, s32 numerator)` keeps
this explicit external platform boundary; the C does not substitute `%`.

Local installed mGBA 0.10.5 implementation evidence supports conventional
DivArm ordering and signed remainder semantics. It is not proof of the
original BIOS. No original BIOS image was executed. Nonzero caller dimensions
are 1..255, and indices are nonnegative u16 values, avoiding signed-overflow
division. Dimension zero can reach the service without a guard, including
row wrapping before the destination-width test. Original-BIOS zero-divisor,
exceptional preservation and termination behavior remain unresolved.

## Bounded verification

The retained reproducer freshly compiles and links this Parked source in an
isolated disk-backed root with the actual include/header set, reproduces the
official size rejection, and executes actual ROM instructions and the fresh
candidate against a separately written mutable-memory operation oracle.
All data fixtures are synthetic RAM, not claims about actual game objects.

- 66 paired fixtures / 132 executions: 50 without any BIOS-service call,
  14 with an explicitly modeled positive-divisor service, and two prefixes
  stopped at the unresolved zero-divisor service boundary.
- The real six-byte wrapper executes in wrapping cases. Only SVC7 is modeled;
  normal models supply quotient/remainder and exercise caller-clobbered
  registers. This is neither original BIOS nor mGBA HLE execution.
- All 288 target, 274 candidate and three wrapper instructions are covered.
  Ordinary returns preserve r4-r11 and SP; stack accesses stay within the
  respective frames and the two incoming argument words. Peak frames are
  56 bytes for the target and 52 for the candidate.
- Independent expected ordered output writes, helper arguments/order and
  complete EWRAM agree for every fixture. Target ordered state-memory reads
  also match the explicit oracle. State traces exclude stack, instruction
  fetches and literal-pool reads. **Target/candidate read footprints differ
  in 65 of 66 fixtures**; equal ordered reads are not claimed.
- Cases cover both source/destination widths, transparent and nontransparent
  values, addition/narrowing, all flip/repetition/alternation branches, empty
  dimensions, in-place/shifted data, and output bytes changing live descriptor
  flags or dimensions. One returning raw-register upper-bit fixture is
  explicitly an ABI machine diagnostic, not a wider value of a narrow C
  parameter. The two stopped zero-divisor cases have no return/ABI-completion
  claim.

Reproduce from the development environment:

```sh
env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp \
  PATH=/home/user/armtc/root/usr/bin:$PATH \
  python3 /home/user/.codex-work/ffta-ulw/08005FC4-author/check.py
```

The small `check.py`/`build.py` scripts and text evidence remain outside the
repository. Generated binaries and isolated roots are removed automatically.
No ROM bytes or compiler outputs are retained here.

## Frozen identities

- Source SHA256: `72f672d7043f13955094e4eb4d2fc23898073e2dc08b765b94ed5d6a2ee7ee91`.
- Target SHA256: `892d21741d74b2e4f33e22b6ab5190c95abe3c09f75beeadacf1f1e4b8199382`.
- Candidate linked FUNC SHA256: `681a0cb2a7598dbfc7d6a18b07b38b447448cd88cfd05ee62644a886c4e2d364`.
- Wrapper SHA256: `830adaf1669e0ba029f2c6d4a13693468d1d6ac999f34bdc0ce736b31f4a54fc`.
