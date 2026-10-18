# Parked: func_08003A40 (40 bytes)

**Not matched.**  A sub-agent reported this as 44/44 byte-identical at `-O0`;
that claim was re-checked and is false - the compile matches the prologue and
then diverges.  Recorded here so nobody repeats the search.

## What it does

```
push {r7, lr}  sub sp, #8  mov r7, sp   str r0, [r7]
ldr r0, [pc, #0x1c]        ; pool 0x08003A68 = 0x0836D480  (four u32 pointers)
ldr r1, [r7]  adds r2, r1, #0  lsls r1, r2, #2  adds r0, r0, r1
ldr r1, [r0]  str r1, [r7, #4]  ldr r1, [r7, #4]  adds r0, r1, #0  adds r0, #8
movs r1, #0   str r1, [r0]
add sp, #8   pop {r7}  pop {r0}  bx r0
```

Best recovered source:

```c
typedef struct { u32 *slots[4]; } EntryTable;
void func_08003A40(int index) {
    u32 *entry = ((EntryTable *)0x0836D480)->slots[index];
    *(u32 *)((u8 *)entry + 8) = 0;
}
```

At `-O2` this folds to 20 bytes with no frame.  At `-O0` it keeps the frame and
the spills but the body does not line up.

## What this did surface (both true, both important)

1. **`match.py` cannot verify any framed function.**  It rejects the symbol with
   `unsupported stack-pointer adjustment` on the `sub sp, #8`.  All 45 sources in
   `src/` are frameless - so the verifier currently only covers functions with no
   stack frame at all.  A scan finds **4,196 sp adjustments** in the code region,
   so the great majority of the ROM is currently unverifiable.  This is the
   biggest tooling gap in the project, ahead of the linked build.
2. **A handful of ROM functions use r7 as a frame pointer** - `0x08000718`,
   `0x08003A08`, `0x08003A40` (a sub-agent reported six).  Those functions need
   `-fno-omit-frame-pointer` or were built with optimisation off, which suggests
   the ROM was **not built with one uniform flag set**.  The `-O2` conclusion
   rests on 43 frameless functions and does not extend to these.
