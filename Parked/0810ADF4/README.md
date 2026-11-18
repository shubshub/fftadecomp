# 0810ADF4 scene effect callback

The original and native agbcc `-mthumb-interwork -O2` output agree on all 742 bytes of `[0810ADF4,0810B0DA)`. SHA-256 is `e2ddb1b3554e464d9278de2279b57784d0daf0d95b50bd2349d77d1232cd50c3`. The closed graph has 317 instructions, 690 code bytes, 44 bytes of literal words and 8 alignment bytes. The registration word at 083950B0 points to this Thumb callback. Its adjacent halfword gives a 68-byte payload.

In phase 0x101 the LDM/STM sequence at 0810AF04–0810AF0E copies the four pointers at 08149F04 to the current SP+20. The table contains 083A1DAC, 083A1D94, 083A1D94 and 083A1DAC. The index byte at payload+6 comes from 080DBC88 in phase 0x100. Instruction 0810AF42 loads this byte unsigned. At 0810AF4A the function reads the pointer at SP+20+4×index for the call to 080D6098.

The default matcher refuses stack-address materialization. The existing `named-data-buffer-stack-index-v1` and `named-data-buffer-stack-index-v2` selectors both request a reviewed bound of 4 for `u8[(entry_R2 + 6)]@0x0810AF42` at 0810AF4A. The callback registration and the signed-byte getter 080DBC88 establish no range. Setter 080DBC90 writes the entire low byte to unit+0x1F. One native caller at 08109A56 supplies the result of 080DBCD4, which calls 0809D6BC. With coincident tile positions 0809D6BC returns −1. This callback would then use index 255 and read at SP+1040, beyond its 36-byte local frame. Whether those actors can meet these conditions at runtime remains unverified. The related [08119914 review](../08119914/README.md) traces further writers of the same facing field.

Recheck the actor and facing lifetime from the effect dispatcher before admitting a bound. A mask or a fallback branch would change the original behavior.
