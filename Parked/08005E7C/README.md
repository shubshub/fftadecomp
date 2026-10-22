# 08005E7C: bounded request publication and progress update

**Parked: natural recovery is not byte-identical. The official matcher rejects
the complete 122-byte candidate against the 124-byte target. No MATCH report
or saved replay is claimed.**

## Full symbol evidence

- Target: `[0x08005E7C,0x08005EF8)`, 124 bytes / 61 instructions, all code.
  There is no literal pool, internal alignment or table. The next prologue at
  `0x08005EF8` belongs to a different function.
- Target SHA256:
  `6f396214c8ed286c45ab3d9d9d9b9e57785e1a6704c49b01a243f25ad0fec60c`.
- Fresh agbcc output has one 122-byte function / 60 instructions. Its `.text`
  section is 124 bytes only because an external `c046` alignment halfword
  follows the function. That padding is not part of the candidate function
  and cannot replace the missing target instruction.
- Complete typed-linked candidate SHA256:
  `ed33e08af6ff3ac14ad8ccc7f26e19d20b2ffa5a6e34c68556b8d4bc189903af`.
- Positional equality is 39 of 124 target bytes and 13 of 61 target
  instructions. These are diagnostic positional counts, not an aligned
  similarity score or a prefix match.
- The sole typed BL targets `0x08000B68`; no unresolved relocation, extra
  emitted helper or data symbol remains. Both complete bodies pass the frozen
  ordinary-call structural CFG check. The plausibility checker has no findings.

Frozen toolkit 4847c93 rejects the isolated, unmodified source with:

```
compiled symbol is shorter than the indexed span: 122 < 124
```

There is no verifier-profile blocker to conceal here. The remaining mismatch
is code generation: the target copies the narrowed remainder to another
register before the minimum, while the candidate reuses it; byte assembly has
different accumulator/register allocation; the limit load and final halfword
narrowing have different instruction schedules. The candidate narrows before
storing progress, whereas the target stores the low halfword and narrows its
retained value before comparison. The BL therefore occurs two bytes earlier
in the candidate. No prefix, padding substitution or hand-edited instruction
is accepted as a match.

## Natural forms tried

Three ordinary forms were compiled with the unchanged default
`-mthumb-interwork -O2` flags:

1. Direct unsigned-halfword amount, conditional limit and field update:
   116-byte function. The compiler repeated a limit load and reloaded the
   final progress field.
2. Explicit unsigned byte decoding, a captured limit and retained updated
   amount: 118-byte function.
3. Explicit wrapped remainder followed by a conditional minimum and retained
   unsigned-halfword amount: 122 bytes, retained here. The queue-node member
   was then given its independently audited natural field layout; the full
   122-byte function stayed unchanged.

No flag sweep, forced register/storage, packing, inline assembly, artificial
control flow or inert operation was tried. Only the retained form received
the paired behavioral checks below; earlier forms are compiler diagnostics.

## Contract and ordered effects

The compatible interface is `u8 func_08005E7C(void *object,
const void *descriptor)`. Both full input pointers are consumed; original r2
and r3 are irrelevant. The result is normalized zero or one, so the original
nominal Boolean width is not uniquely established. The observed caller
`0x08005EF8` consumes the low byte.

`TransferState` is a local typed view, not a claim about the full original
allocation. It places a u16 limit at `+0x04`, u16 progress at `+0x0C`, and the
request node at `+0x18`. The independently audited node has byte status/kind at
`+0x00/+0x01`, full opaque words at `+0x04/+0x08`, control at `+0x0C`, and a
next pointer at `+0x18`. Thirteen target-compiler assertions establish the
observed offsets, node size `0x1C`, state-view size `0x34` and alignment four.
Unknown fields are not initialized by the caller.

The descriptor is read through unsigned characters: no alignment is assumed.
The first full word is assembled from bytes `+0x04..+0x07`, then old progress
is added modulo 2^32. Total bytes `+0x08/+0x09` are assembled, old progress is
subtracted and narrowed to u16 **before** taking the unsigned minimum with
the limit. Underflow wraps; there is no lower clamp. Another full opaque word
is assembled from descriptor bytes `+0x00..+0x03`.

The declaration `void func_08000B68(RequestNode *, u32, u32, u16)` follows the complete
68-byte / 31-instruction helper audit. It receives the embedded request,
second assembled word, first assembled word plus old progress, and selected
amount divided by four. It initializes the request and appends it to the
queue headed by `0x03002BCC`, even when that count is zero. Neither opaque
word is dereferenced by this helper. It consumes no hidden input or stack
argument and returns no meaningful scalar.

The helper's separately recovered definition uses the identical `RequestNode`
tag and members. Updating only this caller declaration from `void *` to that
compatible typed pointer preserves the complete diagnostic function bytes and
all focused behavior checks; it is interface maintenance, not a fourth recovery
form or new matching credit.

After publication, the caller reloads progress, adds the selected amount,
stores low16, reloads descriptor total bytes, and compares the retained low16
progress against that total. These reloads and the publication-before-progress
order are preserved. No queue-consumer, transfer-engine or DMA behavior is
inferred from the control bits alone.

The ordinary domain requires valid suitably aligned typed state/request and
queue storage, at least ten readable descriptor bytes, and a finite queue
whose links are not destructively aliased by the new node's initialization.
Character views into state/request representations are permitted; arbitrary
overlapping typed objects are not thereby validated. The request remains
published after return, so its backing lifetime must satisfy the external
consumer. There is no runtime null guard, cycle check, general allocation or
concurrency guarantee, or proof that arbitrary queues terminate.

## Bounded validation

`/home/user/.codex-work/ffta-ulw/08005E7C-author/check.py` freshly compiles an
isolated source copy, performs complete typed linking and layout checks,
reproduces the official short-symbol rejection, and compares actual target
ROM execution against the recovered candidate. Both execute the actual
`0x08000B68` ROM bytes, with synthetic valid RAM fixtures and **no helper
stubs or callback models**.

Sixteen paired fixtures / 32 executions cover empty, one-node and three-node
queues; zero and nonzero request counts; nonmultiples of four; wrapped
remainder and progress; fullword position overflow; unaligned descriptor
views; and two character views into state/request storage. An independently
specified mutable-memory oracle checks exact ordered nonstack/nonliteral
reads and writes, all four call arguments, normalized result, complete mapped
data RAM, saved r4-r11, SP, return address and the expected post-BL LR. Peak
stack use is 32 bytes. Stack contents and ROM literal accesses are excluded
from the data-trace comparison, not reported as covered by that oracle.

All 61 target instructions, 60 candidate instructions and 31 real helper
instructions are covered across these finite fixtures. This is bounded
behavioral evidence, not whole-domain equivalence or an official byte match.

```
env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp \
PATH=/home/user/armtc/root/usr/bin:$PATH \
python3 /home/user/.codex-work/ffta-ulw/08005E7C-author/check.py
```

Only this parked source/README and the small external reproducer/log remain.
There is no active source/report or retained binary fixture. Promotion needs
an honestly natural full-symbol match, not a relaxed length or CFG check.
