# 0x081491C0 - parked, no match

50 of 54 instructions; the function is **110 bytes** (the index's 98 cut a
4-byte `bl` in half). The span has been corrected in the index.

## The two remaining differences

1. **`0x081491F8`** - agbcc reloads the constant `1` into a fresh register
   where the ROM shares one load across three uses:

   ```
   mine: movs r2,#1 ; orrs r1,r2 ; movs r3,#1 ; ands r5,r3
   rom:  movs r3,#1 ; orrs r1,r3 ; ands r5,r3
   ```

2. **Tail order** - ROM does `ldr r1,[pc,#0x10]` *then* `adds r0,#2`; this
   source does the add first. The `#0x10` vs `#0xc` displacement is a knock-on
   of (1); the ordering itself is independent.

## What was decoded

- `lsls r2,#0x10 / asrs r2,#0xc` is `(s16)raw << 4`, not a shift by 12.
- `lsls r3; subs` is `* 7`.
- Byte 0 is **two bitfield stores merged by GCC** (`flag7` then `bits_0_6`) -
  the only form giving both the ROM's order and its `orrs`.
- Byte 1 is four bitfield stores, and `rsbs #0x11` is `-0x11` = `~0x10`, so the
  masks are `~0x0F, ~0x10, ~0x20, ~0x40`: bits 0, 4, 5 and 6 cleared, then 4
  and 5 set from the arguments.
- The tail call is `func_0814224C(&state->unknown_02[0], 5,
  (void *)(*(u32 *)0x0836D4B8))` - `0x0836D4B8` loaded through a variable, so
  no relocation is needed.
- agbcc gives an all-bitfield struct 4-byte size and alignment, which is why a
  typedef'd bitfield struct puts the fields at +4 instead of +1.

Ruled out: 17 spellings of the byte-0 value, locals for it or for the third
argument (each forces a frame), several bitfield splits, a named symbol for
`0x0836D4B8`, moving the byte-1 stores earlier, and the whole flag matrix
(`-O1..-Os`, `-fcse-follow-jumps`, `-fno-gcse`, `-fno-crossjumping`,
`-fcombine-insns`, …) - all identical output.

## Note: the tooling gap here has since been fixed

This function's last call is `bl 0x0814224C`, a `_call_via_r2` thunk that
`match.py` did not recognise, so it refused the symbol regardless of the source.
`match.py` now accepts agbcc's `_call_via_r0..r14` and verifies each thunk
against the ROM. A future attempt will get a real verdict from the verifier
instead of a compile error.