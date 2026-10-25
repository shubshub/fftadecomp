# 080E8F3C — preserved NONMATCH

One natural candidate was frozen before one canonical invocation using default
`$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`, without profile or tool overrides.
This C is byte-for-byte the frozen source, including the full target-byte
comment. No source/type/order/spelling/register/flag retry, native campaign,
manual link or match credit is claimed.

## Exact result

| Complete ownership | ROM target | Candidate |
| --- | ---: | ---: |
| Start | 080E8F3C | 080E8F3C |
| Exclusive symbol end | 080E921C | 080E9216 |
| Symbol bytes | 736 | 730 |
| Reached instructions | 322 | 329 |
| Code / literals / internal alignment | 676 / 56 / 4 | 690 / 36 / 4 |

The owned comparison is **22 equal, 708 different and six absent bytes** at
the same offsets, first difference offset 2. There are no excess symbol bytes.
Both original and linked `.text` sections are 732 bytes; their final `c046`
at candidate addresses 080E9216..080E9218 is external to the 730-byte function
symbol and is excluded. No external filler or adjacent ROM bytes receive credit.
These are positional metrics, not aligned/LCS scores.

Actual process exit 1, string SystemExit:
`compiled symbol is shorter than the indexed span: 730 < 736`.
The captured `main` return is `None` during exception unwinding, not successful
return 0. Canonical compilation, typed linking and structural/literal checks
did occur before workspace cleanup and the short-symbol gate. No canonical
comparison report or source-plausibility verdict was reached.

Complete raw original ELF (2044 bytes), linked ELF (5620 bytes), compiler
assembly and preprocessed source were passively captured from that same run.
All 16 original call relocations resolve to 12 typed indexed Thumb targets;
the linked image has no residual relocation, undefined symbol or extra
allocated payload apart from the disclosed external text alignment.

Observed differences include saving r8-r10 rather than only r8 in addition to
r4-r7/LR, hoisted address loads, different registers/branches and literal
placement, explicit narrowing of the u16 mask result, and different old-child
boolean construction. Code grows by 14 bytes while literal storage shrinks by
20 bytes. Both signed indexed curve reads remain present at curve-driven calls.
These observations do not authorize rewriting the frozen source to chase codegen.

## Source gate and semantic limits

A separate existing source checker exits 1 with **four unwaived SUSPECT
`rom-address` findings**, for the numeric address initializers at lines 56–59.
Canonical plausibility was not reached. No waiver, fabricated data binding,
automatic plausibility approval or canonical `IMPLAUSIBLE` report is claimed.

The source retains the full-word-zero three-pointer callback, 44-byte ILP32
payload layout, signed coordinate narrowing, separate signed curve expressions,
byte index and halfword timer/angle wraps, phase ordering and low8 DD580 test.
Phase102 distinguishes timer already zero from decrementing to zero. Shadow
mask clearing occurs only on the sequence child's nonnull-to-null transition,
followed by ordered coordinate/wrapper polling. The record child remains
unpolled. No skipped-slot initialization, clamp, null guard or callee-purity
promise is introduced. The DD748 fourth coordinate output is NULL and its
forwarded -2 path remains effectful.

Valid modes/curve indices, original table extents, phase ordering, initialized
index/angle/child fields, readable storage, allocation success and retained
pointer lifetimes remain preconditions. Nominal types are compatible evidence,
not uniquely recovered declarations. The ordinary call-profile result is not
recursive callee equivalence, hardware correctness or a native semantic test.
This finite nonmatch is not a future-impossibility claim.

## Retained evidence

Full author bundle:
`/home/user/.codex-work/ffta-ulw/080E8F3C-author-next`.
Its `ABI.md`, `freeze.json`, `compile-start.json`, `canonical.log`,
`elf-capture.json`, `COMPILED.md`, `verification.json`, `plausibility.log` and
`HANDOFF.md` record the pre-output rationale, actual chronology, complete raw
ELFs, exact ownership and limits. `SHA256SUMS` binds the bundle and this pair.

Frozen source SHA256:
`c4016f1d7744735a7c3eb473aeeca567f458ad0fa921eccc5ac5585358c80d09`.
Source plus nine-header fingerprint:
`ded4cd92745f342ce5c2f3458a341abf015413225dc9f29240ad2635e8d90eb8`.

Only this C and README are proposed for Parked preservation after independent
review. No metadata, report or compiled source is an integration payload.
