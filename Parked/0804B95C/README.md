# 0804B95C — complete reconstruction, unmatched

Target: `0x0804B95C..0x0804BB10`, 436 bytes / 179 reachable instructions.
The preserved C compiles with fixed agbcc `-mthumb-interwork -O2` to a
412-byte symbol (`0x0804B95C..0x0804BAF8`) containing 169 assembly instructions.
A fresh default native match exits 1 with:

```text
compiled symbol is shorter than the indexed span: 412 < 436
```

This is a complete two-mode menu builder. It initializes the menu header,
scans 64 inventory records at state offset `0x2B08` with availability halfwords
at `0x2B0A`, or scans 20 special-item halfwords at `0x1F3C`. It builds 20-byte
entries at menu offset `0x230`, derives text/name identifiers from the indexed
tables, calls `func_080CB99C`, and stores/returns the resulting entry count.
Both loops and the default-mode path are present.

## Remaining compiler differences

The target keeps the menu in r6, the source index in r8, entry count in sb,
entry pointer in r4, and name in r5. The preserved candidate puts the menu in
r8 and source index in r6; count, entry pointer, and name use sb/r4/r5.

In mode 1, the target keeps the availability cursor in sl and a separate
four-byte induction offset in r7, reloading the state base inside the loop.
The candidate uses r7 for availability, recomputes the record offset with
`i << 2`, and reserves sl for a cached zero. This changes both loop setup and
latch instructions. The target recomputes the entry-array address in each
case; the candidate reuses the address calculated during header setup.
Mode 2 also retains the menu/index register-allocation difference. These
changes affect instruction encodings, pool placement, and alignment; no
same-offset equality or native diff score is claimed.

## Bounded natural attempts

Typed inventory records, byte-offset traversal, local state-base pointers,
shared versus case-local counters, direct array-indexed output entries,
fixed-count for/do loops, and equivalent availability conditionals were
compiled at the same fixed flags. They produced complete symbols between
412 and 440 bytes without reproducing the target's register/induction
lifetimes. A u16 name temporary does reproduce the target's conditional
metadata-byte reload; no volatile access was introduced.

The final native refusal happens at the symbol-length check, before linked
byte comparison or the plausibility verdict. It generates no native report.
No match credit is claimed, and the unmatched active source has been removed.

Preserved source SHA-256:
`77f68001dc2aa3c8c84ad7787d912c458533788e03e672862a85d3660711cca4`

Final native stdout SHA-256:
`e15c8934befd6ba1038350420aaaff558c925d86dcb70005c9e9230385496502`
