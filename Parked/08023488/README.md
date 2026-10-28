# 08023488 — recovered, not matched

Target: complete `[0x08023488, 0x08023560)`, 216 bytes and 82 reachable instructions.

The recovered function implements four phases of a menu transition. It allocates a `0x1BD0`-byte display object, starts the existing movement operation, and copies two bytes from resource record 12 at offset `0x18` into the existing mapped destination. It waits for movement completion, saves the actual two-bit mode, and starts the display operation. On completion it frees the object and clears its pointer. The last phase refreshes state if the two-bit mode changed, sets the parent phase to `0x80`, clears its active byte and returns 1. In-progress calls return `0x10`.

Three natural forms of the last mode comparison were attempted with fixed agbcc `-mthumb-interwork -O2` and native `canonical-thunks-v1`: direct comparison, a promoted current-mode local, and an explicit saved-field pointer plus current-mode local. The first two compiled to the target extent but failed byte identity; the pointer form changed the extent. The direct comparison was restored and freshly replayed as the best complete candidate.

The preserved candidate emits one target FUNC of 216 bytes and 82 instructions. Its real typed copy callback is linked through the canonical `_call_via_r3` thunk. The final native invocation exited 1 with `inert-spin complete body differs from ROM`, before source plausibility. No MATCH or native plausible verdict is claimed.

The remaining difference is the phase-3 comparison load schedule. The target forms the saved-mode address in r1, loads the two-bit mode through r0, shifts it left 30, loads the saved byte through r1, then shifts the mode right 30 and compares. The candidate forms the same address but loads the saved byte before loading the mode-offset literal and mode byte. The rest of the compiled instruction sequence and the target's operations are recovered; equal byte/instruction counts do not establish equality.

No assembly, volatile accesses, compiler-option changes, artificial expressions or fake aliases were used. Unknown structure members reflect measured offsets. Active unmatched source/report were removed. The complete captured target and final native log remain under the batch's `08023488` scratch directory. No shared maps, headers, toolkit files or main-tree source were changed.
