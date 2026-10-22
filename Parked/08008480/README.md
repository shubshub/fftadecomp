# 08008480 — Parked first natural recovery

This is not a match and earns no matched-function credit. One natural source
form was compiled with fixed agbcc `-mthumb-interwork -O2`; it remains unchanged.
No assembly, pragma, volatile, artificial storage, source spelling workaround,
flag search, addressed-runtime source alias, or altered function extent was used.

## Complete ownership and discrepancy

The ROM owns `[08008480,080086CE)`: 590 bytes, 287 Thumb instructions, including
eight four-byte BLs. Capstone recursive CFG and Binary Ninja instruction lengths
agree. Every byte is code; there are no pools or internal padding. The zero
halfword at 080086CE is external alignment before indexed entry 080086D0.
The two-map proposal changes only instruction count 295 to 287. Endpoints and
kind stay unchanged. It is a proposal against immutable game-next-94d6d0c, not
a production edit.

The full original ELF has one Thumb function, 590 bytes / 287 instructions,
inside a four-byte-aligned 592-byte `.text`; the external `c046` alignment is
not part of the function. It contains three canonical `__divdi3` and five
canonical `__muldi3` THM_CALL relocations, in the original compiler spelling.
The diagnostic typed link binds them to 08142280 and 08142A20 respectively.
It adds no veneer, allocated section, unresolved relocation, or function and
changes only the eight relocation sites. This binding is diagnostic, not an
official supported runtime proof.

Both complete bodies end at 080086CE, but only 249 of 590 equal-position bytes
agree: 341 byte substitutions, no missing tail. `results.json` lists every
changed byte; `diagnostic.txt` retains complete bytes and decoded candidate,
and `original-object.txt` retains the original relocation disassembly.
The ROM saves 32 bytes and allocates 36 local bytes (68 total); the candidate
saves 32 and allocates 40 (72 total). The fifth argument is at entry SP, loaded
from local SP+68 or SP+72. Register allocation and scheduling differ broadly.
The ROM count guard branches over an unconditional self-branch at 08008498;
the candidate instead repeats `cmp`/`ble` at 08008494/08008496.

| Item | SHA-256 |
| --- | --- |
| Source | `472eca301836017a138267ec2e544f1db295132abc5f1e68a3b1c96a804a26b3` |
| Full target | `fcce05c7af3445b6cbeabf467dbb617f220c7a10133645f58abed096a62b724e` |
| Full diagnostic candidate | `445a169ec09910f76239f3f9e2daff0a0f21a9bf11542b66edf02c53caed5e48` |

## Three separate acceptance limitations

1. There is a genuine full-body byte mismatch, independent of tooling support.
2. The approved ordinary matcher exits 1 with `call target must be an undefined
   addressed function` on the canonical signed64 runtime calls. `official.log`
   is the fresh `--mode thumb --no-write` result. No report is created and no
   strict replay success is claimed. The approved mixed-return-inert-spin-v1
   profile does not compose division/runtime numeric proofs; additionally this
   candidate's multi-instruction loop is outside that profile's narrow self-loop
   definition. No explicit-profile fallback was attempted.
3. Standalone `plausible.py` exits 1 with `empty-body`, describing line 13 as
   an empty function body. Its generic empty-braces regex matches the genuine
   `while (count <= 2) {}` body. This diagnostic is retained in full in
   `plausibility.log`, not relabeled as a passing gate or as evidence that the
   recovery is artificial. No semicolon-spelling change was made to evade it.

## Recovered typed contract

The five arguments are signed 32-bit count, two read-only signed64 arrays
`coordinates` and `values`, signed64 output `result`, and signed64 `workspace`
passed on the stack. Integer64 words are low then high on this target.
`workspace[0..count)` supplies intervals and `workspace[count..2*count)` supplies
pivots/slopes. Interval slot count-1 and pivot slot 0 are untouched.

For count greater than two, the function zeros both result endpoints, computes
adjacent coordinate intervals and scaled value slopes, then performs forward
elimination and backward substitution using signed64 multiply/divide and
arithmetic shifts by 16. This resembles a fixed-point tridiagonal interpolation
calculation; no original source name or higher-level spline identity is proved.
The source and checked integer oracle state the exact recurrence, including
the initial and final boundary multiplications even though their operands are
zero on the supported disjoint-array domain.

The bounded C contract requires valid aligned, live, disjoint arrays: count
elements for each input and result, and 2*count elements for workspace. Object
sizes and count/index arithmetic must fit the target address/signed32 domain;
the tests use counts 3 through 7, not every representable count. Every signed64
subtraction, addition, and multiplication must be representable, each computed
divisor nonzero, and no division may be INT64_MIN/-1. The natural source uses
multiplication by 65536 rather than left-shifting a potentially negative signed
value. Arithmetic right shift of negatives is target-defined and separately
checked with agbcc. Division truncates toward zero. These are typed C domain
limits, not claims that the ROM has defined C behavior for wrapping arithmetic,
bad pointers, aliasing arrays, zero divisors, or overflow. Both increasing and
decreasing coordinates occur in the valid cases; monotonicity alone is not a
proof of all required intermediate bounds or nonzero pivots.

For signed count at most two, the ROM does not return: after saving registers
and allocating its frame, it enters the actual unconditional self-loop. It
does not read the fifth argument or access pointed-to arrays on that path.
The compiled loop also remains nonreturning in the tested environment but has
different instruction/flag behavior. No spin-path ABI restoration is claimed.
Interrupts, hardware effects, timing, and concurrent memory changes are outside
this recovery's contract.

## Actual-helper bounded validation

`check.py` executes both caller bodies in Unicorn with actual ROM helpers,
never a helper-return model. The allowed helper closure is pinned and classified:

| Window | Grounded identity | ROM visited / CFG instructions |
| --- | --- | --- |
| 08142280..081426B8 | signed64 divide | 281 / 496 |
| 08142A20..08142A94 | signed64 multiply | 53 / 56 |
| 08142AB0..08142B28 | unsigned32 divide | 52 / 59 |
| 08142B28..08142BE8 | unsigned32 remainder | 88 / 95 |
| 0814274C..0814274E | division-zero return stub | 0 / 1 |

The first window includes its trailing literal omitted by its old mapped end;
no helper map edit is proposed here. The accessed 256-byte ROM window
0836CF98..0836D098 equals `bit_length(index)` exactly and is allowed read-only.
No larger table allocation size is inferred. Local libgcc2.c `L_divdi3` and
`L_muldi3`, lib1thumb.asm, longlong.h, and the compiler Makefile ground the
identities and are hashed as inputs. They are not substituted for executing
the actual helper machine code. No BIOS or floating-point helper is involved.

Ten returning ROM/candidate pairs cover count 3, forward-loop cases through
count 7, zero and alternating outputs, positive/negative numerators and
divisors, unequal spacing, fractional low bits, and values/coordinates with
nonzero high words. Five additional pairs use counts INT32_MIN, -1, 0, 1, 2:
each observes 32 stable loop samples without external access. Static CFG proves
the ROM self-branch, while finite sampling alone is not an all-state proof.
Thus 15 pairs / 30 executions pass. Both caller instruction sets are covered
287/287, not all paths or all helper branches.

Returning cases compare a checked integer recurrence, every ordered external
word write, all caller-to-helper operand bits (allowing multiplication operand
commutation only), the entire mapped 8 KiB arena including untouched slots,
r4-r11, SP restoration, and Thumb/ARM return state. Entry SP alternates its
word-aligned offset. Memory hooks enforce per-array bounds, the frame/stack
argument envelope and exact allowed ROM reads, rejecting global accesses.
All 32 KiB mapped IWRAM outside the bounded stack scratch remains unchanged;
the fifth-argument word is preserved. Observed maximum stack use is 156 bytes
for ROM and 160 for candidate. This is bounded emulation, not a universal
termination, memory-safety, compiler-correctness, or numeric-runtime proof.

Seven negative controls pass: boundary-value and signed-shift caller mutations,
an actual division-helper return mutation, one-word-short workspace guards for
each body, and oracle rejection of zero divisor and signed64 overflow. The
last two are explicit domain-exclusion tests, not executions of undefined C.
Six fresh agbcc scalar assertions and an eight-byte initializer independently
check sizes, right shift, signed division, negative scaling, and word order.

## Reproduction and immutable inputs

Run a copy of the checker and source in an owned sibling review directory to
avoid overwriting this frozen evidence. It uses immutable game-next-94d6d0c,
all nine headers, and kit-inert-spin-candidate-v2. Its official subprocess is:

```sh
env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 TMPDIR=<owned-disk-fixture> \
  PATH=/home/user/armtc/root/usr/bin:$PATH python3 \
  /home/user/.codex-work/ffta-ulw/kit-inert-spin-candidate-v2/tools/match.py \
  --root <owned-isolated-fixture> --mode thumb --no-write 0x08008480
```

For the complete checker, use the same environment with `python3 check.py`.
`results.json` pins ROM, source, all nine headers, both index inputs and proposed
outputs, data symbols, compiler executable, local runtime sources, and toolkit
inputs. The ROM SHA-1 is `4ac05441f4de70a4ec3dd932116346c61b8783d9`.
All temporary fixture/compiler products are disk-backed and self-cleaned.
Only source and text evidence remain; no production, shared, or lease state
was modified. Root owns any Parked integration and reservation release.
