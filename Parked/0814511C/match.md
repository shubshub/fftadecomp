# match report - 0x0814511C

* source: `src/0814511C.c`
* verification: `elf-symbol-cfg-leaf-v2`
* source SHA-256: `ff079722d4c217e9115fa98e3ddfbafac010187b7acfe73ec046373d34081b78`
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `021c0904090c536b0448834204d1d184918480204000108570470000536d736870b51448` (36 bytes)
* compiled : `00b5021c09040b0c516b0548814204d1d384938480204000108501bc00470000536d7368`
* source plausibility: plausible
* hand-asm allow list: not listed

**NOT MATCHING - bytes differ** - 25/36 bytes

```
compiled                                rom
push {lr}                                                                         <- extra in compiled
adds r2, r0, #0                         adds r2, r0, #0
lsls r1, r1, #0x10                      lsls r1, r1, #0x10
lsrs r3, r1, #0x10                                                                <- extra in compiled
ldr r1, [r2, #0x34]                                                               <- extra in compiled
ldr r0, [pc, #0x14]                                                               <- extra in compiled
cmp r1, r0                                                                        <- extra in compiled
bne #0x8145136                                                                    <- extra in compiled
strh r3, [r2, #0x26]                                                              <- extra in compiled
strh r3, [r2, #0x24]                                                              <- extra in compiled
                                        lsrs r1, r1, #0x10                        <- missing from compiled
                                        ldr r3, [r2, #0x34]                       <- missing from compiled
                                        ldr r0, [pc, #0x10]                       <- missing from compiled
                                        cmp r3, r0                                <- missing from compiled
                                        bne #0x8145134                            <- missing from compiled
                                        strh r1, [r2, #0x26]                      <- missing from compiled
                                        strh r1, [r2, #0x24]                      <- missing from compiled
movs r0, #0x80                          movs r0, #0x80
lsls r0, r0, #1                         lsls r0, r0, #1
strh r0, [r2, #0x28]                    strh r0, [r2, #0x28]
pop {r0}                                                                          <- extra in compiled
bx r0                                                                             <- extra in compiled
                                        bx lr                                     <- missing from compiled
                                        movs r0, r0                               <- missing from compiled
                                        ldr r3, [r2, #0x54]                       <- missing from compiled
```
