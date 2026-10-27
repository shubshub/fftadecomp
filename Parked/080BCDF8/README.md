# 080BCDF8

Target: complete [0x080BCDF8, 0x080BCED0), 216 bytes and 103 reachable instructions. The preserved candidate emits one complete 216-byte FUNC symbol and 102 instructions with fixed agbcc `-mthumb-interwork -O2`.

The last canonical-thunks-v1 native match exited 1 with `inert-spin complete body differs from ROM`. This is an early byte-comparison refusal; no accepted plausibility result or N/N match is claimed.

Recovered behavior: transition into requested mode 1 or 2, invoke its update with the current/requested equality flag, and clear the 0x218-byte state after all linked nodes become inactive while retaining the requested mode. Native update entries narrow their second argument to u8; nodes have an active byte at +0x11 and next pointer at +0x18.

Remaining differences: the candidate folds the initial requested-mode comparison to subtract-one/range testing, whereas ROM compares separately against 1 and 2. Its current-byte address uses r6 and its requested-byte address uses r4 in the update branches; ROM uses r4 and r6 respectively. The inactivity flag is initialized after loading the head in the candidate, versus before that load in ROM. Final callback argument/load ordering also differs. Complete extents agree, but instruction counts and bytes do not.

Three natural forms were tested: a combined inactive-reset inline helper with a nested requested-mode switch; a cached u8 requested mode with explicit OR and earlier inactivity initialization (native extent/profile refusal); and the preserved separate all-inactive predicate with a promoted requested-mode local and resets in the caller. No compiler flags, artificial reads, padding, assembly, or volatile accesses were introduced.
