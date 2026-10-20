# 080CF060 — natural recovery, not a byte match

The complete ROM function is `[0x080CF060, 0x080CF118)`: **184 bytes and
84 reachable Thumb instructions**. Code occupies `[0x080CF060, 0x080CF108)`;
the remaining 16 bytes are four literal words. There are no internal gaps,
calls, switch tables, or incoming stack arguments. The function saves 32
bytes of registers and allocates a four-byte local frame.

| Literal address | Value |
| --- | --- |
| `0x080CF108` | `0x0855AE4C` |
| `0x080CF10C` | `0x02002E34` |
| `0x080CF110` | `0xFFFFD1CC` |
| `0x080CF114` | `0x00001F69` |

## Contract and ordered behavior

The recovery uses `u32 func_080CF060(const void *record)`. Only incoming `r0`
is consumed. The ROM returns the full-word values zero or one; that range
does not uniquely establish the original declared return width.

1. Read input byte zero, then byte one. Form the ten-bit identifier
   `byte0 | ((byte1 & 3) << 8)`.
2. Read byte two of the corresponding 70-byte row at `0x0855AE4C`. If its
   low three bits are not one, return zero without reading the state records.
3. Search five six-byte records beginning at `0x02002E34`. Each comparison
   reads record byte four, then byte five, and extracts the nine-bit value
   `byte4 | ((byte5 & 1) << 8)`. The first comparison uses the input identifier
   already captured. Every later comparison reloads input byte zero and then
   byte one, after reading the current state record's two identifier bytes.
4. Select the first matching record. If none matches, retain the fifth
   record anyway; the ROM has no unsuccessful-search rejection.
5. Read the selected record's byte two, then the full byte at `0x02001F69`.
   Return one exactly when the former's low five bits equal the latter.

There are no nonstack writes. Input identifiers 512 through 1023 cannot
match the nine-bit state identifiers, but still use the fifth-record fallback
after the table-category check succeeds. The global byte is not masked to
five bits. The source does not introduce bounds checks, null checks, volatile
accesses, or an invented failure path.

The table has the same unsized `const u8[][70]` view used by the parked
`080CE4DC` recovery. State accesses use the existing opaque byte-array
declaration of `g_state_02000000`, with the two observed offsets. Six-byte
record stepping uses byte pointers rather than relying on this compiler's
struct padding. The valid domain requires readable input bytes, the accessed
table row, the five state records, and the global byte. Observed accesses do
not prove an allocation bound or a universally valid identifier domain.

## Exact matching result

The reviewed `kit-reviewed-2e2a664` matcher, using agbcc
`-mthumb-interwork -O2`, reports:

```text
compiled symbol is shorter than the indexed span: 132 < 184
```

The retained candidate emits exactly one `STT_FUNC`, occupying the complete
132-byte `.text`: 57 reachable instructions, two alignment bytes, and four
literal words. Its linked bytes have SHA-256
`500761f96c3d627be220cd111df13c01e15bfd2b612d44f6fa730257457bc395`.
The separate diagnostic uses the frozen tool's typed data binding and link
checks; its linked ELF has no unresolved relocations or extra functions.
This does not bypass or replace the official short-span rejection. No
official equality count or MATCH report was produced.

Two ordinary source organizations were tried, with unchanged standard flags:

- An ascending five-iteration `for` loop assigning the selected record,
  using independently named record and global-state objects: 132 bytes.
- The retained search-condition `while` loop using the observed common
  opaque state view: 132 bytes.

The compiler hoists the input identifier out of the scan in both forms. The
retained form keeps the Boolean result in a register, saves fewer registers,
uses a different loop arrangement, and expresses the low-five-bit extraction
with an AND. It loads the common state base and positive record offset,
rather than loading the record address and deriving the common base through
the ROM's negative literal. No explicit negative-base reconstruction, forced
stack storage, register binding, artificial bitfields, or helper expansion
was added to force those instructions. This is a local code-generation gap,
not a claim that the function is inherently unmatchable.

## Behavioral verification and read-footprint difference

The retained reproducer is
`/home/user/.codex-work/ffta-ulw/080CF060/check_recovery.py`. From the game root:

```sh
PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH python3 /home/user/.codex-work/ffta-ulw/080CF060/check_recovery.py Parked/080CF060/080CF060.c
```

It freshly builds and typed-links the candidate, then executes the actual ROM
body and candidate in 305 paired cases, or 610 executions. Sixty-four pairs
use pristine ROM table bytes with synthetic RAM; the other 241 use explicitly
synthetic table bytes and RAM. No callees or helper stubs are involved.
The cases cover every target instruction and every candidate instruction,
all eight category values, first through fifth matches, no matches, ten-bit
identifier boundaries, ignored upper input bits, equal/different/high global
bytes, return values, unchanged nonstack memory, saved `r4`–`r11`, and SP.

**The data-read footprints are not identical.** In 164 cases the target
reloads input bytes during later scan iterations while the candidate does
not. The test separately checks each body's exact ordered reads and confirms
that these omitted reloads account for the differences. Equal results in
stable ordinary memory do not establish equivalent behavior for externally
changing or volatile storage. No claim of equal read sequences is made.

The plausibility check reports zero findings. Active source and match report
are absent. The reproducer cleans its generated build artifacts; only its
small test source is retained for independent review.
