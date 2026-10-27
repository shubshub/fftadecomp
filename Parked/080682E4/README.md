# 080682E4: bounded natural reconstruction

Target: complete indexed [0x080682E4, 0x080684B4), 464 bytes and 197 reachable instructions.
Compiler: fixed agbcc -mthumb-interwork -O2, approved 16 MiB ROM.
Native profile requested: canonical-thunks-v1; genuine buffer callbacks and typed function literals are present.

Three natural forms were tested: cursor pointer captured with the other widget pointers; cursor captured after the list-buffer initialization; direct cursor-member access. The middle form is preserved here. It reconstructs list allocation, quantity comparisons, row updates, saved position, drawing callbacks and task-dependent cursor flags. No assembly, volatile, compiler options, forced inlining or artificial control flow was used.

The preserved form produces a 464-byte ELF text body. Manual compilation under the unchanged flags isolates the remaining instruction differences to 0x08068372..0x08068388, the first-loop preheader. ROM initializes the counter, loads the menu pointer, computes the content-member address into ip, then computes the cursor address into sl; the candidate computes the cursor address first and consequently uses different temporary registers for the initial count comparison. The subsequent instructions align with ROM, excluding unresolved object-file call and literal relocations that require native linking.

Native attempt 2 exited 1 with: `compile failed: inert-spin complete body differs from ROM`. This is the exact-body admission gate; no source-plausibility pass or native match is claimed. The direct-member third form also failed the same gate and introduced broader allocation differences. No metadata or ABI repair is indicated by the observed gap. The unmatched active source/report were removed. Only this complete best tested C and this diagnosis are retained in Parked.
