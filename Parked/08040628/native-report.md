# match report - 0x08040628

* source: `src/08040628.c`
* verification: `elf-symbol-thumb-frame-data-v1`
* source SHA-256: `26617162d49b09edf6b60921089d97bc14bb14fd1d1c3091d95b78e860867a8f`
* stack frame: fixed Thumb frames and bounded stack aliases with return provenance
* mapping SHA-256: `ad36cd9cd48a87bef77aefc8db37f79d1d8a96186ab74f4cf467a5ba0ca2e016`
* control flow: direct Thumb BL with ordinary ARM ABI call summaries
* data symbols SHA-256: `5b424ed1a4737abc4d79aacb62cdf5b3a6637045a77383c11ecdd3a122088683`
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `f0b5474680b48bb0884611991b061b0e09060d0e08a90c32d0cad0c11f4e3168cc22041c544309191d4809180f88ff2b02d008a8037045700125326819495018001901689826360192191219126808a803784078009008a88078019008a8c078029008a8008903900f4c4c20784300192830007804900520059006950c2007904046d6f7bbfe08a8817a4046d6f7ecfa0bb008bc9846f0bc01bc0047102800038409000068090000e0090003` (172 bytes)
* compiled : `f0b5474680b48bb0884611991b061b0e09060d0e08a90c32d0cad0c11f4e3168cc22041c544309191d4809180f88ff2b02d008a80370457032681a495018001901689826360192191219126808a803784078009008a88078019008a8c078029008a800890390104c4c207843001928300078049005200590012006900c2007904046d6f7bbfe08a8817a4046d6f7ecfa0bb008bc9846f0bc01bc0047102800038409000068090000e0090003`
* source plausibility: plausible
* hand-asm allow list: not listed

**NOT MATCHING - bytes differ** - 167/172 bytes

```
compiled                                rom
push {r4, r5, r6, r7, lr}               push {r4, r5, r6, r7, lr}
mov r7, r8                              mov r7, r8
push {r7}                               push {r7}
sub sp, #0x2c                           sub sp, #0x2c
mov r8, r1                              mov r8, r1
ldr r1, [sp, #0x44]                     ldr r1, [sp, #0x44]
lsls r3, r3, #0x18                      lsls r3, r3, #0x18
lsrs r3, r3, #0x18                      lsrs r3, r3, #0x18
lsls r1, r1, #0x18                      lsls r1, r1, #0x18
lsrs r5, r1, #0x18                      lsrs r5, r1, #0x18
add r1, sp, #0x20                       add r1, sp, #0x20
adds r2, #0xc                           adds r2, #0xc
ldm r2!, {r4, r6, r7}                   ldm r2!, {r4, r6, r7}
stm r1!, {r4, r6, r7}                   stm r1!, {r4, r6, r7}
ldr r6, [pc, #0x7c]                     ldr r6, [pc, #0x7c]
ldr r1, [r6]                            ldr r1, [r6]
movs r2, #0xcc                          movs r2, #0xcc
adds r4, r0, #0                         adds r4, r0, #0
muls r4, r2, r4                         muls r4, r2, r4
adds r1, r1, r4                         adds r1, r1, r4
ldr r0, [pc, #0x74]                     ldr r0, [pc, #0x74]
adds r1, r1, r0                         adds r1, r1, r0
ldrh r7, [r1]                           ldrh r7, [r1]
cmp r3, #0xff                           cmp r3, #0xff
beq #0x8040660                          beq #0x8040660
add r0, sp, #0x20                       add r0, sp, #0x20
strb r3, [r0]                           strb r3, [r0]
strb r5, [r0, #1]                       strb r5, [r0, #1]
                                        movs r5, #1                               <- missing from compiled
ldr r2, [r6]                            ldr r2, [r6]
ldr r1, [pc, #0x68]                                                               <- extra in compiled
                                        ldr r1, [pc, #0x64]                       <- missing from compiled
adds r0, r2, r1                         adds r0, r2, r1
adds r0, r0, r4                         adds r0, r0, r4
ldr r1, [r0]                            ldr r1, [r0]
movs r6, #0x98                          movs r6, #0x98
lsls r6, r6, #4                         lsls r6, r6, #4
adds r2, r2, r6                         adds r2, r2, r6
adds r2, r2, r4                         adds r2, r2, r4
ldr r2, [r2]                            ldr r2, [r2]
add r0, sp, #0x20                       add r0, sp, #0x20
ldrb r3, [r0]                           ldrb r3, [r0]
ldrb r0, [r0, #1]                       ldrb r0, [r0, #1]
str r0, [sp]                            str r0, [sp]
add r0, sp, #0x20                       add r0, sp, #0x20
ldrb r0, [r0, #2]                       ldrb r0, [r0, #2]
str r0, [sp, #4]                        str r0, [sp, #4]
add r0, sp, #0x20                       add r0, sp, #0x20
ldrb r0, [r0, #3]                       ldrb r0, [r0, #3]
str r0, [sp, #8]                        str r0, [sp, #8]
add r0, sp, #0x20                       add r0, sp, #0x20
ldrh r0, [r0, #8]                       ldrh r0, [r0, #8]
str r0, [sp, #0xc]                      str r0, [sp, #0xc]
ldr r4, [pc, #0x40]                                                               <- extra in compiled
                                        ldr r4, [pc, #0x3c]                       <- missing from compiled
movs r0, #0x4c                          movs r0, #0x4c
muls r0, r7, r0                         muls r0, r7, r0
adds r0, r0, r4                         adds r0, r0, r4
adds r0, #0x28                          adds r0, #0x28
ldrb r0, [r0]                           ldrb r0, [r0]
str r0, [sp, #0x10]                     str r0, [sp, #0x10]
movs r0, #5                             movs r0, #5
str r0, [sp, #0x14]                     str r0, [sp, #0x14]
movs r0, #1                                                                       <- extra in compiled
str r0, [sp, #0x18]                                                               <- extra in compiled
                                        str r5, [sp, #0x18]                       <- missing from compiled
movs r0, #0xc                           movs r0, #0xc
str r0, [sp, #0x1c]                     str r0, [sp, #0x1c]
mov r0, r8                              mov r0, r8
bl #0x8017424                           bl #0x8017424
add r0, sp, #0x20                       add r0, sp, #0x20
ldrb r1, [r0, #0xa]                     ldrb r1, [r0, #0xa]
mov r0, r8                              mov r0, r8
bl #0x8016c90                           bl #0x8016c90
add sp, #0x2c                           add sp, #0x2c
pop {r3}                                pop {r3}
mov r8, r3                              mov r8, r3
pop {r4, r5, r6, r7}                    pop {r4, r5, r6, r7}
pop {r0}                                pop {r0}
bx r0                                   bx r0
```
