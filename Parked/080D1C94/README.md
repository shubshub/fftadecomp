# 080D1C94 — recovered, not byte-identical

## Complete extent and verdict

The complete target is `[0x080D1C94, 0x080D1E70)`, 476 bytes and
222 reachable instructions. Its ROM-body SHA-256 is
`6e8c350361e0a8ba99a1181cfdfaa7647c8a54acbc5a47d7055b9b2102c0ecb0`.
The 448 code bytes occupy:

- `[0x080D1C94, 0x080D1D1E)`
- `[0x080D1D30, 0x080D1E06)`
- `[0x080D1E10, 0x080D1E70)`

Six literal words occupy `[0x080D1D20, 0x080D1D30)` and
`[0x080D1E08, 0x080D1E10)`. Their values are, respectively,
`0x02000000`, `0x000028C8`, `0xFFFFFEB0`, `0x0855AE4C`,
`0x02000000` and `0x00003C2B`. Internal zero halfwords are at
`0x080D1D1E` and `0x080D1E06`. The next entry starts immediately at
`0x080D1E70`; no external alignment is included in the target.

Bounded Binary Ninja analysis, an independent raw instruction worklist,
and the frozen `2e2a664` framed/direct-call CFG verifier agree on all
222 target instructions. Entry evidence is the indexed prologue, closed
CFG and next boundary; no incoming cross-reference is asserted.

The retained recovery emits exactly one `STT_FUNC` of 474 bytes and
221 instructions: 446 code bytes, six literal words and four internal
alignment bytes. Its linked function SHA-256 is
`b5c6357e21c07cb8c9659aa3840b44857f00a6347672ad45de7475709f03db04`.
The ELF `.text` is 476 bytes because the assembler appends the permitted
two-byte Thumb NOP `C0 46` outside the function symbol. That external NOP
does not enlarge the function and cannot supply the missing target bytes.
No private inline helper is emitted as a separate function.

The official frozen matcher rejects the recovery before comparison:
`compiled symbol is shorter than the indexed span: 474 < 476`.
Separate diagnostic typed linking, mapped-literal validation, local CFG
verification and scoped source plausibility pass. A separate positional
comparison finds 59 equal bytes among the 474 shared positions; the final
two target bytes have no candidate-symbol counterpart. This is not an
official byte score, a complete match, or a prefix-only verification.
No active C, private header or match report remains.

## Grounded interface and effects

The compatible interface is
`u32 func_080D1C94(u8 **expired_records, u32 limit, u8 advance)`.
The output pointer and limit are full words; only the low byte of advance
is consumed. There are no hidden incoming registers or stack arguments.
The full-word count is returned. Both bodies save 32 bytes, but the target
uses 12 local bytes whereas the candidate uses 16.

The state head is at `0x020028C8`; the saturating step is the byte at
`0x02003C2B`. The existing opaque `g_state_02000000[]` declaration remains
compatible, with a local state view naming these observed fields. Nodes
have data, previous and next pointers at offsets `0x00`, `0x04`, `0x08`.
This function reads data and next, not previous. A target-compiler probe
confirms node size 12, alignment four, all pointer offsets, and the two
state offsets. No arbitrary allocation size follows from the view.

Definitions use the existing compatible unsized byte-row declaration
`extern const u8 g_table_0855AE4C[][70]`. The function reads definition
byte `0x02` and mode bits `0x38` of byte `0x10`. It does not establish an
outer table count.

The function walks the list from its initially loaded head. For each
record it forms the ten-bit identifier from byte `0x00` and the low two
bits of byte `0x01`. It skips identifiers `0x150` through `0x166`, records
whose byte `0x02` has any `0x1C` category bit set, and definitions whose
byte `0x02` low three bits are nonzero. Only eligible records reach mode
processing. Modes zero and four through seven do nothing.

The countdown is packed across bytes `0x01` and `0x02`:
`(byte1 >> 2) | ((byte2 & 3) << 6)`. The setter preserves the identifier
bits in byte `0x01` and the upper six bits of byte `0x02`, storing byte
`0x01` before byte `0x02`. The ordinary private inline getter, setter and
advance operation express these reused semantics. Their original source
provenance is not known; they are not asserted to be historical helpers.

- Mode one decrements a nonzero countdown only when low-byte advance is
  nonzero, and emits the record only when the decrement reaches zero.
- Mode two first calls `func_080C9540(0x45)`. On a nonzero low-byte result,
  it decrements a nonzero countdown and emits only on reaching zero.
- Mode three makes the same flag call. For a nonzero countdown it reads
  the state step, subtracts with saturation at zero and emits only when
  saturation reaches zero. A zero step still performs both stores for
  a nonzero countdown but does not emit.

An already-zero countdown never emits. The only actual callee is the
matched `u8 func_080C9540(u16)`, whose complete 50-byte body reads one
bitset byte and returns zero or one without data writes or nested calls.
Argument `0x45` tests mask `0x20` at `0x02001F78`. The two call sites
remain distinct; the flag is not cached across records.

Emission stores the record pointer through the output cursor, advances
the cursor, increments the count and only then compares count with the
full-word limit. There is no initial zero-limit guard. A zero limit does
not prevent writes. On equality the function returns without loading
next; otherwise it reloads the current node's next pointer after all
record and output writes. List exhaustion returns the current count.
The routine neither unlinks nodes nor clears complete records.

## Read-footprint limitation

The retained source produces correct bounded results and ordered writes,
but does not reproduce every target read. This is a behavioral
read-footprint difference, not merely register allocation:

- Mode one in the target reloads byte `0x02` for the initial countdown
  after the category check and again after the countdown stores. The
  candidate reuses already loaded or computed values.
- Modes two and three reload byte `0x02` after the helper for the initial
  countdown in both bodies. The target additionally reloads it after the
  byte `0x01` store to preserve unrelated bits; modes one and two also
  reload it for the post-store zero test. The candidate omits these
  redundant stable-RAM reads.

All observed candidate data events are an ordered subsequence of target
events in the fixtures. The skipped events are exclusively one-byte reads
of the corresponding record's byte `0x02`. Equality of complete read
traces, volatile/concurrent memory behavior, or arbitrary machine aliases
is not claimed.

## Bounded natural attempts

All forms used ordinary agbcc `-mthumb-interwork -O2`:

1. A direct byte-operation switch with a local expiration result:
   438 bytes; rejected as shorter than the complete target.
2. The retained meaningful private inline byte getter/setter/update and
   excluded-range predicate: 474 bytes / 221 instructions.
3. The same organization with observed record bitfields for the split
   countdown: 448 bytes / 210 instructions. This did not improve the
   complete match, so the ordinary byte-access form was restored.

The retained code differs in frame size, count spilling, register
allocation, mode extraction, branch organization, repeated reads and
literal placement. It remains two function bytes shorter despite the
extra local word. No compiler flag sweep, forced inline attribute,
register or storage constraint, artificial branch, alignment directive,
volatile access or manual assembly was used. This is a local recovery
result, not a claim of inherent unmatchability or a verifier limitation.

## Reproducer and execution evidence

From the game root:

```sh
PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp \
PATH=/home/user/armtc/root/usr/bin:$PATH \
python3 /home/user/.codex-work/ffta-ulw/080D1C94-98/check_recovery.py
```

The retained `build.py`, `layout.c` and `check_recovery.py` rebuild the
complete parked function, verify its sole function symbol and external
padding, check the target layouts and source plausibility, and reproduce
the official short-span rejection in an isolated `--no-write` tree.
Generated build artifacts self-clean.

825 paired fixtures / 1,650 executions cover all 222 target instructions,
all 221 candidate instructions and all 22 instructions of the actual
flag getter. No callee is stubbed or modeled. Forty fixtures use pristine
definition-table bytes; 785 use explicitly synthetic table data. All RAM
fixtures are synthetic and do not prove allocation bounds.

The fixtures cover all modes; countdowns 0, 1, 2, 63, 64, 65, 127, 128,
254 and 255; low-byte advance normalization including `0x100` and
`0xFFFFFFFF`; zero, exact and larger full-word limits; step zero and
below/equal/above-countdown boundaries; excluded identifiers, categories
and definition kinds; multi-record call/store order; and overlapping
output locations. One explicitly machine-level overlap makes an output
write alter the live next pointer and supplies readable backing for the
resulting traversal. This confirms the reload order without asserting
that the raw overlap is a valid ISO C object arrangement.

An independently specified operation model checks full return values,
final fixture RAM and ordered helper calls and data writes. The two
bodies agree with this model. Ordered read traces differ in 186 pairs,
only by the byte-`0x02` omissions described above. All other observed data
events agree. Trace hooks cover state/table data reads and writes and
call arguments, excluding instruction fetches, ROM literal fetches and
stack-memory accesses. Saved registers `r4` through `r11`, SP and return
control are checked on returning paths. Observed stack depths are
44/48 bytes for the target and 48/52 bytes for the candidate.

Five pairs are bounded cyclic prefixes, stopped after 32 next-pointer
reads, not termination proofs. Valid ordinary execution requires readable
aligned nodes, readable definitions and record bytes, writable record and
output storage, and sufficient pointer-output capacity for the actual
path. Node data is dereferenced without a null guard. There is no claim
of arbitrary alias validity, list acyclicity, or unconditional termination.
The fixed-address state view describes the target ABI rather than a
general ISO C object-lifetime guarantee. These limits and the real read
differences remain explicit even though the bounded results agree.
