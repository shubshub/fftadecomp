# 080CF690 — natural recovery, not a byte match

The complete target is `[0x080CF690, 0x080CF7F4)`: **356 bytes and 173
reachable Thumb instructions**. The target has these exact ranges:

| Range | Classification |
| --- | --- |
| `[0x080CF690, 0x080CF6E0)` | 80 code bytes |
| `[0x080CF6E0, 0x080CF6E4)` | literal `0x02002E34` |
| `[0x080CF6E4, 0x080CF7F0)` | 268 code bytes |
| `[0x080CF7F0, 0x080CF7F4)` | literal `0x02002E34` |

There are no alignment gaps or switch tables. The next function starts at
`0x080CF7F4`. The target saves 28 bytes of registers and allocates a four-byte
local frame. Its sole call is `0x080CF6C8 -> 0x08036440`.

## Grounded contract

The recovery uses `void func_080CF690(void)`. It does not consume incoming
argument registers or stack arguments, and its return sequence restores the
saved return address into `r0`. The state is five observed six-byte records
at `0x02002E34`, using the established unsized `u8[][6]` declaration. No new
record allocation bound or shared type is introduced.

The helper declaration is the independently audited, compatible
`u32 func_08036440(u8 value, u32 mode)`. This caller supplies the low five bits
of record byte two and mode zero. The helper consumes only low-byte `r0` and
full-word `r1`; the caller's incidental `r2 == 7` is not an argument. The
complete 124-byte helper has no calls or writes. Value zero returns zero
without state access; otherwise mode zero searches six rows through the
pointer at `0x03002810`, requiring row flag bit zero and a matching stored
identifier. The caller compares the helper's full-word result to zero.

The valid domain requires the five accessed records to be readable and
writable, and the helper's state slot and relevant rows to be valid whenever
a nonzero helper argument is used. This is an ordinary-memory recovery, not
a guarantee for arbitrary pointers, asynchronous mutation, or volatile data.

## Three ordered passes

1. Visit the five records in ascending order. Ignore records whose byte-zero
   low three bits are zero. If byte-one bit `0x80` is set, call the helper with
   `record[2] & 0x1F` and zero. A zero result clears byte-one bit `0x80` using a
   fresh byte read and immediately ends this first pass. Otherwise reread
   byte zero and increment the active count if its low three bits remain
   nonzero.
2. Visit all five records again. A record is eligible when byte-zero low
   three bits are nonzero, byte-two bit `0x20` is clear, and byte-one bit
   `0x80` is clear. Its upper seven bits in byte five are a counter; preserve
   the low bit. Counter `0x78` is held unchanged. Other positive counters
   decrement, followed by a fresh byte-five read. A zero counter sets
   byte-two bit `0x40`, clears bit `0x20` using the previously read byte-two
   value, and resets the active count to zero. The guarded decrement never
   shifts a negative signed value in the recovered C.
3. Only if the active count is still five, search for a first strict minimum
   counter below seven. Eligible records have nonzero byte-zero low three
   bits, clear byte-one bit `0x80`, and clear byte-zero bits `0x30`. Any
   scanned record with byte-two bit `0x40` aborts the entire selection,
   including a candidate found earlier. Otherwise set bit `0x40` in the
   selected record with a fresh read; this final store does not clear bit
   `0x20`.

## Exact mismatch

One natural three-loop candidate was tried with the standard agbcc
`-mthumb-interwork -O2` flags. The frozen `kit-reviewed-2e2a664` matcher stops
at the complete-symbol gate:

```text
compiled symbol is shorter than the indexed span: 344 < 356
```

A separate diagnostic using the frozen typed direct-call/data linker emits
exactly one 344-byte `STT_FUNC` and a 344-byte `.text`. Its 165 reachable
instructions occupy 332 bytes, with two four-byte literal words and four
alignment bytes. The linked ELF has no unresolved relocations or extra
functions. Its SHA-256 is
`d715c68f96c652924d4da7c75f9f52e0753c49ba53bc0d0638a60d3a582dce90`.
The target SHA-256 is
`b8929e240942bf4fdb598389535d0efb8cfb29645cd4dbbfec4ee96bbaa52d8b`.

The candidate saves 24 bytes of registers and has no local allocation. It
keeps the first-pass mask in a preserved register rather than spilling it
around the helper call, uses different high-register assignments and field
extraction instructions, and places its pools differently. Only 27 of the
344 overlapping byte positions agree; the target has another 12 bytes.
That positional diagnostic is not an official matching percentage. No
MATCH report is retained.

The frozen structural verifier accepts both complete bodies with their
exact direct-call summaries. The candidate's data literals also pass the
typed binding check, and source plausibility reports zero findings. This
is a concrete code-generation mismatch, not an unsupported-profile blocker.
No forced spills, register bindings, artificial bitfields, volatile accesses,
assembly, or inert control flow were added to manufacture the target layout.

## Bounded behavioral evidence

The retained reproducer is
`/home/user/.codex-work/ffta-ulw/080CF690/check_recovery.py`. From the game root:

```sh
PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH python3 /home/user/.codex-work/ffta-ulw/080CF690/check_recovery.py Parked/080CF690/080CF690.c
```

It freshly builds and typed-links the candidate, then runs 172 paired cases
(344 executions) with actual ROM target instructions, candidate instructions,
and the actual complete ROM helper. All state data are explicitly synthetic
RAM fixtures. There are no helper stubs or modeled callback effects; a
separate reference model checks the expected caller data operations and the
helper's return values.

The cases cover inactive records, early helper failure at each slot, zero
and nonzero helper arguments, early and late helper-row matches, both low
counter bits, counter boundaries including the `0x78` sentinel, phase-two
exclusions and expirations, first strict minima, ties, no minimum, and ready
flags at every position. Sixty-four additional deterministic fixtures vary
the record bytes and helper rows.

All 173 target and 165 candidate instructions execute. The helper executes
44 distinct instructions on the caller's mode-zero paths, with 114 helper
calls per body across the cases. Exact ordered nonstack state-memory reads
(EWRAM and the IWRAM state-pointer slot), nonstack writes, helper
arguments/results/order, complete final RAM, saved `r4`–`r11`, SP, and return
destination agree in every pair. Each caller's ordered record access trace
also agrees with the separate model. There were zero state-memory read-trace
differences in these fixtures; instruction and ROM literal-pool fetches are
excluded, and the callers' pool locations differ. Stack layouts are intentionally different;
the tests allow only each execution's bounded save/frame area to differ.

These finite fixtures do not establish validity for arbitrary storage or
unique original source provenance. The candidate remains parked solely as
an honest nonmatching recovery. Active source and normal report are absent;
the reproducer cleans its generated binary and build artifacts.
