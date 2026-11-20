# 080BEAC8 | self-targeted battle position evaluator

The recovered C covers the full Thumb routine from 0x080BEAC8 to 0x080BEF28, exclusive. It compiles with the unchanged public battle_position_search.h. Statuses 0 and 1 populate the score grid from the two groups. Status 2 scans eligible map cells, retaining a better target and endpoint and yielding after a candidate. At grid end it returns zero if it found a position. Otherwise status 3 runs the fallback scan, which completes in a single call. A zero callback result tells the dispatcher that evaluation is complete.

## Entry and signature

The original game selects this evaluator at 0x080C0334. The unique aligned pointer 0x080BEAC9 at 0x080C0348 is its source. A full ROM sweep found no direct Thumb BL to 0x080BEAC8. The call at 0x080C09B0 invokes the selector and stores its returned pointer in the dispatcher at offset 0x528C. At 0x080C09F8 the dispatcher calls through the R2 thunk, passing its embedded PositionSearch at +0x5290 in R0 and its work pointer from +0 in R1. The caller tests the low byte of R0. The routine itself returns a full word containing 0 or 1 and implements the public PositionEvaluator signature.

Ten original BL sites reach seven helpers. Their definitions support the equipment output of two halfwords, the 12-byte range request, the eight-argument group-grid update, and the ten-argument endpoint-scoring call with two separate byte outputs. The source uses the unsigned first two coordinate parameters in the compiled 0x080BE5F4 definition. The existing caller at 0x080BE8E0 declares those two parameters as signed. Every call from this evaluator follows bounds checks limiting both coordinates to 0 through 15.

## Native build and remaining differences

Using agbcc -mthumb-interwork -O2, the original seven Thumb import addresses, and linking at 0x080BEAC8 produces a 1,116-byte ELF function symbol. Of the 1,120 original offsets, 625 contain the same byte, 491 differ and the final four have no candidate byte. The first difference is at 0x080BEBA7, where the immediate-one instruction selecting the scan flag destination uses R4 in the candidate and R0 in the ROM. Differences after that include register allocation throughout the two scanning phases, signed and unsigned reloads at the 0x080BE5F4 call and the final literal pool.

The original has 538 reachable Thumb instructions occupying 1,096 bytes, five four-byte literals and four bytes of interior alignment. Its SHA-256 is d0101fe4ae244b647b0d4654d19e2763dbbb6c0765ee52237199525cdd21ea47. The linked candidate SHA-256 is a82185908c67ddb51fc6c372971f71932d7ccd0a4e6250729c6f64ab0cc2413e.

The public #423 verifier stops while tracing the local two-halfword output through 0x0812F0D8, 0x0812E55C, 0x0812E4F4 and 0x080CA7A4. It reports an unresolved program-counter write in the last helper. The linked-byte mismatch is independent of that verifier limitation. The public source plausibility check reports zero findings.

The native differential test ran both bodies with 430 combinations covering all statuses, both group lists, cursor and grid boundaries, denied and enabled cells, fixed-position filtering, score comparisons, and end-of-grid transitions. It compared the ordered helper arguments, returned word, context and output writes, restored stack pointer, and preserved R4 through R11. The test ran the same cases twice, once with the helper return preserving R1 through R3 and once deliberately changing those caller-saved registers. The seven helper bodies used controlled returning stubs. This establishes agreement for these fixtures and leaves the byte mismatch open.
