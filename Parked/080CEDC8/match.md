# match report - 0x080CEDC8

* source: `src/080CEDC8.c`
* verification: `elf-symbol-thumb-data-v1`
* source SHA-256: `fd57e0b71ceadb8133ad8c95d8326cef9af500a8a95a39f5410fa16595350975`
* mapping SHA-256: `a171396d4014451610094ec841d614bfb66994c90ffbaece96115af50c0ddb4f`
* control flow: direct Thumb BL with ordinary ARM ABI call summaries
* data symbols SHA-256: `7dfd422e616bf1e62b77210d6b2d3b9f5f87af6b96c6859ebb2675e22a841ab1`
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `f0b5071c024803494018056805e0000000000002c8280000ad68a8680028fbd16b68002b14d02a6891781c200840161c00280bd11c241d1c6b68002b08d02a689178201c0840161c0028f4d0002b03d1002054e0141c20e0a8689860a968002901d0686848601d4c2268301c102173f009fa2268281c0c2173f004fa0023184a0324117850782040000208430028e1d0013310323f2bf4dd002412480368201c391c102273f0f0f900220f490868002804d001320c313f2af8dd00210b480c4bc2181068002815d00c60002048601068886010684160116010e00000b8d43608c8210002bcd43608c825000200000002c828000011600c60886048600120f0bc02bc084730b50004050c281c2a21fff701fb0004` (276 bytes)
* compiled : `f0b5071c024803494018056805e0000000000002c8280000ad68a8680028fbd16a68002a13d02e68b1781c20084000280ad11c23151c6a68002a08d02e68b178181c08400028f5d06968002901d100205de0a8688860a968002901d068684860164c2268301c102173f00cfa2268281c0c2173f007fa0026114b002419785a78032010400002014300290bd0013410333f2c08dc18785a7803211140090208430028f3d11e1c07480368301c391c102273f0eaf9044d00240ce00000b8d43608c8210002bcd43608c825000201340c353f2c02dc28680028f8d1402c00d10025064807494218116800290bd02e6000206860a9604d60156008e0000000000002c828000015602e60a96069600120f0bc02bc0847`
* source plausibility: plausible
* hand-asm allow list: not listed

**NOT MATCHING - bytes differ** - 164/276 bytes

```
compiled                                rom
push {r4, r5, r6, r7, lr}               push {r4, r5, r6, r7, lr}
adds r7, r0, #0                         adds r7, r0, #0
ldr r0, [pc, #8]                        ldr r0, [pc, #8]
ldr r1, [pc, #0xc]                      ldr r1, [pc, #0xc]
adds r0, r0, r1                         adds r0, r0, r1
ldr r5, [r0]                            ldr r5, [r0]
b #0x80cede2                            b #0x80cede2
ldr r5, [r5, #8]                        ldr r5, [r5, #8]
ldr r0, [r5, #8]                        ldr r0, [r5, #8]
cmp r0, #0                              cmp r0, #0
bne #0x80cede0                          bne #0x80cede0
ldr r2, [r5, #4]                                                                  <- extra in compiled
cmp r2, #0                                                                        <- extra in compiled
beq #0x80cee16                                                                    <- extra in compiled
ldr r6, [r5]                                                                      <- extra in compiled
ldrb r1, [r6, #2]                                                                 <- extra in compiled
                                        ldr r3, [r5, #4]                          <- missing from compiled
                                        cmp r3, #0                                <- missing from compiled
                                        beq #0x80cee18                            <- missing from compiled
                                        ldr r2, [r5]                              <- missing from compiled
                                        ldrb r1, [r2, #2]                         <- missing from compiled
movs r0, #0x1c                          movs r0, #0x1c
ands r0, r1                             ands r0, r1
                                        adds r6, r2, #0                           <- missing from compiled
cmp r0, #0                              cmp r0, #0
bne #0x80cee10                                                                    <- extra in compiled
movs r3, #0x1c                                                                    <- extra in compiled
adds r5, r2, #0                                                                   <- extra in compiled
ldr r2, [r5, #4]                                                                  <- extra in compiled
cmp r2, #0                                                                        <- extra in compiled
beq #0x80cee16                                                                    <- extra in compiled
ldr r6, [r5]                                                                      <- extra in compiled
ldrb r1, [r6, #2]                                                                 <- extra in compiled
adds r0, r3, #0                                                                   <- extra in compiled
                                        bne #0x80cee14                            <- missing from compiled
                                        movs r4, #0x1c                            <- missing from compiled
                                        adds r5, r3, #0                           <- missing from compiled
                                        ldr r3, [r5, #4]                          <- missing from compiled
                                        cmp r3, #0                                <- missing from compiled
                                        beq #0x80cee18                            <- missing from compiled
                                        ldr r2, [r5]                              <- missing from compiled
                                        ldrb r1, [r2, #2]                         <- missing from compiled
                                        adds r0, r4, #0                           <- missing from compiled
ands r0, r1                             ands r0, r1
                                        adds r6, r2, #0                           <- missing from compiled
cmp r0, #0                              cmp r0, #0
beq #0x80cedfc                                                                    <- extra in compiled
ldr r1, [r5, #4]                                                                  <- extra in compiled
cmp r1, #0                                                                        <- extra in compiled
bne #0x80cee1a                                                                    <- extra in compiled
                                        beq #0x80cedfe                            <- missing from compiled
                                        cmp r3, #0                                <- missing from compiled
                                        bne #0x80cee20                            <- missing from compiled
movs r0, #0                             movs r0, #0
b #0x80ceed6                                                                      <- extra in compiled
                                        b #0x80ceec6                              <- missing from compiled
                                        adds r4, r2, #0                           <- missing from compiled
                                        b #0x80cee62                              <- missing from compiled
ldr r0, [r5, #8]                        ldr r0, [r5, #8]
str r0, [r1, #8]                                                                  <- extra in compiled
                                        str r0, [r3, #8]                          <- missing from compiled
ldr r1, [r5, #8]                        ldr r1, [r5, #8]
cmp r1, #0                              cmp r1, #0
beq #0x80cee28                                                                    <- extra in compiled
                                        beq #0x80cee2e                            <- missing from compiled
ldr r0, [r5, #4]                        ldr r0, [r5, #4]
str r0, [r1, #4]                        str r0, [r1, #4]
ldr r4, [pc, #0x58]                                                               <- extra in compiled
                                        ldr r4, [pc, #0x74]                       <- missing from compiled
ldr r2, [r4]                            ldr r2, [r4]
adds r0, r6, #0                         adds r0, r6, #0
movs r1, #0x10                          movs r1, #0x10
bl #0x814224c                                                                     <- extra in compiled
ldr r2, [r4]                            ldr r2, [r4]
adds r0, r5, #0                         adds r0, r5, #0
movs r1, #0xc                           movs r1, #0xc
bl #0x814224c                                                                     <- extra in compiled
movs r6, #0                                                                       <- extra in compiled
ldr r3, [pc, #0x44]                                                               <- extra in compiled
movs r4, #0                                                                       <- extra in compiled
ldrb r1, [r3]                                                                     <- extra in compiled
ldrb r2, [r3, #1]                                                                 <- extra in compiled
movs r0, #3                                                                       <- extra in compiled
ands r0, r2                                                                       <- extra in compiled
                                        movs r3, #0                               <- missing from compiled
                                        ldr r2, [pc, #0x60]                       <- missing from compiled
                                        movs r4, #3                               <- missing from compiled
                                        ldrb r1, [r2]                             <- missing from compiled
                                        ldrb r0, [r2, #1]                         <- missing from compiled
                                        ands r0, r4                               <- missing from compiled
lsls r0, r0, #8                         lsls r0, r0, #8
orrs r1, r0                                                                       <- extra in compiled
cmp r1, #0                                                                        <- extra in compiled
beq #0x80cee6c                                                                    <- extra in compiled
adds r4, #1                                                                       <- extra in compiled
adds r3, #0x10                                                                    <- extra in compiled
cmp r4, #0x3f                                                                     <- extra in compiled
bgt #0x80cee6e                                                                    <- extra in compiled
ldrb r0, [r3]                                                                     <- extra in compiled
ldrb r2, [r3, #1]                                                                 <- extra in compiled
movs r1, #3                                                                       <- extra in compiled
ands r1, r2                                                                       <- extra in compiled
lsls r1, r1, #8                                                                   <- extra in compiled
orrs r0, r1                             orrs r0, r1
cmp r0, #0                              cmp r0, #0
bne #0x80cee54                                                                    <- extra in compiled
adds r6, r3, #0                                                                   <- extra in compiled
ldr r0, [pc, #0x1c]                                                               <- extra in compiled
                                        beq #0x80cee1c                            <- missing from compiled
                                        adds r3, #1                               <- missing from compiled
                                        adds r2, #0x10                            <- missing from compiled
                                        cmp r3, #0x3f                             <- missing from compiled
                                        ble #0x80cee4a                            <- missing from compiled
                                        movs r4, #0                               <- missing from compiled
                                        ldr r0, [pc, #0x48]                       <- missing from compiled
ldr r3, [r0]                            ldr r3, [r0]
adds r0, r6, #0                                                                   <- extra in compiled
                                        adds r0, r4, #0                           <- missing from compiled
adds r1, r7, #0                         adds r1, r7, #0
movs r2, #0x10                          movs r2, #0x10
bl #0x8142250                                                                     <- extra in compiled
ldr r5, [pc, #0x10]                                                               <- extra in compiled
movs r4, #0                                                                       <- extra in compiled
b #0x80cee9c                                                                      <- extra in compiled
adds r4, #1                                                                       <- extra in compiled
adds r5, #0xc                                                                     <- extra in compiled
cmp r4, #0x3f                                                                     <- extra in compiled
bgt #0x80ceea2                                                                    <- extra in compiled
ldr r0, [r5]                                                                      <- extra in compiled
                                        movs r2, #0                               <- missing from compiled
                                        ldr r1, [pc, #0x3c]                       <- missing from compiled
                                        ldr r0, [r1]                              <- missing from compiled
cmp r0, #0                              cmp r0, #0
bne #0x80cee94                                                                    <- extra in compiled
cmp r4, #0x40                                                                     <- extra in compiled
bne #0x80ceea8                                                                    <- extra in compiled
movs r5, #0                                                                       <- extra in compiled
ldr r0, [pc, #0x18]                                                               <- extra in compiled
ldr r1, [pc, #0x1c]                                                               <- extra in compiled
adds r2, r0, r1                                                                   <- extra in compiled
ldr r1, [r2]                                                                      <- extra in compiled
cmp r1, #0                                                                        <- extra in compiled
beq #0x80ceecc                                                                    <- extra in compiled
str r6, [r5]                                                                      <- extra in compiled
movs r0, #0                                                                       <- extra in compiled
str r0, [r5, #4]                                                                  <- extra in compiled
str r1, [r5, #8]                                                                  <- extra in compiled
str r5, [r1, #4]                                                                  <- extra in compiled
str r5, [r2]                                                                      <- extra in compiled
b #0x80ceed4                                                                      <- extra in compiled
str r5, [r2]                                                                      <- extra in compiled
str r6, [r5]                                                                      <- extra in compiled
str r1, [r5, #8]                                                                  <- extra in compiled
str r1, [r5, #4]                                                                  <- extra in compiled
movs r0, #1                                                                       <- extra in compiled
pop {r4, r5, r6, r7}                                                              <- extra in compiled
pop {r1}                                                                          <- extra in compiled
bx r1                                                                             <- extra in compiled
                                        beq #0x80cee84                            <- missing from compiled
                                        adds r2, #1                               <- missing from compiled
                                        adds r1, #0xc                             <- missing from compiled
                                        cmp r2, #0x3f                             <- missing from compiled
                                        ble #0x80cee74                            <- missing from compiled
                                        str r0, [r1, #4]                          <- missing from compiled
                                        ldr r0, [r2]                              <- missing from compiled
                                        str r0, [r1, #8]                          <- missing from compiled
                                        ldr r0, [r2]                              <- missing from compiled
                                        str r1, [r0, #4]                          <- missing from compiled
                                        str r1, [r2]                              <- missing from compiled
                                        b #0x80ceec4                              <- missing from compiled
                                        movs r0, r0                               <- missing from compiled
                                        bmi #0x80cee18                            <- missing from compiled
                                        lsrs r6, r6, #0x20                        <- missing from compiled
                                        movs r1, #0xc8                            <- missing from compiled
                                        lsls r0, r0, #8                           <- missing from compiled
                                        bmi #0x80cee28                            <- missing from compiled
                                        lsrs r6, r6, #0x20                        <- missing from compiled
                                        movs r5, #0xc8                            <- missing from compiled
                                        lsls r0, r0, #8                           <- missing from compiled
                                        movs r0, r0                               <- missing from compiled
                                        lsls r0, r0, #8                           <- missing from compiled
                                        cmp r0, #0xc8                             <- missing from compiled
                                        movs r0, r0                               <- missing from compiled
                                        str r1, [r2]                              <- missing from compiled
                                        str r4, [r1]                              <- missing from compiled
                                        str r0, [r1, #8]                          <- missing from compiled
                                        push {r4, r5, lr}                         <- missing from compiled
                                        lsls r0, r0, #0x10                        <- missing from compiled
                                        lsrs r5, r0, #0x10                        <- missing from compiled
                                        adds r0, r5, #0                           <- missing from compiled
                                        movs r1, #0x2a                            <- missing from compiled
                                        lsls r0, r0, #0x10                        <- missing from compiled
```
