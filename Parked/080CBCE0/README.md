# 080CBCE0 — parked natural C attempt

Target: `080CBCE0..080CBD34`, 84 bytes and 39 reachable instructions, including the shared literal word. The function compacts the five halfword entries at `data_02001F30` in order, then returns the byte result of `func_080CC7CC()`.

The preserved candidate was tested with the native matcher at fixed agbcc `-mthumb-interwork -O2`. Fresh result: exit 1, source plausible, complete 88-byte ELF function (`080CBCE0..080CBD38`), direct Thumb call profile, no remaining relocations. It does not match and earns no match credit.

The four-byte excess is two address-register copies. The target keeps the outer array base in R7 and computes the selected destination using the inner base loaded into R4. The candidate copies the outer base from R7 into IP before the loop, then copies IP into R2 for the outer read. It retains R7 for the destination and uses R5 for the inner base. The next outer index is consequently allocated to R4 rather than target R5. Literal-load offsets, branch offsets and the final call relocation differ as a result.

Tested natural forms:

- Direct global array accesses with byte-sized loop indices: 88 bytes; this is the preserved candidate.
- One local array pointer for both loops: 98 bytes, with additional address retention and duplicated inner-loop paths.
- A fully inlined semantic helper that fills one empty slot: 88 bytes, with the same extra IP copies as the direct form.

The native diff compares 88 ROM bytes when the candidate is longer, including four bytes beyond the indexed target. Its alignment score is not same-offset equality or a complete-target instruction count. No compiler flags, shared bindings or validation rules were changed. The unmatched active source and report were removed.
