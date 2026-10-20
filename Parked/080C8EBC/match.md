# match report - 0x080C8EBC

* source: `src/080C8EBC.c`
* verification: `elf-symbol-thumb-frame-calls-v1`
* source SHA-256: `0a594e6a3d5da2d32a81abe85485b66a12c6bab2bd1748456ca38c1bc386c16b`
* stack frame: fixed Thumb frames and bounded stack aliases with return provenance
* mapping SHA-256: `77f92740d2e2c569399298dbfeef8b43bce06e3967b02847ea0f6fa81d7a837b`
* control flow: direct Thumb BL with ordinary ARM ABI call summaries
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `f0b557464e464546e0b481b0071c8a465646fff7b7f9000600281ad1381cfff7c1f90006002814d1381c0a21fff754f9000600280dd1381c0921fff74df90006002806d1381c5e21fff746f90006002867d0381c0321fef7c7ff0006000e0090381cfff79ff9000600281dd1381cfff789f90006002817d1381c0a21fff72cf9000600280dd1381c0921fff725f90006002806d1381c5e21fff71ef90006002802d00120307001360124381c343081460078844275da5146751a381c403000190078631c9846002825d02104090c009800f0a0fa011c0906090e081c0c22fff7e9fa0006020e002a15d001240021ac46a9420bd25346187805e00131614505d25346581800789042f7d10024012c02d13270013501364446484600788442ccdb3fe005240f218846381c0321fef75cff03280cd0032802d8022805d012e0042809d005280bd00de01024162309e017241e20804606e01f242621884602e027242e239846381cfff701f90006002802d1012030700136e51e444512dc2004000c00f080fa0006002807d02906090e081c0c22fff78ffa30700136013401354445ecdd5146701a0006000e01b038bc9846a146aa46f0bc02bc08470000f0b5474680b4` (450 bytes)
* compiled : `f0b557464e464546e0b481b0071c8a465646fff7b7f9000600281ad1381cfff7c1f90006002814d1381c0a21fff754f9000600280dd1381c0921fff74df90006002806d1381c5e21fff746f90006002866d0381c0321fef7c7ff0006000e0090381cfff79ff9000600281dd1381cfff789f90006002817d1381c0a21fff72cf9000600280dd1381c0921fff725f90006002806d1381c5e21fff71ef90006002802d00120307001360121381c343081460078814279da5246b51ac819403000784b1c9846002825d00904090c009800f0a1fa011c0906090e081c0c22fff7eafa0006020e002a15d001240021ac46a9420bd25346187805e00131614505d25346581800789042f7d10024012c02d13270013501364146484600788142cddb44e005250f218846381c0321fef75dff03280dd0032802d8022805d013e004280ad005280cd00ee01025162290460ae017251e23984606e01f252620804602e027252e218846381cfff701f90006002802d1012030700136454517dc2806fd22120684182804000c00f07dfa0006002806d0210e081c0c22fff78dfa3070013680235b04e41801354545ebdd5146701a0006000e01b038bc9846a146aa46f0bc02bc0847`
* source plausibility: plausible
* hand-asm allow list: not listed

**NOT MATCHING - bytes differ** - 390/450 bytes

```
compiled                                rom
push {r4, r5, r6, r7, lr}               push {r4, r5, r6, r7, lr}
mov r7, sl                              mov r7, sl
mov r6, sb                              mov r6, sb
mov r5, r8                              mov r5, r8
push {r5, r6, r7}                       push {r5, r6, r7}
sub sp, #4                              sub sp, #4
adds r7, r0, #0                         adds r7, r0, #0
mov sl, r1                              mov sl, r1
mov r6, sl                              mov r6, sl
bl #0x80c8240                           bl #0x80c8240
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
cmp r0, #0                              cmp r0, #0
bne #0x80c8f0e                          bne #0x80c8f0e
adds r0, r7, #0                         adds r0, r7, #0
bl #0x80c8260                           bl #0x80c8260
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
cmp r0, #0                              cmp r0, #0
bne #0x80c8f0e                          bne #0x80c8f0e
adds r0, r7, #0                         adds r0, r7, #0
movs r1, #0xa                           movs r1, #0xa
bl #0x80c8194                           bl #0x80c8194
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
cmp r0, #0                              cmp r0, #0
bne #0x80c8f0e                          bne #0x80c8f0e
adds r0, r7, #0                         adds r0, r7, #0
movs r1, #9                             movs r1, #9
bl #0x80c8194                           bl #0x80c8194
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
cmp r0, #0                              cmp r0, #0
bne #0x80c8f0e                          bne #0x80c8f0e
adds r0, r7, #0                         adds r0, r7, #0
movs r1, #0x5e                          movs r1, #0x5e
bl #0x80c8194                           bl #0x80c8194
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
cmp r0, #0                              cmp r0, #0
beq #0x80c8fdc                                                                    <- extra in compiled
                                        beq #0x80c8fde                            <- missing from compiled
adds r0, r7, #0                         adds r0, r7, #0
movs r1, #3                             movs r1, #3
bl #0x80c7ea4                           bl #0x80c7ea4
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
lsrs r0, r0, #0x18                      lsrs r0, r0, #0x18
str r0, [sp]                            str r0, [sp]
adds r0, r7, #0                         adds r0, r7, #0
bl #0x80c8260                           bl #0x80c8260
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
cmp r0, #0                              cmp r0, #0
bne #0x80c8f64                          bne #0x80c8f64
adds r0, r7, #0                         adds r0, r7, #0
bl #0x80c8240                           bl #0x80c8240
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
cmp r0, #0                              cmp r0, #0
bne #0x80c8f64                          bne #0x80c8f64
adds r0, r7, #0                         adds r0, r7, #0
movs r1, #0xa                           movs r1, #0xa
bl #0x80c8194                           bl #0x80c8194
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
cmp r0, #0                              cmp r0, #0
bne #0x80c8f5e                          bne #0x80c8f5e
adds r0, r7, #0                         adds r0, r7, #0
movs r1, #9                             movs r1, #9
bl #0x80c8194                           bl #0x80c8194
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
cmp r0, #0                              cmp r0, #0
bne #0x80c8f5e                          bne #0x80c8f5e
adds r0, r7, #0                         adds r0, r7, #0
movs r1, #0x5e                          movs r1, #0x5e
bl #0x80c8194                           bl #0x80c8194
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
cmp r0, #0                              cmp r0, #0
beq #0x80c8f64                          beq #0x80c8f64
movs r0, #1                             movs r0, #1
strb r0, [r6]                           strb r0, [r6]
adds r6, #1                             adds r6, #1
movs r1, #1                                                                       <- extra in compiled
                                        movs r4, #1                               <- missing from compiled
adds r0, r7, #0                         adds r0, r7, #0
adds r0, #0x34                          adds r0, #0x34
mov sb, r0                              mov sb, r0
ldrb r0, [r0]                           ldrb r0, [r0]
cmp r1, r0                                                                        <- extra in compiled
bge #0x80c9066                                                                    <- extra in compiled
mov r2, sl                                                                        <- extra in compiled
subs r5, r6, r2                                                                   <- extra in compiled
adds r0, r1, r7                                                                   <- extra in compiled
                                        cmp r4, r0                                <- missing from compiled
                                        bge #0x80c905e                            <- missing from compiled
                                        mov r1, sl                                <- missing from compiled
                                        subs r5, r6, r1                           <- missing from compiled
                                        adds r0, r7, #0                           <- missing from compiled
adds r0, #0x40                          adds r0, #0x40
                                        adds r0, r0, r4                           <- missing from compiled
ldrb r0, [r0]                           ldrb r0, [r0]
adds r3, r1, #1                                                                   <- extra in compiled
                                        adds r3, r4, #1                           <- missing from compiled
mov r8, r3                              mov r8, r3
cmp r0, #0                              cmp r0, #0
beq #0x80c8fd0                                                                    <- extra in compiled
lsls r1, r1, #0x10                                                                <- extra in compiled
                                        beq #0x80c8fd2                            <- missing from compiled
                                        lsls r1, r4, #0x10                        <- missing from compiled
lsrs r1, r1, #0x10                      lsrs r1, r1, #0x10
ldr r0, [sp]                            ldr r0, [sp]
bl #0x80c94d0                                                                     <- extra in compiled
adds r1, r0, #0                         adds r1, r0, #0
lsls r1, r1, #0x18                      lsls r1, r1, #0x18
lsrs r1, r1, #0x18                      lsrs r1, r1, #0x18
adds r0, r1, #0                         adds r0, r1, #0
movs r2, #0xc                           movs r2, #0xc
bl #0x80c8570                                                                     <- extra in compiled
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
lsrs r2, r0, #0x18                      lsrs r2, r0, #0x18
cmp r2, #0                              cmp r2, #0
beq #0x80c8fd0                                                                    <- extra in compiled
                                        beq #0x80c8fd2                            <- missing from compiled
movs r4, #1                             movs r4, #1
movs r1, #0                             movs r1, #0
mov ip, r5                              mov ip, r5
cmp r1, r5                              cmp r1, r5
bhs #0x80c8fc6                                                                    <- extra in compiled
                                        bhs #0x80c8fc8                            <- missing from compiled
mov r3, sl                              mov r3, sl
ldrb r0, [r3]                           ldrb r0, [r3]
b #0x80c8fc0                                                                      <- extra in compiled
                                        b #0x80c8fc2                              <- missing from compiled
adds r1, #1                             adds r1, #1
cmp r1, ip                              cmp r1, ip
bhs #0x80c8fc6                                                                    <- extra in compiled
                                        bhs #0x80c8fc8                            <- missing from compiled
mov r3, sl                              mov r3, sl
adds r0, r3, r1                         adds r0, r3, r1
ldrb r0, [r0]                           ldrb r0, [r0]
cmp r0, r2                              cmp r0, r2
bne #0x80c8fb4                                                                    <- extra in compiled
                                        bne #0x80c8fb6                            <- missing from compiled
movs r4, #0                             movs r4, #0
cmp r4, #1                              cmp r4, #1
bne #0x80c8fd0                                                                    <- extra in compiled
                                        bne #0x80c8fd2                            <- missing from compiled
strb r2, [r6]                           strb r2, [r6]
adds r5, #1                             adds r5, #1
adds r6, #1                             adds r6, #1
mov r1, r8                                                                        <- extra in compiled
                                        mov r4, r8                                <- missing from compiled
mov r0, sb                              mov r0, sb
ldrb r0, [r0]                           ldrb r0, [r0]
cmp r1, r0                                                                        <- extra in compiled
                                        cmp r4, r0                                <- missing from compiled
blt #0x80c8f76                          blt #0x80c8f76
b #0x80c9066                                                                      <- extra in compiled
movs r5, #5                                                                       <- extra in compiled
                                        b #0x80c905e                              <- missing from compiled
                                        movs r4, #5                               <- missing from compiled
movs r1, #0xf                           movs r1, #0xf
mov r8, r1                              mov r8, r1
adds r0, r7, #0                         adds r0, r7, #0
movs r1, #3                             movs r1, #3
bl #0x80c7ea4                                                                     <- extra in compiled
cmp r0, #3                              cmp r0, #3
beq #0x80c900a                          beq #0x80c900a
cmp r0, #3                              cmp r0, #3
bhi #0x80c8ff8                                                                    <- extra in compiled
                                        bhi #0x80c8ffa                            <- missing from compiled
cmp r0, #2                              cmp r0, #2
beq #0x80c9002                                                                    <- extra in compiled
                                        beq #0x80c9004                            <- missing from compiled
b #0x80c9020                            b #0x80c9020
cmp r0, #4                              cmp r0, #4
beq #0x80c9012                          beq #0x80c9012
cmp r0, #5                              cmp r0, #5
beq #0x80c901a                          beq #0x80c901a
b #0x80c9020                            b #0x80c9020
movs r5, #0x10                                                                    <- extra in compiled
movs r2, #0x16                                                                    <- extra in compiled
mov r8, r2                                                                        <- extra in compiled
b #0x80c9020                                                                      <- extra in compiled
movs r5, #0x17                                                                    <- extra in compiled
movs r3, #0x1e                                                                    <- extra in compiled
mov r8, r3                                                                        <- extra in compiled
b #0x80c9020                                                                      <- extra in compiled
movs r5, #0x1f                                                                    <- extra in compiled
movs r0, #0x26                                                                    <- extra in compiled
                                        movs r4, #0x10                            <- missing from compiled
                                        movs r3, #0x16                            <- missing from compiled
                                        b #0x80c901e                              <- missing from compiled
                                        movs r4, #0x17                            <- missing from compiled
                                        movs r0, #0x1e                            <- missing from compiled
mov r8, r0                              mov r8, r0
b #0x80c9020                            b #0x80c9020
movs r5, #0x27                                                                    <- extra in compiled
movs r1, #0x2e                                                                    <- extra in compiled
                                        movs r4, #0x1f                            <- missing from compiled
                                        movs r1, #0x26                            <- missing from compiled
mov r8, r1                              mov r8, r1
                                        b #0x80c9020                              <- missing from compiled
                                        movs r4, #0x27                            <- missing from compiled
                                        movs r3, #0x2e                            <- missing from compiled
                                        mov r8, r3                                <- missing from compiled
adds r0, r7, #0                         adds r0, r7, #0
bl #0x80c8228                           bl #0x80c8228
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
cmp r0, #0                              cmp r0, #0
bne #0x80c9032                          bne #0x80c9032
movs r0, #1                             movs r0, #1
strb r0, [r6]                           strb r0, [r6]
adds r6, #1                             adds r6, #1
cmp r5, r8                                                                        <- extra in compiled
bgt #0x80c9066                                                                    <- extra in compiled
lsls r0, r5, #0x18                                                                <- extra in compiled
movs r2, #0xfd                                                                    <- extra in compiled
lsls r2, r2, #0x18                                                                <- extra in compiled
adds r4, r0, r2                                                                   <- extra in compiled
lsls r0, r5, #0x10                                                                <- extra in compiled
                                        subs r5, r4, #3                           <- missing from compiled
                                        cmp r4, r8                                <- missing from compiled
                                        bgt #0x80c905e                            <- missing from compiled
                                        lsls r0, r4, #0x10                        <- missing from compiled
lsrs r0, r0, #0x10                      lsrs r0, r0, #0x10
bl #0x80c9540                                                                     <- extra in compiled
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
cmp r0, #0                              cmp r0, #0
beq #0x80c905a                                                                    <- extra in compiled
lsrs r1, r4, #0x18                                                                <- extra in compiled
                                        beq #0x80c9056                            <- missing from compiled
                                        lsls r1, r5, #0x18                        <- missing from compiled
                                        lsrs r1, r1, #0x18                        <- missing from compiled
adds r0, r1, #0                         adds r0, r1, #0
movs r2, #0xc                           movs r2, #0xc
bl #0x80c8570                                                                     <- extra in compiled
strb r0, [r6]                           strb r0, [r6]
adds r6, #1                             adds r6, #1
movs r3, #0x80                                                                    <- extra in compiled
lsls r3, r3, #0x11                                                                <- extra in compiled
adds r4, r4, r3                                                                   <- extra in compiled
                                        adds r4, #1                               <- missing from compiled
adds r5, #1                             adds r5, #1
cmp r5, r8                                                                        <- extra in compiled
ble #0x80c903e                                                                    <- extra in compiled
                                        cmp r4, r8                                <- missing from compiled
                                        ble #0x80c9038                            <- missing from compiled
mov r1, sl                              mov r1, sl
subs r0, r6, r1                         subs r0, r6, r1
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
lsrs r0, r0, #0x18                      lsrs r0, r0, #0x18
add sp, #4                              add sp, #4
pop {r3, r4, r5}                        pop {r3, r4, r5}
mov r8, r3                              mov r8, r3
mov sb, r4                              mov sb, r4
mov sl, r5                              mov sl, r5
pop {r4, r5, r6, r7}                    pop {r4, r5, r6, r7}
pop {r1}                                pop {r1}
bx r1                                   bx r1
                                        movs r0, r0                               <- missing from compiled
                                        push {r4, r5, r6, r7, lr}                 <- missing from compiled
                                        mov r7, r8                                <- missing from compiled
                                        push {r7}                                 <- missing from compiled
```
