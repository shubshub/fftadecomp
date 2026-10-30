# match report - 0x0803652C

* source: `src/0803652C.c`
* verification: `elf-symbol-thumb-data-v1`
* source SHA-256: `7b3b9f64f14cec2e4a55f5053415a15b1e3ba989750bb65dc007ecfe7635ea7e`
* mapping SHA-256: `696d16c2d97d3fc16edab7c872b3c4420105b2c438f505eb124811293640d36f`
* control flow: direct Thumb BL with ordinary ARM ABI call summaries
* data symbols SHA-256: `1f9c81831c41751df523547564a4547d7cebeb2b42bc86a401e2560c101843b1`
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `f0b50006060e301cfff7c2ff021c002a1bdb00230e4950008018400040180d49451820204042071c5c1c301c211cfff7cfff011c002905d01f2001402878384008432870231c032beeddf0bc01bc004700000002362e0000` (88 bytes)
* compiled : `f0b50006060e301cfff7c2ff021c002a1bdb00230e495000801840000d4a8018451820204042071c5c1c301c211cfff7cfff011c002905d01f2001402878384008432870231c032beeddf0bc01bc004700000002362e0000`
* source plausibility: plausible
* hand-asm allow list: not listed

**NOT MATCHING - bytes differ** - 85/88 bytes

```
compiled                                rom
push {r4, r5, r6, r7, lr}               push {r4, r5, r6, r7, lr}
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
lsrs r6, r0, #0x18                      lsrs r6, r0, #0x18
adds r0, r6, #0                         adds r0, r6, #0
bl #0x80364bc                           bl #0x80364bc
adds r2, r0, #0                         adds r2, r0, #0
cmp r2, #0                              cmp r2, #0
blt #0x8036576                          blt #0x8036576
movs r3, #0                             movs r3, #0
ldr r1, [pc, #0x38]                     ldr r1, [pc, #0x38]
lsls r0, r2, #1                         lsls r0, r2, #1
adds r0, r0, r2                         adds r0, r0, r2
lsls r0, r0, #1                         lsls r0, r0, #1
ldr r2, [pc, #0x34]                                                               <- extra in compiled
adds r0, r0, r2                                                                   <- extra in compiled
                                        adds r0, r0, r1                           <- missing from compiled
                                        ldr r1, [pc, #0x34]                       <- missing from compiled
adds r5, r0, r1                         adds r5, r0, r1
movs r0, #0x20                          movs r0, #0x20
rsbs r0, r0, #0                         rsbs r0, r0, #0
adds r7, r0, #0                         adds r7, r0, #0
adds r4, r3, #1                         adds r4, r3, #1
adds r0, r6, #0                         adds r0, r6, #0
adds r1, r4, #0                         adds r1, r4, #0
bl #0x80364fc                           bl #0x80364fc
adds r1, r0, #0                         adds r1, r0, #0
cmp r1, #0                              cmp r1, #0
beq #0x8036570                          beq #0x8036570
movs r0, #0x1f                          movs r0, #0x1f
ands r1, r0                             ands r1, r0
ldrb r0, [r5]                           ldrb r0, [r5]
ands r0, r7                             ands r0, r7
orrs r0, r1                             orrs r0, r1
strb r0, [r5]                           strb r0, [r5]
adds r3, r4, #0                         adds r3, r4, #0
cmp r3, #3                              cmp r3, #3
ble #0x8036554                          ble #0x8036554
pop {r4, r5, r6, r7}                    pop {r4, r5, r6, r7}
pop {r0}                                pop {r0}
bx r0                                   bx r0
```
