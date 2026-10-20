# 0x08021E3C

Status: natural recovery preserved, not byte-identical. This remains a
matching task; it is not classified as inherently unmatchable.

## Complete target and behavior

The complete ROM symbol is `[0x08021E3C, 0x08021E5E)`, 34 bytes and
17 instructions, with no literal pool. The zero halfword at
`0x08021E5E` aligns the following function at `0x08021E60` and is
outside this symbol.

The function consumes an object pointer and compares signed halfwords
at offsets `0x0C` and `0x0E`. It returns the first value when that value
is less than the second; otherwise it returns the first value minus
one. The result remains signed 32-bit: equal fields containing
`-32768` produce `-32769`, not a narrowed signed-halfword result.
There are no calls, global references, stack allocation, or null guard.

## Verification and remaining difference

The retained canonical source uses ordinary typed fields and early
returns. Checks used the frozen reviewed toolkit
`kit-reviewed-868e87e/tools/match.py` and compiler
`$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`.

All three natural forms tested produce a complete 30-byte symbol:

- The retained early-return form.
- A conditional expression selecting the value or value minus one.
- An ordinary result local assigned by `if` and `else`.

The official matcher exits 1 with
`compiled symbol is shorter than the indexed span: 30 < 34`.
It stops before byte comparison, so no matching-byte percentage or
successful verification claim is made. The retained source separately
passes the frozen plausibility checker.

Inspection of the canonical source's standard compiler assembly
isolates the difference. The compiler saves only the link register and
keeps a single object pointer in `r2`. It branches on signed less-than
to a value-reload path; the other path subtracts one from the value
already loaded for comparison.

The ROM additionally saves `r4` and copies the object pointer from
`r2` to `r3`. It branches on signed greater-than-or-equal, returns the
already-loaded value on the first path, and reloads the value through
the second pointer before subtracting one on the other path.

No alternate flags, forced aliases or registers, inline assembly,
volatile accesses, compiler pragmas, artificial code, or gate bypasses
were used.

The unmatched active source was removed, and no match report was
generated. The exact task-owned compiler scratch files were removed.
