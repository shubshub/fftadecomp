# 08021D48 — conditional signed-halfword negations

## Status

Not matching. The complete ROM function is `[08021D48,08021D96)`,
78 bytes and 39 Thumb instructions, with no literal pool. The zero halfword
at `08021D96` is external alignment, not part of the function.

The closest ordinary C candidate produces a 76-byte function under agbcc
`-mthumb-interwork -O2`. The frozen `868e87e` matcher correctly rejects it:
`compiled symbol is shorter than the indexed span: 76 < 78`.
This is a compiler-output mismatch, not an unsupported verifier profile.

## Recovered behavior and ABI

The function takes an object pointer and two writable signed-halfword pointers,
returning no value. It first copies object halfwords at offsets `0x18` and
`0x1A` to the first and second outputs, in that order. It then independently
tests the object word at offset zero for masks `0x20`, `0x200`, and `0x400`.
Each set flag negates the first output; none of these tests negates the second.

The ROM reloads flags between the tests and reloads the signed first output
before each negation. These accesses must not be replaced with one combined
parity test: output aliases can affect subsequent accesses.

Signed-halfword values are promoted to signed 32-bit arithmetic before
negation, so negating `-32768` does not overflow the promoted type. The target
compiler's subsequent signed-halfword narrowing retains the low 16 bits.
The epilogue restores `r4` and returns through the saved LR in `r0`.

## Remaining differences

The retained compound-multiplication source emits all three signed loads and
negations, but retains the second flags load in `r1` across the second output
store. It omits the ROM's third `ldr r0, [r4]` at `08021D7C`, producing a
76-byte symbol rather than 78 bytes. The second and third tests consequently
also use different registers.

## Natural forms checked

- Direct `*first = -*first`: 70-byte symbol; uses unsigned halfword loads for
  the negations and omits the final flags reload.
- Compound `*first *= -1`: 76-byte symbol, retained here.
- A signed 32-bit local for each promoted negation: 76-byte symbol.
- Removing `const` from the object pointer: unchanged 76-byte symbol.
- Diagnostic `-fno-strict-aliasing`: unchanged 76-byte symbol; no report
  was written for that diagnostic.

No volatile accesses, synthetic alias layouts, barriers, assembly, inert
operations, or special optimization controls were added. The indexed extent
was not shortened to accommodate the candidate. No successful match report
exists for this function.
