# 08006720: signed-time interpolation recovery, not a match

## Disposition and complete-symbol evidence

This is one natural-C recovery, retained as Parked only. No active source or
successful match report remains. Original source provenance or inherent
unmatchability is not claimed.

- The complete ROM symbol is `[0x08006720,0x08006878)`, 344 bytes / 164
  instructions: 332 code bytes, two four-byte literals and two internal zero
  halfwords. Code intervals are `[0x08006720,0x080067CA)`,
  `[0x080067D0,0x0800685A)` and `[0x08006860,0x08006878)`.
- The literals at `0x080067CC` and `0x0800685C` both contain `0x03000940`.
  The zero halfwords at `0x080067CA` and `0x0800685A` are internal and included.
  The next function begins at `0x08006878`; there is no external alignment in
  the target span.
- Target SHA-256:
  `ef57997e8064759e162a95d674db181d793a6e610f334d9f427ef382394709a9`.
- Standard `agbcc -mthumb-interwork -O2` produces one code-defined `STT_FUNC`
  and a 324-byte `.text`, both ending at `0x08006864`. The candidate has 153
  reachable instructions, 310 code bytes, three literals and one internal
  zero halfword. There are no extra emitted functions or residual linked
  relocations.
- Diagnostic linked candidate SHA-256:
  `f9bdf88bd37d3dbb4a76b9586d9e37909d8dad4a5a6eaca847fa4dc8f2635aaa`.
- Of the 324 overlapping positions, 58 bytes agree and 266 differ; 20 target
  bytes are absent. These counts are diagnostics, not a partial MATCH score.

The first and only source form was retained. Its local frame is four bytes
instead of eight, with the same 32-byte register-save area. Other differences
include loop strength reduction, register allocation, absolute output-byte
addresses in the pools instead of the observed base-plus-offset operations,
and removal of the target's discarded global reads. No artificial loads,
volatile access, register/storage forcing, padding or compiler-flag search
was used to restore those effects.

## Official proof boundary

The frozen `kit-reviewed-4847c93` official matcher rejects the compiler-generated
`__divsi3` relocation with `call target must be an undefined addressed function`.
The source preserves natural signed `/`; it does not name the runtime to evade
the unsupported profile. This is distinct from the independently established
complete-byte mismatch.

For diagnostics only, the ordinary compiled object was linked with a scratch
typed Thumb definition binding `__divsi3` to audited entry `0x081426B8`.
Undefined symbols, relaxation, unexpected sections and linker stubs were
rejected. Raw fixed-frame CFG checking then accepted all 153 instructions
with ordinary direct-call summaries. This scratch binding is not official
relocation proof, successful report replay or a MATCH. No toolkit change was
made or requested.

## Interface, layouts and ordered behavior

The compatible three-position interface returns `u32` and receives an unused
first pointer, an `InterpolationEvent *` second argument and an
`InterpolationPayload *` third argument. The first position is not deleted.
No incoming stack argument is used; every normal path returns full-word zero.
This is local ABI evidence, not unique original typedef or registration proof.

The four-byte record contains two serialized timestamp bytes and two unsigned
channel bytes. Target-compiler assertions establish its four-byte size and
four-byte aggregate alignment, with channel offsets two and three. The event
has state at zero, record pointer at four and signed count at `0x14`, with
size `0x18`. The payload has record pointer at zero, signed word count at four,
loop byte at eight and cursor halfword at `0x0A`, with size `0x0C`. The private
`TransitionOutput` tag and members reproduce the existing `0800664C` view:
unknown bytes through `0x4B`, then the two output bytes at `0x4C/0x4D` relative
to `0x03000940`. No conflicting named global or shared header was introduced.

- Event state zero copies the record pointer, then reads/sign-extends the
  event count and stores it to the payload. Loop/cursor are not initialized.
- State one and states other than `0x100` perform no transition work.
- State `0x100` snapshots the record pointer and signed count. It searches
  adjacent four-byte records using signed16 timestamps reconstructed from
  bytes, and a live signed16 cursor read for each tested interval. It stops
  at the first containing interval or the final record. A nonpositive count
  still selects the base record; it is not an empty-array guard.
- A terminal nonnull record supplies the two output bytes in order. Otherwise
  start time, elapsed and duration are narrowed as in the ROM; the first
  channel's base byte and both deltas are captured before division. First
  output is stored before the second quotient, and the second current byte
  is reloaded before its final output store.
- The payload cursor is reloaded, incremented and narrowed to u16. At a
  terminal record, a live nonzero loop byte resets cursor to zero; otherwise
  event state becomes two. No null/count/capacity guard was invented.

The target reads each old output byte immediately before replacing it. Those
discarded reads have no needed value in ordinary nonvolatile C and were not
forced into the recovery. The compiler also reorders independent record reads.
Exact read-footprint equivalence is therefore explicitly not claimed.

## Arithmetic and object domain

The ordinary domain requires valid aligned event/payload objects and readable
record storage for every selected/scanned record, plus writable output bytes.
The count is not proof of an allocation. Nonpositive-count cases still require
one accessible base record if that pointer is nonnull. General overlapping
aggregate validity, asynchronous mutation, callback registration, retention,
MMIO semantics and universal termination are not established.

Conversion of out-of-range integers to signed16 is target implementation-defined;
the recovery uses the observed two's-complement narrowing. Channel differences
are in `[-255,255]`, elapsed is signed16, and their products fit signed32.
Reached signed divisions require nonzero duration. In an unchanging ordinary
selected interval, signed start <= cursor < signed end gives a positive
timestamp difference in `[1,65535]`, whose signed16 narrowing is nonzero.
This observation is not a general concurrent/alias data invariant. No numerator
can reach `INT_MIN`, so the signed `INT_MIN / -1` overflow case is absent here.
Output sums are converted to u8, and the cursor wraps as u16.

The actual signed quotient routine `[0x081426B8,0x0814274A)` is 146 bytes,
SHA-256 `80b13b14c17b297e6c92a50aeddcacdffbe951729bcb1290e205055950655884`.
Its no-op zero handler `[0x0814274C,0x0814274E)` was loaded as real ROM bytes
but never reached in the tests. No portable division-by-zero behavior is claimed.

## Bounded execution evidence

The retained reproducer freshly compiles this source, repeats the official
rejection, checks all 15 target-layout assertions and scoped plausibility,
and executes 47 paired target/candidate fixtures, 94 executions total.
The caller target bytes and complete signed quotient runtime come directly
from the user's ROM. RAM is synthetic; there are no helper models or stubs.

42 pairs use ordinary disjoint object/record storage, including initialization
with signed count extremes, idle/default states, first/middle/final intervals,
negative timestamps, duplicate and descending timestamps, signed duration and
elapsed narrowing, negative quotients, output-byte wrapping, zero slopes,
nonpositive counts with an accessible base record and loop/cursor boundaries.
Five separate machine-only pairs use null-record or overlapping record/event
and output storage. They are not assertions of valid arbitrary C objects.

All pairs agree with an independent byte-operation oracle on ordered nonstack
writes, quotient arguments/order, final modeled EWRAM/IWRAM contents, zero
result, saved R4-R11, SP restoration and return control. Both bodies execute
34 real quotient calls over the suite; 65 quotient instructions are covered.
The target's ordered data accesses also agree exactly with the oracle.
Target/candidate read traces differ in 34 of the 47 pairs. These traces cover
only the modeled EWRAM/IWRAM state regions and exclude stack and instruction/
literal-pool fetches; no equal-read claim is made even within that scope.

Coverage is 163/164 target instructions and 152/153 candidate instructions.
The only uncovered instruction in either body is the branch at `0x08006740`:
the unsigned-halfword state cannot be below one while also being neither zero
nor one. It remains structurally present in both complete symbols. Caller
stack depths are 40/36 bytes; real division raises the respective peaks to
44/40 bytes. No faulting or looping test was presented as a completed return.

The small reproducer and build helper are retained outside the repository at
`/home/user/.codex-work/ffta-ulw/08006720-author/{check.py,build.py}`. Run:

```sh
env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp \
  PATH=/home/user/armtc/root/usr/bin:$PATH \
  python3 /home/user/.codex-work/ffta-ulw/08006720-author/check.py
```

Temporary isolated roots and binary build artifacts are cleaned by the script.
No ROM dump, binary or diagnostic linker artifact is retained in the repository.
