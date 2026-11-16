# 0x080A8194 - near miss: byte-identical only through a single-use inline helper (208 bytes)

Target: complete `[0x080A8194, 0x080A8264)`, 208 bytes, 90 instructions. Default flags, no new data symbols, no
relocations. Retried 2026-11-16 with kit fcdf2d45.

`080A8194.c` prints `MATCH - byte identical` (90/90 instructions, 208/208 bytes, elf-symbol-thumb-frame-data-v1) and
`plausible.py --strict` exits 0, through `static inline void reset_sequence(EffectSequence080A8194 *)` (clear one
sequence, set byte 0x1C to 0xFF), called once per sequence. The same loop with the helper body written in place is a
204-byte symbol (`compiled symbol is shorter than the indexed span: 204 < 208`).

Not shipped: a helper ships only with shared text (the same text reproduces a second function) or as a verbatim copy
of a real ROM function. There is no second inlined copy and no standalone version of `reset_sequence`.

## What the function does
It allocates the 0x3498-byte effect state (func_08022840), clears it through `g_callbacks_0836D4B8[0]`, clears each of
its 14 sequences again and marks their byte 0x1C 0xFF, lets func_080A433C fill it, and frees it and returns 0 when the
count at 0x26BD is 0.

## What closed the earlier gap
- An indexed loop: the ROM's signed `ble` of the pointer against base + 0x23F4 is gcc's rewrite of an `i < 14`
  counter.
- An `s32` sixth parameter (never narrowed at entry; the frame becomes 0x20).
- The struct of the merged src/080A80C8.c (14 sequences of 0x2C4 bytes, count at 0x26BD).
- func_080A433C with `s8` byte arguments (the call sign-extends).
- The helper: its parameter pointer, computed in two steps, lets the loop pass replace the counter with the pointer
  compare. Six helper-free forms give a reversed down-counter, `g_callbacks_0836D4B8` in r9, or 204 < 208 (the loop
  pass reports "Cannot eliminate biv").

For the helper: each sequence is re-cleared right after the whole block was cleared, the module has per-sequence
routines (func_080A87B4, 080A87DC, 080A88EC), and src/080A80C8.c calls func_080A53E4 per sequence. Against: nothing
else in the ROM carries its text.

The older parked source (a hand-walked pointer loop, `--function-address-profile canonical-thunks-v1`) was refused
with `inert spins require an exact unique nonoverlapping Thumb span`; neither the flag nor that refusal applies to
the source here.
