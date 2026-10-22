# 08007A8C — Parked recovery candidate, not an official MATCH

This isolated candidate uses natural signed C division and a typed call to
`func_080071E8`. No production file, tool, header or map was changed. The
canonical compiler-emitted `__divsi3` is not replaced by an addressed alias.
Source iteration stopped after the first form and one grounded correction.

## Extent and proposed metadata correction

The complete ROM body is `[0x08007A8C,0x08007AC2)`, **54 bytes / 24 Thumb
instructions**, not the indexed 27 instructions: three BLs each occupy four
bytes. Capstone and Binary Ninja agree on every instruction boundary. There
are no literal pools or local SP allocation. The caller saves r4/r5/LR in
12 bytes and returns through `pop {r1}; bx r1`. Both index endpoints and kinds
are unchanged; `metadata-proposal.diff` proposes only **27 -> 24** in the JSON
and text counts, against the pinned immutable 495-function baseline.

`0x08007AC2` is an external zero alignment halfword. The following unindexed
sequences `[08007AC4,08007AC8)` and `[08007AC8,08007ACE)` are respectively
4-byte and 6-byte leaf-shaped boundary evidence, with external zero alignment
at `08007ACE` before indexed `08007AD0`. They are not authored, claimed or
promoted as functions here; no broad caller/interior-entry search was done.

## Exact disposition: two distinct blockers

The retained complete ELF function is **54 bytes / 24 instructions**. Its
`.text` is 56 bytes, aligned to four bytes, with external `c046` alignment
outside the function symbol. The three original `R_ARM_THM_CALL` relocations
are at offsets 10 and 24 to `func_080071E8`, and 40 to canonical `__divsi3`.
Unmodified typed linking resolves them to `080071E8`, `080071E8`, `081426B8`,
with no remaining relocations, veneers, pools or hidden helper text.

This linked-byte extraction is **diagnostic only**. It does not constitute a
supported-profile verification or MATCH. The complete linked body has
50/54 equal bytes and 20/24 equal instructions at identical positions:

| Address | ROM instruction | Compiled instruction |
| --- | --- | --- |
| `08007AAA` | `lsls r1,r1,#16` | `lsls r5,r5,#16` |
| `08007AAC` | `asrs r1,r1,#16` | `asrs r5,r5,#16` |
| `08007AAE` | `lsls r5,r5,#16` | `lsls r1,r1,#16` |
| `08007AB0` | `asrs r5,r5,#16` | `asrs r1,r1,#16` |

The four differing bytes are exactly at the addresses in the table. The two
operand-narrowing pairs commute but are scheduled in the opposite order.
The official command exits 1 at its first check:
`signed quotient caller requires exact complete mapped ROM bytes`.
It produces no match report. This candidate is therefore not byte exact.

Separately, passing the actual exact ROM body and complete canonical call
bindings into the unchanged profile rejects with:
`signed quotient requires a CFG-proven positive signed32 constant in r1`.
The outer divisor comes from the second helper return and is dynamic, may be
negative and may be zero. Even eliminating the byte mismatch would not satisfy
the approved positive-constant profile. Neither tool changes nor a fallback
profile were attempted.

| Artifact | SHA-256 |
| --- | --- |
| Final C | `4e977127759c109f7ec470bb71c46dc19ffdc79a6e2fed181d35728635f356a7` |
| Complete ROM caller | `a31bd351a3dac4c8b343fb8323bfb2484a6fc507f735e9ede3347b908008575e` |
| Complete linked candidate | `de2e2d3d92d81263092ec5122b3ad53d9774ff3bc0b31a3c502ac734f140a3dd` |

The first form declared signed16 helper returns and signed16 temporaries;
agbcc emitted 58 bytes / 26 instructions, including early truncation of the
first result before the second call. The single correction represents the
helper's full sign-extended r0 result as signed32 and narrows operands at the
division, consistent with the ROM preserving full r0 in r5 until both calls
have completed. This avoids inventing a short-lived narrowed temporary.
No additional form, flag, register/layout constraint, asm, volatile, pragma,
dead code or manual scheduling change was tried.

## Natural contract and arithmetic boundary

Input is signed16 `angle`. The first helper argument is that value; the second
is `s16(angle + 90)`. Addition is promoted to signed32 and cannot overflow.
The conversion back to signed16 is target-defined wrapping, verified with
agbcc; it is not portable-C signed narrowing. For example,32767+90 converts
to -32679, not a mathematical unbounded angle+90.

For each signed16 argument, actual `080071E8` normalizes into `[0,359]` by
adding/subtracting360, computes `(normalized << 8) / 360`, and reads a signed16
element from the256-entry accessed ROM window at `08149568`. Values in this
accessed window range from -256 to256; its zero entries are at indices0 and128.
This does not establish the table's nominal allocation size. The helper contains31 instructions
in `[080071E8,08007228)` and three literal words in `[08007228,08007234)`.
Its own division calls the same actual runtime with constant divisor360.

The caller narrows both full helper returns to signed16, performs signed32
division after integer promotion, then narrows the result to signed16. A
defined C invocation requires the second narrowed helper result to be nonzero.
There is no signed32 `INT_MIN / -1` risk: both promoted operands are signed16.
Even the artificial -32768/-1 case yields valid signed32 quotient32768, then
target-defined signed16 result -32768. Values in the accessed ROM window are much narrower.
No pointer arguments, objects or caller-owned output buffers are involved;
ordinary valid stack and callee ABI assumptions still apply.

The actual runtime's zero path calls `0814274C` (a real `mov pc,lr` leaf) then
returns zero. That machine behavior does **not** make division by zero defined
C. Tested zero-divisor paths are observations of the two machine-code bodies,
not C-equivalence cases or evidence that the current verifier should accept
them. Any future dynamic-divisor profile needs a precise nonzero/domain proof
or an explicitly different machine-semantics contract; weakening the existing
constant proof or naming an addressed runtime alias is not a repair.

## Bounded validation, with models identified

`check.py` creates disk-backed isolated fixtures from the immutable baseline,
copies all nine source/include headers, applies only the proposed instruction
count correction locally, invokes the unmodified approved toolkit, captures
the complete ELF and diagnoses canonical typed linking. Seven agbcc assertions
check type widths, signed16 conversion and integer-promotion division. Source
plausibility passes independently; the official rejection occurs before it
could produce a report.

Actual-ROM/candidate execution uses real `080071E8`, its literal pool and table,
real `081426B8`, and the real zero-path dependency `0814274C`. No helper or BIOS
is modeled in these47 paired cases /94 executions. Of these,39 pairs have
nonzero divisors and eight pairs are explicitly C-undefined zero-divisor
machine observations. Angles cover signs, quadrants, normalization wraps,
near-singular table indices and signed16 addition/narrowing edges. A separate
table/index/quotient oracle checks calls and result. Actual-path coverage is
caller24/24, helper31/31, runtime69/72 and zero dependency1/1 instructions;
this is not exhaustive path or all-input proof.

A separate eight-pair /16-execution suite explicitly **replaces only the two
071E8 calls with an arbitrary full-word ABI return model**, clobbering
caller-saved registers. The actual division runtime still executes. Seven
pairs exercise defined operand/result narrowing, signs and promotion limits;
one zero-divisor pair is again only a machine observation. These modeled
returns are not claimed to be obtainable from the real table.

Both suites check complete ordered memory-access traces including values,
exact call arguments/table reads, equal results, no non-stack writes, guarded
stack and EWRAM, preserved r4-r11/SP, and ARM/Thumb return interworking. The
maximum allowed call-chain stack depth is24 bytes. Four independent caller
mutations (angle offset, divisor signedness, numerator signedness, final result
signedness) fail the oracle. No tests claim universal equivalence, termination,
or defined C behavior for zero divisors.

Reproduce from a reviewer-owned copy of `check.py` and the final C using:

```sh
env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp \
PATH=/home/user/armtc/root/usr/bin:$PATH python3 check.py
```

The copy must remain under `/home/user/.codex-work/ffta-ulw/` so the pinned
sibling baseline/toolkit paths resolve. Evidence outputs are written beside
the script. Temporary fixtures and compiler products are deleted. No ROM or
compiled binary is retained. `results.json` records input and dependency hashes,
the exact case matrix and discrepancies; `SHA256SUMS` freezes this handoff.
