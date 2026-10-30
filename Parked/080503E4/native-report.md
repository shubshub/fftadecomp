# match report - 0x080503E4

* source: `src/080503E4.c`
* verification: `elf-symbol-thumb-data-v1`
* source SHA-256: `ed77592e93a962206e0cda5d8f9921dfde9d577b7bdefc683392cac570ca6cbe`
* mapping SHA-256: `ad36cd9cd48a87bef77aefc8db37f79d1d8a96186ab74f4cf467a5ba0ca2e016`
* control flow: direct Thumb BL with ordinary ARM ABI call summaries
* data symbols SHA-256: `1f9c81831c41751df523547564a4547d7cebeb2b42bc86a401e2560c101843b1`
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `70b5051c2e1c4836fff736fe281cfff75dfe301cfff7b2fc281cfff7e5feb068041c2a3425492e30018001390238a042fada142001212022c5f7c0fe0004c00bb1680c182868ac21c900401801780131201cfff775fc04341949081c208002342868184940180178201cfff769fc281c9c3015492b68154c1a1912785201103201341b191b785b058824e4031b191b14c7f798fd281cac300d49d4221823c7f791fd281cbc300b491c221823c7f78afd0120e87270bc01bc0047000087c0ffff88c000006105000052ba510862050000be373908c6373908` (216 bytes)
* compiled : `70b5051c2e1c4836fff736fe281cfff75dfe301cfff7b2fc281cfff7e5feb068031c2a33254a041c2e342280013a023c9c42fad2142001212022c5f7bffe0004c00bb1680c182868ac21c900401801780131201cfff774fc04341949081c208002342868174940180178201cfff768fc281c9c3014492b68144c1a1912785201103201341b191b785b058824e4031b191b0cc7f797fd281cac300d49d4221823c7f790fd281cbc300a491c221823c7f789fd0120e87270bc01bc004787c0ffff88c000006105000052ba510862050000be373908c6373908`
* source plausibility: plausible
* hand-asm allow list: not listed

**NOT MATCHING - bytes differ** - 194/216 bytes

```
compiled                                rom
push {r4, r5, r6, lr}                   push {r4, r5, r6, lr}
adds r5, r0, #0                         adds r5, r0, #0
adds r6, r5, #0                         adds r6, r5, #0
adds r6, #0x48                          adds r6, #0x48
bl #0x805005c                           bl #0x805005c
adds r0, r5, #0                         adds r0, r5, #0
bl #0x80500b0                           bl #0x80500b0
adds r0, r6, #0                         adds r0, r6, #0
bl #0x804fd60                           bl #0x804fd60
adds r0, r5, #0                         adds r0, r5, #0
bl #0x80501cc                           bl #0x80501cc
ldr r0, [r6, #8]                        ldr r0, [r6, #8]
adds r3, r0, #0                                                                   <- extra in compiled
adds r3, #0x2a                                                                    <- extra in compiled
ldr r2, [pc, #0x94]                                                               <- extra in compiled
adds r4, r0, #0                         adds r4, r0, #0
adds r4, #0x2e                                                                    <- extra in compiled
strh r2, [r4]                                                                     <- extra in compiled
subs r2, #1                                                                       <- extra in compiled
subs r4, #2                                                                       <- extra in compiled
cmp r4, r3                                                                        <- extra in compiled
bhs #0x805040e                                                                    <- extra in compiled
                                        adds r4, #0x2a                            <- missing from compiled
                                        ldr r1, [pc, #0x94]                       <- missing from compiled
                                        adds r0, #0x2e                            <- missing from compiled
                                        strh r1, [r0]                             <- missing from compiled
                                        subs r1, #1                               <- missing from compiled
                                        subs r0, #2                               <- missing from compiled
                                        cmp r0, r4                                <- missing from compiled
                                        bge #0x805040c                            <- missing from compiled
movs r0, #0x14                          movs r0, #0x14
movs r1, #1                             movs r1, #1
movs r2, #0x20                          movs r2, #0x20
bl #0x80161a0                                                                     <- extra in compiled
lsls r0, r0, #0x10                                                                <- extra in compiled
                                        cdp2 p4, #0xc, c0, c0, c0, #0             <- missing from compiled
lsrs r0, r0, #0xf                       lsrs r0, r0, #0xf
ldr r1, [r6, #8]                        ldr r1, [r6, #8]
adds r4, r1, r0                         adds r4, r1, r0
ldr r0, [r5]                            ldr r0, [r5]
movs r1, #0xac                          movs r1, #0xac
lsls r1, r1, #3                         lsls r1, r1, #3
adds r0, r0, r1                         adds r0, r0, r1
ldrb r1, [r0]                           ldrb r1, [r0]
adds r1, #1                             adds r1, #1
adds r0, r4, #0                         adds r0, r4, #0
bl #0x804fd24                                                                     <- extra in compiled
adds r4, #4                                                                       <- extra in compiled
                                        ldc2l p4, c3, [r5], #-0x10                <- missing from compiled
ldr r1, [pc, #0x64]                     ldr r1, [pc, #0x64]
adds r0, r1, #0                         adds r0, r1, #0
strh r0, [r4]                           strh r0, [r4]
adds r4, #2                             adds r4, #2
ldr r0, [r5]                            ldr r0, [r5]
ldr r1, [pc, #0x5c]                                                               <- extra in compiled
                                        ldr r1, [pc, #0x60]                       <- missing from compiled
adds r0, r0, r1                         adds r0, r0, r1
ldrb r1, [r0]                           ldrb r1, [r0]
adds r0, r4, #0                         adds r0, r4, #0
bl #0x804fd24                                                                     <- extra in compiled
adds r0, r5, #0                                                                   <- extra in compiled
                                        stc2l p12, c1, [sb], #-0xa0               <- missing from compiled
adds r0, #0x9c                          adds r0, #0x9c
ldr r1, [pc, #0x50]                                                               <- extra in compiled
                                        ldr r1, [pc, #0x54]                       <- missing from compiled
ldr r3, [r5]                            ldr r3, [r5]
ldr r4, [pc, #0x50]                                                               <- extra in compiled
                                        ldr r4, [pc, #0x54]                       <- missing from compiled
adds r2, r3, r4                         adds r2, r3, r4
ldrb r2, [r2]                           ldrb r2, [r2]
lsls r2, r2, #5                         lsls r2, r2, #5
adds r2, #0x10                          adds r2, #0x10
adds r4, #1                             adds r4, #1
adds r3, r3, r4                         adds r3, r3, r4
ldrb r3, [r3]                           ldrb r3, [r3]
lsls r3, r3, #0x15                      lsls r3, r3, #0x15
movs r4, #0x88                          movs r4, #0x88
lsls r4, r4, #0xf                       lsls r4, r4, #0xf
adds r3, r3, r4                         adds r3, r3, r4
lsrs r3, r3, #0x10                                                                <- extra in compiled
bl #0x8017fa8                                                                     <- extra in compiled
adds r0, r5, #0                                                                   <- extra in compiled
                                        asrs r3, r3, #0x10                        <- missing from compiled
                                        ldc2 p12, c1, [r8, #0xa0]                 <- missing from compiled
adds r0, #0xac                          adds r0, #0xac
ldr r1, [pc, #0x34]                     ldr r1, [pc, #0x34]
movs r2, #0xd4                          movs r2, #0xd4
movs r3, #0x18                          movs r3, #0x18
bl #0x8017fa8                                                                     <- extra in compiled
adds r0, r5, #0                                                                   <- extra in compiled
                                        ldc2 p12, c1, [r1, #0xa0]                 <- missing from compiled
adds r0, #0xbc                          adds r0, #0xbc
ldr r1, [pc, #0x28]                                                               <- extra in compiled
                                        ldr r1, [pc, #0x2c]                       <- missing from compiled
movs r2, #0x1c                          movs r2, #0x1c
movs r3, #0x18                          movs r3, #0x18
bl #0x8017fa8                                                                     <- extra in compiled
movs r0, #1                                                                       <- extra in compiled
                                        stc2 p0, c2, [sl, #4]                     <- missing from compiled
strb r0, [r5, #0xb]                     strb r0, [r5, #0xb]
pop {r4, r5, r6}                        pop {r4, r5, r6}
pop {r0}                                pop {r0}
bx r0                                   bx r0
                                        movs r0, r0                               <- missing from compiled
```
