# 080CCF44 — natural recovery, not byte-matching

The target occupies `[0x080CCF44, 0x080CCFB8)`: 116 bytes and 53 reachable
Thumb instructions. Code occupies `[0x080CCF44, 0x080CCF96)` and
`[0x080CCF9C, 0x080CCFB8)`. Two zero alignment bytes precede the literal at
`0x080CCF98`, whose value is `0x08520080`.

## Recovered behavior

The interface is `void func_080CCF44(void *object, u16 entry)`. A zero entry
returns without reading the object. Otherwise, `func_080CA7A4(entry, 0x12)`
selects a 20-byte effect record with a count byte at offset zero and two-byte
marker/value rows starting at offset two.

Each iteration reads the object's category byte at offset seven before
comparing the marker. An equal marker sets bit `0x80` in the byte at
`object + 0x40 + value`, subject to the observed local null check, then reloads
the pair value and calls `func_080CD620(object, value)`. The local null check
does not make a nonempty traversal null-safe: the category was already read.
An unequal marker of `0xFF` instead stores the value at object offset `0x3D`.
The loop reloads the table count after each iteration.

The shared tagged `EffectRecord` declaration uses `u8 pairs[9][2]`, matching
the physical 20-byte stride and offset-two payload. It adds no count guard or
outer-table bound. Valid selected records, pair storage and accessed object
bytes remain prerequisites; this recovery does not establish their allocation
or the called helpers' termination. No `restrict` or extra null guard is used.

## Exact remaining differences

The retained candidate is plausible and occupies 116 bytes, but has 54
reachable instructions. It narrows the incoming entry in `r1`, tests `r1`,
and adds an extra `r0 = r1` copy before calling `func_080CA7A4`. The target
instead saves the object first and narrows the entry directly into `r0`.

The bit-set block also exchanges the two operand registers: the candidate
loads the existing byte into `r1` and puts `0x80` in `r2`; the target loads
into `r2` and puts the mask in `r1`. The OR and store are otherwise identical.
The extra entry copy shifts code before the pool by two bytes and consumes
the target's alignment gap. Both symbols retain the same pool address and end.

The frozen matcher reports `NOT MATCHING`, with 102/116 bytes in its
sequence-aligned comparison. Only 38/116 bytes agree at identical positions.
The report's instruction comparison uses candidate instruction boundaries;
the independently decoded full CFG counts are 53 target and 54 candidate.
No bytes from the next function are included in this retained comparison.

## Bounded attempts and verification

- A nested two-byte `EffectPair` struct was rejected as a layout recovery:
  this compiler rounds that nested struct to four bytes. Byte-pair arrays
  provide the genuine observed layout without packing directives.
- A raw-byte object view produced 130 bytes, including a hoisted offset-`0x3D`
  address and an extra saved register. The retained typed view uses only the
  observed category and default-value offsets and restores the 116-byte size.
- An outer conditional and an early return generate the same retained bytes.
  Compound OR assignment and an explicit OR expression also generate the same
  retained bytes. No register-steering workaround was introduced.
- The reviewed `d7f9a0a` matcher accepts both direct calls, the named table
  relocation and the complete candidate CFG, and reports plausible source.
- Twenty-four paired target/candidate cases passed, comprising 48 Unicorn
  executions with synthetic object, table and stack memory. Both helpers
  were explicitly modeled: the selector returned row two and the second
  helper optionally changed the object category. These are not executions
  of the real helpers or a proof of arbitrary table contents.
- Those cases cover zero-entry and zero-count paths, all nine physical slots,
  equal and unequal markers, `0xFF` priority, zero and maximum byte values,
  upper argument bits, category changes across calls, matching data-access
  traces and writes, and preservation of SP and `r4`–`r11`. All 53 target and
  54 candidate instructions were executed.

`match.md` is the historical nonmatching diagnostic generated while this
source occupied `src/080CCF44.c`, with the complete game header set. Its
source fingerprint binds that historical path; it is not an active match
certificate. No source or report for this address remains in the active tree.
