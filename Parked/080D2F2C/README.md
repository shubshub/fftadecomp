# 080D2F2C bounded matching failure

Target: complete [0x080D2F2C,0x080D2F78),76 bytes. Accepted request6525963298, author sol-2F2C.

The observed operation counts nonzero bytes at g_state_02000000+0x84+n*0x108 for24 records, then calls the actual defining void func_080C9574(u16,u16) with(0x5A7,0) when count>5 or(0x5A7,1) otherwise. All forms retain that interface and mapped global.

Three bounded natural forms were tested with the default native matcher:

1. Direct byte-field pointer initializer: native extent refusal, compiled72<indexed76. The retained unlinked diagnostic shows a g_state+0x84 literal instead of the ROM base-address navigation. No comparison or plausibility verdict was produced.
2. Observed0x108-stride record view with byte field0x84: native full76B extent, plausible, NOT MATCHING.68/76 bytes and22/28 instructions identical. The compiled loop recalculates field+0x84 each iteration; ROM derives the biased field pointer before entering the loop. The exact complete target/compiled bodies are in attempt2 receipt and report.
3. Explicit state-base navigation to the byte field once, followed by pointer stride: native extent refusal,72<76. No comparison or plausibility verdict was produced. This is the final preserved080D2F2C.c.

attempt2-report.md belongs to the second form. It does not certify the final source. All full native outputs, source snapshots for forms1/2, current-machine receipts, source/header/mapping pins and the form1 unlinked diagnostic remain in the address-owned author directory:

/home/user/Desktop/FFTA-handover-2026-10-30/state/matching-080D2F2C-author/

Each receipt records the exact command and runtime, raw source hash, composite source/header fingerprint, all9 shared-header hashes,3 mapping hashes, complete ROM body, and native exit/failure. No successful proof was replayed. No shared source/header/map/toolkit file was edited. Only the owned active target source/report were moved here after the bounded failure.
