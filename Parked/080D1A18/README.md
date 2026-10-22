# 0x080D1A18 — recovered, not byte matching

## Complete-symbol result

The complete ROM function is `[0x080D1A18,0x080D1B80)`: 360 bytes,
154 reachable instructions, 318 code bytes, ten literal words and one internal
zero halfword. The next function starts at `0x080D1B80`; it is not padding.
The target SHA-256 is
`7b52852892a0093cbd4cffe62e574982b8942d0c7238ffad05c1c37f4a6f86a9`.

The retained source compiles with agbcc `-mthumb-interwork -O2` to exactly one
362-byte function containing 155 instructions, 320 code bytes, ten literal
words and one internal zero halfword. The ELF `.text` section is 364 bytes;
its final two alignment bytes are outside the function and are not counted.
The complete linked function SHA-256 is
`b7d06782877cf6eab937da9864bb74f322ce85c508a363df37e156e45d06e997`.

Frozen toolkit `2e2a664` accepts ordinary typed linking, the complete local
CFG, named data literals and source plausibility, but reports **NOT MATCHING —
bytes differ**. This is not a verifier limitation or a byte-match claim.
There are 126 equal byte positions within the 360-byte target and 31 identical
same-address instructions. Thus 234 target positions differ, and the candidate
has two additional function bytes. No candidate prefix is treated as a match.
The matcher's alignment-based display can include following ROM bytes for an
oversized candidate; the measurements here compare only the actual target
extent and the entire ELF function.

The retained candidate has one additional `adds` instruction in the node-pool
search: it copies the advancing node pointer before loading the data word.
Its register allocation, pool placement, callback-slot load scheduling, loop
increments and branch displacements also differ. In particular, the target
loads the callback-slot address before the pool scan, whereas the candidate
loads that constant near the callback. Neither difference justifies forced
registers or artificial lifetime/control-flow changes.

## Bounded source attempts

Only three ordinary source forms were checked at the standard flags:

1. A persistent state-view local and an early preparation-failure return:
   376-byte function.
2. Direct state views and branch-local next-pointer reads in the unlink helper:
   372-byte function.
3. The same operations enclosed by the positive preparation-result guard:
   the retained 362-byte function.

The private header contains meaningful identifier, excluded-range, node-search
and removal helpers. Their ordinary inlining is consistent with repeated
observed operations in neighboring recoveries; original inline provenance is
not uniquely established. There are no forced-inline attributes, register
bindings, extra emitted helpers, assembly, volatile accesses or dummy work.

## Interface, layout and order

The compatible interface is `u32 func_080D1A18(u8 *kind_out)`. Direct incoming
register use establishes one output pointer and no incoming stack arguments;
the exact original nominal return type is not uniquely recoverable. Normal
results are zero, a definition byte, or a reconstructed ten-bit identifier.

The source preserves these ordered operations:

- Cache `func_080C9540(0x36)` before `func_080CFCD0(0)` and
  `func_0800A5D4(0)`. Test the latter's full word. A zero result returns without
  this function writing the output byte.
- Otherwise write output kind 1, then reload the head at `0x020028C8`.
  There is no fallback scan and no final output-zero write.
- Traverse node data/previous/next words at offsets `0x00/0x04/0x08`.
  Cache the identifier from two separate bytes. Reject `0x150..0x166`, nonzero
  record category bits `0x1C`, definition kinds other than 4/5, and identifier
  `0x1A` when the cached flag is set.
- For identifier `0x18D`, query flag `0x48C`. If set, find the first matching
  data pointer among 64 nodes at `0x020025C8`, stride `0x0C`; unlink it in the
  observed store order; reload its data pointer; call the actual clear slot
  `0x0836D4B8` with count `0x10`; then clear the found node's data word.
  Continue by reloading the original traversal node's next pointer.
- For a nonzero definition byte `0x45`, write output kind 2 before rereading
  identifier bytes, write the live identifier at `0x02003C28`, then reread and
  return definition byte `0x45`. Otherwise store the cached identifier first
  and reread the identifier bytes for the return value.

Target-agbcc checks establish record size 16/alignment 4, category bits 2..4
at byte `0x02`, node size 12, previous/next offsets 4/8, and state-view offsets
`0x28C8` and `0x3C28`. `SelectionRecord`/`Node` use the compatible declarations
from the neighboring parked selection routines. The named global remains
opaque `extern u8 g_state_02000000[]`; the definition table remains compatible
`extern const u8 g_table_0855AE4C[][70]`. The state view describes observed
offsets, not a recovered original allocation or encompassing object identity.

`func_080CFCD0(u8)` is a mutating void helper. Input zero skips its optional
refresh calls but does not make the remaining scan pure. Its saved return
address in `r0` is not a scalar result. `func_0800A5D4(u8)` has a compatible
full-word return declaration; actual normal completion returns the state byte
after dynamic interpretation. Dynamic handlers may retain, mutate or fail
to terminate. Caller verification does not recursively prove those helpers.

## Bounded execution evidence

The retained reproducer is
`/home/user/.codex-work/ffta-ulw/080D1A18-08/check_recovery.py`.
It compiles this source afresh, verifies the full ELF and target layouts, and
executes both bodies against an independently written memory/call model.

115 paired fixtures / 230 executions pass result, whole EWRAM, ordered
non-stack data reads and writes, call order/arguments, preserved `r4..r11`,
SP, return control, and unchanged non-stack IWRAM checks. All 115 paired data
traces agree; instruction/literal fetch scheduling is intentionally excluded
from that trace claim. Both bodies use at most 36 stack bytes in these cases
(32 caller saves plus four helper saves).

The fixtures execute the real 22-instruction `0x080C9540` predicate, the real
`0x0814224C` thunk and the real copied 25-instruction clear body at
`0x03005E78`, backed by ROM `[0x08A38A2C,0x08A38A5E)`. Each side makes 132
predicate calls and nine clear calls. **CFCD0 and A5D4 are explicit mutating
boundary models**, each invoked 115 times per side, not executions of those
large engines. The models mutate head/record/flag storage and clobber
caller-saved registers, exercising post-call reloads and cached flags.
Full-word A5D4 model returns `0x100` and `0xFFFFFFFF` test the caller's width;
they are not claimed to be actual normal A5D4 results.

Coverage is 153/154 target and 154/155 candidate instructions, with complete
22/22 predicate, 25/25 clear and one-instruction thunk coverage. The only
unexecuted caller instruction is the failed-search null assignment
(`0x080D1AD6` in ROM, `0x080D1AD8` in the candidate). No valid matching-node
fixture reaches that assignment. Tests cover both preparation/head failures,
all eight category and kind values, excluded-range edges, cached-flag changes,
nonzero definition returns, first/last pool slots, head/interior/tail removals,
duplicate data pointers, and output/selected-storage overlap.

All RAM and definition records in these fixtures are explicitly synthetic.
Seven output/selected-storage overlap cases establish only the observed
machine ordering, not arbitrary valid C aliasing. One unaligned-record fixture
exercises the real byte-clear path but lies outside the recovered record's
four-byte alignment contract; it is machine-only evidence, not portable C.

Valid C requires readable/aligned nodes and records, valid accessed table rows,
a writable output byte when reached, compatible storage/effective types for
typed state views, and a matching pool node on the removal path. Missing-node
removal dereferences null in the original machine and is not repaired with an
invented guard. List termination, complete allocation/table bounds and dynamic
handler behavior are not proved. The recovery remains parked; no active
source/header or successful match report is retained.
