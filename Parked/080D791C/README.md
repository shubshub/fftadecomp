# 0x080D791C | transfer task callback

The C in this directory passes strict plausibility. With agbcc `-mthumb-interwork -O2`, its complete Thumb symbol has the target length of 340 bytes. Linking the compiler's eight `R_ARM_THM_CALL` relocations and two `R_ARM_ABS32` references to the mapped scheduler pointer gives **310/340 identical bytes**. All 30 differing bytes lie between 0x080D79AA and 0x080D79D2 inclusive. The ROM span is 0x080D791C–0x080D7A70 (exclusive).

| SHA-256 | Data |
| --- | --- |
| `7564b77a8434b5be2fb3e5e3d2ef72397612f469d3373202867bd902a65a11f4` | ROM target |
| `8e57d9f7c72347ba8ed2cb195f614fcd1e6cfad6f76e95b1dfd77369be34cb02` | Linked parked C |

## Callback and frame evidence

The only aligned Thumb function pointer in the USA ROM occurs at 0x080D7A98 in `func_080D7A70`. No Thumb BL targets the callback directly. The registration passes 40 bytes to `func_08005954` for its payload and supplies a 28-byte request with a data pointer at +4 and a count at +0x14. The scheduler calls its task callback with the task, request and payload in that order. Its initial dispatch sets request state 0 and its deferred dispatch uses the task payload at +0x18. The entry pointer, index and buffer fields used by the three outgoing transfer calls agree with the ROM consumers at 0x080D758C, 0x080D7798 and 0x080D7864. The callback itself returns zero on all paths.

`refine` reports 141 reachable instructions covering 298 bytes. Nine literal words occupy 36 bytes and three two-byte alignment gaps account for the rest. Both game indexes record 141 instructions on the original extent.

## Remaining difference

When a command requests a fill, the BIOS reads one repeated word and writes 0x1000 words to the output allocation. The ROM has three distinct initialized source slots at the one call to `func_08141868` (0x080D79D8). For kinds 4, 5 and the default, the ROM uses offsets 0, 4 and 8 above the current SP. The parked C produces offsets 4, 8 and 0. This changes the short branches and the placement of two nearby literal words. The rest of the function, including every relocated call, matches. Ordinary const words, arrays of one word and named scalar locals produced the same discrepancy. Collapsing the three source calls into one C expression or writing the dispatch as an if/else chain changes the function length.

As a diagnostic only, declaring those three local BIOS source words volatile produced the ROM SHA-256 above. Current strict plausibility reports three `ERROR: volatile` findings. The parked source uses ordinary local words.

## Native gate evidence

The following results use toolkit revision `f0c07c2d7` with the 141-instruction count. Default `match.py` on the parked source reports `inconsistent possible pointer offsets at control-flow join`. With `--owner-runtime-profile bounded-buffer-bios-mixed-fast-fill-source-v1` it reports `inert-spin complete body differs from ROM`. The same selector on the byte-equal diagnostic reports the inconsistent offsets. The disjunctive selector `descriptor-disjunctive-alias-v1` reaches the shared fill call on the diagnostic and reports `buffer callee 0x08141868: structural inventory is not closed`. These two profiles each prove part of the required operation. No native match report has been generated.
