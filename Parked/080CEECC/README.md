# 080CEECC: ordered record requirements

This is a plausible recovery, not a byte match. No active source or match report
is retained for this address.

## Complete extent and remaining difference

The target occupies `[080CEECC,080CEF78)`: 172 bytes and 69 reachable Thumb
instructions. Code occupies `[EECC,EEEC)`, `[EEF4,EF20)`, `[EF28,EF66)` and
`[EF70,EF78)`, with the common `080C` prefix omitted. Six literal words occupy
`[EEEC,EEF4)`, `[EF20,EF28)` and `[EF68,EF70)`. The two zero bytes at
`[EF66,EF68)` are internal alignment, not instructions. There is no external
padding within the measured extent.

The retained natural indexed-byte form produces the same complete 172-byte,
69-instruction extent using agbcc `-mthumb-interwork -O2`. Frozen toolkit
`2e2a664` accepts its structural/data-link evidence and plausibility but reports
`NOT MATCHING - bytes differ`. Direct same-offset comparison finds 152/172
bytes and 49/69 instructions equal. The matcher's alignment-based byte summary
is 153/172; that is not a positional equality count.

Twenty instructions differ by register operands only. The first two searches
use candidate `r2` for the required value and `r1` for the slot counter, opposite
the target. Their differing instruction addresses are `EEDC`, `EEDE`, `EEE2`,
`EEF6`, `EEF8`, `EEFE`, `EF02`, `EF10`, `EF12`, `EF16`, `EF2A`, `EF2C`, `EF32`
and `EF36`. The final narrowed value and selected-byte address differ at
`EF44`, `EF46`, `EF4A`, `EF4C`, `EF52` and `EF54`. All branches, calls, literal
contents and positions, and the saved-register layout agree.

Two natural representations were tried. The retained form indexes the opaque
byte global directly. A second form used local views of four-byte record rows
and two-byte quantity rows at the observed bases; it produced a 148-byte symbol
and was rejected before comparison as shorter than the 172-byte target. The
direct form was restored and recompiled to its original result. No declaration
reordering, forced registers, artificial operations or compiler attributes were
used to pursue the remaining operand differences.

## Interface and ordered behavior

The compatible interface is `u32 func_080CEECC(u16 index)`. It consumes the low
16 input bits and returns full-word zero or one. The exact original nominal
types are not uniquely established. Its only helper declaration is the existing
compatible `u32 func_080CE4DC(u16 index, u8 selector)`; the named RAM object
retains the existing opaque `extern u8 g_state_02000000[]` declaration.

Selectors 42 and 44 are called in order. Each result is narrowed to 16 bits; a
nonzero result is sought among at most 64 ascending bytes at
`02002B08 + 4 * slot`. The first equality stops that search. An exhausted search
returns zero before later calls. The second search starts again at slot zero.

Selector 46 is then called and narrowed to 16 bits. Zero returns one. Otherwise
the byte at `020021B4 + 2 * result` is captured before calling selector 47. The
cached byte is compared unsigned against selector 47's full 32-bit return value,
without narrowing that final helper result. The caller performs no non-stack
writes and balances its 12-byte save of `r4`, `r5` and the return address.

In the actual helper, selectors 42/44 yield zero or values `0x178..0x276` through
`080CB4A4`. A nonzero value therefore cannot equal a scanned byte. The observed
64-read searches and calls are nevertheless preserved, not simplified away.
Selector 46 reads the low nibble of row byte `0x38`; selector 47 combines its
high nibble with the low three bits of row byte `0x39`.

## Bounded execution evidence

There were 72 paired target/candidate cases, or 144 caller executions. Of these,
46 pairs executed the real ROM bodies of `080CE4DC` and `080CB4A4` with explicitly
synthetic valid table rows and RAM. They cover both real missing-search paths,
the zero selector-46 path and boundary quantity/threshold comparisons.

The other 26 pairs explicitly modeled the helper. These exercise successful
byte searches unavailable from the real selector-42/44 ranges, first and last
slot matches, missing values, fresh second-search data, truncation of the first
three results, and full-word final thresholds including `0x10000` and
`0xFFFFFFFF`. A model changes the selected quantity during selector 47 to check
that the earlier byte remains cached. Models also clobber caller-saved registers.

All 69 target and 69 candidate instructions were covered, together with 47
instructions of the real selected `080CE4DC` paths and all 11 instructions of
`080CB4A4`. Paired complete non-stack read traces, call arguments/order, return
values and final synthetic RAM agree. Independent expectations check the
caller's exact read sequence, absence of CPU non-stack writes, preserved
`r4..r11`, balanced SP and correct return. Modeled mutations are not attributed
to the real helper. This is not full coverage of the 349-instruction accessor.

The tests establish no actual array allocation, original entry provenance or
universal helper termination guarantee. Execution requires valid storage for the
selected helper row, each executed scan, and any selected quantity byte. No
capacity guard, purity annotation or alias restriction is invented. There is no
MATCH or saved-report replay claim for this parked recovery.
