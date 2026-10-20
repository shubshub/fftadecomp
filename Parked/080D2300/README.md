# 080D2300 — recovered, not byte-identical

## Complete boundary and result

The target occupies `[0x080D2300, 0x080D2380)`: 128 bytes and 56 reachable
Thumb instructions. Its 112 instruction bytes, three four-byte literals,
and four internal alignment bytes account for the entire symbol. Literal
words at `0x080D2318`, `0x080D231C`, and `0x080D237C` contain respectively
`0x02000000`, `0x000028C8`, and `0x08521214`. The zero halfwords at
`0x080D2316` and `0x080D237A` are internal; the next prologue begins at
`0x080D2380`.

Target SHA-256:
`96d228a502cd7c90c8e1e3cbf9bb4f2d92079d2214433bf418014005fc34b460`.

The retained source produces one `STT_FUNC`, with the complete `.text`
equal to that symbol: 128 bytes, 57 instructions, 114 instruction bytes,
three literal words, and two alignment bytes. The ordinary inline lookup
emits no separate function. Linked candidate SHA-256:
`3139ac0ca6143e3d8c8eae4a7dc8745c0d530f1d7fdba4714888b4999e4accc8`.

The reviewed `2e2a664` matcher reports `NOT MATCHING - bytes differ` under
the standard agbcc `-mthumb-interwork -O2` flags. Complete typed linking,
the closed leaf CFG, and source/header plausibility checks pass. Only
42 of 128 bytes are equal at the same offsets. The matcher's aligned
display reports 100 of 128 bytes and 28 of 57 instructions; that alignment
score is not a positional-byte or complete-symbol equality claim.
No active source or match report is retained.

## Recovery and interface

The compatible interface is `s32 func_080D2300(u16 identifier)`. The ROM
consumes only the low 16 bits of incoming `r0`, no other incoming register
or stack argument. It makes no calls and allocates no local frame. The
target saves `r4-r6` and LR; the candidate additionally saves `r7`.
Original nominal types and the absence of unused formal parameters are
not uniquely recoverable from those instructions.

The function reads the list head at the existing opaque state backing plus
`0x28C8`. It follows node record and next pointers at offsets `0x00` and
`0x08`, returning the first record whose identifier equals the requested
value. The record identifier is byte `0x00` combined with the low two bits
of byte `0x01`, so its value is ten-bit even though the requested value is
sixteen-bit. An empty list or exhausted search returns zero.

For the selected record, byte `0x04` is tested first. When nonzero, it is
reloaded and indexes a 16-byte table row at `g_table_08521214`; the unsigned
byte at row offset `0x0D` is added to the total. Byte `0x05` is then tested,
reloaded when nonzero, and processed the same way. The observed signed
lower clamp is retained before the full-word return. Every terminating
result is in `[0, 510]`, making the negative-clamp assignment infeasible
under these byte loads. There are no nonstack writes.

The private inline lookup is an ordinary identifier-search operation,
not forced inlining or proof of the historical source organization. The
node and 16-byte record views follow the adjacent record-list family; this
function itself directly observes only the listed members. Actual agbcc
layout probes confirm node size/alignment `12/4`, record/next offsets
`0x00/0x08`, record size 16 and index offsets `0x04/0x05`, table-row size 16
and value offset `0x0D`, and state head offset `0x28C8`.

## Bounded attempts and remaining difference

Three grounded forms were checked, all with the standard flags:

1. A byte-view lookup with its own head load and `u8[][16]` table:
   128 bytes/57 instructions, different lookup placement and extra table
   address arithmetic for offset `0x0D`.
2. An explicit head argument and empty-list return, with a table-row member
   at the observed offset: 128 bytes/57 instructions.
3. The retained named record fields at the observed offsets: identical
   machine bytes to form two.

The retained candidate needs an extra mask-copy instruction in identifier
assembly. It assigns different registers to the sum, requested identifier,
node, record, and mask, and initializes the sum after input narrowing rather
than before. Subsequent instructions are shifted by two bytes, consuming
the target's final alignment halfword. Both bodies still place the same
three literal values at the same offsets. This is a local code-generation
difference, not an unsupported verifier profile or an inherently impossible
match. No forced register, expression, read, storage, or control-flow form
was added to conceal the difference.

## Behavioral evidence and limits

The bounded reproducer is
`/home/user/.codex-work/ffta-ulw/080D2300-match/check_recovery.py`:

```sh
PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH python3 /home/user/.codex-work/ffta-ulw/080D2300-match/check_recovery.py
```

It freshly compiles and typed-links the parked candidate and executes it
against the actual target bytes from `baserom.bin`. All 412 paired cases,
824 executions, pass an independent result/read-trace oracle. They compare
ordered data-read addresses, widths and values, the full return value,
unchanged RAM/table bytes, saved registers, SP, LR, and return PC. No helper
models are involved because the function is a leaf. Synthetic RAM provides
finite lists and valid record views. Sixteen cases use pristine ROM bytes
at the computed table addresses; remaining cases use explicitly synthetic
table rows, including zero and maximum-byte contributions.

Cases cover empty and exhausted lists; first, middle, last, and duplicate
identifier matches; identifiers `0x0000`, `0x01A5`, `0x03FF`, `0x0400`, and
`0xFFFF`; ignored upper argument bits; zero and nonzero table indices;
both ordered reloads; and totals through 510. There are no observed
read-footprint differences. Coverage is 55/56 target and 56/57 candidate
instructions. The only uncovered instructions, `0x080D2370` and
`0x080D2372` respectively, assign zero after a negative sum, which cannot
arise from at most two zero-extended bytes. Negative values are not forged
to claim coverage.

The source domain requires valid aligned node objects, readable records,
and table storage for every selected index. The unsized table declaration
does not invent an original allocation bound; mapped ROM addresses in
tests do not prove one. Typed views do not establish arbitrary overlapping
object lifetimes. Cyclic or corrupt lists need not terminate. These limits
are not replaced by additional guards or alias assumptions.
