# match report - 0x0813D518

* source: `src/0813D518.c`
* verification: `elf-symbol-thumb-frame-data-v1`
* source SHA-256: `0ffbfa4d7c6d7152741702967d8c4cd059032a4422f3cf2a22b47a0a37291a12`
* stack frame: fixed Thumb frames and bounded stack aliases with return provenance
* mapping SHA-256: `66922b9eb6d67f8feadda97f64866aec7251a87dbf35ede0a00fdaf77d1f8158`
* control flow: direct Thumb BL with ordinary ARM ABI call summaries
* data symbols SHA-256: `c6dfeaa3c18128a41d3cf5aaf93b6b81675b51508efdc53fc8a1f1a9a2a41aa8`
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `f0b557464e464546e0b484b0002082468146002615498846154a1468154be01880190078002800d19de0134af300981b8000851817216956012040421f1c81421ed1b81900010d49401820180822a95e0a23ea5e2b7d00240094ac7c0194ec7c02946c7d039400f057fd49e040090003b0f300026c8b000058903a080480000017202856002802d0012809d015e044466089298b40180004000c8246a08907e04346d8892c8b00190004000c8246188a6d8b40190004000c8146b91909011f4809181f4b18684018bd1bad00ad182989544622041214891a090409146a894c4623041b14d21a120412142b7d00240094ac7c0194ec7c02946c7d039400f00cfd0f4d2c6871000f4aa018421813889c460020115e0c4b1814814219d1b819000106494018201801f0ddfb000600281ad02868064a80188019002113e004800000b0f30002448b00000000ffff6c8b000060460138002110800004002803d1094be01880190170701c0006060e132e00d852e704b038bc9846a146aa46f0bc01bc004700006c8b0000` (392 bytes)
* compiled : `f0b557464e464546e0b484b000208246814600261549884615480468154aa01880190078002800d19de0134af300981b8000851817216956012040421f1c81421ed1b81900010d4bc01820180824295f0a23ea5e2b7d00240094ac7c0194ec7c02946c7d039400f057fd49e040090003b0f300026c8b000058903a080480000017202856002802d0012809d015e044466089298b40180004000c8246a08907e04346d8892c8b00190004000c8246188a6d8b40190004000c8146bd1bad00ad182989524610040014091a6a894b4618040014121a1948bb191b01194c1b190068c01809040914120412142b7d00240094ac7c0194ec7c02946c7d039400f00cfd0e4d2c6871000f4aa018421813889c460020115e0c4b1814814219d1b819000107494018201801f0ddfb000600281ad02868064a80188019002113e0b0f3000204800000448b00000000ffff6c8b000060460138002110800004002803d1094be01880190170701c0006060e132e00d852e704b038bc9846a146aa46f0bc01bc004700006c8b0000`
* source plausibility: plausible
* hand-asm allow list: not listed

**NOT MATCHING - bytes differ** - 351/392 bytes

```
compiled                                rom
push {r4, r5, r6, r7, lr}               push {r4, r5, r6, r7, lr}
mov r7, sl                              mov r7, sl
mov r6, sb                              mov r6, sb
mov r5, r8                              mov r5, r8
push {r5, r6, r7}                       push {r5, r6, r7}
sub sp, #0x10                           sub sp, #0x10
movs r0, #0                             movs r0, #0
mov sl, r0                              mov sl, r0
mov sb, r0                              mov sb, r0
movs r6, #0                             movs r6, #0
ldr r1, [pc, #0x54]                     ldr r1, [pc, #0x54]
mov r8, r1                              mov r8, r1
ldr r0, [pc, #0x54]                                                               <- extra in compiled
ldr r4, [r0]                                                                      <- extra in compiled
ldr r2, [pc, #0x54]                     ldr r2, [pc, #0x54]
adds r0, r4, r2                                                                   <- extra in compiled
                                        ldr r4, [r2]                              <- missing from compiled
                                        ldr r3, [pc, #0x54]                       <- missing from compiled
                                        adds r0, r4, r3                           <- missing from compiled
adds r0, r0, r6                         adds r0, r0, r6
ldrb r0, [r0]                           ldrb r0, [r0]
cmp r0, #0                              cmp r0, #0
bne #0x813d542                          bne #0x813d542
b #0x813d67e                            b #0x813d67e
ldr r2, [pc, #0x4c]                     ldr r2, [pc, #0x4c]
lsls r3, r6, #3                         lsls r3, r6, #3
subs r0, r3, r6                         subs r0, r3, r6
lsls r0, r0, #2                         lsls r0, r0, #2
adds r5, r0, r2                         adds r5, r0, r2
movs r1, #0x17                          movs r1, #0x17
ldrsb r1, [r5, r1]                      ldrsb r1, [r5, r1]
movs r0, #1                             movs r0, #1
rsbs r0, r0, #0                         rsbs r0, r0, #0
adds r7, r3, #0                         adds r7, r3, #0
cmp r1, r0                              cmp r1, r0
bne #0x813d598                          bne #0x813d598
adds r0, r7, r6                         adds r0, r7, r6
lsls r0, r0, #4                         lsls r0, r0, #4
ldr r3, [pc, #0x34]                                                               <- extra in compiled
adds r0, r0, r3                                                                   <- extra in compiled
                                        ldr r1, [pc, #0x34]                       <- missing from compiled
                                        adds r0, r0, r1                           <- missing from compiled
adds r0, r4, r0                         adds r0, r4, r0
movs r4, #8                                                                       <- extra in compiled
ldrsh r1, [r5, r4]                                                                <- extra in compiled
                                        movs r2, #8                               <- missing from compiled
                                        ldrsh r1, [r5, r2]                        <- missing from compiled
movs r3, #0xa                           movs r3, #0xa
ldrsh r2, [r5, r3]                      ldrsh r2, [r5, r3]
ldrb r3, [r5, #0x14]                    ldrb r3, [r5, #0x14]
movs r4, #0                             movs r4, #0
str r4, [sp]                            str r4, [sp]
ldrb r4, [r5, #0x12]                    ldrb r4, [r5, #0x12]
str r4, [sp, #4]                        str r4, [sp, #4]
ldrb r4, [r5, #0x13]                    ldrb r4, [r5, #0x13]
str r4, [sp, #8]                        str r4, [sp, #8]
ldrb r4, [r5, #0x15]                    ldrb r4, [r5, #0x15]
str r4, [sp, #0xc]                      str r4, [sp, #0xc]
bl #0x813e030                           bl #0x813e030
b #0x813d618                            b #0x813d618
movs r0, #0x17                          movs r0, #0x17
ldrsb r0, [r5, r0]                      ldrsb r0, [r5, r0]
cmp r0, #0                              cmp r0, #0
beq #0x813d5a6                          beq #0x813d5a6
cmp r0, #1                              cmp r0, #1
beq #0x813d5b8                          beq #0x813d5b8
b #0x813d5d2                            b #0x813d5d2
mov r4, r8                              mov r4, r8
ldrh r0, [r4, #0xa]                     ldrh r0, [r4, #0xa]
ldrh r1, [r5, #0x18]                    ldrh r1, [r5, #0x18]
adds r0, r0, r1                         adds r0, r0, r1
lsls r0, r0, #0x10                      lsls r0, r0, #0x10
lsrs r0, r0, #0x10                      lsrs r0, r0, #0x10
mov sl, r0                              mov sl, r0
ldrh r0, [r4, #0xc]                     ldrh r0, [r4, #0xc]
b #0x813d5c8                            b #0x813d5c8
mov r3, r8                              mov r3, r8
ldrh r0, [r3, #0xe]                     ldrh r0, [r3, #0xe]
ldrh r4, [r5, #0x18]                    ldrh r4, [r5, #0x18]
adds r0, r0, r4                         adds r0, r0, r4
lsls r0, r0, #0x10                      lsls r0, r0, #0x10
lsrs r0, r0, #0x10                      lsrs r0, r0, #0x10
mov sl, r0                              mov sl, r0
ldrh r0, [r3, #0x10]                    ldrh r0, [r3, #0x10]
ldrh r5, [r5, #0x1a]                    ldrh r5, [r5, #0x1a]
adds r0, r0, r5                         adds r0, r0, r5
lsls r0, r0, #0x10                      lsls r0, r0, #0x10
lsrs r0, r0, #0x10                      lsrs r0, r0, #0x10
mov sb, r0                              mov sb, r0
                                        adds r1, r7, r6                           <- missing from compiled
                                        lsls r1, r1, #4                           <- missing from compiled
                                        ldr r0, [pc, #0x7c]                       <- missing from compiled
                                        adds r1, r1, r0                           <- missing from compiled
                                        ldr r3, [pc, #0x7c]                       <- missing from compiled
                                        ldr r0, [r3]                              <- missing from compiled
                                        adds r0, r0, r1                           <- missing from compiled
subs r5, r7, r6                         subs r5, r7, r6
lsls r5, r5, #2                         lsls r5, r5, #2
adds r5, r5, r2                         adds r5, r5, r2
ldrh r1, [r5, #8]                       ldrh r1, [r5, #8]
mov r2, sl                                                                        <- extra in compiled
lsls r0, r2, #0x10                                                                <- extra in compiled
asrs r0, r0, #0x10                                                                <- extra in compiled
subs r1, r1, r0                                                                   <- extra in compiled
ldrh r2, [r5, #0xa]                                                               <- extra in compiled
mov r3, sb                                                                        <- extra in compiled
lsls r0, r3, #0x10                                                                <- extra in compiled
asrs r0, r0, #0x10                                                                <- extra in compiled
subs r2, r2, r0                                                                   <- extra in compiled
ldr r0, [pc, #0x64]                                                               <- extra in compiled
adds r3, r7, r6                                                                   <- extra in compiled
lsls r3, r3, #4                                                                   <- extra in compiled
ldr r4, [pc, #0x64]                                                               <- extra in compiled
adds r3, r3, r4                                                                   <- extra in compiled
ldr r0, [r0]                                                                      <- extra in compiled
adds r0, r0, r3                                                                   <- extra in compiled
                                        mov r4, sl                                <- missing from compiled
                                        lsls r2, r4, #0x10                        <- missing from compiled
                                        asrs r2, r2, #0x10                        <- missing from compiled
                                        subs r1, r1, r2                           <- missing from compiled
lsls r1, r1, #0x10                      lsls r1, r1, #0x10
asrs r1, r1, #0x10                      asrs r1, r1, #0x10
                                        ldrh r2, [r5, #0xa]                       <- missing from compiled
                                        mov r4, sb                                <- missing from compiled
                                        lsls r3, r4, #0x10                        <- missing from compiled
                                        asrs r3, r3, #0x10                        <- missing from compiled
                                        subs r2, r2, r3                           <- missing from compiled
lsls r2, r2, #0x10                      lsls r2, r2, #0x10
asrs r2, r2, #0x10                      asrs r2, r2, #0x10
ldrb r3, [r5, #0x14]                    ldrb r3, [r5, #0x14]
movs r4, #0                             movs r4, #0
str r4, [sp]                            str r4, [sp]
ldrb r4, [r5, #0x12]                    ldrb r4, [r5, #0x12]
str r4, [sp, #4]                        str r4, [sp, #4]
ldrb r4, [r5, #0x13]                    ldrb r4, [r5, #0x13]
str r4, [sp, #8]                        str r4, [sp, #8]
ldrb r4, [r5, #0x15]                    ldrb r4, [r5, #0x15]
str r4, [sp, #0xc]                      str r4, [sp, #0xc]
bl #0x813e030                           bl #0x813e030
ldr r5, [pc, #0x38]                                                               <- extra in compiled
                                        ldr r5, [pc, #0x3c]                       <- missing from compiled
ldr r4, [r5]                            ldr r4, [r5]
lsls r1, r6, #1                         lsls r1, r6, #1
ldr r2, [pc, #0x3c]                     ldr r2, [pc, #0x3c]
adds r0, r4, r2                         adds r0, r4, r2
adds r2, r0, r1                         adds r2, r0, r1
ldrh r3, [r2]                           ldrh r3, [r2]
mov ip, r3                              mov ip, r3
movs r0, #0                             movs r0, #0
ldrsh r1, [r2, r0]                      ldrsh r1, [r2, r0]
ldr r3, [pc, #0x30]                     ldr r3, [pc, #0x30]
asrs r0, r3, #0x10                      asrs r0, r3, #0x10
cmp r1, r0                              cmp r1, r0
bne #0x813d668                          bne #0x813d668
adds r0, r7, r6                         adds r0, r7, r6
lsls r0, r0, #4                         lsls r0, r0, #4
ldr r1, [pc, #0x1c]                                                               <- extra in compiled
                                        ldr r1, [pc, #0x18]                       <- missing from compiled
adds r0, r0, r1                         adds r0, r0, r1
adds r0, r4, r0                         adds r0, r4, r0
bl #0x813edfc                           bl #0x813edfc
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
cmp r0, #0                              cmp r0, #0
beq #0x813d67e                          beq #0x813d67e
ldr r0, [r5]                            ldr r0, [r5]
ldr r2, [pc, #0x18]                     ldr r2, [pc, #0x18]
adds r0, r0, r2                         adds r0, r0, r2
adds r0, r0, r6                         adds r0, r0, r6
movs r1, #0                             movs r1, #0
b #0x813d67c                            b #0x813d67c
mov r0, ip                              mov r0, ip
subs r0, #1                             subs r0, #1
movs r1, #0                             movs r1, #0
strh r0, [r2]                           strh r0, [r2]
lsls r0, r0, #0x10                      lsls r0, r0, #0x10
cmp r0, #0                              cmp r0, #0
bne #0x813d67e                          bne #0x813d67e
ldr r3, [pc, #0x24]                     ldr r3, [pc, #0x24]
adds r0, r4, r3                         adds r0, r4, r3
adds r0, r0, r6                         adds r0, r0, r6
strb r1, [r0]                           strb r1, [r0]
adds r0, r6, #1                         adds r0, r6, #1
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
lsrs r6, r0, #0x18                      lsrs r6, r0, #0x18
cmp r6, #0x13                           cmp r6, #0x13
bhi #0x813d68a                          bhi #0x813d68a
b #0x813d530                            b #0x813d530
add sp, #0x10                           add sp, #0x10
pop {r3, r4, r5}                        pop {r3, r4, r5}
mov r8, r3                              mov r8, r3
mov sb, r4                              mov sb, r4
mov sl, r5                              mov sl, r5
pop {r4, r5, r6, r7}                    pop {r4, r5, r6, r7}
pop {r0}                                pop {r0}
bx r0                                   bx r0
```
