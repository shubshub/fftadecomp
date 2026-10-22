# 080078A8 — bounded line rasterization recovery, not matching

This is the first natural C recovery, retained after three grounded forms.
With agbcc `-mthumb-interwork -O2`, the official matcher accepts the complete
framed leaf and source plausibility, then reports **NOT MATCHING — bytes
differ**. This is a code-generation mismatch, not a verifier limitation.
No active source, match report or progress credit is requested.

## Complete extent and differences

The ROM body is `[0x080078A8,0x08007A4C)`: 420 bytes / 210 Thumb instructions,
with no calls, literal pools or internal/external alignment at its end.
Capstone and Binary Ninja instruction boundaries agree; all direct branches
remain inside this body, which ends with `bx r1`. The next indexed function
starts immediately at `0x08007A4C`. Existing boundaries and counts need no
metadata correction. No broad caller scan or absence-of-interior-entry proof
is claimed.

The retained source produces one complete 420-byte / 210-instruction ELF
function, a 420-byte `.text` section aligned to four bytes, and no relocations
or additional allocated content. It is not truncated or padded for comparison.
The first differing byte is at `0x080078B2`: ROM allocates 24 local bytes;
the candidate allocates 20. Including saved registers, their stack depths are
56 and 52 bytes respectively. Register allocation, spills, instruction order
and branch encodings also differ; this is not just a four-byte frame fix.

At identical byte positions, **69/420 bytes and 19/210 instructions agree**;
351 bytes differ. The tool's sequence-aligned diagnostic reports 221/420
bytes and 56/210 instructions; those figures are not positional equality.

| Input | SHA-256 |
| --- | --- |
| Retained source | `59e51c786c237a7dfefa635e69835fd108d8304f72bfa4abfbb248de7a58d5c3` |
| Complete ROM body | `55835a86406e179d761181659ae19138965a4eb7f352745d05b3bf8d74e4a137` |
| Complete compiled body | `80d90c1f2e4659985d2c17ce79a9cd5f61ab48d1095bc0eb584c211adc8175af` |

The second form staged the delta calculations and used separate major-axis
loop variables; it produced 426 bytes / 213 instructions with 36 local stack
bytes. The third retained staged initialization but updated the original
coordinate variables; it produced 426 bytes / 213 instructions with 32 local
stack bytes. Neither improved the semantic justification of the first form.
No flags, layout padding, register constraints, assembly, volatile accesses,
dead code or verifier workarounds were introduced. Source iteration stopped.

## Recovered contract and limits

The four register arguments are signed 16-bit endpoint coordinates. The fifth
argument, at entry SP, points to an array of `{s16 horizontal; s16 vertical;}`
with stride four and field offsets zero and two. The function returns
`max(abs(end_horizontal-start_horizontal), abs(end_vertical-start_vertical)) + 1`
and stores an inclusive integer line in original endpoint order.

The larger absolute delta selects the major axis (ties select vertical).
Iteration proceeds in increasing major coordinate; a half-major initial error
controls minor-axis advancement. Each point's output index is its Chebyshev
distance from the original first endpoint, preserving original endpoint order
even when the iteration endpoints are swapped. Each iteration stores the
horizontal halfword before the vertical halfword; it does not read output.

This requires a live, writable, at least two-byte-aligned `LinePoint` array
with capacity for the returned count. That object must not overlap the active
stack frame or fifth-argument slot. Valid stack storage and ordinary ARM ABI
conditions are required. No null, undersized, overlapping or invalid-object
safety claim is made. Signed 32-bit coordinate differences and error arithmetic
fit for signed 16-bit endpoints; signed 16-bit narrowing uses this target
compiler's wrapping conversion, not a portable-C overflow guarantee.

The inclusive major-coordinate loop uses a signed 16-bit counter. The finite
recovery contract excludes a major-axis upper endpoint of `32767`: incrementing
that endpoint wraps and can continue with invalid output indices instead of
returning. Both actual ROM and compiled code exhibit an out-of-arena write for
the tested degenerate `(32767,32767)` endpoint. This is a preserved limitation,
not a condition repaired by the recovery. No all-input equivalence or universal
termination claim is made.

## Validation

The owned author evidence contains a self-cleaning `check.py`, raw-ROM
classification, fresh official log/report, all attempted-form logs, full
position-by-position discrepancy list and input hashes. A scratch fixture
copies this source under `src/` solely to run the unmodified official matcher;
it is deleted afterwards. The supported `elf-symbol-thumb-frame-v1` proof
succeeds. Strict report replay rejects both the honest nonmatch report and a
forged MATCH verdict. Seven agbcc assertions check integer/pointer widths,
point layout and target signed narrowing.

Unicorn executes the actual 420-byte ROM body and the independently compiled
complete candidate in 32 paired cases / 64 executions. There are **no helper,
BIOS or memory-behavior models**: this body makes no calls. A separate
closed-form integer raster oracle checks output values and ordered halfword
writes. Cases cover both major axes, both endpoint orders, all slope signs,
ties, horizontal/vertical/degenerate lines, negative coordinates and bounded
signed-endpoint edges. Varying register upper halves, two-byte-aligned output,
word-aligned SP variants and both ARM/Thumb return states are exercised.

Checks cover full mapped output arena, bounded stack accesses, unchanged stack
outside each body's own frame, preserved incoming argument, restored SP/LR and
r4-r11, and return count. Stack scratch bytes are not compared between bodies:
their proven layouts differ. Coverage is 209/210 instructions in each body,
not exhaustive path coverage. Three ROM mutations (neighbor store, error
branch, return count), two insufficient-capacity checks and two excluded
terminal-overflow checks are detected. These bounded tests support the
recovery; they do not convert the nonmatch into a MATCH.
