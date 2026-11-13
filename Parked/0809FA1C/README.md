# 0809FA1C: 232 of 235 instructions; the rising phase keeps `level` in a different place

Target: `[0x0809FA1C, 0x0809FBF2)`, 470 bytes. It traces an outline over `s16 samples[length]` into `{u8 flags; u8 index; s16 value}` entries: a rising phase to successive maxima (flag 1), then a falling phase to the last sample (flag 2), and returns the count. Plain `/` compiles to `__divsi3`.

`0809FA1C.c` uses two `static inline` step helpers. These match the falling phase and the block layout of both phases. Three things still differ:

- The frame is 40 bytes against the target's 44.
- The target copies the spilled `level` into ip and then r6 on each rising iteration, and keeps `rise` on the stack. Ours reloads `level` and keeps `rise` in r2.
- The prologue reuses the constant-1 register.

Ruled out: no helpers, a single helper, nested helpers, an `s16 level` in the caller, `&level`, reordered parameters, and indexed instead of incremented windows.
