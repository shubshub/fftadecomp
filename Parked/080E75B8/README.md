# 080E75B8: preserved first-candidate nonmatch

**NONMATCH.** This directory contains only the unchanged natural C candidate
and this README. It is not eligible for `src/` or match credit. One canonical
target compilation was performed with the default literal
`$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`, ordinary profile and current
approved mappings. The source was plausible; canonical main/SystemExit/process
statuses were all1. There was no source revision, retry, flag/type/order search,
native campaign or future-impossibility claim.

## Actual difference and ownership

| Measurement | Owned ROM target | Complete compiled symbol |
| --- | --- | --- |
| Envelope | [080E75B8,080E76A2) | [080E75B8,080E76B2) |
| Bytes | 234 | 250 |
| Reached instructions | 103 | 111 |
| Code / literal / internal alignment bytes | 220 / 12 / 2 | 236 / 12 / 2 |

Comparison at each of the234 owned target byte positions gives **13 equal,
221 different, zero missing**, plus **16 excess compiled bytes**. Only two
reached instructions have equal encodings at the same target offset. These
are positional metrics, not a behavioral-equivalence score.

The emitted entry adds `mov r7,r8; push {r7}`, retains additional descriptor
and payload copies, and restores r8 near return. Its phase-increment store is
separate from the completion store rather than sharing the target's store.
Register operands, branch/call offsets and pool placements therefore differ.
The three compiled pool words are at767C/7680/7684 instead of7670/7674/7678;
their literal values still match083978C8/08397A30/08397A0C. All seven direct
destinations remain typed and linked. These observations diagnose the emitted
body, not an evidence-backed reason to alter C for register allocation.

The canonical nonmatch diagnostic is retained unchanged in the full bundle.
It uses a250-byte ROM window, including **16 unowned bytes**: external zero
alignment at76A2..76A4 and14 bytes of the separate76A4 entry. Its `205/250`
byte total is LCS-aligned, not positional; its `64/107` instruction display
samples ROM at compiled instruction positions and misdecodes some target pool
data. Neither metric is used as target ownership or actual reached-code count.
The owned comparison excludes all16 external bytes. Complete generated
`.text` is252 bytes; its final `c046` is outside even the250-byte function.

## Semantics and preconditions

The candidate preserves projected-coordinate DD748 with optional fourth
s16 output pointer NULL and its effectful DD760/-2/DE268 path. DD580 is tested
only through its low byte. Coordinate child+14 and record child+1C are written
only on that true branch; wrapper child+18 is created unconditionally.
Effectful calls are followed by the original field reloads. Polling stores
D6134(+14) first and short-circuits before DBA5C(+18); child+1C is unpolled.
Phase0 does not advance, phase increment narrows to u16, and return is zero.

The payload's+14/+1C values on the false branch are externally initialized
preconditions, not locally proved. D6134 lacks a null guard. No zero stores,
guards, skipped poll or additional cleanup were invented. The unknown four
bytes at+10 describe an observed field gap, not a proof of nested buffer extent
or asynchronous lifetime. Callee effects, scheduler copying, allocation and
object validity remain external assumptions. No native or semantic-equivalence
test was run after this nonmatch; compatible types and structural ROM evidence
do not establish runtime equivalence.

## Retained evidence

The complete author bundle is
`/home/user/.codex-work/ffta-ulw/080E75B8-author-next`:

- `ABI.md` and `freeze.json`: precompile rationale, source/nine-header/map/tool
  hashes, exact target bytes and freeze-before-start chronology.
- `elf-capture.json`: complete original1212-byte and linked2424-byte raw ELF
  images encoded as text, exact statuses and observed commands.
- `verification.json`, `BODY-DIFF.md`, `exact-diff.txt`: separately traversed
  target/compiled CFGs, complete partitions, typed relocations and positional
  differences. These are absolute-bundle references, not adjacent Parked files.
- `compile-1.log` and `isolatedroot/docs/match/080E75B8.md`: the genuine failed
  canonical output/report, retained for audit only and not integration.
- `HANDOFF.md` and `SHA256SUMS`: final provenance and checksums.

The source SHA256 is
`69bdc729b2c397bf97699cdbc264811e0f372183f10e3962d6b570f717bd0dc8`.
Only this C plus README is the proposed preservation payload. No metadata
changes or failed reports belong in that payload. Root controls independent
preservation review, shared integration and claim release.
