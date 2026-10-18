# Parked: func_0814862C (16 bytes)

> **Related:** `Parked/0814860C` is the same story one level deeper — both are
> blocked by a **dead u16 load** in the ROM that no plausible C produces. That
> load is what pushes `h` into a callee-saved register, and that register
> pressure is what forces the frame. Read that note first if you take either on.

**The bytes are reproducible, and that is not enough.** A sub-agent found a C
that compiles to the exact 16 bytes — and rejected it because the only source
that produces them is semantically inert control flow. Recording both halves:
the compiler facts are the most useful thing found in this whole pass, and the
source is *not* a match.

## The rejected source

```c
void func_0814862C(Struct0814862C *p, u32 v) {
    u8 b = (u8)v;
    if (p->id)
        p->flag = b;
    else
        p->flag = b;      /* identical arm - the test does nothing */
}
```

Compiles byte-identically. It is also `p->flag = b;` written the long way, and
the only reason for the `if` is to make the compiler keep a frame. Under the
repo rule ("only byte-exact matches **from plausible source**") that is a
steering trick, so `plausible.py` now rejects it (`inert-control-flow`).

The ROM really does have a dead `ldrh r0, [r2]` and a store that does not
depend on it, so *no* C with an observable test reproduces this — the original
must have differed in a way that leaves no trace in the instructions.

## What the agent established about agbcc (worth keeping)

* **`pop {r0}` is the void return path.** In `thumb_exit`
  (`gcc/thumb.c:583-635`) the interworking epilogue picks the return register
  by type: r0 for `VOIDmode`, r1 for anything ≤ 4 bytes, r2 for `double` and
  large structs. Verified for u8/u16/u32/int/long/float/pointer/small struct
  (all r1), double and ≥12-byte structs (r2), void (r0). So the `u16` landing in
  r0 here is not a return value — it is clobbered by the pop. Every function in
  this ROM ending `pop {r0}; bx r0` returns **void**, whatever r0 held before.

* **The frame is decided before the branch is threaded away.**
  `thumb_function_prologue` (`thumb.c:785-789`) pushes lr when
  `live_regs_mask || !leaf_function_p() || far_jump_used_p()`, and reload
  evaluates the same test at `INITIAL_ELIMINATION_OFFSET` (`thumb.h:617`).
  So *any* function with a conditional branch gets `push {lr} … pop {r0}` even
  when the branch is optimised away and no call remains. A straight-line leaf
  never gets one — no combination of argument count, callee-saved register,
  unused stack argument or flag produces it.

* **The dead load was live at reload time.** agbcc deletes unused loads, so
  `u16 id = p->id;` compiles to nothing; the load only survives if it was a
  branch condition.

* **The `lsl/lsr #24` pair needs a register-materialised narrowing.** A bare
  `p->flag = (u8)v;` folds into the `strb`; putting the cast in a `u8` local
  forces the value into a register first, and that is what produces the pair
  *and* the register roles (r1 = mask, r0 = the loaded id, r2 = copied base).

## If someone picks this up

Look for the *real* C rather than a spelling that reproduces the bytes: a
branch whose arms happen to store the same value, or a `volatile` read of an
id that lives in hardware. `volatile` is banned by default here, so that route
needs justification.