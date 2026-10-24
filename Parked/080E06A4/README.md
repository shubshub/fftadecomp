# 080E06A4 — preserved single natural candidate

**NONMATCH.** This unchanged source earns no matched-function credit. The sole
target compile used the default agbcc `-mthumb-interwork -O2` configuration.
Both complete bodies contain 138 bytes and 65 reached instructions. Exactly
64 of those 65 instructions and 136 of 138 same-position bytes are identical.

## Exact difference and ownership

At `080E06C8`, the allocation-size calculation has commuted ADD operands:

| Body | Bytes | Instruction |
|---|---|---|
| ROM | `20 18` | `adds r0, r4, r0` |
| Compiled | `00 19` | `adds r0, r0, r4` |

This is one changed two-byte instruction, not an added or missing instruction.
The natural source expression is `3 * buffer_bytes`. The two ADD forms have
the same arithmetic result and flags, but their encodings are not identical.
No output-driven operand/source-spelling change was attempted to force the
other encoding. No source retry, flag search or native/emulator campaign ran.

The complete owned ROM envelope is `[080E06A4,080E072E)`, with no literal pool
or internal gap. Both original and linked ELF function symbols are exactly
138 bytes. Their `.text` sections are 140 bytes; the trailing `c046` belongs
to external alignment, not the function. The ROM's following `0000` halfword
is likewise excluded. Extent changes or alignment credit cannot remove the
actual in-body difference.

The original ELF has four `R_ARM_THM_CALL` relocations, to `0800A654`, `08008480`,
`080086D0` and `0800A668`. Typed linking resolves exactly those calls without
veneers, added function bodies or residual relocations. The ordinary framed
call CFG and source-plausibility checks pass. Canonical `match.py` returns 1;
the capture wrapper propagates that same exit status. The diagnostic report
is a nonmatch, not an eligible report for `src/`.

## Recovered behavior and limits

The void wrapper receives unsigned low16 knot and sample counts, two const
signed64 arrays, and a halfword destination. The selected signed16 destination
is consistent with callers, but the original nominal signedness is not proved.
It allocates three times the **u16-truncated** knot-byte count, builds signed64
coefficients/workspace, then samples query coordinates `index * 65536` through
`080086D0`, storing return bits 16..31. It frees the original allocation after
the loop. Its u16 do-while loop emits one sample even for sample count zero.

The 32 saved bytes plus 12 local bytes put incoming argument five at local
SP+44. Evaluator query/result use r0/r1 word pairs; its values and coefficient
pointers are stack arguments. Reached caller sites `080E0204`, `080E0222` and
`080E033A` pass three knots and ignore the result. These are bounded witnesses,
not a whole-ROM caller census.

`08008480` remains Parked, not matched. Ordinary typed-call acceptance assumes
callee ABI contracts; it does not prove downstream signed64 arithmetic or
termination. Actual knots 0..2 do not return from that coefficient function;
knots >=8192 wrap the allocation stride below the nominal array requirement.
There is no allocation/null check. Successful numerical use requires valid
aligned arrays, sufficient storage, successful allocation and the dependencies'
numeric preconditions. Signed negative right shifts and out-of-range signed16
narrowing are target/compiler-specific. No clamps, zeroing or safety repair was
inserted, and no broad numerical correctness claim is made.

## Evidence and integration boundary

Only this C file and this README are intended for Parked integration. Retained
author evidence lives at the explicit absolute path
`/home/user/.codex-work/ffta-ulw/080E06A4-author-next/`:

- `freeze.json`, `compile-start.json` and `ABI.md`: serialized precompile
  chronology, unchanged candidate, nine header bindings, maps, tools and ABI.
- `canonical.log` and `isolatedroot/docs/match/080E06A4.md`: sole canonical run.
- `elf-capture.json`: full original/linked ELF encoded as text from that run.
- `verification.json`: exact byte/instruction differences and complete-symbol
  checks over the captured ELF, with no recompilation.
- `metadata.patch`: separate private proposal, not applied to shared metadata
  by this author; retain endpoints, change JSON/text count 69 to 65 and legacy
  symbol size `000028` to `00008A`. This corrects inventory, not match credit.
- `HANDOFF.md` and `SHA256SUMS`: sealed delivery and reproduction boundaries.

Frozen compiled source SHA-256: `ac094400bb53c8a9afdbc9f5e5b4948e7dc23390e66719090a7604db21fdc9f1`.
Frozen compiled source plus nine-header fingerprint:
`b563c76ce6c41edf432b80f47a1a325a2b609698d4df28892b5a3f478f211ee9`.
Target SHA-256: `fe681c8df8b55a343ee1860f420812298e3f93d76e8d65f5318e913448e88632`.
Compiled complete-body SHA-256:
`164e99ab76664898d0f41f749742459f2a40910a89df742913713df44641d771`.

## Integration-only comment adaptation

The integration adds the actual 138 ROM target bytes to the leading C
comment, satisfying the repository target-byte documentation rule. This
comment was added after the sole compile; it was not recompiled. Everything
following that leading comment is byte-for-byte unchanged, including all
preprocessor directives, declarations and the function body. No codegen
revision, new candidate, native test or match credit is implied.

The sealed author bundle and its ready payload remain unchanged. The
source and source/header fingerprints above identify the frozen compiled
candidate, not this comment-adapted integration. The original nonmatch
report remains diagnostic evidence for that frozen candidate.

Integrated C SHA-256: `ea23bcb7f6954a96b1919670f1af1a0ed955426f76e28e3b4702f178193a2a42`.
Independent adaptation proof and patch:
`/home/user/.codex-work/ffta-ulw/review-080E06A4-next/`.
