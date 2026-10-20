# 080D17C4 — recovered, not byte-identical

## Complete target and result

The complete target is `[0x080D17C4, 0x080D1A18)`: 596 bytes and
260 reachable instructions. Its SHA-256 is
`b1c0a6e664b45efd0525835582a1631f147035f7e7f8c8dbf9853dc2b4971cc4`.
The 528 code bytes occupy these intervals:

- `[0x080D17C4, 0x080D1812)`
- `[0x080D1818, 0x080D18E0)`
- `[0x080D1904, 0x080D1924)`
- `[0x080D1928, 0x080D19E6)`
- `[0x080D19FC, 0x080D1A18)`

Sixteen literal words occupy `[0x080D1814, 0x080D1818)`,
`[0x080D18E0, 0x080D1904)`, `[0x080D1924, 0x080D1928)`, and
`[0x080D19E8, 0x080D19FC)`. Zero alignment halfwords are at
`0x080D1812` and `0x080D19E6`. The next entry at `0x080D1A18` is excluded.
Entry evidence is the indexed prologue, complete CFG and neighboring
boundary; no incoming cross-reference is asserted.

The retained recovery emits exactly one `STT_FUNC`, whose complete size
equals `.text`: 608 bytes and 262 instructions. It contains 532 code bytes,
17 literal words and eight alignment bytes. No separate inline-helper
function is emitted. Its linked SHA-256 is
`19262d2aef41a3879dae7abef73d70bfab9194d3452ae7ce40156b74fbe0b361`.

The reviewed `2e2a664` matcher accepts typed linking, the framed local CFG,
mapped data, the concrete indirect-call thunk and source plausibility,
then reports `NOT MATCHING - bytes differ`. Its comparison display follows
the larger 608-byte candidate extent, including 12 bytes beyond the true
596-byte target. That display is not a true-target byte count. A separate
positional comparison restricted to the complete target finds 54/596 equal
bytes. No prefix truncation, MATCH claim, active source or active report is
retained. This is a local recovery mismatch, not a verifier blocker or a
claim that the function cannot be matched.

## Interface and data views

The compatible interface is
`u32 func_080D17C4(u32 filter, u8 slot_value, u8 *kind_out)`.
The filter is compared as a full word; the second argument is normalized
to its low byte. The output is a byte store and the return is consumed as
a full word. No additional incoming register or stack argument is used.
Both target and candidate save 32 bytes and reserve four local bytes.

The five initial slots use the existing compatible declaration
`extern u8 g_state_02002E34[][6]`. Definition records use the existing
`extern const u8 g_table_0855AE4C[][70]`; the second table uses canonical
`script_entry.h`, with 12-byte rows and the first byte as the filter field.
Neither unsized table declaration invents an allocation bound.

The private header describes the observed 16-byte record, its ten-bit
identifier in bytes `0x00` and `0x01`, and its three-bit category in byte
`0x02`. These are meaningful fields, not unused fields added to steer code.
The separate node view is 12 bytes, with data, previous and next pointers
at `0x00`, `0x04` and `0x08`. The opaque `g_state_02000000[]` declaration
remains compatible; a local view names only the head at `0x28C8` and the
selected identifier at `0x3C28`. The node pool has its independently
grounded address `0x020025C8`, rather than a biased enclosing base.

A target-compiler probe confirms record size 16, alignment four, the
category mask `0x1C` in byte `0x02`, node size 12/alignment four and all
three pointer offsets, both state offsets, and ScriptEntry size 12 with
alignment four. The private ordinary-inline helpers express identifier
extraction, the excluded identifier range, node lookup and removal.
Inlining is a plausible organization, not proof of historical source.

## Ordered behavior

The initial scan checks slots in ascending order: nonzero low three bits
of byte `0x00`, clear bit `0x80` of byte `0x01`, and the low five bits of
byte `0x02` equal to the byte argument. On a match it stores output three
before reloading bytes `0x02` and `0x03` to form the returned eight-bit
value. This reload matters when the output aliases a slot byte.

After an unsuccessful slot scan, the function caches
`func_080C9540(0x36)` and calls `func_0800A5D4(1)`, testing the full return.
If nonzero, it stores output one before reloading the list head. This
first traversal excludes identifiers `0x150` through `0x166`, nonzero
record categories, and definitions whose byte `0x02` low three bits are
neither four nor five. The cached flag additionally suppresses identifier
`0x1A`.

Identifier `0x18D` is removed only when `func_080C9540(0x48C)` is nonzero.
Removal searches the first matching data pointer among all 64 pool nodes,
not necessarily the current traversal node. It splices previous/next
pointers in observed order, updating a nonnull next node's previous field
before the global head in the head-removal case. It reloads the found
node's data pointer, clears 16 bytes through the function slot
`0x0836D4B8`, and then sets the found node's data pointer to null. The
traversal's next pointer is reloaded after this operation.

The actual slot contains `0x03005E79` and uses the `bx r2` thunk at
`0x0814224C`. Startup copies 176 bytes from
`[0x08A38A2C, 0x08A38ADC)` to `[0x03005E78, 0x03005F28)`; that copied
block has SHA-256
`ce26dd719323641c1c4cbfa501368306ce6e31e193dabce7e84c7067f7590130`.
The first 50 bytes implement the initializer used here. The local
`void (void *, s32)` view describes the actual positive count-16 call,
not arbitrary replacement callbacks.

For other eligible records, a nonzero definition byte `0x45` causes output
two, a live identifier reload and store at `0x02003C28`, then a definition
byte reload for the return. If that definition byte is zero, the function
instead stores the earlier cached identifier before reloading the live
identifier for its return. These store/reload distinctions are retained.

The fallback reloads the head and repeats the range/category checks. It
requires a nonzero definition byte `0x45`, a script-table first byte equal
to the full filter, definition kind four or five, and the definition's
own little-endian halfword at `0x00` unequal to `0x1A`. This last test is
not a comparison against the record identifier. It stores output two
before reloading definition byte `0x45`. Exhaustion stores output zero
and returns zero.

## Interpreter boundary and valid domain

The declarations `u8 func_080C9540(u16)` and
`u32 func_0800A5D4(u8)` agree with the audited active definitions.
On its ordinary returning path, A5D4 invokes A06C, A0B8, A10C and the
A154 bytecode interpreter. A10C finishes initializing the eight-byte
context before the interpreter. Opcode zero returns one; other opcodes
dispatch dynamic handlers and continue. A5D4's normal real result is the
post-interpreter byte at `0x0200219C`, not a normalized Boolean or a pure
lookup. Arbitrary handler effects, retention and termination remain
outside this bounded audit.

Defined C execution requires readable record/table storage, writable
output and aligned state/node storage, suitable mutable backing for
records passed to the initializer, and a matching pool node when removal
is attempted. The fixed-address views describe this target's memory ABI,
not arbitrary ISO C object-lifetime or interior-alias guarantees.
Character-pointer output aliases are not excluded with `restrict`.
Machine overlap tests do not establish that every raw overlap is a valid
C object arrangement.

An unsuccessful 64-node lookup dereferences address `0x00000004` in the
ROM and candidate. No invented guard is added; this is undefined in C and
is tested only as machine behavior. List cycles are possible and no
termination or acyclicity guarantee is inferred. A nonzero dynamic opcode
may also fail to return; no unconditional caller-termination claim is made.

## Bounded natural attempts

All attempts used the standard agbcc `-mthumb-interwork -O2` settings:

1. Raw slot bytes, a function-scoped semantic state view and the private
   inline operations: the retained 608-byte / 262-instruction candidate.
2. Branch-local state views and a natural slot-bitfield view: 612 bytes.
   This representation was discarded because emitted word accesses are
   unsuitable for alternating six-byte rows and change the read footprint.
3. Raw slot bytes restored, with branch-local state views: 612 bytes,
   without improvement. The first canonical form was restored.

The retained code still differs in register allocation, low-five-bit
slot extraction, node-scan scheduling and literal placement/repetition.
There are 12 additional bytes overall. No flag sweep, forced inlining,
manual assembly, manufactured branch, register constraint or alignment
directive was used.

## Reproduction and bounded execution evidence

From the game root:

```sh
PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp \
PATH=/home/user/armtc/root/usr/bin:$PATH \
python3 /home/user/.codex-work/ffta-ulw/080D17C4-98/check_recovery.py
```

The retained `build.py`, `layout.c` and `check_recovery.py` compile and
typed-link the complete parked candidate, assert one emitted function,
check layouts and plausibility, and reproduce the official nonmatch in an
isolated `--no-write` tree. Generated build trees self-clean.

409 paired fixtures / 818 executions cover all 260 target and all 262
candidate instructions. Of these fixtures:

- 168 return from the initial slot scan before A5D4 is called.
- 220 execute the actual complete A5D4 chain using pristine bytecode
  tables and the actual zero opcode at `0x08A1ABEB`, with selector zero.
- 21 explicitly model the A5D4 boundary, including memory mutations and
  caller-saved register clobbers. Eight of these use returns above 255 as
  ABI-adversarial models, not values claimed from the actual helper.
- 27 use pristine definition/script table bytes; the other 382 use
  explicitly synthetic table fixtures. All RAM fixtures are synthetic.
- One pair reproduces the missing-pool-node fault as machine-only evidence.
  Two pairs compare bounded cyclic prefixes, stopping after 32 next-field
  reads rather than asserting termination.

Whenever invoked, the flag getter, indirect thunk and copied initializer
execute their actual bytes without stubs. The actual opcode-zero cases
check the initialized context and stream pointer. Dynamic nonzero-opcode
handlers are not represented as real execution.

Cases include all five slots and all 32 slot values, high second-argument
bits, full-width filters, range boundaries, categories and definition
kinds, the definition's own identifier test, output aliases into slot and
record bytes or the selected halfword, cached-versus-live identifier
effects, cached flag mutation, post-A5D4 head changes, removal at pool
positions 0, 7 and 63, every previous/next combination, and duplicate data
pointers where the first matching pool node is not the traversal node.

An independent operation model checks results and final RAM. Target and
candidate additionally agree on ordered state/table reads, data writes,
calls and arguments, complete fixture RAM, and saved registers `r4` through
`r11`, SP and return control on returning paths. There are zero observed
data-trace differences. These trace hooks exclude instruction fetches,
ROM literal fetches and stack-memory accesses; stack depth and restoration
are checked separately. Observed stack depths are 36, 40 and 84 bytes in
both bodies. This bounded agreement does not turn a nonmatching recovery
into a byte match or prove all possible aliases and interpreter paths.
