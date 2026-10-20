# 0x08124E74: recovered coordinate helper, inexact compilation

The complete ROM function occupies `[0x08124E74, 0x08124F22)`: 174 bytes
and 81 reachable Thumb instructions. This includes the four-byte interior
literal at `0x08124EC8`, whose value is `0x02000080`. The two bytes at
`0x08124F22` are alignment before the next function at `0x08124F24`.
Bounded Binary Ninja analysis confirms the entry, conditional output stores,
24-record scan, selector branches, and shared epilogue.

The preserved natural C candidate does not match. With
`agbcc -mthumb-interwork -O2`, it emits 182 bytes. Comparing bytes at the
same offsets over the real 174-byte ROM extent gives 10 equal positions
and 164 differing positions, plus eight extra compiled bytes. The first
difference is at `0x08124E76`, in the high-register save sequence.

## Recovered behavior

The inputs are an unsigned-byte selector, two signed-byte coordinates,
and two output halfword pointers. The fifth incoming argument is the
second output pointer. Negative coordinates produce zero output.

Selector `0xFF` scans 24 records at `0x02000080`, each 264 bytes long,
and selects the first whose flags at offset `0x28` contain `0x400`.
If none matches, the selected record is null. Other selectors choose
`func_08121CB4` when their high bit is set and `func_080C83CC` otherwise.
The selected record is passed to `func_08099560` with the context returned
by `func_08096D7C`. For each nonnegative coordinate, the output is its
tile-center position (`coordinate * 32 + 16`) minus the corresponding
signed object field at offset 8 or 12.

## Remaining difference and attempts

The preserved `-O2` candidate hoists the record stride `0x108` into a
saved register before the scan. The ROM materializes that stride inside
the loop, preserving only `r8`; the candidate also preserves `r9`.
This changes register allocation, the prologue/epilogue, branch positions,
and call displacements. The coordinate calculations now reproduce the
ROM operations, including signed halfword loads, after expressing the
intermediate position as an `s32` local.

The attempts covered a null-initialized search with `break`, a
post-loop index check, a direct exit to shared record processing,
`for` and `do` loops, indexed and incremented record pointers,
named versus literal record bases, scoped versus function-scope locals,
and `-O1`/`-Os` in addition to `-O2`. None produced an exact match.
Narrowing an intermediate position to `s16` instead allowed unsigned
halfword loads and was not retained.

The required `match.py --root . 0x08124E74` command, run while the
candidate was in `src/`, accepts its ABI and control flow and reports
`source plausible`, then exits 1 with `NOT MATCHING - bytes differ`.
Its alignment-oriented score was 46/81 instructions and 145/182 bytes;
that score is not a same-offset byte-equality count and extends into
the next ROM function because the candidate is longer.

No verifier extension or new data mapping is required for this callee.
The nonmatching report was removed from `docs/match/`, and the candidate
is preserved here without an official match claim.
