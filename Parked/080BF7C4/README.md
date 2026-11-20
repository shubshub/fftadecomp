# 080BF7C4 | ranged weapon position evaluator

This is a partial match for the complete Thumb function at 0x080BF7C4 through 0x080BFDB0 (exclusive). At 0x080C09B0 the battle dispatcher calls 0x080C01D0. For equipment kinds 13, 14 and 19 the instruction at 0x080C02EE loads the function pointer from 0x080C02F4. At 0x080C09F8 the dispatcher invokes the evaluator with its embedded PositionSearch and work pointer. A return of zero completes the search.

The C covers all five states. Initialization collects the equipped item, builds and sorts the candidate positions, and enters the scan. The scan examines at most 12 tiles per call and retains the farthest eligible fallback. Kinds 13 and 14 start and poll a target selection. Kind 19 performs a line trace. The final state compares Manhattan distances and calls the position scorer twice on a nonzero tie. The ROM only replaces its saved position on strictly greater distance.

## Native comparison

The public agbcc build with -mthumb-interwork -O2, linked at 0x080BF7C4 with all 11 distinct direct targets bound, emits 1,556 bytes and 724 reachable instructions. The ROM has 1,516 bytes and 708 reachable instructions, with 1,440 code bytes, 72 literal and table bytes and four alignment bytes. Both have 12 external call sites, in the same order. The indexed instruction count of 708 is correct.

Of the 1,516 original offsets, 433 contain the same byte in this build. The first difference occurs at 0x080BF7DC. The branch for a state above four targets 0x080BFD92 in the ROM and 0x080BFDBA in the candidate. The first six call sites agree exactly. The scan and final scoring states have different register allocation, block placement and literal alignment. The ROM SHA-256 is 58843d34bfc25d4b9fe7658036bc0ad7d8a0527d1df515bdb02266ec5a588d1c. The linked candidate SHA-256 is e11257969a673452b8a804b5ca1ba208895b4324471bbe681467bb21ca019fcd.

With the public verification kit from PR #427 the normal matcher reports “switch caller requires an exact mapped Thumb span” for this candidate. An independent replay of the default switch proof on the original bytes reports “unsupported stack-alias use or escape” at 0x080BFC0A. This instruction passes a pointer to its local eight-byte hit position as the fifth argument to 0x080A8700. The scalar switch profiles reject materializing stack addresses. The guarded and data-free buffer profiles reject this owner's five-way word switch.

In 25 paired emulation cases the original and compiled code produced identical return values, observable helper arguments, restored stack pointers and complete 540-byte search states. The cases exercised all five states, all 11 distinct helper targets, the scan budget, map filtering and tie handling. Both runs used the same simulated helper responses. This evidence supports the reconstruction while byte identity and native admission remain open.
