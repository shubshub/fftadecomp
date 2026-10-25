# Interpolation helpers and preserved audio callbacks

Three complete, independently replayed Thumb functions share a local
six-halfword interpolation layout: signed current, remaining, error, step,
period and distance. These descriptive names do not establish original types.
All three first natural candidates matched without source or flag retries.

| Address | Complete bytes | Reached instructions | Behavior |
|---|---:|---:|---|
| `080E0608` | 66 | 31 | Initialize signed-halfword interpolation state |
| `080E064C` | 68 | 34 | Advance the state while retaining halfword narrowing |
| `080E0690` | 20 | 10 | Return whether the remaining count is zero |

The initializer owns its middle literal but not the two following alignment
bytes. Its low-halfword difference sign test and signed duration shift must
not be replaced by unrestricted absolute-value arithmetic. The stepper
preserves its signed-error loop rather than replacing it with division.
Malformed nonzero remaining count, zero period and negative error can fail
to terminate; no repair or universal termination claim is made. Narrowing
outside the signed-halfword range is target/compiler-specific.

The completion predicate returns exactly zero or one. The chosen `u8` return
agrees with observed callers that narrow to the low byte; the original nominal
return width remains ambiguous. The complete `080DFCAC` caller and bounded
`080DEDFC` blocks support the layout. The latter has an unresolved computed
jump outside those blocks, so this is not a complete caller census.

Finite native evidence covers eight initializer cases, sixteen stepper calls,
and five predicate cases, with separate layout assertions. Independent reviews
replayed each unchanged target candidate once and inspected, rather than
repeated, the native campaigns. Exact target bytes and native checks are
distinct evidence, not an exhaustive gameplay-equivalence claim.

## Preserved nonmatches

`Parked/080DFB0C/` retains a timed two-command callback: 424 compiled bytes
versus 416 owned ROM bytes. `Parked/080DFCAC/` retains an interpolated audio
parameter callback: 192 compiled bytes versus 188 owned ROM bytes. Neither
earns match credit. Their READMEs preserve the original author-stage evidence,
including differences, uncertainty and provenance limitations. No source
revisions or compiler-option searches were used to chase their differences.

The shared inventory now incorporates the independently reviewed target
extents and instruction counts, not the larger nonmatching compiler extents.
The private metadata proposals described in those frozen READMEs have now
been applied by the coordinator. Separately reviewed `080DFBCA` was removed
from `symbols/functions.txt`: it is the second halfword of the four-byte BL
at `080DFBC8`, not a separate instruction entry. The bounded nearby scan is
not a whole-ROM absence-of-reference proof.

The named data binding `g_table_08149B88` identifies the ROM-observed float
table base. Observed indices 0 through 32 do not establish total allocation;
the preserved source uses an unbounded external array declaration. Named
linking succeeded, but that does not turn the callback into an exact match.
The downstream helper `08145388` remains Parked, not matched. Callback direct
calls use ABI summaries, not transitive proofs of downstream behavior.
