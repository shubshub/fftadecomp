# 081451EC: bounded nonmatch

This is the first and only frozen natural-C candidate, not a matching source.
One canonical compilation used agbcc `-mthumb-interwork -O2`; there were no
source revisions, alternative flags, or spelling/register searches. Only this
C file and this README are intended for shared `Parked/081451EC/` integration.

## Recovered local contract

The Thumb entry consumes a 16-bit song index. The song table at `0x0814BB48`
has an observed eight-byte stride: header pointer at `+0`, 16-bit player index
at `+4`, and uninterpreted bytes at `+6`. The player table at `0x0814BB24` has
an observed twelve-byte stride and a playback-state pointer at `+0`; the other
eight bytes are not interpreted by this function. The state prefix contains
the current header pointer at `+0` and a 32-bit status word at `+4`.

The function calls `081458AC(state, requested_header)` if the header differs.
If the headers agree, it calls `081458AC(state, current_header)` when either
the status's low sixteen bits are zero or its signed 32-bit value is negative.
Otherwise it returns without a call. The callee's bounded entry/body evidence
supports these two argument roles, including its stores of status at `+4`
and header at `+0`; its transitive behavior was not proved. Names and original
public typedefs are not recovered. Table lengths, index validity, live-state
invariants, and absence of concurrent mutation are not established here.

The indexed local envelope is `[0x081451EC, 0x08145238)`, 76 bytes. Bounded
reachable decoding finds 31 instructions occupying 66 bytes, two alignment
bytes at `0x08145216`, and two literal words at `0x08145218` and `0x0814521C`.
The code resumes after the middle pool at `0x08145220`. The index's legacy
`instrs: 38` is not an actual instruction count. No metadata change is bundled.

## Exact remaining difference

The canonical verifier accepted the source as plausible, linked both direct
calls without remaining relocations, and checked the complete 76-byte ELF
function symbol including its pools. It returned **NOT MATCHING**: 44/76
aligned identical bytes, but only 20/76 identical bytes at the same offsets.
The bodies differ in table-load order, registers, pool placement, and the
status predicate lowering. The report's aligned instruction display is not a
separate authoritative ROM CFG: displaced pools appear as instructions there.

There is also a confirmed behavioral difference in this compiled candidate.
For equal headers, the ROM reads the status as both a word and a halfword.
The candidate C expresses that condition as
`(u16)state->status == 0 || (s32)state->status < 0`. The fixed target compiler
instead emits a word-only test equivalent to calling when the word is zero
or negative. With status `0x00010000`, the exact C predicate is true and the
ROM calls the helper, but the compiled body skips the call. No source-level
predicate defect was found; this frozen input exhibits a target-toolchain
lowering divergence. This does not establish a general compiler diagnosis or
that another honest recovery cannot match.

| Equal-header status | Exact C predicate | ROM helper call | Compiled helper call |
| --- | --- | --- | --- |
| `0x00000000` | true | yes | yes |
| `0x00000001` | false | no | no |
| `0x00010000` | true | yes | **no** |
| `0x80000000` | true | yes | yes |

Eight bounded ROM executions and eight compiled-body executions used these
four statuses with equal and unequal headers. A hooked helper recorded call
arguments and returned using the ordinary ABI. All eight ROM cases agreed
with the recovered local contract; seven compiled cases agreed and the case
above did not. These synthetic fixtures also checked low-16-bit input
narrowing, selected table entries, return, SP restoration, and preservation of
`r4` through `r11`. A separate native compilation of the exact predicate
agreed with the ROM for the four values; it was not another agbcc attempt.
This is targeted caller-local evidence, not exhaustive behavior or a proof
of actual table bounds, helper internals, or reachability of every status in
gameplay. Compiled behavioral equivalence is explicitly **not** claimed.

## Retained evidence

The source SHA-256 is
`d0e9b3462c21d18d850ff1193250c649bf9e9bd5007b7c46dd3aafc50cd767fb`.
The full author bundle is retained at
`/home/user/.codex-work/ffta-ulw/081451EC-author-next/`:

- `freeze.json`: the unchanged first source, all nine header bindings, mapping,
  flags, and matcher fingerprint.
- `canonical.log` and `isolated/docs/match/081451EC.md`: the one complete-ELF
  canonical attempt, exact target/output bytes, and mismatch.
- `evidence.json`: bounded ROM/compiled CFGs, native predicate input/output,
  and all sixteen machine-body case results.
- `HANDOFF.md` and `SHA256SUMS`: provenance, tool identity, scope, and hashes.

Those supplemental files are not part of the two-file shared payload.
The reservation and any integration are coordinator-owned. No match credit
or whole-game completion follows from this preserved attempt.
