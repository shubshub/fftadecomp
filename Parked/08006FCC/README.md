# 08006FCC — coalesce a released block (Parked)

**Not a match.** The retained natural C compiles to a complete 246-byte,
114-instruction function; the ROM function is 252 bytes and 118 instructions.
Frozen toolkit `4847c93` rejects it with exit 1:

```text
compiled symbol is shorter than the indexed span: 246 < 252
```

There is no active `src/08006FCC.c` or `docs/match/08006FCC.md`. The official
checker and metadata were not weakened. Passing bounded behavioral checks
does not override the failed full-symbol comparison.

## Recovered contract

Compatible interface: `void func_08006FCC(u8 *owner, u8 *block)`.
The owner and blocks occupy live byte-addressed arena storage. Encoded links
are little-endian byte pairs: zero means null, otherwise the address is
`owner + 4 * offset`. A nonnull pointer encodes as its owner-relative word
offset narrowed to 16 bits. No packed structure or shared-header change is
used.

Owner offsets 0/2/4 hold free-index head, search cursor, and count. Block
offsets 0/2 hold physical previous/next; 4 holds the marker; 6 holds size;
8/10 hold free-index previous/next. These are separate linked relations.

The function subtracts three from the original block's size modulo 65536,
marks it `0x7370`, and follows free physical predecessors to the leftmost
block. It unlinks that leftmost block if distinct from the original. It then
merges free physical successors, unlinking each unless it is the original
block, reloading sizes after calls, adding `3 + successor.size` modulo 65536,
and copying the successor's physical-next link. It repairs the first
nonmerged successor's physical-previous link and inserts the result into
the free index.

Calls retain the real interfaces `08006DA0(owner, block)` and
`08006E28(owner, block)`. Their actual ROM closure contains `08006D38` and
`08006C88`; no helper result is used and there is no callback in this chain.
The redundant null-to-offset conversion does not make null block input
valid: the block is dereferenced at entry.

## Bounded forms and exact discrepancy

Only fixed agbcc `-mthumb-interwork -O2` was used. Two grounded forms were
tested, without flag sweeps or register, storage, control-flow, pragma,
volatile, or assembly tricks:

1. Explicit byte accesses with a shared nullable link decoder: 238-byte,
   112-instruction symbol, rejected as shorter than 252 bytes.
2. Shared little-endian 16-bit read/write codecs and an offset decoder,
   retaining the same linked loops and real calls: 246-byte,
   114-instruction symbol. This is the retained source.

The retained candidate has 54/252 equal same-position bytes and 13/118
equal same-address instruction encodings; its missing final six bytes are
not treated as a matching prefix. Its full ELF function occupies
`[08006FCC,080070C2)`. `.text` is 248 bytes, with external `c046` alignment
at `080070C2` excluded from the function. All three call relocations were
typed-linked to actual indexed helpers with no leftover relocations or
veneers. Diagnostic ordinary-call CFG verification passes; official matching
still fails the full span.

The ROM includes 242 code bytes, two `0x7370` pool words at `08006FF8` and
`08007038`, and internal zero alignment at `08006FF6`. The candidate includes
234 code bytes, two corresponding pool words at `08006FF8` and `0800708C`,
and two internal zero halfwords. The whole symbol, including these bytes,
was inspected. Candidate loop rotation, register allocation, byte-codec
address calculations, and narrowing/masking differ. It saves only r8 in
addition to r4-r7/LR, using 24 caller stack bytes; the ROM also saves r9 and
uses 28. No further source-search claim is made.

## Fresh bounded verification

Source plausibility and five target-agbcc scalar/byte-pointer layout checks
pass. Seven paired ROM/candidate cases execute the actual ROM bodies of all
four helpers, never the byte-different Parked helper C:

- Single release into an empty index.
- Allocated physical neighbors without a merge.
- Two free physical predecessors and two free successors.
- Left-only merge with interior free-index insertion.
- Right-only merge with distant free-index neighbors.
- Size-byte carry with a terminal merge.
- Head insertion before larger distant free blocks.

All fourteen executions match the independently specified caller access
order and an arena/list final-memory oracle. ROM and candidate also have
identical ordered non-stack RAM accesses across the real helper chain and
identical helper argument traces. Complete 256 KiB EWRAM and 32 KiB IWRAM
are compared outside reserved stack scratch. r4-r11, SP restoration, return
control, helper output-pointer placement, and bounded stack accesses pass.
Peak nested depth differs as expected: ROM 68 bytes, candidate 64 bytes.
Stack scratch contents are not claimed equal.

Coverage reaches 117/118 ROM and 113/114 candidate instructions. Only the
redundant null-leftmost conversion instruction is unexecuted in these valid
nonnull fixtures. Negative controls reject both an incorrect initial size
decrement and a real insertion-helper mutation omitting its count increment.

These finite tests do not prove universal equivalence, original nominal
types, allocation capacity, arbitrary overlapping/aliased metadata, invalid
or cyclic links, concurrency/MMIO behavior, or universal termination. The
fixtures use coherent finite physical chains and a consistent sorted free
index within sufficiently backed storage. No blanket helper proof follows.

## Frozen identities and reproduction

```text
source SHA256
3566aa26293442f8eb875e28fa5df314afcf4ccc7dfd583e4512928951981d92
complete target SHA256
1c178b498423212776ef0bf27836958dee9899b97b44059e586aa70bbf414d26
complete linked candidate SHA256
973faa22d4875a6803502515123364f53bcb1e92a947c9547e994470659bca8c
```

Reproducible local evidence is under
`/home/user/.codex-work/ffta-ulw/08006FCC-author/`: `check.py`,
`compile_candidate.py`, `check.log`, `official-final.log`, `freeze.json`,
and the two form ELF/disassembly records. Run `check.py` with `FFTA_ROM`
unset, `PYTHONDONTWRITEBYTECODE=1`, disk-backed `TMPDIR`, and
`/home/user/armtc/root/usr/bin` prepended to `PATH`. It copies only this
source into isolated roots, repeats official rejection and diagnostic
linking, and executes the real-helper checks. No production reports or maps
are written. All generated compiler/linker/layout binaries and isolated
roots were removed; only small text evidence remains.
