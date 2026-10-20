# 080D0ED4 — recovered, not byte-identical

## Result

The complete target is `[0x080D0ED4, 0x080D0F74)`: 160 bytes and
68 reachable instructions. Its 140 code bytes occupy
`[0x080D0ED4, 0x080D0F10)`, `[0x080D0F14, 0x080D0F40)`, and
`[0x080D0F48, 0x080D0F6C)`. Five literal words supply the remaining
20 bytes, without internal alignment gaps:

| Address | Value |
| --- | --- |
| `0x080D0F10` | `0x0855AE4C` |
| `0x080D0F40` | `0x020025C8` |
| `0x080D0F44` | `0x0836D4B8` |
| `0x080D0F6C` | `0x02000000` |
| `0x080D0F70` | `0x000028C8` |

The preceding zero halfword and the next entry at `0x080D0F74` are excluded.
The full target SHA-256 is
`16be0ac3d650c45c172e19f3e90fb8309152ae93654b10f3b9567163aca7b15e`.

The retained recovery produces exactly one `STT_FUNC`, whose complete
160-byte extent equals `.text`: 67 instructions, 138 code bytes, five
literal words, and one zero alignment halfword at `0x080D0F3E`.
Its linked SHA-256 is
`0961048e8c69baeb3d506aa08c18b49057e50d3320f146be73db37b68f73f41b`.
No separate inline-helper symbol is emitted.

The reviewed `2e2a664` matcher accepts the typed link, complete local CFG,
mapped data literals, and source plausibility, but reports
`NOT MATCHING - bytes differ`. Its aligned display reports 124/160 bytes;
only 70/160 bytes agree at identical offsets. Those are different metrics,
neither a MATCH nor a prefix-only comparison. No active source or match
report is retained. This is a local source/code-generation mismatch, not a
missing verifier feature or a claim that the function is unmatchable.

## Grounded interface and effects

The interface is `void func_080D0ED4(u8 *data)`. No additional incoming
register or stack argument is consumed. The target saves eight bytes and
has no local frame. Entry evidence is the indexed prologue, complete closed
CFG, and adjacent boundaries; no incoming cross-reference is asserted.

The first operation calls `func_080CF118(data, 0)`, before any caller record
read. This is a real, mutating helper, not a pure lookup. The recovery uses
its audited `void (u8 *, u8)` contract; its own parked C is not claimed to
match. After that call, the caller reads bytes `0x00` then `0x01` and forms
the ten-bit identifier. The definition is a 70-byte row of the existing
compatible `extern const u8 g_table_0855AE4C[][70]` declaration.

When definition byte `0x40` is nonzero, the caller reads data byte `0x02`,
preserves bits outside `0x1C`, replaces that category with three, and stores
it. It then reloads definition byte `0x40` and stores data byte `0x03`.
The ordinary three-bit category field expresses those independently
observed semantics, rather than a fabricated padding field. A target
compiler probe confirms the record is 16 bytes, duration is at `0x03`,
and category three changes byte `0x02` to `0x0C` in a zero-initialized
record.

Otherwise the caller searches exactly 64 nodes at RAM `0x020025C8` for
the first node containing the data pointer. Each node is 12 bytes, with
data, previous, and next pointers at `0x00`, `0x04`, and `0x08`; these
offsets and four-byte alignment were checked with the target compiler.
The private ordinary-inline lookup represents this meaningful operation.
Inlining is a plausible source organization, not proven historical source.

For a nonnull previous pointer, removal stores the next pointer into
`previous->next`, then updates `next->previous` if next is nonnull. For a
null previous pointer, it first updates a nonnull next node's previous
pointer, then stores next into the head at
`g_state_02000000 + 0x28C8`. The existing opaque byte-array global
declaration is preserved; the node-pool address is a separate grounded RAM
view, not a fabricated enclosing structure.

Removal reloads the selected node's data pointer, loads the callback through
ROM slot `0x0836D4B8`, and calls it with byte count 16 through the actual
`bx r2` thunk at `0x0814224C`. Only after that call does it store null into
the node's data field. The actual slot contains Thumb address `0x03005E79`.
The audited startup copy places ROM `[0x08A38A2C, 0x08A38ADC)` at RAM
`[0x03005E78, 0x03005F28)`; the copied block SHA-256 is
`ce26dd719323641c1c4cbfa501368306ce6e31e193dabce7e84c7067f7590130`.
The first 50 bytes implement the initializer used here. The local
`void (void *, u32)` callback view describes this positive count-16 call,
not every possible count or an arbitrary replacement callback.

No null, bounds, or missing-node guard is added. In the ROM, an unsuccessful
64-node scan sets the node pointer to zero and faults while reading address
`0x00000004`. Dereferencing that null pointer is undefined in C; the
machine-only fault fixtures below are not valid-C equivalence evidence.
Defined execution requires the actual helper's valid data domain, readable
definition storage, a matching node on the removal path, writable aligned
node/head storage, and the actual initialized callback code. Neither table
allocation bounds nor arbitrary alias validity are inferred. There is no
linked-list traversal here and no assumed acyclicity.

## Bounded natural attempts

Both attempts used ordinary agbcc `-mthumb-interwork -O2`:

1. Direct byte operations and an inline-in-the-body scan with a found-node
   local: 152 bytes / 64 instructions. The official check rejected the
   complete symbol as shorter than 160 bytes, before byte comparison.
2. The retained three-bit category view and ordinary private lookup,
   with a branch-local view of the named state: 160 bytes / 67 instructions.

The second form reproduces the category store and required definition-byte
reload. It still allocates different identifier/scan registers, loads the
callback slot address near the call instead of before the scan, loads next
before testing previous, and places literals differently. The candidate
has two alignment bytes where the target has two additional code bytes.
No flags sweep, register constraints, forced inlining, dummy operations,
manual assembly, or control-flow/alignment forcing was used.

## Bounded behavior evidence

The retained disk-backed reproducer is:

```sh
PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp \
PATH=/home/user/armtc/root/usr/bin:$PATH \
python3 /home/user/.codex-work/ffta-ulw/080D0ED4-98/check_recovery.py
```

It freshly builds and typed-links the complete parked candidate, checks
the layouts and plausibility, and reproduces the official nonmatch in an
isolated tree with `--no-write`. Its temporary build trees self-clean.

441 paired fixtures / 882 executions run both complete caller bodies with
the actual ROM `080CF118`, actual thunk, and actual copied initializer;
no helper stubs or modeled callback effects are used. Twenty fixtures use
pristine ROM table bytes and 421 use explicitly synthetic table bytes.
Pristine bytes do not establish that every selected identifier is a valid
allocated game-table entry. All RAM fixtures are synthetic.

The cases cover all 256 category-storage byte values, all 64 pool slots,
first-match duplicates, each null/non-null neighbor combination, shared
and self-referential node pointers, upper unused identifier bits, real
helper mutations, and two expected missing-node fault pairs. All
68 target and 67 candidate caller instructions are reached, including the
failed-scan assignments in those machine-only fault cases.

The paired executions agree on ordered state/table/callback-slot reads
including values, ordered writes and call arguments, final RAM, untouched
table/code/slot storage, and saved registers/SP on returns. These traces
exclude instruction fetches, ROM literal fetches, and stack-memory events;
they are not a claim of identical instruction-level memory traffic.
Nested stack depths are 52 or 56 bytes for both bodies, while the caller's
own save area is eight bytes. No meaningful scalar return is inferred.
