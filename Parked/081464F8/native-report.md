# match report - 0x081464F8

* source: `src/081464F8.c`
* verification: `elf-symbol-cfg-leaf-v2`
* source SHA-256: `520a56cc6c91ddb11212e6f86678990fe874d1a37a5a8f5be2299bf4838e4c77`
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `10b50a6c0c48044010780443507803020a4804401c4390780304094804401c43d0780306074804401c438c6204320a6410bc01bc0047000000ffffffff00ffffffff00ffffffff00` (72 bytes)
* compiled : `10b50b6c1a780c4804401443587800020a4a1440044398780004094a14400443d8780006074a144004438c6204330b6410bc01bc0047000000ffffffff00ffffffff00ffffffff00`
* source plausibility: plausible
* hand-asm allow list: not listed

**NOT MATCHING - bytes differ** - 51/72 bytes

```
compiled                                rom
push {r4, lr}                           push {r4, lr}
ldr r3, [r1, #0x40]                                                               <- extra in compiled
ldrb r2, [r3]                                                                     <- extra in compiled
                                        ldr r2, [r1, #0x40]                       <- missing from compiled
ldr r0, [pc, #0x30]                     ldr r0, [pc, #0x30]
ands r4, r0                             ands r4, r0
orrs r4, r2                                                                       <- extra in compiled
ldrb r0, [r3, #1]                                                                 <- extra in compiled
lsls r0, r0, #8                                                                   <- extra in compiled
ldr r2, [pc, #0x28]                                                               <- extra in compiled
ands r4, r2                                                                       <- extra in compiled
orrs r4, r0                                                                       <- extra in compiled
ldrb r0, [r3, #2]                                                                 <- extra in compiled
lsls r0, r0, #0x10                                                                <- extra in compiled
ldr r2, [pc, #0x24]                                                               <- extra in compiled
ands r4, r2                                                                       <- extra in compiled
orrs r4, r0                                                                       <- extra in compiled
ldrb r0, [r3, #3]                                                                 <- extra in compiled
lsls r0, r0, #0x18                                                                <- extra in compiled
ldr r2, [pc, #0x1c]                                                               <- extra in compiled
ands r4, r2                                                                       <- extra in compiled
                                        ldrb r0, [r2]                             <- missing from compiled
orrs r4, r0                             orrs r4, r0
                                        ldrb r0, [r2, #1]                         <- missing from compiled
                                        lsls r3, r0, #8                           <- missing from compiled
                                        ldr r0, [pc, #0x28]                       <- missing from compiled
                                        ands r4, r0                               <- missing from compiled
                                        orrs r4, r3                               <- missing from compiled
                                        ldrb r0, [r2, #2]                         <- missing from compiled
                                        lsls r3, r0, #0x10                        <- missing from compiled
                                        ldr r0, [pc, #0x24]                       <- missing from compiled
                                        ands r4, r0                               <- missing from compiled
                                        orrs r4, r3                               <- missing from compiled
                                        ldrb r0, [r2, #3]                         <- missing from compiled
                                        lsls r3, r0, #0x18                        <- missing from compiled
                                        ldr r0, [pc, #0x1c]                       <- missing from compiled
                                        ands r4, r0                               <- missing from compiled
                                        orrs r4, r3                               <- missing from compiled
str r4, [r1, #0x28]                     str r4, [r1, #0x28]
adds r3, #4                                                                       <- extra in compiled
str r3, [r1, #0x40]                                                               <- extra in compiled
                                        adds r2, #4                               <- missing from compiled
                                        str r2, [r1, #0x40]                       <- missing from compiled
pop {r4}                                pop {r4}
pop {r0}                                pop {r0}
bx r0                                   bx r0
```
