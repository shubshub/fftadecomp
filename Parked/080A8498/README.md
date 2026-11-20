# 0x080A8498 path workspace wrapper

080A8498..080A84E8, 80 bytes, 39 decoded instructions including one Thumb BL.

The verified preceding function 080A8430 ends at 080A8498. At 080A8498
the wrapper saves R4/R5/R6/LR and R8, allocates 416 bytes, and passes SP+32
to 080A12FC. It releases that frame, restores the saves, and returns at
080A84E6. The following function at 080A84E8 opens a different frame.
No direct Thumb BL occurred in the first 0x150000 ROM bytes to this entry.
No decoded nearby direct branch or full-ROM aligned or unaligned word using
its even or Thumb-tagged address was found.

C was compiled with cpp, agbcc -mthumb-interwork -O2 and arm-none-eabi-as.
The call was linked at 080A84D8 against a typed Thumb symbol for 080A12FC.
The complete ELF symbol linked at 080A8498 has size 80 and all 80 bytes
equal the ROM, with no differing offsets.

Both toolkit revisions b141ba59 and b9f1de5 rejected the default match:
  buffer callee 0x080A12FC: signed quotient requires its canonical positive-constant proof
The signed quotient calls at 080A139A and 080A13B0 use coordinate-derived
divisors. Both kits also rejected the documented applicable selector
--owner-runtime-profile bounded-buffer-runtime-summaries-v1:
  buffer callee 0x080A12FC: buffer callee 0x080A0BB8: buffer callee 0x08008480: software float requires its canonical runtime proof
080A14B2 calls 080A0BB8; 080A0CE4 calls 08008480. That function calls
the __muldi3 helper at 08142A20, which software_float_profile reserves
as part of its checked runtime closure. The bounded buffer division profile
summarizes only the four 32-bit division and remainder helpers. No canonical
match report was produced.
