# match report - 0x080CCF44

* source: `src/080CCF44.c`
* verification: `elf-symbol-thumb-data-v1`
* source SHA-256: `541be7af0b56b96693b1f93bae2262ed5addce99566a2f54d3594cb436705989`
* mapping SHA-256: `c57511fb680b186833bda5c321aa1ef2b13f8ab9036d6ac0755ac0f5309b4b38`
* control flow: direct Thumb BL with ordinary ARM ABI call summaries
* data symbols SHA-256: `5510d2c9d4b144b6040e8dbfc4cbe1f4c46853622faf8e4b925fce069935ead5`
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `f0b5051c0904080c002830d01221fdf727fc8100091889000e480f1800263878864224dafc1c7000b91c0918e8790978884211d12178002d06d0281c4030401802788021114301702178281c00f046fb08e0000080005208ff2903d12078291c3d3108700234013638788642dbdbf0bc01bc0047` (116 bytes)
* compiled : `f0b50904090c051c002930d0081c1221fdf726fc8100091889000e480f1800263878864223dafc1c7000b91c0918e8790978884210d12178002d06d0281c4030401801788022114301702178281c00f045fb07e080005208ff2903d12078291c3d3108700234013638788642dcdbf0bc01bc0047`
* source plausibility: plausible
* hand-asm allow list: not listed

**NOT MATCHING - bytes differ** - 102/116 bytes

```
compiled                                rom
push {r4, r5, r6, r7, lr}               push {r4, r5, r6, r7, lr}
lsls r1, r1, #0x10                                                                <- extra in compiled
lsrs r1, r1, #0x10                                                                <- extra in compiled
adds r5, r0, #0                         adds r5, r0, #0
cmp r1, #0                                                                        <- extra in compiled
                                        lsls r1, r1, #0x10                        <- missing from compiled
                                        lsrs r0, r1, #0x10                        <- missing from compiled
                                        cmp r0, #0                                <- missing from compiled
beq #0x80ccfb2                          beq #0x80ccfb2
adds r0, r1, #0                                                                   <- extra in compiled
movs r1, #0x12                          movs r1, #0x12
bl #0x80ca7a4                                                                     <- extra in compiled
lsls r1, r0, #2                                                                   <- extra in compiled
                                        stc2 p0, c0, [r7], #-0x204                <- missing from compiled
adds r1, r1, r0                         adds r1, r1, r0
lsls r1, r1, #2                         lsls r1, r1, #2
ldr r0, [pc, #0x38]                     ldr r0, [pc, #0x38]
adds r7, r1, r0                         adds r7, r1, r0
movs r6, #0                             movs r6, #0
ldrb r0, [r7]                           ldrb r0, [r7]
cmp r6, r0                              cmp r6, r0
bge #0x80ccfb2                          bge #0x80ccfb2
adds r4, r7, #3                         adds r4, r7, #3
lsls r0, r6, #1                         lsls r0, r6, #1
adds r1, r7, #2                         adds r1, r7, #2
adds r1, r1, r0                         adds r1, r1, r0
ldrb r0, [r5, #7]                       ldrb r0, [r5, #7]
ldrb r1, [r1]                           ldrb r1, [r1]
cmp r0, r1                              cmp r0, r1
bne #0x80ccf9c                          bne #0x80ccf9c
ldrb r1, [r4]                           ldrb r1, [r4]
cmp r5, #0                              cmp r5, #0
beq #0x80ccf8e                                                                    <- extra in compiled
                                        beq #0x80ccf8c                            <- missing from compiled
adds r0, r5, #0                         adds r0, r5, #0
adds r0, #0x40                          adds r0, #0x40
adds r0, r0, r1                         adds r0, r0, r1
ldrb r1, [r0]                                                                     <- extra in compiled
movs r2, #0x80                                                                    <- extra in compiled
                                        ldrb r2, [r0]                             <- missing from compiled
                                        movs r1, #0x80                            <- missing from compiled
orrs r1, r2                             orrs r1, r2
strb r1, [r0]                           strb r1, [r0]
ldrb r1, [r4]                           ldrb r1, [r4]
adds r0, r5, #0                         adds r0, r5, #0
bl #0x80cd620                                                                     <- extra in compiled
b #0x80ccfa8                                                                      <- extra in compiled
                                        smlsd r0, r6, r8, lr                      <- missing from compiled
                                        movs r0, r0                               <- missing from compiled
cmp r1, #0xff                           cmp r1, #0xff
bne #0x80ccfa8                          bne #0x80ccfa8
ldrb r0, [r4]                           ldrb r0, [r4]
adds r1, r5, #0                         adds r1, r5, #0
adds r1, #0x3d                          adds r1, #0x3d
strb r0, [r1]                           strb r0, [r1]
adds r4, #2                             adds r4, #2
adds r6, #1                             adds r6, #1
ldrb r0, [r7]                           ldrb r0, [r7]
cmp r6, r0                              cmp r6, r0
blt #0x80ccf6c                                                                    <- extra in compiled
                                        blt #0x80ccf6a                            <- missing from compiled
pop {r4, r5, r6, r7}                    pop {r4, r5, r6, r7}
pop {r0}                                pop {r0}
bx r0                                   bx r0
```
