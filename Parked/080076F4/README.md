# 080076F4 — signed-threshold line-step advancement

**Parked, not a match.** The retained natural C compiles to 116 bytes /
58 instructions, versus the complete 136-byte / 68-instruction target.
There is no active source or match report for this address.

## Complete extent and bounded attempts

The target owns `[0x080076F4,0x0800777C)`, entirely code, with no literal,
table or alignment bytes. The separate prologue at `0x0800777C` is excluded.
Bounded Binary Ninja, Capstone and the frozen leaf CFG verifier agree on
all 68 reachable instructions. Actual calls at `0x080066D6` and
`0x080066E0` establish inbound entry use.

Two ordinary arithmetic representations were tried, both with agbcc
`-mthumb-interwork -O2`:

| Form | Complete FUNC | Instructions | `.text` |
| --- | ---: | ---: | ---: |
| Unsigned word arithmetic locals, signed-halfword comparisons | 106 bytes | 53 | 108 bytes |
| Retained unsigned-halfword state-width locals | 116 bytes | 58 | 116 bytes |

The retained candidate emits exactly one function, no relocation, helper,
pool or trailing section bytes. Its complete interval ends at `0x08007768`.
The original saves 28 bytes, including r8/r9 through low-register moves;
the candidate saves 20 bytes. Both have no local allocation or incoming
stack arguments. Other differences include register allocation, explicit
narrowing of the local error/coordinate, and reordered independent loads.
Only nine byte positions agree within the common 116-byte length; the last
20 target bytes are absent. This is not a match percentage or a prefix match.

Frozen toolkit `4847c93` independently reproduces the official rejection:
`compiled symbol is shorter than the indexed span: 116 < 136`.
The source passes its focused plausibility check and the generated leaf CFG
passes, but neither can override the full-symbol mismatch. No compiler flag
sweep, forced storage or artificial reload mechanism was used.

## Interface and state contract

The public interface is the compatible `void func_080076F4(void *object)`.
Only incoming r0 is consumed; the saved return address overwrites r0 at
return. The private `LineStepState` describes eleven observed halfwords:
current coordinates at `0x00/0x02`, targets at `0x04/0x06`, steps at
`0x08/0x0A`, deltas at `0x0C/0x0E`, error at `0x10`, half-delta at
`0x12`, and remaining count at `0x14`. The target compiler verifies every
offset, size `0x18` and alignment 4. The implicit trailing structure padding
is not an observed field or proof of the original allocation/type. The ROM
accesses require valid halfword storage through byte `0x15`; the recovered C
additionally requires a legitimately typed/aligned object view.

Raw fields are unsigned halfwords. Signed conditions explicitly interpret
their low16 bit patterns as `s16`. Out-of-range unsigned-to-signed conversions
use the target compiler's two's-complement behavior; no portable original
typedef is claimed. Promoted additions/subtractions fit signed32 and unsigned
halfword assignments narrow modulo 65536. The local coordinate/error narrow
earlier than the ROM's wide arithmetic registers, without changing their
subsequent low16 comparisons or stores in the tested domain.

The positive signed count path decrements the count, advances the second
coordinate, and immediately stores the accumulated error. It captures the
second delta and half-delta, then repeatedly advances the first coordinate
and subtracts the second delta while the signed16 error meets the signed16
threshold. On loop exit it stores error before the first coordinate. A
positive half-delta enables the final signed correction; that path stores
error before reloading the first step/current coordinate and updating it.
Nonpositive signed counts cause no state writes.

No missing guard is added. A malformed positive count with second delta zero
and nonnegative error enters a nonreturning loop. Other arbitrary mutated
states are not promised to terminate. This body has no outgoing calls,
retention, pointer fields or hidden engine contract.

## Fresh bounded evidence

The retained test rebuilds this Parked source in an isolated disk-backed root
using the actual headers, verifies one complete ELF function and 13 layout
assertions, and reproduces the official size rejection. It executes actual
ROM bytes and the fresh candidate against a separately specified mutable
halfword-operation oracle. All state objects are synthetic RAM fixtures;
there are no helper stubs or modeled external services.

- 36 paired invocations / 72 executions across 19 state fixtures: 35
  returning pairs and one malformed pair stopped after 2000 instructions
  per body. Sequential fixtures feed each resulting state to the next call.
- All 68 target and 58 candidate instructions are covered. Returning cases
  preserve r4-r11, LR and SP. Stack effects remain within the respective
  28-byte and 20-byte saves; untouched RAM and stack canaries remain intact.
- Both bodies agree with the oracle's complete final RAM and ordered state
  writes. The target additionally agrees with every expected ordered state
  read. **State-read footprints differ in 30 of 36 pairs**, principally
  first-delta/error ordering and half-delta capture scheduling. These trace
  claims exclude stack accesses and instruction fetches; there are no pools.
- Cases cover positive/zero/negative remaining counts, signed-error
  boundaries, wrapped error and coordinates, repeated inner steps,
  half-delta correction and skip paths, negative/noncanonical stored values,
  and the zero-delta loop prefix. The stopped prefix is not a normal-return
  or completion-ABI claim, and finite tests do not establish arbitrary
  storage/alias/concurrency safety or universal termination.

Reproduce with:

```sh
env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp \
  PATH=/home/user/armtc/root/usr/bin:$PATH \
  python3 /home/user/.codex-work/ffta-ulw/080076F4-author/check.py
```

Only the small `check.py`/`build.py` scripts and text log remain in that
external scratch directory. Temporary compiler outputs and isolated roots
are removed automatically. No ROM bytes are retained in this directory.

## Frozen identities

- Source SHA256: `a1f5ca5739af3f9c517bb7de4f5344f0c5c278888df8d796231431963c468cda`.
- Target SHA256: `f5d817eb9cbea96e6fda920f2a22ff2d20c6fc5857f9883f704f37481a5ec676`.
- Candidate FUNC SHA256: `f78a1a3ae6924648a1f3f269e16de9b50359c1aca3016901eeccdf897eb2ea4e`.
